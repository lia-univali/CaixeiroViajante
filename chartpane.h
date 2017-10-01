#ifndef CHART_H
#define CHART_H

#include <list>
#include <cmath>
#include <functional>

#include <QWidget>
#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QLinearGradient>

class ChartPane : public QWidget
{
    Q_OBJECT
public:
    explicit ChartPane(QScrollArea*, QWidget *parent = 0);
    void clearChart();
    void addStep(double step);

signals:

public slots:
    void callRepaint();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QScrollArea *scrollArea;

    std::function<void(int)> resizeFunction;
    std::list<double> steps;

    const double lineWidth = 1.5;
    const double pointRadius = 2.0;
    const double stepDistance = 8.5;

    int count = 0;
};

#endif // CHART_H
