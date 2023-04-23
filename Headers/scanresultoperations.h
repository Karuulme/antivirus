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
    Q_PROPERTY(QString quarantineProcessed READ getQuarantineProcessed  WRITE setQuarantineProcessed NOTIFY quarantineProcessedChanged)
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
    QString m_quarantineProcessed;
    void setQuarantineProcessed(const QString quarantineFile);
    QString getQuarantineProcessed();
signals:
    void quarantineFileChanged();
    void quarantineFileAdded(QString file);
    void quarantineProcessedChanged();
public slots:
    void setStart();
    void getQuarantineOptions(int indexNo,int OptionsNo);
    void getApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions);
    void getVirusOne(QString filePath,int virusOptions);

};
#endif // SCANRESULTOPERATIONS_H
