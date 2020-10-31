#-------------------------------------------------
#
# Project created by QtCreator 2019-08-28T19:57:25
#
#-------------------------------------------------
TARGET = Notepad
TEMPLATE = app

include(project.pri)

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

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
