#ifndef IDRAWTIMER_H
#define IDRAWTIMER_H

#include <chrono>

#include "IDrawable.h"

class IDrawTimer : public IDrawable
{
public:
    [[nodiscard]] decltype(auto) timeDraw() const;
protected:
    virtual ~IDrawTimer() = default;

    void draw() const override = 0;
};

#endif // IDRAWTIMER_H
