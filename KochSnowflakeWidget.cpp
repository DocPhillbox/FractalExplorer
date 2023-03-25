#include <QPainter>
#include "KochSnowflakeWidget.h"

KochSnowflakeWidget::KochSnowflakeWidget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("Koch Snowflake"));
}

void KochSnowflakeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int depth = 7;
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.translate(width / 3.0, height / 3.0);
    snowFlake(&painter, 4 * height / 6.0, depth);
}

void KochSnowflakeWidget::snowFlake(QPainter *painter, double size, int depth)
{
    for (int i = 0; i < 3; i++)
    {
        segment(painter, size, depth);
        painter->rotate(120);
    }
}

void KochSnowflakeWidget::segment(QPainter *painter, double size, int depth)
{
    if (depth == 0)
    {
        painter->drawLine(0, 0, size, 0);
        painter->translate(size, 0);
    }
    else
    {
        segment(painter, size / 3.0, depth - 1);
        painter->rotate(-60);
        segment(painter, size / 3.0, depth - 1);
        painter->rotate(120);
        segment(painter, size / 3.0, depth - 1);
        painter->rotate(-60);
        segment(painter, size / 3.0, depth - 1);
    }
}