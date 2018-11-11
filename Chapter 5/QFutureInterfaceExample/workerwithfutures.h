#ifndef WORKERWITHFUTURES_H
#define WORKERWITHFUTURES_H

#include <QThread>
#include <QMutex>
#include <QFuture>
#include <QList>

#include <functional>


class MyStdException : public QException
{
public:
    MyStdException(QString const& what)
        : what_(what)
    {}

    virtual const QString& text() const { return what_; }

    void raise() const override { throw *this; }
    MyStdException *clone() const override { return new MyStdException(*this); }

private:
    // example only, shouldn't allocate!
    QString what_;
};


class WorkerWithFutures : public QObject
{
    Q_OBJECT

public:
    void start()
    {
        connect(this, &WorkerWithFutures::taskAdded, this, &WorkerWithFutures::handleNewTasks);

        thread_ = new QThread();
        moveToThread(thread_);
        thread_->start();
    }

    ~WorkerWithFutures()
    {
        thread_->terminate();
        thread_->deleteLater();
    }

    template<typename F>
    QFuture<typename std::result_of<F()>::type> dispatch(const F& func)
    {
        QFutureInterface<typename std::result_of<F()>::type> futureInterface;
        futureInterface.reportStarted();

        auto wrapper = [this, func, futureInterface] () mutable
        {
            this->reportTaskResult(futureInterface, func);
        };

        {
            QMutexLocker guard(&tasksMutex_);
            tasks_ << wrapper;
        }

        emit taskAdded();
        return futureInterface.future();
    }

signals:
    void taskAdded();

private slots:
    void handleNewTasks()
    {
        decltype(tasks_) tasks;
        {
            QMutexLocker guard(&tasksMutex_);
            swap(tasks_, tasks);
        }

        for (const auto& task : tasks)
        {
            task();
        }
    }

private:
    template<typename R, typename F, typename... Args>
    std::enable_if<!std::is_same<R, void>::value>
        reportTaskResult(QFutureInterface<R>& futureInterface, F&& func, Args... args)
    {
        try
        {
            const auto result = func(args...);     
            futureInterface.reportResult(&result);
        }
        catch (const QException& e)
        {
            futureInterface.reportException(e);
        }
        catch (const std::exception& e)
        {
            futureInterface.reportException(MyStdException(e.what()));
        }
        catch(...)
        {
            futureInterface.reportException(QUnhandledException());
        }

        futureInterface.reportFinished();
    }

    template<typename F, typename... Args>
    void reportTaskResult(QFutureInterface<void>& futureInterface, F&& func, Args... args)
    {
        try
        {
            func(args...);
        }
        catch (const QException& e)
        {
            futureInterface.reportException(e);
        }
        catch (const std::exception& e)
        {
            futureInterface.reportException(MyStdException(e.what()));
        }
        catch(...)
        {
            futureInterface.reportException(QUnhandledException());
        }

        futureInterface.reportFinished();
    }

    QMutex tasksMutex_;
    QList<std::function<void()>> tasks_;
    QThread* thread_ = nullptr;
};


#endif // WORKERWITHFUTURES_H
