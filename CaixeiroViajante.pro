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
    chartpane.cpp \
    toolbox.cpp \
    graphicpane.cpp

HEADERS  += mainwindow.h \
    chartpane.h \
    logpane.h \
    toolbox.h \
    setupalgorithms.h \
    graphicpane.h \
    coordinate.h \
    graphic.h \
    tspreader.h
