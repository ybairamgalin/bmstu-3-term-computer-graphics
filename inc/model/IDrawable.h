#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <PointDrawer.h>

class IDrawable
{
public:
    virtual void draw(QPainter &) const { };
};

#endif // IDRAWABLE_H
