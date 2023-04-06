#ifndef LISTENPROCESS_H
#define LISTENPROCESS_H
#ifndef EVENTSINK_H
#define EVENTSINK_H
#define _WIN32_DCOM
#include <iostream>
//using namespace std;
#include <comdef.h>
#include <QDebug>
#include <comutil.h>
#include <Wbemidl.h>
#include <QObject>
#include <Psapi.h>
#include <thread>
class listenProcess : public QObject, public IWbemObjectSink
{
    Q_OBJECT
public:
    explicit listenProcess(QObject *parent = nullptr);
    ~listenProcess();
    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
    virtual HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount, IWbemClassObject __RPC_FAR* __RPC_FAR* apObjArray);
    virtual HRESULT STDMETHODCALLTYPE SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR* pObjParam);
    int setStart();

    QString setFilePath;
    LONG m_lRef;
    bool bDone;
    HRESULT hres;
    IWbemServices* pSvc = NULL;
    IWbemLocator* pLoc = NULL;
    IWbemObjectSink* pStubSink = NULL;
    IUnsecuredApartment* pUnsecApp = NULL;
    IUnknown* pStubUnk = NULL;

    void listenProcessNamesClear();
    QList<QString> qls_listenProcessNames;
    unsigned __int8 ui8_listenProcess_Loop_Number=0;
    bool listenProcess_Control=false;

signals:
    void setFilePahtReg(QString filePath,unsigned long int pID);
};
#endif    // end of EventSink.h
#endif // LISTENPROCESS_H
