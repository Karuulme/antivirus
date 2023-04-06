#ifndef HOOKINGCALLS_H
#define HOOKINGCALLS_H

#include <QObject>
#include <windows.h>
#include <thread>
#include <iostream>
#include <QDebug>
#include <mutex>
#define BUFFERSIZE 1024
#define BUFFERREADSIZE 24
class HookingCalls : public QObject
{
    Q_OBJECT
public:
    explicit HookingCalls(QObject *parent = nullptr);
    int dllEnjection(unsigned long int pID);
private:
    QList<QString> qls_protectedRegistry;
    QList<QString> *qls_regeditSecureList;
    int regeditControl(QString  address);
    int fileControl(QString  address);
    //--------------------------------------------------
    LPVOID memory_pointer;
    HANDLE memory_handle;
    std::mutex mtx;

    int Add(unsigned long int pid,HANDLE hProcess);
    int DT_MapViewEnable() ;
    void DT_MapViewWrite(int value);
    int DT_MapViewRead();
    void listenToEvents(HANDLE hProcess,HANDLE hsetEvent,HANDLE hgetEvent);

    //--------------------------------------------------

public slots:
    void getDllEnjection(unsigned long int pID);
    void getSecureList(QList<QString> * secure);
signals:

};
#endif // HOOKINGCALLS_H
