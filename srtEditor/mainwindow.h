#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "docksubtitleeditorwidget.h"
#include "player.h"

#include <QMainWindow>

#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QActionGroup>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    QActionGroup *getEncodeActions() const;
    void setEncodeActions(QActionGroup *value);

private:

    QAction *openMediaAction;
    QAction *openSubAction;
    QAction *exitAction;
    QAction *closeMediaAction;
    QAction *showDurationAction;
    QAction *fullScreenAction;
    QAction *showSubtitlesEditorAction;
    QAction *saveAsAction;
    QAction *saveAction;
    QAction *encodeUTF8Action;
    QAction *encodeGreekAction;
    QActionGroup *encodeActions;
    QAction *fontAction;
    QFont tableFont;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *encodeMenu;

    Player *player;
    DockSubtitleEditorWidget *dockSubtitleEditor;

QVBoxLayout *layout;
QWidget *centralWidget;
void createBasicLayout();
void createActions();
void createConnections();
void createMenuBar();

signals:
void fontChanged(const QFont &);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
void createFontDialog();
void setFullScreen(bool isFullScreen);



};

#endif // MAINWINDOW_H
