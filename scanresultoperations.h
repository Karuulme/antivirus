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
class scanResultOperations : public QObject
{
    Q_OBJECT
public:
    explicit scanResultOperations(QObject *parent = nullptr);
    void getProgramData();
private:
    void virusProcesses(QString path,int Options);
    void computerOperations(int Options);
    void getMac();
    void encrypt(QString file);
    void Decrypt(QString file);
    QString mac_Address;
    QString quarantineAddress;
signals:
public slots:
    void getApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions);
};
#endif // SCANRESULTOPERATIONS_H
