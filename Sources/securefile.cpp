#include "../Headers/securefile.h"

secureFile::secureFile(QObject *parent): QObject{parent}{

}
//-----------------------------------------------------------------------------------------
void secureFile::setStart(){
    wchar_t  appData[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_DEFAULT, appData);
    std::wstring ws( appData);
    std::string test( ws.begin(), ws.end() );
    filePathDESKTOP=QString::fromStdString(test);
    filePathDESKTOP=filePathDESKTOP.replace("\\","/");
    getRegSecureFiles();
}
//-----------------------------------------------------------------------------------------
void secureFile::setsecureFiles(QString childFileName){
    m_secureFiles=childFileName;
    emit secureFilesChanged();
}
//-----------------------------------------------------------------------------------------
QString secureFile::getsecureFiles(){
    return m_secureFiles;
}
//-----------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------
int secureFile::StringToWString(Kwstring& ws, Kstring& s)
{
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
    return 0;
}
//-----------------------------------------------------------------------------------------
int secureFile::getRegSecureFiles(){
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
    for (int i= 0; i < (int)cSubKeys; i++) {
        cbName = _MAX_PATH;
        retCode = RegEnumKeyEx(regKey, (DWORD)i,achKey,&cbName,NULL,NULL,NULL,&ftLastWriteTime);
        if (retCode == ERROR_SUCCESS){
            RegSecureFile regSecureFile;
            std::string str;
            std::wstring wStr = achKey;
            str = std::string(wStr.begin(), wStr.end());
            Kstring path2 = pathX + str;
            char value[BUFFER];
            BufferSize = BUFFER;
            RegGetValueA(regMachine, path2.c_str(), "fKey", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regSecureFile.fKey = KcharToString(value);
            BufferSize = BUFFER;
            RegGetValueA(regMachine, path2.c_str(), "fPath", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regSecureFile.fPath = KcharToString(value);
            regSecureFile.fFile = path2;
            regSecureFile.fRegFileName=str;
            KSpace(value);
            _secureList.append(regSecureFile);
            setsecureFiles(QString::fromStdString("Null:?!?:"+regSecureFile.fPath+":?!?:"+regSecureFile.fKey));// kayıt defterinden gelen bir kayıf ise standart olarak gönderiyoruz
        }
    }
    setSecureList(&_secureList);
    RegCloseKey(regKey);
    return 0;
}
//-----------------------------------------------------------------------------------------
int  secureFile::setRegCreateRecure(HKEY hKey, Kstring path, Kstring key, Kstring value) { // KAYIT DEFTERİNE VERİ EKLEME VE GÜNCELLEME
    Kstring sPath;
    Kstring sKey= key;
    Kstring sValue= value;
    for (int i = 0; i < (int)path.length(); i++) {//path space clear; //boşluk olduğunda hatalı dosya işlemi yapıyor.
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
//-----------------------------------------------------------------------------------------
int secureFile::folderPathControl(QString path){
    if(path.contains(filePathDESKTOP)){
        for(int i=0;i<_secureList.size();i++){
            if(QString::fromStdString(_secureList.at(i).fPath).contains(path)){
                return -1;
            }
        }
    }
    else
        return -1;
    return 1;
}
//-----------------------------------------------------------------------------------------
void secureFile::set_folderPath(QString parentFileName){
    parentFileName=parentFileName.replace("file:///","");
    QList<int> secureListFRegFileName;
    for (int i = 0; i < _secureList.size(); ++i) {
        secureListFRegFileName.append(KStringToInt(_secureList.at(i).fRegFileName));
    }
    int secureFileIndex;
    if(_secureList.size()!=0){
        std::sort(secureListFRegFileName.begin(), secureListFRegFileName.end(), std::greater<int>());
         secureFileIndex=secureListFRegFileName.at(0)+1;
    }
    else{
         secureFileIndex=1001;
    }
    if(folderPathControl(parentFileName)>0){
        QString Filepassword = QString::fromUtf8(getRandomSha256().toHex());
        setRegCreateRecure(KMachine,KSecure+KToString(secureFileIndex),"fPath",parentFileName.toStdString());
        setRegCreateRecure(KMachine,KSecure+KToString(secureFileIndex),"fKey",Filepassword.toStdString());
        setsecureFiles("new:?!?:"+parentFileName+":?!?:"+Filepassword);// Yeni eklendiğini belirtmek için başına "new" ekliyoruz
        Kstring newFolderPath=parentFileName.toStdString()+"/"+Filepassword.toStdString();
        CreateDirectoryA(newFolderPath.c_str(),NULL);
        RegSecureFile regSecureFile;
        regSecureFile.fKey=Filepassword.toStdString();
        regSecureFile.fFile=KSecure+KToString(secureFileIndex);
        regSecureFile.fPath=parentFileName.toStdString();
        regSecureFile.fRegFileName=KToString(secureFileIndex);
        _secureList.append(regSecureFile);
        setSecureList(&_secureList);
    }
}
//-----------------------------------------------------------------------------------------
void secureFile::set_RecureOpenFile(QString parentFileName){
    Kstring shelpath=parentFileName.toStdString();
    ShellExecuteA(NULL, "open",shelpath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
//-----------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------
LPCTSTR qstringToLPCTSTR(const QString& str)
{
#ifdef UNICODE
    return reinterpret_cast<const wchar_t*>(str.utf16());
#else
    QByteArray utf8Data = str.toUtf8();
    return utf8Data.constData();
#endif
}
//-----------------------------------------------------------------------------------------
int secureFile::set_RecureDeleteFile(QString rKey,QString rPath){
    int i=0;
    for (; i < _secureList.size(); ++i) {
        if(_secureList.at(i).fKey==rKey.toStdString()){
            break;
        }
    }
    LPCTSTR deleteAddress=qstringToLPCTSTR(QString::fromStdString(_secureList.at(i).fFile));
    BOOL bSuccess=RegDelnode(HKEY_CURRENT_USER, deleteAddress);
    if(bSuccess==FALSE){
        QString returnValue=rKey+"!secure!"+"unsuccessful";
        setSecureProcessed(returnValue);
    }
    else{
        _secureList.removeAt(i);
        QString returnValue=rKey+"!secure!"+"successful";
        setSecureProcessed(returnValue);
    }
    return 0;
}
//-----------------------------------------------------------------------------------------
BOOL secureFile::RegDelnodeRecurse (HKEY hKeyRoot, LPTSTR lpSubKey)
{
    LPTSTR lpEnd;
    LONG lResult;
    DWORD dwSize;
    TCHAR szName[MAX_PATH];
    HKEY hKey;
    FILETIME ftWrite;

    // First, see if we can delete the key without having
    // to recurse.

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);

    if (lResult == ERROR_SUCCESS)
        return TRUE;

    lResult = RegOpenKeyEx (hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        if (lResult == ERROR_FILE_NOT_FOUND) {
            printf("Key not found.\n");
            return TRUE;
        }
        else {
            printf("Error opening key.\n");
            return FALSE;
        }
    }

    // Check for an ending slash and add one if it is missing.

    lpEnd = lpSubKey + lstrlen(lpSubKey);

    if (*(lpEnd - 1) != TEXT('\\'))
    {
        *lpEnd =  TEXT('\\');
        lpEnd++;
        *lpEnd =  TEXT('\0');
    }

    // Enumerate the keys

    dwSize = MAX_PATH;
    lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
                           NULL, NULL, &ftWrite);

    if (lResult == ERROR_SUCCESS)
    {
        do {

            *lpEnd = TEXT('\0');
            StringCchCat(lpSubKey, MAX_PATH * 2, szName);

            if (!RegDelnodeRecurse(hKeyRoot, lpSubKey)) {
                break;
            }

            dwSize = MAX_PATH;

            lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
                                   NULL, NULL, &ftWrite);

        } while (lResult == ERROR_SUCCESS);
    }

    lpEnd--;
    *lpEnd = TEXT('\0');

    RegCloseKey (hKey);

    // Try again to delete the key.

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);

    if (lResult == ERROR_SUCCESS)
        return TRUE;

    return FALSE;
}
//-----------------------------------------------------------------------------------------
BOOL secureFile::RegDelnode (HKEY hKeyRoot, LPCTSTR lpSubKey)
{
    TCHAR szDelKey[MAX_PATH*2];
    StringCchCopy (szDelKey, MAX_PATH*2, lpSubKey);
    return RegDelnodeRecurse(hKeyRoot, szDelKey);
}
//-----------------------------------------------------------------------------------------
void secureFile::getUserDefinitions_Delete_Signal(){
    RegDelnode(KMachine, qstringToLPCTSTR(KBank));
}
//----------------------------------------------------------------------------------------
QString secureFile::getSecureProcessed(){
    //qDebug()<<m_secureProcessed;
    return m_secureProcessed;
}
//----------------------------------------------------------------------------------------
void secureFile::setSecureProcessed(QString secureValue){

    m_secureProcessed=secureValue;
    emit secureProcessedChanged();
}
//----------------------------------------------------------------------------------------











