#include "../Headers/filepathtransactions.h"

filePathTransactions::filePathTransactions(QObject *parent): QObject{parent}
{
}
//-----------------------------------------------------------------------------------------
int  filePathTransactions::setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value) { // KAYIT DEFTERİNE VERİ EKLEME VE GÜNCELLEME
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
    if (reg.pRunCount !=-1)
    {
        reg.pRunCount=0;
        if(KDllSource > reg.pRunCount){
            //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            // DEĞERİ KÜÇÜK İSE
            // DLL injection YAPILACAK
            emit setDllEnjection(pID);
            //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        }
        if(_identificationConfirmation){
            setRegCreateBank(KMachine, KBank + reg.pFile, "pRunCount", KToString(reg.pRunCount));// güncelleme
        }
    }
    else{// yeni kayıt

        if(pID==-1){
            regeditNewRecord(reg,200);
        }else{
            emit setDllEnjection(pID);
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
    regListIndex++;
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
    for (int i = 0; i < regListIndex; i++){
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
void filePathTransactions::getfileChangesNotification(QString filePath){ // BİR .EXE DOSYASI OLUŞTURULDUĞUNDA BURAYA GELİR
    RegProgramList fileChangesProgram;
    fileChangesProgram.pFile=KToString(1000 +regListIndex);
    fileChangesProgram.pHash=getfileHash(filePath).toStdString();
    if(fileChangesProgram.pHash!="000"){
        if(!boolRegListControl(fileChangesProgram.pHash)){
            regeditNewRecord(fileChangesProgram);
            //Bundan sonra taramaya gidecek
        }
    }
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getUserDefinitions_FileOperations(QVector<QString>* regInstallProgram){
    regListIndex=0;
    regList.clear();
    setRegCreateBank(KMachine,KLocal,"Time",KToString(KIdentification_Time));
    std::thread  userDefinitions(&filePathTransactions::getUserDefinitions_FileOperations_Thread, this, *regInstallProgram);
    userDefinitions.detach();
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getUserDefinitions_FileOperations_Thread(QVector<QString> regInstallProgram){
    for(int i=0;i<regInstallProgram.size();i++){
        // TARAMAYA GİDECEK GÜVENLİ İSE KAYIT DEFTERİNE EKLENECEK
        m_userDefinitions_UploadIndexNo=QString::number(i)+"*&*"+QString::number(regInstallProgram.size());
        setRegQuestion(regInstallProgram.at(i),-1);
        emit userDefinitions_UploadIndexNoChanged();
    }

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
QString  filePathTransactions::get_storage() {
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
    Py_Initialize();
    pName = PyUnicode_FromString("MalwareAnalysis");
    pModule = PyImport_Import(pName);
    pFunc = PyObject_GetAttrString(pModule, "malwarePath");
    pArgs = PyTuple_New(2);
    std::thread  scanThread(&filePathTransactions::scanDiskThread, this, firstFilePath,total);
    scanThread.join();
    Py_DECREF(pArgs);
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    scanHDDName="";
    setscaningDisk(scanHDDName);
    breakScanThread=false;
    m_scandisk_status=false;
    emit scandisk_status_changed();
    setscaningDisk("");

}
//-----------------------------------------------------------------------------------------
void filePathTransactions::scanDiskThread(std::string firstFilePath,long double total){
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
                if(fileName[netLength-1]=='e' && fileName[netLength-2]=='x' && fileName[netLength-3]=='e'){
                    PyObject* pValue = PyLong_FromLong(9);
                    PyTuple_SetItem(pArgs, 0, pValue);
                    PyObject* pValue2 = PyLong_FromLong(5);
                    PyTuple_SetItem(pArgs, 1, pValue2);
                    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);

                    if (PyLong_Check(pResult)) {
                        long result = PyLong_AsLong(pResult);
                        qDebug() << "result: " << result;
                        Sleep(1000);
                    }
                    /*setSescanedFileName(fileName+"q:*!"+QString::number(malwareListIndex)+"q:*!"+QString::fromStdString(firstFilePath));
                    malwareList[malwareListIndex]=QString::fromStdString(firstFilePath).replace("\\\\","\\")+"\\"+fileName;
                    malwareListIndex++;*/
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
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_get_storage(){
    emit storage_changed();
    setscaningDisk(scanHDDName);
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::set_ScanResultApply(){
    emit setApplyResults(malwareList,malwareListOptions,virusOptionIndex,computerOptionIndex);
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
//file:///C:/Users/karuulme/Documents/anivirus/pythonCode
int filePathTransactions::machineLearning(Kstring filePath){


    return 1;
}
