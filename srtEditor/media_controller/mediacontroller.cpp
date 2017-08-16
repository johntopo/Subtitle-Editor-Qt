#include "mediacontroller.h"

MediaController::MediaController(QWidget *parent):
    QWidget(parent)
{
    setMaximumHeight(60);
    setMinimumHeight(60);
    slider = new QSlider(this);
    slider->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"border: 1px solid #bbb;\n"
"background: white;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,\n"
"    stop: 0 #66e, stop: 1 #bbf);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #bbf, stop: 1 #55f);\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: #fff;\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #eee, stop:1 #ccc);\n"
"border: 1px solid #777;\n"
"width: 13px;\n"
"margin-top: -2px;\n"
"margin-bottom: -2px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #fff, stop:1 #ddd);\n"
"border: 1px solid #444;\n"
"border-radius: 4px;\n"
"}\n"
""
                    "\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #bbb;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}"));
    slider->setOrientation(Qt::Horizontal);



    timeLabel = new QLabel(this);
    timeLabel->setEnabled(true);
    timeLabel->setMinimumSize(QSize(422, 20));
    timeLabel->setMaximumSize(QSize(16777215, 20));



    volumeLabel = new QLCDNumber(this);
    volumeLabel->setMinimumSize(QSize(64, 23));
    volumeLabel->setMaximumSize(QSize(16777215, 23));

    layout=new QGridLayout(this);
    layout->addWidget(slider,0,0,1,2);
    layout->addWidget(timeLabel,1,0,1,1);
    layout->addWidget(volumeLabel, 1, 1, 1, 1, Qt::AlignRight);

    setLayout(layout);
}

void MediaController::setUpSlider(qint64 duration)
{
    slider->setRange(0,duration);
    slider->setTracking(true);
    timeConverter=new TimeConverter(duration);
    durationOfMedia=timeConverter->toHourMinSec();



}
void MediaController::updateTimeLabel(qint64 value)
{
    if(!timeConverter){
        setUpSlider(value);
    }
    timeConverter->setTime(value);
    timeLabel->setText(timeConverter->toHourMinSec()+"/"+durationOfMedia);


}


void MediaController::updateSliderValue(qint64 pos)
{
    slider->setValue((int)(pos));
}

