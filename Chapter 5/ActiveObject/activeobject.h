#ifndef ACTIVEOBJECT_H
#define ACTIVEOBJECT_H

#include <QThread>
#include <functional>


// woker object for QThread event loop as input queue
//  - we don't want to use thread->moveToThread(thread) hack!

class WorkerObject : public QObject
{
    Q_OBJECT
public:
    WorkerObject(QObject* parent = nullptr)
        : QObject(parent)
    {}

public slots:
    void execAction(const std::function<void(void)>& action)
    {
        action();
    }
};


// active object using QThread's event loop as input queue

class ActiveObject : public QThread
{
    Q_OBJECT
public:
    ActiveObject(QObject* parent = nullptr)
        : QThread(parent),
          worker_(nullptr)
    {
        worker_.moveToThread(this);

        qRegisterMetaType<std::function<void(void)>>("std::function<void(void)>");
        connect(this, &ActiveObject::triggerAction, &worker_, &WorkerObject::execAction);

        start();
    }

    void send(const std::function<void(void)>& action)
    {
        emit triggerAction(action);
    }

signals:
    void triggerAction(const std::function<void(void)>& action);

private:
    WorkerObject worker_;
};

#endif // ACTIVEOBJECT_H
