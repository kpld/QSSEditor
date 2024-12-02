#include "Editor.h"
#include "QsciLexerQSS.h"
#include "QsciLexerText.h"
#include "SearchDialog.h"
#include <QMimeData>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QIODevice>
#include <Qsci/qscilexerasm.h>
#include <Qsci/qscilexeravs.h>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerbatch.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercoffeescript.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qscilexercss.h>
#include <Qsci/qscilexerd.h>
#include <Qsci/qscilexerdiff.h>
#include <Qsci/qscilexeredifact.h>
#include <Qsci/qscilexerfortran.h>
#include <Qsci/qscilexerfortran77.h>
#include <Qsci/qscilexerhex.h>
#include <Qsci/qscilexerhtml.h>
#include <Qsci/qscilexeridl.h>
#include <Qsci/qscilexerintelhex.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerjson.h>
#include <Qsci/qscilexerlua.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexermarkdown.h>
#include <Qsci/qscilexermasm.h>
#include <Qsci/qscilexermatlab.h>
#include <Qsci/qscilexernasm.h>
#include <Qsci/qscilexeroctave.h>
#include <Qsci/qscilexerpascal.h>
#include <Qsci/qscilexerperl.h>
#include <Qsci/qscilexerpo.h>
#include <Qsci/qscilexerpostscript.h>
#include <Qsci/qscilexerpov.h>
#include <Qsci/qscilexerproperties.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerruby.h>
#include <Qsci/qscilexerspice.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexersrec.h>
#include <Qsci/qscilexertcl.h>
#include <Qsci/qscilexertekhex.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexervhdl.h>
#include <Qsci/qscilexerxml.h>
#include <Qsci/qscilexeryaml.h>



QMap<QString,QString> typeList = {
    {"68746D6C3E", "html"},
    {"d0cf11e0a1b11ae10000", "xls"},
    {"44656C69766572792D64", "eml"},
    {"ffd8ffe000104a464946", "jpg"},
    {"89504e470d0a1a0a0000", "png"},
    {"47494638396126026f01", "gif"},
    {"49492a00227105008037", "tif"},
    {"424d228c010000000000", "bmp"},
    {"424d8240090000000000", "bmp"},
    {"424d8e1b030000000000", "bmp"},
    {"41433130313500000000", "dwg"},
    {"3c21444f435459504520", "html"},
    {"3c21646f637479706520", "htm"},
    {"48544d4c207b0d0a0942", "css"},
    {"696b2e71623d696b2e71", "js"},
    {"7b5c727466315c616e73", "rtf"},
    {"38425053000100000000", "psd"},
    {"46726f6d3a203d3f6762", "eml"},
    {"d0cf11e0a1b11ae10000", "doc"},
    {"d0cf11e0a1b11ae10000", "vsd"},
    {"5374616E64617264204A", "mdb"},
    {"252150532D41646F6265", "ps"},
    {"255044462d312e350d0a", "pdf"},
    {"2e524d46000000120001", "rmvb"},
    {"464c5601050000000900", "flv"},
    {"00000020667479706d70", "mp4"},
    {"49443303000000002176", "mp3"},
    {"000001ba210001000180", "mpg"},
    {"3026b2758e66cf11a6d9", "wmv"},
    {"52494646e27807005741", "wav"},
    {"52494646d07d60074156", "avi"},
    {"4d546864000000060001", "mid"},
    {"504b0304140000080044", "zip"},
    {"504b03040a0000080000", "zip"},
    {"504b03040a0000000000", "zip"},
    {"526172211a0700cf9073", "rar"},
    {"235468697320636f6e66", "ini"},
    {"504b03040a0000000000", "jar"},
    {"4d5a9000030000000400", "exe"},
    {"3c25402070616765206c", "jsp"},
    {"4d616e69666573742d56", "mf"},
    {"3c3f786d6c2076657273", "xml"},
    {"494e5345525420494e54", "sql"},
    {"7061636b616765207765", "java"},
    {"406563686f206f66660d", "bat"},
    {"1f8b0800000000000000", "gz"},
    {"6c6f67346a2e726f6f74", "properties"},
    {"cafebabe0000002e0041", "class"},
    {"49545346030000006000", "chm"},
    {"04000000010000001300", "mxp"},
    {"504b0304140006000800", "docx"},
    {"d0cf11e0a1b11ae10000", "wps"},
    {"6431303a637265617465", "torrent"},
};

