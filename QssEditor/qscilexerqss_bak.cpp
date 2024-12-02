// This module implements the QsciLexerQSS class.
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


#include "qsciLexerqss.h"
//#include "Scintilla.h"
#include <Qsci/qsciapis.h>
#include <Qsci/qsciscintillabase.h>
#include <QEventLoop>
#include <QRegularExpression>
// #include <qcolor.h>
// #include <qfont.h>
// #include <qsettings.h>


// The ctor.
QsciLexerQSS::QsciLexerQSS(QObject *parent)
    : QsciLexerCustom(parent)
{
    // QsciAPIs *api = new QsciAPIs(this);

    // QString keys = QString(keywords(1)) + " " + QString(keywords(2)) + " " + QString(keywords(3)) + " " + QString(keywords(4));
    // QStringList keylist = keys.split(' ');
    // keylist.removeDuplicates();
    // foreach (const QString &word, keylist) {
    //     api->add(word);
    // }

    // QEventLoop loop;
    // connect(api, SIGNAL(apiPreparationFinished()), &loop, SLOT(quit()));
    // api->prepare();
    // loop.exec();

    // setAPIs(api);


    setDefaultStyle();
    setQssAutocomplete();
}


// The dtor.
QsciLexerQSS::~QsciLexerQSS()
{
}


// Returns the language name.
const char *QsciLexerQSS::language() const
{
    return "QSS";
}

// const char *QsciLexerQSS::lexer() const
// {
//     return "qss";
// }

void QsciLexerQSS::setDefaultStyle()
{
    // Default text settings
    setDefaultColor(QColor("#ff000000"));
    setDefaultPaper(QColor("#ffffffff"));
    setDefaultFont(QFont("Consolas", 12));
    // int nameCount = sizeof(namelist)/sizeof(namelist[0]);
    // for(int var=0; var<nameCount; var++) {
    //     setFont(QFont("Consolas", 12), var);
    // }

    // Initialize colors per style
    setColor(QColor("#000"), this->Default);
    setColor(QColor("#099"), this->Tag); // 青色
    setColor(QColor("#a11"), this->IDSelector); // 紫红969
    setColor(QColor("#a11"), this->ClassSelector);
    setColor(QColor("#a11"), this->PseudoElement);
    setColor(QColor("#a11"), this->PseudoClass);
    setColor(QColor("#aaa"), this->Attribute); // 浅灰
    setColor(QColor("gray"), this->Operator);
    setColor(QColor("#04e"), this->Property); // 浅蓝03c
    setColor(QColor("#808"), this->Value); // 深红 a11
    setColor(QColor("gray"), this->Comment); // 灰
    setColor(QColor("#690"), this->DoubleQuotedString); // 浅绿
    setColor(QColor("#690"), this->SingleQuotedString);
    setColor(QColor("#a60"), this->Variable); // 05a深蓝
    setColor(QColor("#aaa"), this->Param); // 浅灰
}

QString QsciLexerQSS::description(int style) const
{
    // QString namelist[15] = {
    //     tr("Default"),
    //     tr("Tag"),
    //     tr("IDSelector"),
    //     tr("ClassSelector"),
    //     tr("PseudoElement"),
    //     tr("PseudoClass"),
    //     tr("Attribute"),
    //     tr("Operator"),
    //     tr("Property"),
    //     tr("Value"),
    //     tr("Comment"),
    //     tr("DoubleQuotedString"),
    //     tr("SingleQuotedString"),
    //     tr("Variable"),
    //     tr("Param"),
    // };
    switch (style)
    {
    case Default:
        return tr("Default");

    case Tag:
        return tr("Tag");

    case IDSelector:
        return tr("IDSelector");

    case ClassSelector:
        return tr("ClassSelector");

    case PseudoElement:
        return tr("PseudoElement");

    case PseudoClass:
        return tr("PseudoClass");

    case Attribute:
        return tr("Attribute");

    case Operator:
        return tr("Operator");

    case Property:
        return tr("Property");

    case Value:
        return tr("Value");

    case Comment:
        return tr("Comment");

    case DoubleQuotedString:
        return tr("DoubleQuotedString");

    case SingleQuotedString:
        return tr("SingleQuotedString");

    case Variable:
        return tr("Variable");

    case Param:
        return tr("Param");
    }

    return QString();
}

