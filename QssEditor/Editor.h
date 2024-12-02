#ifndef EDITOR_H
#define EDITOR_H

#include <QKeyEvent>
#include <QSci/qsciscintilla.h>


class SearchDialog;

class Editor : public QsciScintilla
{
    Q_OBJECT

public:
    Editor();
    ~Editor();

private:
    QString encoding;
    SearchDialog *searchDialog;

public:
    void setDefaultConfig();
    QString getEncoding();
    bool load(QString fileName);
    QString getFileType(QString fileName);
    void setLanguage(QString language);
    QString guessLanguage(QString fileName);
    QString detectEncoding(QString fileName);
    void save(QString fileName);
    int count(QString string, bool caseSensitive=false);

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusOutEvent(QFocusEvent *) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void dropEvent(QDropEvent *e) override;

signals:
    void keyPress(QKeyEvent *e);
    void loseFocus();
    void mouseLeave();
    void mousePress();
    void drop(QDropEvent *e);

public slots:
    void find();
    void replace();
};

#endif // EDITOR_H