QStringList binfiletypes = {
    "xls", "eml", "jpg", "png", "gif", "tif", "bmp", "bmp", "bmp", "dwg", "psd", "eml", "doc", "vsd", "mdb", "ps",
    "pdf", "rmvb", "flv", "mp4", "mp3", "mpg", "wmv", "wav", "avi", "mid", "zip", "zip", "zip", "rar", "jar", "exe",
    "gz", "class", "chm", "mxp", "docx", "wps"
};

QMap<QString,QString> textfiletypes = {
    {"html","HTML"},
    {"htm", "HTML"},
    {"css", "CSS"},
    {"js",  "JavaScript"},
    {"rtf", "Text"},
    {"ini", "Text"},
    {"jsp", "Text"},
    {"mf",  "Text"},
    {"xml", "XML"},
    {"sql", "SQL"},
    {"java","Java"},
    {"bat", "Batch"},
    {"properties", "Text"},
    {"torrent", "XML"},
};

QString language_extensions[][2] = {
    //  {"None", ".txt .text"},
    {"Text", ".txt .text .rtf .ini .jsp .mf .properties"},
    {"QSS", ".qss .qsst"},
    {"Bash", ".sh .bashrc .bash_history"},
    {"Batch", ".bat .cmd"},
    {"CMake", ".cmake"},
    {"CPP", ".c++ .cpp .cxx .cc .hh .hxx .hpp .c .h"},
    {"CSharp", ".cs"},
    {"CSS", ".css"},
    {"CoffeeScript", ".coffee"},
    {"D", ".d"},
    {"Diff", ".diff"},
    {"Fortran", ".f"},
    {"Fortran77", ".f77 .f90"},
    {"HTML", ".html .htm"},
    {"IDL", ".idl"},
    {"JSON", ".json"},
    {"Java", ".java"},
    {"JavaScript", ".js"},
    {"Lua", ".lua"},
    {"Makefile", ".make .mk .makefile"},
    {"Markdown", ".md .markdown"},
    {"Matlab", ".m"},
    {"Pascal", ".pas"},
    {"Perl", ".pl"},
    {"PostScript", ".ps .eps .ai"},
    {"POV", ".pov"},
    {"Properties", ".properties"},
    {"Python", ".py .pyw"},
    {"Ruby", ".rb"},
    {"SQL", ".sql"},
    {"TCL", ".tcl"},
    {"TeX", ".tex .latex"},
    {"VHDL", ".vhd .vhdl"},
    {"Verilog", ".v"},
    {"XML", ".xml .svg"},
    {"YAML", ".yaml .yml .torrent"},
};


Editor::Editor()
{
    encoding = "utf-8";

    searchDialog = new SearchDialog(/*this*/);

    setDefaultConfig();
}

Editor::~Editor()
{
    if (searchDialog) {
        delete searchDialog;
        searchDialog = NULL;
    }
}

void Editor::setDefaultConfig()
{
    setWrapMode(WrapNone);
    setWrapVisualFlags(WrapFlagNone);
    setEolVisibility(false);

    setWhitespaceVisibility(WsInvisible);
    setWhitespaceSize(2);

    setIndentationsUseTabs(true);
    setTabWidth(4);
    setIndentationGuides(true);
    setIndentationWidth(0);
    setAutoIndent(true);
    setBackspaceUnindents(true);
    setTabIndents(true);

    setCaretWidth(2);
    setCaretForegroundColor(QColor("#ff000000"));
    setCaretLineVisible(true);
    setCaretLineBackgroundColor(QColor("#FFF0F0F0"));

    setEdgeColumn(80);
    setEdgeMode(EdgeLine);
    setEdgeColor(QColor("#FF88FFFF"));

    setBraceMatching(SloppyBraceMatch);

    setAutoCompletionSource(AcsAll);
    setAutoCompletionCaseSensitivity(false);
    setAutoCompletionThreshold(1);
    setAutoCompletionReplaceWord(true);

    // setMarginWidth(1, 0);
    // setMarginWidth(3, 0);
    // setMarginWidth(4, 0);

    // setMarginLineNumbers(0, true);
    // setMarginsForegroundColor(QColor("#ff000000"));
    // setMarginsBackgroundColor(QColor("lightgray"));

    // setFolding(BoxedTreeFoldStyle);
    // setFoldMarginColors(QColor("#aad"), QColor("#bbe"));
}