void QsciLexerQSS::setQssAutocomplete()
{
    QStringList widgets = {"QAbstractScrollArea", "QButton", "QCheckBox", "QColumnView", "QComboBox", "QDateEdit", "QDateTimeEdit",
           "QDialog", "QDialogButtonBox", "QDockWidget", "QDoubleSpinBox", "QFrame", "QGroupBox", "QHeaderView",
           "QLabel", "QLineEdit", "QListView", "QListWidget", "QMainWindow", "QMenu", "QMenuBar", "QMessageBox",
           "QProgressBar", "QPushButton", "QRadioButton", "QScrollBar", "QSizeGrip", "QSlider", "QSpinBox",
           "QSplitter", "QStatusBar", "QTabBar", "QTabWidget", "QTableView", "QTableWidget", "QTextEdit",
           "QTimeEdit", "QToolBar", "QToolButton", "QToolBox", "QToolTip", "QTreeView", "QTreeWidget",
           "QWidget"};
    QStringList properties = {"alternate-background-color", "background", "background-color", "background-image",
           "background-repeat", "background-position", "background-attachment", "background-clip",
           "background-origin", "border", "border-top", "border-right", "border-bottom", "border-left",
           "border-color", "border-top-color", "border-right-color", "border-bottom-color",
           "border-left-color", "border-image", "border-radius", "border-top-left-radius",
           "border-top-right-radius", "border-bottom-right-radius", "border-bottom-left-radius",
           "border-style", "border-top-style", "border-right-style", "border-bottom-style",
           "border-left-style", "border-width", "border-top-width", "border-right-width",
           "border-bottom-width", "border-left-width", "bottom", "button-layout", "color",
           "dialogbuttonbox-buttons-have-icons", "font", "font-family", "font-size", "font-style",
           "font-weight", "gridline-color", "height", "icon-size", "image", "image-position", "left",
           "lineedit-password-character", "lineedit-password-mask-delay", "margin", "margin-top",
           "margin-right", "margin-bottom", "margin-left", "max-height", "max-width",
           "messagebox-text-interaction-flags", "min-height", "min-width", "opacity*", "outline",
           "outline-color", "outline-offset", "outline-style", "outline-radius",
           "outline-bottom-left-radius", "outline-bottom-right-radius", "outline-top-left-radius",
           "outline-top-right-radius", "padding", "padding-top", "padding-right", "padding-bottom",
           "padding-left", "paint-alternating-row-colors-for-empty-area", "position", "right",
           "selection-background-color", "selection-color", "show-decoration-selected", "spacing",
           "subcontrol-origin", "subcontrol-position", "titlebar-show-tooltips-on-buttons",
            "widget-animation-duration", "text-align", "text-decoration", "top", "width"};
    QStringList subcontrols = {"add-line", "add-page", "branch", "chunk", "close-button", "corner", "down-arrow", "down-button",
           "drop-down", "float-button", "groove", "indicator", "handle", "icon", "item", "left-arrow",
           "left-corner", "menu-arrow", "menu-button", "menu-indicator", "right-arrow", "pane",
           "right-corner", "scroller", "section", "separator", "sub-line", "sub-page", "tab", "tab-bar",
           "tear", "tearoff", "text", "title", "up-arrow", "up-button"};
    QStringList pseudostates = {"active", "adjoins-item", "alternate", "bottom", "checked", "closable", "closed", "default",
           "disabled", "editable", "edit-focus", "enabled", "exclusive", "first", "flat", "floatable",
           "focus", "has-children", "has-siblings", "horizontal", "hover", "indeterminate", "last", "left",
           "maximized", "middle", "minimized", "movable", "no-frame", "non-exclusive", "off", "on",
           "only-one", "open", "next-selected", "pressed", "previous-selected", "read-only", "right",
           "selected", "top", "unchecked", "vertical", "window"};

    QsciAPIs *api = new QsciAPIs(this);
    QStringList allkey;
    allkey<<widgets<<properties<<subcontrols<<pseudostates;
    allkey.removeDuplicates();
    foreach(auto ks, allkey) {
        api->add(ks);
    }
    api->prepare();
    setAPIs(api);
}

