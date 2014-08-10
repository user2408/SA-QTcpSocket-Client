#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T18:21:56
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SA-qt-socket
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    changeaccountdialog.cpp

HEADERS  += mainwindow.h \
    changeaccountdialog.h

FORMS    += mainwindow.ui \
    changeaccountdialog.ui
