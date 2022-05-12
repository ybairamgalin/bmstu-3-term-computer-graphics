#include "lab5/PolygonSet.h"

namespace Lab5
{
    void PolygonSet::draw(QPainter &painter) const
    {
        for (const auto &poly: polygonSet)
            poly->draw(painter);

        if (!fill)
            return;

        int width = maxX - minX;
        int height = maxY - minY;
//
//        QImage img(width, height);
//        QPainter tmpPainter(img);

        for (const auto &poly: polygonSet)
            poly->draw(painter);
    }
}

