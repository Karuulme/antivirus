#ifndef SYSTEM_H
#define SYSTEM_H
#include <QArrayData>
#include <QObject>
#include <QThreadPool>
#include <QMap>
#include <QFileDialog>
#include <QtWidgets>
#include <iostream>
#include <string>
#include <windows.h>
#include <QStringList>
#include <fstream>
#include <QDebug>
#include <QThread>
#include <QtXml>
#include <QFile>

#include <filesystem>
class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString  storageList READ get_storage NOTIFY storage_changed)
    Q_PROPERTY(bool scandisk_status READ get_scandisk_status NOTIFY scandisk_status_changed)
    Q_PROPERTY(QString scanedFileName READ getscanedFileName WRITE setSescanedFileName NOTIFY scanedFileName_changed)
    Q_PROPERTY(QString scaningDisk READ getscaningDisk WRITE setscaningDisk NOTIFY scaningDisk_changed)

public:
    explicit System(QObject *parent = nullptr);
private:
   double byteToGb(long double byte);
   QString get_storage();
   bool get_scandisk_status();
   void scanDiskThread(std::string firstFilePath,long double total);
   void scanDiskThreadControl(std::string firstFilePath,long double total);
   void set_scanFile(QString scanFile);

   QString getscanedFileName();
   void setSescanedFileName(QString value);

   QString getscaningDisk();
   void setscaningDisk(QString value);


    //Değişkenler
    QString m_name;
    bool m_scandisk_status=false;
    QString m_scandisk;
    long double ld_scanDiskTotalByte;
    long double ld_scanedDiskTotalByte;
    bool breakScanThread=false;
    long double scanByte;
    QString scanHDDName;
    QMap<int,QString> malwareList;
    QMap<int,int> malwareListOptions;
    int malwareListIndex=0;
    bool autoScanResult=false;
    int virusOptionIndex=0;
    int computerOptionIndex=0;
    QString m_scanedFileName;
    QString m_scaningDisk;

signals:
    void name_changed();
    void storage_changed();
    void scandisk_status_changed();
    void scandiskArea_changed(int scandiskArea);
    void scanFile_changed(QString value);
   // void scanFileName_changed(QString scanFileName);
   // void set_scanTotalByte(double scanTotalByte);
   // void set_scanByte(double scanByte);
    void setApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions);
    void scanedFileName_changed();
    void scaningDisk_changed();
public slots:
    void set_scandisk(QString value,double total,double free);
    void set_scandiskClose();
    void set_get_storage();
    void set_ScanResultApply();
    void set_singleVirusChanges(int index,int setvalue);
    void set_ScanResultAutoApply(int index);
    void set_VirusComputerOption(int virus,int computer);
};
#endif // SYSTEM_H















