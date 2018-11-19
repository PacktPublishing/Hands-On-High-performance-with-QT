#include <QCoreApplication>

#if 0
//QXmlStreamReader xml;



//void readXBEL()
//{
//    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("xbel"));

//    while (xml.readNextStartElement()) {
//        if (xml.name() == QLatin1String("folder"))
//            readFolder(0);
//        else if (xml.name() == QLatin1String("bookmark"))
//            readBookmark(0);
//        else if (xml.name() == QLatin1String("separator"))
//            readSeparator(0);
//        else
//            xml.skipCurrentElement();
//    }
//}



//bool read(QIODevice *device)
//{
//xml.setDevice(device);

//if (xml.readNextStartElement())
//{
//  if (xml.name() == QLatin1String("xbel") &&
//      xml.attributes().value(versionAttribute()) == QLatin1String("1.0"))
//{
//  readXBEL();
//}
//else
//{
// xml.raiseError(QObject::tr("The file is not an XBEL version 1.0 file.")); }
//}
//return !xml.error();
//}
#endif

#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>


int main(int argc, char *argv[])
{
#if 0
    QFile file("./test.xml");

    if(!file.open(QFile::ReadOnly | QFile::Text)){
         qDebug() << "Cannot read file" << file.errorString();
         exit(0);
     }

    QXmlStreamReader reader(&file);
#else
    QByteArray xmlData = R"(<?xml version="1.0" encoding="UTF-8"?>
    <users>
      <name>Dante</name>
      <name>Petrarca</name>
      <name>Villon</name>
      <name>Chaucer</name>
    </users>)";

    QXmlStreamReader reader(xmlData);
#endif

     if (reader.readNextStartElement())
     {
         if (reader.name() == "users")
         {
             while(reader.readNextStartElement())
             {
                 if(reader.name() == "name")
                 {
                     QString name = reader.readElementText();
                     qDebug() << "user: " << name << "\n";
                 }
                 else
                 {
                     reader.skipCurrentElement();
                 }
             }
         }
         else
         {
             reader.raiseError(QObject::tr("Incorrect file"));
         }
     }

    if (reader.hasError())
    {
         qDebug() << reader.errorString();
    }

     return 0;


    QCoreApplication a(argc, argv);
    return a.exec();
}
