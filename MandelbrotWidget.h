#include <QWidget>
#include <QThread>
#include <QKeyEvent>

#ifndef FRACTALEXPLORER_MANDELBROTWIDGET_H
#define FRACTALEXPLORER_MANDELBROTWIDGET_H

class MandelbrotWorker : public QThread
{
    Q_OBJECT

public:
    explicit MandelbrotWorker(QObject *parent = nullptr);

    void render(double centerX, double centerY, double scaleFactor, int width, int height, double devicePixelRatio);
    void draw();

    signals:
        void renderedImage(const QImage &image, double scaleFactor);

private:
    double centerX;
    double centerY;
    double scaleFactor;
    int width;
    int height;
    double devicePixelRatio;

    int isStable(double cr, double ci, int iterations);
    static double mapToReal(double x, int width, double minR, double maxR);
    static double mapToImaginary(double y, int height, double minI, double maxI);
};

class MandelbrotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MandelbrotWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap pixmap;
    MandelbrotWorker workerThread;
    double centerX;
    double centerY;
    double pixmapScale;
    double curScale;

    void keyPressEvent(QKeyEvent *event) override;
    void scroll(int deltaX, int deltaY);

    private slots:
        void updatePixmap(const QImage &image, double scaleFactor);
        void zoom(double zoomFactor);
};

#endif //FRACTALEXPLORER_MANDELBROTWIDGET_H
