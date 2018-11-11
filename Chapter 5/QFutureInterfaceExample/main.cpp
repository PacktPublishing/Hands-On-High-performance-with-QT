#include <QCoreApplication>
#include <QTimer>
#include <QThread>

#include <iostream>

#include "workerwithfutures.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    WorkerWithFutures worker;
    worker.start();

    // trigger async worker test
    QTimer::singleShot(0, &app, [&](){
        // void result
        auto future = worker.dispatch([]{
                            QThread::currentThread()->msleep(50);
                            std::cout << "Hello from the OTHER thread, ID="
                                      << QThread::currentThreadId() << "\n"; });

        while(!future.isFinished())
        {
            std::cout << "Waiting in the main thread, ID="
                      << QThread::currentThreadId() << "\n";
        }

        std::cout << "Waiting ready in main thread, ID="
                  << QThread::currentThreadId();

        // int result
        auto future1 = worker.dispatch([]() -> int {
                            std::cout << "Hello2 from the OTHER thread, ID="
                                      << QThread::currentThreadId() << "\n";
                                       return 44; });

        while(!future1.isFinished())
        {
            std::cout << "Waiting2 in the main thread, ID="
                      << QThread::currentThreadId() << "\n";
        }

        auto result = future1.result();

        std::cout << "Waiting2 ready in main thread, result="
                  << result << std::endl;

    });

    return app.exec();
}
