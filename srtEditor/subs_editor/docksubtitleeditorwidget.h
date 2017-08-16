#ifndef DOCKSUBTITLEEDITORWIDGET_H
#define DOCKSUBTITLEEDITORWIDGET_H

#include "srtDialog.h"
#include "widgetrichtextedit.h"

#include <QDockWidget>
#include <QTableWidget>
#include "utilitylistsrtdialogs.h"
#include <QFont>





class DockSubtitleEditorWidget : public QDockWidget
{
    Q_OBJECT
public:

    DockSubtitleEditorWidget(QWidget *parent = 0);
    QTableWidget *table;
    WidgetRichTextEdit *richTextEdit;
    SrtDialog *dialog;
    QList<SrtDialog> *allDialogs;
    QHBoxLayout *layout;
    QWidget *centralWidget;
    UtilityListSrtDialogs *utilitySrtDialogs;
    QByteArray encod;
private:
     QString fileNameSub;
     void readSubs(QString fileNameSub);
    void setupTable();
    void utilizeTable();
    QList<SrtDialog> saveDialogs();

public slots:
    void openSubtitles();
    void saveAsSubs();
    void saveSubs();
    void setGreekEncoding();
    void setUtf8Encoding();
    void setFont(const QFont &font);
    void findSuitableSub(qint64 timeMs);
    signals:
        void suitableSubForUpdate(QString sub);
};

#endif // DOCKSUBTITLEEDITORWIDGET_H
