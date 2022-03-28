#ifndef LAB3DOCK_H
#define LAB3DOCK_H

#include <QObject>
#include <QDockWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#ifndef MIN_DOCK_WIDTH
#define MIN_DOCK_WIDTH 250
#endif

class Lab3Dock : public QDockWidget
{
    Q_OBJECT
public:
    explicit Lab3Dock(QWidget *parent = nullptr);
    ~Lab3Dock();

private:
    QWidget *multiWidget;
    QGridLayout *grid;

    QLabel *algorithmLabel;
    QComboBox *algorithmComboBox;
    QLabel *colorLabel;
    QComboBox *colorComboBox;

    QLabel *drawLineLabel;
    QLineEdit *x1Edit;
    QLineEdit *y1Edit;
    QLineEdit *x2Edit;
    QLineEdit *y2Edit;
    QPushButton *drawLineButton;

    QLabel *drawSunLabel;
    QLineEdit *sunLinesEdit;
    QLineEdit *sunLineLngEdit;
    QLineEdit *sunXEdit;
    QLineEdit *sunYEdit;
    QPushButton *drawSunButton;

    QPushButton *clearAllButton;

    void createFields();
    void placeFields();
};

#endif // LAB3DOCK_H
