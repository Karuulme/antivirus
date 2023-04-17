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
#include <Headers/klibrary.h>
#include <shlobj.h>
#include <strsafe.h>
#include <dirent.h>
#include <QMessageBox>
extern bool _identificationConfirmation;
class userDefinition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool userDefinition READ getuserDefinition NOTIFY userDefinitionChanged);
public:
    explicit userDefinition(QObject *parent = nullptr);
    ~userDefinition();
    int getMemoryType(Kstring* _address);
    int byteToGb(ULONGLONG* byte);
    void invokeReferance();
    void scanThread();
    void getProcessList(QVector<QString>* regInstallProgram);
    int getRegProgramsList();
    void setStart();
    int getIdentityCheck();
    void timeMeasurement();
    bool getuserDefinition();
    void regeditUninstallProgram();
    int setRegCreateTime();


    RegProgramList upRegListControl(Kstring reg);
    int regListNum = 0;
    int StringToWString(Kwstring& ws, Kstring& s);
    Kstring KTcharToString(TCHAR value[1024]);
    Kstring KWcharToString(wchar_t value[1024]);
    Kstring KcharToString(char value[256]);
private:
    void regeditInstalledProgramsList(HKEY machine,Kstring regAddress,QVector<QString>* regInstallProgram);
    unsigned __int8 ui8_time=0;
    int setRegeditKeyValue(HKEY hKey,Kstring Path, Kstring key, Kstring value);
    //int getProgramTime();
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now.time_since_epoch();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
signals:
    void setFilePahtReg(QString filePath,unsigned long int pID);
    void setRegList(Kmap<int, RegProgramList> setreg);
    void userDefinitionChanged();
    void setUserDefinitions_Delete_Signal();
    void setUserDefinitions_FileOperations(QVector<QString>* regInstallProgram);
public slots:
    void setUserDefinition();

};
#endif // USERDEFINITION_H