void QsciLexerQSS::styleText(int start, int end)
{
    QString text = this->editor()->text().mid(start, end-start);

    while(start > 0) {
        if (text.at(start) == '{' || start == 0) {
            break;
        }
        start--;
    }

    this->startStyling(start);
    text = this->editor()->text().mid(start, end-start);

    static QRegularExpression re("\\/[*]|[*]\\/|\\/\\/|::|\r|\n|\\s+|[*]+|=+|\"|'|\\W|\\w+|[\u0080-\uffff]+");
    QRegularExpressionMatch match = re.match(text);
    QStringList tokenList;
    if (match.hasMatch()) {
        int count = match.capturedLength();
        for (int var=1; var<=count; var++) {
            QString result = match.captured(count);
            tokenList.append(result);
        }
    }

    int state = -1;
    int lastState = -1;
    QString opPrev = " ";
    bool inBrace = false, inBracket = false, inParentheses = false;
    for(int var=0; var<tokenList.size(); var++) {
        QString token = tokenList.at(var);
        int token_len = token.length();

        if (state == Comment) {
            if (token == "*/") {
                setStyling(token_len, Operator);
                if (inBrace) {
                    lastState = state;
                    state = Property;
                } else {
                    lastState = state;
                    state = Tag;
                }
            } else {
                setStyling(token_len, Comment);
            }
        } else if (state == DoubleQuotedString) {
            if (token == "\"") {
                // lastState = state;
                // state = lastState;
                qSwap(lastState, state);
            }
            setStyling(token_len, DoubleQuotedString);
        } else if (state == SingleQuotedString) {
            if (token == "'") {
                qSwap(lastState, state);
            }
            setStyling(token_len, SingleQuotedString);
        } else if (inParentheses) {
            if (token == ")") {
                inParentheses = false;
                qSwap(lastState, state);
                setStyling(token_len, Operator);
            } else {
                setStyling(token_len, Param);
            }
        } else if (isOperator(token)) {
            bool opStyle = true;

            lastState = state;
            if (token == "/*") {
                state = Comment;
            } else if (token == "*/") {
                lastState = Comment;
                if (inBrace) {
                    state = Property;
                } else {
                    state = Tag;
                }
            } else if (token == "\"") {
                state = DoubleQuotedString;
                opStyle = false;
            } else if (token == "'") {
                state = SingleQuotedString;
                opStyle = false;
            } else if (token == "$") {
                state = Variable;
                opStyle = false;
            } else if (token == "=") {
                if (inBracket) {
                    state = Attribute;
                } else {
                    state = Value;
                }
            } else if (token == "{") {
                state = Property;
                inBrace = true;
            } else if (token == "}") {
                state = Tag;
                inBrace = false;
            } else if (token == ":") {
                if (inBrace) {
                    state = Value;
                } else {
                    state = PseudoClass;
                }
            } else if (token == "::") {
                lastState = Property;
                state = PseudoElement;
            } else if (token == "#") {
                if (inBrace) {
                    state = Param;
                } else {
                    state = IDSelector;
                }
            } else if (token == "[") {
                lastState = Property;
                state = Attribute;
                inBracket = true;
            } else if (token == "]") {
                state = Tag;
                inBracket = false;
            } else if (token == "(") {
                state = Param;
                inParentheses = true;
            } else if (token == ")") {
                state = lastState;
                inParentheses = false;
            } else if (token == ",") {
                if (!inBrace) {
                    lastState = state;
                    state = Tag;
                }
            } else if (token == ";") {
                if (opPrev == "=") {
                    state = Tag;
                } else {
                    state = Property;
                }
            } else if (token.contains("\r") || token.contains("\n")) {
                if (opPrev == "=") {
                    state = Tag;
                }
            } else {
                state = lastState;
            }

            opPrev = token;
            if (opStyle) {
                setStyling(token_len, Operator);
            } else {
                setStyling(token_len, state);
            }
        } else {
            setStyling(token_len, state);
        }
    }

    // int index = this->editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION, start);
    // int level = 0, lastLevel = 0;
    // if (!index) {
    //     level = QsciScintillaBase::SC_FOLDLEVELBASE;
    // } else {
    //     lastLevel = this->editor()->SendScintilla(QsciScintillaBase::SCI_GETFOLDLEVEL, index-1);
    //     level = lastLevel;
    // }

    // QStringList lineList = text.split("\r\n");
    // int nCount = lineList.count();
    // for(int var=0; var<nCount; var++) {

    // }
}

