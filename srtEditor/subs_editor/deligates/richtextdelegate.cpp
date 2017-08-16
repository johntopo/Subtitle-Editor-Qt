#include "richtextdelegate.h"
#include <QTextEdit>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QTextDocument>
#include <QStyle>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QRect>
#include <qDebug>



RichTextDelegate::RichTextDelegate(QObject *parent,TextEditFont *editor)
:QStyledItemDelegate(parent)
{
    this->editor=editor;
}

void RichTextDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

emit editorIsBeingCreated(index.row());
}




void RichTextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

       QStyleOptionViewItem opt = option;
       initStyleOption(&opt, index);

       QStyle *style = opt.widget->style();
       QString text=index.model()->data(index).toString();
       QTextDocument doc;
//       qDebug()<<opt.text;
       text.replace("\n","<br>");
//        qDebug()<<opt.text;
       doc.setHtml(text);
       doc.setTextWidth(opt.rect.width());


       doc.setDefaultFont(opt.font);
       emit editorIsBeingCreated(index.row());
       /// Painting item without text
       opt.text = QString();
       style->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

       QAbstractTextDocumentLayout::PaintContext ctx;

       // Highlighting text if item is selected
//       if (optionV4.state & QStyle::State_Selected)
//           ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::HighlightedText));

       QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &opt);
       painter->save();
       QPoint leftTopConrer=QPoint(textRect.topLeft().x(),textRect.topLeft().y()-3);

       painter->translate(leftTopConrer);
//       painter->setClipRect(textRect.translated(-textRect.topLeft()));
        doc.documentLayout()->draw(painter, ctx);

       painter->restore();

//            painter->save();
//           painter->translate(opt.rect.topLeft());
//           painter->setClipRect(textRect.translated(-textRect.topLeft()));
//           doc.drawContents(painter,/*QRect(QPoint(0,0),opt.rect.size())*/QRectF());
//           painter->restore();




}


QWidget *RichTextDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QStyleOptionViewItem opt=option;
    initStyleOption(&opt, index);


    TextEditFont *textEdit=editor? editor:new TextEditFont();

    textEdit->setFocusPolicy(Qt::StrongFocus);
    if(textEdit->font()!=opt.font){
    textEdit->setFont(opt.font);
    }
    textEdit->setWindowTitle("Edit Line");
    return textEdit;
}

void RichTextDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text=index.model()->data(index).toString();
    QTextEdit *textEdit=qobject_cast<QTextEdit *>(editor);
    textEdit->setPlainText(text);
    qDebug()<<text;

}

void RichTextDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    QTextEdit *textEdit=qobject_cast<QTextEdit *>(editor);
    QString text=textEdit->toPlainText();
    model->setData(index,text);
}




void RichTextDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    (qobject_cast<QTextEdit *>(editor))->setPlainText("");
editor->setVisible(true);
editor->setFocusPolicy(Qt::NoFocus);

}

