#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T13:30:26
#
#-------------------------------------------------

QT       += core gui extserialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += extserialport
TARGET = irrigationsysApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gsmreader.cpp \
    datahelper.cpp

HEADERS  += mainwindow.h \
    gsmreader.h \
    datahelper.h

FORMS    += mainwindow.ui

addFiles.sources =data.db3
addFiles.path = /home/qasem/outapp/irrigationsystem/build-irrigationsysApp-desktoplinux4-Debug/
DEPLOYMENT += addFiles
