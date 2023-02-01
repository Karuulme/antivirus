#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

#include <windowtaskbar.h>
#include <system.h>
//#include <userdefinition.h>
//#include <listenprocess.h>
#include <filepathtransactions.h>
#include <filechanges.h>
#include <scanresultoperations.h>
#include <securefile.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication _app(argc, argv);
    QIcon icon(":Image/logo2ico.ico");
    _app.setWindowIcon(icon);
    QQmlApplicationEngine _engine;
    WindowTaskBar _windowstaskbar;
    System _system;
   // listenProcess _listenProcess;
    filePathTransactions  filepathtransactions;
   // userDefinition  _userdefinition;
    fileChanges  _filechanges;
    scanResultOperations _scanresultoperations;
    secureFile _secureFile;

    QQmlContext *ctx=_engine.rootContext();
    ctx->setContextProperty("windowstaskbar",&_windowstaskbar);
    ctx->setContextProperty("system",&_system);
    ctx->setContextProperty("securefile",&_secureFile);

    //QObject::connect(&_userdefinition,SIGNAL(setFilePahtReg(QString*)),&filepathtransactions, SLOT(getFilePahtReg(QString*)));
  //  QObject::connect(&_listenProcess,SIGNAL(setFilePahtReg(QString*)),&filepathtransactions, SLOT(getFilePahtReg(QString*)));
   // QObject::connect(&_userdefinition,SIGNAL(setRegList(Kmap<int, RegProgramList>)),&filepathtransactions, SLOT(getRegList(Kmap<int, RegProgramList>)));
    QObject::connect(&_filechanges,SIGNAL(setfileChangesNotification(QString)),&filepathtransactions, SLOT(getfileChangesNotification(QString)));
    QObject::connect(&_system,SIGNAL(setApplyResults(QMap<int,QString>,QMap<int,int>,int,int)),&_scanresultoperations, SLOT(getApplyResults(QMap<int,QString>,QMap<int,int>,int,int)));

    //_userdefinition.setStart();
    //_listenProcess.setStart();
    //_secureFile.setStart();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&_engine, &QQmlApplicationEngine::objectCreated,
                     &_app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    _engine.load(url);


    //------------------------SYSTEM TRAY  --->>
   /* QObject *root = 0;
    if (_engine.rootObjects().size() > 0)
    {
        root = _engine.rootObjects().at(0);

        QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), root);
        root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
        QAction *maximizeAction = new QAction(QObject::tr("Ma&ximize"), root);
        root->connect(maximizeAction, SIGNAL(triggered()), root, SLOT(showMaximized()));
        QAction *restoreAction = new QAction(QObject::tr("&Restore"), root);
        root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
        QAction *quitAction = new QAction(QObject::tr("&Quit"), root);
        root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        QMenu *trayIconMenu = new QMenu();
        trayIconMenu->addAction(minimizeAction);
        trayIconMenu->addAction(maximizeAction);
        trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);

        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon(":/icon.png"));
        trayIcon->show();
    }*/

   // ------------------------SYSTEM TRAY  <<---


    return _app.exec();
}
