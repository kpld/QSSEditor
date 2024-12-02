#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QMainWindow>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class Editor;

class SearchDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

private:
    QWidget *mParent;
    bool    isReplaceMode;
    Editor* editor;

    bool    reFlag;
    bool    caseFlag;
    bool    wordFlag;
    bool    wrapFlag;
    bool    forwardFlag;
    int     startLine;
    int     startIndex;
    bool    showAllFlag;
    bool    posixFlag;
    bool    cxx11Flag;
    bool    startNewSearch;
    bool    escapeFlag;
    QString searchText;
    QString replaceText;
    bool    finded;

    QCheckBox    *reverseCheckbox;
    QLabel       *replaceLabel;
    QLineEdit    *searchTextBox;
    QLineEdit    *replaceTextBox;
    QPushButton  *findPreBtn;
    QPushButton  *countBtn;
    QPushButton  *replaceBtn;
    QPushButton  *replaceAllBtn;


private:
    void setupUi();

public:
    void setReplaceMode(bool isReplace);
    void findReplace(bool isReplace=false);
signals:

public slots:
    void changeText();
    void setReverse(bool isReverse);
    void setCase(bool casesencitive);
    void setWord(bool word);
    void setEscape(bool escape);
    void setRe(bool regexpression);

};

#endif // SEARCHDIALOG_H
