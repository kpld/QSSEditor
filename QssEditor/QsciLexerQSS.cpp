#include "QsciLexerQSS.h"
#include <qsci/qsciscintilla.h>
//#include <qsci/qsciscintillabase.h>
#include <qsci/qsciapis.h>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


QsciLexerQSS::QsciLexerQSS(QObject *parent, QsciScintilla *editor)
    : QsciLexerCustom{parent}
    , mEditor(editor)
{
    if (editor == NULL) {
        mEditor = (QsciScintilla*)parent;
    }

    setDefaultStyle();
    setQssAutocomplete();

    // QsciAPIs*apis = new QsciAPIs(this);

    // apis->add("if");
    // apis->add("for");
    // apis->add("else");
    // apis->add("include");
    // apis->add("while");

    // apis->prepare();
    // setAPIs(apis);


}

QsciLexerQSS::~QsciLexerQSS()
{

}

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

    mEditor->SendScintilla(QsciScintilla::SCI_MARKERSETBACK, QsciScintilla::SC_MARKNUM_FOLDERSUB, QColor("0xa0a0a0"));
    mEditor->SendScintilla(QsciScintilla::SCI_MARKERSETBACK, QsciScintilla::SC_MARKNUM_FOLDERMIDTAIL, QColor("0xa0a0a0"));
    mEditor->SendScintilla(QsciScintilla::SCI_MARKERSETBACK, QsciScintilla::SC_MARKNUM_FOLDERTAIL, QColor("0xa0a0a0"));
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

const char* QsciLexerQSS::language() const
{
    return "QSS";
}

QString QsciLexerQSS::description(int style) const
{
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

bool QsciLexerQSS::isOperator(QString aChar)
{
    if (aChar.length() <= 0) return false;

    if (!aChar[0].isPrint()) {
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

void QsciLexerQSS::styleText(int start, int end)
{
    QString allText = this->editor()->text();//.mid(start, end-start);
    //qDebug()<<text;

    QByteArray textArray = allText.toUtf8();
    while(start > 0) {
        if (textArray.at(start) == '{' || start == 0) {
            break;
        }
        start--;
    }

    this->startStyling(start);
    QString text = QString(textArray.mid(start, end-start+1));  ///////////////*************
    //text = this->editor()->text().mid(start, end-start);

    //static QRegularExpression re("[\\x{0080}-\\x{ffff}]+|\\/[*]|[*]\\/|\\w+|\\s+|\\/\\/|::|\r|\n|[*]+|=+|\"|'|\\W");  // good
    static QRegularExpression re("\\/[*]|[*]\\/|\\/\\/|::|\r\n|\\s+|[*]+|=+|\"|'|\\W|\\w+|[\\x{0080}-\\x{ffff}]+|");

    QRegularExpressionMatchIterator iter = re.globalMatch(text);
    QStringList tokenList;
    while (iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        QString matched = match.captured(0);
        if (matched.length() > 0) {
            tokenList<<matched;
        }
    }

    int state = -1;
    int lastState = -1;
    QString opPrev = " ";
    bool inBrace = /*{}*/false, inBracket = /*[]*/false, inParentheses = /*()*/false;
    for(int var=0; var<tokenList.size(); var++) {
        QString token = tokenList.at(var);
        // if (token == "不") {
        //     qDebug()<<token;
        // }
        // if (start != 0) {
        //     qDebug()<<token;
        // }
        // if (token == "才") {
        //     qDebug()<<token;
        // }
        int token_len = token.toUtf8().length();
        if (text.length() == text.toUtf8().length()) {
            //token_len = token.length();
        }

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
                state = inBrace ? Property : Tag;
                // if (inBrace) {
                //     state = Property;
                // } else {
                //     state = Tag;
                // }
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
                state = inBracket ? Attribute : Value;
                // if (inBracket) {
                //     state = Attribute;
                // } else {
                //     state = Value;
                // }
            } else if (token == "{") {
                state = Property;
                inBrace = true;
            } else if (token == "}") {
                state = Tag;
                inBrace = false;
            } else if (token == ":") {
                state = inBrace ? Value : PseudoClass;
                // if (inBrace) {
                //     state = Value;
                // } else {
                //     state = PseudoClass;
                // }
            } else if (token == "::") {
                lastState = Property;
                state = PseudoElement;
            } else if (token == "#") {
                state = inBrace ? Param : IDSelector;
                // if (inBrace) {
                //     state = Param;
                // } else {
                //     state = IDSelector;
                // }
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

    // Folding Setting
    int index=0, level=0, lastLevel=0;
    index = this->editor()->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION, 0);
    if (!index) {
        level = QsciScintilla::SC_FOLDLEVELBASE;
    } else {
        lastLevel = this->editor()->SendScintilla(QsciScintilla::SCI_GETFOLDLEVEL, index-1);
        level = lastLevel;
    }

    QStringList lineList = allText.split(QRegularExpression("(?<=\r\n)"), Qt::KeepEmptyParts);
    int nCount = lineList.count();
    for(int var=0; var<nCount; var++) {
        QString line = lineList.at(var);
        if (line.length() <= 0) continue;

        int open_count = line.count("{");
        int close_count = line.count("}");
        bool isBlankLine = line.isEmpty();
        int flag = 0x000;

        if (isBlankLine) {
            flag = QsciScintilla::SC_FOLDLEVELWHITEFLAG;
        } else if (open_count > close_count) {
            flag = QsciScintilla::SC_FOLDLEVELHEADERFLAG;
        } else {
            flag &= QsciScintilla::SC_FOLDLEVELNUMBERMASK;
        }

        this->editor()->SendScintilla(QsciScintilla::SCI_SETFOLDLEVEL, index, level | flag);
        level += open_count;
        level -= close_count;
        index += 1;
    }

}
