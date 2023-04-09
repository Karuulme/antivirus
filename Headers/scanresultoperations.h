#ifndef SCANRESULTOPERATIONS_H
#define SCANRESULTOPERATIONS_H

#include <QObject>
#include <QDebug>
#include <iphlpapi.h>
#include <windows.h>
#include <Shlobj.h>
#include <fstream>
#include <QCryptographicHash>
#include <QFile>
#include <Headers/klibrary.h>
#include <Shlobj.h>
#include <QDateTime>
class scanResultOperations : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString quarantineFile READ getQuarantineFile WRITE setQuarantineFile NOTIFY quarantineFileChanged)
public:
    explicit scanResultOperations(QObject *parent = nullptr);
private:
    QString m_quarantineFile;
    QString getQuarantineFile();
    void setQuarantineFile(QString file);
    void findQuarantineFile();
    QStringList quarentineFileNameList;
    QStringList quarentineOrjinalFileNameList;
    void virusProcesses(QString path,int Options);
    void computerOperations(int Options);
    void getMac();
    void encrypt(QString file);
    int Decrypt(int fileindex);
    void getAppDataAddress();
    QString mac_Address;
    QString quarantineAddress;
signals:
    void quarantineFileChanged();
    void quarantineFileAdded(QString file);
public slots:
    void setStart();
    void getQuarantineOptions(int indexNo,int OptionsNo);
    void getApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions);
};
#endif // SCANRESULTOPERATIONS_H