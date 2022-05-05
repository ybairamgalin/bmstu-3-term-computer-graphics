//
// Created by Yaroslav Bairamgalin on 05.05.2022.
//

#ifndef INVOKER_H
#define INVOKER_H

#include <vector>

#include "lab4/AddCommand.h"
#include "lab4/Ellipse.h"
#include "lab4/EllipseSet.h"
#include "lab4/Circle.h"
#include "lab4/EllipseDrawer.h"
#include "renderarea.h"

class Invoker
{
    std::vector<BaseCommand *> doneCommands;
    BaseCommand *command = nullptr;
    RenderArea *canvas;
public:
    explicit Invoker(RenderArea *canvas) : canvas(canvas) { };

    void addEllipse(int x, int y, int a, int b, int colIndex, int algInd)
    {
        auto *ellipse = new Lab4::Ellipse(x, y, a, b,
                Lab4::EllipseDrawer::fromIndex(algInd),
                Color::fromIndex(colIndex));

        command = new Lab4::AddEllipseCommand(ellipse, canvas);
        command->execute();
        doneCommands.push_back(command);
    }

    void addCircle(int x, int y, int r, int colIndex, int algInd)
    {
        auto *circle = new Lab4::Circle(x, y, r,
                Lab4::EllipseDrawer::fromIndex(algInd),
                Color::fromIndex(colIndex));

        command = new Lab4::AddEllipseCommand(circle, canvas);
        command->execute();
        doneCommands.push_back(command);
    }

    void addEllipseSet(int a, int b, int n, int step, int colIndx, int algInd)
    {
        auto *ellipses = new Lab4::EllipseSet(a, b, n, step,
                Lab4::EllipseDrawer::fromIndex(algInd),
                Color::fromIndex(colIndx));

        command = new Lab4::AddEllipseCommand(ellipses, canvas);
        command->execute();
        doneCommands.push_back(command);
    }

    void undo()
    {
        if (doneCommands.empty())
            return;

        doneCommands[doneCommands.size() - 1]->undo();
        doneCommands.pop_back();
    }

    void showWarning(const QString &str) const
    {
        qDebug() << str;
    }
};

#endif //LAB_01_INVOKER_H
