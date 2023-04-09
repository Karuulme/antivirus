#include "../Headers/userdefinition.h"

userDefinition::userDefinition(QObject *parent): QObject{parent}{
    getRegProgramsList();
    if(getIdentityCheck()<KIdentification_Time){
        std::thread  time(&userDefinition::timeMeasurement, this);
        time.detach();
        std::thread  getRegProgramsListThread(&userDefinition::getRegProgramsList, this);
        getRegProgramsListThread.detach();
    }else{
        _identificationConfirmation=true;
        m_userDefinition=true;
    }
}
//-----------------------------------------------------------------------------------------
userDefinition::~userDefinition(){
    //RegCloseKey(regMachine);
}
//-----------------------------------------------------------------------------------------
void userDefinition::setStart(){
    emit userDefinitionChanged();
}
//-----------------------------------------------------------------------------------------
void userDefinition::setUserDefinition(){
    ui8_time=KIdentification_Time-1;
    setProgramTime(KMachine,"Time",KToString(ui8_time));
    m_userDefinition=true;
    emit userDefinitionChanged();
}
bool userDefinition::getuserDefinition(){
    return m_userDefinition;
}
//-----------------------------------------------------------------------------------------
void userDefinition::timeMeasurement(){
    while(true){
        Sleep(3600000);
        //Sleep(2000);
        if(KIdentification_Time==ui8_time){
            m_userDefinition=true;
            emit userDefinitionChanged();
            break;
        }
        ui8_time++;
        setProgramTime(HKEY_CURRENT_USER,"Time",KToString(ui8_time));
    }
}
//-----------------------------------------------------------------------------------------
int userDefinition::setProgramTime(HKEY hKey, Kstring key, Kstring value){
    Kstring sPath=KLocal;
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

}
//-----------------------------------------------------------------------------------------
int userDefinition::getIdentityCheck(){
    Kstring pathX=KLocal;
    HKEY  regKey;
    std::wstring name;
    const wchar_t* szName = name.c_str();
    if(RegOpenKeyEx(KMachine, szName, 0, KEY_ALL_ACCESS | KEY_QUERY_VALUE, &regKey)!= ERROR_SUCCESS)
    {
        return -1;
    }
    char value[BUFFER];
    DWORD BufferSize = BUFFER;
    RegGetValueA(regKey, pathX.c_str(), "Time", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
    ui8_time=std::stoi(value);
    return ui8_time;
}
//-----------------------------------------------------------------------------------------
Kstring userDefinition::KTcharToString(TCHAR value[1024])
{
    std::wstring test(&value[0]);
    Kstring test2(test.begin(), test.end());
    return test2;
}
//-----------------------------------------------------------------------------------------
Kstring userDefinition::KWcharToString(wchar_t value[1024])
{
    Kwstring ws(value);
    Kstring str(ws.begin(), ws.end());
    //KSpace(value);
    return str;
}
//-----------------------------------------------------------------------------------------
Kstring userDefinition::KcharToString(char value[256])
{
    Kstring target;
    for (int i = 0; i < 256;i++) {
        if (value[i] == '\0')
            break;
        target += value[i];
    }
    //KSpace(value);
    return target;
}
//-----------------------------------------------------------------------------------------
int userDefinition::StringToWString(Kwstring& ws, Kstring& s)
{
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
    return 0;
}
//-----------------------------------------------------------------------------------------
void userDefinition::getProcessList()
{
    QList<QString> processNames;
    HANDLE hProcessShot;
    PROCESSENTRY32 ProcessInformation;
    hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    ProcessInformation.dwSize = sizeof(PROCESSENTRY32);
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
                    if(!processNames.contains(temp)){
                        processNames.append(temp);
                         emit setFilePahtReg(temp,ProcessInformation.th32ProcessID);
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
int  userDefinition::getRegProgramsList()
{
    regListNum = 0;
    HKEY  regKey;
    Kstring pathX=KBank;
    std::wstring name;
    StringToWString(name, pathX);
    const wchar_t* szName = name.c_str();
    if(RegOpenKeyEx(KMachine, szName, 0, KEY_ALL_ACCESS | KEY_QUERY_VALUE, &regKey)!= ERROR_SUCCESS){
        return GetLastError();
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
    if(RegQueryInfoKey(regKey,achClass,&cchClassName,NULL,&cSubKeys,&cbMaxSubKey,&cchMaxClass,&cValues,&cchMaxValue,&cbMaxValueData,&cbSecurityDescriptor,&ftLastWriteTime)!=ERROR_SUCCESS){
        return GetLastError();
    }
    DWORD   cbName;
    int index=0;
    Kmap<int, RegProgramList>  regList;
    for (int i= 0; i < (int)cSubKeys; i++) {
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
            RegGetValueA(KMachine, path2.c_str(), "pHash", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            regProgramList.pHash = KcharToString(value);
            RegGetValueA(KMachine, path2.c_str(), "pRunCount", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
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
//-----------------------------------------------------------------------------------------
void userDefinition::regeditUninstallProgram(){
    QVector<QString> regInstallProgram;
    regeditInstalledProgramsList(HKEY_LOCAL_MACHINE,"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\",&regInstallProgram);
    regeditInstalledProgramsList(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\",&regInstallProgram);
    regeditInstalledProgramsList(HKEY_CURRENT_USER ,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\",&regInstallProgram);

}
//-----------------------------------------------------------------------------------------
void userDefinition::regeditInstalledProgramsList(HKEY machine,Kstring regAddress,QVector<QString>* regInstallProgram) {
    HKEY  regKey;
    machine = HKEY_LOCAL_MACHINE;
    std::wstring name;
    StringToWString(name, regAddress);
    const wchar_t* szName = name.c_str();
    RegOpenKeyEx(machine, szName, 0, KEY_ALL_ACCESS, &regKey);
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
    DWORD i, retCode;
    RegQueryInfoKey(regKey,achClass,&cchClassName,NULL,&cSubKeys,&cbMaxSubKey,&cchMaxClass,&cValues,&cchMaxValue,&cbMaxValueData,&cbSecurityDescriptor,&ftLastWriteTime);
    DWORD   cbName;
    QString programAddress;
    for (i = 0; i < cSubKeys; i++) {
        cbName = _MAX_PATH;
        retCode = RegEnumKeyEx(regKey, i,achKey,&cbName,NULL,NULL,NULL,&ftLastWriteTime);
        if (retCode == ERROR_SUCCESS)
        {
            std::string str;
            std::wstring wStr = achKey;
            str = std::string(wStr.begin(), wStr.end());
            std::string path2 = regAddress + str;
            char value[255];
            DWORD BufferSize = BUFFER;
            RegGetValueA(machine, path2.c_str(), "DisplayIcon", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
            programAddress=QString::fromUtf8(value);
            if(programAddress.contains(",0")){
                programAddress.remove(",0");
            }
            if(!regInstallProgram->contains(programAddress)){
                regInstallProgram->append(programAddress);
            }
        }
    }
    RegCloseKey(machine);
    RegCloseKey(regKey);
}
