#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <QWidget>
#include <QPainter>

class RepresentationPane : public QWidget
{
public:
    RepresentationPane();

protected:
    void paintEvent(QPaintEvent *) override;

};

#endif // REPRESENTATION_H
