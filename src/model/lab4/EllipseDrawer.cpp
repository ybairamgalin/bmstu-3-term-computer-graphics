#include "lab4/EllipseDrawer.h"

Lab4::EllipseDrawer *Lab4::EllipseDrawer::fromIndex(int index)
{
    switch (index)
    {
        case 0:
            return new Lab4::EllipseDrawerCanonical;
        case 1:
            return new Lab4::EllipseDrawerParametric;
        case 2:
            return new Lab4::EllipseDrawerBresenham;
        case 3:
            return new Lab4::EllipseDrawerMidPoint;
        case 4:
            return new Lab4::EllipseDrawerLib;
        default:
            throw;
    }
}

void Lab4::EllipseDrawerCanonical::drawEllipse(Lab4::Ellipse ellipse,
                                               QPainter &drawer) const
{
    drawer.setPen(QColor(ellipse.getColor()));

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
        int y = static_cast<int>(std::lround(std::sqrt(b * b -
                (x - startX) * (x - startX) * (bSqr / aSqr))) + startY);

        drawer.drawPoint(x, y);
        drawer.drawPoint(2 * startX - x, y);
        drawer.drawPoint(x, 2 * startY - y);
        drawer.drawPoint(2 * startX - x, 2 * startY - y);
    }

    int endY = startY + static_cast<int>(double(b) /
                                         std::sqrt(1.0 + aSqr / bSqr));

    for (int y = startY; y <= endY; y++)
    {
        int x = static_cast<int>(std::lround(std::sqrt(a * a - (y - startY) *
                (y - startY) * (aSqr / bSqr))) + startX);

        drawer.drawPoint(x, y);
        drawer.drawPoint(2 * startX - x, y);
        drawer.drawPoint(x, 2 * startY - y);
        drawer.drawPoint(2 * startX - x, 2 * startY - y);
    }
}

void Lab4::EllipseDrawerParametric::drawEllipse(Lab4::Ellipse ellipse,
                                                QPainter &drawer) const
{
    drawer.setPen(QColor(ellipse.getColor()));

    int xc = ellipse.getX();
    int yc = ellipse.getY();
    int a = ellipse.getRx();
    int b = ellipse.getRy();

    double step = (a > b) ? 1.0 / a : 1.0 / b;

    for (double t = 0; t <= M_PI_2 + step; t += step)
    {
        int x = static_cast<int>(std::lround(std::cos(t) * a) + xc);
        int y = static_cast<int>(std::lround(std::sin(t) * b) + yc);

        drawer.drawPoint(x, y);
        drawer.drawPoint(2 * xc - x, y);
        drawer.drawPoint(x, 2 * yc - y);
        drawer.drawPoint(2 * xc - x, 2 * yc - y);
    }
}

void Lab4::EllipseDrawerBresenham::drawEllipse(Lab4::Ellipse ellipse,
                                               QPainter &drawer) const
{
    drawer.setPen(QColor(ellipse.getColor()));

    int a = ellipse.getRx();
    int b = ellipse.getRy();

    int aSqr = a * a;
    int bSqr = b * b;

    int startX = ellipse.getX();
    int startY = ellipse.getY();

    int endX = startX + static_cast<int>(double(a) /
                                         std::sqrt(1.0 + double(bSqr) / aSqr));

    int x = 0;
    int y = b;

    drawer.drawPoint(x + startX, y + startY);
    drawer.drawPoint(-x + startX, y + startY);
    drawer.drawPoint(x + startX, -y + startY);
    drawer.drawPoint(-x + startX, -y + startY);

    int delta = 4 * bSqr * (x + 1) * (x + 1) +
                aSqr * (2 * y - 1) * (2 * y - 1) -
                4 * aSqr * bSqr;

    for ( ; x < endX - startX; ++x)
    {
        if (delta < 0)
            delta += 4 * bSqr * (2 * x + 3);
        else
        {
            delta += 4 * bSqr * (2 * x + 3) - 8 * aSqr * (y - 1);
            --y;
        }

        drawer.drawPoint(x + startX, y + startY);
        drawer.drawPoint(-x + startX, y + startY);
        drawer.drawPoint(x + startX, -y + startY);
        drawer.drawPoint(-x + startX, -y + startY);
    }

    x = a;
    y = 0;

    delta = 4 * aSqr * (y + 1) * (y + 1) +
            bSqr * (2 * x - 1) * (2 * x - 1) -
            4 * aSqr * bSqr;

    for ( ; x >= endX - startX; ++y)
    {
        if (delta < 0)
            delta += 4 * aSqr * (2 * y + 3);
        else
        {
            delta += 4 * aSqr * (2 * y + 3) - 8 * bSqr * (x - 1);
            --x;
        }

        drawer.drawPoint(x + startX, y + startY);
        drawer.drawPoint(-x + startX, y + startY);
        drawer.drawPoint(x + startX, -y + startY);
        drawer.drawPoint(-x + startX, -y + startY);
    }
}

void Lab4::EllipseDrawerMidPoint::drawEllipse(Lab4::Ellipse ellipse,
                                              QPainter &drawer) const
{
    drawer.setPen(QColor(ellipse.getColor()));

    int a = ellipse.getRx();
    int b = ellipse.getRy();

    int aSqr = a * a;
    int bSqr = b * b;

    int startX = ellipse.getX();
    int startY = ellipse.getY();

    int endX = startX + static_cast<int>(double(a) /
                                         std::sqrt(1.0 + double(bSqr) / aSqr));

    int x = 0;
    int y = b;

    drawer.drawPoint(x + startX, y + startY);
    drawer.drawPoint(-x + startX, y + startY);
    drawer.drawPoint(x + startX, -y + startY);
    drawer.drawPoint(-x + startX, -y + startY);

    int delta = 4 * bSqr * (x + 1) * (x + 1) +
                aSqr * (2 * y - 1) * (2 * y - 1) -
                4 * aSqr * bSqr;

    for ( ; x < endX - startX; ++x)
    {
        if (delta < 0)
            delta += 4 * bSqr * (2 * x + 3);
        else
        {
            delta += 4 * bSqr * (2 * x + 3) - 8 * aSqr * (y - 1);
            --y;
        }

        drawer.drawPoint(x + startX, y + startY);
        drawer.drawPoint(-x + startX, y + startY);
        drawer.drawPoint(x + startX, -y + startY);
        drawer.drawPoint(-x + startX, -y + startY);
    }

    x = a;
    y = 0;

    delta = 4 * aSqr * (y + 1) * (y + 1) +
            bSqr * (2 * x - 1) * (2 * x - 1) -
            4 * aSqr * bSqr;

    for ( ; x >= endX - startX; ++y)
    {
        if (delta < 0)
            delta += 4 * aSqr * (2 * y + 3);
        else
        {
            delta += 4 * aSqr * (2 * y + 3) - 8 * bSqr * (x - 1);
            --x;
        }

        drawer.drawPoint(x + startX, y + startY);
        drawer.drawPoint(-x + startX, y + startY);
        drawer.drawPoint(x + startX, -y + startY);
        drawer.drawPoint(-x + startX, -y + startY);
    }
}

void Lab4::EllipseDrawerLib::drawEllipse(Lab4::Ellipse ellipse,
                                         QPainter &drawer) const
{
    drawer.setPen(QColor(ellipse.getColor()));

    drawer.drawEllipse(ellipse.getX() - ellipse.getRx(),
                       ellipse.getY() - ellipse.getRy(),
                       ellipse.getRx() * 2,
                       ellipse.getRy() * 2);
}
