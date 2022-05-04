#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QPointF>
#include <QDebug>

#ifndef EPS
#define EPS 1e-6
#endif

class Triangle
{
private:
    QPointF vertices[3];

public:
    Triangle(const QPointF first, const QPointF second,
             const QPointF third);
    double sumBisectressIntersectionCoords();
    bool isDegenerate();
    QPointF bisectressIntersection();
    void lineEqCoefs(QPointF first, QPointF second, double *coefs);
    QPointF lineInterCoords(const double *firstCoefs, const double *secondCoefs);
    double edgeLng(const int nEdge);
    QPointF getVertex(const int nVertex);
    double minX();
    double minY();
    double maxX();
    double maxY();
};

#endif // TRIANGLE_H
