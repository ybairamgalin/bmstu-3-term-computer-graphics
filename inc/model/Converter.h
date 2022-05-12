#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

#include <QString>

class ConvertException : std::exception
{
public:
    explicit ConvertException() = default;

    [[nodiscard]] const char *what() const noexcept override
    {
        return err.c_str();
    }

protected:
    std::string err = "Ошибка конвертации";;
};

class Converter
{
public:
    static double toDouble(const QString &str)
    {
        bool converted = true;
        double value = str.toDouble(&converted);

        if (!converted)
        {
            throw ConvertException();
        }

        return value;
    }

    static int toInt(const QString &str)
    {
        bool converted = true;
        int value = str.toInt(&converted);

        if (!converted)
        {
            throw ConvertException();
        }

        return value;
    }
};

#endif //LAB_01_CONVERTER_H
