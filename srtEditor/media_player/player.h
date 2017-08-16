#ifndef PLAYER_H
#define PLAYER_H

#include "videomediaplayerwidget.h"
#include "mediacontroller.h"
#include <timeconverter.h>
#include <QFileDialog>
#include <QTimer>
#include <QList>
#include <QTextEdit>
#include <QTableWidget>
#include <QTextBrowser>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QMenuBar>
#include <QMainWindow>



class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = 0);

private:
    VideoMediaPlayerWidget *videoPlayer;
    MediaController *controller;
    QGridLayout *gridLayout;

    QTimer *noButtonPressedTimer;
    QString fileNameMedia;
    QLabel *subtitleLabel;
    QFont subtitleFont;




    QFileDialog *fileDialog;
    //    const QByteArray encoding="ISO 8859-7";
    QByteArray encoding="UTF-8";
    void setUpActions();



QFile *fileSrt;

void setupUI();


public slots:

    void openMedia();
    void closeMedia();
    void setMediaControllerVisible(bool isVisible);
    void mouseMoveEvent(QMouseEvent *event);
    void hideCursor();

    void setSubtitleLabel(QString label);

private slots:
        void setSubtitlePotision();
signals:
        void frameChanged(qint64);
        void mediaFileWasOpened(QString name);
};

#endif // PLAYER_H
