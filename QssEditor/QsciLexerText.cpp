#include "QsciLexerText.h"

QsciLexerText::QsciLexerText(QObject *parent)
    : QsciLexerCustom{parent}
{
    setAutoIndentStyle(0);
}

QsciLexerText::~QsciLexerText()
{

}

const char* QsciLexerText::language() const
{
    return "Plain text";
}

QString QsciLexerText::description(int style) const
{
    if (style == 0) {
        return "Text";
    } else {
        return "";
    }
}

void QsciLexerText::styleText(int start, int end)
{
    startStyling(start);
    setStyling(end-start, 0);
}
