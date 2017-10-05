#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::setlocale(LC_ALL, "C" );
    w.start();

    return a.exec();
}
