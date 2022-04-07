#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Лабораторная работа 1 | Копьютерная графика");
    setMinimumSize(QSize(startWidth, startHeight));

    createDockWindowAddPoint();
    createDockWindowScale();

    createDockWindowLab1();
    createDockWindowListOfPoints();
    createDockChangePoint();

    renderArea = new RenderArea;
    setCentralWidget(renderArea);
    lab2Dock = new Lab2Dock(renderArea, this);
    lab3Dock = new Lab3Dock(this);

    Line *line = new Line(QPointF(0, 0), QPointF(100, 50), new LineDrawerLibFunc);
    Line *CDALine = new Line (QPointF(0, 10), QPointF(100, 60), new LineDrawerCda);
    Line *brFloat = new Line(QPointF(0, 20), QPointF(100, 70), new LineDrawerBresenhamFloat);
    Line *brInt = new Line(QPointF(0, 30), QPointF(100, 80), new LineDrawerBresenhamInt);
    Line *brSmooth = new Line(QPointF(0, 40), QPointF(100, 90), new LineDrawerBresenhamSmooth);
    Line *wu = new Line(QPointF(0, 50), QPointF(100, 100), new LineDrawerWu);

    renderArea->addMyLine(line);
    renderArea->addMyLine(CDALine);
    renderArea->addMyLine(brFloat);
    renderArea->addMyLine(brInt);
    renderArea->addMyLine(brSmooth);
    renderArea->addMyLine(wu);


    setNeededDocks();

    connect(addPointButton, SIGNAL(released()), this, SLOT(onAddPointButtonClick()));
    connect(scaleUpButton, SIGNAL(released()), this, SLOT(onScaleUpButtonClick()));
    connect(scaleDownButton, SIGNAL(released()), this, SLOT(onScaleDownButtonClick()));
    connect(solveButton, SIGNAL(released()), this, SLOT(onSolveButtonClick()));
    connect(clearAllPointsButton, SIGNAL(released()), this, SLOT(onClearAllPointsButtonClick()));
    connect(clearSolutionButton, SIGNAL(released()), this, SLOT(onClearSolutionButtonClick()));
    connect(deletePointButton, SIGNAL(released()), this, SLOT(onDeletePointButtonCLick()));
    connect(changePointButton, SIGNAL(released()), this, SLOT(onChangePointButtonClick()));
    connect(changePointAcceptButton, SIGNAL(released()), this, SLOT(onChangePointAcceptButton()));
    connect(changePointRejectButton, SIGNAL(released()), this, SLOT(onChangePointRejectButton()));

//    connect(addPointDock, &QDockWidget::topLevelChanged, this, &MainWindow::onDockLevelChange);
//    connect(listOfPointsDock, &QDockWidget::topLevelChanged, this, &MainWindow::onDockLevelChange);
//    connect(scaleDock, &QDockWidget::topLevelChanged, this, &MainWindow::onDockLevelChange);
//    connect(lab1Dock, &QDockWidget::topLevelChanged, this, &MainWindow::onDockLevelChange);
}

