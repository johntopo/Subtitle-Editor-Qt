#include "texteditfont.h"

TextEditFont::TextEditFont(QTextEdit *parent)
    : QTextEdit(parent)
{

}

void TextEditFont::setFont(const QFont font)
{
    QTextEdit::setFont(font);
    emit fontChanged(font);
}
