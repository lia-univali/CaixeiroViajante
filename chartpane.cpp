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

