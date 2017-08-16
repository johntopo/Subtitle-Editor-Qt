#ifndef TIMEDELEGATE_H
#define TIMEDELEGATE_H

#include <QStyledItemDelegate>
#include <QString>

class TimeDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    TimeDelegate(QObject *parent=0);
//    QString displayText(const QVariant &value, const QLocale &locale) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
private slots:
    void commitAndCloseEditor();

};

#endif // TIMEDELEGATE_H
