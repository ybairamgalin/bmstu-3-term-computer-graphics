#ifndef LAB4_ELLIPSE_H
#define LAB4_ELLIPSE_H

#include "IDrawTimer.h"
#include "PointDrawer.h"
#include "lab4/EllipseDrawer.h"

namespace Lab4
{
    class EllipseDrawer;

    class Ellipse : public IDrawTimer
    {
    public:
        Ellipse(int x, int y, int rx, int ry, EllipseDrawer *drawer,
                Color color);

        Ellipse(const Ellipse &other) = default;

        Ellipse(Ellipse &&) = default;

        Ellipse &operator=(const Ellipse &) = default;

        void draw(QPainter &pointDrawer) const override;

        [[nodiscard]] int getX() const;
        [[nodiscard]] int getY() const;
        [[nodiscard]] int getRx() const;
        [[nodiscard]] int getRy() const;
    private:
        EllipseDrawer *drawer;
        Color color;

        int x;
        int y;
        int rx;
        int ry;
    };
}

#endif
