#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "IDrawTimer.h"
#include "PointDrawer.h"

namespace Lab4
{
    class Ellipse : public IDrawTimer
    {
    public:
        void draw() const override;

    private:
        PointDrawer drawPoint;
    };
}

#endif //LAB_01_ELLIPSE_H
