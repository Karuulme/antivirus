#include <QApplication>
#include <QQmlApplicationEngine>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QQmlContext>
//------------------------------------------------------------------
bool _identificationConfirmation=false;
//------------------------------------------------------------------
#include <Headers/windowtaskbar.h>
#include <Headers/system.h>
#include <Headers/userdefinition.h>
#include <Headers/listenprocess.h>
#include <Headers/filepathtransactions.h>
#include <Headers/filechanges.h>
#include <Headers/scanresultoperations.h>
#include <Headers/securefile.h>
#include <Headers/hookingcalls.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    QIcon icon(":Image/logo2ico.ico");
    app.setWindowIcon(icon);
    QQmlApplicationEngine engine;
    userDefinition  _userdefinition;
    WindowTaskBar _windowstaskbar;
    System _system;
    listenProcess _listenProcess;
    filePathTransactions  _filepathtransactions;
    fileChanges  _filechanges;
    scanResultOperations _scanresultoperations;
    secureFile _secureFile;
    HookingCalls _hookingCalls;

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                                 QObject::tr("I couldn't detect any system tray "
                                             "on this system."));
        return 1;
    }
    QQmlContext *ctx=engine.rootContext();
    ctx->setContextProperty("windowstaskbar",&_windowstaskbar);
    ctx->setContextProperty("system",&_system);
    ctx->setContextProperty("securefile",&_secureFile);
    ctx->setContextProperty("quarantine",&_scanresultoperations);
    ctx->setContextProperty("userdefinition",&_userdefinition);

    QObject::connect(&_userdefinition,SIGNAL(setFilePahtReg(QString,unsigned long int)),&_filepathtransactions, SLOT(getFilePahtReg(QString,unsigned long int)));
    QObject::connect(&_listenProcess,SIGNAL(setFilePahtReg(QString,unsigned long int)),&_filepathtransactions, SLOT(getFilePahtReg(QString,unsigned long int)));
    QObject::connect(&_userdefinition,SIGNAL(setRegList(Kmap<int, RegProgramList>)),&_filepathtransactions, SLOT(getRegList(Kmap<int, RegProgramList>)));
    QObject::connect(&_filechanges,SIGNAL(setfileChangesNotification(QString)),&_filepathtransactions, SLOT(getfileChangesNotification(QString)));
    QObject::connect(&_system,SIGNAL(setApplyResults(QMap<int,QString>,QMap<int,int>,int,int)),&_scanresultoperations, SLOT(getApplyResults(QMap<int,QString>,QMap<int,int>,int,int)));
    QObject::connect(&_secureFile,SIGNAL(setSecureList(QList<QString>*)),&_hookingCalls, SLOT(getSecureList(QList<QString>*)));
    QObject::connect(&_filepathtransactions,SIGNAL(setDllEnjection(unsigned long int)),&_hookingCalls, SLOT(getDllEnjection(unsigned long int)));

    _userdefinition.setStart();
    _listenProcess.setStart();
   // _secureFile.setStart();
    //_scanresultoperations.setStart();
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    QObject *root = 0;
    if (engine.rootObjects().size() > 0)
    {
        root = engine.rootObjects().at(0);

        QAction *minimizeAction = new QAction(QObject::tr("&Open"), root);
        root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(showNormal()));
        QAction *restoreAction = new QAction(QObject::tr("&Close"), root);
        root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(hide()));
        QAction *quitAction = new QAction(QObject::tr("&Quit"), root);
        root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        QMenu *trayIconMenu = new QMenu();
        trayIconMenu->addAction(minimizeAction);
        trayIconMenu->addAction(restoreAction);
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
