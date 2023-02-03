#include "../Headers/securefile.h"

secureFile::secureFile(QObject *parent): QObject{parent}{

}
void secureFile::setStart(){
    wchar_t  appData[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_DEFAULT, appData);
    std::wstring ws( appData);
    std::string test( ws.begin(), ws.end() );
    filePathDESKTOP=QString::fromStdString(test);
    filePathDESKTOP=filePathDESKTOP.replace("\\","/");
    getRegSecureFiles();
}
void secureFile::setsecureFiles(QString childFileName){
    m_secureFiles=childFileName;
    emit secureFilesChanged();
}
QString secureFile::getsecureFiles(){
    return m_secureFiles;
}
Kstring secureFile::KcharToString(char value[256])
{
    Kstring target;
    for (int i = 0; i < 256;i++) {
        if (value[i] == '\0')
            break;
        target += value[i];
    }
    return target;
}


int secureFile::StringToWString(Kwstring& ws, Kstring& s)
{
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
    return 0;
}
int secureFile::getRegSecureFiles()
{
    regListNum = 0;
    PVOID   pvData = {};
    LPDWORD pcbData = (LPDWORD)pvData;
    HKEY  regKey;

    Kstring pathX=KSecure;
    std::wstring name;
    StringToWString(name, pathX);
    const wchar_t* szName = name.c_str();
    int error = 0;
    if(RegOpenKeyEx(regMachine, szName, 0, KEY_ALL_ACCESS | KEY_QUERY_VALUE, &regKey)!= ERROR_SUCCESS)
    {
        error = GetLastError();
        return error;
    }
    TCHAR    achKey[_MAX_PATH];
    TCHAR    achClass[MAX_PATH] = TEXT("");
    DWORD    cchClassName = MAX_PATH;
    DWORD    cSubKeys = 0;
    DWORD    cbMaxSubKey;
    DWORD    cchMaxClass;
    DWORD    cValues;
    DWORD    cchMaxValue;
    DWORD    cbMaxValueData;
    DWORD    cbSecurityDescriptor;
    FILETIME ftLastWriteTime;
    DWORD retCode;
    DWORD BufferSize = BUFFER;
    if(RegQueryInfoKey(regKey,achClass,&cchClassName,NULL,&cSubKeys,&cbMaxSubKey,&cchMaxClass,&cValues,&cchMaxValue,&cbMaxValueData,&cbSecurityDescriptor,&ftLastWriteTime)!=ERROR_SUCCESS)
    {
        error = GetLastError();
        return error;
    }
    DWORD   cbName;
    for (int i= 0; i < cSubKeys; i++) {
        cbName = _MAX_PATH;
        retCode = RegEnumKeyEx(regKey, (DWORD)i,achKey,&cbName,NULL,NULL,NULL,&ftLastWriteTime);
        if (retCode == ERROR_SUCCESS)
        {
            RegSecureFile regSecureFile;
            std::string str;
            std::wstring wStr = achKey;
            str = std::string(wStr.begin(), wStr.end());
            Kstring path2 = pathX + str;
            char value[BUFFER];
            RegGetValueA(regMachine, path2.c_str(), "fKey", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regSecureFile.fKey = KcharToString(value);
            RegGetValueA(regMachine, path2.c_str(), "fPath", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regSecureFile.fPath = KcharToString(value);
            regSecureFile.fFile = str;
            secureFileRegList[secureFileIndex] = regSecureFile;
            secureFileIndex++;
            KSpace(value);

            setsecureFiles(QString::fromStdString("Null:?!?:"+regSecureFile.fPath+":?!?:"+regSecureFile.fKey));// kayıt defterinden gelen bir kayıf ise standar olarak gönderiyoruz
        }
    }
    RegCloseKey(regKey);
    return 0;
}
int  secureFile::setRegCreateRecure(HKEY hKey, Kstring path, Kstring key, Kstring value) { // KAYIT DEFTERİNE VERİ EKLEME VE GÜNCELLEME
    Kstring sPath;
    Kstring sKey= key;
    Kstring sValue= value;
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
    LONG res2 = RegSetValueExA(hkRegOpen, (LPCSTR)sKey.c_str(), 0, REG_SZ, (LPBYTE)sValue.c_str(), strlen((char*)sValue.c_str()) + 1);
    if (res2 != ERROR_SUCCESS)
        return res2;
    RegCloseKey(hkRegOpen);
    return 0;
}
int secureFile::folderPathControl(QString path){
    if(path.contains(filePathDESKTOP)){
        for(int i=0;i<secureFileIndex;i++){
            if(QString::fromStdString(secureFileRegList[i].fPath).contains(path)){
                return -1;
            }
        }
    }
    else
        return -1;
    return 1;
}
void secureFile::set_folderPath(QString parentFileName){
    parentFileName=parentFileName.replace("file:///","");
    if(folderPathControl(parentFileName)>0){
        secureFileIndex++;
        QString Filepassword = QString::fromUtf8(getRandomSha256().toHex());
        setRegCreateRecure(regMachine,KSecure+KToString(1000+secureFileIndex),"fPath",parentFileName.toStdString());
        setRegCreateRecure(regMachine,KSecure+KToString(1000+secureFileIndex),"fKey",Filepassword.toStdString());

        secureFileRegList[secureFileIndex-1].fPath=parentFileName.toStdString();
        secureFileRegList[secureFileIndex-1].fFile=KToString(1000+secureFileIndex);
        secureFileRegList[secureFileIndex-1].fKey=Filepassword.toStdString();
        setsecureFiles("new:?!?:"+parentFileName+":?!?:"+Filepassword);// Yeni eklendiğini belirtmek için başına "new" ekliyoruz
        Kstring newFolderPath=parentFileName.toStdString()+"/"+Filepassword.toStdString();
        CreateDirectoryA(newFolderPath.c_str(),NULL);
    }
}
void secureFile::set_RecureOpenFile(QString parentFileName){
    Kstring shelpath=parentFileName.toStdString();
    ShellExecuteA(NULL, "open",shelpath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
QByteArray secureFile::getRandomSha256(){
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;

    QByteArray randomData;
    randomData.resize(32);
    for (int i = 0; i < randomData.size(); ++i) {
        randomData[i] = static_cast<char>(distr(eng) & 0xff);
    }
    return QCryptographicHash::hash(randomData, QCryptographicHash::Sha256);
}















