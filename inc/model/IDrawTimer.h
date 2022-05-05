#ifndef IDRAWTIMER_H
#define IDRAWTIMER_H

#include <chrono>

#include "IDrawable.h"

class IDrawTimer : public IDrawable
{
public:
    [[nodiscard]] decltype(auto) timeDraw() const;
    void draw(QPainter &) const override { };
protected:
    virtual ~IDrawTimer() = default;

    size_t repeats = 1000;
};

#endif // IDRAWTIMER_H
