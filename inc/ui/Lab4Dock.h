#ifndef LAB4DOCK_H
#define LAB4DOCK_H

#include "BaseDock.h"

#include <QLabel>

class Lab4Dock : public BaseDock
{
    Q_OBJECT

public:
    explicit Lab4Dock(QWidget *parent = nullptr);

private:
    QLabel *description{};

    void createFields();
    void placeFields();
};

#endif // LAB4DOCK_H
