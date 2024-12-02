#include "MainWnd.h"
#include "ui_MainWnd.h"
#include "ColorPanelWidget.h"
#include "PreviewWidget.h"
#include "qscilexerqss.h"
#include "flowlayout.h"
#include "PaletteDialog.h"
#include "ConfDialog.h"
//#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexerjson.h>
#include <QDebug>
#include <QFile>
//#include <QTextCodec>
#include <QRegularExpression>
#include <QColor>
#include <QMap>
#include <QDockWidget>
#include <QStyleFactory>
#include <QToolBar>
#include <QLabel>
#include <QKeyEvent>
#include <QPushButton>
#include <QColorDialog>
#include <QDateTime>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileDialog>



MainWnd::MainWnd(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWnd)
{
    newIndex = 0;
    version = "v1.0";
    title = "QssEditor " + version;
    setWindowTitle(title);
    curFile = "";
    lastSavedText = "";
    firstAutoExport = true;
    isNewFromTemplate = false;
    maxPathCount  = 4;

    currentUIqss = "";
    qssSrc = "";
    qssConvert = "";

    txtChanged = false;
    colorPanelLayout = new FlowLayout();

    paletteDialog = NULL;
    confDialog = NULL;
    paletteDialog = new PaletteDialog(this);
    confDialog = new ConfDialog(this);
    confDialog->setMinimumWidth(650);

    ui->setupUi(this);

    this->setupUi();
    this->newFromTemplate();
}

MainWnd::~MainWnd()
{
    delete ui;
}

void MainWnd::setupUi()
{
    this->resize(1200, 600);

    createActions();
    setupMenu();
    setupToolbars();
    setupStatusbar();
    setupDocks();
    setupEditor();

    setAcceptDrops(true);

    if (tr("LTR") == "RTL") {
        setLayoutDirection(Qt::RightToLeft);
    }

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [=](){
        renderStyle();
        loadColorPanel();
        timer->stop();
    });

    connect(colorWgt, &QDockWidget::dockLocationChanged, this, [=](Qt::DockWidgetArea area){
        if (area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea) {
            colorWgt->widget()->resize(colorWgt->width(), colorPanelLayout->minimumSize().height());
        }
    });

    txtChanged = false;
    connect(editor, &Editor::textChanged, this, &MainWnd::textChanged);
    connect(editor, &Editor::keyPress, this, &MainWnd::keyPressed);

    loadColorPanel();
    renderStyle();

    mActionUndo->setEnabled(editor->isUndoAvailable());
    mActionRedo->setEnabled(editor->isRedoAvailable());
}

QAction* MainWnd::createAct(QString text, QString tip, QKeySequence shortcut, QString iconimg, bool checkable, MenuAction menuAct)
{
    QAction *action = new QAction(text, this);

    if (!iconimg.isEmpty()) {
        action->setIcon(QIcon(iconimg));
    }
    if (!shortcut.isEmpty()) {
        action->setShortcut(shortcut);
    }
    if (!tip.isEmpty()) {
        action->setToolTip(tip);
        action->setStatusTip(tip);
    }
    if (checkable) {
        action->setCheckable(checkable);
    }
    if (menuAct) {
        connect(action, &QAction::triggered, this, menuAct);
    }

    return action;
}

