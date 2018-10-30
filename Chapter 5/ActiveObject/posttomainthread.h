#ifndef POSTTOMAINTHREAD_H
#define POSTTOMAINTHREAD_H

#include <QtCore>
#include <functional>


// workaround for Qt 5.10's QMetaObject::invokeMethod(a, [](){ })
namespace workaround
{


class FunctorCallEvent : public QEvent
{
   std::function<void()> m_fun;
public:
   FunctorCallEvent(const std::function<void()> & fun)
       : QEvent(QEvent::None), m_fun(fun) {}

   FunctorCallEvent(std::function<void()> && fun, QObject * /*receiver*/)
       : QEvent(QEvent::None), m_fun(std::move(fun)) {}

   ~FunctorCallEvent() { m_fun(); }
};

void postToMainThread(const std::function<void()> & fun)
{
   QCoreApplication::postEvent(qApp, new FunctorCallEvent(fun));
}

void postToMainThread(std::function<void()> && fun)
{
   QCoreApplication::postEvent(qApp, new FunctorCallEvent(std::move(fun)));
}


}

#endif // POSTTOMAINTHREAD_H
