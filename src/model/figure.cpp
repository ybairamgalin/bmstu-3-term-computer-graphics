#include "figure.h"

Figure::Figure()
{
    center = QPointF(0, 0);
    angle = 0;

    // body
    ellipses.push_back(Ellipse(QPointF(0, 0), 4, 5));

    // head
    ellipses.push_back(Ellipse(QPointF(0, 9), 4, 4));

    // eyes
    ellipses.push_back(Ellipse(QPointF(2, 10), 1, 1));
    ellipses.push_back(Ellipse(QPointF(-2, 10), 1, 1));


    // left hand
    lines.push_back(QLineF(-2, -1, -2, 3));
    lines.push_back(QLineF(-2, -1, -7, 5));
    lines.push_back(QLineF(-7, 5, -2, 3));

    // right hand
    lines.push_back(QLineF(2, -1, 2, 3));
    lines.push_back(QLineF(2, -1, 7, 5));
    lines.push_back(QLineF(7, 5, 2, 3));

    // top part
    lines.push_back(QLineF(0, 12, -3, 15));
    lines.push_back(QLineF(-3, 15, -6, 15));
    lines.push_back(QLineF(0, 12, 3, 15));
    lines.push_back(QLineF(3, 15, 6, 15));

    // feet
    lines.push_back(QLineF(-1, -4, -1, -7));
    lines.push_back(QLineF(-3, -7, -1, -7));

    lines.push_back(QLineF(1, -4, 1, -7));
    lines.push_back(QLineF(3, -7, 1, -7));

    // mouse
    arcs.push_back(Arc(0, 11, 4, 5, 250, 300));
}

Figure& Figure::operator=(const Figure& other)
{
    this->center = other.center;
    this->lines = other.lines;
    this->ellipses = other.ellipses;
    this->arcs = other.arcs;

    this->prev = other.prev;
    this->next = other.next;

    return *this;
}

Figure::Figure(const Figure& other)
{
    this->center = other.center;
    this->lines = other.lines;
    this->ellipses = other.ellipses;
    this->arcs = other.arcs;

    this->prev = nullptr;
    this->next = nullptr;
}

void Figure::translate(double dx, double dy)
{
    saveState();

    QPointF delta = QPointF(dx, dy);

    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i].setP1(lines[i].p1() + delta);
        lines[i].setP2(lines[i].p2() + delta);
    }

    for (size_t i = 0; i < ellipses.size(); i++)
        ellipses[i].translate(dx, dy);

    for (size_t i = 0; i < arcs.size(); i++)
        arcs[i].translate(dx, dy);
}

void Figure::scale(double kx, double ky)
{
    saveState();

    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i].setP1(QPointF((lines[i].p1().x() - center.x()) * kx + center.x(),
                               (lines[i].p1().y() - center.y()) * ky + center.y()));
        lines[i].setP2(QPointF((lines[i].p2().x() - center.x()) * kx + center.x(),
                               (lines[i].p2().y() - center.y()) * ky + center.y()));
    }

    for (size_t i = 0; i < ellipses.size(); i++)
        ellipses[i].scale(center, kx, ky);

    for (size_t i = 0; i < arcs.size(); i++)
        arcs[i].scale(center, kx, ky);
}

void Figure::rotate(double angle)
{
    saveState();

    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i].setP1(rotatePoint(lines[i].p1(), angle));
        lines[i].setP2(rotatePoint(lines[i].p2(), angle));
    }

    for (size_t i = 0; i < ellipses.size(); i++)
        ellipses[i].rotate(center, angle);

    for (size_t i = 0; i < arcs.size(); i++)
        arcs[i].rotate(center, angle);

    this->angle += angle;
}

QPointF Figure::rotatePoint(QPointF point, double angle)
{
    point -= center;
    QPointF result = QPointF(point.x() * cos(angle) - point.y() * sin(angle),
                             point.x() * sin(angle) + point.y() * cos(angle));
    result += center;

    return result;
}

void Figure::setCenter(QPointF point)
{
    center = point;
}

std::vector<QLineF> Figure::getLines()
{
    return lines;
}

std::vector<Ellipse> Figure::getEllipces()
{
    return ellipses;
}

QPointF Figure::getCenter()
{
    return center;
}

std::vector<Arc> Figure::getArcs()
{
    return arcs;
}

void Figure::saveState()
{
    Figure *old = prev;
    prev = new Figure(*this);

    if (old)
        old->next = prev;

    prev->prev = old;
    prev->next = this;
}

void Figure::goBack()
{
    if (prev == nullptr)
        return;

    *this = *prev;
}

void Figure::reset()
{
    for ( ; prev != nullptr; *this = *prev);
}
