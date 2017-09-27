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

    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(5);

    setCentralWidget( mainWidget );
    mainWidget->setLayout( mainLayout );
    mainLayout->addWidget( representationPane, 1 );
    mainLayout->addWidget( rightWidget, 0 );
    rightWidget->setLayout( rightLayout );
    rightLayout->addWidget( chartPane );
    rightLayout->addWidget( logPane );

    this->setMinimumSize( 1000, 500 );
    this->setWindowTitle("Caixeiro Viajante");
}

MainWindow::~MainWindow()
{
}
