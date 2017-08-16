#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <QString>
#include <QTime>

class TimeConverter
{

public:
    TimeConverter(qint64 value);
    TimeConverter();
    QString toHourMinSec();


    void setTime(qint64 value);
    QTime getTime();
private:
    QTime *time;
    static qint64 getRemainingHours(qint64 value);
    static qint64 getRemainingMinutes(qint64 value);
    static qint64 getRemainingSeconds(qint64 value);

};

#endif // TIMECONVERTER_H
