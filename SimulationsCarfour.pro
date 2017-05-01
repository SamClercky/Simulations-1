#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T19:10:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SimulationsCarfour
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    generatedata.cpp \
    getdatainthread.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    generatedata.h \
    getdatainthread.h

FORMS    += mainwindow.ui
