#include "lab3dock.h"

void Lab3Dock::createFields()
{
    algorithmLabel = new QLabel("Метод разложения");
    algorithmComboBox = new QComboBox;
    algorithmComboBox->addItem("Первый");
    algorithmComboBox->addItem("Второй");
    colorLabel = new QLabel("Цвет линий");
    colorComboBox = new QComboBox;
    colorComboBox->addItem("Черный");
    colorComboBox->addItem("Не черный");

    drawLineLabel = new QLabel("Координаты линии");
    x1Edit = new QLineEdit;
    x1Edit->setPlaceholderText("x1");
    y1Edit = new QLineEdit;
    y1Edit->setPlaceholderText("y1");
    x2Edit = new QLineEdit;
    x2Edit->setPlaceholderText("x2");
    y2Edit = new QLineEdit;
    y2Edit->setPlaceholderText("y2");
    drawLineButton = new QPushButton("Добавить линию");

    drawSunLabel = new QLabel("Рисование пучка");
    sunLinesEdit = new QLineEdit;
    sunLinesEdit->setPlaceholderText("Количество линий пучка");
    sunLineLngEdit = new QLineEdit;
    sunLineLngEdit->setPlaceholderText("Длина линий пучка");
    sunXEdit = new QLineEdit;
    sunXEdit->setPlaceholderText("Центр пучка - x");
    sunYEdit = new QLineEdit;
    sunYEdit->setPlaceholderText("Центр пучка - y");
    drawSunButton = new QPushButton("Нарисовать пучок");

    clearAllButton = new QPushButton("Очистить все");
}

void Lab3Dock::placeFields()
{
    multiWidget = new QWidget;
    multiWidget->setMaximumHeight(650);
    grid = new QGridLayout(multiWidget);

    grid->addWidget(algorithmLabel, 0, 0, 1, 2);
    grid->addWidget(algorithmComboBox, 1, 0, 1, 2);
    grid->addWidget(colorLabel, 2, 0, 1, 2);
    grid->addWidget(colorComboBox, 3, 0, 1, 2);

    grid->addWidget(drawLineLabel, 4, 0, 1, 2);
    grid->addWidget(x1Edit, 5, 0);
    grid->addWidget(y1Edit, 5, 1);
    grid->addWidget(x2Edit, 6, 0);
    grid->addWidget(y2Edit, 6, 1);
    grid->addWidget(drawLineButton, 7, 0, 1, 2);

    grid->addWidget(drawSunLabel, 8, 0, 1, 2);
    grid->addWidget(sunLinesEdit, 9, 0, 1, 2);
    grid->addWidget(sunLineLngEdit, 10, 0, 1, 2);
    grid->addWidget(sunXEdit, 11, 0, 1, 2);
    grid->addWidget(sunYEdit, 12, 0, 1, 2);
    grid->addWidget(drawSunButton, 13, 0, 1, 2);

    grid->addWidget(clearAllButton, 14, 0, 1, 2);

    setWidget(multiWidget);
}

Lab3Dock::Lab3Dock(QWidget *parent) : QDockWidget{parent}
{
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setMinimumWidth(MIN_DOCK_WIDTH);
    setWindowTitle("Лабораторная работа 3");

    createFields();
    placeFields();
}

Lab3Dock::~Lab3Dock()
{

}
