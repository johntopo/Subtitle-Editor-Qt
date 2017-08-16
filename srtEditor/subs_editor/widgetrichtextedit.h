#ifndef WIDGETRICHTEXTEDIT_H
#define WIDGETRICHTEXTEDIT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QTextEdit>
#include <QAction>
#include <QColorDialog>
#include "texteditfont.h"

class WidgetRichTextEdit : public QWidget
{
    Q_OBJECT

public:
    WidgetRichTextEdit(QWidget *parent = 0);

    TextEditFont *textEdit;

private:
    QVBoxLayout *layout;
    QToolBar *toolbar;
    QAction *boldAction;
    QAction *italicAction;
    QAction *colorDialogAction;
    TextEditFont *viewEdit;

    QColorDialog *colorDialog;

    void setupLayout();
    void setupActions();

private slots:
    void pickColor();
    void setTextBold();
    void setTextItalic();
    void updateViewEditText();

};

#endif // WIDGETRICHTEXTEDIT_H
