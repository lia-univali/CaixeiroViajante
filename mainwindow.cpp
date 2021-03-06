#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mainLayout = new QHBoxLayout;
    rightLayout = new QVBoxLayout;
    mainWidget = new QWidget;
    rightWidget = new QWidget;

    chartScroll = new QScrollArea();
    graphPane = new GraphicPane(&graphicData);
    chartPane = new ChartPane(chartScroll);
    logPane = new LogPane;
    toolBox = new ToolBox;

    chartTitle = new QLabel("Evolução");
    {
        QFont font = chartTitle->font();
        font.setBold(true);
        chartTitle->setFont(font);
        chartTitle->setStyleSheet("color: black");
    }

    chartScroll->setWidget(chartPane);
    chartScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chartScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    chartScroll->setFixedHeight( chartPane->height()+10 );
    chartScroll->setMinimumWidth( chartPane->width() );
    chartScroll->setWidgetResizable(true);
    chartScroll->setFrameShape(QFrame::NoFrame);
    chartScroll->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(5);

    setCentralWidget( mainWidget );
    mainWidget->setLayout( mainLayout );
    mainLayout->addWidget( graphPane, 1 );
    mainLayout->addWidget( rightWidget, 0 );
    rightWidget->setLayout( rightLayout );
    rightLayout->addWidget( toolBox );
    rightLayout->addWidget( chartTitle );
    rightLayout->addWidget( chartScroll );
    rightLayout->addWidget( logPane );

    this->setMinimumSize( 1000, 500 );
    this->setWindowTitle("Caixeiro Viajante");

    toolBox->setGraphicPane(graphPane);
    toolBox->setChartPane(chartPane);
    toolBox->setLogPane(logPane);
}

void MainWindow::start(){
    this->show();
}

MainWindow::~MainWindow()
{}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if ( e->key() == Qt::Key_F11 ){
        this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    }
}
