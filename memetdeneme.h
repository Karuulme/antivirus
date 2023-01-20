// EventSink.h
#ifndef EVENTSINK_H
#define EVENTSINK_H
#define _WIN32_DCOM
#include <iostream>
//using namespace std;
#include <comdef.h>
#include <QDebug>
#include <comutil.h>
#include <Wbemidl.h>
//#pragma comment(lib, "wbemuuid.lib")
class EventSink : public IWbemObjectSink
{
    LONG m_lRef;
    bool bDone;
public:
    EventSink();
    ~EventSink() { bDone = true; }

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
    virtual HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount, IWbemClassObject __RPC_FAR* __RPC_FAR* apObjArray);
    virtual HRESULT STDMETHODCALLTYPE SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR* pObjParam);
                                                int deneme222();
};
#endif    // end of EventSink.h
EventSink::EventSink(){
     m_lRef = 0;
     deneme222();
 }


ULONG EventSink::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}
ULONG EventSink::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRef);
    if (lRef == 0)
        delete this;
    return lRef;
}
HRESULT EventSink::QueryInterface(REFIID riid, void** ppv) {
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink*)this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else return E_NOINTERFACE;
}
HRESULT EventSink::Indicate(long lObjectCount, IWbemClassObject** apObjArray) {
    HRESULT hr = S_OK;
    _variant_t vtProp;
    for (int i = 0; i < lObjectCount; i++)
    {
        hr = apObjArray[i]->Get(BSTR(L"TargetInstance"), 0, &vtProp, 0, 0);
        if (!FAILED(hr))
        {
            IUnknown* str = vtProp;
            hr = str->QueryInterface(IID_IWbemClassObject, reinterpret_cast<void**>(&apObjArray[i]));
            if (SUCCEEDED(hr))
            {
                _variant_t cn;
                VariantClear(&cn);
                hr = apObjArray[i]->Get(L"Handle", 0, &cn, NULL, NULL);
                if (SUCCEEDED(hr))
                {
                    if (!(cn.vt == VT_NULL) || !(cn.vt == VT_EMPTY))
                        if (!(cn.vt & VT_ARRAY))
                            qDebug() << "Process ID : " << cn.bstrVal;
                }
                VariantClear(&cn);
            }
            VariantClear(&vtProp);
        }
        VariantClear(&vtProp);
    }
    VariantClear(&vtProp);
    return WBEM_S_NO_ERROR;
}
HRESULT EventSink::SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR* pObjParam) {
    if (lFlags == WBEM_STATUS_COMPLETE)
    {
        printf("Call complete. hResult = 0x%X\n", hResult);
    }
    else if (lFlags == WBEM_STATUS_PROGRESS)
    {
        printf("Call in progress.\n");
    }
    return WBEM_S_NO_ERROR;
}
int deneme222() {
    HRESULT hres;
    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {

        return 1;                  // Program has failed.
    }
    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM negotiates service
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities
        NULL                         // Reserved
    );
    if (FAILED(hres))
    {

        CoUninitialize();
        return 1;                      // Program has failed.
    }
    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres))
    {
        CoUninitialize();
        return 1;                 // Program has failed.
    }
    // Step 4: ---------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method
    IWbemServices* pSvc = NULL;
    // Connect to the local root\cimv2 namespace
    // and obtain pointer pSvc to make IWbemServices calls.
    hres = pLoc->ConnectServer(BSTR(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres))
    {
        pLoc->Release();
        CoUninitialize();
        return 1;                // Program has failed.
    }
    //cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;
    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    // Indicates the proxy to set
    // RPC_C_AUTHN_xxx
    // RPC_C_AUTHZ_xxx
    // Server principal name
    // RPC_C_AUTHN_LEVEL_xxx
    // RPC_C_IMP_LEVEL_xxx
    // client identity
    // proxy capabilities
    if (FAILED(hres))
    {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }
    // Step 6: -------------------------------------------------
    // Receive event notifications -----------------------------
    // Use an unsecured apartment for security
    IUnsecuredApartment* pUnsecApp = NULL;
    hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL, CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, (void**)&pUnsecApp);
    EventSink* pSink = new EventSink;
    pSink->AddRef();
    IUnknown* pStubUnk = NULL;
    pUnsecApp->CreateObjectStub(pSink, &pStubUnk);
    IWbemObjectSink* pStubSink = NULL;
    pStubUnk->QueryInterface(IID_IWbemObjectSink, (void**)&pStubSink);
    // The ExecNotificationQueryAsync method will call
    // The EventQuery::Indicate method when an event occurs
   // BSTR WQL;
  //  WQL = BSTR(L"Select * From __InstanceCreationEvent Within 1 "L"Where TargetInstance ISA 'Win32_Process' ");
              //  "SELECT * ""FROM __InstanceCreationEvent WITHIN 1 ""WHERE TargetInstance ISA 'Win32_Process'"

    hres = pSvc->ExecNotificationQueryAsync(BSTR("WQL"), BSTR("SELECT * FROM __InstanceCreationEvent WITHIN 1 ""WHERE TargetInstance ISA 'Win32_Process'"), WBEM_FLAG_SEND_STATUS, NULL, pStubSink);
    // Check for errors.
    if (FAILED(hres))
    {
        printf("ExecNotificationQueryAsync failed ""with = 0x%X\n", hres);
        pSvc->Release();
        pLoc->Release();
        pUnsecApp->Release();
        pStubUnk->Release();
        pSink->Release();
        pStubSink->Release();
        CoUninitialize();
        return 1;
    }
    // Wait for the event
    Sleep(100000);
    hres = pSvc->CancelAsyncCall(pStubSink);
    // Cleanup
    // ========
    pSvc->Release();
    pLoc->Release();
    pUnsecApp->Release();
    pStubUnk->Release();
    pSink->Release();
    pStubSink->Release();
    CoUninitialize();
    return 0;   // Program successfully completed.
}
//https://learn.microsoft.com/en-us/windows/win32/wmisdk/example--receiving-event-notifications-through-wmi-?redirectedfrom=MSDN
//https://stackoverflow.com/questions/31753518/get-process-handle-of-created-processes-windows
