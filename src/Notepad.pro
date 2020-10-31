#-------------------------------------------------
#
# Project created by QtCreator 2019-08-28T19:57:25
#
#-------------------------------------------------

QT       += core gui concurrent printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notepad
TEMPLATE = app

include(project.pri)

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    project.pri \
    style/style.qss

FORMS += \
    testdialog.ui
