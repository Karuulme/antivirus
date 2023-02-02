#ifndef USERDEFINITION_H
#define USERDEFINITION_H
#include <Windows.h>
#include <thread>
#include <Tlhelp32.h>
#include <psapi.h>
#include <QByteArray>
#include <Headers/klibrary.h>
#include <QDebug>
class userDefinition : public QObject
{
    Q_OBJECT
public:
    explicit userDefinition(QObject *parent = nullptr);
    ~userDefinition();
    int setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value);
    int getMemoryType(Kstring* _address);
    int byteToGb(ULONGLONG* byte);
    void invokeReferance();
    void scanThread();
    void getProcessList();
    int getRegProgramsList();
    void setStart();

    RegProgramList upRegListControl(Kstring reg);
    int regListNum = 0;
    HKEY regMachine = HKEY_CURRENT_USER;
    int StringToWString(Kwstring& ws, Kstring& s);
    Kstring KTcharToString(TCHAR value[1024]);
    Kstring KWcharToString(wchar_t value[1024]);
    Kstring KcharToString(char value[256]);
   // QString KTcharToQString(TCHAR * value);
   // std::string KQStringToString(QString value);

signals:
    void setFilePahtReg(QString *filePath);
    void setRegList(Kmap<int, RegProgramList> setreg);
};
#endif // USERDEFINITION_H

