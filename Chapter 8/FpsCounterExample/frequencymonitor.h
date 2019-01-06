#ifndef FREQUENCYMONITOR_H
#define FREQUENCYMONITOR_H

#include <QObject>
#include <QElapsedTimer>


class FrequencyMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal currentFrequency READ currentFrequency NOTIFY currentFrequencyChanged)
    Q_PROPERTY(qreal averageFrequency READ averageFrequency NOTIFY averageFrequencyChanged)

public:
    FrequencyMonitor(QObject* parent = nullptr);

    qreal currentFrequency() const;
    qreal averageFrequency() const;

signals:
    void currentFrequencyChanged();
    void averageFrequencyChanged();

public slots:
    Q_INVOKABLE void notify();

private:
    qreal currentFreq_;
    qreal averageFreq_;
    int count_;
    QElapsedTimer lastMeasInterval_;
};

#endif // FREQUENCYMONITOR_H
