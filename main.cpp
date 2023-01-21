#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <windowtaskbar.h>
#include <system.h>
#include <userdefinition.h>
#include <listenprocess.h>
#include <filepathtransactions.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication _app(argc, argv);
    QQmlApplicationEngine _engine;
    WindowTaskBar _windowstaskbar;
    System _system;
    listenProcess _listenProcess;
    filePathTransactions  filepathtransactions;
    userDefinition  _userdefinition;



    QQmlContext *ctx=_engine.rootContext();
    ctx->setContextProperty("windowstaskbar",&_windowstaskbar);
    ctx->setContextProperty("system",&_system);

    QObject::connect(&_userdefinition,SIGNAL(setFilePahtReg(QString*)),&filepathtransactions, SLOT(getFilePahtReg(QString*)));
    QObject::connect(&_listenProcess,SIGNAL(setFilePahtReg(QString*)),&filepathtransactions, SLOT(getFilePahtReg(QString*)));
    QObject::connect(&_userdefinition,SIGNAL(setRegList(Kmap<int, RegProgramList>)),&filepathtransactions, SLOT(getRegList(Kmap<int, RegProgramList>)));
    _userdefinition.userStart();
    _listenProcess.setStart();


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&_engine, &QQmlApplicationEngine::objectCreated,
                     &_app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    _engine.load(url);
    return _app.exec();
}
