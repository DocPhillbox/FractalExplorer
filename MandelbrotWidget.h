#include <QWidget>

#ifndef FRACTALEXPLORER_MANDELBROTWIDGET_H
#define FRACTALEXPLORER_MANDELBROTWIDGET_H

class MandelbrotWidget : public QWidget
{
    Q_OBJECT

public:
    MandelbrotWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    int isStable(double cr, double ci, int iterations);
    double mapToReal(int x, int width, double minR, double maxR);
    double mapToImaginary(int y, int height, double minI, double maxI);

private:

};

#endif //FRACTALEXPLORER_MANDELBROTWIDGET_H
