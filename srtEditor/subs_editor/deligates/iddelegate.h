#ifndef IDDELEGATE_H
#define IDDELEGATE_H

#include <QStyledItemDelegate>

class IdDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    IdDelegate(QObject *parent=0);
protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
};

#endif // IDDELEGATE_H