void MainWnd::createActions()
{
    // File
    mActionNew = createAct(tr("&New"), tr("new")+"("+QKeySequence(QKeySequence::New).toString()+")", QKeySequence::New, ":res/img/NewDocument.png", false, &MainWnd::OnActionNew);
    mActionOpen = createAct(tr("&Open"), tr("open")+"("+QKeySequence(QKeySequence::Open).toString()+")", QKeySequence::Open, ":res/img/openHS.png", false, &MainWnd::OnActionOpen);
    mActionSave = createAct(tr("&Save"), tr("save")+"("+QKeySequence(QKeySequence::Save).toString()+")", QKeySequence::Save, ":res/img/save.png", false, &MainWnd::OnActionSave);
    mActionSaveAs = createAct(tr("&Save as..."), tr("save as..."), QKeySequence::UnknownKey, ":res/img/SaveAs.png", false, &MainWnd::OnActionSaveAs);
    mActionExport = createAct(tr("&ExportQss"), tr("ExportQss")+"("+QKeySequence("Ctrl+Alt+E").toString()+")", QKeySequence("Ctrl+Alt+E"), ":res/img/export5.png", false, &MainWnd::OnActionExport);
    mActionExit = createAct(tr("&Exit"), tr("Exit")+"("+QKeySequence("Ctrl+Q").toString()+")", QKeySequence("Ctrl+Q"), ":res/img/close.png", false, &MainWnd::OnActionExit);

    // Edit
    mActionUndo = createAct(tr("&Undo"), tr("undo")+"("+QKeySequence(QKeySequence::Undo).toString()+")", QKeySequence::Undo, ":res/img/undo.png", false, &MainWnd::OnActionUndo);
    mActionRedo = createAct(tr("&Redo"), tr("redo")+"("+QKeySequence(QKeySequence::Redo).toString()+")", QKeySequence::Redo, ":res/img/redo.png", false, &MainWnd::OnActionRedo);
    mActionCut = createAct(tr("&Cut"), tr("cut")+"("+QKeySequence(QKeySequence::Cut).toString()+")", QKeySequence::Cut, ":res/img/cut.png", false, &MainWnd::OnActionCut);
    mActionCopy = createAct(tr("&Copy"), tr("copy")+"("+QKeySequence(QKeySequence::Copy).toString()+")", QKeySequence::Copy, ":res/img/copy.png", false, &MainWnd::OnActionCopy);
    mActionPaste = createAct(tr("&Paste"), tr("paste")+"("+QKeySequence(QKeySequence::Paste).toString()+")", QKeySequence::Paste, ":res/img/paste.png", false, &MainWnd::OnActionPaste);
    mActionFind = createAct(tr("&Find"), tr("find")+"("+QKeySequence(QKeySequence::Find).toString()+")", QKeySequence::Find, ":res/img/find.png", false, &MainWnd::OnActionFind);
    mActionReplace = createAct(tr("&Replace"), tr("replace")+"("+QKeySequence(QKeySequence::Replace).toString()+")", QKeySequence::Replace, ":res/img/replace.png", false, &MainWnd::OnActionReplace);
    mActionComment = createAct(tr("&Comment"), tr("comment the selected code"), QKeySequence::UnknownKey, ":res/img/commentcode.png", false, &MainWnd::OnActionComment);
    mActionUnComment = createAct(tr("&UnComment"), tr("uncomment code"), QKeySequence::UnknownKey, ":res/img/uncommentcode.png", false, &MainWnd::OnActionUnComment);

    // View
    mActionShowColor = createAct(tr("&ColorPanel"), tr("ShowColorPanel"), QKeySequence::UnknownKey, ":res/img/color.png", true, &MainWnd::OnActionShowColor);
    mActionShowColor->setChecked(true);
    mActionShowPreview = createAct(tr("&PreviewPanel"), tr("ShowPreviewPanel"), QKeySequence::UnknownKey, ":res/img/view.png", true, &MainWnd::OnActionShowPreview);
    mActionShowPreview->setChecked(true);
    mActionPalette = createAct(tr("&Palette"), tr("ShowPaletteSettingDialog"), QKeySequence::UnknownKey, ":res/img/texture.png", false, &MainWnd::OnActionPalette);

    // Tool
    mActionConfig = createAct(tr("&Config"), tr("settings."), QKeySequence::UnknownKey, ":res/img/config.png", true, &MainWnd::OnActionConfig);

    // Help
    mActionCheckUpdate = createAct(tr("&Check for Updates..."), tr("Check is there new version released for update."), QKeySequence::UnknownKey, "", false, &MainWnd::OnActionCheckUpdate);
    mActionAbout = createAct(tr("&About"), tr("settings."), QKeySequence::UnknownKey, "", false, &MainWnd::OnActionAbout);

    // Toolbar
    mActionDisableQss = createAct(tr("&DisableQss"), tr("DisableQss"), QKeySequence::UnknownKey, "", true, &MainWnd::OnActionDisableQss);
    mActionDisableQss->setChecked(false);

    mActionFontUp = createAct(tr("&BiggerFont"), tr("Bigger Font"), QKeySequence::UnknownKey, ":res/img/fontup.png", false, &MainWnd::OnActionFontUp);
    mActionFontDown = createAct(tr("&SmallerFont"), tr("Smaller Font"), QKeySequence::UnknownKey, ":res/img/fontdown.png", false, &MainWnd::OnActionFontDown);
    mActionEchoSpace = createAct(tr("&Space"), tr("Show Spaces"), QKeySequence::UnknownKey, ":res/img/space.png", false, &MainWnd::OnActionEchoSpace);
    mActionEchoEol = createAct(tr("&Eol"), tr("Show Eol"), QKeySequence::UnknownKey, ":res/img/eol.png", false, &MainWnd::OnActionEchoEol);
    mActionAutoWrap = createAct(tr("&AutoWrap"), tr("Auto wrap text"), QKeySequence::UnknownKey, ":res/img/autowrap.png", false, &MainWnd::OnActionAutoWrap);

    // Test
    mActionTest1 = new QAction(tr("Test1(&1)"), this);
    mActionTest2 = new QAction(tr("Test2(&2)"), this);
    connect(mActionTest1,&QAction::triggered,this,&MainWnd::OnActionTest1);
    connect(mActionTest2,&QAction::triggered,this,&MainWnd::OnActionTest2);
}

void MainWnd::setupMenu()
{
    mMenuFile = new QMenu(tr("&File"), this);
    mMenuEdit = new QMenu(tr("&Edit"), this);
    mMenuView = new QMenu(tr("&View"), this);
    mMenuTool = new QMenu(tr("&Tool"), this);
    mMenuHelp = new QMenu(tr("&Help"), this);

    ui->menubar->addMenu(mMenuFile);
    ui->menubar->addMenu(mMenuEdit);
    ui->menubar->addMenu(mMenuView);
    ui->menubar->addMenu(mMenuTool);
    ui->menubar->addMenu(mMenuHelp);

    mSubMenuRecent = new QMenu(tr("&Recent"), mMenuFile);
    mSubMenuRecent->setIcon(QIcon(":res/img/none.png"));

    mMenuFile->addAction(mActionNew);
    mMenuFile->addAction(mActionOpen);
    mMenuFile->addAction(mActionSave);
    mMenuFile->addAction(mActionSaveAs);
    mMenuFile->addAction(mActionExport);
    mMenuFile->addMenu(mSubMenuRecent);
    mMenuFile->addSeparator();
    mMenuFile->addAction(mActionExit);

    // Edit
    mSubMenuText = new QMenu(tr("&Text"), mMenuEdit);
    mSubMenuText->setIcon(QIcon(":res/img/edit_whitepage.png"));
    mSubMenuSearch = new QMenu(tr("&Search"), mMenuEdit);
    mSubMenuSearch->setIcon(QIcon(":res/img/findnext.png"));

    mMenuEdit->addMenu(mSubMenuText);
    mSubMenuText->addAction(mActionUndo);
    mSubMenuText->addAction(mActionRedo);
    mSubMenuText->addSeparator();
    mSubMenuText->addAction(mActionCut);
    mSubMenuText->addAction(mActionCopy);
    mSubMenuText->addAction(mActionPaste);
    mMenuEdit->addMenu(mSubMenuSearch);
    mSubMenuSearch->addAction(mActionFind);
    mSubMenuSearch->addAction(mActionReplace);
    mMenuEdit->addAction(mActionComment);
    mMenuEdit->addAction(mActionUnComment);

    // View
    mMenuView->addAction(mActionShowColor);
    mMenuView->addAction(mActionShowPreview);
    mMenuView->addAction(mActionPalette);

    // Tool
    mMenuTool->addAction(mActionConfig);

    // Help
    mMenuHelp->addAction(mActionCheckUpdate);
    mMenuHelp->addAction(mActionAbout);


    // Test
    //mMenuFile->addAction(mActionTest1);
    //mMenuEdit->addAction(mActionTest2);
}

