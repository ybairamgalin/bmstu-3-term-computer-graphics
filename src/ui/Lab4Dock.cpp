#include "Lab4Dock.h"

Lab4Dock::Lab4Dock(Invoker *invoker, QWidget *parent) :
        BaseDock(invoker, parent)
{
    createFields();
    placeFields();
    connectHandlers();
}

void Lab4Dock::createFields()
{
    description = new QLabel("Лабораторная работа 4");

    algLabel = new QLabel("Выбор алгоритма");
    algComboBox = new QComboBox;
    algComboBox->addItem("Каноническое уравнение");
    algComboBox->addItem("Параметрическое уравнение");

    colorLabel = new QLabel("Выбор цвета");
    colorComboBox = new QComboBox;
    colorComboBox->addItem("Черный");
    colorComboBox->addItem("Красный");
    colorComboBox->addItem("Зеленый");
    colorComboBox->addItem("Синий");
    colorComboBox->addItem("Белый");

    circleLabel = new QLabel("Окружность");
    circleXEdit = new QLineEdit;
    circleYEdit = new QLineEdit;
    circleREdit = new QLineEdit;
    drawCircleButton = new QPushButton("Построить окружность");

    ellipseLabel = new QLabel("Эллипс");
    ellipseXEdit = new QLineEdit;
    ellipseYEdit = new QLineEdit;
    ellipseAEdit = new QLineEdit;
    ellipseBEdit = new QLineEdit;

    drawEllipseButton = new QPushButton("Построить эллипс");

}

void Lab4Dock::placeFields()
{
    grid->addWidget(description, 0, 0);
    grid->addWidget(algLabel, 1, 0);
    grid->addWidget(algComboBox, 2, 0);
    grid->addWidget(colorLabel, 3, 0);
    grid->addWidget(colorComboBox, 4, 0);
    grid->addWidget(circleLabel, 5, 0);
    grid->addWidget(circleXEdit, 6, 0);
    grid->addWidget(circleYEdit, 7, 0);
    grid->addWidget(circleREdit, 8, 0);
    grid->addWidget(drawCircleButton, 9, 0);
    grid->addWidget(ellipseLabel, 10, 0);
    grid->addWidget(ellipseXEdit, 11, 0);
    grid->addWidget(ellipseYEdit, 12, 0);
    grid->addWidget(ellipseAEdit, 13, 0);
    grid->addWidget(ellipseBEdit, 14, 0);
    grid->addWidget(drawEllipseButton, 15, 0);
}

void Lab4Dock::connectHandlers()
{
    connect(drawEllipseButton, SIGNAL(released()),
            this, SLOT(onDrawEllipseButtonClick()));
}

void Lab4Dock::onDrawEllipseButtonClick()
{
    int x, y, a, b;

    try
    {
        x = Converter::toInt(ellipseXEdit->text());
        y = Converter::toInt(ellipseYEdit->text());
        a = Converter::toInt(ellipseAEdit->text());
        b = Converter::toInt(ellipseBEdit->text());

        int color = colorComboBox->currentIndex();
        int alg = algComboBox->currentIndex();

        invoker->addEllipse(x, y, a, b, color, alg);
    }
    catch (ConvertException &exception)
    {
        invoker->showWarning(exception.what());
    }
}
