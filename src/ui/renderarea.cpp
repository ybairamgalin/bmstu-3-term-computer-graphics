#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget{parent}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lastMousePress = QPoint(0, 0);
    curDeltaVector = QPoint(0, 0);
    curDeltaVector = QPoint(0, 0);

    if (parent)
        canvasSize = parent->size();
    else
        canvasSize = QSize(1000, 600);
}

RenderArea::~RenderArea() { }

void RenderArea::resize(QSize newSize)
{
    canvasSize = newSize;
    update();
}

void RenderArea::setMousePress(QPoint point)
{
    lastMousePress = point;
}

void RenderArea::setDelta(QPoint newPoint)
{
    curDeltaVector.setX(newPoint.x() - lastMousePress.x());
    curDeltaVector.setY(-newPoint.y() + lastMousePress.y());
    update();
}

void RenderArea::drawMyLines()
{
    QPoint delta = curDeltaVector + oldDeltaVector;

    Line::setDelta(delta);
    Line::setScale(scaleFactor);

    QPainter painter(this);
    painter.translate(toCanvasCoords(delta));
    painter.scale(2, -2);

    for (size_t i = 0; i < myLines.size(); i++)
        myLines[i]->draw(painter, QColor(Qt::red));
}

void RenderArea::paintEvent(QPaintEvent*)
{
    QPoint delta = curDeltaVector + oldDeltaVector;

    drawBg(delta);

    QPainter painter(this);

    QPen pen = QPen();
    pen.setWidth(3);
    pen.setBrush(QColor(63, 136, 71));
    painter.setPen(pen);

    for (size_t i = 0; i < lines.size(); i++)
    {
        painter.drawLine(QLine(toCanvasCoords(QPointF(lines[i].p1().x() * scaleFactor + delta.x(),
                                                      lines[i].p1().y() * scaleFactor + delta.y())),
                               toCanvasCoords(QPointF(lines[i].p2().x() * scaleFactor + delta.x(),
                                                      lines[i].p2().y() * scaleFactor + delta.y()))));
    }

    painter.setPen(QColor(184, 48, 48));
    painter.setBrush(QColor(184, 48, 48));

    for (size_t i = 0; i < points.size(); i++)
    {
        painter.drawEllipse(toCanvasCoords(QPointF(points[i].x() * scaleFactor + delta.x(),
                                                  points[i].y() * scaleFactor + delta.y())),
                            pointRadius, pointRadius);
    }

    painter.setPen(QColor(37, 91, 164));
    painter.setBrush(QColor(37, 91, 164));

    for (size_t i = 0; i < bluePoints.size(); i++)
    {
        painter.drawEllipse(toCanvasCoords(QPointF(bluePoints[i].x() * scaleFactor + delta.x(),
                                                  bluePoints[i].y() * scaleFactor + delta.y())),
                            pointRadius, pointRadius);
    }

    drawFigures();
    drawMyLines();

    QPainter newPainter(this);
    newPainter.translate(toCanvasCoords(delta));
    newPainter.scale(1, -1);

    for (const auto &element: drawable)
        element->draw(newPainter);
}

