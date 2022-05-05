#ifndef IDRAWTIMER_H
#define IDRAWTIMER_H

#include <chrono>

#include "IDrawable.h"

class IDrawTimer : public IDrawable
{
public:
    [[nodiscard]] decltype(auto) timeDraw(QPainter &dr, size_t repeats) const
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < repeats; i++)
            draw(dr);

        auto end = std::chrono::high_resolution_clock::now();

        auto taken = std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                           start);

        return taken.count();
    }

    void draw(QPainter &) const override { };
protected:
    virtual ~IDrawTimer() = default;
};

#endif // IDRAWTIMER_H
