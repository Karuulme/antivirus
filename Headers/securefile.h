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
    Q_PROPERTY(QString secureProcessed READ getSecureProcessed  WRITE setSecureProcessed NOTIFY secureProcessedChanged)
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
   QString m_secureFiles;
   QString filePathDESKTOP;
   HKEY regMachine = HKEY_CURRENT_USER;
   //QList<QString> secureList;
   //QList<QString> secureListFileName;
   QList<RegSecureFile> _secureList;
   QString m_secureProcessed;
   QString getSecureProcessed();
   void setSecureProcessed(QString secureValue);

signals:
   void secureFilesChanged();
   void setSecureList(QList<RegSecureFile> *secureList);
   void setUserDefinitions(QVector<QString> * regInstallProgram);
   void secureProcessedChanged();
public slots:
   void getUserDefinitions_Delete_Signal();
   int set_RecureDeleteFile(QString rKey,QString rPath);
   void set_folderPath(QString parentFileName);
   void setStart();
   void set_RecureOpenFile(QString parentFileName);
};

#endif // SECUREFILE_H
