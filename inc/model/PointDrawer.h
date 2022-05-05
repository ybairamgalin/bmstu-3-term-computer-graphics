#ifndef POINTDRAWER_H
#define POINTDRAWER_H

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <string>

class ColorException : std::exception
{
    [[nodiscard]] const char *what() const noexcept override
    {
        return err.c_str();
    }

protected:
    std::string err = "Check color values";
};

struct Color
{
    Color(int r, int g, int b, int a)
    {
        if (r > 255 || r < 0)
            throw ColorException();

        if (g > 255 || g < 0)
            throw ColorException();

        if (b > 255 || b < 0)
            throw ColorException();

        if (a > 255 || a < 0)
            throw ColorException();

        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    Color(const Color &) = default;
    Color(Color &&) = default;
    Color& operator=(const Color &) = default;

    explicit operator QColor() const
    {
        return QColor(r, g, b, a);
    }

    static Color fromIndex(int index)
    {
        switch (index)
        {
            case 0:
                return Color(0, 0, 0, 255);
            case 1:
                return Color(255, 0, 0, 255);
            case 2:
                return Color(0, 255, 0, 255);
            case 3:
                return Color(0, 0, 255, 255);
            case 4:
                return Color(255, 255, 255, 255);
            default:
                return Color(0, 0, 0, 255);
        }
    }

    int r;
    int g;
    int b;
    int a;
};

class [[maybe_unused]] PointDrawer
{
public:
    explicit PointDrawer(QPainter &painter) : painter(painter) { };
    PointDrawer(const PointDrawer &) = default;
    PointDrawer(PointDrawer &&) noexcept = default;

    void operator()(int x, int y, Color color) const
    {
        painter.setPen(QColor(color.r, color.g, color.b, color.a));
        painter.drawPoint(x, y);
    }
private:
    QPainter &painter;
};

#endif //LAB_01_POINTDRAWER_H
