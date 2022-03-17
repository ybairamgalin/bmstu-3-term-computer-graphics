#ifndef ARC_H
#define ARC_H

#include <QRect>

#include <math.h>
#include <vector>

#include "ellipse.h"

class Arc : public Ellipse
{
public:
    Arc(double x, double y, double width, double height,
        double startAngle, double endAngle);
    std::vector<QPointF> getPoints();

private:
    int startPoint;
    int endPoint;

    int angleToPoint(double angle);
};

#endif // ARC_H
