//
// Created by Yaroslav Bairamgalin on 12.05.2022.
//

#include <lab5/Polygon.h>

void Lab5::Polygon::draw(QPainter &drawer) const
{
    if (data.empty())
        return;

    for (const auto& point: data)
        drawer.drawEllipse(point.x, point.y, 3, 3);

    for (auto iter = data.begin(); iter < data.end() - 1; ++iter)
    {
        drawer.drawLine((*iter).x, (*iter).y,
                        (*(iter + 1)).x, (*(iter + 1)).y);
    }
}

