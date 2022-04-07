#include "linedrawer.h"

// algs taken from
// Mathematical Elements for Computer Graphics, Davif F. Rogers
// https://ru.wikipedia.org/wiki/Алгоритм_Ву

int LineDrawerBresenhamSmooth::sign(const int x)
{
    if (x > 0)
        return 1;

    if (x < 0)
        return -1;

    return 0;
}

int LineDrawerWu::mapOpacity(const double x)
{
    int opacity = (int)(x * 255);

    return opacity;
}

void LineDrawerWu::setOpacity(QPainter &painter, int opacity)
{
    QPen pen = painter.pen();
    QColor color = pen.color();
    color.setAlpha(opacity);
    pen.setColor(color);
    painter.setPen(pen);
}

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
    QPen old = painter.pen();
    painter.setPen(pen);

    int x = p1.x();
    int y = p1.y();

    int dx = std::abs(p2.x() - p1.x());
    int dy = std::abs(p2.y() - p1.y());

    int s1 = sign(p2.x() - p1.x());
    int s2 = sign(p2.y() - p1.y());

    int exchange = 0;

    if (dy > dx)
    {
        int tmp = dx;
        dx = dy;
        dy = tmp;
        exchange = 1;
    }

    int error = 2 * dy - dx;

    for (int i = 1; i <= dx; i++)
    {
        painter.drawPoint(x, y);

        while (error >= 0)
        {
            if (exchange)
                x += s1;
            else
                y += s2;

            error -= 2 * dx;
        }

        if (exchange)
            y += s2;
        else
            x += s1;

        error += 2 * dy;
    }

    painter.setPen(old);
}

void LineDrawerWu::drawLine(QPainter &painter,
                            QPointF p1, QPointF p2,
                            QPen pen)
{
    double part;

    QPen old = painter.pen();
    painter.setPen(pen);

    double x1 = p1.x(), x2 = p2.x();
    double y1 = p1.y(), y2 = p2.y();

    if (p1.x() > p2.x())
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    double dx = x2 - x1;
    double dy = y2 - y1;
    double gradient = dy / dx;

    double xend = std::round(x1);
    double yend = y1 + gradient * (xend - x1);

    double xgap = 1 - std::modf(x1 + 0.5, &part);
    double xpxl1 = xend;
    double ypxl1 = (int)yend;

    setOpacity(painter, mapOpacity((1 - std::modf(yend, &part) * xgap)));
    painter.drawPoint(xpxl1, ypxl1);
    setOpacity(painter, mapOpacity(std::modf(yend, &part) * xgap));
    painter.drawPoint(xpxl1, ypxl1 + 1);

    double intery = yend + gradient;

    xend = std::round(x2);
    yend = y2 + gradient * (xend - x2);

    xgap = std::modf(x2 + 0.5, &part);
    double xpxl2 = xend;
    double ypxl2 = int(yend);

    setOpacity(painter, mapOpacity((1 - std::modf(yend, &part) * xgap)));
    painter.drawPoint(xpxl2, ypxl2);
    setOpacity(painter, mapOpacity(std::modf(yend, &part) * xgap));
    painter.drawPoint(xpxl2, ypxl2 + 1);

    for (int x = xpxl1 + 1; x < xpxl2; x++)
    {
        setOpacity(painter, mapOpacity(1 - std::modf(intery, &part)));
        painter.drawPoint(x, int(intery));
        setOpacity(painter, mapOpacity(std::modf(intery, &part)));
        painter.drawPoint(x, int(intery) + 1);

        intery += gradient;
    }

    painter.setPen(old);
}
