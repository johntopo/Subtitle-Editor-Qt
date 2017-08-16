#include "iddelegate.h"
#include <QTextEdit>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QTextDocument>
#include <QStyle>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QRect>

IdDelegate::IdDelegate(QObject *parent)
:QStyledItemDelegate(parent)
{

}

void IdDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString idText=index.model()->data(index,Qt::DisplayRole).toString();
    QStyleOptionViewItem opt=option;


    initStyleOption(&opt, index);
    QStyle *style = opt.widget->style();
    opt.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter);
    painter->save();
    painter->setFont(opt.font);
    painter->drawText(opt.rect,Qt::AlignVCenter | Qt::AlignLeft,idText);
    painter->restore();

}
