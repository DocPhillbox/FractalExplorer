#include <QApplication>
#include <QWindow>
#include <QQuickView>
#include "RecursiveFractalWidget.h"
#include "KochSnowflakeWidget.h"
#include "SierpinskiTriangleWidget.h"
#include "DragonCurveWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto *view = new QQuickView;

    view->setSource(QUrl::fromLocalFile("ui.qml"));
    view->show();
    return app.exec();
}