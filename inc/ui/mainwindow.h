#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QListWidget>
#include <QSize>
#include <QSizePolicy>
#include <QString>
#include <QPoint>
#include <QMessageBox>
#include <QAbstractButton>

#include "renderarea.h"
#include "triangle.h"
#include "lab1solver.h"
#include "lab2dock.h"
#include "lab3dock.h"
#include "Lab4Dock.h"
#include "linedrawer.h"
#include "Invoker.h"

#define MIN_DOCK_WIDTH 250

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDockWidget *addPointDock;
    QDockWidget *listOfPointsDock;
    QDockWidget *scaleDock;
    QDockWidget *lab1Dock;
    QDockWidget *changePointDock;
    QLabel *addPointLabel;
    QLabel *xLabel;
    QLabel *yLabel;
    QLabel *scaleLabel;
    QLabel *lab1InfoLabel;
    QLabel *changePointLabel;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *changeXEdit;
    QLineEdit *changeYEdit;
    QPushButton *addPointButton;
    QPushButton *scaleUpButton;
    QPushButton *scaleDownButton;
    QPushButton *solveButton;
    QPushButton *clearSolutionButton;
    QPushButton *clearAllPointsButton;
    QPushButton *deletePointButton;
    QPushButton *changePointButton;
    QPushButton *changePointAcceptButton;
    QPushButton *changePointRejectButton;
    QListWidget *listOfPoints;
    RenderArea *renderArea;

    Lab2Dock *lab2Dock;
    Lab3Dock *lab3Dock;
    Lab4Dock *lab4Dock;

    Invoker *invoker;

    Lab1Solver lab1Solver;

    void createDockWindowAddPoint();
    void createDockWindowListOfPoints();
    void createDockWindowScale();
    void createDockWindowLab1();
    void createDockChangePoint();
    void createAddPoint();

    void setNeededDocks();

    void updateListOfPoints();

    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;

    const int startWidth = 1200;
    const int startHeight = 800;

private slots:
    void onAddPointButtonClick();
    void onScaleUpButtonClick();
    void onScaleDownButtonClick();
    void onSolveButtonClick();
    void onClearSolutionButtonClick();
    void onClearAllPointsButtonClick();
    void onDeletePointButtonCLick();
    void onChangePointButtonClick();
    void onChangePointRejectButton();
    void onChangePointAcceptButton();
    void onDockLevelChange(bool change);
};
#endif // MAINWINDOW_H

