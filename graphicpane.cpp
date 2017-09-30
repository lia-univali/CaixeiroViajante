#include "graphicpane.h"

GraphicPane::GraphicPane(GraphicData *graphicData, QWidget *parent) : QWidget(parent), coordinates(graphicData)
{
    setMouseTracking(true);
    setAutoFillBackground(false);
    QTimer *fpsTimer = new QTimer();
    QObject::connect(fpsTimer, SIGNAL(timeout()), this, SLOT(callRepaint()));
    fpsTimer->start( 50 );
}

void GraphicPane::callRepaint(){
    this->repaint();
}

void GraphicPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

//    if ( lastWidth == width() && lastHeight == height() && !doRepaint ){
////        painter.drawRe
//        return;
//    }
//    lastWidth  = width();
//    lastHeight = height();
//    doRepaint = false;

    QFont font;
    font.setBold(true);
    painter.setFont(font);
    painter.drawText( 4, 14, "Representação Gráfica" );

    if ( coordinates->size() > 0 ){
        double minX, maxX;
        double minY, maxY;
        bool first = true;
        for (Coordinate &c : *coordinates){
            if ( c.x < minX || first ) minX = c.x;
            if ( c.x > maxX || first ) maxX = c.x;
            if ( c.y < minY || first ) minY = c.y;
            if ( c.y > maxY || first ) maxY = c.y;
            first = false;
        }

        double W = width() - 20;
        double H = height() - 40;

        double scaleX = W / (maxX-minX);
        double scaleY = H / (maxY-minY);

        double scale = std::min( scaleX, scaleY );

        double offsetX = -10 + (W-scale*(maxX-minX)) / 2.0;
        double offsetY = -30 + (H-scale*(maxY-minY)) / 2.0;

        auto toX = [&](double x) -> double {
            return W - (x-minX) * scale - offsetX;
        };
        auto toY = [&](double y) -> double {
            return H - (y-minY) * scale - offsetY;
        };

//        for (Vertice &v1 : graphicData->vertices){
//            for (Edge &edge : v1.edges){
//                if ( edge.source == graphicData->getIndexOfVertice(v1.name) ){
//                    Vertice &v2 = graphicData->vertices.at(edge.target);
//                    painter.drawLine( QPointF( v1.x, v1.y ), QPointF( v2.x, v2.y ) );
//                }
//            }
//        }


        // path
        if ( solution.path.size() >= 2 ) {
            painter.setPen(QPen(QBrush(QColor(255,0,0,100)), 1.5));
            Coordinate prev = coordinates->at(solution.path.back());
            for (int i : solution.path){
                Coordinate curr = coordinates->at(i);
                painter.drawLine(
                    QPointF( toX(prev.x), toY(prev.y) ),
                    QPointF( toX(curr.x), toY(curr.y) )
                );
                prev = curr;
            }
        }

        // all points
        painter.setBrush(QBrush(QColor(0,120,0)));
        for (Coordinate &c : *coordinates){
            double x = toX( c.x );
            double y = toY( c.y );
//            if ( selected != NULL ){
//                if ( c.x == coordinates->at(*selected).x
//                  && c.y == coordinates->at(*selected).y ){
//                    painter.setPen(QPen(QBrush(QColor("red")), 2.0));
//                } else {
//                    painter.setPen(QPen(QBrush(QColor("gray")), 2.0));
//                }
//            } else {
//                painter.setPen(QPen(QBrush(QColor("gray")), 2.0));
//            }
            painter.drawEllipse(QPointF( x, y ), nodeRadius, nodeRadius);
        }
    }

    painter.setPen(QColor("black"));

//    lastRegion = painter.clipRegion();
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
//    mousePos = e->localPos();
//    if ( moving ){
//        coordinates->at(*selected).x = e->localPos().x();
//        coordinates->at(*selected).y = e->localPos().y();
//    } else {
//        selected = NULL;
//        for (size_t i = 0; i < coordinates->size(); ++i){
//            double x = coordinates->at(i).x;
//            double y = coordinates->at(i).y;
//            if ( std::sqrt( std::pow( x-e->localPos().x(), 2 ) + std::pow( y-e->localPos().y(), 2 ) ) <= nodeRadius ){
//                if (selected != NULL){
//                    delete selected;
//                }
//                selected = new int(i);
//                break;
//            }
//        }
//    }
//    this->repaint();
}

void GraphicPane::setSolution(const Solution &s)
{
    this->solution = s;
}

GraphicData & GraphicPane::getGraphicData() const
{
    return *coordinates;
}

void GraphicPane::reload()
{
    doRepaint = true;
    this->repaint();
}

