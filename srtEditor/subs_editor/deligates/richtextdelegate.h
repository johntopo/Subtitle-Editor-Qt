#ifndef RICHTEXTDELEGATE_H
#define RICHTEXTDELEGATE_H

#include <QStyledItemDelegate>
#include <QTextEdit>
#include "texteditfont.h"

class RichTextDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    RichTextDelegate(QObject *parent=0,TextEditFont *editor=0);

protected:
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const;

private:
    TextEditFont *editor;
private slots:

signals:
     void editorIsBeingCreated(int) const;


};

#endif // RICHTEXTDELEGATE_H
