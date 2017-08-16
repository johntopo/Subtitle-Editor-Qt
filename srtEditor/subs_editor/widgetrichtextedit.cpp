#include "widgetrichtextedit.h"
#include <QTextFormat>
#include <QColorDialog>
#include <QColor>
#include <qDebug>



WidgetRichTextEdit::WidgetRichTextEdit(QWidget *parent)
    : QWidget(parent)
{
    setupActions();
    setupLayout();


    setMaximumWidth(400);


}



void WidgetRichTextEdit::setupLayout()
{
    layout=new QVBoxLayout;
    this->setLayout(layout);

    toolbar=new QToolBar;
    toolbar->addAction(boldAction);
    toolbar->addAction(italicAction);
    toolbar->addAction(colorDialogAction);


    textEdit=new TextEditFont;
    textEdit->setFocusPolicy(Qt::NoFocus);
    viewEdit=new TextEditFont;
    viewEdit->setReadOnly(true);
    viewEdit->setFocusPolicy(Qt::NoFocus);

    layout->addWidget(toolbar);
    layout->addWidget(textEdit);
    layout->addWidget(viewEdit);
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(updateViewEditText()));
    textEdit->resize(300,textEdit->minimumSizeHint().height());
    connect(textEdit,SIGNAL(fontChanged(QFont)),viewEdit,SLOT(setFont(QFont)));
}

void WidgetRichTextEdit::setupActions()
{
    boldAction=new QAction(QIcon(":/images/assets/images/format-text-bold.png"),"%Bold");
    italicAction=new QAction(QIcon(":/images/assets/images/format-text-italic.png"),"%Italics");
    colorDialogAction=new QAction(QIcon(":/images/assets/images/colorpicker.png"),"Pick Color");

    connect(boldAction,SIGNAL(triggered(bool)),this,SLOT(setTextBold()));
    connect(italicAction,SIGNAL(triggered(bool)),this,SLOT(setTextItalic()));
    connect(colorDialogAction,SIGNAL(triggered(bool)),this,SLOT(pickColor()));


}

void WidgetRichTextEdit::pickColor()
{

 QColor color=QColorDialog::getColor(Qt::white,textEdit,QString(),QColorDialog::ShowAlphaChannel);

if(color.isValid()){


    //

        QString text="";

        text+="<font color=\""+color.name()+"\">";
        text+= textEdit->textCursor().selectedText();
        text+="</font>";
        textEdit->textCursor().insertText(text);

}



}

void WidgetRichTextEdit::setTextBold()
{

    QString text="";
    text+="<b>";
    text+= textEdit->textCursor().selectedText();
    text+="</b>";
    textEdit->textCursor().insertText(text);

}

void WidgetRichTextEdit::setTextItalic()
{
    QString text="";
    text+="<i>";
    text+= textEdit->textCursor().selectedText();
    text+="</i>";
    textEdit->textCursor().insertText(text);
}

void WidgetRichTextEdit::updateViewEditText()
{
    QString text=textEdit->toPlainText();
    text.replace("\n","<br>");
    viewEdit->setHtml(text);

}

