#ifndef LAB1SOLVER_H
#define LAB1SOLVER_H

#include <QPointF>
#include <vector>
#include "triangle.h"

class Lab1Solver
{
private:
    std::vector<QPointF> points;
    std::vector<Triangle> _solution;
    QString _solutionMessage;
    QString _degenerateMessage;
    bool updated;
public:
    Lab1Solver();
    ~Lab1Solver();
    void addPoint(QPointF point);
    void removePoint(const int index);
    void clearPoints();
    void solve();
    QString solutionMessage();
    QString degenerateMessage();
    std::vector<Triangle> solution();
    std::vector<QPointF> getPoints();
};

#endif // LAB1SOLVER_H
