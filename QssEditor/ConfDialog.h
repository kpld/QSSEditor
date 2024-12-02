#ifndef CONFDIALOG_H
#define CONFDIALOG_H

#include <QDialog>

class QListWidget;
class QStackedWidget;
class QComboBox;
class QSpinBox;
class QCheckBox;

class ConfDialog : public QDialog
{
    Q_OBJECT
public:
    ConfDialog(QWidget *parent = nullptr);
    ~ConfDialog();

private:
    QListWidget    *leftList;
    QStackedWidget *rightStack;
    QPushButton    *cancelbtn;
    QPushButton    *okbtn;

    QComboBox      *langCombo;
    QSpinBox       *recentcountspin;
    QCheckBox      *checkboxAutoExportQss;

    QComboBox      *skinCombo;
    QString        skindir;

    QCheckBox      *checkboxUpdate;
    QComboBox      *updateCombo;


public:
    void initUI();
    void fillLangItems(QComboBox *box);
    void apply();
    void cancel();

signals:

public slots:

};

#endif // CONFDIALOG_H
