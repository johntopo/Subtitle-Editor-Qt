#include "timestringconverter.h"
#include <qDebug>
TimeStringConverter::TimeStringConverter()
{
    time=new QTime;
}

QTime TimeStringConverter::convertStringToTime(QString stringTime)
{
    QStringList list=stringTime.split(':');
    if(list.last().contains(',')){
        QStringList seconds=list.takeLast().split(',');


        time->setHMS((list.takeFirst()).toInt(),
                     (list.takeLast()).toInt(),
                     (seconds.takeFirst()).toInt(),
                     (seconds.takeLast()).toInt());

    }else{

        time->setHMS(list.takeAt(0).toInt(),
                     list.takeAt(1).toInt(),
                     list.takeAt(2).toInt());


    }
    return *time;
}
