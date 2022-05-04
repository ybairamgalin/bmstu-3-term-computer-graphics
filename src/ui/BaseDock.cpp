#include "BaseDock.h"

BaseDock::BaseDock(QWidget *parent) : QDockWidget(parent)
{
    multiWidget = new QWidget();
    multiWidget->setMaximumHeight(maxHeight);

    grid = new QGridLayout(multiWidget);
    setWidget(multiWidget);
}
