#include "mainwindow.h"
#include "widgetrichtextedit.h"
#include "docksubtitleeditorwidget.h"
#include "player.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//     Player *mainWindow=new Player;
MainWindow *mainWindow=new MainWindow;

    mainWindow->show();



    return a.exec();
}
