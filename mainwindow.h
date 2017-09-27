#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "representationpane.h"
#include "chartpane.h"
#include "logpane.h"

#include "graph.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QWidget *mainWidget;
    QWidget *rightWidget;

    RepresentationPane *representationPane;
    ChartPane *chartPane;
    LogPane *logPane;


    Graph graph;

};

#endif // MAINWINDOW_H
