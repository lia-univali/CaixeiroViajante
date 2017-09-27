#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class ChartPane : public QWidget
{
public:
    ChartPane();
private:
    QVBoxLayout *mainLayout;
    QLabel *title;
    QWidget *chart;
};

#endif // CHART_H
