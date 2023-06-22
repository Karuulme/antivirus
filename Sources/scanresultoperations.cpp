#include "../Headers/scanresultoperations.h"
scanResultOperations::scanResultOperations(QObject *parent): QObject{parent}
{
    getMac();
    getAppDataAddress();
    //setStart();
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::setStart(){
    findQuarantineFile();
}
void scanResultOperations::getAppDataAddress(){
    wchar_t  appData[MAX_PATH];
    std::string file_DESKTOP;
    SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_DEFAULT, appData);
    quarantineAddress=QString::fromWCharArray(appData)+"\\"+QString::fromStdString(KProgramName)+"\\";
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::setQuarantineFile(QString file){
    m_quarantineFile=file;
    emit quarantineFileChanged();
}
//-----------------------------------------------------------------------------------------
QString scanResultOperations::getQuarantineFile(){
    return m_quarantineFile;
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::findQuarantineFile(){
    quarentineFileNameList.clear();
    quarentineOrjinalFileNameList.clear();
    std::string aaa = mac_Address.toStdString();
    long  key = 0;
    for (int i = 0,j=10; i< aaa.length();i++,j*=10) {
        int t = aaa[i];
        key+= t*j;
    }
    char c;
    char aa;
    WIN32_FIND_DATAA fileInformation;
    HANDLE firstFile = FindFirstFileExA((quarantineAddress.toStdString() + "/*").c_str(), FindExInfoStandard, &fileInformation, FindExSearchNameMatch, NULL, 0);

    QString str_verification;
    int indexNo=0;
    do {
        if ((std::string)fileInformation.cFileName != "." && (std::string)fileInformation.cFileName != "..") {
            std::string fileName(fileInformation.cFileName);
            std::ifstream readFile;
            readFile.open(quarantineAddress.toStdString().c_str()+fileName, std::ios::binary);
            if (!readFile.is_open()) {
                continue;
            }
            int lineNumber=0;
            while (readFile.get(c)){
                aa=(char)(c + key);
                str_verification += QString::fromLatin1(&aa, 1);
                lineNumber++;
                if (str_verification.contains("X_2*HTZ*")) {
                    QStringList array=str_verification.split("X_1*HTZ*");
                    array[1].remove("X_2*HTZ*");
                    quarentineFileNameList.append(QString::fromStdString(fileName));
                    quarentineOrjinalFileNameList.append(array[0]);
                    setQuarantineFile(array[0]+"--"+array[1]+"--"+QString::fromStdString(KToString(indexNo)));
                    indexNo++;
                    readFile.close();
                    break;
                }
                if(lineNumber>258){
                    readFile.close();
                    break;
                }
            }
        }
    } while (FindNextFileA(firstFile, &fileInformation));
    FindClose(firstFile);
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::getQuarantineOptions(int indexNo,int OptionsNo){
    switch(OptionsNo){
        case 0: // delete
        if(remove(quarentineFileNameList.at(indexNo).toStdString().c_str())){
                QString returnValue=QString::number(indexNo)+"!quartine!"+"successful";
                setQuarantineProcessed(returnValue);
            }
            else{
                QString returnValue=QString::number(indexNo)+"!quartine!"+"unsuccessful";
                setQuarantineProcessed(returnValue);
            }
        break;
        case 1: // return
            //Decrypt(indexNo);
            if(Decrypt(indexNo)){
                QString returnValue=QString::number(indexNo)+"!quartine!"+"successful";
                setQuarantineProcessed(returnValue);
            }
            else{
                QString returnValue=QString::number(indexNo)+"!quartine!"+"unsuccessful";
                setQuarantineProcessed(returnValue);
            }
        break;
        default:
        break;
    }
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::getMac() {
    PIP_ADAPTER_INFO AdapterInfo;
    AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    ULONG SizePointer = sizeof(IP_ADAPTER_INFO);
    if (AdapterInfo != NULL) {
        if (GetAdaptersInfo(AdapterInfo, &SizePointer) == ERROR_BUFFER_OVERFLOW)
        {
            free(AdapterInfo);
            AdapterInfo = (IP_ADAPTER_INFO*)malloc(SizePointer);
        }
        if (GetAdaptersInfo(AdapterInfo, &SizePointer) == ERROR_SUCCESS) {

            for (int i = 0; i < AdapterInfo->AddressLength; i++) {
                mac_Address+= QString::number((int)AdapterInfo->Address[i]);
            }
        }
        free(AdapterInfo);
    }
//https://docs.google.com/document/d/1FLLpN588_OIlLsoEqNaB4OkjLx3ZKGk8TevD2cJppSo/edit
}
//-----------------------------------------------------------------------------------------
int scanResultOperations::Decrypt(int fileindex){

    QString filePath=quarantineAddress+quarentineFileNameList.at(fileindex);
    std::string in= filePath.toStdString();
    std::ifstream readFile;
    readFile.open(in.c_str(), std::ios::binary);
    if(!readFile.is_open()){
        setQuarantineFile(quarentineOrjinalFileNameList.at(fileindex));
        return -1;
    }
    std::string aaa = mac_Address.toStdString();
    long  key = 0;
    for (int i = 0,j=10; i< aaa.length();i++,j*=10) {
        int t = aaa[i];
        key+= t*j;
    }
    char c;
    std::ofstream writeFile;
    QString str_verification;
    char aa;
    BOOL b_verification=FALSE;
    while (readFile.get(c)) {
        aa=(char)(c + key);
        if (b_verification) {
            writeFile << aa;
        } else {
            str_verification += QString::fromLatin1(&aa, 1);
            if (str_verification.contains("X_2*HTZ*")) {
                b_verification = TRUE;
                QStringList array=str_verification.split("X_1*HTZ*");
                writeFile.open(array[0].toStdString().c_str(), std::ios::binary | std::ios::app);
            }
        }
    }
    readFile.close();
    writeFile.close();
    remove(filePath.toStdString().c_str());
    return 0;
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::encrypt(QString filePath){
    QString retValue="000";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray exeFile=file.readAll();
        QString hash = QString(QCryptographicHash::hash((exeFile+"kar"+"ul"),QCryptographicHash::Sha256).toHex());
        retValue= hash.toLocal8Bit().data();
    }
    file.close();
    std::string aaa = mac_Address.toStdString();
    long  key = 0;
    for (int i = 0,j=10; i< aaa.length();i++,j*=10) {
        int t = aaa[i];
        key+= t*j;
    }
    std::string in= filePath.toStdString();
    char c;
    std::ifstream readFile;
    std::ofstream writeFile;
    readFile.open(in.c_str(), std::ios::binary);
    in = quarantineAddress.toStdString()+retValue.toStdString();
    writeFile.open(in.c_str(), std::ios::binary);
    for (int i = 0; i <=filePath.toStdString().size()-1; i++) {
        writeFile<<(char)(filePath.toStdString()[i]-key);
    }
    char* bolen="X_1*HTZ*";
    for (int i = 0; i <sizeof(bolen); i++) {
        writeFile <<(char)(bolen[i]-key);
    }
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("dd.MM.yyyy hh:mm:ss");
    for (int i = 0; i < dateTimeString.size(); i++) {
        writeFile << (char)(dateTimeString.toStdString()[i]-key);
    }
    bolen="X_2*HTZ*";
    for (int i = 0; i < sizeof(bolen); i++) {
        writeFile <<(char)(bolen[i]-key);
    }
    while (readFile.get(c)) {
           writeFile << (char)(c - key);
    }
    readFile.close();
    writeFile.close();
    remove(filePath.toStdString().c_str());
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::virusProcesses(QString path,int Options){
    switch(Options){
    case 1: // Quarantine
        qDebug()<<"DOSYAYI KARANTINAYA AL";
        ///////////////////////////////////////////////////////////////////////
        encrypt(path);////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    break;
    case 2: // Delete
        qDebug()<<"DOSYAYI SIL";
        ///////////////////////////////////////////////////////////////////////
        remove(path.toUtf8().constData());/////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    break;
    default:

    break;
    }
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::computerOperations(int Options){
    switch(Options){
    case 0: //Wait

    break;
    case 1: //Shut Down
        qDebug()<<"BILGISAYARI KAPAT";
        ///////////////////////////////////////////////////////////////////////
        ExitWindowsEx(EWX_SHUTDOWN,SHTDN_REASON_MINOR_MAINTENANCE);//////
        ///////////////////////////////////////////////////////////////////////

    break;
    case 2: //Restart
         qDebug()<<"BILGISAYARI YENIDEN BASLAT";
         ///////////////////////////////////////////////////////////////////////
         ExitWindowsEx(EWX_RESTARTAPPS,SHTDN_REASON_MINOR_MAINTENANCE);/////
         ///////////////////////////////////////////////////////////////////////
    break;
    default:

    break;
    }
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::getApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions){
    for(int i=0;i<malwares.size();i++){
        if(virusOptions==0){
            if(malwareListOptions[i]!=0){
                virusProcesses(malwares[i],malwareListOptions[i]);
            }
        }
        else{
            virusProcesses(malwares[i],virusOptions-1);
        }
    }
    computerOperations(computerOptions);
    findQuarantineFile();
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::getVirusOne(QString filePath,int virusOptions){
    virusProcesses(filePath,virusOptions);
    if(virusOptions==1){
        findQuarantineFile();
    }
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::setQuarantineProcessed(const QString quarantineFile){
    m_quarantineProcessed=quarantineFile;
    emit quarantineProcessedChanged();
}
//-----------------------------------------------------------------------------------------
QString scanResultOperations::getQuarantineProcessed(){
    return m_quarantineProcessed;
}
//-----------------------------------------------------------------------------------------















