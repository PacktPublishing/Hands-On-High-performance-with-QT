#include "timerthreads.h"


int main(int argc, char *argv[])
{
    qDebug()<< " -- main thread: "<< QThread::currentThreadId()  << "\n";

    // subclassing
    auto mythread = new MyThread();
    mythread->start();

    // worker object
    auto thread = new QThread();
    auto worker = new WorkerObject();

    QObject::connect(thread, &QThread::started, worker, &WorkerObject::startTimer);

    worker->moveToThread(thread);
    thread->start();

    // move thread to thread =8D
    //  - not recommended!
    int oneSec = 1000; // msec
    auto thread1 = new MootThread();
    auto timer1 = new QTimer();

    QObject::connect(timer1, &QTimer::timeout, thread1, &MootThread::doWork);
    QObject::connect(thread1, &QThread::started, thread1, &MootThread::startTimer);

    timer1->setInterval(oneSec);
    timer1->moveToThread(thread1);

    thread1->moveToThread(thread1); // controversial!
    thread1->setTimer(timer1);
    thread1->start();

    QCoreApplication a(argc, argv);

    return a.exec();
}
