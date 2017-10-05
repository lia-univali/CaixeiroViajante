#include "toolbox.h"

#include "resolution/setupalgorithms.h"
#include "resolution/tspreader.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent)
{
    qRegisterMetaType<Solution>("Solution");

    setupAlgorithms(algorithms);

    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    loadBtn       = new QPushButton("Carregar");
    algorithmsBox = new QComboBox;
    stopBtn       = new QPushButton("Parar");
    runBtn        = new QPushButton("Rodar");
    mainLayout->addWidget(loadBtn);
    mainLayout->addWidget(algorithmsBox);
    mainLayout->addWidget(stopBtn);
    mainLayout->addWidget(runBtn);

    stopBtn->setEnabled(false);

    connect( loadBtn, SIGNAL(clicked(bool)), this, SLOT(loadInstance()) );
    connect( stopBtn, SIGNAL(clicked(bool)), this, SLOT(stopClicked ()) );
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
    if (file.empty()){
        return;
    }
    graphicPane->getGraphicData().clear();
    Solution empty;
    empty.path.clear();
    graphicPane->setSolution(empty);
    std::vector<Coordinate> tspInstance = getTspInstance( file, graphicPane->getMetadata() );
    std::copy( tspInstance.begin(), tspInstance.end(), std::back_inserter(graphicPane->getGraphicData()) );
    graphicPane->reload();
}

void ToolBox::stopClicked(){
    if (running){
        stopBtn->setEnabled(false);
        stopRequested = true;
    }
}

void ToolBox::runClicked(){
    if (!running){
        runBtn->setEnabled(false);
        stopBtn->setEnabled(true);
        running = true;
        stopRequested = false;
        this->logPane->clearLog();
        this->chartPane->clearChart();
        proccess = new std::thread( &ToolBox::startThread, this );
    }
}

void ToolBox::clearChart(){
    this->chartPane->clearChart();
}
void ToolBox::appendStep(double value){
    this->chartPane->addStep( value );
}
void ToolBox::appendLog(QString log){
    this->logPane->addLog( log.toStdString() );
}
void ToolBox::logIterations(QString str){
    this->logPane->setIterations( str );
}
void ToolBox::setSolution(const Solution &s){
    this->graphicPane->setSolution(s);
}

void ToolBox::startThread()
{
//    auto last = std::chrono::system_clock::now();
    algorithms.at( algorithmsBox->currentIndex() ).run(

        // graphic Data
        graphicPane->getGraphicData(),

        // initial node
        rand() % graphicPane->getGraphicData().size(),

        // set solution
        [this](const Solution &s) -> void {
            QMetaObject::invokeMethod(
                this, "setSolution",
                Qt::QueuedConnection,
                Q_ARG( Solution, s )
            );
        },

        // log
        [this](std::string log) -> void {
            QMetaObject::invokeMethod(
                this, "appendLog",
                Qt::QueuedConnection,
                Q_ARG( QString, QString::fromStdString(log) )
            );
        },

        // log chart data
        [this/*,&last*/](double value) -> void {
            QMetaObject::invokeMethod(
                this,
                "appendStep",
                Qt::QueuedConnection,
                Q_ARG( double, value )
            );
//            auto now = std::chrono::system_clock::now();
//            if ( now-last < std::chrono::milliseconds(1) ){
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//            last = std::chrono::system_clock::now();
        },

        // log iterations
        [this](std::string str) -> void {
            QMetaObject::invokeMethod(
                this, "logIterations",
                Qt::QueuedConnection,
                Q_ARG( QString, QString::fromStdString(str) )
            );
        },

        // clear chart
        [this]() -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            QMetaObject::invokeMethod(
                this, "clearChart",
                Qt::QueuedConnection
            );
        },

        // stop requested
        [this]() -> bool {
            return stopRequested;
        },

        // finished
        [this]() -> void {
            this->running = false;
            runBtn->setEnabled(true);
            stopBtn->setEnabled(false);
        }
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

