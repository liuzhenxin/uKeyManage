#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T16:35:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fileManage
TEMPLATE = app
RC_ICONS = "img.ico"
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        SM4.cpp \
        certparse.cpp \
        choosekeydialog.cpp \
        cparseseal.cpp \
        dialogforcreatefile.cpp \
        main.cpp \
        mainwindow.cpp \
        typedefine.cpp \
        usbthread.cpp \
        utilfunction.cpp \
        verifypin.cpp

HEADERS += \
        B_SESealASN1.h \
        OFD_SESealASN1.h \
        OFD_ZWFWSESealASN1.h \
        SESealASN1.h \
        SM4.h \
        certparse.h \
        choosekeydialog.h \
        cparseseal.h \
        dialogforcreatefile.h \
        mainwindow.h \
        typedefine.h \
        usbthread.h \
        utilfunction.h \
        verifypin.h

FORMS += \
        choosekeydialog.ui \
        dialogforcreatefile.ui \
        mainwindow.ui \
        verifypin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    image.qrc



LIBS += -L$$PWD/openssl/lib/ -llibssl
LIBS += -L$$PWD/openssl/lib/ -llibcrypto
LIBS += -lsetupapi

INCLUDEPATH += $$PWD/openssl/include
DEPENDPATH += $$PWD/openssl/include
