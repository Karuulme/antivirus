#include "../Headers/filechanges.h"

fileChanges::fileChanges(QObject *parent): QObject{parent}
{
    std::thread  setStart_DESKTOP(&fileChanges::fileChangesThread_DESKTOP, this);
    setStart_DESKTOP.detach();

    std::thread  setStart_DOWNLOADS(&fileChanges::fileChangesThread_DOWNLOADS, this);
    setStart_DOWNLOADS.detach();
}
//-----------------------------------------------------------------------------------------
fileChanges::~fileChanges(){
    CloseHandle(hFile_DESKTOP);
    CloseHandle(hFile_DOWNLOADS);
}
//-----------------------------------------------------------------------------------------
int fileChanges::fileChangesThread_DESKTOP(){

    wchar_t  appData[MAX_PATH];
    std::string file_DESKTOP;
    SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_DEFAULT, appData);
    std::wstring ws(appData);
    std::string test(ws.begin(), ws.end() );
    file_DESKTOP=test;
    hFile_DESKTOP = CreateFileA(file_DESKTOP.c_str(), GENERIC_READ | FILE_LIST_DIRECTORY,
                                FILE_SHARE_DELETE | FILE_SHARE_READ| FILE_SHARE_WRITE, NULL,OPEN_EXISTING,
                                FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,NULL);
    if (hFile_DESKTOP == INVALID_HANDLE_VALUE)
        return 1;

    OVERLAPPED overlapped;
    overlapped.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    char lpBuffer[2048];
    DWORD lpBytesReturned;
    FILE_NOTIFY_INFORMATION* fileInformation;
    int offset;
    BOOL result = TRUE;
    QString filePath;
    while (result) {
        result= ReadDirectoryChangesW(hFile_DESKTOP, &lpBuffer, sizeof(lpBuffer), TRUE,FILE_NOTIFY_CHANGE_FILE_NAME
                                     | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE, &lpBytesReturned,&overlapped,NULL);
        WaitForSingleObject(overlapped.hEvent,INFINITE);
        offset = 0;
        char fileName[_MAX_PATH]="";
        do {
            fileInformation = (FILE_NOTIFY_INFORMATION*)((char*)lpBuffer + offset);
            WideCharToMultiByte(CP_ACP, 0, fileInformation->FileName, fileInformation->FileNameLength / 2, fileName, sizeof(fileName), NULL, NULL);
            fileName[fileInformation->FileNameLength / 2] = '\0';
            std::stringstream ss;
            std::string myString;
            ss << fileName;
            ss >> myString;
            filePath=QString::fromStdString(fileName);
            if(filePath.contains(".exe")){
                switch (fileInformation->Action)
                {
                case FILE_ACTION_ADDED:
                    qDebug()<<"FILE_ACTION_ADDED :"<<QString::fromStdString(file_DESKTOP)+"\\"+filePath;
                    emit setfileChangesNotification(QString::fromStdString(file_DESKTOP)+"\\"+filePath);
                    break;
                case FILE_ACTION_RENAMED_NEW_NAME:
                    qDebug()<<"FILE_ACTION_RENAMED_NEW_NAME :"<<QString::fromStdString(file_DESKTOP)+"\\"+filePath;
                    emit setfileChangesNotification(QString::fromStdString(file_DESKTOP)+"\\"+filePath);
                    break;
                default:
                    break;
                }
            }
            offset+= fileInformation->NextEntryOffset;
        } while (fileInformation->NextEntryOffset);
        //ResetEvent(overlapped.hEvent);
    }
    CloseHandle(hFile_DESKTOP);
    return 0;
}
//-----------------------------------------------------------------------------------------
int fileChanges::fileChangesThread_DOWNLOADS(){
    wchar_t  appData[MAX_PATH];
    std::string file_DOWNLOADS;
    SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_DEFAULT, appData);
    std::wstring ws( appData);
    std::string test( ws.begin(), ws.end());
    file_DOWNLOADS=test;
    file_DOWNLOADS.replace(file_DOWNLOADS.find("Desktop"), file_DOWNLOADS.length(), "Downloads");
    hFile_DOWNLOADS = CreateFileA(file_DOWNLOADS.c_str(), GENERIC_READ | FILE_LIST_DIRECTORY, FILE_SHARE_DELETE | FILE_SHARE_READ| FILE_SHARE_WRITE, NULL,OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,NULL);
    if (hFile_DOWNLOADS == INVALID_HANDLE_VALUE)
        return 1;
    OVERLAPPED overlapped;
    overlapped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    char lpBuffer[2048];
    DWORD lpBytesReturned;
    FILE_NOTIFY_INFORMATION* fileInformation;
    int offset;
    BOOL result = TRUE;
    QString filePath;
    while (result) {
        result= ReadDirectoryChangesW(hFile_DOWNLOADS, &lpBuffer, sizeof(lpBuffer), TRUE,FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE, &lpBytesReturned,&overlapped,NULL);
        WaitForSingleObject(overlapped.hEvent,INFINITE);
        offset = 0;
        char fileName[_MAX_PATH]="";
        do {
            fileInformation = (FILE_NOTIFY_INFORMATION*)((char*)lpBuffer + offset);
            WideCharToMultiByte(CP_ACP, 0, fileInformation->FileName, fileInformation->FileNameLength / 2, fileName, sizeof(fileName), NULL, NULL);
            fileName[fileInformation->FileNameLength / 2] = '\0';
            std::stringstream ss;
            std::string myString;
            ss << fileName;
            ss >> myString;
            filePath=QString::fromStdString(fileName);
            if(filePath.contains(".exe")){
                switch (fileInformation->Action)
                {
                case FILE_ACTION_ADDED:
                    qDebug()<<"FILE_ACTION_ADDED :"<<QString::fromStdString(file_DOWNLOADS)+"\\"+filePath;
                    emit setfileChangesNotification(QString::fromStdString(file_DOWNLOADS)+"\\"+filePath);
                    break;
                case FILE_ACTION_RENAMED_NEW_NAME:
                    qDebug()<<"FILE_ACTION_RENAMED_NEW_NAME :"<<QString::fromStdString(file_DOWNLOADS)+"\\"+filePath;
                    emit setfileChangesNotification(QString::fromStdString(file_DOWNLOADS)+"\\"+filePath);
                    break;
                default:
                    break;
                }
            }
            offset+= fileInformation->NextEntryOffset;
        } while (fileInformation->NextEntryOffset);
    }
    CloseHandle(hFile_DOWNLOADS);
    return 0;
}
//-----------------------------------------------------------------------------------------
