#ifndef SECUREFILE_H
#define SECUREFILE_H

#include <QObject>
#include <windows.h>
#include <fstream>
#include <Shlobj.h>
#include <QDebug>
#include <iostream>
#include <windows.h>
#include "klibrary.h"
#include <QCryptographicHash>
#include <random>
#include <dirent.h>
#include <strsafe.h>
class secureFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString secureFiles READ getsecureFiles WRITE setsecureFiles NOTIFY secureFilesChanged);
public:
    explicit secureFile(QObject *parent = nullptr);

private:
   void setsecureFiles(QString childFileName);
   QString getsecureFiles();
   int folderPathControl(QString path);
   int setRegCreateRecure(HKEY hKey, Kstring path, Kstring key, Kstring value);
   int getRegSecureFiles();
   int StringToWString(Kwstring& ws, Kstring& s);
   Kstring KcharToString(char value[256]);
   QByteArray getRandomSha256();
   BOOL RegDelnodeRecurse (HKEY hKeyRoot, LPTSTR lpSubKey);
   BOOL RegDelnode (HKEY hKeyRoot, LPCTSTR lpSubKey);
   Kmap<int, RegSecureFile> secureFileRegList;
   int secureFileIndex=0;
   QString m_secureFiles;
   QString filePathDESKTOP;
   int regListNum = 0;
   HKEY regMachine = HKEY_CURRENT_USER;
   QList<QString> secureList;
   QList<QString> secureListFileName;

signals:
   void secureFilesChanged();
   void setSecureList(QList<QString> *secureList);
   void setUserDefinitions(QVector<QString> * regInstallProgram);
public slots:
   void getUserDefinitions_Delete_Signal();
   void set_RecureDeleteFile(QString rKey,QString rPath);
   void set_folderPath(QString parentFileName);
   void setStart();
   void set_RecureOpenFile(QString parentFileName);
};

#endif // SECUREFILE_H
