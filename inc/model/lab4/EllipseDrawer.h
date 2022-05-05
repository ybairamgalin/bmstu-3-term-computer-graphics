#ifndef LAB4_ELLIPSEDRAWER_H
#define LAB4_ELLIPSEDRAWER_H

#include "Ellipse.h"
#include "PointDrawer.h"
#include <QPainter>

namespace Lab4
{
    class Ellipse;

    class EllipseDrawer
    {
    public:
        virtual ~EllipseDrawer() = default;
        virtual void drawEllipse(Ellipse ellipse, QPainter &drawer) const = 0;
        static EllipseDrawer *fromIndex(int index);
    };

    class EllipseDrawerCanonical : public EllipseDrawer
    {
        void drawEllipse(Ellipse ellipse, QPainter &drawer) const override;
    };

    class EllipseDrawerParametric : public EllipseDrawer
    {
        void drawEllipse(Ellipse ellipse, QPainter &drawer) const override;
    };

    class EllipseDrawerBresenham : public EllipseDrawer
    {
        void drawEllipse(Ellipse ellipse, QPainter &drawer) const override;
    };

    class EllipseDrawerMidPoint : public EllipseDrawer
    {
        void drawEllipse(Ellipse ellipse, QPainter &drawer) const override;
    };

    class EllipseDrawerLib : public EllipseDrawer
    {
        void drawEllipse(Ellipse ellipse, QPainter &drawer) const override;
    };
}

#endif // ELLIPSEDRAWER_H
