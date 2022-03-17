#include "ellipse.h"

Ellipse::Ellipse(QPointF p1, QPointF p2, QPointF p3,
        QPointF p4, QPointF p5)
{
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
}

Ellipse::Ellipse(QPointF center, double rx, double ry)
{
    double step = (M_PI * 2.0) / pointsInEllipse;

    for (int i = 0; i < pointsInEllipse; i++)
        points.push_back(QPointF(rx * cos(i * step) + center.x(),
                                 ry * sin(i * step) + center.y()));
}

void Ellipse::translate(double dx, double dy)
{
    for (size_t i = 0; i < points.size(); i++)
        points[i] = translatePoint(points[i], dx, dy);
}

QPointF Ellipse::translatePoint(QPointF point, double dx, double dy)
{
    return QPointF(point.x() + dx, point.y() + dy);
}

void Ellipse::scale(QPointF center, double kx, double ky)
{
    for (size_t i = 0; i < points.size(); i++)
        points[i] = QPointF((points[i].x() - center.x()) * kx + center.x(),
                            (points[i].y() - center.y()) * ky + center.y());
}

void Ellipse::rotate(QPointF center, double angle)
{
    for (size_t i = 0; i < points.size(); i++)
    {
        QPointF newPoint = points[i] - center;
        newPoint = QPointF(newPoint.x() * cos(angle) - newPoint.y() * sin(angle),
                           newPoint.x() * sin(angle) + newPoint.y() * cos(angle));
        newPoint += center;
        points[i] = newPoint;
    }
}

int Ellipse::gauss (std::vector<std::vector<double>> a, std::vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    const double EPS = 1e-6;
    const double INF = 2;

    std::vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
        {
            double tmp = a[sel][i];
            a[sel][i] = a[row][i];
            a[row][i] = tmp;
        }
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

std::vector<double> Ellipse::equation()
{
    // returns (A, B, C, ...) of Ax^2 + By^2 + Cxy + Dx + Ey + F = 0

    std::vector<std::vector<double>> matrix;

    for (size_t i = 0; i < points.size(); i++)
    {
        std::vector<double> line;

        line.push_back(points[i].x() * points[i].x()); // x^2
        line.push_back(points[i].y() * points[i].y()); // y^2
        line.push_back(points[i].x() * points[i].y()); // xy
        line.push_back(points[i].x()); // x
        line.push_back(points[i].y()); // y
        line.push_back(-1.0); // F

        matrix.push_back(line);
    }

    std::vector<double> coefs(matrix.size());
    gauss(matrix, coefs);
    coefs.push_back(-1.0);

    // TODO implement rc check
    double toDivide = coefs[0];

    for (size_t i = 0; i < coefs.size(); i++)
        coefs[i] /= toDivide;

    return coefs;
}

std::vector<QPointF>& Ellipse::getPoints()
{
    return points;
}

Ellipse& Ellipse::operator=(const Ellipse & other)
{
    this->points = other.points;

    return *this;
}
