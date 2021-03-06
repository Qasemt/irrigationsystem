#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T13:30:26
#
#-------------------------------------------------

QT       += core gui extserialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += extserialport
 CONFIG += debug exceptions
TARGET = irrigationsysApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gsmreader.cpp \
    datahelper.cpp \
    modelsystemparameter.cpp \
    bssystemparameter.cpp \
    frmdbtest.cpp \
    modeldailytime.cpp \
    bsmodeldailytime.cpp \
    basebusiness.cpp \
    modelcustomtime.cpp \
    modeldeviceinfo.cpp \
    modeleventslog.cpp \
    modelmanualtime.cpp \
    modelweeklytime.cpp \
    bsweeklytime.cpp \
    bsmanualtime.cpp \
    bsdeviceinfo.cpp \
    bscustomtime.cpp \
    bseventslog.cpp \
    frmcmdtest.cpp \
    messagewatcher.cpp \
    qdateconvertor.cpp \
    deviceprocess.cpp \
    imagedelegate.cpp \
    myapplication.cpp

HEADERS  += mainwindow.h \
    gsmreader.h \
    datahelper.h \
    modelsystemparameter.h \
    bssystemparameter.h \
    frmdbtest.h \
    modeldailytime.h \
    bsmodeldailytime.h \
    basebusiness.h \
    modelcustomtime.h \
    modeldeviceinfo.h \
    modeleventslog.h \
    modelmanualtime.h \
    modelweeklytime.h \
    bsweeklytime.h \
    bsmanualtime.h \
    bsdeviceinfo.h \
    bscustomtime.h \
    bseventslog.h \
    frmcmdtest.h \
    messagewatcher.h \
    qdateconvertor.h \
    aenums.h \
    deviceprocess.h \
    imagedelegate.h \
    myapplication.h

FORMS    += mainwindow.ui \
    frmdbtest.ui \
    frmcmdtest.ui

addFiles.sources =data.db3
addFiles.path = /home/qasem/outapp/irrigationsystem/build-irrigationsysApp-desktoplinux4-Debug/
DEPLOYMENT += addFiles

RESOURCES += \
    resourcefiles/res.qrc
