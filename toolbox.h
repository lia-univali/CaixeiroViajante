#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <functional>
#include <thread>

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFileDialog>

#include "graphicpane.h"
#include "chartpane.h"
#include "logpane.h"
#include "graphic.h"

class ToolBox : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBox(QWidget *parent = 0);

    void setGraphicPane(GraphicPane *value);
    void setChartPane(ChartPane *value);
    void setLogPane(LogPane *value);

    struct AlgorithmData {
        std::string name;
        std::function<
            void(
                GraphicData&,
                int,                              // initial node
                std::function<void(std::string)>, // log
                std::function<void(double)>,      // chart data
                std::function<bool()>,            // if stop requested
                std::function<void()>             // on finish
            )
        > run;
    };

signals:

public slots:
    void loadInstance();
    void stopClicked();
    void runClicked();
    void appendStep(double);
    void appendLog(QString);

private:
    GraphicPane *graphicPane;
    ChartPane *chartPane;
    LogPane *logPane;

    QHBoxLayout *mainLayout;
    QPushButton *loadBtn;
    QComboBox *algorithmsBox;
    QPushButton *stopBtn;
    QPushButton *runBtn;

    std::vector<AlgorithmData> algorithms;

    std::thread *proccess = NULL;

    void startThread();

    bool stopRequested = false;
    bool running = false;

};


#endif // TOOLBOX_H
