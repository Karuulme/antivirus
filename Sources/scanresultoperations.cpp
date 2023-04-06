#include "../Headers/scanresultoperations.h"
scanResultOperations::scanResultOperations(QObject *parent): QObject{parent}
{
    getMac();
    getAppDataAddress();
    encrypt("C:\\Users\\karuulme\\Desktop\\ConsoleApplication8.exe");
    //Decrypt("C:\\Users\\karuulme\\AppData\\Local\\Vkarul\\e2583914785571ae1ddd17cae975dda1b8543491bec9b525dd5a643b8af40f45");
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::getAppDataAddress(){
    wchar_t  appData[MAX_PATH];
    std::string file_DESKTOP;
    SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_DEFAULT, appData);
    quarantineAddress=QString::fromWCharArray(appData)+"\\"+QString::fromStdString(KProgramName)+"\\";
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
void scanResultOperations::Decrypt(QString filePath){
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

    QString str_verification;
    char aa;
    BOOL b_verification=FALSE;
    while (readFile.get(c)) {
        aa=(char)(c + key);
        if (b_verification) {
            writeFile << aa;
        } else {
            str_verification += QString::fromLatin1(&aa, 1);
            if (str_verification.contains("X*HTZ*") && !b_verification) {
                b_verification = TRUE;
                in =  str_verification.remove("X*HTZ*").toStdString();
                writeFile.open(in.c_str(), std::ios::binary | std::ios::app);
            }
        }
    }
    readFile.close();
    writeFile.close();
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
    char* bolen="X*HTZ*";
    for (int i = 0; i < 6; i++) {
        writeFile << (char)(bolen[i]-key);
    }
    while (readFile.get(c)) {
           writeFile << (char)(c - key);
    }
    while (readFile.good())
    {
        readFile.get(c);
        int temp = (c - key);
        writeFile << (char)temp;
    }
    readFile.close();
    writeFile.close();
    remove(filePath.toStdString().c_str());
    Decrypt(in.c_str());
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::virusProcesses(QString path,int Options){
    switch(Options){
    case 0: // Quarantine
        qDebug()<<"DOSYAYI KARANTINAYA AL";
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////encrypt(path);/////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    break;
    case 1: // Delete
        qDebug()<<"DOSYAYI SIL";
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////////remove(path);/////////////////////////////
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
        //////ExitWindowsEx(EWX_SHUTDOWN,SHTDN_REASON_MINOR_MAINTENANCE);//////
        ///////////////////////////////////////////////////////////////////////

    break;
    case 2: //Restart
         qDebug()<<"BILGISAYARI YENIDEN BASLAT";
         ///////////////////////////////////////////////////////////////////////
         ////ExitWindowsEx(EWX_RESTARTAPPS,SHTDN_REASON_MINOR_MAINTENANCE);/////
         ///////////////////////////////////////////////////////////////////////
    break;
    default:

    break;
    }
}
//-----------------------------------------------------------------------------------------
void scanResultOperations::getApplyResults(QMap<int,QString> malwaress,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions){
    for(int i=0;i<malwaress.size();i++){
        if(virusOptions==0){
            virusProcesses(malwaress[i],malwareListOptions[i]);
        }
        else{
            virusProcesses(malwaress[i],virusOptions-1);
        }
    }
    computerOperations(computerOptions);
}
//-----------------------------------------------------------------------------------------
