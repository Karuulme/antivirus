#include "scanresultoperations.h"
scanResultOperations::scanResultOperations(QObject *parent): QObject{parent}
{
    getMac();
}
void scanResultOperations::getProgramData(){
    wchar_t  appData[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_DEFAULT, appData)))
    {
        quarantineAddress=QString::fromWCharArray(appData);
    }
    quarantineAddress+="/Antivirus/quarantine/";
}
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
void scanResultOperations::Decrypt(QString file){
    wchar_t  appData[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_DEFAULT, appData);
    std::wstring ws( appData);
    std::string file_DESKTOP( ws.begin(), ws.end() );

    std::string aaa = mac_Address.toStdString();
    long  key = 0;
    for (int i = 0,j=10; i< aaa.length();i++,j*=10) {
        int t = aaa[i];
        key+= t*j;
    }
    char c;
    std::string in=file.toStdString();
    std::ifstream fin;
    std::ofstream fout;
    fin.open(in.c_str(), std::ios::binary);
    in = file_DESKTOP+"Quarantine.exe";  // DOSYADADN ALINACAK
    fout.open(in.c_str(), std::ios::binary);
    while (!fin.eof())
    {
        fin >> std::noskipws >> c;
        int temp = (c - key);
        fout << (char)temp;
    }
    fin.close();
    fout.close();
}
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
    int ans;
    long  key = 0;
    for (int i = 0,j=10; i< aaa.length();i++,j*=10) {
        int t = aaa[i];
        key+= t*j;
    }
    std::string in= filePath.toStdString();
    char c;
    std::ifstream fin;
    {
        char c;
        std::ifstream fin;
        std::ofstream fout;
        fin.open(in.c_str(), std::ios::binary);
        in = quarantineAddress.toStdString()+"//"+retValue.toStdString();
        fout.open(in.c_str(), std::ios::binary);
        while (!fin.eof())
        {
            fin >> std::noskipws >> c;
            int temp = (c - key);
            fout << (char)temp;
        }
        fin.close();
        fout.close();
    }
}
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
