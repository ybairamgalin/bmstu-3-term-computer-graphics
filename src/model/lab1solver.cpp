#include "lab1solver.h"

Lab1Solver::Lab1Solver()
{
    updated = false;
}

Lab1Solver::~Lab1Solver()
{

}

void Lab1Solver::addPoint(QPointF point)
{
    points.push_back(point);
    updated = false;
}

void Lab1Solver::removePoint(const int index)
{
    points.erase(points.begin() + index);
    updated = false;
}

void Lab1Solver::solve()
{
    _solution.clear();
    _solutionMessage = QString("");
    _degenerateMessage = QString("");

    if (points.size() < 3)
    {
        _solutionMessage += "Точек слишком мало\n";
        updated = true;
        return;
    }

    double minDistance = INFINITY;
    Triangle minTriangle = Triangle(points[0], points[0], points[0]);

    for (size_t i = 0; i < points.size() - 2; i++)
        for (size_t j = i + 1; j < points.size() - 1; j++)
            for (size_t k = j + 1; k < points.size(); k++)
            {
                Triangle triangle = Triangle(points[i], points[j], points[k]);

                if (triangle.isDegenerate())
                {
                    if (_degenerateMessage.isEmpty())
                        _degenerateMessage += QString("Вырожденный случай в точках\n");

                    _degenerateMessage += QString("(") +
                        QString::number(points[i].x()) + QString(", ") + QString::number(points[i].y()) + QString("), (") +
                        QString::number(points[j].x()) + QString(", ") + QString::number(points[j].y()) + QString("), (") +
                        QString::number(points[k].x()) + QString(", ") + QString::number(points[k].y()) + QString(");\n");
                    continue;
                }

                double curDistance = triangle.sumBisectressIntersectionCoords();

                if (curDistance < minDistance)
                {
                    minDistance = curDistance;
                    minTriangle = triangle;
                }
            }

    if (minDistance != INFINITY)
    {
        _solution.push_back(minTriangle);
        _solutionMessage += "Решено\n";
    }
    updated = true;
}

QString Lab1Solver::solutionMessage()
{
    if (!updated)
        return QString("Задача еще не была решена\n");

    if (_solutionMessage.isEmpty())
        return QString("Решения нет\n");

    return _solutionMessage;
}

QString Lab1Solver::degenerateMessage()
{
    if (_degenerateMessage.isEmpty())
        return QString("Вырожденных случаев нет\n");

    return _degenerateMessage;
}

std::vector<Triangle> Lab1Solver::solution()
{
    return _solution;
}

void Lab1Solver::clearPoints()
{
    points.clear();
    updated = false;
}

std::vector<QPointF> Lab1Solver::getPoints()
{
    return points;
}
