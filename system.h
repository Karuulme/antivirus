#ifndef SYSTEM_H
#define SYSTEM_H
#include <QArrayData>
#include <QObject>
#include <QThreadPool>

class System : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString  storageList READ get_storage NOTIFY storage_changed)
     Q_PROPERTY(bool  scandisk_status READ get_scandisk_status NOTIFY scandisk_status_changed)

public:
    explicit System(QObject *parent = nullptr);


private:
   double byteToGb(long double byte);
   QString get_storage();
   bool get_scandisk_status();
   void scanDiskThread(std::string firstFilePath,long double total);
   void scanDiskThreadControl(std::string firstFilePath,long double total);
   void set_scanFile(QString scanFile);

    //Değişkenler
    QString m_name;
    bool m_scandisk_status=false;
    QString m_scandisk;
    long double ld_scanDiskTotalByte;
    long double ld_scanedDiskTotalByte;
    bool breakScanThread=false;
    long double scanByte;


signals:
    void name_changed();
    void storage_changed();
    void scandisk_status_changed();
    void scandiskArea_changed(int scandiskArea);
    void scanFile_changed(QString value);
    void scanFileName_changed(QString scanFileName);
    void scanedFileName_changed(QString scanedFileName);
   // void set_scanTotalByte(double scanTotalByte);
   // void set_scanByte(double scanByte);
public slots:
    void set_scandisk(QString value,double total,double free);
    void set_scandiskClose();
    void set_get_storage(){emit storage_changed();}

};
#endif // SYSTEM_H
