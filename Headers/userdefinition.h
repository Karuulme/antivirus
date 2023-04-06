#ifndef USERDEFINITION_H
#define USERDEFINITION_H
#include <Windows.h>
#include <thread>
#include <Tlhelp32.h>
#include <psapi.h>
#include <QByteArray>
#include <Headers/klibrary.h>
#include <QDebug>
#include <chrono>
#include <iostream>
class userDefinition : public QObject
{
    Q_OBJECT
public:
    explicit userDefinition(QObject *parent = nullptr);
    ~userDefinition();
    int getMemoryType(Kstring* _address);
    int byteToGb(ULONGLONG* byte);
    void invokeReferance();
    void scanThread();
    void getProcessList();
    int getRegProgramsList();
    void setStart();
    int getIdentityCheck();
    void timeMeasurement();

    HKEY hkRegOpen;
    RegProgramList upRegListControl(Kstring reg);
    int regListNum = 0;
    HKEY regMachine = HKEY_CURRENT_USER;
    int StringToWString(Kwstring& ws, Kstring& s);
    Kstring KTcharToString(TCHAR value[1024]);
    Kstring KWcharToString(wchar_t value[1024]);
    Kstring KcharToString(char value[256]);
   // QString KTcharToQString(TCHAR * value);
   // std::string KQStringToString(QString value);
private:
    unsigned __int8 ui8_time;
    bool identityCheck=false;

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now.time_since_epoch();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);

signals:
    void setFilePahtReg(QString filePath,unsigned long int pID);
    void setRegList(Kmap<int, RegProgramList> setreg);
    void setProgramTime(unsigned long int value);
};
#endif // USERDEFINITION_H

