#include <QWidget>

#ifndef FRACTALEXPLORER_RECURSIVEFRACTALWIDGET_H
#define FRACTALEXPLORER_RECURSIVEFRACTALWIDGET_H

class RecursiveFractalWidget : public QWidget
{
    Q_OBJECT

public:
    RecursiveFractalWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void tree(QPainter *painter, double size, int depth);
};

#endif //FRACTALEXPLORER_RECURSIVEFRACTALWIDGET_H