void RenderArea::drawBg(QPoint delta)
{
    QPainter painter(this);

    painter.setPen(QColor(217, 217, 217));

    const int drawArea = 1000;

    painter.setBrush(QColor(245, 245, 245));
    painter.drawRect(0, 0, drawArea * 2, drawArea * 2);

    // grid
    painter.setPen(QColor(207, 207, 207));

    for (int i = 0;
            i * scaleFactor * multiple / SCREENS_GRID <= (canvasSize.height() > canvasSize.width() ?
                                           canvasSize.height() : canvasSize.width());
            i++)
    {
        painter.drawLine(toCanvasCoords(QPoint(i* scaleFactor * multiple + delta.x(),
                                               canvasSize.height() / 2 + 1)),
                         toCanvasCoords(QPoint(i* scaleFactor * multiple + delta.x(),
                                               -canvasSize.height() / 2 - 1)));
        painter.drawLine(toCanvasCoords(QPoint(-i* scaleFactor * multiple + delta.x(),
                                               canvasSize.height() / 2 + 1)),
                         toCanvasCoords(QPoint(-i* scaleFactor * multiple + delta.x(),
                                               -canvasSize.height() / 2 - 1)));

        painter.drawLine(toCanvasCoords(QPoint(canvasSize.width() / 2 + 1,
                                               i* scaleFactor * multiple + delta.y())),
                         toCanvasCoords(QPoint(-canvasSize.width() / 2 - 1,
                                               i* scaleFactor * multiple + delta.y())));
        painter.drawLine(toCanvasCoords(QPoint(canvasSize.width() / 2 + 1, -i
                                               * scaleFactor * multiple + delta.y())),
                         toCanvasCoords(QPoint(-canvasSize.width() / 2 - 1, -i
                                               * scaleFactor * multiple + delta.y())));
    }

    painter.setPen(QColor(125, 125, 125));

    for (int i = 0;
            i * scaleFactor * multiple / SCREENS_GRID <= (canvasSize.height() > canvasSize.width() ?
                                           canvasSize.height() : canvasSize.width());
            i++)
        if (i % 5 == 0)
        {
            painter.drawLine(toCanvasCoords(QPoint(i* scaleFactor * multiple + delta.x(),
                                                   canvasSize.height() / 2 + 1)),
                             toCanvasCoords(QPoint(i* scaleFactor * multiple + delta.x(),
                                                   -canvasSize.height() / 2 - 1)));
            painter.drawLine(toCanvasCoords(QPoint(-i* scaleFactor * multiple + delta.x(),
                                                   canvasSize.height() / 2 + 1)),
                             toCanvasCoords(QPoint(-i* scaleFactor * multiple + delta.x(),
                                                   -canvasSize.height() / 2 - 1)));

            painter.drawLine(toCanvasCoords(QPoint(canvasSize.width() / 2 + 1,
                                                   i* scaleFactor * multiple + delta.y())),
                             toCanvasCoords(QPoint(-canvasSize.width() / 2 - 1,
                                                   i* scaleFactor * multiple + delta.y())));
            painter.drawLine(toCanvasCoords(QPoint(canvasSize.width() / 2 + 1, -i
                                                   * scaleFactor * multiple + delta.y())),
                             toCanvasCoords(QPoint(-canvasSize.width() / 2 - 1, -i
                                                   * scaleFactor * multiple + delta.y())));
        }

    painter.setPen(QColor(0, 0, 0));

    // x axis
    painter.drawLine(toCanvasCoords(QPoint(delta.x(), canvasSize.height() / 2 + 1)),
                     toCanvasCoords(QPoint(delta.x(), -canvasSize.height() / 2 - 1)));

    // y axis
    painter.drawLine(toCanvasCoords(QPoint(canvasSize.width() / 2 + 1, delta.y())),
                     toCanvasCoords((QPoint(-canvasSize.width() / 2 - 1, delta.y()))));

    // numbers
    painter.setPen(QColor(0, 0, 0, 0));

    // zero
    painter.drawRect(QRect(toCanvasCoords(QPoint(-23 + delta.x(), -3 + delta.y())),
                           toCanvasCoords(QPoint(-3 + delta.x(), -18 + delta.y()))));

    painter.setPen(QColor(0, 0, 0, 255));
    painter.drawText(QRect(toCanvasCoords(QPoint(-23 + delta.x(), -3 + delta.y())),
                           toCanvasCoords(QPoint(-3 + delta.x(), -18 + delta.y()))),
                     Qt::AlignVCenter | Qt::AlignRight, QString::number(0));

    QPoint numberDelta = delta;

    if (delta.x() > canvasSize.width() / 2)
    {
        numberDelta.setX(canvasSize.width() / 2 - 20);
    }

    if (delta.x() < -canvasSize.width() / 2)
    {
        numberDelta.setX(-canvasSize.width() / 2 + 20);
    }

    if (delta.y() > canvasSize.height() / 2)
    {
        numberDelta.setY(canvasSize.height() / 2 - 20);
    }

    if (delta.y() < -canvasSize.height() / 2)
    {
        numberDelta.setY(-canvasSize.height() / 2 + 20);
    }

    for (int i = 1;
            i * scaleFactor * multiple / SCREENS_GRID < (canvasSize.height() > canvasSize.width() ?
                                          canvasSize.height() : canvasSize.width());
            i++)
    {
        if (i % 5 == 0)
        {
            int yPosV = -23;
            int xPosH = 15;

            if (i * multiple >= 10000)
            {
                yPosV -= 40;
                xPosH += 20;
            }
            else if (i * multiple >= 10000)
            {
                yPosV -= 30;
                xPosH += 15;
            }
            else if (i * multiple >= 1000)
            {
                yPosV -= 20;
                xPosH += 10;
            }
            else if (i * multiple >= 100)
            {
                yPosV -= 10;
                xPosH += 5;
            }
            else if (i * multiple < 0.01)
            {
                yPosV -= 10;
                xPosH += 5;
            }
            else if (i * multiple < 0.001)
            {
                yPosV -= 20;
                xPosH += 10;
            }


            // hotizontal
            painter.setPen(QColor(0, 0, 0, 0));
            painter.drawRect(QRect(toCanvasCoords(QPoint(yPosV + numberDelta.x(), scaleFactor * multiple * i + 10 + delta.y())),
                                   toCanvasCoords(QPoint(-3 + numberDelta.x(), scaleFactor * multiple * i - 10 + delta.y()))));
            painter.drawRect(QRect(toCanvasCoords(QPoint(yPosV + numberDelta.x(), -scaleFactor * multiple * i + 10 + delta.y())),
                                   toCanvasCoords(QPoint(-3 + numberDelta.x(), -scaleFactor * multiple * i - 10 + delta.y()))));

            painter.setPen(QColor(0, 0, 0, 255));
            painter.drawText(QRect(toCanvasCoords(QPoint(yPosV + numberDelta.x(), scaleFactor * multiple * i + 10 + delta.y())),
                                   toCanvasCoords(QPoint(-3 + numberDelta.x(), scaleFactor * multiple * i - 10 + delta.y()))),
                             Qt::AlignVCenter | Qt::AlignRight, QString::number(multiple * i));
            painter.drawText(QRect(toCanvasCoords(QPoint(yPosV + numberDelta.x(), -scaleFactor * multiple * i + 10 + delta.y())),
                                   toCanvasCoords(QPoint(-3 + numberDelta.x(), -scaleFactor * multiple * i - 10 + delta.y()))),
                             Qt::AlignVCenter | Qt::AlignRight, QString::number(-multiple * i));

            // vertical
            painter.setPen(QColor(0, 0, 0, 0));
            painter.drawRect(QRect(toCanvasCoords(QPoint(scaleFactor * multiple * i - xPosH + delta.x(), -3 + numberDelta.y())),
                                   toCanvasCoords(QPoint(scaleFactor * multiple * i + xPosH + delta.x(), -18 + numberDelta.y()))));
            painter.drawRect(QRect(toCanvasCoords(QPoint(-scaleFactor * multiple * i - xPosH + delta.x(), -3 + numberDelta.y())),
                                   toCanvasCoords(QPoint(-scaleFactor * multiple * i + xPosH + delta.x(), -18 + numberDelta.y()))));

            painter.setPen(QColor(0, 0, 0, 255));
            painter.drawText(QRect(toCanvasCoords(QPoint(scaleFactor * multiple * i - xPosH + delta.x(), -3 + numberDelta.y())),
                                   toCanvasCoords(QPoint(scaleFactor * multiple * i + xPosH + delta.x(), -18 + numberDelta.y()))),
                             Qt::AlignCenter, QString::number(multiple * i));
            painter.drawText(QRect(toCanvasCoords(QPoint(-scaleFactor * multiple * i - xPosH + delta.x(), -3 + numberDelta.y())),
                                   toCanvasCoords(QPoint(-scaleFactor * multiple * i + xPosH + delta.x(), -18 + numberDelta.y()))),
                             Qt::AlignCenter, QString::number(-multiple * i));
        }
    }
}

