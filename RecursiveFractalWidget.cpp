#include <QPainter>
#include "RecursiveFractalWidget.h"

RecursiveFractalWidget::RecursiveFractalWidget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("Tree fractal"));
}

void RecursiveFractalWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int depth = 15;
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.translate(width / 2.0, 5 * height / 6);
    tree(&painter, height / 6.0, depth);
}

void RecursiveFractalWidget::tree(QPainter *painter, double size, int depth)
{
    if (depth > 0)
    {
        painter->drawLine(0, 0, 0, -size);
        painter->translate(0, -size);
        int angle = 25;
        painter->rotate(angle);
        tree(painter, 0.8 * size, depth - 1);
        painter->rotate(-2 * angle);
        tree(painter, 0.8 * size, depth - 1);
        painter->rotate(angle);
        painter->translate(0, size);
    }
}
