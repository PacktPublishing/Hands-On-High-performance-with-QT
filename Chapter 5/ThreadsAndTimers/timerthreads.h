#ifndef TIMERTHREADS_H
#define TIMERTHREADS_H

#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QDebug>


namespace {
    // helpers
    unsigned long oneSec = 1;
    QMutex m;

    bool checkCounter(unsigned threadId)
    {
        static unsigned val = 1;
        QMutexLocker guard(&m);

        if ((val % 3) == threadId - 1)
        {
            ++val;
            return true;
        }

        return false;
    }
}


// subclassing

class MyThread : public QThread
{
public:
  void run() override
  {
    while(!isInterruptionRequested())
    {
       if(checkCondition() == true)
       {
           qDebug() << "MyThread -- working!";
           qDebug()<< " -- threadId: "<< QThread::currentThreadId() << "\n";
       }
       QThread::currentThread()->sleep(oneSec);
    }
  }
private:
  bool checkCondition()
  {
      return checkCounter(1);
  }
};


// no subclassing, use worker object

class WorkerObject : public QObject
{
  Q_OBJECT

public:
    // needed to move the timer to thread along the worker!
    WorkerObject()
        : timer_(this) {}

public slots:
  void doWork()
  {
      if(checkCondition() == true)
      {
          qDebug() << "WorkerObject -- working!";
          qDebug()<< " -- threadId: "<< QThread::currentThreadId() << "\n";
      }
  }

  void startTimer()
  {      
      timer_.start(1000);
      connect(&timer_, &QTimer::timeout, this, &WorkerObject::doWork);
  }

private:
  bool checkCondition()
  {
      return checkCounter(2);
  }

   QTimer timer_;
};


// semi-subclassing
//  - not recommended!

class MootThread : public QThread
{
  Q_OBJECT

public:
    void setTimer(QTimer* t)  { timer_ = t; }

public slots:
  void doWork()
  {
      if(checkCondition() == true)
      {
          qDebug() << "MootThread -- working!";
          qDebug()<< " -- threadId: "<< QThread::currentThreadId() << "\n";
      }
  }
  void startTimer()
  {
      Q_ASSERT(timer_);
      timer_->start(oneSec);
  }

private:
  bool checkCondition()
  {
      return checkCounter(3);
  }

  QTimer* timer_ = nullptr;
  const int oneSec = 1000; // msec
};

#endif // TIMERTHREADS_H
