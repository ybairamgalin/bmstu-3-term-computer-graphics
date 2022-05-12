#ifndef LAB5_POLYGON_H
#define LAB5_POLYGON_H

#include <vector>

#include "IDrawTimer.h"

namespace Lab5
{
    struct Point
    {
        int x;
        int y;
    };

    class Polygon : public IDrawTimer
    {
    public:
        virtual void addPoint(Point point)
        {
            minX = std::min(minX, point.x);
            maxX = std::max(maxX, point.x);

            minY = std::min(minY, point.y);
            maxY = std::max(maxY, point.y);

            data.push_back(point);
        }

        virtual void deleteLast() { data.pop_back(); }

        void draw(QPainter &painter) const override;
    private:
        std::vector<Point> data;

    protected:
        static int minX;
        static int maxX;
        static int minY;
        static int maxY;
    };

    int Polygon::minX = INT_MAX;
    int Polygon::maxX = INT_MIN;
    int Polygon::minY = INT_MAX;
    int Polygon::maxY = INT_MIN;
}

#endif //LAB5_POLYGON_H
