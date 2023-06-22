#include <QApplication>
#include <QQmlApplicationEngine>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QQmlContext>
#include <QCursor>
#include <QTimer>
#include <QThread>
//------------------------------------------------------------------
bool _identificationConfirmation=false;
//------------------------------------------------------------------
#include <Headers/klibrary.h>
#include <Headers/userdefinition.h>
#include <Headers/listenprocess.h>
#include <Headers/filepathtransactions.h>
#include <Headers/filechanges.h>
#include <Headers/scanresultoperations.h>
#include <Headers/securefile.h>
#include <Headers/hookingcalls.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    QApplication app(__argc,__argv);
    QApplication::setQuitOnLastWindowClosed(false);
    QIcon icon(":Image/logo2ico.ico");
    app.setWindowIcon(icon);
    if (!IsUserAnAdmin()) //Admin Control
    {
        MessageBoxA(NULL,"Please Start As Admin","Error",MB_OK);
        exit(EXIT_FAILURE);
        return app.exec();

    }
    QQmlApplicationEngine engine;
    listenProcess _listenProcess;
    filePathTransactions  _filepathtransactions;
    fileChanges  _filechanges;
    scanResultOperations _scanresultoperations;
    secureFile _secureFile;
    HookingCalls _hookingCalls;
    userDefinition _userdefinition;

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        QVariant cursorPos = QVariant::fromValue(QCursor::pos());
        engine.rootContext()->setContextProperty("cursorPos", cursorPos);
    });
    timer.start(10);

    QQmlContext *ctx=engine.rootContext();
    ctx->setContextProperty("securefile",&_secureFile);
    ctx->setContextProperty("quarantine",&_scanresultoperations);
    ctx->setContextProperty("userdefinition",&_userdefinition);
    ctx->setContextProperty("filepathtransactions",&_filepathtransactions);

    QObject::connect(&_userdefinition,SIGNAL(setFilePahtReg(QString,unsigned long int)),&_filepathtransactions, SLOT(getFilePahtReg(QString,unsigned long int)));
    QObject::connect(&_listenProcess,SIGNAL(setFilePahtReg(QString,unsigned long int)),&_filepathtransactions, SLOT(getFilePahtReg(QString,unsigned long int)));
    QObject::connect(&_userdefinition,SIGNAL(setRegList(Kmap<int, RegProgramList>)),&_filepathtransactions, SLOT(getRegList(Kmap<int, RegProgramList>)));
    QObject::connect(&_filechanges,SIGNAL(setfileChangesNotification(QString)),&_filepathtransactions, SLOT(getfileChangesNotification(QString)));
    QObject::connect(&_filepathtransactions,SIGNAL(setApplyResults(QMap<int,QString>,QMap<int,int>,int,int)),&_scanresultoperations, SLOT(getApplyResults(QMap<int,QString>,QMap<int,int>,int,int)));
    QObject::connect(&_secureFile,SIGNAL(setSecureList(QList<RegSecureFile>*)),&_hookingCalls, SLOT(getSecureList(QList<RegSecureFile>*)));
    QObject::connect(&_filepathtransactions,SIGNAL(setDllEnjection(unsigned long int)),&_hookingCalls, SLOT(getDllEnjection(unsigned long int)));
    QObject::connect(&_userdefinition,SIGNAL(setUserDefinitions_Delete_Signal()),&_secureFile, SLOT(getUserDefinitions_Delete_Signal()));
    QObject::connect(&_userdefinition,SIGNAL(setUserDefinitions_FileOperations(QVector<QString>*)),&_filepathtransactions, SLOT(getUserDefinitions_FileOperations(QVector<QString>*)));
    QObject::connect(&_filepathtransactions,SIGNAL(setVirusOne(QString ,int )),&_scanresultoperations, SLOT(getVirusOne(QString ,int )));


    /*QThread threadFilepathtransactions;
    _filepathtransactions.moveToThread(&threadFilepathtransactions);
    threadFilepathtransactions.start();*/

   /* QThread threadListenProcess;
    _listenProcess.moveToThread(&threadListenProcess);
    threadListenProcess.start();*/
    _userdefinition.setStart();

    engine.load(QUrl(QStringLiteral("qrc:///view/main.qml")));
    QObject *rootObject = engine.rootObjects().first();
    QObject::connect(rootObject, SIGNAL(startTimer()), &timer, SLOT(start()));
    QObject::connect(rootObject, SIGNAL(stopTimer()), &timer, SLOT(stop()));
    timer.stop();
    QObject *root = 0;
    if (engine.rootObjects().size() > 0)
    {
        root = engine.rootObjects().at(0);
        QAction *minimizeAction = new QAction(QObject::tr("&Open"), root);
        root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(showNormal()));
        //QAction *restoreAction = new QAction(QObject::tr("&Close"), root);
        //root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(hide()));
        QAction *quitAction = new QAction(QObject::tr("&Quit"), root);
        root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        QMenu *trayIconMenu = new QMenu();
        trayIconMenu->addAction(minimizeAction);
        //trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);

        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon(":/Image/logo2ico"));
        trayIcon->show();
    }
    return app.exec();
}
/*
System Tray
https://stackoverflow.com/questions/24423418/is-it-possible-to-implement-systemtrayicon-functionality-in-qt-quick-application
*/
