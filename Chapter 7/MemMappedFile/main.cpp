#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>


void fileMapTest()
{
    // find the example file
    QString filePath = "./example.txt";
    QFile file(filePath);

    if(!file.exists())
    {
        filePath = "../MemMappedFile/example.txt";
        file.setFileName(filePath);
        if(!file.exists())
        {
            filePath.append(", ./example.txt");
        }
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning().noquote().nospace()
                << "ERROR: \"" + file.errorString() << "\", paths=\"" << filePath << "\"";
    }

    uchar *memory = file.map(0, file.size());

    if (memory)
    {
        // mind: problem with old Qt interfaces!
        int fileSize32Bit = static_cast<int>(file.size());

        // fromRawData() won't copy!
        auto bytes = QByteArray::fromRawData(reinterpret_cast<const char*>(memory), fileSize32Bit);

        QTextStream istream(bytes);

        while(!istream.atEnd())
        {
            QString line = istream.readLine();
            QStringList fields = line.split(",");
            qDebug() << "phrase: " << fields << endl; // flush!
        }

        file.unmap(memory);
    }

    file.close();
}


int main(int argc, char *argv[])
{           
    QCoreApplication a(argc, argv);

    fileMapTest();

    return a.exec();
}
