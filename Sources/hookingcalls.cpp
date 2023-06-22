#include "../Headers/hookingcalls.h"

HookingCalls::HookingCalls(QObject *parent): QObject{parent}{

    //qls_protectedRegistry.append("AntiVirus");
    DT_MapViewEnable();
}
//-----------------------------------------------------------------------------------------
int HookingCalls::dllEnjection(unsigned long int pID){
    char dllFile[] ="C:\\Users\\karuulme\\Desktop\\dll\\test3\\Dll1.dll";
    unsigned int dllFileSize = sizeof(dllFile) + 1;
    HANDLE hrProcess;
    HANDLE hrVirtual;
    hrProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (hrProcess == NULL)
        return -1;
    hrVirtual =VirtualAllocEx(hrProcess,NULL, dllFileSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (hrVirtual ==NULL)
        return -2;
    if (WriteProcessMemory(hrProcess, hrVirtual, dllFile, dllFileSize, NULL)==0)
        return -3;
    LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
    if (CreateRemoteThread(hrProcess, NULL, 0, (LPTHREAD_START_ROUTINE)addr, hrVirtual, NULL, NULL) == NULL)
        return -4;
    Add(pID,hrProcess);
    return 1;
}
//-----------------------------------------------------------------------------------------
void HookingCalls::getDllEnjection(unsigned long int pID){
    std::thread  thDllEnjection(&HookingCalls::dllEnjection, this,pID);
    thDllEnjection.detach();
}
//-----------------------------------------------------------------------------------------
void HookingCalls::getSecureList(QList<RegSecureFile>* secure){
    qls_regeditSecureList=secure;
}
//-----------------------------------------------------------------------------------------
int HookingCalls::regeditControl(QString  address){
    for(int i=0;i<qls_regeditSecureList->size();i++){
        if(address.contains(QString::fromStdString(qls_regeditSecureList->at(i).fKey))){
            return -1;
        }
    }
    return 1;
}
//-----------------------------------------------------------------------------------------
int HookingCalls::Add(unsigned long int pid,HANDLE hProcess) {
    std::string str = std::to_string(pid);
    const char* c_pid = str.c_str();
    char eventAddress[30] = "Global\\";
    //-----
    memcpy_s(eventAddress + 7, str.size(), c_pid, str.size());
    memcpy_s(eventAddress + 7 + str.size(), 3, "get", 3);
    HANDLE hgetEvent=CreateEventA(NULL, TRUE, FALSE, eventAddress);
    memcpy_s(eventAddress + 7 + str.size(), 3, "set", 3);
    HANDLE hsetEvent=CreateEventA(NULL, TRUE, FALSE, eventAddress);
    //-----
    std::thread  watchToEvents(&HookingCalls::listenToEvents,this, hProcess,hsetEvent,hgetEvent);
    watchToEvents.detach();
    return 0;
}
//------------------------------------------------------------------
int HookingCalls::DT_MapViewEnable() {
    memory_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUFFERSIZE, L"example_memory");
    if (memory_handle == NULL) {
        return -1;
    }
    memory_pointer = MapViewOfFile(memory_handle, FILE_MAP_ALL_ACCESS, 0, 0, BUFFERSIZE);
    if (memory_pointer == NULL) {
        CloseHandle(memory_handle);
        return -2;
    }
    memset(memory_pointer, NULL, BUFFERSIZE);
    return 1;
}
//------------------------------------------------------------------
void HookingCalls::DT_MapViewWrite(int value) {
    memcpy_s((unsigned char*)memory_pointer+ BUFFERSIZE-BUFFERREADSIZE, sizeof(value), &value, sizeof(value));
}
//-----------------------------------------------------------------
int HookingCalls::DT_MapViewRead() {
    char buffer[BUFFERSIZE - BUFFERREADSIZE];
    memcpy_s(buffer, sizeof(buffer), memory_pointer, sizeof(buffer));
    DT_MapViewWrite(regeditControl(buffer));
    return 1;
}
//------------------------------------------------------------------
void HookingCalls::listenToEvents(HANDLE hProcess,HANDLE hsetEvent,HANDLE hgetEvent){
    int retIndex = 0;
    DWORD exitCode;
    do{
        retIndex = WaitForSingleObject(hgetEvent, 10000);
        mtx.lock();
        if (retIndex == WAIT_TIMEOUT) {
            if (GetExitCodeProcess(hProcess, &exitCode) != 0) {
                if (exitCode!= STILL_ACTIVE) {
                    CloseHandle(hProcess);
                    CloseHandle(hsetEvent);
                    CloseHandle(hgetEvent);
                    break;
                }
            }
        }
        else {
            DT_MapViewRead();
            SetEvent(hsetEvent);
        }
        mtx.unlock();
        memset(memory_pointer ,NULL, BUFFERSIZE - BUFFERREADSIZE);
    } while (true);
    mtx.unlock();
    memset(memory_pointer ,NULL, BUFFERSIZE - BUFFERREADSIZE);
}
