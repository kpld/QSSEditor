// This defines the interface to the QsciLexerQSS class.
//
// Copyright (c) 2020 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of QScintilla.
// 
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the Free Software Foundation and appearing in
// the file LICENSE included in the packaging of this file.  Please review the
// following information to ensure the GNU General Public License version 3.0
// requirements will be met: http://www.gnu.org/copyleft/gpl.html.
// 
// If you do not wish to use this file under the terms of the GPL version 3.0
// then you may purchase a commercial license.  For more information contact
// info@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#ifndef QsciLexerQSS_H
#define QsciLexerQSS_H
#include <Qsci/qscilexercustom.h>



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

    explicit QsciLexerQSS(QObject *parent = nullptr);
    ~QsciLexerQSS();

    const char *language() const override;
    //const char *lexer() const override;

    void setDefaultStyle();
    void setQssAutocomplete();
    QString description(int style) const override;

    void styleText(int start, int end) override;
    const char *keywords(int set) const override;

private:
    bool isOperator(QString aChar);
};

#endif
