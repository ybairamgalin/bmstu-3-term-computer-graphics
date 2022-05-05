//
// Created by Yaroslav Bairamgalin on 05.05.2022.
//

#ifndef INVOKER_H
#define INVOKER_H

#include <vector>

#include "lab4/AddCommand.h"
#include "lab4/Ellipse.h"
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
        QPainter painter(canvas);
        auto *ellipse = new Lab4::Ellipse(x, y, a, b,
                Lab4::EllipseDrawer::fromIndex(algInd),
                Color::fromIndex(colIndex));

        command = new Lab4::AddEllipseCommand(ellipse, canvas);
        command->execute();
        doneCommands.push_back(command);
    }

    void showWarning(const QString &str) const
    {
        qDebug() << str;
    }
};

#endif //LAB_01_INVOKER_H
