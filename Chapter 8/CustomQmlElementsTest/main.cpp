#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "painteditemtriangle.h"
#include "quickitemtriangle.h"
#include "framebuffertriangle.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<PaintedItemTriangle>("CustomShapes", 1, 0, "PaintedItemTriangle");
    qmlRegisterType<QuickItemTriangle>("CustomShapes", 1, 0, "QuickItemTriangle");
    qmlRegisterType<FrameBufferTriangle>("CustomShapes", 1, 0, "FrameBufferTriangle");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
