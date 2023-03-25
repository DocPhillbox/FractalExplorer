#include <QApplication>
#include <QWindow>
#include <QGridLayout>
#include "RecursiveFractalWidget.h"
#include "KochSnowflakeWidget.h"
#include "SierpinskiTriangleWidget.h"
#include "DragonCurveWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget w;
    QGridLayout gridLayout;

    RecursiveFractalWidget recursiveFractalWidget;
    KochSnowflakeWidget kochSnowflakeWidget;
    SierpinskiTriangleWidget sierpinskiTriangleWidget;
    DragonCurveWidget dragonCurveWidget;

    gridLayout.addWidget(&recursiveFractalWidget, 0, 0);
    gridLayout.addWidget(&kochSnowflakeWidget, 0, 1);
    gridLayout.addWidget(&sierpinskiTriangleWidget, 1, 0);
    gridLayout.addWidget(&dragonCurveWidget, 1, 1);
    w.setLayout(&gridLayout);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return app.exec();
}