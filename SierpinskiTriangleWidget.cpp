#include <QPainter>
#include "SierpinskiTriangleWidget.h"

SierpinskiTriangleWidget::SierpinskiTriangleWidget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("Sierpinski Triangle"));
}

void SierpinskiTriangleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int depth = 6;
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.translate(width / 4.0, 3.0 * height / 4.0);
    sierpinski(&painter, 4 * height / 6.0, depth);
}

void SierpinskiTriangleWidget::sierpinski(QPainter *painter, double size, int depth)
{
    if (depth == 0)
    {
        static const QPointF trianglePoints[3] = {
            QPointF(0.0, 0.0),
            QPointF(size, 0.0),
            QPointF(size / 2.0, -size * sqrt(3) / 2.0)
        };
        painter->drawPolygon(trianglePoints, 3);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            sierpinski(painter, size / 2.0, depth - 1);
            painter->translate(size / 2.0, -size * sqrt(3) / 2.0);
            painter->rotate(120);
        }
    }
}