void MainWnd::setupToolbars()
{
    qssCheckBox = new QCheckBox(tr("DisableQSS"));
    qssCheckBox->setToolTip(tr("Using system style, disable qss."));

    themeCombo = new QComboBox();
    themeCombo->setToolTip(tr("Select system style."));
    themeCombo->setMinimumWidth(105);

    themeCombo->addItems(QStyleFactory::keys());
    QString theme = QApplication::style()->objectName();
    themeCombo->setCurrentIndex(themeCombo->findText(theme, Qt::MatchFixedString));

    connect(qssCheckBox, &QCheckBox::stateChanged, this, &MainWnd::OnActionDisableQss);
    //connect(qssCheckBox, &QCheckBox::stateChanged, mActionDisableQss, &QAction::setChecked);

    connect(themeCombo, &QComboBox::currentTextChanged, this, &MainWnd::SetAppStyle);

    mToolbarMain = new QToolBar(tr("Main", "toolbar"));
    mToolbarMain->addWidget(qssCheckBox);
    mToolbarMain->addWidget(themeCombo);

    mToolbarFile = new QToolBar(tr("File"));
    mToolbarFile->addAction(mActionNew);
    mToolbarFile->addAction(mActionOpen);
    mToolbarFile->addAction(mActionSave);
    mToolbarFile->addAction(mActionExport);

    mToolbarEdit = new QToolBar(tr("Edit"));
    mToolbarEdit->addAction(mActionUndo);
    mToolbarEdit->addAction(mActionRedo);
    mToolbarEdit->addSeparator();
    mToolbarEdit->addAction(mActionCut);
    mToolbarEdit->addAction(mActionCopy);
    mToolbarEdit->addAction(mActionPaste);

    mToolbarSearch = new QToolBar(tr("Search"));
    mToolbarSearch->addAction(mActionFind);
    mToolbarSearch->addAction(mActionReplace);

    mToolbarView = new QToolBar(tr("View"));
    mToolbarView->addAction(mActionShowColor);
    mToolbarView->addAction(mActionShowPreview);
    mToolbarView->addAction(mActionPalette);

    mToolbarEcho = new QToolBar(tr("Echo"));
    mToolbarEcho->addAction(mActionFontUp);
    mToolbarEcho->addAction(mActionFontDown);
    mToolbarEcho->addAction(mActionEchoSpace);
    mToolbarEcho->addAction(mActionEchoEol);
    mToolbarEcho->addAction(mActionAutoWrap);

    mToolbarCode = new QToolBar(tr("Code"));
    mToolbarCode->addAction(mActionComment);
    mToolbarCode->addAction(mActionUnComment);

    addToolBar(mToolbarMain);
    addToolBar(mToolbarFile);
    addToolBar(mToolbarEdit);
    addToolBar(mToolbarSearch);
    addToolBar(mToolbarView);
    addToolBar(mToolbarEcho);
    addToolBar(mToolbarCode);
}

void MainWnd::setupStatusbar()
{
    this->statusBar()->showMessage(tr("Ready"));

    mStatusLine = new QLabel(tr("line:0 pos:0"));
    mStatusSelect = new QLabel(tr("select: none"));
    mStatusCoding = new QLabel(tr("select: coding"));
    mStatusLines = new QLabel(tr("lines:0"));

    mStatusLine->setMinimumWidth(120);
    mStatusSelect->setMinimumWidth(150);
    mStatusCoding->setMinimumWidth(80);
    mStatusCoding->setAlignment(Qt::AlignCenter);
    mStatusLines->setMinimumWidth(60);
    mStatusLines->setAlignment(Qt::AlignRight);

    statusBar()->addPermanentWidget(mStatusLine);
    statusBar()->addPermanentWidget(mStatusSelect);
    statusBar()->addPermanentWidget(mStatusCoding);
    statusBar()->addPermanentWidget(mStatusLines);
}

void MainWnd::setupDocks()
{
    colorWgt = new QDockWidget(tr("Color Variables"));//, this);
    previewWgt = new QDockWidget(tr("Preview"));//, this);

    colorWgt->setMinimumSize(QSize(80, 20));
    colorWgt->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    previewWgt->setMinimumSize(QSize(200,200));
    previewWgt->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::LeftDockWidgetArea, colorWgt);
    addDockWidget(Qt::RightDockWidgetArea, previewWgt);

    QWidget* colorPanelWidget = new ColorPanelWidget(this);
    colorPanelWidget->setLayout(colorPanelLayout);
    colorWgt->setWidget(colorPanelWidget);
    previewWgt->setWidget(new PreviewWidget());//this));

    connect(colorWgt, &QDockWidget::visibilityChanged, mActionShowColor, &QAction::setChecked);
}

