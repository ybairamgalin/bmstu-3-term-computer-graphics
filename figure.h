#ifndef FIGURE_H
#define FIGURE_H

#include <QPointF>
#include <QLineF>
#include <QRectF>

#include <vector>

#include "arc.h"
#include "ellipse.h"

class Figure
{
public:
    Figure();
    Figure (const Figure &);

    Figure& operator=(const Figure& other);

    void translate(double dx, double dy);
    void scale(double kx, double ky);
    void rotate(double angle);
    void setCenter(QPointF point);

    std::vector<QLineF> getLines();
    std::vector<Ellipse> getEllipces();
    QPointF getCenter();
    std::vector<Arc> getArcs();

    void goBack();
    void goForward();
    void reset();

    double angle;
private:
    QPointF center;
    std::vector<QLineF> lines;
    std::vector<Ellipse> ellipses;
    std::vector<Arc> arcs;

    Figure *prev;
    Figure *next;

    QPointF rotatePoint(QPointF point, double angle);

    void saveState();
};

#endif // FIGURE_H
