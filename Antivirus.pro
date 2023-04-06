QT += quick
QT += xml
QT += core
QT += widgets
QT += sql
CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG += separate_debug_info
CONFIG += link_separate

# Debug configuration
CONFIG(debug, debug|release) {
    TARGET = YourProjectName_debug
    DESTDIR = debug
    OBJECTS_DIR = debug/obj
    MOC_DIR = debug/moc
    RCC_DIR = debug/rcc
    UI_DIR = debug/ui
}

# Release configuration
CONFIG(release, debug|release) {
    TARGET = YourProjectName
    DESTDIR = release
    OBJECTS_DIR = release/obj
    MOC_DIR = release/moc
    RCC_DIR = release/rcc
    UI_DIR = release/ui
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
        Sources/customsystem.cpp \
        Sources/filechanges.cpp \
        Sources/filepathtransactions.cpp \
        Sources/hookingcalls.cpp \
        Sources/klibrary.cpp \
        Sources/listenprocess.cpp \
        Sources/notificationlisten.cpp \
        Sources/processmemet.cpp \
        Sources/scanresultoperations.cpp \
        Sources/securefile.cpp \
        Sources/system.cpp \
        Sources/userdefinition.cpp \
        Sources/windowtaskbar.cpp \
        main.cpp

HEADERS += \
    Headers/customsystem.h \
    Headers/filechanges.h \
    Headers/filepathtransactions.h \
    Headers/hookingcalls.h \
    Headers/klibrary.h \
    Headers/listenprocess.h \
    Headers/notificationlisten.h \
    Headers/processmemet.h \
    Headers/scanresultoperations.h \
    Headers/securefile.h \
    Headers/system.h \
    Headers/userdefinition.h \
    Headers/windowtaskbar.h

RESOURCES += qml.qrc

DISTFILES += \
    settings2.xml

RC_ICONS=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -lOle32
win32: LIBS += -lOleAut32
win32: LIBS += -lwbemuuid
win32: LIBS += -liphlpapi
win32: LIBS += -lshell32
