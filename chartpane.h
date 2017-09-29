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
    Q_OBJECT
public:
    explicit ChartPane(QWidget *parent = 0);
    void clearChart();
    void addStep(double step);
    void setScrollRightFunction(const std::function<void(int)> &value);

signals:

public slots:
    void callRepaint();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    std::function<void(int)> resizeFunction;
    std::list<double> steps;

    const double lineWidth = 1.5;
    const double pointRadius = 2.0;
    const double stepDistance = 8.5;
};

#endif // CHART_H
