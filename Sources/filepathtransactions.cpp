#include "../Headers/filepathtransactions.h"
filePathTransactions::filePathTransactions(QObject *parent): QObject(parent) {
    _connection = new Pythonconnection(this);
    _connection->moveToThread(threadConnection);
    threadConnection->start();
    connect(this, &filePathTransactions::setdataWillSendToScan, _connection, &Pythonconnection::getdataWillSendToScan);
    //setSescanedFileName("ornek_1.exeq:*!1q:*!C:\\Users\\karuulme\\Desktop\\");
}
//-----------------------------------------------------------------------------------------
filePathTransactions::~filePathTransactions(){
    threadConnection->quit();
    threadConnection->wait();
    delete _connection;
    delete threadConnection;
}
//-----------------------------------------------------------------------------------------
int  filePathTransactions::setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value) { // KAYIT DEFTERİNE VERİ EKLEME VE GÜNCELLEME
    qDebug()<<QString::fromStdString(path)<<"----"<<QString::fromStdString(value);
    Kstring sPath;
    for (int i = 0; i < path.length(); i++) {		//path space clear; //boşluk olduğunda hatalı dosya işlemi yapıyor.
        if (path[i] != ' ') {
            sPath += path[i];
        }
    }
    HKEY hkRegOpen;
    DWORD dRegReturn;
    sPath = sPath + "\0";
    LONG res1 = RegCreateKeyExA(hKey, sPath.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkRegOpen, &dRegReturn);
    if (res1 != ERROR_SUCCESS)
        return res1;
    LONG res2 = RegSetValueExA(hkRegOpen, (LPCSTR)key.c_str(), 0, REG_SZ, (LPBYTE)value.c_str(), strlen((char*)value.c_str()) + 1);
    if (res2 != ERROR_SUCCESS)
        return res2;
    RegCloseKey(hkRegOpen);
    return 0;
}//-----------------------------------------------------------------------------------------
void filePathTransactions::getProgramTime(unsigned __int8 value){
    setRegCreateBank(KMachine,KLocal,"Time",std::to_string(value));
}
//-----------------------------------------------------------------------------------------
int filePathTransactions::setRegQuestion(QString filePath,unsigned long int pID){// DOSYA HASH'LEME VE KAYIT İŞLEMLERİ
    RegProgramList reg;
    reg.pHash=getfileHash(filePath).toStdString();
    if(reg.pHash=="000"){
        return 1;
    }
    reg = upRegListControl(reg.pHash);
    if (reg.pRunCount !=-1){
        if(KDllSource > reg.pRunCount){

            //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            // DEĞERİ KÜÇÜK İSE
            // DLL injection YAPILACAK
            //emit setDllEnjection(pID);
            //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        }
        if(_identificationConfirmation){
            qDebug()<<"ESKİ KAYIT";
            setRegCreateBank(KMachine, KBank + reg.pFile,"pRunCount", KToString(reg.pRunCount));// güncelleme
        }
    }
    else{// yeni kayıt
        qDebug()<<"YENİ KAYIT";
        if(pID==-1){
            regeditNewRecord(reg,200);
        }else{
            //emit setDllEnjection(pID);
            regeditNewRecord(reg);
        }
        //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //DLL injection YAPILACAK
        //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    }
    return 0;
}
//-----------------------------------------------------------------------------------------
QString filePathTransactions::getfileHash(QString filePath){ //DOSYA HASH DEĞERİ
    QString retValue="000";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray exeFile=file.readAll();
        QString hash = QString(QCryptographicHash::hash((exeFile+"kar"+"ul"),QCryptographicHash::Sha256).toHex());
        retValue= hash.toLocal8Bit().data();
    }
    file.close();
    return retValue;
}
//-----------------------------------------------------------------------------------------
int filePathTransactions::regeditNewRecord(RegProgramList regProgram,int runCount){ //YENİ KAYIT EKLEME , -1 olmamasının şartı kullanıcı tanımınlarının eklenmesi. onların değerleri 101 olarak gelir
    qDebug()<<QString::fromStdString(regProgram.pHash);
    regListIndex++;
    regProgram.pRunCount++;
    regProgram.pFile=KToString(1000 +regListIndex);
    setRegCreateBank(KMachine, KBank + KToString(1000 +regListIndex), "pHash", regProgram.pHash);
    setRegCreateBank(KMachine, KBank + KToString(1000 +regListIndex), "pRunCount", KToString(runCount ==-1 ? regProgram.pRunCount:runCount));
    regList[regListIndex-1]=regProgram;
    return 0;
}
//-----------------------------------------------------------------------------------------
RegProgramList filePathTransactions::upRegListControl(Kstring regg) { // LİSTEDEN KAYDI BULUR VE +1 EKLEYEREK GERİ DÖNDÜRÜR

    RegProgramList regProgramList;
    regProgramList.pHash=regg;
    regProgramList.pRunCount= - 1;
    //qDebug()<<"***********************"<<"boyut:"<<regListIndex;
    for (int i = 0; i < regListIndex; i++){
       //qDebug()<<QString::fromStdString(regList[i].pHash);
        if (regList[i].pHash == regg) {
            regList[i].pRunCount++;
            regProgramList = regList[i];
            return regProgramList;
        }
    }
    return regProgramList;
}
//-----------------------------------------------------------------------------------------
bool filePathTransactions::boolRegListControl(Kstring regg){
    for (int i = 0; i < regListIndex; i++)
    {
        if (regList[i].pHash == regg) {
            return true;
        }
    }
    return false;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getFilePahtReg(QString  filePath,unsigned long int pID){//AÇILAN İŞLEMLER BURAYA GÖNDERİLİR
    setRegQuestion(filePath,pID);
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getRegList(Kmap<int, RegProgramList> reg){// BAŞLANGIÇTA KAYIT DEFTERİNDEKİ LİSTE BURAYA GÖNDERİLİR
    regList=reg;
    regListIndex=reg.size();
}
//-----------------------------------------------------------------------------------------
// BİR .EXE ve .dll DOSYASI OLUŞTURULDUĞUNDA BURAYA GELİR
void filePathTransactions::getfileChangesNotification(QString filePath){
    qDebug()<<filePath;
    RegProgramList fileChangesProgram;
    fileChangesProgram.pFile=KToString(1000 +regListIndex);
    fileChangesProgram.pHash=getfileHash(filePath).toStdString();
    if(fileChangesProgram.pHash!="000"){
        if(!boolRegListControl(fileChangesProgram.pHash)){
            regeditNewRecord(fileChangesProgram);
            _connection->mxGlobalScan.lock();
            machineLearning(filePath);
        }
    }
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getUserDefinitions_FileOperations(QVector<QString>* regInstallProgram){ // userdefinition.cpp dan buraya kayıtlı ve açık programlar gelir
    setRegCreateBank(KMachine,KLocal,"Time",KToString(KIdentification_Time));
    std::thread  userDefinitions(&filePathTransactions::getUserDefinitions_FileOperations_Thread, this, *regInstallProgram);
    userDefinitions.detach();
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getUserDefinitions_FileOperations_Thread(QVector<QString> regInstallProgram){

    for(int i=0;i<regInstallProgram.size();i++){
        _connection->mxGlobalScan.lock();
        // TARAMAYA GİDECEK GÜVENLİ İSE KAYIT DEFTERİNE EKLENECEK
        if(machineLearning(regInstallProgram.at(i))==1){

            QStringList file=regInstallProgram.at(i).split("\\");
            QString file_Name=file[file.size()-1];
            file.removeLast();
            QString file_Path=file.join("\\");
            setSescanedFileName(file_Name+"q:*!"+QString::number(malwareListIndex)+"q:*!"+file_Path);
            malwareList[malwareListIndex]=file_Path+"\\"+file_Name;
            malwareListIndex++;

        }
        else{
            setRegQuestion(regInstallProgram.at(i),-1);
        }
        Sleep(50);
        m_userDefinitions_UploadIndexNo=QString::number(i)+"*&*"+QString::number(regInstallProgram.size());
        emit userDefinitions_UploadIndexNoChanged();
    }
    //_connection->mxGlobalScan.unlock();
}
QString filePathTransactions::getuserDefinitions_UploadIndexNo(){
    return m_userDefinitions_UploadIndexNo;
}
//-----------------------------------------------------------------------------------------
bool filePathTransactions::get_scandisk_status(){
    return m_scandisk_status;
}
//-----------------------------------------------------------------------------------------
double filePathTransactions::byteToGb(long double byte) {
    double kilobyte;
    double megabyte;
    double gigabyte;
    kilobyte = byte / 1024;
    megabyte = kilobyte / 1024;
    gigabyte = megabyte / 1024;
    return gigabyte;
}
//-----------------------------------------------------------------------------------------
QString  filePathTransactions::get_storage() { // takılı sürücüleri alır
    QString  list;
    ULARGE_INTEGER p1, p2, p3;
    int driverNumbers = GetLogicalDrives();
    for (int i = 0;  i < 26; i++) {
        if ((1 << i) & driverNumbers) {
            char driverName[] = "A:\\";
            driverName[0] += i;
            if (GetDiskFreeSpaceExA(driverName, &p1, &p2, &p3) != 0) {
                list+=QString::fromStdString(driverName)+"/";
                list+=QString::number(byteToGb(p2.QuadPart),'f',1)+"/";
                list+=QString::number(byteToGb(p1.QuadPart),'f',1)+"@";
            }
        }
    }
    return list;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_scandisk(QString value,double total,double free){
    if(m_scandisk_status!=true){
        scanHDDName=value;
        setscaningDisk(scanHDDName);
        m_scandisk=value;
        m_scandisk_status=true;
        emit scandisk_status_changed();
        std::string firstFilePath = value.toStdString();
        std::thread  scanThread(&filePathTransactions::scanDiskThreadControl, this, firstFilePath,(total-free)*1024*1024*1024);
        scanThread.detach();
    }
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::scanDiskThreadControl(std::string firstFilePath,long double total){
    std::thread  scanThread(&filePathTransactions::scanDiskThread, this, firstFilePath,total);
    scanThread.join();
    scanHDDName="";
    setscaningDisk(scanHDDName);
    breakScanThread=false;
    m_scandisk_status=false;
    emit scandisk_status_changed();
    setscaningDisk("");
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::scanDiskThread(std::string firstFilePath,long double total){ //SEÇİLİ DİSKİ TARAR
    WIN32_FIND_DATAA fileInformation;
    HANDLE firstFile = FindFirstFileExA((firstFilePath+ "\\*").c_str(), FindExInfoStandard, &fileInformation, FindExSearchNameMatch, NULL, 0);
           do {
        if(breakScanThread)
            goto exit;
        if ((std::string)fileInformation.cFileName !="." && (std::string)fileInformation.cFileName != "..") {
            if (GetFileAttributesA((firstFilePath + "\\" + fileInformation.cFileName).c_str()) == FILE_ATTRIBUTE_DIRECTORY) {
                if(breakScanThread)
                    goto exit;
                scanDiskThread(firstFilePath + "\\" + fileInformation.cFileName,total);
            }
            else {
                QString fileName=QString::fromStdString(fileInformation.cFileName);
                int netLength=fileName.size();
                if(fileName.contains(".exe") || fileName.contains(".dll")){
                    _connection->mxGlobalScan.lock();
                    if(breakScanThread)
                        goto exit;
                    emit setdataWillSendToScan(QString::fromStdString(firstFilePath)+"\\"+fileName);
                    int wret=WaitForSingleObject(_connection->hEventReturnValue,100000);
                    if(breakScanThread)
                        goto exit;
                    if(wret==WAIT_TIMEOUT){
                        _connection->scanResult=true;
                    }
                    ResetEvent(_connection->hEventReturnValue);
                    if(_connection->scanResult==false){
                        setSescanedFileName(fileName+"q:*!"+QString::number(malwareListIndex)+"q:*!"+QString::fromStdString(firstFilePath));
                        malwareList[malwareListIndex]=QString::fromStdString(firstFilePath).replace("\\\\","\\")+"\\"+fileName;
                        malwareListIndex++;
                    }
                    Sleep(50);
                }
            }
        }
    } while (FindNextFileA(firstFile, &fileInformation));
exit:
    FindClose(firstFile);
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_scandiskClose(){
    breakScanThread=true;
    m_scandisk_status=false;
    if(autoScanResult)
        set_ScanResultApply();
    _connection->mxGlobalScan.unlock();
    SetEvent(_connection->hEventReturnValue);
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_get_storage(){
    emit storage_changed();
    setscaningDisk(scanHDDName);
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_ScanResultApply(){
    emit setApplyResults(malwareList,malwareListOptions,virusOptionIndex,computerOptionIndex);
    malwareList.clear();
    malwareListIndex=0;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_singleVirusChanges(int index,int setvalue){
    malwareListOptions[index]=setvalue;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_ScanResultAutoApply(int index){
    autoScanResult=index;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_VirusComputerOption(int virus,int computer){
    virusOptionIndex=virus;
    computerOptionIndex=computer;
}
//-----------------------------------------------------------------------------------------
QString filePathTransactions::getscanedFileName(){

    return m_scanedFileName;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::setSescanedFileName(QString value){
    m_scanedFileName=value;
    emit scanedFileName_changed();
}
//-----------------------------------------------------------------------------------------
QString filePathTransactions::getscaningDisk() {
    return m_scaningDisk;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::setscaningDisk(QString value) {
    m_scaningDisk=value;
    emit scaningDisk_changed();
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getVirusOne(QString filePath,int virusOptions,int index){
    malwareList.remove(index);
    malwareListIndex--;
    emit setVirusOne(filePath,virusOptions);
}
//-----------------------------------------------------------------------------------------
int filePathTransactions::machineLearning(QString filePath){ //
    emit setdataWillSendToScan(filePath);
    int wret=WaitForSingleObject(_connection->hEventReturnValue,100000);
    if(wret==WAIT_TIMEOUT){
        _connection->scanResult=true;
        return 0;
    }
    ResetEvent(_connection->hEventReturnValue);
    if(_connection->scanResult==false){
        return 1;
    }
    else{
        return 0;
    }
}
//-----------------------------------------------------------------------------------------
void  filePathTransactions::send(const QString message){
     emit setdataWillSendToScan(message);
}
//-----------------------------------------------------------------------------------------
Pythonconnection::Pythonconnection(QObject *parent): QObject(parent) {
     if (!server.listen(QHostAddress::LocalHost, MALWARE_SOCKET_PORT)) {
        qDebug() << "Could not start server";
     }
     qDebug() << "Server started on port " << server.serverPort();
     connect(&server, &QTcpServer::newConnection, this, &Pythonconnection::acceptConnection, Qt::DirectConnection);
     hEventReturnValue=CreateEventA(NULL,TRUE,FALSE,NULL);
     //startVirusDetectionProcess();
}
//-----------------------------------------------------------------------------------------
void Pythonconnection::acceptConnection() {
     clientConnection = server.nextPendingConnection();
     if (!clientConnection) {
        qDebug() << "Could not accept client connection";
        return;
     }
     connect(clientConnection, &QTcpSocket::readyRead, this, &Pythonconnection::readDataFromPython, Qt::DirectConnection);
}
//-----------------------------------------------------------------------------------------
void Pythonconnection::readDataFromPython() {
    while (clientConnection && clientConnection->bytesAvailable()) {
        QByteArray data = clientConnection->readAll();
        QString message = QString::fromUtf8(data).trimmed();
        qDebug()<<"Gelen dönüt:"<<message.toInt();
        scanResult=true;
        if(message.toInt()!=0){
            scanResult=false;
        }
        qDebug()<<"Sonuç:"<<message.toInt();


        qDebug()<<"serbes bırakıld";
        SetEvent(hEventReturnValue);
        mxGlobalScan.unlock();
    }
}
//-----------------------------------------------------------------------------------------
void Pythonconnection::getdataWillSendToScan(const QString sendedfilePath) {
    //qDebug()<<sendedfilePath;
    /*if(virusDetectionProcessStatus()<0){
        startVirusDetectionProcess();
        Sleep(10000);
    }*/
    scanResult=true;
    QString filePath = sendedfilePath.trimmed();
    filePath=filePath.replace("\\\\","\\");
    qDebug()<<"Güncel address:"<<sendedfilePath;
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out << filePath;
    if (clientConnection && clientConnection->isOpen()) {
       clientConnection->write(buffer);
    } else {
        qDebug() << "Client connection is not available";
    }
}
//-----------------------------------------------------------------------------------------
int Pythonconnection::startVirusDetectionProcess(){
    STARTUPINFO info = { sizeof(info)};
    if(!CreateProcess(NULL, (LPWSTR)filePathExe.unicode(), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfoVirusProcessDetection)){
        DWORD err = GetLastError();
        qDebug() << "Başarısız: " << err;
    }
    return 0;
}
//-----------------------------------------------------------------------------------------
int Pythonconnection::virusDetectionProcessStatus(){
    DWORD exitCode=0;
    if (GetExitCodeProcess(processInfoVirusProcessDetection.hProcess, &exitCode) != 0) {
        if (exitCode!= STILL_ACTIVE) {
            CloseHandle(processInfoVirusProcessDetection.hProcess);
            ResetEvent(hEventReturnValue);
            mxGlobalScan.unlock();
            return -1;
        }
    }
    return 1;
}
//-----------------------------------------------------------------------------------------
LPCWSTR Pythonconnection::QStringToLPCWSTR(const QString& qstr)
{
    std::vector<wchar_t> buffer(qstr.length() + 1);
    qstr.toWCharArray(buffer.data());
    return reinterpret_cast<LPCWSTR>(buffer.data());
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::setTest(QString adddress){

    qDebug()<<adddress;
    emit setdataWillSendToScan(adddress);
}




