#include "lab2dock.h"

Lab2Dock::Lab2Dock(RenderArea *renderArea, QWidget *parent) : QDockWidget{parent},
    renderArea(renderArea)
{
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setMinimumWidth(MIN_DOCK_WIDTH);
    setWindowTitle("Лабораторная работа 2");

    descriptionLabel = new QLabel("Задание: выполнить перенос, "
                                  "масштабирование, вращение "
                                  "заданной фигуры");
    descriptionLabel->setWordWrap(true);

    showFigureButton = new QPushButton("Показать фигуру");
    hideFigureButton = new QPushButton("Очистить");

    transformationLabel = new QLabel("Перенос");
    dxTransformLabel = new QLabel("dx");
    dxEdit = new QLineEdit;
    dyTransformLabel = new QLabel("dy");
    dyEdit = new QLineEdit;
    transformButton = new QPushButton("Выполнить перенос");

    scaleLabel = new QLabel("Масштабирование");
    kxScaleLabel = new QLabel("kx");
    kxEdit = new QLineEdit;
    kyScaleLabel = new QLabel("ky");
    kyEdit = new QLineEdit;
    scaleButton = new QPushButton("Выполнить масштабирование");

    rotationLabel = new QLabel("Поворот");
    angleLabel = new QLabel("Угол");
    rotationEdit = new QLineEdit;
    rotationButton = new QPushButton("Выполнить поворот");

    centerLabel = new QLabel("Центр преобразований");
    xCenterLabel = new QLabel("x");
    xCenterEdit = new QLineEdit;
    yCenterLabel = new QLabel("y");
    yCenterEdit = new QLineEdit;
    setCenterButton = new QPushButton("Установить центр преобразований");

    goBackButton = new QPushButton("Назад");
    restoreImgButton = new QPushButton("Сброс");

    createGrid();

    connect(transformButton, SIGNAL(released()), this, SLOT(onTransformButtonClick()));
    connect(scaleButton, SIGNAL(released()), this, SLOT(onScaleButtonClick()));
    connect(setCenterButton, SIGNAL(released()), this, SLOT(onSetCenterButtonClick()));
    connect(rotationButton, SIGNAL(released()), this, SLOT(onRotationButtonClick()));
    connect(goBackButton, SIGNAL(released()), this, SLOT(onGoBackButtonClick()));
    connect(restoreImgButton, SIGNAL(released()), this, SLOT(onRestoreImgButtonCLick()));
    connect(showFigureButton, SIGNAL(released()), this, SLOT(onShowFigureButtonCLick()));
    connect(hideFigureButton, SIGNAL(released()), this, SLOT(onHideFigureButtonClick()));
}

Lab2Dock::~Lab2Dock()
{

}

void Lab2Dock::createGrid()
{
    multiWidget = new QWidget;
    multiWidget->setMaximumHeight(650);
    grid = new QGridLayout(multiWidget);

    grid->addWidget(descriptionLabel, 0, 0, 1, 2);
    grid->addWidget(showFigureButton, 1, 0);
    grid->addWidget(hideFigureButton, 1, 1);
    grid->addWidget(transformationLabel, 2, 0, 1, 2);
    grid->addWidget(dxTransformLabel, 3, 0);
    grid->addWidget(dxEdit, 3, 1);
    grid->addWidget(dyTransformLabel, 4, 0);
    grid->addWidget(dyEdit, 4, 1);
    grid->addWidget(transformButton, 5, 0, 1, 2);

    grid->addWidget(scaleLabel, 6, 0, 1, 2);
    grid->addWidget(kxScaleLabel, 7, 0);
    grid->addWidget(kxEdit, 7, 1);
    grid->addWidget(kyScaleLabel, 8, 0);
    grid->addWidget(kyEdit, 8, 1);
    grid->addWidget(scaleButton, 9, 0, 1, 2);

    grid->addWidget(rotationLabel, 10, 0, 1, 2);
    grid->addWidget(angleLabel, 11, 0);
    grid->addWidget(rotationEdit, 11, 1);
    grid->addWidget(rotationButton, 12, 0, 1, 2);

    grid->addWidget(centerLabel, 13, 0, 1, 2);
    grid->addWidget(xCenterLabel, 14, 0);
    grid->addWidget(xCenterEdit, 14, 1);
    grid->addWidget(yCenterLabel, 15, 0);
    grid->addWidget(yCenterEdit, 15, 1);
    grid->addWidget(setCenterButton, 16, 0, 1, 2);

    grid->addWidget(goBackButton, 17, 0, 1, 2);
    grid->addWidget(restoreImgButton, 18, 0, 1, 2);

    setWidget(multiWidget);
}

void Lab2Dock::onShowFigureButtonClick()
{

}

void Lab2Dock::onTransformButtonClick()
{
    if (!renderArea->figureIsShown())
    {
        QMessageBox::warning(this, "Warning", "Включите отображение");
        return;
    }

    bool converted = true;
    double dx = dxEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте dx");
        return;
    }

    double dy = dyEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте dy");
        return;
    }

    renderArea->figure().translate(dx, dy);
    renderArea->update();
}

void Lab2Dock::onScaleButtonClick()
{
    if (!renderArea->figureIsShown())
    {
        QMessageBox::warning(this, "Warning", "Включите отображение");
        return;
    }

    bool converted = true;
    double kx = kxEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте kx");
        return;
    }

    double ky = kyEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте ky");
        return;
    }

    renderArea->figure().scale(kx, ky);
    renderArea->update();
}

void Lab2Dock::onSetCenterButtonClick()
{
    if (!renderArea->figureIsShown())
    {
        QMessageBox::warning(this, "Warning", "Включите отображение");
        return;
    }

    bool converted = true;
    double x = xCenterEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте x");
        return;
    }

    double y = yCenterEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте y");
        return;
    }

    renderArea->figure().setCenter(QPointF(x, y));
    renderArea->update();
}

void Lab2Dock::onRotationButtonClick()
{
    if (!renderArea->figureIsShown())
    {
        QMessageBox::warning(this, "Warning", "Включите отображение");
        return;
    }

    bool converted = true;
    double angleDegrees = rotationEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте угол");
        return;
    }

    double angleRad = angleDegrees * (M_PI) / 180;

    renderArea->figure().rotate(angleRad);
    renderArea->update();
}

void Lab2Dock::onGoBackButtonClick()
{
    renderArea->figure().goBack();
    renderArea->update();
}

void Lab2Dock::onRestoreImgButtonCLick()
{
    renderArea->figure().reset();
    renderArea->update();
}

void Lab2Dock::onShowFigureButtonCLick()
{
    renderArea->showFigure();
}

void Lab2Dock::onHideFigureButtonClick()
{
    renderArea->clearFigures();
}
