#include "IDrawTimer.h"

decltype(auto) IDrawTimer::timeDraw() const
{

    auto start = std::chrono::high_resolution_clock::now();

//    for (size_t i = 0; i < repeats; i++)
//        draw(PointDrawer());

    auto end = std::chrono::high_resolution_clock::now();

    auto taken = std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start);

    return taken.count();
}
