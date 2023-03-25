#include <QWidget>

#ifndef FRACTALEXPLORER_KOCHSNOWFLAKEWIDGET_H
#define FRACTALEXPLORER_KOCHSNOWFLAKEWIDGET_H

class KochSnowflakeWidget : public QWidget
{
    Q_OBJECT

public:
    KochSnowflakeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void snowFlake(QPainter *painter, double size, int depth);
    void segment(QPainter *painter, double size, int depth);
};

#endif //FRACTALEXPLORER_KOCHSNOWFLAKEWIDGET_H
