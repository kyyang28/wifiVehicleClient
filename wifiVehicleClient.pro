#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T13:50:13
#
#-------------------------------------------------

QT       += core gui network

TARGET = wifiVehicleClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    displayvideo.cpp \
    control.cpp \
    setupdialog.cpp \
    aboutdialog.cpp \
    grapdialog.cpp \
    logindialog.cpp \
    ctrlmodedialog.cpp

HEADERS  += mainwindow.h \
    displayvideo.h \
    control.h \
    setupdialog.h \
    aboutdialog.h \
    grapdialog.h \
    logindialog.h \
    ctrlmodedialog.h

FORMS    += mainwindow.ui \
    setupdialog.ui \
    aboutdialog.ui \
    grapdialog.ui \
    grapdialog.ui \
    logindialog.ui \
    ctrlmodedialog.ui

RESOURCES += \
    wifiVehicleImages.qrc

OTHER_FILES += \
    icon.rc

RC_FILE = \
    icon.rc













