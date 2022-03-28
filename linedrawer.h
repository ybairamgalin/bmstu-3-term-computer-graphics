#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include <QPainter>

// strategy pattern

class LineDrawer
{
public:
    virtual ~LineDrawer();

    virtual void drawLine(QPainter &painter, QPointF p1,
                          QPointF p2, QPen pen);
};

class LineDrawerLibFunc : public LineDrawer
{
public:
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen);
};

class LineDrawerCda : public LineDrawer
{
public:
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen);
};

class LineDrawerBresenhamFloat : public LineDrawer
{
public:
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen);
};

class LineDrawerBresenhamInt : public LineDrawer
{
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen);
};

class LineDrawerBresenhamSmooth : public LineDrawer
{
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen);
};

class LineDrawerWu : public LineDrawer
{
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen);
};

#endif // LINEDRAWER_H
