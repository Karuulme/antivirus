#include "../Headers/userdefinition.h"

userDefinition::userDefinition(QObject *parent): QObject{parent}{
    if (IsUserAnAdmin())
    {
        qDebug()<<"ADMİN";
    }
    else{
        qDebug()<<"ADMİN DEĞİL";
    }
    getRegProgramsList();
    __int8 programTime=getIdentityCheck();
    if(programTime<KIdentification_Time && programTime>0){
        std::thread  time(&userDefinition::timeMeasurement, this);
        time.detach();
        std::thread  getRegProgramsListThread(&userDefinition::getRegProgramsList, this);
        getRegProgramsListThread.detach();
    }
    else if(programTime==-1){

    }
    else{
        _identificationConfirmation=true;
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
    _identificationConfirmation=true;
    emit userDefinitionChanged();
    regeditUninstallProgram();
}
bool userDefinition::getuserDefinition(){
    return _identificationConfirmation;
}
//-----------------------------------------------------------------------------------------
void userDefinition::timeMeasurement(){
    while(true){
        Sleep(3600000);
        //Sleep(2000);
        if(KIdentification_Time==ui8_time){
            _identificationConfirmation=true;
            emit userDefinitionChanged();
            break;
        }
        ui8_time++;
        setRegeditKeyValue(KMachine,KLocal,"Time",KToString(ui8_time));
    }
}
//-----------------------------------------------------------------------------------------
int userDefinition::setRegeditKeyValue(HKEY hKey,Kstring Path, Kstring key, Kstring value){
    Kstring sPath=Path;
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
    if(RegOpenKeyEx(KMachine, szName, 0, KEY_ALL_ACCESS | KEY_QUERY_VALUE, &regKey)!= ERROR_SUCCESS){

    }
    char value[BUFFER];
    DWORD BufferSize = BUFFER;
    LSTATUS regTimeControl= RegGetValueA(regKey, pathX.c_str(), "Time", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
    if(regTimeControl==ERROR_FILE_NOT_FOUND){
        setRegCreateTime();
        return 1;
    }
    ui8_time=std::stoi(value);
    return ui8_time;
}
int  userDefinition::setRegCreateTime() {
    Kstring sPath=KLocal;
    HKEY hKey=KMachine;
    HKEY hkRegOpen;
    DWORD dRegReturn;
    sPath = sPath + "\0";
    LONG res1 = RegCreateKeyExA(hKey, sPath.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkRegOpen, &dRegReturn);
    if (res1 != ERROR_SUCCESS)
        return res1;
    LONG res2 = RegSetValueExA(hkRegOpen, (LPCSTR)"Time", 0, REG_SZ, (LPBYTE)"1",4);
    if (res2 != ERROR_SUCCESS)
        return res2;
    RegCloseKey(hkRegOpen);
    return 0;
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
    emit setUserDefinitions_Delete_Signal();
    QVector<QString> regInstallProgram;
    regeditInstalledProgramsList(HKEY_LOCAL_MACHINE,"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\",&regInstallProgram);
    regeditInstalledProgramsList(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\",&regInstallProgram);
    regeditInstalledProgramsList(HKEY_CURRENT_USER ,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\",&regInstallProgram);
    getProcessList(&regInstallProgram);
    emit setUserDefinitions_FileOperations(&regInstallProgram);
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
                programAddress.chop(2);
            }
            if(programAddress.contains(".ico")){
                continue;
            }
            if(!regInstallProgram->contains(programAddress)){
                if(regInstallProgram->contains(".exe")){
                    regInstallProgram->append(programAddress);
                }
            }
        }
    }
    RegCloseKey(machine);
    RegCloseKey(regKey);
}
//-----------------------------------------------------------------------------------------
void userDefinition::getProcessList(QVector<QString>* regInstallProgram)
{
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
                    if(!regInstallProgram->contains(temp)){
                        regInstallProgram->append(temp);

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