void MainWnd::setupEditor()
{
    // QFile *file = new QFile("C:\\Users\\kpld\\Desktop\\sample.qss");
    // file->open(QFile::ReadOnly);
    // QByteArray all = file->readAll();
    // file->close();
    // QString content = QString(all);
    // int len = content.length();


    mainWidget = new QTabWidget();
    mainWidget->setTabBarAutoHide(true);

    editor = new Editor();
    this->centralWidget()->hide();
    this->setCentralWidget(mainWidget);

    mainWidget->addTab(editor, "main editor");

    editor->setMarginType(0, QsciScintilla::NumberMargin);
    editor->setMarginWidth(0, 35);
    editor->setMarginWidth(1, 0);
    editor->setMarginWidth(3, 0);
    editor->setMarginWidth(4, 0);
    editor->setMarginLineNumbers(0, true);
    editor->setMarginsBackgroundColor(QColor("lightgray"));
    editor->setMarginsForegroundColor(QColor("#ff000000"));

    editor->setUtf8(true);
    editor->setMarginsFont(QFont("Courier New", 11, 50));
    editor->setFont(QFont("Consolas", 11, 50));

    editor->setWrapMode(QsciScintilla::WrapNone);
    editor->setWrapVisualFlags(QsciScintilla::WrapFlagNone);
    editor->setEolVisibility(false);
    editor->setWhitespaceVisibility(QsciScintilla::WsInvisible);
    editor->setWhitespaceSize(2);
    editor->setIndentationsUseTabs(true);
    editor->setTabWidth(4);
    editor->setIndentationGuides(true);
    editor->setIndentationWidth(0);
    editor->setAutoIndent(true);
    editor->setBackspaceUnindents(true);
    editor->setTabIndents(true);

    editor->setCaretWidth(2);
    editor->setCaretForegroundColor(QColor("#ff000000"));
    editor->setCaretLineVisible(true);
    editor->setCaretLineBackgroundColor(QColor("#fff0f0f0"));

    editor->setEdgeColumn(80);
    editor->setEdgeMode(QsciScintilla::EdgeLine);
    editor->setEdgeColor(QColor("#FF88FFFF"));

    editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);

    editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    editor->setAutoCompletionCaseSensitivity(false);
    editor->setAutoCompletionThreshold(1);
    editor->setAutoCompletionReplaceWord(true);

    editor->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    editor->setFoldMarginColors(QColor("#aad"), QColor("#bbe"));
    editor->setMarginSensitivity(2, true);

    QsciLexer* lexer = new QsciLexerQSS(this, editor);
    //lexer->setEditor(editor);
    editor->setLexer(lexer);
//    editor->setText(content.mid(0));

    connect(editor, &Editor::loseFocus, this, &MainWnd::rend);
    connect(editor, &Editor::mousePress, this, &MainWnd::rend);

}


void MainWnd::changeBtnColor(QString var, QLabel *lbl, QPushButton *btn)
{
    QString varDef = var;
    QString varVal = varMap[var];
    QColor *c = new QColor();
    if (!varVal.isEmpty()) {
        c->setNamedColor(varVal);
    } else {
        c->setNamedColor("white");
    }

    QColor color = QColorDialog::getColor(*c, this, tr("color pick"), QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        QString styleSheet;
        QString clrstr = color.name();
        if (color.alpha() == 255) {
            clrstr = color.name().toUpper();
        } else {
            clrstr = color.name(QColor::HexArgb).toUpper();
        }
        if (clrstr == c->name().toUpper()) return;

        if (qGray(color.rgb()) < 100) {
            styleSheet += "color:white;";
        }
        btn->setText(clrstr);
        btn->setStyleSheet(styleSheet + "background:" + clrstr);

        varMap[varDef] = clrstr;
        writeVars();

        int pos = editor->verticalScrollBar()->sliderPosition();
        editor->selectAll();
        editor->replaceSelectedText(qssSrc);
        editor->verticalScrollBar()->setSliderPosition(pos);

        renderStyle();
    }
}

void MainWnd::rend()
{
    QDateTime time1 = QDateTime::currentDateTime();
    renderStyle();
    QDateTime time2 = QDateTime::currentDateTime();
    loadColorPanel();
    QDateTime time3 = QDateTime::currentDateTime();

    qint64 interval1 = time1.msecsTo(time2);
    qint64 interval2 = time2.msecsTo(time3);
    qDebug("[%s] interval1=%lld, interval2=%lld", __FUNCTION__, interval1, interval2);
}

void MainWnd::renderStyle()
{
    QDateTime time1 = QDateTime::currentDateTime();
    if (!loadVars()) return;
    QDateTime time2 = QDateTime::currentDateTime();
    convertQss();
    QDateTime time3 = QDateTime::currentDateTime();
    QDateTime time4;
    if (qssCheckBox->isChecked()) {
        previewWgt->setStyleSheet("");
        time4 = QDateTime::currentDateTime();
    } else {

        //previewWgt->setPalette(QPalette(QColor(0xFF444444)));
        //qApp->setPalette(QPalette(QColor(0xFF444444)));
        //this->editor->setPaper(QColor(0xFF444444));
        // if (editor->lexer()) {
        //     editor->lexer()->setPaper(QColor(0xFF444444));
        // } else {
        //     editor->setPaper(QColor(0xFF444444));
        // }
        time4 = QDateTime::currentDateTime();
        //qApp->setStyleSheet(qssConvert);
        previewWgt->setStyleSheet(qssConvert);
        if (paletteDialog) paletteDialog->setStyleSheet(qssConvert);
        if (varMap.contains("background")) {
            QColor c;
            c.setNamedColor(varMap["background"]);
            if (editor->lexer()) {
                editor->lexer()->setPaper(c);
            } else {
                editor->setPaper(c);
            }
        }
    }

    QDateTime time5 = QDateTime::currentDateTime();
    qint64 interval1 = time1.msecsTo(time2);
    qint64 interval2 = time2.msecsTo(time3);
    qint64 interval3 = time3.msecsTo(time4);
    qint64 interval4 = time4.msecsTo(time5);
    qDebug("[%s] interval1=%lld, interval2=%lld, interval3=%lld, interval4=%lld", __FUNCTION__, interval1, interval2, interval3, interval4);
}

