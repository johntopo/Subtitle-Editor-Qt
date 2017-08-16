#include "docksubtitleeditorwidget.h"
#include "richtextdelegate.h"
#include "timedelegate.h"
#include "iddelegate.h"
#include <QHeaderView>
#include <QFileDialog>
#include <QStandardPaths>
#include <utilitylistsrtdialogs.h>
#include "encodingname.h"
#include "timeconverter.h"

DockSubtitleEditorWidget::DockSubtitleEditorWidget(QWidget *parent)
    :QDockWidget(parent)
{

    centralWidget=new QWidget(this);

    layout=new QHBoxLayout;
    setWidget(centralWidget);
    centralWidget->setLayout(layout);
    table=new QTableWidget(this);
    richTextEdit=new WidgetRichTextEdit(this);
    layout->addWidget(table);
    layout->addWidget(richTextEdit);

    richTextEdit->resize(300,100);
    setupTable();
    encod=EncodingName::UTF8;

}

void DockSubtitleEditorWidget::setupTable()
{
    table->setColumnCount(4);


    table->setFont(QFont("Times", 12, QFont::Normal));
    table->setHorizontalHeaderItem(0,new QTableWidgetItem("id"));
    table->setHorizontalHeaderItem(1,new QTableWidgetItem("start time"));
    table->setHorizontalHeaderItem(2,new QTableWidgetItem("end time"));
    table->setHorizontalHeaderItem(3,new QTableWidgetItem("text"));
    table->verticalHeader()->hide();
    table->setItemDelegateForColumn(0,new IdDelegate);
    table->setItemDelegateForColumn(1,new TimeDelegate);
    table->setItemDelegateForColumn(2,new TimeDelegate);
    RichTextDelegate *richTextDelegate=new RichTextDelegate(nullptr,richTextEdit->textEdit);
    table->setItemDelegateForColumn(3,richTextDelegate);
    connect(richTextDelegate,SIGNAL(editorIsBeingCreated(int)),table,SLOT(resizeRowToContents(int)));



}


void DockSubtitleEditorWidget::utilizeTable()
{
    table->setRowCount(0);
    for( int i=0; i<allDialogs->count(); ++i )

    {   SrtDialog dialoge=allDialogs->at(i);
        table->insertRow(i);
        QTableWidgetItem *itemId=new QTableWidgetItem(QString::number(dialoge.index));
        itemId->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        table->setItem(i,0,itemId);


        QTableWidgetItem *itemStartTime=new QTableWidgetItem();
        itemStartTime->setData(Qt::DisplayRole,dialoge.startTime);
        table->setItem(i,1,itemStartTime);


        QTableWidgetItem *itemEndTime=new QTableWidgetItem();
        itemEndTime->setData(Qt::DisplayRole,dialoge.endTime);
        table->setItem(i,2,itemEndTime);

        QTableWidgetItem *textItem=new QTableWidgetItem();
        textItem->setData(Qt::DisplayRole,dialoge.text);
        table->setItem(i,3,textItem);



    }

    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    table->horizontalHeader()->setSectionResizeMode(
                3, QHeaderView::Stretch);

}

QList<SrtDialog> DockSubtitleEditorWidget::saveDialogs()
{
    QList<SrtDialog> dialogsToSave;
    SrtDialog *dialogToSave;
    for (int counter = 0; counter < table->rowCount(); ++counter) {
        dialogToSave=new SrtDialog;
        dialogToSave->index=table->model()->index(counter,0).data().toInt();
        dialogToSave->startTime=table->model()->index(counter,1).data().toTime();
        dialogToSave->endTime=table->model()->index(counter,2).data().toTime();
        dialogToSave->text=table->model()->index(counter,3).data().toString();
        dialogsToSave.append(*dialogToSave);
        delete dialogToSave;
    }
    return dialogsToSave;
}




void DockSubtitleEditorWidget::openSubtitles()
{



    fileNameSub=QFileDialog::getOpenFileName(this, "Choose a file", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "subtitles (*.srt)");
    readSubs(fileNameSub);
    setWindowTitle(fileNameSub);



}

void DockSubtitleEditorWidget::saveAsSubs()
{
    QString fileNameSubForSave=QFileDialog::getSaveFileName(this, "Choose a file", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "subtitles (*.srt)");
    if(fileNameSubForSave!=""){

        utilitySrtDialogs->saveListSrtDialogToFile(fileNameSubForSave,saveDialogs(),encod);

    }
}

void DockSubtitleEditorWidget::saveSubs()
{

    if(fileNameSub!=""){

        utilitySrtDialogs->saveListSrtDialogToFile(fileNameSub,saveDialogs(),encod);
    }
}
    void DockSubtitleEditorWidget::setGreekEncoding()
    {
        encod=EncodingName::ISO8859_7;
        utilitySrtDialogs->setSrtDialogsEncode(allDialogs,encod);
        utilizeTable();
    }

    void DockSubtitleEditorWidget::setUtf8Encoding()
    {
        encod=EncodingName::UTF8;
        utilitySrtDialogs->setSrtDialogsEncode(allDialogs,encod);
        utilizeTable();
    }

    void DockSubtitleEditorWidget::setFont(const QFont &font)
    {

        table->setFont(font);
        table->resizeRowsToContents();
        table->resizeColumnsToContents();
        table->horizontalHeader()->setSectionResizeMode(
                    3, QHeaderView::Stretch);
    }

    void DockSubtitleEditorWidget::findSuitableSub(qint64 timeMs)
    {
        TimeConverter currentFrameTime(timeMs);
        QString sub="";
        for (int line = 0; line < table->rowCount(); ++line) {
            if(currentFrameTime.getTime()>table->model()->index(line,1).data().toTime() && currentFrameTime.getTime()<table->model()->index(line,2).data().toTime()){
                sub=table->model()->index(line,3).data().toString();
                table->setCurrentCell(line,0);
            }
        }


        QString result=QString("<font color=\"white\">"+sub+"</font>");
        emit suitableSubForUpdate(result);
    }



    void DockSubtitleEditorWidget::readSubs(QString fileNameSub)
    {

        table->setRowCount(0);
        utilitySrtDialogs=new UtilityListSrtDialogs;
        allDialogs=utilitySrtDialogs->createListSrtDialogFromFile(fileNameSub,encod);

        utilizeTable();


    }






