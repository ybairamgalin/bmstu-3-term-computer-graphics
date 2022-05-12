#ifndef LAB5_ADDPOINTCOMMAND_H
#define LAB5_ADDPOINTCOMMAND_H

#include "BaseCommand.h"
#include "lab5/Polygon.h"

namespace Lab5
{
    class AddMousePoint : public BaseCommand
    {
    public:
        AddMousePoint(int x, int y, Polygon &poly) : x(x), y(y), poly(poly) { }

        void execute() override
        {
            poly.addPoint(Point{x, y});
        }

        void undo() const override
        {
            poly.deleteLast();
        }

    private:
        int x;
        int y;
        Polygon &poly;
    };
}

#endif //LAB_01_ADDPOINTCOMMAND_H
