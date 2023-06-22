#ifndef FILECHANGES_H
#define FILECHANGES_H
#include <QObject>
#include <windows.h>
#include <sstream>
#include <thread>
#include <QDebug>
#include <Shlobj.h>
#include <codecvt>
#include <string>
class fileChanges : public QObject
{
    Q_OBJECT
public:
    explicit fileChanges(QObject *parent = nullptr);
    ~fileChanges();
private:
    QList<QString> filesToListen;
    int fileChangesThread_DESKTOP();
    int fileChangesThread_DOWNLOADS();

    HANDLE hFile_DESKTOP;
    HANDLE hFile_DOWNLOADS;
public:
signals:
    void setfileChangesNotification(QString filePath);
};

#endif // FILECHANGES_H
