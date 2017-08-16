#include "utilitylistsrtdialogs.h"
#include <QFile>
#include <QTextCodec>
#include "srtDialog.h"
#include <QTextStream>

UtilityListSrtDialogs::UtilityListSrtDialogs()
{

dialogsByteArray=new QList<QByteArray>;
}

QList<SrtDialog>* UtilityListSrtDialogs::createListSrtDialogFromFile(QString fileName, QByteArray encode)
{
    dialogsByteArray->clear();


    QFile *fileSrt=new QFile(fileName);

    fileSrt->open(QIODevice::ReadOnly|QIODevice::Text);



    while(!fileSrt->atEnd()){
        QByteArray line=fileSrt->readLine();
        dialogsByteArray->append(line);

    }
    fileSrt->close();
    delete fileSrt;

    return generateQlistDialogFromByteArray(dialogsByteArray,encode);


}



QList<SrtDialog>* UtilityListSrtDialogs::generateQlistDialogFromByteArray(QList<QByteArray>* dialogs,QByteArray encode)
{

    QList<SrtDialog> *allDialogs=new QList<SrtDialog>();
    SrtDialog *dialog;

    QTextCodec *codec = QTextCodec::codecForName(encode);
    QString tempString("");
    foreach (QByteArray line, *dialogs) {
        if(line!="\n"){
            tempString.append(codec->toUnicode(line));

        }else{
            if(tempString!="" && tempString.contains("-->")){
                dialog=new SrtDialog(tempString);
                allDialogs->append(*dialog);

                tempString="";

                delete dialog;

            }

        }
    }

return allDialogs;


}



bool UtilityListSrtDialogs::saveListSrtDialogToFile(QString fileName, QList<SrtDialog> dialogs,QByteArray encode)
{


    QFile fileWrite(fileName);
    fileWrite.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&fileWrite);
    out.setCodec(QTextCodec::codecForName(encode));
    foreach (SrtDialog dialog, dialogs) {

        out<<dialog.index<<"\n";
        out<<dialog.startTime.toString("hh:mm:ss,zzz")<<" --> "<<dialog.endTime.toString("hh:mm:ss,zzz")<<"\n";
        out<<dialog.text<<"\n\n";

        /*
          format
          1
          00:00:00,227 --> 00:00:02,813
          Attention. I've been asked
          to read this statement.

          2
          00:00:02,828 --> 00:00:05,266
          "Two months ago, Gina
          Linetti was hit by a bus*/
    }


    fileWrite.close();





    return true;
}

void UtilityListSrtDialogs::setSrtDialogsEncode(QList<SrtDialog> *dialogs, QByteArray encode)
{
    delete dialogs;
    dialogs=generateQlistDialogFromByteArray(dialogsByteArray,encode);
}







