#ifndef QSCILEXERQSS_H
#define QSCILEXERQSS_H

#include <qsci/qscilexercustom.h>

class QsciLexerQSS : public QsciLexerCustom
{
    Q_OBJECT

public:
    enum {
        Default = 0,
        Tag = 1,
        IDSelector = 2,
        ClassSelector = 3,
        PseudoElement = 4,
        PseudoClass = 5,
        Attribute = 6,
        Operator = 7,
        Property = 8,
        Value = 9,
        Comment = 10,
        DoubleQuotedString = 11,
        SingleQuotedString = 12,
        Variable = 13,
        Param = 14,
    };

    QStringList namelist = {
        "Default",
        "Tag",
        "IDSelector",
        "ClassSelector",
        "PseudoElement",
        "PseudoClass",
        "Attribute",
        "Operator",
        "Property",
        "Value",
        "Comment",
        "DoubleQuotedString",
        "SingleQuotedString",
        "Variable",
        "Param",
    };

    QStringList operatorList = {
                                "{",
                                "}",
                                "[",
                                "]",
                                "(",
                                ")",
                                "::",
                                ".",
                                ":",
                                ";",
                                ",",
                                "/*",
                                "*/",
                                "#",
                                "$",
                                "=",
                                "\"",
                                "'",
                                "\r",
                                "\n",
                                };

    QStringList unitList = {
        "pt",
        "px",
        "ex",
        "em",
    };

private:
    QsciScintilla *mEditor;

public:
    explicit QsciLexerQSS(QObject *parent = nullptr, QsciScintilla *editor = nullptr);
    ~QsciLexerQSS();

    void setDefaultStyle();
    void setQssAutocomplete();

    bool isOperator(QString aChar);

    const char *language() const override;
    QString description(int style) const override;
    const char *keywords(int set) const override;
    void styleText(int start, int end) override;
};

#endif // QSCILEXERQSS_H
