#ifndef FILEPATHTRANSACTIONS_H
#define FILEPATHTRANSACTIONS_H
#include <QObject>
#include <windows.h>
#include <klibrary.h>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <vector>
class filePathTransactions : public QObject
{
    Q_OBJECT
public:
    explicit filePathTransactions(QObject *parent = nullptr);
    int  setRegCreateBank(HKEY hKey, std::string path, std::string key, std::string value);
    RegProgramList upRegListControl(Kstring reg);
    bool boolRegListControl(Kstring regg);
    int setRegQuestion(QString filePath);
    int regeditNewRecord(RegProgramList regProgram);
    QString getfileHash(QString filePath);


private:
    Kmap<int, RegProgramList>  regList;
    int regListIndex=0;
public slots:
    void getFilePahtReg(QString *filePath);
    void getRegList(Kmap<int, RegProgramList> reg);
    void getfileChangesNotification(QString filePath);;
};
#endif // FILEPATHTRANSACTIONS_H