void MainWindow::onDockLevelChange(bool)
{
    // TODO
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDockWindowLab1()
{
    lab1Dock = new QDockWidget("Лабораторная работа 1", this);
    scaleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    scaleDock->setMinimumWidth(MIN_DOCK_WIDTH);

    lab1InfoLabel = new QLabel("Задание: из заданного множества точек найти 3 такие, "
                               "что точка переcечения биссектрис треeгольника, построенного "
                               "на этих трех точках будет иметь минимальную сумму расстояний "
                               "до осей координат.");
    lab1InfoLabel->setWordWrap(true);

    solveButton = new QPushButton("Решить");
    clearSolutionButton = new QPushButton("Очистить решение");

    QWidget *multiWidget = new QWidget;
    multiWidget->setMaximumHeight(210);
    QGridLayout *grid = new QGridLayout(multiWidget);

    grid->addWidget(lab1InfoLabel, 0, 0, Qt::AlignCenter);
    grid->addWidget(solveButton, 1, 0);
    grid->addWidget(clearSolutionButton, 2, 0);

    lab1Dock->setWidget(multiWidget);
}

void MainWindow::createDockWindowScale()
{
    scaleDock = new QDockWidget("Масштаб", this);
    scaleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    scaleDock->setMinimumWidth(MIN_DOCK_WIDTH);

    scaleLabel = new QLabel("Масштаб");

    scaleUpButton = new QPushButton("+");
    scaleDownButton = new QPushButton("-");

    QWidget *multiWidget = new QWidget;
    multiWidget->setMaximumHeight(110);
    QGridLayout *grid = new QGridLayout(multiWidget);

    grid->addWidget(scaleLabel, 0, 0, Qt::AlignCenter);

    grid->addWidget(scaleUpButton, 1, 0, 1, 1);
    grid->addWidget(scaleDownButton, 2, 0, 1, 1);

    scaleDock->setWidget(multiWidget);
}

void MainWindow::createDockChangePoint()
{
    changePointDock = new QDockWidget("Изменение координат");

    addPointDock->setMinimumWidth(MIN_DOCK_WIDTH + 90);

    changePointLabel = new QLabel("Изменить точку");

    changeXEdit = new QLineEdit;
    changeYEdit = new QLineEdit;

    changePointAcceptButton = new QPushButton("Ок");
    changePointRejectButton = new QPushButton("Отмена");

    changePointAcceptButton->setAutoDefault(true);

    changeXEdit->setPlaceholderText("x");
    changeYEdit->setPlaceholderText("y");

    QWidget *multiWidget = new QWidget;
    multiWidget->setMaximumHeight(140);
    QGridLayout *grid = new QGridLayout(multiWidget);

    grid->addWidget(changePointLabel, 0, 0, 1, 2, Qt::AlignCenter);
    grid->addWidget(changeXEdit, 1, 0, 1, 2);
    grid->addWidget(changeYEdit, 2, 0, 1, 2);
    grid->addWidget(changePointAcceptButton, 3, 0);
    grid->addWidget(changePointRejectButton, 3, 1);

    changePointDock->setWidget(multiWidget);
    //
    //
}

void MainWindow::createDockWindowAddPoint()
{
    addPointDock = new QDockWidget("Параметры", this);
    addPointDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addPointDock->setMinimumWidth(MIN_DOCK_WIDTH);

    addPointLabel = new QLabel("Добавление точки");

    xLabel = new QLabel("x");
    yLabel = new QLabel("y");

    xEdit = new QLineEdit;
    yEdit = new QLineEdit;

    addPointButton = new QPushButton("Добавить точку");

    QWidget *multiWidget = new QWidget;
    multiWidget->setMaximumHeight(150);
    QGridLayout *grid = new QGridLayout(multiWidget);
    grid->addWidget(addPointLabel, 0, 0, 1, 2, Qt::AlignCenter);

    grid->addWidget(xLabel, 1, 0);
    grid->addWidget(xEdit, 1, 1);

    grid->addWidget(yLabel, 2, 0);
    grid->addWidget(yEdit, 2, 1);

    grid->addWidget(addPointButton, 3, 0, 1, 2);

    addPointDock->setWidget(multiWidget);
}

void MainWindow::createDockWindowListOfPoints()
{
    listOfPointsDock = new QDockWidget("Список точек", this);
    listOfPointsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listOfPointsDock->setMinimumWidth(MIN_DOCK_WIDTH);

    listOfPoints = new QListWidget;
    clearAllPointsButton = new QPushButton("Очистить список");
    deletePointButton = new QPushButton("Удалить выбранную точку");
    changePointButton = new QPushButton("Изменить коордикаты");

    QWidget *multiWidget = new QWidget;
    multiWidget->setMaximumHeight(210);
    QGridLayout *grid = new QGridLayout(multiWidget);

    grid->addWidget(listOfPoints, 0, 0);
    grid->addWidget(changePointButton, 1, 0);
    grid->addWidget(deletePointButton, 2, 0);
    grid->addWidget(clearAllPointsButton, 3, 0);

    listOfPointsDock->setWidget(multiWidget);

}

void MainWindow::resizeEvent(QResizeEvent*)
{
    renderArea->resize(centralWidget()->size());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    QPoint point = event->pos();
//    QPoint point = event->pos();
//    point.setX(point.x() - dockWindowList->width());
//    point = renderArea->toNormalCoords(point);

    renderArea->setDelta(event->pos());

//    statusBar()->showMessage(QString::number(point.x()) +
//                             ", " + QString::number(point.y()));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    renderArea->setMousePress(event->pos());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    renderArea->updateDelta();
}

void MainWindow::onAddPointButtonClick()
{
    bool converted = true;
    double x = xEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте координату x");
        return;
    }

    double y = yEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте координату y");
        return;
    }

    renderArea->addPoint(x, y);
    lab1Solver.addPoint(QPointF(x, y));
    listOfPoints->addItem(QString::number(renderArea->pointsSz()) + ".\t(" +
                          QString::number(x) + ", " + QString::number(y) + ")");

    xEdit->clear();
    yEdit->clear();
}

void MainWindow::updateListOfPoints()
{
    listOfPoints->clear();
    std::vector points = lab1Solver.getPoints();

    for (size_t i = 0; i < points.size(); i++)
    {
        listOfPoints->addItem(QString::number(i + 1) + ".\t(" +
                              QString::number(points[i].x()) + ", " +
                              QString::number(points[i].y()) + ")");
    }
}

void MainWindow::onScaleUpButtonClick()
{
    renderArea->scaleUp();
}

void MainWindow::onScaleDownButtonClick()
{
    renderArea->scaleDown();
}

