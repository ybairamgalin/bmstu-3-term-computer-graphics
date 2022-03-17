#include "triangle.h"

Triangle::Triangle(const QPointF first, const QPointF second,
                   const QPointF third)
{
    vertices[0] = first;
    vertices[1] = second;
    vertices[2] = third;
}

//bool Triangle::isDegenerate()
//{
//    if (edgeLng(0) + edgeLng(1) < edgeLng(2))
//        return true;

//    if (edgeLng(1) + edgeLng(2) < edgeLng(0))
//        return true;

//    if (edgeLng(2) + edgeLng(0) < edgeLng(1))
//        return true;

//    return false;
//}

void Triangle::lineEqCoefs(QPointF first, QPointF second, double *coefs)
{
    QPointF pVector = QPointF(second.x() - first.x(),
                            second.y() - first.y());

    QPointF nVector = QPointF(pVector.y(), -pVector.x());

    double c = -(nVector.x() * first.x() +
            nVector.y() * first.y());

    coefs[0] = nVector.x();
    coefs[1] = nVector.y();
    coefs[2] = c;
}

double Triangle::edgeLng(const int nEdge)
{
    QPointF first, second;

    if (nEdge == 0)
    {
        first = vertices[0];
        second = vertices[1];
    }
    else if (nEdge == 1)
    {
        first = vertices[1];
        second = vertices[2];
    }
    else if (nEdge == 2)
    {
        first = vertices[2];
        second = vertices[0];
    }
    else
        throw;

    double lng = sqrt(pow(first.x() - second.x(), 2) +
                      pow(first.y() - second.y(), 2));

    return lng;
}

QPointF Triangle::lineInterCoords(const double *firstCoefs, const double *secondCoefs)
{
    QPointF point;

    point.setX((firstCoefs[1] * secondCoefs[2] - firstCoefs[2] * secondCoefs[1]) /
            (firstCoefs[0] * secondCoefs[1] - firstCoefs[1] * secondCoefs[0]));
    point.setY((firstCoefs[0] * secondCoefs[2] - firstCoefs[2] * secondCoefs[0]) /
            (firstCoefs[1] * secondCoefs[0] - firstCoefs[0] * secondCoefs[1]));

    return point;
}

QPointF Triangle::bisectressIntersection()
{
    double firstRatio = edgeLng(0) / edgeLng(1);
    double xBisInter = (vertices[0].x() + firstRatio * vertices[2].x()) / (firstRatio + 1);
    double yBisInter = (vertices[0].y() + firstRatio * vertices[2].y()) / (firstRatio + 1);

    QPointF firstBisIntersection = QPointF(xBisInter, yBisInter);

    double firstCoefs[3];
    lineEqCoefs(vertices[1], firstBisIntersection, firstCoefs);

    double secondRatio = edgeLng(1) / edgeLng(2);
    xBisInter = (vertices[1].x() + secondRatio * vertices[0].x()) / (secondRatio + 1);
    yBisInter = (vertices[1].y() + secondRatio * vertices[0].y()) / (secondRatio + 1);

    QPointF secondBisIntersection = QPointF(xBisInter, yBisInter);

    double secondCoefs[3];
    lineEqCoefs(vertices[2], secondBisIntersection, secondCoefs);

    return lineInterCoords(firstCoefs, secondCoefs);
}

double Triangle::sumBisectressIntersectionCoords()
{
    QPointF intersection = bisectressIntersection();

    return fabs(intersection.x()) + fabs(intersection.y());
}

bool Triangle::isDegenerate()
{
    if (edgeLng(0) + edgeLng(1) <= edgeLng(2))
        return true;

    if (edgeLng(1) + edgeLng(2) <= edgeLng(0))
        return true;

    if (edgeLng(2) + edgeLng(0) <= edgeLng(1))
        return true;

    return false;
}

QPointF Triangle::getVertex(const int nVertex)
{
    if (nVertex == 0)
        return vertices[0];

    if (nVertex == 1)
        return vertices[1];

    if (nVertex == 2)
        return vertices[2];

    throw;
}

double Triangle::minX()
{
    double minX = vertices[0].x();

    if (vertices[1].x() < minX)
        minX = vertices[1].x();

    if (vertices[2].x() < minX)
        minX = vertices[2].x();

    return minX;
}

double Triangle::minY()
{
    double minY = vertices[0].y();

    if (vertices[1].y() < minY)
        minY = vertices[1].y();

    if (vertices[2].y() < minY)
        minY = vertices[2].y();

    return minY;
}

double Triangle::maxX()
{
    double maxX = vertices[0].x();

    if (vertices[1].x() > maxX)
        maxX = vertices[1].x();

    if (vertices[2].x() > maxX)
        maxX = vertices[2].x();

    return maxX;
}

double Triangle::maxY()
{
    double maxY = vertices[0].y();

    if (vertices[1].y() > maxY)
        maxY = vertices[1].y();

    if (vertices[2].y() > maxY)
        maxY = vertices[2].y();

    return maxY;
}