void RenderArea::drawFigures()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(184, 48, 48)));
    QPoint delta = curDeltaVector + oldDeltaVector;

    for (size_t i = 0; i < figures.size(); i++)
    {
        std::vector<Ellipse> ellipces = figures[i].getEllipces();

        for (size_t j = 0; j < ellipces.size(); j++)
        {
            std::vector<QPointF> points = ellipces[j].getPoints();

            for (size_t i = 0; i < points.size() - 1; i++)
            {
                painter.drawLine(toCanvasCoords(points[i] * scaleFactor + delta),
                                 toCanvasCoords(points[i + 1] * scaleFactor + delta));
            }

            painter.drawLine(toCanvasCoords(points[0] * scaleFactor + delta),
                             toCanvasCoords(points[points.size() - 1] * scaleFactor + delta));

//            std::vector<double> equation = ellipces[i].equation();
//            qDebug() << equation;

//            double A = equation[0];
//            double B = equation[1];
//            double C = equation[2];
//            double D = equation[3];
//            double E = equation[4];
//            double F = -equation[5];

//            double S = A + C;
//            double delta = A * C - (B / 2) * (B / 2);

//            double lamda1 = (S + sqrt(S * S - 4 * delta)) / (2);
//            double lamda2 = (S - sqrt(S * S - 4 * delta)) / (2);

//            double ellipseRotation = atan(C / (A - B)) / 2.0 * 180.0 / M_PI;
//            qDebug() << ellipseRotation;

//            double alpha = cos(ellipseRotation);
//            double beta = sin(ellipseRotation);

//            double newA = A * alpha * alpha + B * beta * beta + C * alpha * beta;
//            double newB = A * beta * beta + B * alpha * alpha - C * alpha * beta;
//            double newC = 0;
//            double newD = D * alpha + E * beta;
//            double newE = -D * beta + E * alpha;
//            double newF = F;

//            qDebug() << newA << newB << newC << newD << newE << newF;

//            if (newA < newB)
//            {
//                double tmp = newA;
//                newA = newB;
//                newB = tmp;

//                tmp = newD;
//                newD = newE;
//                newE = tmp;
//            }

//            double deltaX = -newD / (2.0 * newA);
//            newF -= (newD * newD) / (4.0 * newA);

//            double deltaY = -newE / (2.0 * newB);
//            newF -= (newE * newE) / (4.0 * newB);

//            qDebug() << deltaX << deltaY;

//            painter.translate(toCanvasCoords(QPointF(deltaX, deltaY) * scaleFactor + delta));
//            painter.rotate(-ellipseRotation);

//            painter.drawEllipse(QPointF(0, 0), sqrt(-newF / newA) * scaleFactor, sqrt(-newF / newB) * scaleFactor);

//            qDebug() << sqrt(-newF / newA) << sqrt(-newF / newB);

//            painter.rotate(ellipseRotation);
//            painter.translate(-toCanvasCoords(QPointF(deltaX, deltaY) * scaleFactor + delta));

//            double alpha2 = atan((lamda2 - A) / (B / 2));

//            qDebug() << alpha1 * 180 / 3.14 << alpha2 * 180 / 3.14;

//            double range1 = (-(2 * C * D - 4 * A * E) +
//                             sqrt((2 * C * D - 4 * A * E) * (2 * C * D - 4 * A * E) -
//                                  4 * (C - 4 * A * B) * (D * D - 4 * A * F))) /
//                            (2 * (C - 4 * A * B));
//            double range2 = (-(2 * C * D - 4 * A * E) -
//                             sqrt((2 * C * D - 4 * A * E) * (2 * C * D - 4 * A * E) -
//                                  4 * (C - 4 * A * B) * (D * D - 4 * A * F))) /
//                            (2 * (C - 4 * A * B));

//            double maxY = range1 >= range2 ? range1 : range2;
//            double minY = range1 < range2 ? range1 : range2;
//            double prevY = minY;
//            double prevX1 = (-(C * minY + D) + sqrt(((C * minY + D) * (C * minY + D) -
//                                                  4 * A * (B * minY * minY + E * minY + F)))) /
//                            (2 * A);
//            double prevX2 = (-(C * minY + D) - sqrt(((C * minY + D) * (C * minY + D) -
//                                                  4 * A * (B * minY * minY + E * minY + F)))) /
//                            (2 * A);

//            painter.drawLine(toCanvasCoords(QPointF(prevX1, prevY) * scaleFactor + delta),
//                             toCanvasCoords(QPointF(prevX2, prevY) * scaleFactor + delta));

//            for (double i = minY; i < maxY; i += 0.01)
//            {
//                double x1 = (-(C * i + D) + sqrt(((C * i + D) * (C * i + D) -
//                                                  4 * A * (B * i * i + E * i + F)))) /
//                            (2 * A);
//                double x2 = (-(C * i + D) - sqrt(((C * i + D) * (C * i + D) -
//                                                  4 * A * (B * i * i + E * i + F)))) /
//                            (2 * A);

//                painter.drawLine(toCanvasCoords(QPointF(x1, i) * scaleFactor + delta),
//                                 toCanvasCoords(QPointF(prevX1, prevY) * scaleFactor + delta));
//                painter.drawLine(toCanvasCoords(QPointF(x2, i) * scaleFactor + delta),
//                                 toCanvasCoords(QPointF(prevX2, prevY) * scaleFactor + delta));

//                prevX1 = x1;
//                prevX2 = x2;
//                prevY = i;
//            }
        }

        std::vector<QLineF> lines = figures[i].getLines();

        for (size_t j = 0; j < lines.size(); j++)
        {
            painter.drawLine(QLine(toCanvasCoords(QPointF(lines[j].p1().x() * scaleFactor + delta.x(),
                                                          lines[j].p1().y() * scaleFactor + delta.y())),
                                   toCanvasCoords(QPointF(lines[j].p2().x() * scaleFactor + delta.x(),
                                                          lines[j].p2().y() * scaleFactor + delta.y()))));
        }

        std::vector<Arc> arcs = figures[i].getArcs();

        for (size_t j = 0; j < arcs.size(); j++)
        {
            std::vector<QPointF> points = arcs[i].getPoints();

            for (size_t i = 0; i < points.size() - 1; i++)
                painter.drawLine(toCanvasCoords(points[i] * scaleFactor + delta),
                                 toCanvasCoords(points[i + 1] * scaleFactor + delta));
        }

        painter.setPen(QColor(37, 91, 164));
        painter.setBrush(QColor(37, 91, 164));
        painter.drawEllipse(toCanvasCoords(figures[i].getCenter() * scaleFactor + delta),
                            pointRadius, pointRadius);
    }
}

