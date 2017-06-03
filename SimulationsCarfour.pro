#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T19:10:08
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SimulationsCarfour
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    generatedata.cpp \
    getdatainthread.cpp \
    datadialog.cpp \
    csvdata.cpp \
    writecsv.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    generatedata.h \
    getdatainthread.h \
    datadialog.h \
    csvdata.h \
    writecsv.h

FORMS    += mainwindow.ui \
    datadialog.ui \
    csvdata.ui
