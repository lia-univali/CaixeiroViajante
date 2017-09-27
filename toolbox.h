#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include "representationpane.h"
#include "chartpane.h"
#include "logpane.h"

class ToolBox : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBox(QWidget *parent = 0);

    void setRepresentationPane(RepresentationPane *value);
    void setChartPane(ChartPane *value);
    void setLogPane(LogPane *value);

signals:

public slots:
    void runClicked();

private:
    RepresentationPane *representationPane;
    ChartPane *chartPane;
    LogPane *logPane;

    QHBoxLayout *mainLayout;
    QPushButton *runBtn;


};

#endif // TOOLBOX_H
