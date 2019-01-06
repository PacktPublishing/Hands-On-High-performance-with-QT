#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickWindow>

#include "frequencymonitor.h"

#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<FrequencyMonitor>("FrequencyMonitor", 1, 0, "FrequencyMonitor");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    ///
    QObject* rootObject = engine.rootObjects().first();
    auto name = rootObject->objectName();

    QObject* rootObject2 = engine.rootObjects().last();
    auto name2 = rootObject2->objectName();

//    QQuickItem* root = rootObject->findChild<QQuickItem*>("root");

//    for(auto& elem : rootObject->children())
//    {
//        auto qi = dynamic_cast<QQuickItem*>(elem);
//        qDebug() << qi->objectName() << endl;
//    }

    //QObject* freqDispay = root->findChild<QObject*>("fpsRateDisplay");

    QQuickItem* freqDisplay = rootObject->findChild<QQuickItem*>("fpsRateDisplay");
    QQuickItem* qmlObject3 = rootObject2->findChild<QQuickItem*>("frequencyDisplay");

    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));

    QObject::connect(window, SIGNAL(afterRendering()),
                     freqDisplay, SLOT(framePainted()));

    return app.exec();
}
