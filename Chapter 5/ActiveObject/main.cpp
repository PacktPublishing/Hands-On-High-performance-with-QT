#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QTime>

#include <activeobject.h>
#include <posttomainthread.h>


class SyncLogFile
{
public:
    static void setPath(const QString& filePath)
    {
        filePath_ = filePath;
    }

    SyncLogFile()
        : file_(filePath_)
    {
        file_.open(QIODevice::Append);
    }

    ~SyncLogFile()
    {
        file_.close();
    }

    bool write(QString text)
    {
        auto byteArray = text.toUtf8();
        byteArray.append("\r\n");
        byteArray.prepend(QTime::currentTime().toString().toUtf8() + ": ");

        bool ok = file_.write(byteArray) == byteArray.size();
        ok &= file_.flush();

        qDebug() << " ## Logging: " << text << ", status=" << (ok ? "ok" : "err");
        return ok;
    }

private:
    // the single log file we have:
    static QString filePath_;
    QFile file_;
};

QString SyncLogFile::filePath_;


class AsyncLogFile
{
public:
  void write(const QString& str)
  {
    // we use a lambda taking a copy of the data with it
    a_.send( [=] { log_.write(str); } );
  }

private:
  SyncLogFile log_; // log file
  ActiveObject a_;  // helper (queue+thread)
};



int main(int argc, char *argv[])
{
    SyncLogFile::setPath("./log.txt");
    AsyncLogFile logFile;

    QCoreApplication a(argc, argv);

    // We could do that it Qt 5.10 directly with:
    //  - QMetaObject::invokeMethod(a, [](){ startThreadsANdTimers(); })
    // Instead we'll use a workaround:
    workaround::postToMainThread([&] {
        logFile.write(" text text text ... ");
        logFile.write(" bla bla bla ... ");
        logFile.write(" yadda yadda yadda ... ");
        });

    return a.exec();
}
