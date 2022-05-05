#include "IDrawTimer.h"

//decltype(auto) IDrawTimer::timeDraw(QPainter &drawer, size_t repeats) const
//{
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (size_t i = 0; i < repeats; i++)
//        draw(drawer);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    auto taken = std::chrono::duration_cast<std::chrono::microseconds>(end -
//                                                                       start);
//
//    return taken.count();
//}