void MainWnd::loadColorPanel()
{
    qssSrc = editor->text();

    if (!loadVars()) return;

    QStringList varList1 = QStringList(varMap.keys());
    varList1.sort();
    QStringList varList2;
    QMap<QLabel*, QPushButton*>::iterator iter0;
    for(iter0=clrBtnMap.begin(); iter0!=clrBtnMap.end(); iter0++) {
        varList2.append(iter0.key()->text());
    }
    varList2.sort();
    if (varList1 != varList2) {
        while (colorPanelLayout->count() > 0) {
            QLayoutItem* item = colorPanelLayout->itemAt(0);
            colorPanelLayout->removeItem(item);
            delete item;
        }

        int lblWidth = 0, btnWidth = 0;

        QMap<QLabel*, QPushButton*>::iterator iter0;
        for(iter0=clrBtnMap.begin(); iter0!=clrBtnMap.end(); iter0++) {
            delete iter0.key();
            delete iter0.value();
        }
        clrBtnMap.clear();

        QMap<QString,QString>::iterator iter;
        for(iter=varMap.begin(); iter!=varMap.end(); iter++) {
            QString varName = iter.key();
            QString varValue = iter.value();
            QLabel *label = new QLabel(varName, this);
            QPushButton *btn = new QPushButton(varValue, this);
#if defined(Q_OS_WIN)
            QFont *font1 = new QFont("Arial", 10, QFont::Medium);
            QFont *font2 = new QFont("sans-serif", 9, QFont::Medium);
            label->setFont(*font1);
            btn->setFont(*font2);
#endif

            clrBtnMap.insert(label, btn);
            label->adjustSize();
            if (label->width() > lblWidth ) {
                lblWidth = label->width();
            }
            btn->adjustSize();
            if (btn->width() > btnWidth) {
                btnWidth = btn->width();
            }

            connect(btn, &QPushButton::clicked, this, [=](){
                changeBtnColor(varName, label, btn);
            });
        }
        QMap<QLabel*,QPushButton*>::Iterator it;
        for(it=clrBtnMap.begin(); it!=clrBtnMap.end(); it++) {
            QWidget* containerWidget = new QWidget(this);
            QHBoxLayout *hlay = new QHBoxLayout();
            it.key()->setFixedWidth(lblWidth);
            it.value()->setFixedWidth(btnWidth);
            hlay->addWidget(it.key());
            hlay->addWidget(it.value());
            containerWidget->setLayout(hlay);
            colorPanelLayout->addWidget(containerWidget);
        }
    }

    QMap<QLabel*,QPushButton*>::Iterator it;
    for(it=clrBtnMap.begin(); it!=clrBtnMap.end(); it++) {
        QLabel *label = it.key();
        QPushButton *btn = it.value();
        QString varDef = label->text();
        QString strColor = varMap[varDef];
        btn->setText(strColor);

        QColor *color = NULL;
        QString styleSheet;
        QString tmp;
        strColor.trimmed();
        if (strColor.startsWith("rgba(")) {
            tmp = strColor.mid(5, strColor.length()-5-1);
            QStringList cValList = tmp.split(',');
            if (cValList.length() > 3) {
                color = new QColor(cValList[0].toInt(), cValList[1].toInt(), cValList[2].toInt(), cValList[3].toInt());
            } else {
                color = new QColor(cValList[0].toInt(), cValList[1].toInt(), cValList[2].toInt(), 255);
            }
        } else if (strColor.startsWith("rgb(")) {
            tmp = strColor.mid(4, strColor.length()-4-1);
            QStringList cValList = tmp.split(',');
            color = new QColor(cValList[0].toInt(), cValList[1].toInt(), cValList[2].toInt(), 255);
        } else {
            color = new QColor(strColor);
        }

        if (qGray(color->rgb()) < 100) {
            styleSheet = "color:white;";
        } else {
            styleSheet = "color:black;";
        }
        delete color;
        styleSheet += "background:";
        styleSheet += btn->text();
        btn->setStyleSheet(styleSheet);
    }
}

void MainWnd::textChanged()
{
    txtChanged = true;
    mActionUndo->setEnabled(editor->isUndoAvailable());
    mActionRedo->setEnabled(editor->isRedoAvailable());
}

void MainWnd::keyPressed(QKeyEvent *e)
{

}