QString Editor::getEncoding()
{
    return encoding;
}

bool Editor::load(QString fileName)
{
    encoding = "utf-8";
    setText("");
    QString fileType = getFileType(fileName);
    QFile *f = new QFile(fileName);
    f->open(QIODevice::ReadWrite);
    QByteArray strBytes = f->readAll();
    f->close();

    if (binfiletypes.contains(fileType)) {
        setEnabled(true);
        encoding = "unknown";
        setText(strBytes);
        setLanguage("None");
    } else {
        setEnabled(true);
        encoding = detectEncoding(fileName).toLower();
        if (encoding == "utf-8") {
            setText(strBytes);
        } else {
            QTextCodec* utf8Codec = QTextCodec::codecForName("utf-8");
            QTextCodec* otherCodec = QTextCodec::codecForName(encoding.toStdString().c_str());
            //qDebug(strBytes);
            QString strUnicode = otherCodec ->toUnicode(strBytes.data());
            QString strAll = utf8Codec ->fromUnicode(strUnicode);
            //qDebug(strAll.toStdString().c_str());
            setText(strAll);
        }

        setModified(false);
        if (textfiletypes.contains(fileType)) {
            setLanguage(textfiletypes[fileType]);
        } else {
            setLanguage(guessLanguage(fileName));
        }

        return true;
    }

    return true;
}

QString Editor::getFileType(QString fileName)
{
    QString ftype = "unknown";

    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadWrite);
    QByteArray bins = file->read(20);
    file->close();
    bins = bins.toLower();

    QMap<QString, QString>::iterator iter;
    for(iter=typeList.begin(); iter!=typeList.end(); iter++){
        QString key = iter.key();
        QString val = iter.value();
        int len = key.length();
        if(QString(bins.left(len)) == key) {
            ftype = val;
            break;
        }
    }

    if (ftype == "unknown") {
        bins = bins.left(5);
        for(iter=typeList.begin(); iter!=typeList.end(); iter++){
            QString key = iter.key();
            QString val = iter.value();
            int len = key.length();
            if (len > 5 && QString(bins) == key.left(5)) {
                ftype = val;
                break;
            }
        }
    }

    return ftype;
}

void Editor::setLanguage(QString language)
{
    if (language.isEmpty() || language == "None") {
        language = "Text";
    }

    QsciLexer *lexer= NULL;
    if (language == "Text") {
        lexer = new QsciLexerText(this);
    } else if (language == "QSS") {
        lexer = new QsciLexerQSS(this);
    } else if (language == "Bash") {
        lexer = new QsciLexerBash(this);
    } else if (language == "Batch") {
        lexer = new QsciLexerBatch(this);
    } else if (language == "CMake") {
        lexer = new QsciLexerCMake(this);
    } else if (language == "CPP") {
        lexer = new QsciLexerCPP(this);
    } else if (language == "CSharp") {
        lexer = new QsciLexerCSharp(this);
    } else if (language == "CSS") {
        lexer = new QsciLexerCSS(this);
    } else if (language == "CoffeeScript") {
        lexer = new QsciLexerCoffeeScript(this);
    } else if (language == "D") {
        lexer = new QsciLexerD(this);
    } else if (language == "Diff") {
        lexer = new QsciLexerDiff(this);
    } else if (language == "Fortran") {
        lexer = new QsciLexerFortran(this);
    } else if (language == "Fortran77") {
        lexer = new QsciLexerFortran77(this);
    } else if (language == "HTML") {
        lexer = new QsciLexerHTML(this);
    } else if (language == "IDL") {
        lexer = new QsciLexerIDL(this);
    } else if (language == "JSON") {
        lexer = new QsciLexerJSON(this);
    } else if (language == "Java") {
        lexer = new QsciLexerJava(this);
    } else if (language == "JavaScript") {
        lexer = new QsciLexerJavaScript(this);
    } else if (language == "Lua") {
        lexer = new QsciLexerLua(this);
    } else if (language == "Makefile") {
        lexer = new QsciLexerMakefile(this);
    } else if (language == "Markdown") {
        lexer = new QsciLexerMarkdown(this);
    } else if (language == "Matlab") {
        lexer = new QsciLexerMatlab(this);
    } else if (language == "Pascal") {
        lexer = new QsciLexerPascal(this);
    } else if (language == "Perl") {
        lexer = new QsciLexerPerl(this);
    } else if (language == "PostScript") {
        lexer = new QsciLexerPostScript(this);
    } else if (language == "POV") {
        lexer = new QsciLexerPOV(this);
    } else if (language == "Properties") {
        lexer = new QsciLexerProperties(this);
    } else if (language == "Python") {
        lexer = new QsciLexerPython(this);
    } else if (language == "Ruby") {
        lexer = new QsciLexerRuby(this);
    } else if (language == "SQL") {
        lexer = new QsciLexerSQL(this);
    } else if (language == "TCL") {
        lexer = new QsciLexerTCL(this);
    } else if (language == "TeX") {
        lexer = new QsciLexerTeX(this);
    } else if (language == "VHDL") {
        lexer = new QsciLexerVHDL(this);
    } else if (language == "Verilog") {
        lexer = new QsciLexerVerilog(this);
    } else if (language == "XML") {
        lexer = new QsciLexerXML(this);
    } else if (language == "YAML") {
        lexer = new QsciLexerYAML(this);
    }

    setLexer(lexer);
}

