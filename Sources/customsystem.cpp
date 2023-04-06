#include "../Headers/customsystem.h"
#include <QChar>

CustomSystem::CustomSystem(QObject *parent): QObject{parent}
{
    /*getRegProgramsListThread.join();
    std::thread  getProcessListThread(&CustomSystem::getProcessList, this);
    getProcessListThread.detach();*/
}
//-----------------------------------------------------------------------------------------
CustomSystem::~CustomSystem()
{
    RegCloseKey(regMachine);
}
//-----------------------------------------------------------------------------------------
void CustomSystem::SetStart(){
    getRegProgramsList();
    getProcessList();
}
//-----------------------------------------------------------------------------------------
Kstring CustomSystem::KTcharToString(TCHAR value[1024])
{
    std::wstring test(&value[0]);
    Kstring test2(test.begin(), test.end());

    return test2;
}
//-----------------------------------------------------------------------------------------
Kstring CustomSystem::KWcharToString(wchar_t value[1024])
{
    Kwstring ws(value);
    Kstring str(ws.begin(), ws.end());
    KSpace(value);
    return str;
}
//-----------------------------------------------------------------------------------------
Kstring CustomSystem::KcharToString(char value[256])
{
    Kstring target;
    for (int i = 0; i < 256;i++) {
        if (value[i] == '\0')
            break;
        target += value[i];
    }
    KSpace(value);
    return target;
}
//-----------------------------------------------------------------------------------------
int CustomSystem::StringToWString(Kwstring& ws, Kstring& s)
{
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
    return 0;
}
//-----------------------------------------------------------------------------------------
QString KTcharToQString(TCHAR * value){

    return QString::fromWCharArray(value);
}
//-----------------------------------------------------------------------------------------
std::string KQStringToString(QString value){

    return value.toStdString();
}
//-----------------------------------------------------------------------------------------
void CustomSystem::getProcessList()
{
    HANDLE hProcessShot;
    PROCESSENTRY32 ProcessInformation;
    hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    ProcessInformation.dwSize = sizeof(PROCESSENTRY32);
    int i = 1;
    int numara = 1000;
    Kmap<Kstring,int>  runFirstList;
    if (Process32First(hProcessShot, &ProcessInformation) && INVALID_HANDLE_VALUE != hProcessShot){
        do
        {
            RegProgramList reg;
            HANDLE hProcessT;
            hProcessT = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessInformation.th32ProcessID);
            if (NULL != hProcessT) {
                wchar_t filePath[MAX_PATH];
                if(GetModuleFileNameExW(hProcessT,NULL,filePath,MAX_PATH)!=0){ //(!GetProcessImageFileName(hProcessT, filePath, sizeof(filePath) / sizeof(*filePath)) == 0) {
                    QFile file(QString::fromWCharArray(filePath));
                    if (file.open(QIODevice::ReadOnly)) {

                        QByteArray exeFile=file.readAll();
                        QString blah = QString(QCryptographicHash::hash((exeFile+"kar"+"ul"),QCryptographicHash::Sha256).toHex());
                        reg.pHash = blah.toLocal8Bit().data();
                    }
                    else{
                         file.close();
                         continue;
                    }
                    file.close();
                    KWcharToString(ProcessInformation.szExeFile);
                    if (reg.pHash != "") {
                        RegProgramList regRet;
                        regRet = upRegListControl(reg.pHash);
                        if (regRet.pRunCount !=-1) {
                            setRegCreateBank(HKEY_CURRENT_USER, KBank + regRet.pFile, "pRunCount", KToString(regRet.pRunCount + 1));
                        }
                        else {
                            if (runFirstList.find(reg.pHash)== runFirstList.end()) {
                                runFirstList[reg.pHash] = i;
                                setRegCreateBank(HKEY_CURRENT_USER, KBank + KToString(numara + i), "pHash", reg.pHash);
                                setRegCreateBank(HKEY_CURRENT_USER, KBank + KToString(numara + i), "pRunCount", KToString(reg.pRunCount));
                                i++;
                            }
                        }
                    }
                }
            }
            CloseHandle(hProcessT);
        } while (Process32Next(hProcessShot, &ProcessInformation));
    }
    CloseHandle(hProcessShot);
    runFirstList.clear();
}
//-----------------------------------------------------------------------------------------
int  CustomSystem::getRegProgramsList()
{
    regListNum = 0;
    PVOID   pvData = {};
    LPDWORD pcbData = (LPDWORD)pvData;
    HKEY  regKey;

    Kstring pathX=KBank;
    std::wstring name;
    StringToWString(name, pathX);
    const wchar_t* szName = name.c_str();
    DWORD BufferSize = 8192;
    int error = 0;
    if(RegOpenKeyEx(regMachine, szName, 0, KEY_ALL_ACCESS | KEY_QUERY_VALUE, &regKey)!= ERROR_SUCCESS)
    {
        error = GetLastError();
        return 1;
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
    if(RegQueryInfoKey(regKey,achClass,&cchClassName,NULL,&cSubKeys,&cbMaxSubKey,&cchMaxClass,&cValues,&cchMaxValue,&cbMaxValueData,&cbSecurityDescriptor,&ftLastWriteTime)!=ERROR_SUCCESS)
    {
        error = GetLastError();
        return 1;
    }
    DWORD   cbName;
    int index=0;
    for (int i= 0; i < cSubKeys; i++) {
        cbName = _MAX_PATH;
        retCode = RegEnumKeyEx(regKey, (DWORD)i,achKey,&cbName,NULL,NULL,NULL,&ftLastWriteTime);
        if (retCode == ERROR_SUCCESS)
        {
            RegProgramList regProgramList;
            std::string str;
            std::wstring wStr = achKey;
            str = std::string(wStr.begin(), wStr.end());
            Kstring path2 = pathX+"\\" + str;
            char value[BUFFER];
            DWORD BufferSize = BUFFER;

            RegGetValueA(regMachine, path2.c_str(), "pHash", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regProgramList.pHash = KcharToString(value);
            RegGetValueA(regMachine, path2.c_str(), "pRunCount", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regProgramList.pRunCount = KCharToInt(value);
            regProgramList.pFile = str;
            regList[index] = regProgramList;
            index++;
            KSpace(value);
        }
    }
    regListNum = index;
    RegCloseKey(regKey);
    return 0;
}
//-----------------------------------------------------------------------------------------
int  CustomSystem::setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value) {
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
//-----------------------------------------------------------------------------------------
RegProgramList CustomSystem::upRegListControl(Kstring reg) {
    RegProgramList regProgramList;
    regProgramList.pRunCount= - 1;
    for (int i = 0; i < regList.size(); i++)
    {
        if (regList[i].pHash == reg) {
            regProgramList = regList[i];
            return regProgramList;
        }
    }
    return regProgramList;
}
//-----------------------------------------------------------------------------------------
