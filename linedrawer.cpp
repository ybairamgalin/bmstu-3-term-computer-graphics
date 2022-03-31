#include "linedrawer.h"

void LineDrawerLibFunc::drawLine(QPainter &painter,
                                 QPointF p1, QPointF p2,
                                 QPen pen)
{
    QPen old = painter.pen();
    painter.setPen(pen);

    painter.drawLine(p1, p2);

    painter.setPen(old);
}

void LineDrawerCda::drawLine(QPainter &painter, QPointF p1,
                             QPointF p2, QPen pen)
{
    QPen old = painter.pen();
    painter.setPen(pen);

    double xLng = std::abs(p1.x() - p2.x());
    double yLng = std::abs(p1.y() - p2.y());

    double lng = xLng > yLng ? xLng : yLng;

    double dx = (p2.x() - p1.x()) / lng;
    double dy = (p2.y() - p1.y()) / lng;

    double x = p1.x() + 0.5;

    if (dx < 0)
        x -= 1;

    double y = p1.y() + 0.5;

    if (dy < 0)
        y -= 1;

    for (int i = 0; i < lng; i++)
    {
        painter.drawPoint(x, y);
        x += dx;
        y += dy;
    }

    painter.setPen(old);
}

void LineDrawerBresenhamFloat::drawLine(QPainter &painter,
                                        QPointF p1, QPointF p2,
                                        QPen pen)
{
    QPen old = painter.pen();
    painter.setPen(pen);

    int x = p1.x();
    int y = p1.y();

    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();

    double e = (double)dy / (double)dx - 0.5;

    for (int i = 0; i < dx; i++)
    {
        painter.drawPoint(x, y);

        while (e >= 0)
        {
            y++;
            e--;
        }

        x++;
        e += (double)dy / (double)dx;
    }

    painter.setPen(old);
}

void LineDrawerBresenhamInt::drawLine(QPainter &painter,
                                      QPointF p1, QPointF p2,
                                      QPen pen)
{
    QPen old = painter.pen();
    painter.setPen(pen);

    int x = p1.x();
    int y = p1.y();

    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();

    int e = dy * 2 - dx;

    for (int i = 0; i < dx; i++)
    {
        painter.drawPoint(x, y);

        while (e >= 0)
        {
            y++;
            e -= 2 * dx;
        }

        x++;
        e += 2 * dy;
    }

    painter.setPen(old);
}

void LineDrawerBresenhamSmooth::drawLine(QPainter &painter,
                                         QPointF p1, QPointF p2,
                                         QPen pen)
{

}

void LineDrawerWu::drawLine(QPainter &painter,
                            QPointF p1, QPointF p2,
                            QPen pen)
{

}
