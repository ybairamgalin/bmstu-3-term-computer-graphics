//
// Created by Yaroslav Bairamgalin on 06.05.2022.
//

#ifndef LAB_04_TIMECOMMAND_H
#define LAB_04_TIMECOMMAND_H

#include <QDebug>
#include "lab4/Ellipse.h"

#include "BaseCommand.h"

namespace Lab4
{
    class TimeCommand : public BaseCommand
    {
    public:
        void execute() const override
        {
            IDrawTimer *ellipse = new Ellipse(0, 0, 1000, 1000,
                    new EllipseDrawerParametric,
                    Color(0, 0, 0, 255), false);

            QPainter fakePainter;
            qDebug() << ellipse->timeDraw(fakePainter, 1000);
        }

        void undo() const override { }
    };
}

#endif //LAB_01_TIMECOMMAND_H
