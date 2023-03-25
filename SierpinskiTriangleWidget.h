#include <QWidget>

#ifndef FRACTALEXPLORER_SIERPINSKITRIANGLEWIDGET_H
#define FRACTALEXPLORER_SIERPINSKITRIANGLEWIDGET_H

class SierpinskiTriangleWidget : public QWidget
{
    Q_OBJECT

public:
    SierpinskiTriangleWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void sierpinski(QPainter *painter, double size, int depth);
};

#endif //FRACTALEXPLORER_SIERPINSKITRIANGLEWIDGET_H
