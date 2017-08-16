#ifndef SRTDIALOG_H
#define SRTDIALOG_H


#include <QString>
#include <QTime>
#include <QRegularExpression>

class SrtDialog
{
public:
    SrtDialog(QString block);
    SrtDialog();

    QTime startTime;
    QTime endTime;
    QString text;
    quint32 index;
    QRegularExpression *reg;






};

#endif // SRTDIALOG_H
