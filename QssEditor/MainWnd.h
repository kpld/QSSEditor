#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>
#include <QSet>
#include <QMap>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QKeyEvent>
#include "Editor.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWnd;
}
QT_END_NAMESPACE

class QsciScintilla;
class FlowLayout;
class QPushButton;
class PaletteDialog;
class ConfDialog;

class MainWnd : public QMainWindow
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = nullptr);
    ~MainWnd();

    void setupUi();
    void createActions();
    void setupMenu();
    void setupToolbars();
    void setupStatusbar();
    void setupDocks();
    void setupEditor();

    typedef void (MainWnd::*MenuAction)(bool checked);

private:
    QAction* createAct(QString text, QString tip="", QKeySequence shortcut=QKeySequence::UnknownKey, QString iconimg="", bool checkable=false, MenuAction menuAct=NULL);

private:
    QMenu *mMenuFile;
    QMenu *mMenuEdit;
    QMenu *mMenuView;
    QMenu *mMenuTool;
    QMenu *mMenuHelp;

    // File
    QAction *mActionNew;
    QAction *mActionOpen;
    QAction *mActionSave;
    QAction *mActionSaveAs;
    QAction *mActionExport;
    QMenu   *mSubMenuRecent;
    QAction *mActionExit;

    // Edit
    QMenu   *mSubMenuText;
    QAction *mActionUndo;
    QAction *mActionRedo;
    QAction *mActionCut;
    QAction *mActionCopy;
    QAction *mActionPaste;
    QMenu   *mSubMenuSearch;
    QAction *mActionFind;
    QAction *mActionReplace;
    QAction *mActionComment;
    QAction *mActionUnComment;

    // View
    QAction *mActionShowColor;
    QAction *mActionShowPreview;
    QAction *mActionPalette;

    // Tool
    QAction *mActionConfig;

    // Help
    QAction *mActionCheckUpdate;
    QAction *mActionAbout;

    // Toolbar
    QCheckBox *qssCheckBox;
    QComboBox *themeCombo;

    QAction   *mActionDisableQss;

    QAction   *mActionFontUp;
    QAction   *mActionFontDown;
    QAction   *mActionEchoSpace;
    QAction   *mActionEchoEol;
    QAction   *mActionAutoWrap;

    QToolBar *mToolbarMain;
    QToolBar *mToolbarFile;
    QToolBar *mToolbarEdit;
    QToolBar *mToolbarSearch;
    QToolBar *mToolbarView;
    QToolBar *mToolbarEcho;
    QToolBar *mToolbarCode;

    // Status
    QLabel *mStatusLine;
    QLabel *mStatusSelect;
    QLabel *mStatusCoding;
    QLabel *mStatusLines;

    // Test
    QAction *mActionTest1;
    QAction *mActionTest2;

private:
    QTabWidget    *mainWidget;
    Editor        *editor;
    QString       curFile;
    int           newIndex;
    QString       version;
    QString       title;
    QString       lastSavedText;
    bool          firstAutoExport;
    bool          isNewFromTemplate;
    QStringList   pathList;
    int           maxPathCount;

    QMap<QLabel*, QPushButton*> clrBtnMap;
    FlowLayout    *colorPanelLayout;
    QDockWidget   *colorWgt;
    QDockWidget   *previewWgt;

    QTimer        *timer;
    bool          txtChanged;

    PaletteDialog *paletteDialog;
    ConfDialog    *confDialog;

public:
    void changeBtnColor(QString var, QLabel *lbl, QPushButton *btn);
    void renderStyle();
    void loadColorPanel();
    void newFromTemplate(QString templateFile="default.qsst");

private:
    QString currentUIqss;
    QString qssSrc;
    QString qssConvert;
    QSet<QString> varUsedList;
    QMap<QString,QString> varsDefinedList;
    QStringList varUndefinedList;
    QMap<QString,QString> varMap;

private:
    Ui::MainWnd *ui;
    QString namelist[15] = {
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
public:


public:
    void open(QString fileName);
    bool loadVars();
    void convertQss();
    void writeVars();
    void autoExport(QString fileName);
    void addRecentFile(QString fileName);
    void updateRecentMenu();

signals:

public slots:
    // File
    void OnActionNew(bool checked);
    void OnActionOpen(bool checked);
    void OnActionSave(bool checked);
    void OnActionSaveAs(bool checked);
    void OnActionExport(bool checked);
    void OnActionExit(bool checked);

    // Edit
    void OnActionUndo(bool checked);
    void OnActionRedo(bool checked);
    void OnActionCut(bool checked);
    void OnActionCopy(bool checked);
    void OnActionPaste(bool checked);
    void OnActionFind(bool checked);
    void OnActionReplace(bool checked);
    void OnActionComment(bool checked);
    void OnActionUnComment(bool checked);

    // View
    void OnActionShowColor(bool checked);
    void OnActionShowPreview(bool checked);
    void OnActionPalette(bool checked);

    // Tool
    void OnActionConfig(bool checked);

    // Help
    void OnActionCheckUpdate(bool checked);
    void OnActionAbout(bool checked);

    // Toolbar
    void OnActionDisableQss(bool checked);
    void SetAppStyle(QString style);

    void OnActionFontUp(bool checked);
    void OnActionFontDown(bool checked);
    void OnActionEchoSpace(bool checked);
    void OnActionEchoEol(bool checked);
    void OnActionAutoWrap(bool checked);

    void textChanged();
    void keyPressed(QKeyEvent *e);

    void rend();

    // Test
    void OnActionTest1();
    void OnActionTest2();

};
#endif // MAINWND_H
