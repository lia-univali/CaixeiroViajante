#include "toolbox.h"

#include "setupalgorithms.h"
#include "tspreader.h"

ToolBox::ToolBox(GraphicData *graphicData, QWidget *parent) : QWidget(parent), graphicData(graphicData)
{
    setupAlgorithms(algorithms);

    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    loadBtn       = new QPushButton("Carregar");
    algorithmsBox = new QComboBox;
    runBtn        = new QPushButton("Rodar");
    mainLayout->addWidget(loadBtn);
    mainLayout->addWidget(algorithmsBox);
    mainLayout->addWidget(runBtn);

    connect( loadBtn, SIGNAL(clicked(bool)), this, SLOT(loadInstance()) );
    connect( runBtn,  SIGNAL(clicked(bool)), this, SLOT(runClicked  ()) );

    for (const AlgorithmData &alg : algorithms){
        algorithmsBox->addItem(QString::fromStdString( alg.name ));
    }
}

void ToolBox::loadInstance()
{
    std::string file = QFileDialog::getOpenFileName(
        this,
        tr("Selecione uma instância"),
        "instances",
        tr("Arquivo tsp (*.tsp)")
    ).toStdString();
    graphicData->clear();
    std::vector<Coordinate> tspInstance = getTspInstance( file );
    printf("Copyied\n");
    std::copy( tspInstance.begin(), tspInstance.end(), graphicData->begin() );
    graphicPane->repaint();
}

void ToolBox::runClicked(){
    if (!running){
        running = true;
        stopRequested = false;
        this->logPane->clearLog();
        this->chartPane->clearChart();
        proccess = new std::thread( &ToolBox::startThread, this );
    }
}

void ToolBox::appendStep(double value){
    this->chartPane->addStep( value );
}

void ToolBox::appendLog(QString log){
    this->logPane->addLog( log.toStdString() );
}

void ToolBox::startThread()
{
    algorithms.at( algorithmsBox->currentIndex() ).run(

        // graphic Data
        graphicPane->getGraphicData(),

        // initial node
        0,

        // log
        [this](std::string log) -> void {
            QMetaObject::invokeMethod(
                this, "appendLog",
                Qt::QueuedConnection,
                Q_ARG( QString, QString::fromStdString(log) )
            );
        },

        // chart data
        [this](double value) -> void {
            QMetaObject::invokeMethod(
                this,
                "appendStep",
                Qt::QueuedConnection,
                Q_ARG( double, value )
            );
        },

        // stop requested
        [this]() -> bool {
            return stopRequested;
        },

        // finished
        [this]() -> void { this->running = false; }
    );
}

void ToolBox::setLogPane(LogPane *value)
{
    logPane = value;
}

void ToolBox::setChartPane(ChartPane *value)
{
    chartPane = value;
}

void ToolBox::setGraphicPane(GraphicPane *value)
{
    graphicPane = value;
}

