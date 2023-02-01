QT += quick
QT += core
QT += widgets
QT += sql
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
        filechanges.cpp \
        filepathtransactions.cpp \
        klibrary.cpp \
        listenprocess.cpp \
        main.cpp \
        scanresultoperations.cpp \
        securefile.cpp \
        system.cpp \
        userdefinition.cpp \
        windowtaskbar.cpp

RESOURCES += qml.qrc
RC_ICONS=
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    filechanges.h \
    filepathtransactions.h \
    klibrary.h \
    listenprocess.h \
    scanresultoperations.h \
    securefile.h \
    system.h \
    userdefinition.h \
    windowtaskbar.h

win32: LIBS += -lOle32

win32: LIBS += -lOleAut32

win32: LIBS += -lwbemuuid

win32: LIBS += -liphlpapi

win32: LIBS += -lshell32
