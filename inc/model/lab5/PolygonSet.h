//
// Created by Yaroslav Bairamgalin on 12.05.2022.
//

#ifndef LAB4_POLYGONSET_H
#define LAB4_POLYGONSET_H

#include <vector>

#include "PointDrawer.h"
#include "lab5/Polygon.h"

namespace Lab5
{
    class PolygonSet : public Polygon
    {
    public:
        PolygonSet()
        {
            polygonSet.push_back(std::make_shared<Polygon>());
        }

        void addPoint(Point point) override
        {
            (*(polygonSet.end() - 1))->addPoint(point);
        }

        void deleteLast() override
        {
            (*(polygonSet.end() - 1))->deleteLast();
        }

        void draw(QPainter &painter) const override;

        void setFill()
        {
            fill = true;
        }

        void setColor(const Color &col)
        {
            color = col;
        }

    private:
        std::vector<std::shared_ptr<Polygon>> polygonSet;
        bool fill = false;
        bool delay = false;

        Color color = Color(0, 0, 0, 255);
    };
}

#endif //LAB_01_POLYGONSET_H
