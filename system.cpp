#include "system.h"
#include <windows.h>
#include <QStringList>
#include <fstream>
#include <QDebug>
#include <QThread>
System::System(QObject *parent): QObject{parent}
{
    emit scanFileName_changed("NULL");
    emit storage_changed();
}

bool System::get_scandisk_status(){
    return m_scandisk_status;
}
double System::byteToGb(long double byte) {
    double kilobyte;
    double megabyte;
    double gigabyte;
    kilobyte = byte / 1024;
    megabyte = kilobyte / 1024;
    gigabyte = megabyte / 1024;

    return gigabyte;
}

QString  System::get_storage() {
    QString  list;
    ULARGE_INTEGER p1, p2, p3;
    int driverNumbers = GetLogicalDrives();
    for (int i = 0;  i < 26; i++) {
        if ((1 << i) & driverNumbers) {
            char driverName[] = "A:\\";
            driverName[0] += i;
            if (GetDiskFreeSpaceExA(driverName, &p1, &p2, &p3) != 0) {
                list+=QString::fromStdString(driverName)+"/";
                list+=QString::number(byteToGb(p2.QuadPart),'f',1)+"/";
                list+=QString::number(byteToGb(p1.QuadPart),'f',1)+"@";
            }
        }
    }
    return list;
};
void System::set_scandisk(QString value,double total,double free){

    if(m_scandisk_status!=true){
        emit scanFileName_changed(value);
        m_scandisk=value;
        m_scandisk_status=true;
        emit scandisk_status_changed();
        std::string firstFilePath = value.toStdString();
        std::thread  scanThread(&System::scanDiskThreadControl, this, firstFilePath,(total-free)*1024*1024*1024);
        scanThread.detach();
    }
}
void System::scanDiskThreadControl(std::string firstFilePath,long double total){
    std::thread  scanThread(&System::scanDiskThread, this, firstFilePath,total);
    scanThread.join();
    emit scanFileName_changed("");
    breakScanThread=false;
    m_scandisk_status=false;

}
void System::scanDiskThread(std::string firstFilePath,long double total){
    WIN32_FIND_DATAA fileInformation;
  //  bool control= breakScanThread;
    HANDLE firstFile = FindFirstFileExA((firstFilePath+ "/*").c_str(), FindExInfoStandard, &fileInformation, FindExSearchNameMatch, NULL, 0);
    do {
        if ((std::string)fileInformation.cFileName !="." && (std::string)fileInformation.cFileName != "..") {

            if (GetFileAttributesA((firstFilePath + "/" + fileInformation.cFileName).c_str()) == FILE_ATTRIBUTE_DIRECTORY) {
                if(breakScanThread)
                    goto exit;
                scanDiskThread(firstFilePath + "/" + fileInformation.cFileName,total);
            }
            else {
                if(breakScanThread)
                    goto exit;
                QString net=QString::fromStdString(fileInformation.cFileName);
               // int netLength=net.size();
              //  if(net[netLength-1]=='e' && net[netLength-2]=='x' && net[netLength-3]=='e'){

              //  }
                Sleep(100);
                emit scanedFileName_changed(net);
              // emit scanFileName_changed(net);
              //  emit set_scanByte(fileInformation.nFileSizeLow);
              // emit scanFile_changed(QString::fromStdString(fileInformation.cFileName));
               // int scaneDisk=(100*total)/scanByte;
               // emit scandiskArea_changed(scaneDisk);
            }
        }
    } while (FindNextFileA(firstFile, &fileInformation));

    exit:
    FindClose(firstFile);
}
void System::set_scandiskClose(){
    breakScanThread=true;
    emit scanFileName_changed("");
    m_scandisk_status=false;
}









