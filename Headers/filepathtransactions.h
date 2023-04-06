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
class filePathTransactions : public QObject
{
    Q_OBJECT
public:
    explicit filePathTransactions(QObject *parent = nullptr);
    int  setRegCreateBank(HKEY hKey, std::string path, std::string key, std::string value);
    RegProgramList upRegListControl(Kstring reg);
    bool boolRegListControl(Kstring regg);
    int setRegQuestion(QString filePath,unsigned long int pID);
    int regeditNewRecord(RegProgramList regProgram);
    QString getfileHash(QString filePath);
    int dllEnjection(unsigned long int pID);

private:
    Kmap<int, RegProgramList>  regList;
    int regListIndex=0;
public slots:
    void getFilePahtReg(QString filePath,unsigned long int pID);
    void getRegList(Kmap<int, RegProgramList> reg);
    void getfileChangesNotification(QString filePath);
    void getProgramTime(unsigned __int8 value);
signals:
    void setDllEnjection(unsigned long int pID);

};
#endif // FILEPATHTRANSACTIONS_H
