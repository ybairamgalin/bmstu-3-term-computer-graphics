#include "line.h"

QPoint Line::_delta = QPoint(0, 0);
double Line::_scaleFactor = 1;

Line::Line(QPointF point1, QPointF point2, LineDrawer *drawer) :
    p1(point1), p2(point2), drawer(drawer)
{
}

void Line::setDrawer(LineDrawer *drawer)
{
    if (this->drawer)
        delete this->drawer;

    this->drawer = drawer;
}

void Line::draw(QPainter &painter, QColor color)
{
    drawer->drawLine(painter, p1, p2, QPen(color));
}

void Line::setDelta(QPoint delta)
{
    _delta = delta;
}

void Line::setScale(double scaleFactor)
{
    _scaleFactor = scaleFactor;
}