void MainWindow::onSolveButtonClick()
{
    onClearSolutionButtonClick();
    lab1Solver.solve();

    QString message = lab1Solver.solutionMessage();

    if (lab1Solver.solution().size() != 0)
    {
        Triangle triangle = lab1Solver.solution()[0];
        message += "Треугольник (" +
                QString::number(triangle.getVertex(0).x()) + ", " +
                QString::number(triangle.getVertex(0).y()) + "), (" +
                QString::number(triangle.getVertex(1).x()) + ", " +
                QString::number(triangle.getVertex(1).y()) + "), (" +
                QString::number(triangle.getVertex(2).x()) + ", " +
                QString::number(triangle.getVertex(2).y()) + ")\n" +
                "Биссектрисы пересекаются в точке (" +
                QString::number(triangle.bisectressIntersection().x()) + ", " +
                QString::number(triangle.bisectressIntersection().y()) + ")\n" +
                "Сумма расстояний до осей " +
                QString::number(triangle.sumBisectressIntersectionCoords()) + "\n";

        QPointF intersection = triangle.bisectressIntersection();

        renderArea->addLine(QLineF(triangle.getVertex(0), triangle.getVertex(1)));
        renderArea->addLine(QLineF(triangle.getVertex(1), triangle.getVertex(2)));
        renderArea->addLine(QLineF(triangle.getVertex(2), triangle.getVertex(0)));

        renderArea->addLine(QLineF(triangle.getVertex(0), intersection));
        renderArea->addLine(QLineF(triangle.getVertex(1), intersection));
        renderArea->addLine(QLineF(triangle.getVertex(2), intersection));

        renderArea->addLine(QLineF(QPointF(0, intersection.y()), intersection));
        renderArea->addLine(QLineF(QPointF(intersection.x(), 0), intersection));

        renderArea->addBLuePoint(intersection);

        QPointF centralPoint = QPointF((triangle.minX() + triangle.maxX()) / 2,
                                       (triangle.minY() + triangle.maxY()) / 2);
        renderArea->setCentralPoint(centralPoint);

    }

    message += lab1Solver.degenerateMessage();

    QMessageBox::information(this, "Решение", message);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_Equal:
            onScaleUpButtonClick();
            break;
        case Qt::Key_Minus:
            onScaleDownButtonClick();
            break;
    }
}

void MainWindow::onClearSolutionButtonClick()
{
    renderArea->clearBluePoints();
    renderArea->clearLines();
}

void MainWindow::onClearAllPointsButtonClick()
{
    renderArea->clearPoints();
    listOfPoints->clear();
    lab1Solver.clearPoints();
}

void MainWindow::onDeletePointButtonCLick()
{
    if (listOfPoints->selectedItems().size() == 0)
    {
        qDebug() << "NOTHING SELECTED";
        return;
    }

    int row = listOfPoints->row(listOfPoints->selectedItems()[0]);

    lab1Solver.removePoint(row);
    updateListOfPoints();
    renderArea->setPoints(lab1Solver.getPoints());
}

void MainWindow::onChangePointButtonClick()
{
    if (listOfPoints->selectedItems().size() == 0)
    {
        qDebug() << "NOTHING SELECTED";
        return;
    }

    int row = listOfPoints->row(listOfPoints->selectedItems()[0]);
    QPointF pointToChange = lab1Solver.getPoints()[row];

    changePointLabel->setText("Изменить точку (" + QString::number(pointToChange.x()) + ", " +
                              QString::number(pointToChange.y()) + ")");

    QMessageBox mBox = QMessageBox(this);
    changePointDock->show();
}

void MainWindow::onChangePointRejectButton()
{
    changePointDock->hide();
}

void MainWindow::onChangePointAcceptButton()
{
    bool converted = true;
    double x = changeXEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте координату x");
        return;
    }

    double y = changeYEdit->text().toDouble(&converted);

    if (!converted)
    {
        QMessageBox::warning(this, "Warning", "Проверьте координату y");
        return;
    }

    int row = listOfPoints->row(listOfPoints->selectedItems()[0]);

    lab1Solver.removePoint(row);
    updateListOfPoints();
    renderArea->setPoints(lab1Solver.getPoints());

    renderArea->addPoint(x, y);
    lab1Solver.addPoint(QPointF(x, y));
    listOfPoints->addItem(QString::number(renderArea->pointsSz()) + ".\t(" +
                          QString::number(x) + ", " + QString::number(y) + ")");

    changeXEdit->clear();
    changeYEdit->clear();

    changePointDock->hide();
}

void MainWindow::setNeededDocks()
{
    // lab_01
    addDockWidget(Qt::LeftDockWidgetArea, lab1Dock);
    addDockWidget(Qt::RightDockWidgetArea, addPointDock);
    addDockWidget(Qt::LeftDockWidgetArea, listOfPointsDock);

    lab1Dock->hide();
    addPointDock->hide();
    listOfPointsDock->hide();

    // lab_02
    addDockWidget(Qt::LeftDockWidgetArea, lab2Dock);

    lab2Dock->hide();

    // lab_03
    addDockWidget(Qt::LeftDockWidgetArea, lab3Dock);

    // common
    addDockWidget(Qt::RightDockWidgetArea, scaleDock);

    scaleDock->hide();
}
