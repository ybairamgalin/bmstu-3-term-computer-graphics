#include "arc.h"


Arc::Arc(double x, double y, double width, double height,
         double startAngle, double endAngle) :
    Ellipse(QPointF(x, y), width, height)
{
    startPoint = angleToPoint(startAngle);
    endPoint = angleToPoint(endAngle) + 1;
}

int Arc::angleToPoint(double angle)
{
    double step = ((M_PI * 2.0) / pointsInEllipse) * 180.0 / M_PI;

    return angle / step;
}

std::vector<QPointF> Arc::getPoints()
{
    return std::vector<QPointF>(Ellipse::getPoints().begin() + startPoint,
                                Ellipse::getPoints().begin() + endPoint);
}
