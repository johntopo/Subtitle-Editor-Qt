#include "timeconverter.h"




TimeConverter::TimeConverter(qint64 value)
{
    time=new QTime(getRemainingHours(value),getRemainingMinutes(value),getRemainingSeconds(value));
}

TimeConverter::TimeConverter()
{
    time=new QTime;
}




QString TimeConverter::toHourMinSec()
{

    if(time->hour()>0){
        return time->toString();
    }else{
        return time->toString("mm:ss");
    }



}

qint64 TimeConverter::getRemainingHours(qint64 value)
{

    return value/3600000;

}

qint64 TimeConverter::getRemainingMinutes(qint64 value)
{

    return (value%3600000)/60000;


}

qint64 TimeConverter::getRemainingSeconds(qint64 value)
{
    return ((value%3600000)%60000)/1000;
}

void TimeConverter::setTime(qint64 value)
{
    time->setHMS(getRemainingHours(value),getRemainingMinutes(value),getRemainingSeconds(value));

}

QTime TimeConverter::getTime()
{
    return *time;
}
