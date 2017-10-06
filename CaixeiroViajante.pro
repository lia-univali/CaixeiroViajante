#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T10:57:42
#
#-------------------------------------------------

QT       += core gui
CONFIG   += console c++11
CONFIG   += bundle
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CaixeiroViajante
TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += main.cpp\
    mainwindow.cpp \
    logpane.cpp \
    toolbox.cpp \
    graphicpane.cpp \
    chartpane.cpp \
    resolution/solution.cpp

HEADERS  += mainwindow.h \
    logpane.h \
    toolbox.h \
    graphicpane.h \
    graphic.h \
    chartpane.h \
    resolution/methods/bruteforce.h \
    resolution/methods/guidedsearch.h \
    resolution/methods/iteratedSearch.h \
    resolution/methods/minimumLocalRoute.h \
    resolution/setupalgorithms.h \
    resolution/solution.h \
    resolution/tspreader.h \
    resolution/methods/tabu.h