QString Editor::guessLanguage(QString fileName)
{
    QStringList names = fileName.split(".");

    int count = sizeof(language_extensions)/sizeof(language_extensions[2]);
    for(int var=0; var<count; var++) {
        QString lexer = language_extensions[var][0];
        QString exts  = language_extensions[var][1];

        QStringList extList = exts.split(" ");
        if (extList.contains("." + names[1])) {
            return lexer;
        }
    }

    return "None";
}

enum EncodingFormat
{
    ANSI,
    UTF16LE,
    UTF16BE,
    UTF8,
    UTF8BOM,
};

QString Editor::detectEncoding(QString fileName)
{
    EncodingFormat encoding = EncodingFormat::UTF8;
    QString codecName = "UTF-8";
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray buffer = file.readAll();
        if (buffer.startsWith("\xEF\xBB\xBF")) {
            encoding = EncodingFormat::UTF8BOM;
            codecName = "UTF-8-BOM";
        } else if (buffer.startsWith("\xFF\xFE")) {
            encoding = EncodingFormat::UTF16LE;
            codecName = "UTF-16LE";
        } else if (buffer.startsWith("\xFE\xFF")) {
            encoding = EncodingFormat::UTF16BE;
            codecName = "UTF-16BE";
        } else {
            QTextCodec::ConverterState state;
            QTextCodec *codec = QTextCodec::codecForName("utf-8");
            codec->toUnicode(buffer.constData(), buffer.size(), &state);
            if (state.invalidChars > 0) {
                encoding = EncodingFormat::ANSI;
                codecName = "GB18030";
            } else {
                encoding = EncodingFormat::UTF8;
                codecName = "UTF-8";
            }
        }

        file.close();
    }

    return codecName;
}

void Editor::save(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite)) return;
    file.write(this->text().toUtf8());
    file.close();
    setModified(false);
}

void Editor::keyPressEvent(QKeyEvent *e)
{
    QsciScintilla::keyPressEvent(e);
    emit keyPress(e);
}

void Editor::focusOutEvent(QFocusEvent *e)
{
    QsciScintilla::focusOutEvent(e);
    emit loseFocus();
}

void Editor::leaveEvent(QEvent *event)
{
    emit mouseLeave();
}

void Editor::mousePressEvent(QMouseEvent *e)
{
    QsciScintilla::mousePressEvent(e);
    emit mousePress();
}

void Editor::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        emit drop(e);
    }
}

void Editor::find()
{
    searchDialog->setReplaceMode(false);
    searchDialog->show();
}

void Editor::replace()
{
    searchDialog->setReplaceMode(true);
    searchDialog->show();
}

int Editor::count(QString string, bool caseSensitive)
{
    int counter;
    if (caseSensitive) {
        counter = text().count(string);
    } else {
        counter = text().toLower().count(string.toLower());
    }

    return counter;
}
