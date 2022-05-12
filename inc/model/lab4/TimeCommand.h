//
// Created by Yaroslav Bairamgalin on 06.05.2022.
//

#ifndef LAB_04_TIMECOMMAND_H
#define LAB_04_TIMECOMMAND_H

#include <QDebug>
#include <fstream>
#include "lab4/Ellipse.h"

#include "BaseCommand.h"

namespace Lab4
{
    class TimeCommand : public BaseCommand
    {
    public:
        void execute() override
        {
            int rad[] = { 500, 1000, 5000, 10000, 15000, 20000 };
            file.open(filename);

            for (auto value: rad)
            {
                std::shared_ptr<IDrawTimer> canonical =
                        std::shared_ptr<IDrawTimer>(new Ellipse(
                        0, 0, value, value,
                        new EllipseDrawerParametric,
                        Color(0, 0, 0, 255), false));

                std::shared_ptr<IDrawTimer> parametric =
                        std::shared_ptr<IDrawTimer>(new Ellipse(
                                0, 0, value, value,
                                new EllipseDrawerParametric,
                                Color(0, 0, 0, 255), false));

                std::shared_ptr<IDrawTimer> bresenham =
                        std::shared_ptr<IDrawTimer>(new Ellipse(
                                0, 0, value, value,
                                new EllipseDrawerBresenham,
                                Color(0, 0, 0, 255), false));

                std::shared_ptr<IDrawTimer> midPoint =
                        std::shared_ptr<IDrawTimer>(new Ellipse(
                                0, 0, value, value,
                                new EllipseDrawerMidPoint,
                                Color(0, 0, 0, 255), false));

                std::shared_ptr<IDrawTimer> lib =
                        std::shared_ptr<IDrawTimer>(new Ellipse(
                                0, 0, value, value,
                                new EllipseDrawerLib,
                                Color(0, 0, 0, 255), false));

                QPainter fakePainter;

                std::string res;
                res += std::to_string(canonical->timeDraw(fakePainter,
                                                          repeats)) + " ";
                res += std::to_string(parametric->timeDraw(fakePainter,
                                                          repeats)) + " ";
                res += std::to_string(bresenham->timeDraw(fakePainter,
                                                           repeats)) + " ";
                res += std::to_string(midPoint->timeDraw(fakePainter,
                                                           repeats)) + " ";
                res += std::to_string(lib->timeDraw(fakePainter,
                                                           repeats)) + " ";

                qDebug() << res.c_str();
                file << res << "\n";
            }

            file.close();
            genGraph();
        }

        void undo() const override { }

    private:
        std::string filename = "../basicGeometry/time.txt";
        std::ofstream file;

        const int repeats = 1000;

        void genGraph() const
        {
            system("python3 ../basicGeometry/src/utils/main.py");
        }
    };
}

#endif //LAB_01_TIMECOMMAND_H
