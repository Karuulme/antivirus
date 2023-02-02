#include "../Headers/userdefinition.h"

userDefinition::userDefinition(QObject *parent): QObject{parent}
{

}

userDefinition::~userDefinition()
{
    RegCloseKey(regMachine);
}
void userDefinition::setStart(){
    getRegProgramsList();
    getProcessList();
    /*std::thread  getRegProgramsListThread(&userDefinition::getRegProgramsList, this);
    getRegProgramsListThread.join();
    std::thread  getProcessListThread(&userDefinition::getProcessList, this);
    getProcessListThread.detach();*/

}
Kstring userDefinition::KTcharToString(TCHAR value[1024])
{
    std::wstring test(&value[0]);
    Kstring test2(test.begin(), test.end());

    return test2;
}
Kstring userDefinition::KWcharToString(wchar_t value[1024])
{
    Kwstring ws(value);
    Kstring str(ws.begin(), ws.end());
    KSpace(value);
    return str;
}
Kstring userDefinition::KcharToString(char value[256])
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
int userDefinition::StringToWString(Kwstring& ws, Kstring& s)
{
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
    return 0;
}
/*
QString KTcharToQString(TCHAR * value){

    return QString::fromWCharArray(value);
}
std::string KQStringToString(QString value){

    return value.toStdString();
}
*/
void userDefinition::getProcessList()
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
                    QString temp=QString::fromWCharArray(filePath);
                    emit setFilePahtReg(&temp);
                }
            }
            CloseHandle(hProcessT);
        } while (Process32Next(hProcessShot, &ProcessInformation));
    }
    CloseHandle(hProcessShot);
    runFirstList.clear();
}
int  userDefinition::getRegProgramsList()
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
    Kmap<int, RegProgramList>  regList;
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
    emit setRegList(regList);
    RegCloseKey(regKey);
    return 0;
}

