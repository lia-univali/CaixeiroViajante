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

#include "graphicpane.h"
#include "chartpane.h"
#include "logpane.h"
#include "toolbox.h"

#include "graphic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();

protected:
    void keyReleaseEvent(QKeyEvent *) override;

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QWidget *mainWidget;
    QWidget *rightWidget;

    GraphicPane *graphPane;
    ChartPane *chartPane;
    LogPane *logPane;
    ToolBox *toolBox;

    QLabel *chartTitle;
    QScrollArea *chartScroll;

    GraphicData graphicData;

};

#endif // MAINWINDOW_H
