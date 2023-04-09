#include "../Headers/system.h"
System::System(QObject *parent): QObject{parent}
{
    QFile inFile("settings2.xml");
    if (inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Dosya acildi";
        QXmlStreamReader xmlReader(&inFile);
        while (xmlReader.readNextStartElement())
        {
            if (xmlReader.name().toString() == "language")
            {
                qDebug()<<xmlReader.readElementText();
            }
        }
    }
    else{
        qDebug()<<"Dosya acilmadi";
    }


    //emit setscaningDisk("NULL");
    //emit storage_changed();
}
//-----------------------------------------------------------------------------------------
bool System::get_scandisk_status(){
    return m_scandisk_status;
}
//-----------------------------------------------------------------------------------------
double System::byteToGb(long double byte) {
    double kilobyte;
    double megabyte;
    double gigabyte;
    kilobyte = byte / 1024;
    megabyte = kilobyte / 1024;
    gigabyte = megabyte / 1024;
    return gigabyte;
}
//-----------------------------------------------------------------------------------------
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
}
//-----------------------------------------------------------------------------------------
void System::set_scandisk(QString value,double total,double free){

    if(m_scandisk_status!=true){
        scanHDDName=value;
        setscaningDisk(scanHDDName);
        m_scandisk=value;
        m_scandisk_status=true;
        emit scandisk_status_changed();
        std::string firstFilePath = value.toStdString();
        std::thread  scanThread(&System::scanDiskThreadControl, this, firstFilePath,(total-free)*1024*1024*1024);
        scanThread.detach();

    }
}
//-----------------------------------------------------------------------------------------
void System::scanDiskThreadControl(std::string firstFilePath,long double total){
    std::thread  scanThread(&System::scanDiskThread, this, firstFilePath,total);
    scanThread.join();
    scanHDDName="";
    setscaningDisk(scanHDDName);
    breakScanThread=false;
    m_scandisk_status=false;
    emit scandisk_status_changed();
}
//-----------------------------------------------------------------------------------------
void System::scanDiskThread(std::string firstFilePath,long double total){
    WIN32_FIND_DATAA fileInformation;
    HANDLE firstFile = FindFirstFileExA((firstFilePath+ "/*").c_str(), FindExInfoStandard, &fileInformation, FindExSearchNameMatch, NULL, 0);
    do {
        if(breakScanThread)
            goto exit;
        if ((std::string)fileInformation.cFileName !="." && (std::string)fileInformation.cFileName != "..") {
            if (GetFileAttributesA((firstFilePath + "/" + fileInformation.cFileName).c_str()) == FILE_ATTRIBUTE_DIRECTORY) {
                if(breakScanThread)
                    goto exit;
                scanDiskThread(firstFilePath + "/" + fileInformation.cFileName,total);
            }
            else {
                QString fileName=QString::fromStdString(fileInformation.cFileName);
                int netLength=fileName.size();
                if(fileName[netLength-1]=='e' && fileName[netLength-2]=='x' && fileName[netLength-3]=='e'){
                    setSescanedFileName(fileName+"q:"+QString::number(malwareListIndex));

                    malwareList[malwareListIndex]=QString::fromStdString(firstFilePath)+"//"+fileName;
                    malwareListIndex++;
                }
                Sleep(200);
              // emit scanFileName_changed(net);
              // emit set_scanByte(fileInformation.nFileSizeLow);
              // emit scanFile_changed(QString::fromStdString(fileInformation.cFileName));
               //int scaneDisk=(100*total)/scanByte;
               //emit scandiskArea_changed(scaneDisk);
            }
        }
    } while (FindNextFileA(firstFile, &fileInformation));
    exit:
    FindClose(firstFile);
}
//-----------------------------------------------------------------------------------------
void System::set_scandiskClose(){
    breakScanThread=true;
    setscaningDisk("");
    m_scandisk_status=false;
    if(autoScanResult)
       set_ScanResultApply();
}
//-----------------------------------------------------------------------------------------
void System::set_get_storage(){
    emit storage_changed();
    setscaningDisk(scanHDDName);
}
//-----------------------------------------------------------------------------------------
void System::set_ScanResultApply(){
    emit setApplyResults(malwareList,malwareListOptions,virusOptionIndex,computerOptionIndex);
}
//-----------------------------------------------------------------------------------------
void System::set_singleVirusChanges(int index,int setvalue){
    malwareListOptions[index]=setvalue;
}
//-----------------------------------------------------------------------------------------
void System::set_ScanResultAutoApply(int index){
    autoScanResult=index;
}
//-----------------------------------------------------------------------------------------
void System::set_VirusComputerOption(int virus,int computer){
    virusOptionIndex=virus;
    computerOptionIndex=computer;
}
//-----------------------------------------------------------------------------------------
QString System::getscanedFileName(){
    return m_scanedFileName;
}
//-----------------------------------------------------------------------------------------
void System::setSescanedFileName(QString value){
    m_scanedFileName=value;
    emit scanedFileName_changed();
}
//-----------------------------------------------------------------------------------------
QString System::getscaningDisk() {
    return m_scaningDisk;
}
//-----------------------------------------------------------------------------------------
void System::setscaningDisk(QString value) {
   m_scaningDisk=value;
   emit scaningDisk_changed();
}
//-----------------------------------------------------------------------------------------






