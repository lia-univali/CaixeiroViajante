#include "graphicpane.h"

GraphicPane::GraphicPane(GraphicData *graphicData, QWidget *parent) : QWidget(parent), coordinates(graphicData)
{
    setMouseTracking(true);
    setAutoFillBackground(false);
    QTimer *fpsTimer = new QTimer();
    QObject::connect(fpsTimer, SIGNAL(timeout()), this, SLOT(callRepaint()));
    fpsTimer->start( 100 );
}

void GraphicPane::callRepaint(){
    this->update();
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

    painter.save();
    painter.setPen(QPen( QBrush(Qt::black), 1.0 ));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRoundedRect( QRectF( 0, 0, width(), height() ), 4, 4 );
    painter.restore();

    QFont boldFont;
    QFont plainFont;
    boldFont.setBold(true);

    QFontMetrics fmBold (boldFont);
    QFontMetrics fmPlain(plainFont);

    painter.setFont(boldFont);
    QString title("Representação Gráfica");
    qreal marginText = 14;
    painter.drawText( QPointF(4,marginText), title );

    // metadata
    double accPos = 8 + fmBold.width(title);
    for (const auto &data : metadata){
        accPos += 10;
        QString key   = QString::fromStdString( data.first+": " );
        QString value = QString::fromStdString( data.second );

        painter.setFont( boldFont );
        painter.drawText( QPointF( accPos, marginText ), key );
        accPos += fmBold .width( key );

        painter.setFont( plainFont );
        painter.drawText( QPointF( accPos, marginText ), value );
        accPos += fmPlain.width( value );
    }

    if ( coordinates->size() > 0 ){
        double minX = 0, maxX = 0;
        double minY = 0, maxY = 0;
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

        double offsetX = 10 + (W-scale*(maxX-minX)) / 2.0;
        double offsetY = -30 + (H-scale*(maxY-minY)) / 2.0;

        auto toX = [&](double x) -> double {
            return (x-minX) * scale + offsetX;
        };
        auto toY = [&](double y) -> double {
            return H - (y-minY) * scale - offsetY;
        };

        painter.save();
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
                painter.drawEllipse(
                    QPointF( toX(curr.x), toY(curr.y) ),
                    nodeRadius + .5, nodeRadius + 0.5
                );
                prev = curr;
            }
        }
        painter.restore();

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

void GraphicPane::mouseMoveEvent(QMouseEvent *){
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

std::map<std::string, std::string> & GraphicPane::getMetadata()
{
    return metadata;
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

