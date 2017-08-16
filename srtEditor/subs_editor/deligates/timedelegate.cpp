#include "timedelegate.h"
#include <QTime>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QTimeEdit>
#include <QStyle>
#include <QApplication>
#include <QStyledItemDelegate>


TimeDelegate::TimeDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

QSize TimeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   QSize size=QStyledItemDelegate::sizeHint(option,index);
   QStyleOptionViewItem opt=option;

   initStyleOption(&opt, index);
   QFontMetrics metric(opt.font);
   qDebug()<<opt.font.pointSize();
   QString sizeString=index.model()->data(index,Qt::DisplayRole).toTime().toString("hh:mm:ss,zzz");
   size.setWidth(metric.width(sizeString));
   return size;
}


void TimeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTime time=index.model()->data(index,Qt::DisplayRole).toTime();
    QString text=time.toString("hh:mm:ss,zzz");
    QStyleOptionViewItem opt=option;

    initStyleOption(&opt, index);
    QStyle *style = opt.widget->style();
    opt.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter);
    painter->save();
    painter->setFont(opt.font);
    qDebug()<<opt.font.pointSize();
    painter->drawText(opt.rect,Qt::AlignVCenter | Qt::AlignRight,text);
    painter->restore();
}

QWidget *TimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTimeEdit *timeEdit=new QTimeEdit(parent);
    timeEdit->setDisplayFormat("hh:mm:ss,zzz");
    timeEdit->setAlignment(Qt::AlignRight);
    connect(timeEdit,SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
    return timeEdit;
}

void TimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTime time=index.model()->data(index,Qt::DisplayRole).toTime();
    QTimeEdit *timeEdit=qobject_cast<QTimeEdit *>(editor);
    timeEdit->setTime(time);
}

void TimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *timeEdit=qobject_cast<QTimeEdit *>(editor);
    QTime time=timeEdit->time();
    model->setData(index,time);
}

void TimeDelegate::commitAndCloseEditor()
{
        QTimeEdit *editor=qobject_cast<QTimeEdit *>(sender());
        emit commitData(editor);
        emit closeEditor(editor);
}

