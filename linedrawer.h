#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include <QPainter>
#include <QDebug>

// strategy pattern

class LineDrawer
{
public:
    virtual ~LineDrawer() { };
    virtual void drawLine(QPainter &painter, QPointF p1,
                          QPointF p2, QPen pen) = 0;
};

class LineDrawerLibFunc : public LineDrawer
{
public:
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen) override;
};

class LineDrawerCda : public LineDrawer
{
public:
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen) override;
};

class LineDrawerBresenhamFloat : public LineDrawer
{
public:
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen) override;
};

class LineDrawerBresenhamInt : public LineDrawer
{
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen) override;
};

class LineDrawerBresenhamSmooth : public LineDrawer
{
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen) override;
};

class LineDrawerWu : public LineDrawer
{
    void drawLine(QPainter &painter, QPointF p1,
                  QPointF p2, QPen pen) override;
};

#endif // LINEDRAWER_H
