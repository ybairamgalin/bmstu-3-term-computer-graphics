#ifndef BASEDOCK_H
#define BASEDOCK_H

#include <QDockWidget>
#include <QGridLayout>

#include <memory>

#include "Invoker.h"

class BaseDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit BaseDock(Invoker *invoker, QWidget *parent = nullptr);

protected:
    int maxHeight = 650;

    QGridLayout *grid;
    Invoker *invoker;
private:
    QWidget *multiWidget;
};


#endif //BASEDOCK_H
