#ifndef BASEDOCK_H
#define BASEDOCK_H

#include <QDockWidget>
#include <QGridLayout>

#include <memory>

class BaseDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit BaseDock(QWidget *parent = nullptr);

protected:
    int maxHeight = 650;

    QGridLayout *grid;
private:
    QWidget *multiWidget;
};


#endif //BASEDOCK_H
