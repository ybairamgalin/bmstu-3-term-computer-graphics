#ifndef LAB5DOCK_H
#define LAB5DOCK_H

#include <QListWidget>
#include <QCheckBox>
#include <QComboBox>

#include "BaseDock.h"

class Lab5Dock : public BaseDock
{
    Q_OBJECT

public:
    explicit Lab5Dock(Invoker *invoker, QWidget *parent = nullptr);

private:
    QLabel *description;

    QLabel *colorLabel;
    QComboBox *colorComboBox;

    QListWidget *pointsList;

    QLabel *addPointLabel;
    QLineEdit *addPointXEdit;
    QLineEdit *addPointYEdit;
    QPushButton *addPointButton;
    QPushButton *deleteLastButton;

    QPushButton *drawButton;

    QCheckBox *delayBox;

    QPushButton *timeButton;
    QPushButton *clearScreenButton;

    void createFields();
    void placeFields();
    void connectHandlers();

private slots:
    void onAddPointButtonClick();
    void onClearScreenButtonClick();
};

#endif
