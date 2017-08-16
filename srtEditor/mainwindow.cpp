#include "mainwindow.h"
#include "player.h"
#include "docksubtitleeditorwidget.h"
#include <QApplication>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{


    createBasicLayout();
    createActions();
    createConnections();
    createMenuBar();
}

QActionGroup *MainWindow::getEncodeActions() const
{
    return encodeActions;
}

void MainWindow::setEncodeActions(QActionGroup *value)
{
    encodeActions = value;
}

void MainWindow::createBasicLayout()
{

    setGeometry(200,200,1500,720);

    centralWidget=new QWidget;

    layout=new QVBoxLayout;
    layout->setMargin(0);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
    player=new Player(this);
    player->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    layout->addWidget(player);
    dockSubtitleEditor=new DockSubtitleEditorWidget(this);

    dockSubtitleEditor->centralWidget->resize(1000,100);

    addDockWidget(Qt::BottomDockWidgetArea,dockSubtitleEditor);
    dockSubtitleEditor->setAllowedAreas(Qt::BottomDockWidgetArea);
    dockSubtitleEditor->resize(1000,100);
    dockSubtitleEditor->centralWidget->resize(1000,100);
}

void MainWindow::createActions()
{
    openMediaAction=new QAction("Open Media",this);
    openSubAction=new QAction("Open Subs",this);
    exitAction=new QAction("Exit",this);
    closeMediaAction=new QAction("Close Media",this);
    showDurationAction=new QAction("Media Controller",this);
    showDurationAction->setCheckable(true);
    showDurationAction->setChecked(true);
    fullScreenAction=new QAction("Full Screen",this);
    fullScreenAction->setCheckable(true);
    fullScreenAction->setChecked(false);
    showSubtitlesEditorAction= dockSubtitleEditor->toggleViewAction();
    showSubtitlesEditorAction->setText("Subtitle Editor");
    //new QAction("Subtitle Editor",this);

    saveAsAction=new QAction("Save As",this);
    saveAction=new QAction("Save",this);

    encodeUTF8Action=new QAction("UTF-8",this);
    encodeUTF8Action->setCheckable(true);
    encodeUTF8Action->setChecked(true);
    encodeGreekAction=new QAction("Greek",this);
    encodeGreekAction->setCheckable(true);
    encodeGreekAction->setChecked(false);

    fontAction=new QAction("Font",this);



}

void MainWindow::createConnections()
{
    //connections in MainWindow
    connect(openMediaAction,SIGNAL(triggered(bool)),player,SLOT(openMedia()));
    connect(player,SIGNAL(mediaFileWasOpened(QString)),this,SLOT(setWindowTitle(QString)));
    connect(openSubAction,SIGNAL(triggered(bool)),dockSubtitleEditor,SLOT(openSubtitles()));
    connect(exitAction,SIGNAL(triggered(bool)),QApplication::instance(),SLOT(quit()));
    connect(closeMediaAction,SIGNAL(triggered(bool)),player,SLOT(closeMedia()));
    connect(showDurationAction,SIGNAL(toggled(bool)),player,SLOT(setMediaControllerVisible(bool)));
    connect(fullScreenAction,SIGNAL(toggled(bool)),this,SLOT(setFullScreen(bool)));
    //save
    connect(saveAsAction,SIGNAL(triggered(bool)),dockSubtitleEditor,SLOT(saveAsSubs()));
    connect(saveAction,SIGNAL(triggered(bool)),dockSubtitleEditor,SLOT(saveSubs()));
    //encoding
    connect(encodeUTF8Action,SIGNAL(triggered(bool)),dockSubtitleEditor,SLOT(setUtf8Encoding()));
    connect(encodeGreekAction,SIGNAL(triggered(bool)),dockSubtitleEditor,SLOT(setGreekEncoding()));


    connect(fontAction,SIGNAL(triggered(bool)),SLOT(createFontDialog()));
    connect(this,SIGNAL(fontChanged(QFont)),dockSubtitleEditor,SLOT(setFont(QFont)));
    //connections between widgets

    connect(player,SIGNAL(frameChanged(qint64)),dockSubtitleEditor,SLOT(findSuitableSub(qint64)));
    connect(dockSubtitleEditor,SIGNAL(suitableSubForUpdate(QString)),player,SLOT(setSubtitleLabel(QString)));

}

void MainWindow::createMenuBar()
{
    fileMenu=menuBar()->addMenu("File");
    viewMenu=menuBar()->addMenu("View");
    encodeMenu=menuBar()->addMenu("Encode");

    fileMenu->addAction(openMediaAction);
    fileMenu->addAction(openSubAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeMediaAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu->addAction(showDurationAction);
    viewMenu->addAction(showSubtitlesEditorAction);
    viewMenu->addAction(fullScreenAction);

    encodeActions=new QActionGroup(this);
    encodeActions->addAction(encodeUTF8Action);
    encodeActions->addAction(encodeGreekAction);

    encodeMenu->addAction(encodeUTF8Action);
    encodeMenu->addAction(encodeGreekAction);
    encodeMenu->addAction(fontAction);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape && isFullScreen()){
        this->showNormal();
        fullScreenAction->setChecked(false);
    }
}

void MainWindow::createFontDialog()
{
    bool fontIsOk;
    tableFont = QFontDialog::getFont(&fontIsOk, QFont("Times", 12), this);
    if(fontIsOk){
        emit fontChanged(tableFont);
    }
}

void MainWindow::setFullScreen(bool isFullScreen)
{
    if(isFullScreen){
        this->showFullScreen();
    }else{
        this->showNormal();
    }
}