QPoint RenderArea::toCanvasCoords(const QPoint point)
{
    return QPoint(canvasSize.width() / 2 + point.x(),
                  canvasSize.height() / 2 - point.y());
}

QPoint RenderArea::toCanvasCoords(const QPointF point)
{
    return QPoint(canvasSize.width() / 2 + point.x(),
                  canvasSize.height() / 2 - point.y());
}

QPoint RenderArea::toNormalCoords(const QPoint point)
{
    return QPoint(point.x() - canvasSize.width() / 2,
                  -point.y() + canvasSize.height() / 2);
}

void RenderArea::addPoint(const double x, const double y)
{
    points.push_back(QPointF(x, y));
    update();
}

void RenderArea::addPoint(const QPointF point)
{
    points.push_back(point);
    update();
}

void RenderArea::scaleUp()
{
    scaleFactor *= scaleUpMultiple;

    if (scaleFactor * multiple > maxGridUnitSz)
    {
        phase--;

        if (phase % totalPhases == 0)
            multiple /= onPhaseMultiple;
        else
            multiple /= offPhaseMultiple;
    }

    update();
}

void RenderArea::scaleDown()
{
    if (scaleFactor * scaleDownMultiple <= EPS)
    {
        QMessageBox::warning(this, "Warning", "Слишком мелкий масштаб");
        return;
    }

    scaleFactor *= scaleDownMultiple;

    if (scaleFactor * multiple < minGridUnitSz)
    {
        if (phase % totalPhases == 0)
            multiple *= onPhaseMultiple;
        else
            multiple *= offPhaseMultiple;

        phase++;
    }

    update();
}

