#include <QPainter>
#include "DragonCurveWidget.h"

DragonCurveWidget::DragonCurveWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("Dragon Curve"));
}

void DragonCurveWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int depth = 12;
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.translate(width / 1.5, height / 1.75);
    leftDragon(&painter, 6, depth);
}

void DragonCurveWidget::leftDragon(QPainter *painter, double size, int depth)
{
    if (depth == 0)
    {
        painter->drawLine(0, 0, size, 0);
        painter->translate(size, 0);
    }
    else
    {
        leftDragon(painter, size, depth - 1);
        painter->rotate(-90);
        rightDragon(painter, size, depth - 1);
    }
}

void DragonCurveWidget::rightDragon(QPainter *painter, double size, int depth)
{
    if (depth == 0)
    {
        painter->drawLine(0, 0, size, 0);
        painter->translate(size, 0);
    }
    else
    {
        leftDragon(painter, size, depth - 1);
        painter->rotate(90);
        rightDragon(painter, size, depth - 1);
    }
}