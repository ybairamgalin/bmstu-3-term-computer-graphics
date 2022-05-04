#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QPoint>

#include <vector>
#include <math.h>


class Ellipse
{
public:
    Ellipse(QPointF p1, QPointF p2, QPointF p3,
            QPointF p4, QPointF p5);
    Ellipse(const Ellipse &) = default;
    Ellipse &operator=(const Ellipse &);
    Ellipse(QPointF center, double rx, double ry);
    QPointF p1();
    QPointF p2();
    QPointF p3();
    QPointF p4();
    QPointF p5();

    void translate(double dx, double dy);
    void scale(QPointF center, double kx, double ky);
    void rotate(QPointF center, double angle);

    std::vector<QPointF>& getPoints();
    std::vector<double> equation();

protected:
    const int pointsInEllipse = 50;

private:
    std::vector<QPointF> points;

    QPointF translatePoint(QPointF point, double dx, double dy);
    int gauss(std::vector<std::vector<double>> a, std::vector<double> & ans);
};

#endif // ELLIPSE_H
