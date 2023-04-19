#include <QPainter>
#include "MandelbrotWidget.h"

const double DefaultCenterX = -0.637011;
const double DefaultCenterY = -0.0395159;
const double DefaultScale = 0.00403897;

const double ZoomInFactor = 0.6;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 20;

MandelbrotWorker::MandelbrotWorker(QObject *parent)
    : QThread(parent)
{

}

void MandelbrotWorker::render(double centerX, double centerY, double scaleFactor, int width, int height, double devicePixelRatio)
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->scaleFactor = scaleFactor;
    this->width = width;
    this->height = height;
    this->devicePixelRatio = devicePixelRatio;


    draw();
}

void MandelbrotWorker::draw()
{
    printf("run");
    QImage image(QSize(width, height), QImage::Format_RGB32);
    int halfWidth = this->width / 2;
    int halfHeight = this->height / 2;
    image.setDevicePixelRatio(devicePixelRatio);
    int iterations = 26;
    double minR = -3;
    double maxR = 2.5;
    double minI = -1.5;
    double maxI = 1.5;

    for (int y = 0; y < height; ++y)
    {
        auto scaneLine = reinterpret_cast<uint *>(image.scanLine(y));

        for (int x = 0; x < width; ++x)
        {
            // double cr = mapToReal(x, width, minR, maxR);
            // double ci = mapToImaginary(y, height, minI, maxI);
            double cr = centerX + ((x - halfWidth) * scaleFactor);
            double ci = centerY + ((y - halfHeight) * scaleFactor);
            int n = isStable(cr, ci, iterations);
            int r = (n % 256);
            int g = (n % 256);
            int b = ((int)pow(n, 2.0) % 256);
            if (n < iterations)
                *scaneLine++ = qRgb(r, g, b);
            else
                *scaneLine++ = qRgb(0, 0, 0);
        }
    }
    emit renderedImage(image, scaleFactor);
}

int MandelbrotWorker::isStable(double cr, double ci, int iterations)
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

double MandelbrotWorker::mapToReal(double x, int width, double minR, double maxR)
{
    double range = maxR - minR;
    return x * (range / width) + minR;
}

double MandelbrotWorker::mapToImaginary(double y, int height, double minI, double maxI)
{
    double range = maxI - minI;
    return y * (range / height) + minI;
}

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
    : QWidget(parent),
    centerX(DefaultCenterX),
    centerY(DefaultCenterY),
    pixmapScale(DefaultScale),
    curScale(DefaultScale)
{
    connect(&workerThread, &MandelbrotWorker::renderedImage, this, &MandelbrotWidget::updatePixmap);
}

void MandelbrotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    workerThread.render(this->centerX, this->centerY, this->curScale, this->width(), this->height(), devicePixelRatio());
    QRectF exposed = painter.transform().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
    painter.drawPixmap(exposed, pixmap, exposed);
}

void MandelbrotWidget::updatePixmap(const QImage &image, double scaleFactor)
{
    pixmap = QPixmap::fromImage(image);
    update();
}

void MandelbrotWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Z:
            zoom(ZoomInFactor);
            break;
        case Qt::Key_U:
            zoom(ZoomOutFactor);
            break;
        case Qt::Key_Left:
            scroll(-ScrollStep, 0);
            break;
        case Qt::Key_Right:
            scroll(+ScrollStep, 0);
            break;
        case Qt::Key_Up:
            scroll(0, ScrollStep);
            break;
        case Qt::Key_Down:
            scroll(0, -ScrollStep);
            break;
        case Qt::Key_Q:
            close();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void MandelbrotWidget::zoom(double zoomFactor)
{
    printf("Zoom");
    curScale *= zoomFactor;
    update();
    workerThread.render(centerX, centerY, curScale, size().width(), size().height(), devicePixelRatio());
}

void MandelbrotWidget::scroll(int deltaX, int deltaY)
{
    centerX += deltaX * curScale;
    centerY += deltaY * curScale;
    update();
    workerThread.render(centerX, centerY, curScale, size().width(), size().height(), devicePixelRatio());
}