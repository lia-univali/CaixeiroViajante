#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainLayout = new QHBoxLayout;
    rightLayout = new QVBoxLayout;
    mainWidget = new QWidget;
    rightWidget = new QWidget;

    representationPane = new RepresentationPane(&graph);
    chartPane = new ChartPane;
    logPane = new LogPane;
    toolBox = new ToolBox;

    chartScroll = new QScrollArea();
    chartScroll->setWidget(chartPane);
    chartScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chartScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    chartScroll->setFixedHeight( chartPane->height()+10 );
    chartScroll->setMinimumWidth( chartPane->width() );
    chartScroll->setWidgetResizable(true);
    chartScroll->setFrameShape(QFrame::NoFrame);
    chartScroll->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    chartPane->setScrollRightFunction( std::bind(&MainWindow::scrollChartToRight, this) );


    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(5);

    setCentralWidget( mainWidget );
    mainWidget->setLayout( mainLayout );
    mainLayout->addWidget( representationPane, 1 );
    mainLayout->addWidget( rightWidget, 0 );
    rightWidget->setLayout( rightLayout );
    rightLayout->addWidget( toolBox );
    rightLayout->addWidget( chartScroll );
    rightLayout->addWidget( logPane );

    this->setMinimumSize( 1000, 500 );
    this->setWindowTitle("Caixeiro Viajante");

    toolBox->setRepresentationPane(representationPane);
    toolBox->setChartPane(chartPane);
    toolBox->setLogPane(logPane);
}



MainWindow::~MainWindow()
{
}

void MainWindow::scrollChartToRight()
{
    chartScroll->horizontalScrollBar()->setValue( chartScroll->horizontalScrollBar()->maximum() );
}
