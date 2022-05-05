#include "BaseDock.h"

BaseDock::BaseDock(Invoker *invoker, QWidget *parent) :
        QDockWidget(parent), invoker(invoker)
{
    multiWidget = new QWidget();
    multiWidget->setMaximumHeight(maxHeight);

    grid = new QGridLayout(multiWidget);
    setWidget(multiWidget);
}
