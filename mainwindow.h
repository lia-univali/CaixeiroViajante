#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>

#include "representationpane.h"
#include "chartpane.h"
#include "logpane.h"
#include "toolbox.h"

#include "graph.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void scrollChartToRight();

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QWidget *mainWidget;
    QWidget *rightWidget;

    RepresentationPane *representationPane;
    ChartPane *chartPane;
    LogPane *logPane;
    ToolBox *toolBox;

    QScrollArea *chartScroll;


    Graph graph;

};

#endif // MAINWINDOW_H
