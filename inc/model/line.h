#ifndef LINE_H
#define LINE_H

#include <QPainter>
#include <QPointF>

#include "linedrawer.h"

class Line
{
private:
    static QPoint _delta;
    static double _scaleFactor;

    QPointF p1;
    QPointF p2;
    LineDrawer *drawer;
public:
    Line(QPointF p1, QPointF p2, LineDrawer *drawer);

    static void setDelta(QPoint delta);
    static void setScale(double scaleFactor);

    void setDrawer(LineDrawer *drawer);
    void draw(QPainter &painter, QColor color);
};

#endif // LINE_H
