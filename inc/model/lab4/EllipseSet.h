//
// Created by Yaroslav Bairamgalin on 05.05.2022.
//

#ifndef ELLIPSESET_H
#define ELLIPSESET_H

#include <vector>

#include "lab4/Ellipse.h"

namespace Lab4
{
    class EllipseSet : public Ellipse
    {
    public:
        EllipseSet(int a, int b, int n, int step, EllipseDrawer *drawer,
                   Color col) : Ellipse(0, 0, a, b, drawer, col), sz(n),
                   step(step)
        {
            for (int i = 0; i < n; ++i)
            {
                ellipseSet.push_back(new Ellipse(0, 0, a + step * i,
                        b + step * i, drawer, col));
            }
        }
        EllipseSet(const EllipseSet&) = default;
        EllipseSet(EllipseSet&&) = default;

        void draw(QPainter &pointDrawer) const override
        {
            for (auto &element: ellipseSet)
                element->draw(pointDrawer);
        }

    private:
        std::vector<Ellipse *> ellipseSet;

        int sz;
        int step;
    };
}

#endif // ELLIPSESET_H
