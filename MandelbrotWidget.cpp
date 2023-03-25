#include <QPainter>
#include "MandelbrotWidget.h"

MandelbrotWidget::MandelbrotWidget(QWidget *parent) :
        QWidget(parent)
{

}

void MandelbrotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int iterations = 255;
    double minR = -1.5;
    double maxR = 0.7;
    double minI = -1.0;
    double maxI = 1.0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double cr = mapToReal(x, width, minR, maxR);
            double ci = mapToImaginary(y, height, minI, maxI);
            int n = isStable(cr, ci, iterations);
            int r = ((int) (n * sin(n)) % 256);
            int g = (n % 256);
            int b = ((int)pow(n, 2.0) % 256);
            painter.setPen(QColor(r, g, b));
            painter.drawPoint(x, y);
        }
    }
}

int MandelbrotWidget::isStable(double cr, double ci, int iterations)
{
    int i = 0;
    double zr = 0.0; double zi = 0.0;
    while (i < iterations && pow(zr, 2.0) + pow(zi, 2.0) < 4.0)
    {
        double temp = pow(zr, 2.0) - pow(zi, 2.0) + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        i++;
    }
    return i;
}

double MandelbrotWidget::mapToReal(int x, int width, double minR, double maxR)
{
    double range = maxR - minR;
    return x * (range / width) + minR;
}

double MandelbrotWidget::mapToImaginary(int y, int height, double minI, double maxI)
{
    double range = maxI - minI;
    return y * (range / height) + minI;
}