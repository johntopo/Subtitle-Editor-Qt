#ifndef TEXTEDITFONT_H
#define TEXTEDITFONT_H

#include <QTextEdit>

class TextEditFont : public QTextEdit
{
    Q_OBJECT
public:
    TextEditFont(QTextEdit *parent = 0);

signals:
    void fontChanged(const QFont font);
public slots:
    void setFont(const QFont font);
};

#endif // TEXTEDITFONT_H
