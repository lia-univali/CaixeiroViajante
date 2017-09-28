#include "toolbox.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    runBtn = new QPushButton("Rodar");
    mainLayout->addWidget(runBtn);

    connect( runBtn, SIGNAL(clicked(bool)), this, SLOT(runClicked()) );

}



void ToolBox::runClicked()
{
    this->logPane->clearLog();
//    this->chartPane->clearChart();

    this->chartPane->addStep( 1 );
    this->chartPane->addStep( 1.5 );
    this->chartPane->addStep( 2 );
    this->chartPane->addStep( 3 );
    this->chartPane->addStep( 4 );
    this->chartPane->addStep( 5 );
    this->chartPane->addStep( 3 );
    this->chartPane->addStep( 2 );
    this->chartPane->addStep( 1.4 );
    this->chartPane->addStep( 0.2 );
    this->chartPane->addStep( 0.1 );
    this->chartPane->addStep( 0.00001 );
    this->chartPane->addStep( 10 );
    this->chartPane->addStep( 1 );
    this->chartPane->addStep( 1.5 );
    this->chartPane->addStep( 2 );
    this->chartPane->addStep( 3 );
    this->chartPane->addStep( 4 );
    this->chartPane->addStep( 5 );
    this->chartPane->addStep( 3 );
    this->chartPane->addStep( 2 );
    this->chartPane->addStep( 1.4 );
    this->chartPane->addStep( 0.2 );
    this->chartPane->addStep( 0.1 );
    this->chartPane->addStep( 0.00001 );
    this->chartPane->addStep( -1 );
    this->chartPane->addStep( 1 );
    this->chartPane->addStep( 1.5 );
    this->chartPane->addStep( 2 );
    this->chartPane->addStep( 3 );
    this->chartPane->addStep( 4 );
    this->chartPane->addStep( 5 );
    this->chartPane->addStep( 3 );
    this->chartPane->addStep( 2 );
    this->chartPane->addStep( 1.4 );
    this->chartPane->addStep( 0.2 );
    this->chartPane->addStep( 0.1 );
    this->chartPane->addStep( 0.00001 );
    this->chartPane->addStep( -1 );
    this->chartPane->addStep( 0.2 );
    this->chartPane->addStep( 0.1 );
    this->chartPane->addStep( 0.00001 );
    this->chartPane->addStep( -1 );
    this->chartPane->addStep( -4 );
    this->chartPane->addStep( -5 );
    this->chartPane->addStep( -7 );
    this->chartPane->addStep( -8 );
    this->chartPane->addStep( -10 );
    this->chartPane->addStep( -20 );
    this->chartPane->addStep( -40 );
    this->chartPane->addStep( -80 );
}

void ToolBox::setLogPane(LogPane *value)
{
    logPane = value;
}

void ToolBox::setChartPane(ChartPane *value)
{
    chartPane = value;
}

void ToolBox::setRepresentationPane(RepresentationPane *value)
{
    representationPane = value;
}

