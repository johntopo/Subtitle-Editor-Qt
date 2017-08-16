#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include "timeconverter.h"

#include <QLCDNumber>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>



class MediaController: public QWidget
{
    Q_OBJECT
public:
    TimeConverter *timeConverter=0;
    QGridLayout *layout;
    QString durationOfMedia;
    MediaController(QWidget *parent = 0);
    QSlider *slider;
    QLabel *timeLabel;
    QLCDNumber *volumeLabel;


public slots:
    void updateSliderValue(qint64 pos);
    void updateTimeLabel(qint64 value);
    void setUpSlider(qint64 duration);
};

#endif // MEDIACONTROLLER_H
