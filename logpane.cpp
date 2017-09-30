#include "logpane.h"

LogPane::LogPane(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(450);

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
    clearBtn = new QPushButton("Limpar Log");
    titleLayout->addWidget(clearBtn, 0);

    connect( clearBtn, SIGNAL(clicked()), this, SLOT(clearLog()) );

    logs = new QTextEdit;
    logs->setStyleSheet("font-family: \"Anonymous Pro 11\"; background-color: black; color: white;");
    QPalette palette = logs->palette();
    palette.setColor(QPalette::Highlight, QColor("white"));
    palette.setColor(QPalette::HighlightedText, QColor("black"));
    logs->setPalette(palette);
    logs->setTextInteractionFlags(Qt::NoTextInteraction);

    mainLayout->addWidget( titleWidget, 0 );
    mainLayout->addWidget( logs, 1 );

}

void LogPane::clearLog(){
    logs->setPlainText("");
}

void LogPane::addLog(std::string str){
    QScrollBar *sb = logs->verticalScrollBar();
    bool change = ( sb->value() == sb->maximum() );
    str += "\n";
    logs->insertPlainText( QString::fromStdString(str) );
    if (change){
        sb->setValue( sb->maximum() );
    }
//    QTextCursor textCursor = logs->textCursor();
//    textCursor.movePosition(QTextCursor::End);
//    logs->setTextCursor(textCursor);
}

