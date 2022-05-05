#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QObject>
#include <QWidget>
#include <QSizePolicy>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QRect>
#include <QMessageBox>
#include <QDebug>

#include <vector>
#include <math.h>

#include "figure.h"
#include "arc.h"
#include "ellipse.h"
#include "line.h"
#include "IDrawable.h"

#ifndef EPS
#define EPS 1e-7
#endif

// TODO optimize
#define SCREENS_GRID 4

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();

    void resize(QSize newSize);
    void setCentralPoint(QPointF point);

    QPoint toCanvasCoords(const QPoint point);
    QPoint toCanvasCoords(const QPointF point);
    QLine toCanvasCoords(const QLineF line);
    QPoint toNormalCoords(const QPoint point);

    void setPoints(const std::vector<QPointF> points);
    void addPoint(const double x, const double y);
    void addPoint(const QPointF point);
    void clearPoints();

    void addBLuePoint(const QPointF point);
    void clearBluePoints();

    void addLine(const QLineF line);
    void clearLines();

    void addMyLine(Line *myLine);
    void clearMyLines();

    bool figureIsShown();
    void showFigure();
    void clearFigures();

    void setMousePress(QPoint point);
    void setDelta(QPoint newPoint);
    void updateDelta();

    void scaleUp();
    void scaleDown();
    size_t pointsSz();

    void add(const IDrawable *element);
    void pop();

    Figure &figure();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QSize canvasSize;
    QPoint lastMousePress;
    QPoint curDeltaVector;
    QPoint oldDeltaVector;

    std::vector<QPointF> points;
    std::vector<QPointF> bluePoints;
    std::vector<QLineF> lines;
    std::vector<QRectF> ellipces;
    std::vector<Figure> figures;
    std::vector<Line*> myLines;

    std::vector<const IDrawable*> drawable;

    double scaleFactor = 20;
    // multiple to set up grid unit as
    // scaleFactor * multiple
    double multiple = 1;
    // phase of scaling
    int phase = 1;

    void drawBg(QPoint delta);
    void drawFigures();
    void drawMyLines();

    // two consts should eq to 1 when multiplied
    const double scaleUpMultiple = 1.25;
    const double scaleDownMultiple = 0.8;

    const int totalPhases = 3;

    const int maxGridUnitSz = 35;
    const int minGridUnitSz = 15;

    const double offPhaseMultiple = 2;
    const double onPhaseMultiple = 2.5;

    const int pointRadius = 4;

signals:

};

#endif // RENDERAREA_H
