#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T10:57:42
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CaixeiroViajante
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logpane.cpp \
    representationpane.cpp \
    chartpane.cpp

HEADERS  += mainwindow.h \
    representationpane.h \
    chartpane.h \
    logpane.h \
    graph.h
