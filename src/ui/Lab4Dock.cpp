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
    algComboBox->addItem("Брезенхем");
    algComboBox->addItem("Средняя точка");
    algComboBox->addItem("Библиотечная функция");

    colorLabel = new QLabel("Выбор цвета");
    colorComboBox = new QComboBox;
    colorComboBox->addItem("Черный");
    colorComboBox->addItem("Красный");
    colorComboBox->addItem("Зеленый");
    colorComboBox->addItem("Синий");
    colorComboBox->addItem("Белый");

    circleLabel = new QLabel("Окружность");
    circleXEdit = new QLineEdit;
    circleXEdit->setPlaceholderText("x");
    circleYEdit = new QLineEdit;
    circleYEdit->setPlaceholderText("y");
    circleREdit = new QLineEdit;
    circleREdit->setPlaceholderText("R");
    drawCircleButton = new QPushButton("Построить окружность");

    ellipseLabel = new QLabel("Эллипс");
    ellipseXEdit = new QLineEdit;
    ellipseXEdit->setPlaceholderText("x");
    ellipseYEdit = new QLineEdit;
    ellipseYEdit->setPlaceholderText("y");
    ellipseAEdit = new QLineEdit;
    ellipseAEdit->setPlaceholderText("a");
    ellipseBEdit = new QLineEdit;
    ellipseBEdit->setPlaceholderText("b");
    drawEllipseButton = new QPushButton("Построить эллипс");

    circleSetLabel = new QLabel("Пучок окружностей");
    circleSetREdit = new QLineEdit;
    circleSetREdit->setPlaceholderText("Start R");
    circleSetNEdit = new QLineEdit;
    circleSetNEdit->setPlaceholderText("N");
    circleSetStepEdit = new QLineEdit;
    circleSetStepEdit->setPlaceholderText("Step");
    drawCircleSetButton = new QPushButton("Построить пучок");

    ellipseSetLabel = new QLabel("Пучок эллипсов");
    ellipseSetAEdit = new QLineEdit;
    ellipseSetAEdit->setPlaceholderText("A");
    ellipseSetBEdit = new QLineEdit;
    ellipseSetBEdit->setPlaceholderText("B");
    ellipseSetNEdit = new QLineEdit;
    ellipseSetNEdit->setPlaceholderText("N");
    ellipseSetStepEdit = new QLineEdit;
    ellipseSetStepEdit->setPlaceholderText("Step");
    drawEllipseSetButton = new QPushButton("Построить пучок");

    undoButton = new QPushButton("Назад");
    clearAllButton = new QPushButton("Очистить");

    showTimeButton = new QPushButton("Замерить время");
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
    grid->addWidget(circleSetLabel);
    grid->addWidget(circleSetREdit);
    grid->addWidget(circleSetNEdit);
    grid->addWidget(circleSetStepEdit);
    grid->addWidget(drawCircleSetButton);
    grid->addWidget(ellipseSetLabel);
    grid->addWidget(ellipseSetAEdit);
    grid->addWidget(ellipseSetBEdit);
    grid->addWidget(ellipseSetNEdit);
    grid->addWidget(ellipseSetStepEdit);
    grid->addWidget(drawEllipseSetButton);
    grid->addWidget(undoButton);
    grid->addWidget(clearAllButton);
    grid->addWidget(showTimeButton);
}

void Lab4Dock::connectHandlers()
{
    connect(drawEllipseButton, SIGNAL(released()),
            this, SLOT(onDrawEllipseButtonClick()));
    connect(drawEllipseSetButton, SIGNAL(released()),
            this, SLOT(onDrawEllipseSetButtonClick()));
    connect(drawCircleButton, SIGNAL(released()),
            this, SLOT(onDrawCircleButtonClick()));
    connect(undoButton, SIGNAL(released()),
            this, SLOT(onUndoButtonClick()));
    connect(showTimeButton, SIGNAL(released()),
            this, SLOT(onTimeButtonCLick()));
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

void Lab4Dock::onDrawEllipseSetButtonClick()
{
    int a, b, n, step;

    try
    {
        a = Converter::toInt(ellipseSetAEdit->text());
        b = Converter::toInt(ellipseSetBEdit->text());
        n = Converter::toInt(ellipseSetNEdit->text());
        step = Converter::toInt(ellipseSetStepEdit->text());

        int color = colorComboBox->currentIndex();
        int alg = algComboBox->currentIndex();

        invoker->addEllipseSet(a, b, n, step, color, alg);
    }
    catch (ConvertException &exception)
    {
        invoker->showWarning(exception.what());
    }
}

void Lab4Dock::onDrawCircleButtonClick()
{
    int x, y, r;

    try
    {
        x = Converter::toInt(circleXEdit->text());
        y = Converter::toInt(circleYEdit->text());
        r = Converter::toInt(circleREdit->text());

        int color = colorComboBox->currentIndex();
        int alg = algComboBox->currentIndex();

        invoker->addCircle(x, y, r, color, alg);
    }
    catch (ConvertException &exception)
    {
        invoker->showWarning(exception.what());
    }
}

void Lab4Dock::onUndoButtonClick()
{
    invoker->undo();
}

void Lab4Dock::onTimeButtonCLick()
{
    invoker->measureTime();
}
