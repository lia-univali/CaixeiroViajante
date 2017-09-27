#include "chartpane.h"

ChartPane::ChartPane()
{
    setMinimumHeight(250);
    setMaximumHeight(250);
    setMaximumWidth(400);
    setMinimumWidth(400);

    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    title = new QLabel("Evolução");
    title->setStyleSheet("color: black; font-weight: bold;");


    chart = new QWidget;

    mainLayout->addWidget( title, 0 );
    mainLayout->addWidget( chart, 1 );
}

void ChartPane::clearChart(){
    steps.clear();
    this->repaint();
}

void ChartPane::addStep(double step){
    steps.push_back(step);
    this->repaint();
}



void ChartPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor("white")));
    painter.fillRect( 0, 30, width()-1, height()-31, Qt::SolidPattern );
    painter.setPen(QColor("black"));
    painter.drawRect( 0, 30, width()-1, height()-31 );

    if ( steps.size() >= 2 ){

    }
}






























