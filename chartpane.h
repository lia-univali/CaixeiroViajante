#ifndef CHART_H
#define CHART_H

#include <list>
#include <cmath>
#include <functional>

#include <QWidget>
#include <QPainter>
#include <QScrollArea>

class ChartPane : public QWidget
{
public:
    ChartPane();
    void clearChart();
    void addStep(double step);
    void setScrollRightFunction(const std::function<void()> &value);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    std::function<void()> scrollRightFunction;
    std::list<double> steps;

    const double stepDistance = 5;

};

#endif // CHART_H
