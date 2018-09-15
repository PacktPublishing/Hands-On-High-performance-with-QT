#include <QGuiApplication>

#include <QQuickView>
#include <QQmlContext>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QTimer>


void makeLeak()
{
    auto leakedArray = new char[10000];
    Q_UNUSED(leakedArray);
}


void wasteCpuCycles()
{
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
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QStringList countryList;
    countryList << "Thinking...";

    QQuickView view;
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("myModel", QVariant::fromValue(countryList));

    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    // get country names from network
    QNetworkAccessManager networkManager;

    QObject::connect(&networkManager, &QNetworkAccessManager::finished,
                     [&](QNetworkReply* reply){
        // this lambda is called when the reply is received
        countryList.clear();
        if(reply->error() != QNetworkReply::NoError){
            countryList << "Sorry, cannot google it!";
            networkManager.clearAccessCache();
        } else {
            QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
            for(auto& key : jsonObject.keys())
            {
                countryList << jsonObject.value(key).toString();
            }
        }
        ctxt->setContextProperty("myModel", QVariant::fromValue(countryList));
        reply->deleteLater();
    });

    // trigger async fetch
    QTimer::singleShot(0, &app, [&](){
        QUrlQuery query;
        QUrl url("http://country.io/names.json");
        url.setQuery(query);
        QNetworkRequest networkRequest(url);

        networkManager.get(networkRequest);
    });

    // induce memory leak
    //makeLeak();
    // waste time
    //wasteCpuCycles();

    return app.exec();
}
