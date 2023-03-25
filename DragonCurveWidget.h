#include <QWidget>

#ifndef FRACTALEXPLORER_DRAGONCURVEWIDGET_H
#define FRACTALEXPLORER_DRAGONCURVEWIDGET_H

class DragonCurveWidget : public QWidget
{
    Q_OBJECT

public:
    DragonCurveWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void leftDragon(QPainter *painter, double size, int depth);
    void rightDragon(QPainter *painter, double size, int depth);
};

#endif //FRACTALEXPLORER_DRAGONCURVEWIDGET_H
