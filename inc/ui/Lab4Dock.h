#ifndef LAB4DOCK_H
#define LAB4DOCK_H

#include "BaseDock.h"
#include "Converter.h"
#include "lab4/Ellipse.h"

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>

class Lab4Dock : public BaseDock
{
    Q_OBJECT

public:
    explicit Lab4Dock(Invoker *invoker, QWidget *parent = nullptr);

private:
    QLabel *description;

    QLabel *algLabel;
    QComboBox *algComboBox;

    QLabel *colorLabel;
    QComboBox *colorComboBox;

    QLabel *circleLabel;
    QLineEdit *circleXEdit;
    QLineEdit *circleYEdit;
    QLineEdit *circleREdit;
    QPushButton *drawCircleButton;

    QLabel *ellipseLabel;
    QLineEdit *ellipseXEdit;
    QLineEdit *ellipseYEdit;
    QLineEdit *ellipseAEdit;
    QLineEdit *ellipseBEdit;
    QPushButton *drawEllipseButton;

    QLabel *circleSetLabel;
    QLineEdit *circleSetREdit;
    QLineEdit *circleSetNEdit;
    QLineEdit *circleSetStepEdit;
    QPushButton *drawCircleSetButton;

    QLabel *ellipseSetLabel;
    QLineEdit *ellipseSetAEdit;
    QLineEdit *ellipseSetBEdit;
    QLineEdit *ellipseSetNEdit;
    QLineEdit *ellipseSetStepEdit;
    QPushButton *drawEllipseSetButton;

    QPushButton *undoButton;
    QPushButton *clearAllButton;

    void createFields();
    void placeFields();
    void connectHandlers();

private slots:
    void onDrawEllipseButtonClick();
    void onDrawEllipseSetButtonClick();
    void onDrawCircleButtonClick();
    void onUndoButtonClick();
};

#endif // LAB4DOCK_H
