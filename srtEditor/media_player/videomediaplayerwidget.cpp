#include "videomediaplayerwidget.h"
#include <QFileDialog>
#include <QPainter>


VideoMediaPlayerWidget::VideoMediaPlayerWidget(QWidget *parent):
    QVideoWidget(parent)
{

    setAttribute(Qt::WA_DeleteOnClose);
    initialize();
    createActions();
    createContextMenus();
    this->setMouseTracking(true);


}


void VideoMediaPlayerWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(player->state()==QMediaPlayer::PlayingState){
        player->pause();
        showPlayHidePause();
    }else{
        player->play();
        showPauseHidePlay();
    }
}

void VideoMediaPlayerWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void VideoMediaPlayerWidget::wheelEvent(QWheelEvent *event)
{

   QPoint numDeg= event->angleDelta()/120;
   player->setVolume(player->volume()+numDeg.y()*5);



   event->accept();
}

void VideoMediaPlayerWidget::resizeEvent(QResizeEvent *event)
{
    QVideoWidget::resizeEvent(event);
    emit sizeChanged();
}



void VideoMediaPlayerWidget::setPosition(int pos)
{
player->setPosition(pos);
}



void VideoMediaPlayerWidget::initialize()
{
    player=new QMediaPlayer(nullptr,QMediaPlayer::VideoSurface);
    player->setNotifyInterval(10);
}

void VideoMediaPlayerWidget::play(QString fileName)
{

    player->setMedia(QUrl::fromLocalFile(fileName));
    player->setVolume(50);
    player->setVideoOutput(this);



    player->play();
    update();
}

void VideoMediaPlayerWidget::createActions()
{



    //    playAction=new QAction("play");
    //    connect(playAction,SIGNAL(triggered(bool)),this,SLOT(play()));

    pauseAction=new QAction("Pause");

    resumeAction=new QAction("Resume");
    resumeAction->setVisible(false);
    connect(pauseAction,SIGNAL(triggered(bool)),player,SLOT(pause()));
    connect(resumeAction,SIGNAL(triggered(bool)),player,SLOT(play()));
    connect(pauseAction,SIGNAL(triggered(bool)),this,SLOT(showPlayHidePause()));
    connect(resumeAction,SIGNAL(triggered(bool)),this,SLOT(showPauseHidePlay()));

}

void VideoMediaPlayerWidget::createContextMenus()
{

    this->addAction(pauseAction);
    this->addAction(resumeAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}
void VideoMediaPlayerWidget::showPlayHidePause()
{
    pauseAction->setVisible(false);
    resumeAction->setVisible(true);
}

void VideoMediaPlayerWidget::showPauseHidePlay()
{
    pauseAction->setVisible(true);
    resumeAction->setVisible(false);
}

void VideoMediaPlayerWidget::hideCursor()
{
    this->setCursor(Qt::BlankCursor);
}

void VideoMediaPlayerWidget::showCursor()
{
    this->setCursor(Qt::ArrowCursor);
}

