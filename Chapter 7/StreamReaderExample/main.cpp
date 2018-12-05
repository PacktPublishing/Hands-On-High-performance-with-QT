#include <QCoreApplication>

#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>


void outputLibraryUsers(QXmlStreamReader& reader);
void getUserLanguages(QXmlStreamReader& reader, QStringList& langs, QStringList& langCodes);


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
    <library>
    <name>
    </name>
    <books>
      <book>Legenda aurea</book>
      <book>Le roman de la rose</book>
      <book>Στοιχεῖα</book>
      <book>Ars Poetica</book>
      <book>Tusculanae disputationes</book>
    </books>
    <users>
      <user>
        <name>Dante</name>
        <lang code="it_IT">old italian</lang>
        <lang code="la_EU">medieval latin</lang>
      </user>
      <user>
      <name>Petrarch</name>
        <lang code="it_IT">old italian</lang>
        <lang code="la_EU">medieval latin</lang>
        </user>
      <user>
        <name>Villon</name>
        <lang code="fr_FR">old french</lang>
      </user>
      <user>
        <name>Chaucer</name>
        <lang code="en_UK">middle english</lang>
        <lang code="la_EU">medieval latin</lang>
      </user>
    </users>
    </library>)";

    QXmlStreamReader reader(xmlData);
#endif

     if (reader.readNextStartElement())
     {
         if (reader.name() == "library")
         {
             outputLibraryUsers(reader);
         }
         else
         {
             reader.raiseError(QObject::tr("Incorrect XML data - 'library' root tag missing "));
         }
     }

    if (reader.hasError())
    {
         qDebug() << reader.errorString();
         return -1;
    }

    QCoreApplication a(argc, argv);
    return a.exec();
}


void outputLibraryUsers(QXmlStreamReader& reader)
{
    while(reader.readNextStartElement())
    {
        if(reader.name() == "users")
        {
            while(reader.readNextStartElement())
            {
                if(reader.name() == "user")
                {
                    QString name;
                    QStringList langs, langCodes;

                    while(reader.readNextStartElement())
                    {
                        if(reader.name() == "name")
                        {
                            name = reader.readElementText();
                        }
                        else if(reader.name() == "lang")
                        {
                            getUserLanguages(reader, langs, langCodes);
                        }
                        else
                        {
                             reader.skipCurrentElement();
                        }
                    }

                    qDebug() << "user: " << name << ", languages:" << langs << "codes:" << langCodes << "\n";
                }
            }
        }
        else
        {
            reader.skipCurrentElement();
        }
    }
}

void getUserLanguages(QXmlStreamReader& reader, QStringList& langs, QStringList& langCodes)
{
    Q_ASSERT(reader.name() == "lang");

    // process attrs _before_ text
    auto attributes = reader.attributes();

    if(!attributes.hasAttribute("code"))
    {
        reader.raiseError(QObject::tr("Incorrect XML data - missing 'code' attribute in the 'lang' tag"));
        return;
    }

    langCodes << attributes.value("", "code").toString();

    langs << reader.readElementText();
}

