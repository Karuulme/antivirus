#ifndef FILEPATHTRANSACTIONS_H
#define FILEPATHTRANSACTIONS_H
#include <QObject>
#include <windows.h>
#include <Headers/klibrary.h>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <vector>
#include <iostream>
#include <QThread>
extern bool _identificationConfirmation;
class filePathTransactions : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString userDefinitions_UploadIndexNo READ getuserDefinitions_UploadIndexNo  NOTIFY userDefinitions_UploadIndexNoChanged);
public:
    explicit filePathTransactions(QObject *parent = nullptr);
    int  setRegCreateBank(HKEY hKey, std::string path, std::string key, std::string value);
    RegProgramList upRegListControl(Kstring reg);
    bool boolRegListControl(Kstring regg);
    int setRegQuestion(QString filePath,unsigned long int pID=-1);
    int regeditNewRecord(RegProgramList regProgram,int runCount=-1);
    QString getfileHash(QString filePath);
    int dllEnjection(unsigned long int pID);
    void getUserDefinitions_FileOperations_Thread(QVector<QString>* regInstallProgram);
    QString getuserDefinitions_UploadIndexNo();
    QString m_userDefinitions_UploadIndexNo;

private:
    Kmap<int, RegProgramList>  regList;
    int regListIndex=0;
signals:
    void setDllEnjection(unsigned long int pID);
    void userDefinitions_UploadChanged();
    void userDefinitions_UploadIndexNoChanged();
public slots:
    void getFilePahtReg(QString filePath,unsigned long int pID);
    void getRegList(Kmap<int, RegProgramList> reg);
    void getfileChangesNotification(QString filePath);
    void getProgramTime(unsigned __int8 value);
    void getUserDefinitions_FileOperations(QVector<QString>* regInstallProgram);

};
#endif // FILEPATHTRANSACTIONS_H
