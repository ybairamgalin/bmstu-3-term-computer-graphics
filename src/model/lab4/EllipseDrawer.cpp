#include "lab4/EllipseDrawer.h"

Lab4::EllipseDrawer *Lab4::EllipseDrawer::fromIndex(int index)
{
    switch (index)
    {
        case 0:
            return new Lab4::EllipseDrawerCanonical;
        case 1:
            return new Lab4::EllipseDrawerParametric;
        default:
            return nullptr;
    }
}

void Lab4::EllipseDrawerCanonical::drawEllipse(Lab4::Ellipse ellipse,
                                               QPainter &drawer) const
{
    int a = ellipse.getRx();
    int b = ellipse.getRy();

    double aSqr = a * a;
    double bSqr = b * b;

    int startX = ellipse.getX();
    int startY = ellipse.getY();

    int endX = startX + static_cast<int>(double(a) /
            std::sqrt(1.0 + bSqr / aSqr));

    for (int x = startX; x <= endX; x++)
    {
        int y = static_cast<int>(std::sqrt(b * b - (x - startX) * (x - startX)
                * (bSqr / aSqr))) + startY;

        drawer.drawPoint(x, y);
        drawer.drawPoint(2 * startX - x, y);
        drawer.drawPoint(x, 2 * startY - y);
        drawer.drawPoint(2 * startX - x, 2 * startY - y);
    }

    int endY = startY + static_cast<int>(double(b) /
                                         std::sqrt(1.0 + aSqr / bSqr));

    for (int y = startY; y <= endY; y++)
    {
        int x = static_cast<int>(std::sqrt(a * a - (y - startY) * (y - startY)
                                                   * (aSqr / bSqr))) + startX;

        drawer.drawPoint(x, y);
        drawer.drawPoint(2 * startX - x, y);
        drawer.drawPoint(x, 2 * startY - y);
        drawer.drawPoint(2 * startX - x, 2 * startY - y);
    }
}

void Lab4::EllipseDrawerParametric::drawEllipse(Lab4::Ellipse ellipse,
                                                QPainter &drawer) const
{
    int xc = ellipse.getX();
    int yc = ellipse.getY();
    int a = ellipse.getRx();
    int b = ellipse.getRy();

    double step = (a > b) ? 1.0 / a : 1.0 / b;

    for (double t = 0; t <= M_PI_2 + step; t += step)
    {
        int x = static_cast<int>(std::cos(t) * a) + xc;
        int y = static_cast<int>(std::sin(t) * b) + yc;

        drawer.drawPoint(x, y);
        drawer.drawPoint(2 * xc - x, y);
        drawer.drawPoint(x, 2 * yc - y);
        drawer.drawPoint(2 * xc - x, 2 * yc - y);
    }
}