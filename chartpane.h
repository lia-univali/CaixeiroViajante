#ifndef CHART_H
#define CHART_H

#include <list>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QScrollArea>

class ChartPane : public QWidget
{
public:
    ChartPane();
    void clearChart();
    void addStep(double step);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QVBoxLayout *mainLayout;
    QLabel *title;
    QWidget *chart;

    std::list<double> steps;

};

#endif // CHART_H
