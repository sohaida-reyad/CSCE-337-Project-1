#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T14:54:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Logic-Circuit-Beautifier
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DAG.cpp \
    TopoSort.cpp

HEADERS  += mainwindow.h \
    DAG.h \
    gate.h \
    TopoSort.h

FORMS    += mainwindow.ui
