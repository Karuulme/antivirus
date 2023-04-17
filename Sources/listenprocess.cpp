#include "../Headers/listenprocess.h"
listenProcess::listenProcess(QObject *parent): QObject{parent}
{
    m_lRef = 0;
    //listenProcessNamesClear
}
//-----------------------------------------------------------------------------------------
listenProcess::~listenProcess() {
     bDone = true;
     hres = pSvc->CancelAsyncCall(pStubSink);
     pSvc->Release();
     pLoc->Release();
     pUnsecApp->Release();
     pStubUnk->Release();
     pStubSink->Release();
     CoUninitialize();
}
//-----------------------------------------------------------------------------------------
ULONG listenProcess::AddRef(){
    return InterlockedIncrement(&m_lRef);
}
//-----------------------------------------------------------------------------------------
ULONG listenProcess::Release(){
    LONG lRef = InterlockedDecrement(&m_lRef);
    if (lRef == 0)
        delete this;
    return lRef;
}
//-----------------------------------------------------------------------------------------
HRESULT listenProcess::QueryInterface(REFIID riid, void** ppv) {
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink*)this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else return E_NOINTERFACE;
}
//-----------------------------------------------------------------------------------------
void listenProcess::listenProcessNamesClear(){
    listenProcess_Control=true;
    for(;ui8_listenProcess_Loop_Number>0;ui8_listenProcess_Loop_Number--){
        Sleep(2000);
        if(qls_listenProcessNames.size()!=0){
            qls_listenProcessNames.removeFirst();
        }
        else{
            ui8_listenProcess_Loop_Number=0;
            break;
        }
    }
    listenProcess_Control=false;
}
//-----------------------------------------------------------------------------------------
HRESULT listenProcess::Indicate(long lObjectCount, IWbemClassObject** apObjArray) {
    QString temp;
    HRESULT hr = S_OK;
    QString pInformation;
    _variant_t vtProp;
    for (int i = 0; i < lObjectCount; i++){
        hr = apObjArray[i]->Get(SysAllocString(L"TargetInstance"), 0, &vtProp, 0, 0);
        if (!FAILED(hr)){
            IUnknown* str = vtProp;
            hr = str->QueryInterface(IID_IWbemClassObject, reinterpret_cast<void**>(&apObjArray[i]));
            if (SUCCEEDED(hr)){
                _variant_t cn;
                hr = apObjArray[i]->Get(L"Handle", 0, &cn, NULL, NULL);
                if (SUCCEEDED(hr)){
                    if (!(cn.vt == VT_NULL) || !(cn.vt == VT_EMPTY)){
                        if (!(cn.vt & VT_ARRAY)){
                            pInformation= QString::fromWCharArray(cn.bstrVal);
                            if(_wtoi(cn.bstrVal)==GetCurrentProcessId()){
                                return WBEM_S_NO_ERROR;
                            }
                            HANDLE hProcessT=OpenProcess(PROCESS_ALL_ACCESS, FALSE,_wtoi(cn.bstrVal));
                            if (NULL != hProcessT) {
                                wchar_t filePath[MAX_PATH];
                                if(GetModuleFileNameExW(hProcessT,NULL,filePath,MAX_PATH)!=0){
                                    temp=QString::fromWCharArray(filePath);
                                    if(!temp.contains("C:\\Program Files\\WindowsApps")){
                                        if(!qls_listenProcessNames.contains(temp)){
                                            qls_listenProcessNames.append(temp);
                                            emit setFilePahtReg(temp,_wtoi(cn.bstrVal));

                                        }
                                    }
                                }
                            }
                            CloseHandle(hProcessT);
                        }
                    }
                }
                VariantClear(&cn);
            }
            VariantClear(&vtProp);
        }
    }
    VariantClear(&vtProp);
    ui8_listenProcess_Loop_Number+=4;
    if(!listenProcess_Control){
        std::thread  th_listenProcessNamesClear(&listenProcess::listenProcessNamesClear, this);
        th_listenProcessNamesClear.detach();
    }
    return WBEM_S_NO_ERROR;
}
//-----------------------------------------------------------------------------------------
HRESULT listenProcess::SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR* pObjParam) {
    if (lFlags == WBEM_STATUS_COMPLETE)
    {
    }
    else if (lFlags == WBEM_STATUS_PROGRESS)
    {
    }
    return WBEM_S_NO_ERROR;
}
//-----------------------------------------------------------------------------------------
int listenProcess::setStart() {
    hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hres))
    {
        return 1;
    }
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );
    if (FAILED(hres))
    {
        CoUninitialize();
        return 2;
    }
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres))
    {
        CoUninitialize();
        return 3;
    }
    wchar_t bbbb[]=L"ROOT\\CIMV2";
    hres = pLoc->ConnectServer(bbbb, NULL, NULL, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres))
    {
        pLoc->Release();
        CoUninitialize();
        return 4;
    }
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hres))
    {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 5;
    }
    hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL, CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, (void**)&pUnsecApp);
    AddRef();
    pUnsecApp->CreateObjectStub(this, &pStubUnk);
    pStubUnk->QueryInterface(IID_IWbemObjectSink, (void**)&pStubSink);
    wchar_t aa[]=L"WQL";
    wchar_t a2[]=L"SELECT * FROM __InstanceCreationEvent WITHIN 0.1 ""WHERE TargetInstance ISA 'Win32_Process'";
    hres = pSvc->ExecNotificationQueryAsync(aa, a2, WBEM_FLAG_SEND_STATUS, NULL, pStubSink);
    if (FAILED(hres))
    {
        pSvc->Release();
        pLoc->Release();
        pUnsecApp->Release();
        pStubUnk->Release();
      //  pSink->Release();
        pStubSink->Release();
        CoUninitialize();
        return 6;
    }
    return 0;
}
//-----------------------------------------------------------------------------------------
//https://learn.microsoft.com/en-us/windows/win32/wmisdk/example--receiving-event-notifications-through-wmi-?redirectedfrom=MSDN
//https://stackoverflow.com/questions/31753518/get-process-handle-of-created-processes-windows
