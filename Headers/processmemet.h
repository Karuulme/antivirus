#ifndef PROCESSMEMET_H
#define PROCESSMEMET_H
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
class processmemet : public IWbemObjectSink
{
    LONG m_lRef;
    bool bDone;
    HRESULT hres;
    IWbemServices* pSvc = NULL;
    IWbemLocator* pLoc = NULL;
    IWbemObjectSink* pStubSink = NULL;
    IUnsecuredApartment* pUnsecApp = NULL;
    IUnknown* pStubUnk = NULL;

public:
    processmemet();
    ~processmemet();
    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
    virtual HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount, IWbemClassObject __RPC_FAR* __RPC_FAR* apObjArray);
    virtual HRESULT STDMETHODCALLTYPE SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR* pObjParam);
    int dinleyiciStart();
};
#endif    // end of EventSink.h
#endif // PROCESSMEMET_H
