#ifndef UTILITYLISTSRTDIALOGS_H
#define UTILITYLISTSRTDIALOGS_H



#include "srtDialog.h"


class UtilityListSrtDialogs
{

public:
    UtilityListSrtDialogs();
    QList<SrtDialog>* createListSrtDialogFromFile(QString fileName,QByteArray encode);

    bool saveListSrtDialogToFile(QString fileName,QList<SrtDialog> dialogs,QByteArray encode);
    void setSrtDialogsEncode(QList<SrtDialog>* dialogs ,QByteArray encode);
private:
    QList<QByteArray> *dialogsByteArray;
    QList<SrtDialog>* generateQlistDialogFromByteArray(QList<QByteArray>* dialogs,QByteArray encode);
};

#endif // UTILITYLISTSRTDIALOGS_H
