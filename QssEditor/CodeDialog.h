#ifndef CODEDIALOG_H
#define CODEDIALOG_H

#include <QDialog>

class QTextEdit;

class CodeDialog : public QDialog
{
    Q_OBJECT
public:
    CodeDialog(QWidget *parent = nullptr);
    ~CodeDialog();

private:
    QTextEdit *edit;

public:
    void initUI();
    void showDialog(QString text);

signals:

public slots:

};

#endif // CODEDIALOG_H
