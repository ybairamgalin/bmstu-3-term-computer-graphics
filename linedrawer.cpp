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

}

void LineDrawerBresenhamFloat::drawLine(QPainter &painter,
                                        QPointF p1, QPointF p2,
                                        QPen pen)
{

}

void LineDrawerBresenhamInt::drawLine(QPainter &painter,
                                      QPointF p1, QPointF p2,
                                      QPen pen)
{

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
