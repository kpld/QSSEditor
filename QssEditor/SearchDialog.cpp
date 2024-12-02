#include "SearchDialog.h"
#include "Editor.h"
#include <QStatusBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


SearchDialog::SearchDialog(QWidget *parent)
    : QMainWindow{parent}
{
    mParent = parent;
    isReplaceMode = false;
    if (parent) {
        editor = (Editor*)parent;
    } else {
        editor = NULL;
    }

    reFlag = false;
    caseFlag = false;
    wordFlag = false;
    wrapFlag = false;
    forwardFlag = true;
    startLine = -1;
    startIndex = -1;
    showAllFlag = true;
    posixFlag = true;
    cxx11Flag = false;
    startNewSearch = true;
    escapeFlag = false;
    searchText = "";
    replaceText = "";
    finded = false;

    setupUi();
}

SearchDialog::~SearchDialog()
{

}

void SearchDialog::setReplaceMode(bool isReplace)
{
    isReplaceMode = isReplace;
    findPreBtn->setVisible(!isReplace);
    countBtn->setVisible(!isReplace);
    replaceBtn->setVisible(isReplace);
    replaceAllBtn->setVisible(isReplace);
    replaceLabel->setVisible(isReplace);
    replaceTextBox->setVisible(isReplace);
    reverseCheckbox->setVisible(isReplace);
    if (isReplace) {
        setWindowTitle(tr("Replace"));
    } else {
        setWindowTitle(tr("Find"));
    }
}

void SearchDialog::setupUi()
{
    setWindowFlags(Qt::Tool);
    setMinimumSize(320, 200);
    QStatusBar *s = this->statusBar();
    s->setSizeGripEnabled(false);

    if (isReplaceMode) {
        setWindowTitle(tr("Replace"));
    } else {
        setWindowTitle(tr("Find"));
    }

    QWidget *mainWgt = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    QGridLayout *leftLayout = new QGridLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();
    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);
    mainWgt->setLayout(layout);
    setCentralWidget(mainWgt);
    mainWgt->setFixedHeight(200);

    reverseCheckbox = new QCheckBox(tr("reverse"));
    QCheckBox *caseSensitiveCheckbox = new QCheckBox(tr("case sensitive"));
    QCheckBox *wordCheckbox = new QCheckBox(tr("match word"));
    QCheckBox *escapeCheckbox = new QCheckBox(tr("support escape char '\\n,\\r,\\t,\\0,\\x...'"));
    QCheckBox *regCheckbox = new QCheckBox(tr("regular expression"));

    QLabel *findLabel = new QLabel(tr("Search Text"));
    replaceLabel = new QLabel(tr("Replace to:"));
    searchTextBox = new QLineEdit();
    replaceTextBox = new QLineEdit();

    leftLayout->addWidget(findLabel, 0, 0, 1, 1, Qt::AlignRight);
    leftLayout->addWidget(replaceLabel, 1, 0, 1, 1, Qt::AlignRight);
    leftLayout->addWidget(searchTextBox, 0, 1);
    leftLayout->addWidget(replaceTextBox, 1, 1);
    leftLayout->addItem(new QSpacerItem(20, 5), 2, 0);
    leftLayout->setRowStretch(2, 1);
    leftLayout->addWidget(reverseCheckbox, 3, 0);
    leftLayout->addWidget(caseSensitiveCheckbox, 4, 0);
    leftLayout->addWidget(wordCheckbox, 5, 0);
    leftLayout->addWidget(escapeCheckbox, 6, 0, 1, 2);
    leftLayout->addWidget(regCheckbox, 7, 0);
    if (!isReplaceMode) {
        replaceLabel->setVisible(false);
        replaceTextBox->setVisible(false);
        reverseCheckbox->setVisible(false);
    }

    connect(searchTextBox, &QLineEdit::textChanged, this, &SearchDialog::changeText);
    connect(replaceTextBox, &QLineEdit::textChanged, this, &SearchDialog::changeText);
    connect(reverseCheckbox, &QCheckBox::stateChanged, this, &SearchDialog::setReverse);
    connect(caseSensitiveCheckbox, &QCheckBox::stateChanged, this, &SearchDialog::setCase);
    connect(wordCheckbox, &QCheckBox::stateChanged, this, &SearchDialog::setWord);
    connect(escapeCheckbox, &QCheckBox::stateChanged, this, &SearchDialog::setEscape);
    connect(regCheckbox, &QCheckBox::stateChanged, this, &SearchDialog::setRe);

    QPushButton *findNextBtn = new QPushButton(tr("Find Next"));
    findNextBtn->setShortcut(Qt::Key_Return);
    findPreBtn = new QPushButton(tr("Find previous"));
    findPreBtn->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
    findPreBtn->resize(findPreBtn->sizeHint());
    countBtn = new QPushButton(tr("Count"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));
    replaceBtn = new QPushButton(tr("Replace"));
    replaceAllBtn = new QPushButton(tr("Replace All"));
    QString stylesheet = "QPushButton { padding: 5 15}";
    findPreBtn->setStyleSheet(stylesheet);
    findNextBtn->setStyleSheet(stylesheet);
    countBtn->setStyleSheet(stylesheet);
    replaceBtn->setStyleSheet(stylesheet);
    replaceAllBtn->setStyleSheet(stylesheet);
    rightLayout->addWidget(findNextBtn);
    rightLayout->addWidget(findPreBtn);
    rightLayout->addWidget(replaceBtn);
    rightLayout->addWidget(replaceAllBtn);
    rightLayout->addWidget(countBtn);
    rightLayout->addWidget(cancelBtn);
    rightLayout->addStretch(1);
    if (isReplaceMode) {
        findPreBtn->setVisible(false);
        countBtn->setVisible(false);
    } else {
        replaceBtn->setVisible(false);
        replaceAllBtn->setVisible(false);
    }

    connect(findNextBtn, &QPushButton::clicked, this, [=](){
        setReverse(false);
        findReplace();
    });
    connect(findPreBtn, &QPushButton::clicked, this, [=](){
        setReverse(true);
        findReplace();
    });
    connect(replaceBtn, &QPushButton::clicked, this, [=](){
        findReplace(true);
    });
    connect(countBtn, &QPushButton::clicked, this, [=](){
        if (editor) {
            QString str = QString(tr("Count:%1 times matched.")).arg(editor->count(searchText, caseFlag));
            statusBar()->showMessage(str);
        }
    });

    connect(cancelBtn, &QPushButton::clicked, this, &SearchDialog::close);
    cancelBtn->setShortcut(Qt::Key_Escape);

    setFixedSize(sizeHint());
}

