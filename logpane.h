#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

class LogPane : public QWidget
{
    Q_OBJECT
public:
    explicit LogPane(QWidget *parent = 0);
    void addLog(std::string);

signals:

public slots:
    void clearLog();

private:
    QVBoxLayout *mainLayout;
    QWidget *titleWidget;
    QHBoxLayout *titleLayout;

    QLabel *title;
    QPushButton *clearBtn;
    QTextEdit *logs;

};

#endif // TEST_H
