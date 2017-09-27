#include "representationpane.h"

RepresentationPane::RepresentationPane(Graph *graph) : graph(graph)
{
}

void RepresentationPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect( 10, 30, 30, 30, Qt::SolidPattern);

    QFont font;
    font.setBold(true);
    painter.setFont(font);
    painter.drawText( 4, 14, "Representação Gráfica" );

    painter.drawRoundedRect( 0, 0, width()-1, height()-1, 1, 1 );
}