void SearchDialog::changeText()
{
    searchText = searchTextBox->text();
    replaceText = replaceTextBox->text();
    startNewSearch = true;
    if (escapeFlag) {
        searchText = searchText.replace("\\\\", "\\");
        replaceText = replaceText.replace("\\\\", "\\");
    }
}

void SearchDialog::setReverse(bool isReverse)
{
    if (forwardFlag == isReverse) {
        forwardFlag = !isReverse;
        startNewSearch = true;
    }
}

void SearchDialog::setCase(bool casesencitive)
{
    caseFlag = casesencitive;
}

void SearchDialog::setWord(bool word)
{
    wordFlag = word;
}

void SearchDialog::setEscape(bool escape)
{
    escapeFlag = escape;
}

void SearchDialog::setRe(bool regexpression)
{
    reFlag = regexpression;
}

void SearchDialog::findReplace(bool isReplace)
{
    if (!editor) return;
    statusBar()->showMessage("");

    if (startNewSearch) {
        finded = editor->findFirst(searchText, reFlag, caseFlag, wordFlag, wrapFlag, forwardFlag, startLine, startIndex, showAllFlag, posixFlag, cxx11Flag);
        if(finded)  {
            startNewSearch = false;
        } else {
            statusBar()->showMessage(tr("Nothing finded."));
        }
    } else {
        if (isReplace && finded) {
            editor->replaceSelectedText(replaceText);
        }

        finded = editor->findNext();
        if (!finded) {
            QString text = forwardFlag ? tr("bottom") : tr("top");
            statusBar()->showMessage(tr("reach ") + text + ".");
        }
    }

    int lineFrom, indexFrom, lineTo, indexTo;
    editor->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    if (forwardFlag) {
        startLine = lineTo;
        startIndex = indexTo;
    } else {
        startLine = lineFrom;
        startIndex = indexFrom;
    }
}
