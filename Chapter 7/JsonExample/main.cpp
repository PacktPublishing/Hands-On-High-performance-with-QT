#include <QCoreApplication>

#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QDebug>


int main(int argc, char *argv[])
{
#if 0
    QFile file("./example.json");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
         qDebug() << "Cannot read file" << file.errorString();
         exit(0);
     }

    QByteArray data = file.readAll();
#else
       QByteArray data =
           R"({
               "author" : "Dante Alighieri",
               "books" : [
                    { "year" : 1295, "title" : "La Vita Nuova" },
                    { "year" : 1320, "title" : "Divina Commedia" }
                ]
              })";
#endif

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    if(err.error == QJsonParseError::NoError)
    {
      QJsonObject topObject = doc.object();
      auto name = topObject["author"].toString();
      QJsonArray bookArray = topObject["books"].toArray();

      for(const auto& elem: qAsConst(bookArray))
      {
            const QJsonObject& book = elem.toObject();
            auto year  = QString::number(book["year"].toInt());
            auto title = book["title"].toString();

            qDebug() << "author: " << name << "year:" << year << "title:" << title;
      }
    }
    else
    {
        qDebug() << "Cannot parse JSON" << err.errorString();
        exit(0);

    }

    QCoreApplication a(argc, argv);
    return a.exec();
}
