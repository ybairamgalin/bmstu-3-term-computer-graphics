#include "Lab5Dock.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Converter.h"

Lab5Dock::Lab5Dock(Invoker *invoker, QWidget *parent) :
        BaseDock(invoker, parent)
{
    createFields();
    placeFields();
    connectHandlers();
}

void Lab5Dock::createFields()
{
    description = new QLabel("Лабораторная работа 5");

    colorLabel = new QLabel("Выбор цвета");
    colorComboBox = new QComboBox;
    colorComboBox->addItem("Черный");
    colorComboBox->addItem("Красный");
    colorComboBox->addItem("Зеленый");
    colorComboBox->addItem("Синий");
    colorComboBox->addItem("Белый");

    pointsList = new QListWidget;

    addPointLabel = new QLabel("Добавление точки");
    addPointXEdit = new QLineEdit;
    addPointXEdit->setPlaceholderText("x");
    addPointYEdit = new QLineEdit;
    addPointYEdit->setPlaceholderText("y");
    addPointButton = new QPushButton("Добавить точку");
    deleteLastButton = new QPushButton("Удалить последнюю точку");

    drawButton = new QPushButton("Нарисовать!");

    delayBox = new QCheckBox("Задержка");

    timeButton = new QPushButton("Замерить время");
    clearScreenButton = new QPushButton("Очистить экран");
}

void Lab5Dock::placeFields()
{
    grid->addWidget(description);
    grid->addWidget(colorLabel);
    grid->addWidget(colorComboBox);
    grid->addWidget(pointsList);
    grid->addWidget(addPointLabel);
    grid->addWidget(addPointXEdit);
    grid->addWidget(addPointYEdit);
    grid->addWidget(addPointButton);
    grid->addWidget(deleteLastButton);
    grid->addWidget(drawButton);
    grid->addWidget(delayBox);
    grid->addWidget(timeButton);
    grid->addWidget(clearScreenButton);
}

void Lab5Dock::connectHandlers()
{
    connect(addPointButton, SIGNAL(released()),
            this, SLOT(onAddPointButtonClick()));
    connect(clearScreenButton, SIGNAL(released()),
            this, SLOT(onClearScreenButtonClick()));
}

void Lab5Dock::onAddPointButtonClick()
{
    int x, y;

    try
    {
        x = Converter::toInt(addPointXEdit->text());
        y = Converter::toInt(addPointYEdit->text());

        invoker->addPoint(x, y);
    }
    catch (ConvertException &exception)
    {
        invoker->showWarning(exception.what());
    }
}

void Lab5Dock::onClearScreenButtonClick()
{
    invoker->undo_all();
}
