#include "../Headers/processmemet.h"
processmemet::processmemet()
{
    m_lRef = 0;
   // deneme222();

}
 processmemet::~processmemet() {
     bDone = true;
     hres = pSvc->CancelAsyncCall(pStubSink);
     // Cleanup
     // ========
     pSvc->Release();
     pLoc->Release();
     pUnsecApp->Release();
     pStubUnk->Release();
    // pSink->Release();
     pStubSink->Release();
     CoUninitialize();
     //qDebug()<<" HATASIZ ÇIKIŞ YAPILDI:";
    // return 0;   // Program successfully completed.

 }
ULONG processmemet::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}
ULONG processmemet::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRef);
    if (lRef == 0)
        delete this;
    return lRef;
}
HRESULT processmemet::QueryInterface(REFIID riid, void** ppv) {
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink*)this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else return E_NOINTERFACE;
}
HRESULT processmemet::Indicate(long lObjectCount, IWbemClassObject** apObjArray) {
       qDebug() <<"1111";
    HRESULT hr = S_OK;
    QString pInformation;
    _variant_t vtProp;
    for (int i = 0; i < lObjectCount; i++)
    {
        hr = apObjArray[i]->Get(SysAllocString(L"TargetInstance"), 0, &vtProp, 0, 0);
        if (!FAILED(hr))
        {
            IUnknown* str = vtProp;
            hr = str->QueryInterface(IID_IWbemClassObject, reinterpret_cast<void**>(&apObjArray[i]));
            if (SUCCEEDED(hr))
            {
                _variant_t cn;
                hr = apObjArray[i]->Get(L"CommandLine", 0, &cn, NULL, NULL);
                if (SUCCEEDED(hr))
                {
                    if (!(cn.vt == VT_NULL) || !(cn.vt == VT_EMPTY))
                        if(!(cn.vt & VT_ARRAY))
                            pInformation= QString::fromWCharArray(cn.bstrVal);
                }
                //QList<QString> aaa=pInformation.split("--");
               // qDebug()<<"CommandLine:"<<aaa[0].mid(1,aaa[0].length()-3);
               qDebug()<<pInformation;
                VariantClear(&cn);
                hr = apObjArray[i]->Get(L"Handle", 0, &cn, NULL, NULL);
                if (SUCCEEDED(hr))
                {
                    if (!(cn.vt == VT_NULL) || !(cn.vt == VT_EMPTY))
                        if (!(cn.vt & VT_ARRAY))
                            pInformation= QString::fromWCharArray(cn.bstrVal);
                }
               // qDebug()<<"Process ID"<<pInformation;
                VariantClear(&cn);
            }
            VariantClear(&vtProp);
        }
    }
    VariantClear(&vtProp);

    qDebug() << "----------------------------------------------";
    return WBEM_S_NO_ERROR;
}
HRESULT processmemet::SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR* pObjParam) {
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
int processmemet::dinleyiciStart() {


    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------
    hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    //qDebug()<<GetLastError();
    if (FAILED(hres))
    {
       // qDebug() << "Failed to initialize COM library. Error code = 0x"<<  QByteArray::fromHex(hres);
       // qDebug()<<"HATAAAAAAA"<<hres;
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
        return 2;                      // Program has failed.
    }
    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres))
    {
        CoUninitialize();
        return 3;                 // Program has failed.
    }
    // Step 4: ---------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    // Connect to the local root\cimv2 namespace
    // and obtain pointer pSvc to make IWbemServices calls.
    wchar_t bbbb[]=L"ROOT\\CIMV2";
    hres = pLoc->ConnectServer(bbbb, NULL, NULL, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres))
    {
        pLoc->Release();
        CoUninitialize();
        return 4;                // Program has failed.
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
        return 5;               // Program has failed.
    }
    // Step 6: -------------------------------------------------
    // Receive event notifications -----------------------------
    // Use an unsecured apartment for security
    processmemet* pSink = new processmemet;
    hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL, CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, (void**)&pUnsecApp);

    pSink->AddRef();

    pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

    pStubUnk->QueryInterface(IID_IWbemObjectSink, (void**)&pStubSink);
    // The ExecNotificationQueryAsync method will call
    // The EventQuery::Indicate method when an event occurs
   // BSTR WQL;
  //  WQL = BSTR(L"Select * From __InstanceCreationEvent Within 1 "L"Where TargetInstance ISA 'Win32_Process' ");
              //  "SELECT * ""FROM __InstanceCreationEvent WITHIN 1 ""WHERE TargetInstance ISA 'Win32_Process'"
    wchar_t aa[]=L"WQL";
    wchar_t a2[]=L"SELECT * FROM __InstanceCreationEvent WITHIN 1 ""WHERE TargetInstance ISA 'Win32_Process'";
    hres = pSvc->ExecNotificationQueryAsync(aa, a2, WBEM_FLAG_SEND_STATUS, NULL, pStubSink);
    // Check for errors.
    if (FAILED(hres))
    {
        //qDebug()<<"HATA KODU YENİ:"<<hres;
        pSvc->Release();
        pLoc->Release();
        pUnsecApp->Release();
        pStubUnk->Release();
        pSink->Release();
        pStubSink->Release();
        CoUninitialize();
        return 6;
    }
    // qDebug()<<" HATASIZ ÇIKIŞ YAPILDI:";
    // Wait for the event
    //Sleep(100000);


}
//https://learn.microsoft.com/en-us/windows/win32/wmisdk/example--receiving-event-notifications-through-wmi-?redirectedfrom=MSDN
//https://stackoverflow.com/questions/31753518/get-process-handle-of-created-processes-windows
