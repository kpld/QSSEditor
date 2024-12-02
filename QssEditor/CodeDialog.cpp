#include "CodeDialog.h"
#include <QVBoxLayout>
#include <QTextEdit>


CodeDialog::CodeDialog(QWidget *parent)
    :QDialog(parent)
{
    edit = NULL;

    initUI();
}

CodeDialog::~CodeDialog()
{

}

void CodeDialog::initUI()
{
    setWindowTitle(tr("Custom Palette Code"));
    setMinimumSize(650, 400);
    QVBoxLayout *layout = new QVBoxLayout();
    edit = new QTextEdit();
    layout->addWidget(edit);
    setLayout(layout);
}

void CodeDialog::showDialog(QString text)
{
    if (text.length() <= 0) {
        edit->setText(tr("No Custom QPalette, using the default palette."));
        edit->setEnabled(false);
    } else {
        edit->setEnabled(true);
        edit->setReadOnly(true);
        edit->setText(text);
    }

    show();
}
