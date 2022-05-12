//
// Created by Yaroslav Bairamgalin on 12.05.2022.
//

#ifndef LAB5_ADDPOLYCOMMAND_H
#define LAB5_ADDPOLYCOMMAND_H

#include "Polygon.h"
#include "BaseCommand.h"
#include "vector"

namespace Lab5
{
    class AddPolyCommand : public BaseCommand
    {
    public:
        AddPolyCommand(Polygon *poly, RenderArea *canvas) :
                polygon(poly), canvas(canvas) { };

        void execute() override
        {
            canvas->add(polygon);
        }

        void undo() const override
        {
            canvas->pop();
        }

    private:
        Polygon *polygon;
        RenderArea *canvas;
    };
}

#endif
