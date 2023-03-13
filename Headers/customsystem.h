#ifndef CUSTOMSYSTEM_H
#define CUSTOMSYSTEM_H
#include <D3d9.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <map>
#include <string>
#include <tchar.h>
#include <vector>
//#include <msclr\marshal_cppstd.h>
//#include <msclr\marshal.h>
//#include <msclr\marshal_windows.h>
#include <functional>
#include <Tlhelp32.h>
#include <sstream>
#include <psapi.h>
#include <winreg.h>
#include <atomic>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#pragma comment(lib, "Advapi32.lib")

#define Kstring  std::string
#define Kwstring std::wstring
#define Kmap std::map
#define Kprivate private:
#define Kpublic public:
#define Kpaint  System::Drawing
#define Kform System::Windows::Forms
#define Kuse using namespace
#define KstringToText(x) (gcnew System::String(x))
#define Kthread std::thread
#define KToString std::to_string
#define KStringToInt stoi
#define KVector std::vector
#define BUFFER 8192
#define KCharToInt(x) atoi(x)
#define KSpace(x)(memset(x,0,sizeof(x)))
#define KBank  "SOFTWARE\\AntiVirus\\Bank\\"
#include <QObject>
#include <QCryptographicHash>
struct RegProgramList {
    Kstring pHash;
    Kstring pFile;
    int pRunCount=0;
};


class CustomSystem : public QObject
{
    Q_OBJECT
public:
    explicit CustomSystem(QObject *parent = nullptr);
     ~CustomSystem();
    int setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value);
    int getMemoryType(Kstring* _address);
    int byteToGb(ULONGLONG* byte);
    void invokeReferance();
    void scanThread();
    void getProcessList();
    int getRegProgramsList();
    RegProgramList upRegListControl(Kstring reg);
    int regListNum = 0;
    HKEY regMachine = HKEY_CURRENT_USER;
    Kmap<int, RegProgramList>  regList;
    int StringToWString(Kwstring& ws, Kstring& s);
    Kstring KTcharToString(TCHAR value[1024]);
    Kstring KWcharToString(wchar_t value[1024]);
    Kstring KcharToString(char value[256]);
    QString KTcharToQString(TCHAR * value);
    std::string KQStringToString(QString value);
    void SetStart();



signals:

};

#endif // CUSTOMSYSTEM_H