void MainWnd::OnActionNew(bool checked)
{
    //qDebug("OnActionNew");
    if (editor->isModified()) {
        int nRet = QMessageBox::question(this, title, tr("Current file has not been saved, do you want to save?"), QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::No);
        if (nRet == QMessageBox::Yes) {
            OnActionSave(checked);
        } else if (nRet == QMessageBox::Cancel) {
            return;
        }
    }

    newIndex += 1;
    curFile = QString(tr("new")) + QString::number(newIndex) + QString(tr(".qsst"));
    lastSavedText = "";
    editor->setText("");

    renderStyle();
    loadColorPanel();
    setWindowTitle(title + " - " + curFile);
    editor->setModified(false);
}
void MainWnd::open(QString fileName)
{
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "QSS(*.qss *.qsst);;qsst(*.qsst);;qss(*.qss);;all(*.*)");
    }
    if (QFile::exists(fileName)) {
        curFile = fileName;
        statusBar()->showMessage(tr("opening file..."));
        lastSavedText = editor->text();
        bool ok = editor->load(curFile);
        if (ok) {
            statusBar()->showMessage(tr("load file successfully"));
        } else {
            statusBar()->showMessage(tr("load file failed"));
        }
        renderStyle();
        loadColorPanel();
        setWindowTitle(title + " - " + fileName);
        mStatusCoding->setText(editor->getEncoding());
        if (!isNewFromTemplate) {
            addRecentFile(curFile);
        }
    } else {
        statusBar()->showMessage(tr("file not found."));
    }
}

void MainWnd::OnActionOpen(bool checked)
{
    //qDebug("OnActionOpen");
    open("");
}

void MainWnd::OnActionSave(bool checked)
{
    //qDebug("OnActionSave");
    if(QFile::exists(curFile)) {
        lastSavedText = editor->text();
        editor->save(curFile);
        mStatusCoding->setText("utf-8");
        setWindowTitle(title + " - " + curFile);
        mActionSave->setEnabled(false);
        addRecentFile(curFile);
        autoExport(curFile);
    } else {
        OnActionSaveAs(checked);
    }
}

void MainWnd::OnActionSaveAs(bool checked)
{
    //qDebug("OnActionSaveAs");
    QString file = QFileDialog::getSaveFileName(this, tr("save file"), curFile, "qsst(*.qsst);;qss(*.qss);;all(*.*)");
    if (!file.isEmpty()) {
        curFile = file;
        lastSavedText = editor->text();
        editor->save(curFile);
        mStatusCoding->setText("utf-8");
        setWindowTitle(title + " - " + curFile);
        mActionSave->setEnabled(false);
        addRecentFile(curFile);
        autoExport(curFile);
        firstAutoExport = true;
    }
}

void MainWnd::OnActionExport(bool checked)
{
    //qDebug("OnActionExport");
    convertQss();
    QString f;
    if (curFile.isEmpty()) {
        f = ".";
    } else {
        f = curFile.split(".")[0];
    }

    QString saveFileName = QFileDialog::getSaveFileName(this, tr("export QSS"), f, "Qss(*.qss);;all(*.*)");
    if (!saveFileName.isEmpty()) {
        QFile saveFile(saveFileName);
        if (saveFile.open(QIODevice::ReadWrite)) {
            saveFile.write(qssConvert.toUtf8());
            saveFile.close();
        }
    }
}

void MainWnd::OnActionExit(bool checked)
{
    close();
}

void MainWnd::OnActionUndo(bool checked)
{
    //qDebug("OnActionUndo");
    editor->undo();
}

void MainWnd::OnActionRedo(bool checked)
{
    //qDebug("OnActionRedo");
    editor->redo();
}

void MainWnd::OnActionCut(bool checked)
{
    //qDebug("OnActionCut");
    editor->cut();
}

void MainWnd::OnActionCopy(bool checked)
{
    //qDebug("OnActionCopy");
    editor->copy();
}

void MainWnd::OnActionPaste(bool checked)
{
    //qDebug("OnActionPaste");
    editor->paste();
}

void MainWnd::OnActionFind(bool checked)
{
    //qDebug("OnActionFind");
    editor->find();
}

void MainWnd::OnActionReplace(bool checked)
{
    //qDebug("OnActionReplace");
    editor->replace();
}

void MainWnd::OnActionComment(bool checked)
{
    //qDebug("OnActionComment");
    int lineFrom, indexFrom, lineTo, indexTo;
    editor->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    if (lineFrom == -1) {
        int index;
        editor->getCursorPosition(&lineFrom, &index);
        indexFrom = 0;
        lineTo = lineFrom;
        indexTo = editor->lineLength(lineTo) + 1;
    }
    editor->insertAt("/*", lineFrom, indexFrom);
    editor->insertAt("*/", lineTo, indexTo);
}

