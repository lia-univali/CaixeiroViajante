#ifndef CHART_H
#define CHART_H

#include <list>
#include <cmath>
#include <functional>

#include <QWidget>
#include <QPainter>
#include <QScrollArea>
#include <QTimer>
#include <QLinearGradient>

class ChartPane : public QWidget
{
public:
    ChartPane();
    void clearChart();
    void addStep(double step);
    void setScrollRightFunction(const std::function<void()> &value);

public slots:
    void update();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    std::function<void()> scrollRightFunction;
    std::list<double> steps;

    const double lineWidth = 1.5;
    const double pointRadius = 2.5;
    const double stepDistance = 7.0;
};

#endif // CHART_H
