#include "player.h"
#include "mediacontroller.h"
#include <timeconverter.h>
#include <QStandardPaths>
#include <QTextCodec>
#include <QTableWidgetItem>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>


Player::Player(QWidget *parent) :
    QWidget(parent)
{
    setupUI();

    setMinimumHeight(300);
    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);



    connect(videoPlayer,SIGNAL(mouseMoved(QMouseEvent*)),this,SLOT(mouseMoveEvent(QMouseEvent*)));
    connect(videoPlayer->player,SIGNAL(positionChanged(qint64)),SLOT(update()));
    connect(videoPlayer->player,SIGNAL(positionChanged(qint64)),SIGNAL(frameChanged(qint64)));
    connect(videoPlayer,SIGNAL(sizeChanged()),this,SLOT(setSubtitlePotision()));

    update();
    setUpActions();
    this->setMouseTracking(true);










//    openMedia();



}


void Player::mouseMoveEvent(QMouseEvent *event)
{


    if(this->isFullScreen()){

        videoPlayer->showCursor();
        noButtonPressedTimer->start(5000);
        noButtonPressedTimer->setSingleShot(true);

    }
}


void Player::hideCursor()
{
    if(this->isFullScreen()){
        videoPlayer->hideCursor();

    }
}






void Player::openMedia()
{

    fileNameMedia=QFileDialog::getOpenFileName(this, "Choose a file", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "video (*.avi *.wmv *.mp4 *.mkv);;sound (*.mp3)");
    if(fileNameMedia!=""){
        videoPlayer->play(fileNameMedia);
        emit mediaFileWasOpened(fileNameMedia);

    }
}

void Player::closeMedia()
{
    videoPlayer->player->setMedia(QMediaContent(),nullptr);
    emit mediaFileWasOpened("");
}

void Player::setMediaControllerVisible(bool isVisible)
{
    controller->setVisible(isVisible);
}







void Player::setUpActions()
{



    connect(controller->slider,SIGNAL(sliderMoved(int)),videoPlayer,SLOT(setPosition(int)));
    connect(videoPlayer->player,SIGNAL(positionChanged(qint64)),controller,SLOT(updateTimeLabel(qint64)));
    connect(videoPlayer->player,SIGNAL(positionChanged(qint64)),controller,SLOT(updateSliderValue(qint64)));
    connect(videoPlayer->player,SIGNAL(durationChanged(qint64)),controller,SLOT(setUpSlider(qint64)));
    connect(videoPlayer->player,SIGNAL(volumeChanged(int)),controller->volumeLabel,SLOT(display(int)));

    connect(videoPlayer->player,SIGNAL(positionChanged(qint64)),this,SLOT(update()));



    noButtonPressedTimer=new QTimer;






}

void Player::setSubtitlePotision()
{
    QString tempString=subtitleLabel->text();
    tempString.replace("<br>","\n");
    int lines=tempString.count("\n")+1;
    tempString.remove(QRegExp("<[^>]*>"));

    QFontMetrics metric=QFontMetrics(subtitleFont);
    int playerWidth=videoPlayer->geometry().width();
    int playerHeight=videoPlayer->geometry().height();

    int subWidth=0;
    QStringList allLines=tempString.split("\n",QString::SkipEmptyParts);
    foreach (QString line, allLines) {
        if(subWidth<metric.width(line)){
            subWidth=metric.width(line);
        }
    }


    int subHeight=metric.height()*lines;
    subtitleLabel->setGeometry((playerWidth-subWidth)/2,playerHeight-subHeight-50,subWidth, subHeight);
}

void Player::setSubtitleLabel(QString label)
{
    subtitleLabel->setText(label.replace("\n","<br>"));
    setSubtitlePotision();
}

void Player::setupUI()
{
    this->resize(700, 600);
    //setuplayout
    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 5);
    gridLayout->setMargin(0);
    //setupVideoPlayer
    videoPlayer = new VideoMediaPlayerWidget(this);
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    palette.setBrush(QPalette::Active, QPalette::Window, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
    videoPlayer->setPalette(palette);
    videoPlayer->setAutoFillBackground(true);


    //setupController

    controller=new MediaController();

    //addToLayout
    gridLayout->addWidget(videoPlayer, 0, 0, 1, 2);
    gridLayout->addWidget(controller,1,0,1,2);



    videoPlayer->rect();
    subtitleLabel=new QLabel("<font color=\"white\"></font>",this,Qt::Widget);
    subtitleLabel->setTextFormat(Qt::RichText);
    subtitleLabel->setWordWrap(true);
    subtitleFont=QFont("Times", 22, QFont::Bold);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setAlignment(Qt::AlignCenter);



}









































