#ifndef QSCILEXERTEXT_H
#define QSCILEXERTEXT_H

#include <qsci/qscilexercustom.h>

class QsciLexerText : public QsciLexerCustom
{
public:
    explicit QsciLexerText(QObject *parent = nullptr);
    ~QsciLexerText();

    const char *language() const override;
    QString description(int style) const override;
    void styleText(int start, int end) override;
};

#endif // QSCILEXERTEXT_H
