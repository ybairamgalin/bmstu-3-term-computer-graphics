#include "lab4/Ellipse.h"

Lab4::Ellipse::Ellipse(int x, int y, int rx, int ry,  EllipseDrawer *drawer,
                       Color color, bool draw) :
        drawer(drawer), color(color), x(x), y(y), rx(rx), ry(ry),
        drawable(draw) { }

void Lab4::Ellipse::draw(QPainter &painter) const
{
    drawer->drawEllipse(*this, painter);
}

int Lab4::Ellipse::getX() const
{
    return x;
}

int Lab4::Ellipse::getY() const
{
    return y;
}

int Lab4::Ellipse::getRx() const
{
    return rx;
}

int Lab4::Ellipse::getRy() const
{
    return ry;
}

Color Lab4::Ellipse::getColor() const
{
    return color;
}

bool Lab4::Ellipse::isDrawable() const
{
    return drawable;
}
