#include <QGuiApplication>

#include <QQuickView>
#include <QQmlContext>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QTimer>

#include "minitrace.h"


void wasteMemory()
{
    MTR_SCOPE_FUNC();

    for(int i = 0; i < 100000; i++)
    {
        auto array = new char[10000];
        array[10000 - 1] = 'x';
        delete [] array;
    }
}


void wasteCpuCycles()
{
    MTR_SCOPE_FUNC();

    size_t count = 10000000;
    double result = 0;

    for(size_t i = 0; i < count; ++i)
    {
        result += i / 2.33;
    }

    qDebug() << QString("Wasted %1 divisions, sresult=%2").arg(count).arg(result);
}


int main(int argc, char *argv[])
{
    mtr_init("trace.json");

    MTR_META_PROCESS_NAME("QmlWithModel");
    MTR_META_THREAD_NAME("Main GUI tread");
    MTR_BEGIN("main", "main()");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QStringList countryList;
    countryList << "Thinking...";

    MTR_BEGIN("main", "load QML View");
    QQuickView view;
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("myModel", QVariant::fromValue(countryList));

    view.setSource(QUrl("qrc:/main.qml"));
    view.show();
    MTR_END("main", "load QML View");

    // get country names from network
    MTR_BEGIN("main", "init NetworkMgr");
    QNetworkAccessManager networkManager;
    MTR_END("main", "init NetworkMgr");

    QObject::connect(&networkManager, &QNetworkAccessManager::finished,
                     [&](QNetworkReply* reply){
        // this lambda is called when the reply is received

        MTR_SCOPE("lambda", "networkResponse");
        wasteCpuCycles();

        countryList.clear();
        if(reply->error() != QNetworkReply::NoError){
            countryList << "Sorry, cannot google it!";
            networkManager.clearAccessCache();
        } else {
            wasteCpuCycles();

            QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
            for(auto& key : jsonObject.keys())
            {
                countryList << jsonObject.value(key).toString();
            }
        }
        ctxt->setContextProperty("myModel", QVariant::fromValue(countryList));
        reply->deleteLater();

        wasteCpuCycles();
    });

    // trigger async fetch
    QTimer::singleShot(0, &app, [&](){        
        MTR_SCOPE("lambda", "networkRequest");

        QUrlQuery query;
        QUrl url("http://country.io/names.json");
        url.setQuery(query);
        QNetworkRequest networkRequest(url);

        wasteCpuCycles();

        networkManager.get(networkRequest);

        // OPEN TODO:::
        // --> document progress ...
        // ...

        wasteCpuCycles();
    });

    // waste time
    wasteCpuCycles();

    // get some memory
    wasteMemory();

    // run the QML UI
    MTR_INSTANT("main", "start event loop");

    int ret = app.exec();

    // finish
    MTR_INSTANT("main", "exiting");
    MTR_END("main", "main()");

    mtr_flush();
    mtr_shutdown();

    return ret;
}