void MainWnd::OnActionUnComment(bool checked)
{
    //qDebug("OnActionUnComment");
    int lineFrom, indexFrom, lineTo, indexTo;
    editor->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    int start=-1, end=-1;

    if (lineFrom == -1) {
        int index;
        editor->getCursorPosition(&lineFrom, &index);
        lineTo = lineFrom;
        QString lineText = editor->text(lineFrom);
        //lineBytes = lineText.encode();
        if ( lineText.length()<4 || index<2 || index>(lineText.length()-2) )
            return;
        for(int i=index-1; i>-1; i--) {
            if (lineText[i] == '*' && lineText[i-1] == '/') {
                start = i-1;
                break;
            }
        }
        for(int i=index; i<lineText.length()-1; i++) {
            if (lineText[i] == '*' && lineText[i+1] == '/') {
                end = i;
                break;
            }
        }
    } else {
        QString lineStart = editor->text(lineFrom);
        int indexEnd= lineTo>lineFrom ? lineStart.length() : indexTo;
        for(int i=indexFrom; i<indexEnd; i++) {
            if (lineStart[i] == '/' && lineStart[i+1] == '*') {
                start = i;
                break;
            }
        }
        if (start == -1) {
            for(int i=indexFrom; i>0; i--) {
                if (lineStart[i] == '/' && lineStart[i=1] == '*') {
                    start = -2;
                    break;
                }
                else if (lineStart[i] == '*' && lineStart[i-1] == '/') {
                    start = i-1;
                    break;
                }
            }
        }
        if (start == -1 && lineFrom > 0) {
            while (lineFrom > 0) {
                lineFrom = lineFrom-1;
                if (!editor->text(lineFrom).trimmed().isEmpty()) {
                    break;
                }
            }
            lineStart = editor->text(lineFrom);
            for(int i=lineStart.length()-1; i>-1; i--) {
                if (lineStart[i] == '/' && lineStart[i-1] == '*') {
                    break;
                } else if (lineStart[i] == '*' && lineStart[i-1] == '/') {
                    start = i-1;
                    break;
                }
            }
        }
        if (start > 0) {
            QString lineEnd = editor->text(lineTo);
            int indexStart = lineTo>lineFrom ? 0 : indexFrom;
            for(int i=indexTo; i>indexStart; i--) {
                if (lineEnd[i] == '/' && lineEnd[i-1] == '*') {
                    end = i;
                    break;
                }
            }
            if (end == -1) {
                for(int i=indexTo; i<lineEnd.length()-1; i++) {
                    if (lineEnd[i] == '/' && lineEnd[i+1] == '*') {
                        end = -2;
                        break;
                    } else if (lineEnd[i] == '*' && lineEnd[i+1] == '/') {
                        end = i;
                        break;
                    }
                }
            }
            if ( end < 0 && lineTo < editor->lines()-1 ) {
                while (lineTo < editor->lines()-1) {
                    lineTo = lineTo + 1;
                    if (!editor->text(lineTo).trimmed().isEmpty()) {
                        break;
                    }
                }
                lineEnd = editor->text(lineTo);
                for(int i=0; i<lineEnd.length()-1; i++) {
                    if (lineEnd[i] == '/' && lineEnd[i+1] == '*') {
                        break;
                    } else if (lineEnd[i] == '*' && lineEnd[i+1] == '/') {
                        end = i;
                    }
                }
            }
        }
    }

    if (start >= 0 && end >= 0) {
        editor->setSelection(lineTo, end, lineTo, end+2);
        editor->removeSelectedText();
        editor->setSelection(lineFrom, start, lineFrom, start+2);
        editor->removeSelectedText();
    }
}

void MainWnd::OnActionShowColor(bool checked)
{
    colorWgt->setVisible(checked);
}

void MainWnd::OnActionShowPreview(bool checked)
{
    previewWgt->setVisible(checked);
}

void MainWnd::OnActionPalette(bool checked)
{
    //qDebug("OnActionPalette");
    if (paletteDialog) {
        paletteDialog->exec();
    }
}

void MainWnd::OnActionConfig(bool checked)
{
    //qDebug("OnActionConfig");
    if (confDialog) {
        confDialog->exec();
    }
}

void MainWnd::OnActionCheckUpdate(bool checked)
{
    qDebug("OnActionCheckUpdate");
}

void MainWnd::OnActionAbout(bool checked)
{
    qDebug("OnActionAbout");
}

void MainWnd::OnActionDisableQss(bool checked)
{
    //qDebug("OnActionDisableQss");

    if (checked) {
        previewWgt->setStyleSheet("");
        setStyleSheet("");
        //qApp->setStyleSheet("");
    } else {
        //setStyleSheet(qssConvert);
        setStyleSheet("");
        renderStyle();
        loadColorPanel();
        //qApp->setStyleSheet(qssConvert);
    }
}

void MainWnd::SetAppStyle(QString style)
{
    qApp->setStyle(style);
}

void MainWnd::OnActionFontUp(bool checked)
{
    //qDebug("OnActionFontUp");
    editor->zoomIn();
}

void MainWnd::OnActionFontDown(bool checked)
{
    //qDebug("OnActionFontDown");
    editor->zoomOut();
}

void MainWnd::OnActionEchoSpace(bool checked)
{
    //qDebug("OnActionEchoSpace");
    editor->setWhitespaceVisibility(editor->whitespaceVisibility() ? Editor::WsInvisible : Editor::WsVisible);
}

void MainWnd::OnActionEchoEol(bool checked)
{
    //qDebug("OnActionEchoEol");
    editor->setEolVisibility(!editor->eolVisibility());
}

void MainWnd::OnActionAutoWrap(bool checked)
{
    //qDebug("OnActionAutoWrap");
    editor->setWrapMode(editor->wrapMode() ? Editor::WrapNone : Editor::WrapCharacter);
}

void MainWnd::OnActionTest1()
{
    //qDebug("Test1");
    loadVars();
}

void MainWnd::OnActionTest2()
{
    //qDebug("Test2");
    convertQss();
}

