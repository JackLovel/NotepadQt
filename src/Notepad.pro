#-------------------------------------------------
#
# Project created by QtCreator 2019-08-28T19:57:25
#
#-------------------------------------------------

QT       += core gui concurrent printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notepad
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        advancesettingpage.cpp \
#        config.cpp \
        contact.cpp \
        content.cpp \
        editor.cpp \
        finddialog.cpp \
        golinedialog.cpp \
        main.cpp \
        mainwindow.cpp \
        md5dialog.cpp \
        replacedialog.cpp \
        settingdialog.cpp \
        shortcutpage.cpp \
        util.cpp

HEADERS += \
        advancesettingpage.h \
        config.h \
        contact.h \
        content.h \
        editor.h \
        finddialog.h \
        golinedialog.h \
        mainwindow.h \
        md5dialog.h \
        replacedialog.h \
        settingdialog.h \
        shortcutpage.h \
        util.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    style/style.qss