size_t RenderArea::pointsSz()
{
    return points.size();
}

Figure &RenderArea::figure()
{
    if (figures.size() == 0)
        throw;

    return figures[0];
}

void RenderArea::updateDelta()
{
    oldDeltaVector += curDeltaVector;
    curDeltaVector = QPoint(0, 0);
    qDebug() << "MOVED TO "<< oldDeltaVector;
}

void RenderArea::addLine(const QLineF line)
{
    lines.push_back(line);
    update();
}

QLine RenderArea::toCanvasCoords(const QLineF line)
{
    return QLine(toCanvasCoords(line.p1()),
                 toCanvasCoords(line.p2()));
}

void RenderArea::addBLuePoint(const QPointF point)
{
    bluePoints.push_back(point);
    update();
}

void RenderArea::clearLines()
{
    lines.clear();
    update();
}

void RenderArea::clearPoints()
{
    points.clear();
    update();
}

void RenderArea::clearBluePoints()
{
    bluePoints.clear();
    update();
}

void RenderArea::setCentralPoint(QPointF point)
{
    qDebug() << "GIVEN " << point;
    qDebug() << "TO COORDS " << toCanvasCoords(point);
    oldDeltaVector = QPoint(-point.x() * scaleFactor * multiple,
                            -point.y() * scaleFactor * multiple);
    update();
}

void RenderArea::setPoints(const std::vector<QPointF> newPoints)
{
    points.clear();
    points = newPoints;
    update();
}

void RenderArea::showFigure()
{
    figures.push_back(Figure());
    update();
}

void RenderArea::clearFigures()
{
    figures.clear();
    update();
}

bool RenderArea::figureIsShown()
{
    if (figures.size() > 0)
        return true;

    return false;
}

void RenderArea::addMyLine(Line *myLine)
{
    myLines.push_back(myLine);
    update();
}

void RenderArea::clearMyLines()
{
    myLines.clear();
    update();
}

void RenderArea::add(const IDrawable *element)
{
    drawable.push_back(element);
    update();
}

void RenderArea::pop()
{
    drawable.pop_back();
    update();
}
