
#include "srtDialog.h"
#include <QDebug>
#include <QTextCodec>

#include "timestringconverter.h"

SrtDialog::SrtDialog(QString block)
{

    text=QString("");
    QStringList lines(block.split("\n"));
    TimeStringConverter *converter= new TimeStringConverter;
    foreach (QString line, lines) {
        reg= new QRegularExpression("^[0-9]+$");
        QRegularExpressionMatch match=reg->match(line);
        if(match.hasMatch()){
            index=line.toUInt();
            qDebug()<< "index is: "<< index;
        }
        else if(line.contains("-->")){
            QStringList timeStartEndline=line.split("-->");
            startTime=converter->convertStringToTime((timeStartEndline.takeFirst()).trimmed());
            endTime=converter->convertStringToTime((timeStartEndline.takeFirst()).trimmed());

//            qDebug() << "Start time is : "<< startTime.toString("hh:mm:ss") << " and end time is: " << endTime.toString("hh:mm:ss");

        }else{
        text.append(line+"\n");


        }

    }
    text.chop(2);
}

SrtDialog::SrtDialog()
{

}




