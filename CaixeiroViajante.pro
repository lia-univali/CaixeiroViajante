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
    toolbox.cpp \
    graphicpane.cpp \
    solution.cpp \
    chartpane.cpp

HEADERS  += mainwindow.h \
    logpane.h \
    toolbox.h \
    setupalgorithms.h \
    graphicpane.h \
    graphic.h \
    tspreader.h \
    solution.h \
    bruteforce.h \
    minimumLocalRoute.h \
    iteratedSearch.h \
    chartpane.h
