//
// Created by Yaroslav Bairamgalin on 05.05.2022.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "lab4/Ellipse.h"

namespace Lab4
{
    class Circle : public Ellipse
    {
    public:
        Circle(int x, int y, int r, EllipseDrawer *drawer, Color col) :
                Ellipse(x, y, r, r, drawer, col) { };
        Circle(const Circle&) = default;
        Circle(Circle &&) = default;

        Circle& operator=(const Circle &) = default;
    };
}

#endif // CIRCLE_H
