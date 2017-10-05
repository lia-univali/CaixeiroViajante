#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollBar>

class LogPane : public QWidget
{
    Q_OBJECT
public:
    explicit LogPane(QWidget *parent = 0);
    void addLog(std::string);
    void setIterations(QString);

signals:

public slots:
    void clearLog();

private:
    QVBoxLayout *mainLayout;
    QWidget *titleWidget;
    QHBoxLayout *titleLayout;

    QLabel *title;
    QLabel *iterations;
    QPushButton *clearBtn;
    QTextEdit *logs;

};

#endif // TEST_H
