#include "graphicpane.h"

GraphicPane::GraphicPane(GraphicData *graphicData, QWidget *parent) : QWidget(parent), coordinates(graphicData)
{
    setMouseTracking(true);
}

void GraphicPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QFont font;
    font.setBold(true);
    painter.setFont(font);
    painter.drawText( 4, 14, "Representação Gráfica" );
    painter.setPen(QPen(QBrush(QColor("black")), 2.0));

    // path
//    for (Vertice &v1 : graphicData->vertices){
//        for (Edge &edge : v1.edges){
//            if ( edge.source == graphicData->getIndexOfVertice(v1.name) ){
//                Vertice &v2 = graphicData->vertices.at(edge.target);
//                painter.drawLine( QPointF( v1.x, v1.y ), QPointF( v2.x, v2.y ) );
//            }
//        }
//    }

    painter.setBrush(QBrush(QColor("black")));
    for (Coordinate &c : *coordinates){
        if ( selected != NULL ){
            if ( c.x == coordinates->at(*selected).x
              && c.y == coordinates->at(*selected).y ){
                painter.setPen(QPen(QBrush(QColor("red")), 2.0));
            } else {
                painter.setPen(QPen(QBrush(QColor("gray")), 2.0));
            }
        } else {
            painter.setPen(QPen(QBrush(QColor("gray")), 2.0));
        }
        painter.drawEllipse(QPointF( c.x, c.y ), nodeRadius, nodeRadius);
    }
    painter.setPen(QColor("black"));
}

void GraphicPane::mousePressEvent(QMouseEvent *){
    if (selected != NULL){
        moving = true;
    }
}

void GraphicPane::mouseReleaseEvent(QMouseEvent *)
{
    moving = false;
}

void GraphicPane::mouseMoveEvent(QMouseEvent *e){
    mousePos = e->localPos();
    if ( moving ){
        coordinates->at(*selected).x = e->localPos().x();
        coordinates->at(*selected).y = e->localPos().y();
    } else {
        selected = NULL;
        for (size_t i = 0; i < coordinates->size(); ++i){
            double x = coordinates->at(i).x;
            double y = coordinates->at(i).y;
            if ( std::sqrt( std::pow( x-e->localPos().x(), 2 ) + std::pow( y-e->localPos().y(), 2 ) ) <= nodeRadius ){
                if (selected != NULL){
                    delete selected;
                }
                selected = new int(i);
                break;
            }
        }
    }
    this->repaint();
}

GraphicData & GraphicPane::getGraphicData() const
{
    return *coordinates;
}

