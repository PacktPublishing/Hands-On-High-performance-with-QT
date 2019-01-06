#include "frequencymonitor.h"


FrequencyMonitor::FrequencyMonitor(QObject* parent)
    : QObject(parent),
      currentFreq_(0),
      averageFreq_(0),
      count_(0)
{
    lastMeasInterval_.start();
}

qreal FrequencyMonitor::currentFrequency() const
{
    return currentFreq_;
}

qreal FrequencyMonitor::averageFrequency() const
{
    return averageFreq_;
}

void FrequencyMonitor::notify()
{
    auto msec = lastMeasInterval_.restart();
    currentFreq_ = msec ? 1000.0 / msec : 0.0;

    emit currentFrequencyChanged();

    // OPEN TODO:: calculate average frequency..
    ++count_;
}
