#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <QWidget>
#include <QPainter>

#include "graph.h"

class RepresentationPane : public QWidget
{
public:
    RepresentationPane(Graph*);

protected:
    void paintEvent(QPaintEvent *) override;
private:
    Graph *graph;
};

#endif // REPRESENTATION_H