bool MainWnd::loadVars()
{
    varUsedList.clear();
    varsDefinedList.clear();
    varMap.clear();
    varUndefinedList.clear();

    if (qssSrc.isEmpty()) {
        qssSrc = editor->text();
    }

    static QRegularExpression re(":[ \t\\w,.:()]*[$]([\\w]+)");
    static QRegularExpression re2("[$](\\w+)\\s*=[ \\t]*([#(),.\\w ]*)[\\t ]*[\r\n;\\/]+");
    static QRegularExpression re3("#[0-9A-Fa-f]{1,8}|rgb(\\s*[0-9]*\\s*(,\\s*[0-9]*\\s*){2})|rgba(\\s*[0-9]*\\s*(,\\s*[0-9]*\\s*){3})|[\\w]*px");
    QRegularExpressionMatchIterator iter = re.globalMatch(qssSrc);
    //QStringList varUsedList, varsDefinedList, varUndefinedList;
    while(iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        QString matched0 = match.captured(0);
        QString matched1 = match.captured(1);
        varUsedList<<matched1;
    }

    iter = re2.globalMatch(qssSrc);
    while(iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        QString matched0 = match.captured(0);
        QString matched1 = match.captured(1);
        QString matched2 = match.captured(2);
        varsDefinedList.insert(matched1, matched2);
    }

    qDebug();
    bool valErr = false;
    QStringList varsList;

    for(QMap<QString,QString>::Iterator Iter=varsDefinedList.begin(); Iter!=varsDefinedList.end(); Iter++) {
        QString key, value;
        key = Iter.key();
        value = Iter.value();

        if (QColor::colorNames().contains(value)) {
            varMap[key] = value;
        } else {
            QRegularExpressionMatchIterator iter = re3.globalMatch(value);
            if (!iter.hasNext()) {
                valErr = true;
            } else {
                varMap[key] = value;
            }
        }
    }

    for(QSet<QString>::Iterator iter = varUsedList.begin(); iter != varUsedList.end(); iter++) {
        QString varUsed = *iter;
        if (varMap.keys().indexOf(varUsed) < 0) {
            varMap[varUsed] = "";
            varUndefinedList.append(varUsed);
        }
    }

    qDebug();
    return !valErr;
}

void MainWnd::convertQss()
{
    loadVars();
    static QRegularExpression re("[$](\\w+)\\s*=[ \t]*([#(),.\\w ]*)[ \t;]*[\r\n]{0,2}");

    // delete variable defined
    QString qssSrc2 = qssSrc;
    qssSrc2.replace(re, "");
    //qDebug()<<qssSrc2;

    for(QMap<QString,QString>::Iterator iter = varMap.begin(); iter != varMap.end(); iter++) {
        qssSrc2.replace("$" + iter.key(), iter.value());
    }
    //qDebug()<<qssSrc2;

    // static QRegularExpression re2("[$](\\w+)([\\s;]*)");
    // QRegularExpressionMatchIterator iter = re2.globalMatch(qssSrc2);
    // while(iter.hasNext()) {
    //     QRegularExpressionMatch match = iter.next();

    //     QString matched0 = match.captured(0);
    //     QString matched1 = match.captured(1);
    //     QString matched2 = match.captured(2);

    //     qDebug()<<matched1<<matched2;

    //     qssSrc2.replace(matched1, varMap[matched1]);
    //     qDebug()<<qssSrc2;
    // }

    //qssSrc2.replace(re2, QString("s\\1"));
    qssConvert = qssSrc2;
}

void MainWnd::writeVars()
{
    QMap<QString,QString> varMapNew;
    varMapNew = varMap;

    loadVars();
    if (!varMap.isEmpty()) {
        static QRegularExpression re("[$](\\w+)\\s*=[ \\t]*([#(),.\\w]*)[\\t ]*[;]?");
        QRegularExpressionMatchIterator iter = re.globalMatch(qssSrc);
        while(iter.hasNext()) {
            QRegularExpressionMatch match = iter.next();
            QString matched0 = match.captured(0);
            QString matched1 = match.captured(1);
            QString matched2 = match.captured(2);
            qssSrc.replace(matched2, varMapNew[matched1]);
        }
        //qDebug()<<qssSrc;
    } else {
    }
    loadVars();
}

void MainWnd::autoExport(QString fileName)
{
    if (1) {
        convertQss();
        QString qssFile = fileName.split(".")[0] + ".qss";
        QString backupFile = qssFile + ".backup";
        if (firstAutoExport && QFile::exists(qssFile)) {
            if (QFile::exists(backupFile)) {
                QFile::remove(backupFile);
            }
            QFile::rename(qssFile, backupFile);

            QFile f(qssFile);
            if (f.open(QIODevice::ReadWrite)) {
                f.write(qssConvert.toUtf8());
                f.close();
                firstAutoExport = false;
            }
        }
    }
}

void MainWnd::addRecentFile(QString fileName)
{
    if (pathList.contains(fileName)) {
        pathList.removeOne(fileName);
    }
    pathList.insert(0, fileName);
    if (pathList.count() > maxPathCount) {
        pathList.pop_front();
    }
    updateRecentMenu();
}

void MainWnd::updateRecentMenu()
{
    QMenu* recentMenu = mSubMenuRecent;
    if (!recentMenu) {
        recentMenu = new QMenu();
    }
    if (recentMenu) {
        recentMenu->clear();
        foreach(QString str, pathList) {
            QAction *action = new QAction(str, recentMenu);
            action->setToolTip(str);
            action->setStatusTip(str);
            connect(action, &QAction::triggered, this, [=](){
                open(str);
            });
            recentMenu->addAction(action);
        }
    }
}

void MainWnd::newFromTemplate(QString templateFile)
{
    if (!editor) return;
    if (editor->isModified()) {
        int nRet = QMessageBox::question(this, title, tr("Current file hasn't been saved, do you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::No);
        if (nRet == QMessageBox::Yes) {
            OnActionSave(true);
        } else if (nRet == QMessageBox::Cancel) {
            return;
        }
    }

    isNewFromTemplate = true;
    open(templateFile);
    isNewFromTemplate = false;
    this->statusBar()->showMessage(tr("new file created, using template"));
    newIndex++;
    curFile = QString(tr("new")) + QString::number(newIndex) + QString(tr(".qsst"));
    setWindowTitle(title + " - " + curFile);
    editor->setModified(false);
}
