#ifndef LAB4_ADDCOMMAND_H
#define LAB4_ADDCOMMAND_H

#include <utility>

#include "BaseCommand.h"
#include "renderarea.h"
#include "lab4/Ellipse.h"

namespace Lab4
{
    class AddEllipseCommand : public BaseCommand
    {
    public:
        AddEllipseCommand(Lab4::Ellipse *ellipse,
                          RenderArea *canvas)
                : ellipse(ellipse), canvas(canvas) { };

        void execute() const override
        {
            canvas->add(ellipse);
        }

        void undo() const override
        {
            canvas->pop();
        }

    private:
        Lab4::Ellipse *ellipse;
        RenderArea *canvas;
    };
}

#endif // ADDCOMMAND_H
