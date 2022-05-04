#include "Lab4Dock.h"

Lab4Dock::Lab4Dock(QWidget *parent) : BaseDock(parent)
{
    createFields();
    placeFields();
}

void Lab4Dock::createFields()
{
    description = new QLabel("Лабораторная работа 4");
}

void Lab4Dock::placeFields()
{
    grid->addWidget(description, 0, 0);
}
