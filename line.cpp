#include "line.h"

Line::Line(QPointF point1, QPointF point2, LineDrawer drawer) :
    p1(point1), p2(point2), drawer(drawer)
{

}

void Line::setDrawer(LineDrawer drawer)
{
    this->drawer = drawer;
}

void Line::draw(QPainter &painter, QColor color)
{
    drawer.drawLine(painter, p1, p2, QPen(color));
}

