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
#include <string>
#include <QStringList>
#include <fstream>
#include <QtNetwork>
#include <QMap>
#include <QFileDialog>
#include <QtWidgets>
#include <QThread>
#include <QMutex>
extern bool _identificationConfirmation;

class Pythonconnection : public QObject
{
    Q_OBJECT
public:
    explicit Pythonconnection(QObject *parent = nullptr);
   // ~connection();
    HANDLE hEventReturnValue{};
    PROCESS_INFORMATION processInfoVirusProcessDetection;
    DWORD dwhVirusProcessId;
    QString filePathExe="mele/mele.exe";

    void startConnection();
    QMutex mxGlobalScan;
    bool scanResult=false;
    void acceptConnection();
    int startVirusDetectionProcess();
    int virusDetectionProcessStatus();
    LPCWSTR QStringToLPCWSTR(const QString& qstr);

signals:
    void finished();

public slots:
    void readDataFromPython();
    void getdataWillSendToScan(const QString message);

private:
    QTcpServer server;
    QTcpSocket *clientConnection = nullptr;
    QByteArray buffer;
};
//-------------------------------------------------------
class filePathTransactions : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString  storageList READ get_storage NOTIFY storage_changed)
    Q_PROPERTY(bool scandisk_status READ get_scandisk_status NOTIFY scandisk_status_changed)
    Q_PROPERTY(QString scanedFileName READ getscanedFileName WRITE setSescanedFileName NOTIFY scanedFileName_changed)
    Q_PROPERTY(QString scaningDisk READ getscaningDisk WRITE setscaningDisk NOTIFY scaningDisk_changed)
    Q_PROPERTY(QString userDefinitions_UploadIndexNo READ getuserDefinitions_UploadIndexNo  NOTIFY userDefinitions_UploadIndexNoChanged);
public:
    explicit filePathTransactions(QObject *parent = nullptr);
    ~filePathTransactions();
    int  setRegCreateBank(HKEY hKey, std::string path, std::string key, std::string value);
    RegProgramList upRegListControl(Kstring reg);
    bool boolRegListControl(Kstring regg);
    int setRegQuestion(QString filePath,unsigned long int pID=-1);
    int regeditNewRecord(RegProgramList regProgram,int runCount=-1);
    QString getfileHash(QString filePath);
    int dllEnjection(unsigned long int pID);
    void getUserDefinitions_FileOperations_Thread(QVector<QString> regInstallProgram);
    QString getuserDefinitions_UploadIndexNo();
    QString m_userDefinitions_UploadIndexNo;




    Pythonconnection *_connection;
    QThread *threadConnection = new QThread(this);


    //Soket ->
   /* QTcpServer server;
    QTcpSocket *clientConnection = nullptr;
    void readDataFromPython();
    void sendDataToPython(QString message);
    void acceptConnection();*/
    //Soket <-


private:
    double byteToGb(long double byte);
    QString get_storage();
    bool get_scandisk_status();
    void scanDiskThread(std::string firstFilePath,long double total);
    void scanDiskThreadControl(std::string firstFilePath,long double total);
    void set_scanFile(QString scanFile);
    int machineLearning(QString filePath);

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


    Kmap<int, RegProgramList>  regList;
    int regListIndex=0;
signals:
    void name_changed();
    void storage_changed();
    void scandisk_status_changed();
    void scandiskArea_changed(int scandiskArea);
    void scanFile_changed(QString value);
    void setApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions);
    void scanedFileName_changed();
    void scaningDisk_changed();
    void setVirusOne(QString filePath,int virusOptions);
    //------------------------------------------
    void setDllEnjection(unsigned long int pID);
    void userDefinitions_UploadChanged();
    void userDefinitions_UploadIndexNoChanged();
    void setdataWillSendToScan(const QString filePath);

public slots:
    void setTest(QString adddress);
    void set_scandisk(QString value,double total,double free);
    void set_scandiskClose();
    void set_get_storage();
    void set_ScanResultApply();
    void set_singleVirusChanges(int index,int setvalue);
    void set_ScanResultAutoApply(int index);
    void set_VirusComputerOption(int virus,int computer);
    void getVirusOne(QString filePath,int virusOptions,int index);
    //-------------------------------------------------------------
    void getFilePahtReg(QString filePath,unsigned long int pID);
    void getRegList(Kmap<int, RegProgramList> reg);
    void getfileChangesNotification(QString filePath);
    void getProgramTime(unsigned __int8 value);
    void getUserDefinitions_FileOperations(QVector<QString>* regInstallProgram);


    void send(const QString message);


};
#endif // FILEPATHTRANSACTIONS_H
