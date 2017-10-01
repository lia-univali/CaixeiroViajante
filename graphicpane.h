#ifndef GRAPHPANE_H
#define GRAPHPANE_H

#include <cmath>
#include <map>

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#include "graphic.h"
#include "solution.h"

class GraphicPane : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicPane(GraphicData *coordinates, QWidget *parent = 0);

    GraphicData & getGraphicData() const;
    void reload();

    void setSolution(const Solution &);
    std::map<std::string, std::string> & getMetadata();

signals:

public slots:
    void callRepaint();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    bool doRepaint = true;
    int lastWidth = 0, lastHeight = 0;
    QRegion lastRegion;

    GraphicData *coordinates = NULL;
    Solution solution;
    const int nodeRadius = 2.5;

    std::map<std::string,std::string> metadata;

    QPointF mousePos;
    int *selected = NULL;
    bool moving = false;

};

#endif // GRAPHPANE_H
