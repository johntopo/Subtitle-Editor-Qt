#ifndef TIMESTRINGCONVERTER_H
#define TIMESTRINGCONVERTER_H

#include <QTime>
class TimeStringConverter
{
public:
    QTime *time;
    TimeStringConverter();
    QTime convertStringToTime(QString stringTime);
};

#endif // TIMESTRINGCONVERTER_H
