#ifndef LAB2DOCK_H
#define LAB2DOCK_H

#include <QObject>
#include <QDockWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>

#include <cmath>

#include "renderarea.h"

#ifndef MIN_DOCK_WIDTH
#define MIN_DOCK_WIDTH 250
#endif

class Lab2Dock : public QDockWidget
{
    Q_OBJECT
public:
    explicit Lab2Dock(RenderArea *renderArea,
                      QWidget *parent = nullptr);
    ~Lab2Dock();

private:
    QWidget *multiWidget;
    QGridLayout *grid;

    QLabel *descriptionLabel;
    QPushButton *showFigureButton;
    QPushButton *hideFigureButton;

    QLabel *transformationLabel;
    QLabel *dxTransformLabel;
    QLineEdit *dxEdit;
    QLabel *dyTransformLabel;
    QLineEdit *dyEdit;
    QPushButton *transformButton;

    QLabel *scaleLabel;
    QLabel *kxScaleLabel;
    QLineEdit *kxEdit;
    QLabel *kyScaleLabel;
    QLineEdit *kyEdit;
    QPushButton *scaleButton;

    QLabel *rotationLabel;
    QLabel *angleLabel;
    QLineEdit *rotationEdit;
    QPushButton *rotationButton;

    QLabel *centerLabel;
    QLabel *xCenterLabel;
    QLineEdit *xCenterEdit;
    QLabel *yCenterLabel;
    QLineEdit *yCenterEdit;
    QPushButton *setCenterButton;

    QPushButton *goBackButton;
    QPushButton *restoreImgButton;

    RenderArea *renderArea;

    void createGrid();

private slots:
    void onShowFigureButtonClick();
    void onTransformButtonClick();
    void onScaleButtonClick();
    void onSetCenterButtonClick();
    void onRotationButtonClick();
    void onGoBackButtonClick();
    void onRestoreImgButtonCLick();
    void onShowFigureButtonCLick();
    void onHideFigureButtonClick();
};

#endif // LAB2DOCK_H
