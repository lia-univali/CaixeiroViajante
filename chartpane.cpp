#include "chartpane.h"

ChartPane::ChartPane()
{
    setFixedHeight(220);
    setFixedWidth(400);
}

void ChartPane::clearChart(){
    steps.clear();
}

void ChartPane::addStep(double step){
    steps.push_back(step);
    scrollRightFunction();
    this->repaint();

}


void ChartPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // white background
    painter.setBrush(QBrush(QColor("white")));
    painter.fillRect( 0, 0, width()-1, height()-1, Qt::SolidPattern );

    // fill
    painter.setBrush(Qt::NoBrush);
    QRect background( 0,0, width(),height() );
    QLinearGradient gradient( background.topLeft(), background.bottomLeft() );
    gradient.setColorAt(0.0, QColor(255,120,120));
    gradient.setColorAt(0.5, QColor(210,210,100));
    gradient.setColorAt(1.0, QColor(120,255,120));
    painter.fillRect(background, gradient);

    // border
    painter.setPen(QColor("black"));
    painter.drawRect( 0, 0, width()-1, height()-1 );

    painter.setRenderHint(QPainter::Antialiasing);

    this->setFixedWidth(std::max(400, (int) (20 + steps.size() * stepDistance) ));

    if ( steps.size() >= 2 ){

        double max, min; ///
        { // found max and min values
            bool first = true;
            for (const double &step : steps){
                if ( first ){
                    max = step;
                    min = step;
                    first = false;
                } else {
                    if ( step > max ){
                        max = step;
                    }
                    if ( step < min ){
                        min = step;
                    }
                }
            }
        }
        double scale = ((double) height()*0.8) / (max-min);
        double offset = height() * 0.1;
        double x = 10;

        // 0
        painter.setPen( QPen(QBrush(QColor("gray")),2.0) );
        painter.drawLine(
            QPoint( 0,       height() - ((-min) * scale) - offset ),
            QPoint( width(), height() - ((-min) * scale) - offset )
        );

        // max
        painter.setPen( QPen(QBrush(QColor("red")),1.5) );
        painter.drawLine(
            QPointF( 0,         height() - ((max-min) * scale) - offset ),
            QPointF( width()-1, height() - ((max-min) * scale) - offset)
        );
        // min
        painter.setPen( QPen(QBrush(QColor("green")),1.5) );
        painter.drawLine(
            QPointF( 0,         height() - offset ),
            QPointF( width()-1, height() - offset)
        );

        // steps
        painter.setPen( QPen(QBrush(QColor("black")), lineWidth) );

        bool first = true;
        double prevX, prevY;
        for (const double &step : steps){
            double y = ( height() - ((step-min) * scale) ) - offset;
            painter.setBrush(QBrush(QColor("black")));
//            painter.drawText( QPointF( x-5, y-5 ), QString::fromStdString(std::to_string((int) step)) );
            painter.drawEllipse( QPointF(x,y), pointRadius, pointRadius );
            if ( first ){
                prevX = x;
                prevY = y;
                first = false;
            } else {
                painter.drawLine( QPointF( prevX, prevY ), QPointF( x, y ) );
                prevX = x;
                prevY = y;
            }
            x += stepDistance;
        }
    }
}

void ChartPane::setScrollRightFunction(const std::function<void()> &value)
{
    scrollRightFunction = value;
}
