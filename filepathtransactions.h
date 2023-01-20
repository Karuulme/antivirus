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
    int setRegQuestion(QString filePath);


private:
    Kmap<int, RegProgramList>  regList;
    int regListIndex=0;
public slots:
    void getFilePahtReg(QString *filePath);
    void getRegList(Kmap<int, RegProgramList> reg);
};
#endif // FILEPATHTRANSACTIONS_H
