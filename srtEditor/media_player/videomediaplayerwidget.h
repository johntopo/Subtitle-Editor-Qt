#ifndef VIDEOMEDIAPLAYERWIDGET_H
#define VIDEOMEDIAPLAYERWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMenu>
#include <QWheelEvent>

class VideoMediaPlayerWidget: public QVideoWidget
{
    Q_OBJECT
public:
    QMediaPlayer *player;
    VideoMediaPlayerWidget(QWidget *parent = 0);
    void resume();
    void pause();
    void play(QString fileName);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event );
    void resizeEvent(QResizeEvent *event);


public slots:
    void setPosition(int pos);
    void showPlayHidePause();
    void showPauseHidePlay();
    void hideCursor();
    void showCursor();


private:

    void initialize();
    void createActions();
    void createContextMenus();






    QAction *pauseAction;
    QAction *resumeAction;
    QMenu *menu;
    QAction *playAction;
    QString fileName;

signals:

void mouseMoved(QMouseEvent *event);
void sizeChanged();

};

#endif // VIDEOMEDIAPLAYERWIDGET_H
