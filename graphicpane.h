#ifndef GRAPHPANE_H
#define GRAPHPANE_H

#include <cmath>

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

#include "graphic.h"

class GraphicPane : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicPane(GraphicData *coordinates, QWidget *parent = 0);

    GraphicData & getGraphicData() const;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    GraphicData *coordinates = NULL;
    const int nodeRadius = 15;

    QPointF mousePos;
    int *selected = NULL;
    bool moving = false;

};

#endif // GRAPHPANE_H
