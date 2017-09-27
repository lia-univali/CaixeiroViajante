#include "logpane.h"

LogPane::LogPane(QWidget *parent) : QWidget(parent)
{
    setMaximumWidth(400);
    setMinimumWidth(400);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    titleWidget = new QWidget;
    titleLayout = new QHBoxLayout;
    titleLayout->setMargin(0);
    titleLayout->setSpacing(0);
    titleWidget->setLayout(titleLayout);
    title = new QLabel("Log");
    title->setStyleSheet("color: black; font-weight: bold;");
    titleLayout->addWidget(title, 1);
    clearBtn = new QPushButton("Clear Log");
    titleLayout->addWidget(clearBtn, 0);

    connect( clearBtn, SIGNAL(clicked()), this, SLOT(clearLog()) );

    logs = new QTextEdit;
    logs->setStyleSheet("background-color: black; color: white;");
    QPalette palette = logs->palette();
    palette.setColor(QPalette::Highlight, QColor("white"));
    palette.setColor(QPalette::HighlightedText, QColor("black"));
    logs->setPalette(palette);
    logs->setReadOnly(true);

    mainLayout->addWidget( titleWidget, 0 );
    mainLayout->addWidget( logs, 1 );

}

void LogPane::clearLog(){
    logs->setPlainText("");
}


void LogPane::addLog(std::string str){
    str += "\n";
    logs->insertPlainText( QString::fromStdString(str) );
}