bool QsciLexerQSS::isOperator(QString aChar)
{
    if (!aChar[0].isLetterOrNumber()) {
        return false;
    } else {
        if (operatorList.contains(aChar)) {
            return true;
        }
    }

    return false;
}

const char *QsciLexerQSS::keywords(int set) const
{
    if (set == 1) {
        return "QAbstractScrollArea QButton QCheckBox QColumnView QComboBox QDateEdit QDateTimeEdit "
               "QDialog QDialogButtonBox QDockWidget QDoubleSpinBox QFrame QGroupBox QHeaderView "
               "QLabel QLineEdit QListView QListWidget QMainWindow QMenu QMenuBar QMessageBox "
               "QProgressBar QPushButton QRadioButton QScrollBar QSizeGrip QSlider QSpinBox "
               "QSplitter QStatusBar QTabBar QTabWidget QTableView QTableWidget QTextEdit "
               "QTimeEdit QToolBar QToolButton QToolBox QToolTip QTreeView QTreeWidget "
               "QWidget";
    } else if (set == 2) {
        return "alternate-background-color background background-color background-image "
               "background-repeat background-position background-attachment background-clip "
               "background-origin border border-top border-right border-bottom border-left "
               "border-color border-top-color border-right-color border-bottom-color "
               "border-left-color border-image border-radius border-top-left-radius "
               "border-top-right-radius border-bottom-right-radius border-bottom-left-radius "
               "border-style border-top-style border-right-style border-bottom-style "
               "border-left-style border-width border-top-width border-right-width "
               "border-bottom-width border-left-width bottom button-layout color "
               "dialogbuttonbox-buttons-have-icons font font-family font-size font-style "
               "font-weight gridline-color height icon-size image image-position left "
               "lineedit-password-character lineedit-password-mask-delay margin margin-top "
               "margin-right margin-bottom margin-left max-height max-width "
               "messagebox-text-interaction-flags min-height min-width opacity* outline "
               "outline-color outline-offset outline-style outline-radius "
               "outline-bottom-left-radius outline-bottom-right-radius outline-top-left-radius "
               "outline-top-right-radius padding padding-top padding-right padding-bottom "
               "padding-left paint-alternating-row-colors-for-empty-area position right "
               "selection-background-color selection-color show-decoration-selected spacing "
               "subcontrol-origin subcontrol-position titlebar-show-tooltips-on-buttons "
               "widget-animation-duration text-align text-decoration top width";
    } else if (set == 3) {
        return "add-line add-page branch chunk close-button corner down-arrow down-button "
               "drop-down float-button groove indicator handle icon item left-arrow "
               "left-corner menu-arrow menu-button menu-indicator right-arrow pane "
               "right-corner scroller section separator sub-line sub-page tab tab-bar "
               "tear tearoff text title up-arrow up-button";
    } else if (set == 4) {
        return "active adjoins-item alternate bottom checked closable closed default "
               "disabled editable edit-focus enabled exclusive first flat floatable "
               "focus has-children has-siblings horizontal hover indeterminate last left "
               "maximized middle minimized movable no-frame non-exclusive off on "
               "only-one open next-selected pressed previous-selected read-only right "
               "selected top unchecked vertical window";
    }

    return NULL;
}
