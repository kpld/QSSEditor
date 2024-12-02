#include "PaletteDialog.h"
#include "CodeDialog.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QFont>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>
#include <QPalette>

PaletteDialog::PaletteDialog(QWidget *parent)
    :QDialog(parent)
{
    palette = qApp->palette();
    codeDialog = new CodeDialog(this);

    initUI();
}

PaletteDialog::~PaletteDialog()
{

}

void PaletteDialog::initUI()
{
    setWindowTitle(tr("Palette Color Setting"));
    setMinimumSize(500, 500);

    tabRole["Window"] = QPalette::Window;
    tabRole["WindowText"] = QPalette::WindowText;
    tabRole["Base"] = QPalette::Base;
    tabRole["AlternateBase"] = QPalette::AlternateBase;
    tabRole["Text"] = QPalette::Text;
    tabRole["Button"] = QPalette::Button;
    tabRole["ButtonText"] = QPalette::ButtonText;
    tabRole["BrightText"] = QPalette::BrightText;
    tabRole["ToolTipBase"] = QPalette::ToolTipBase;
    tabRole["ToolTipText"] = QPalette::ToolTipText;
    tabRole["PlaceholderText"] = QPalette::PlaceholderText;
    tabRole["Light"] = QPalette::Light;
    tabRole["Midlight"] = QPalette::Midlight;
    tabRole["Dark"] = QPalette::Dark;
    tabRole["Mid"] = QPalette::Mid;
    tabRole["Shadow"] = QPalette::Shadow;
    tabRole["Highlight"] = QPalette::Highlight;
    tabRole["HighlightedText"] = QPalette::HighlightedText;
    tabRole["Link"] = QPalette::Link;
    tabRole["LinkVisited"] = QPalette::LinkVisited;
    tabRole["NoRole"] = QPalette::NoRole;
    // tabRole.append(qMakePair("Window", QPalette::Window));
    // tabRole.append(qMakePair("WindowText", QPalette::WindowText));
    // tabRole.append(qMakePair("Base", QPalette::Base));
    // tabRole.append(qMakePair("AlternateBase", QPalette::AlternateBase));
    // tabRole.append(qMakePair("Text", QPalette::Text));
    // tabRole.append(qMakePair("Button", QPalette::Button));
    // tabRole.append(qMakePair("ButtonText", QPalette::ButtonText));
    // tabRole.append(qMakePair("BrightText", QPalette::BrightText));
    // tabRole.append(qMakePair("ToolTipBase", QPalette::ToolTipBase));
    // tabRole.append(qMakePair("ToolTipText", QPalette::ToolTipText));
    // tabRole.append(qMakePair("PlaceholderText", QPalette::PlaceholderText));
    // tabRole.append(qMakePair("Light", QPalette::Light));
    // tabRole.append(qMakePair("Midlight", QPalette::Midlight));
    // tabRole.append(qMakePair("Dark", QPalette::Dark));
    // tabRole.append(qMakePair("Mid", QPalette::Mid));
    // tabRole.append(qMakePair("Shadow", QPalette::Shadow));
    // tabRole.append(qMakePair("Highlight", QPalette::Highlight));
    // tabRole.append(qMakePair("HighlightedText", QPalette::HighlightedText));
    // tabRole.append(qMakePair("Link", QPalette::Link));
    // tabRole.append(qMakePair("LinkVisited", QPalette::LinkVisited));
    // tabRole.append(qMakePair("NoRole", QPalette::NoRole));

    QVBoxLayout *layout = new QVBoxLayout();
    tblWgt = new QTableWidget();
    tblWgt->setRowCount(tabRole.size());
    tblWgt->setColumnCount(5);
    tblWgt->setHorizontalHeaderLabels({"ColorRole", "Active", "Inactive", "Disabled", "reset"});
    tblWgt->verticalHeader()->setVisible(false);
    tblWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblWgt->setDragEnabled(false);
    tblWgt->setSelectionMode(QAbstractItemView::NoSelection);
    tblWgt->horizontalHeader()->setSectionsClickable(false);
    QFont f = tblWgt->font();
    f.setPointSize(9);
    tblWgt->setFont(f);
    for(int i=1; i<tblWgt->columnCount(); i++) {
        tblWgt->setColumnWidth(i, 80);
    }

    for(int i=0; i<tabRole.count(); i++) {
        tblWgt->setRowHeight(i, 15);
        tblWgt->setItem(i, 0, new QTableWidgetItem(tabRole.key(i)/*key*/));
        QPushButton *btn1 = new QPushButton();
        int clrRole = tabRole[tblWgt->item(i, 0)->text()];
        QString c1 = palette.color(QPalette::Active, (QPalette::ColorRole)clrRole).name();
        QString c2 = palette.color(QPalette::Inactive, (QPalette::ColorRole)clrRole).name();
        QString c3 = palette.color(QPalette::Disabled, (QPalette::ColorRole)clrRole).name();
        oldclr[tblWgt->item(i, 0)->text()] = ColorName(c1, c2, c3);
        btn1->setStyleSheet("background:" + c1);
        tblWgt->setCellWidget(i, 1, btn1);
        QPushButton *btn2 = new QPushButton();
        btn2->setStyleSheet("background:" + c2);
        tblWgt->setCellWidget(i, 2, btn2);
        QPushButton *btn3 = new QPushButton();
        btn3->setStyleSheet("background:" + c3);
        tblWgt->setCellWidget(i, 3, btn3);
        QPushButton *btn4 = new QPushButton("reset");
        btn4->setEnabled(false);
        tblWgt->setCellWidget(i, 4, btn4);

        connect(btn1, &QPushButton::clicked, this, &PaletteDialog::changeClr);
        connect(btn2, &QPushButton::clicked, this, &PaletteDialog::changeClr);
        connect(btn3, &QPushButton::clicked, this, &PaletteDialog::changeClr);
        connect(btn4, &QPushButton::clicked, this, &PaletteDialog::resetRow);
    }

    tblWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(tblWgt);
    setLayout(layout);

    QHBoxLayout *hlay = new QHBoxLayout();
    QPushButton *btnCode = new QPushButton(tr("ViewPaletteCode"));
    QPushButton *btnCancel = new QPushButton(tr("Cancel"));
    QPushButton *btnOk = new QPushButton(tr("OK"));
    btnCode->setMinimumSize(120, 25);
    btnCancel->setMinimumSize(60, 25);
    btnOk->setMinimumSize(60, 25);
    hlay->addWidget(btnCode);
    hlay->addStretch(1);
    hlay->addWidget(btnCancel);
    hlay->addWidget(btnOk);
    layout->addLayout(hlay);

    connect(btnCode, &QPushButton::clicked, this, &PaletteDialog::getCode);
    connect(btnOk, &QPushButton::clicked, this, &PaletteDialog::apply);
    connect(btnCancel, &QPushButton::clicked, this, &PaletteDialog::cancel);
}


void PaletteDialog::changeClr()
{
    int rowNum = tblWgt->currentRow();
    int colNum = tblWgt->currentColumn();
    QPushButton *btn = (QPushButton*)tblWgt->cellWidget(rowNum, colNum);
    QString clrRoleText = tblWgt->item(rowNum, 0)->text();
    QString c = oldclr[clrRoleText].clr[colNum-1];
    QColor color = QColorDialog::getColor(QColor(c), this, tr("color pick"), QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        QString clrstr = color.name();
        if (color.alpha() == 255) {
            clrstr = color.name().toUpper();
        } else {
            clrstr = color.name(QColor::HexArgb).toUpper();
        }
        if (!newclr.contains(clrRoleText)){
            newclr.insert(clrRoleText, ColorName(0, 0, 0));
        }
        //newclr[clrRoleText]]colNum-1] = clrstr
        newclr[clrRoleText].clr[colNum-1] = clrstr;
        btn->setStyleSheet("background:" + clrstr);
        QPushButton *btn1 = (QPushButton*)tblWgt->cellWidget(rowNum, 4);
        btn1->setEnabled(true);
    }
}

void PaletteDialog::resetRow()
{
    int rowNum = tblWgt->currentRow();
    //int colNum = tblWgt->currentColumn();
    QString clrRoleText = tblWgt->item(rowNum, 0)->text();
    newclr.take(clrRoleText);

    for(int i=1; i<=3; i++) {
        QPushButton *btn = (QPushButton*)tblWgt->cellWidget(rowNum, i);
        QString c = oldclr[clrRoleText].clr[i-1];
        btn->setStyleSheet("background:" + c);
    }

    QPushButton *btn = (QPushButton*)tblWgt->cellWidget(rowNum, 4);
    btn->setEnabled(false);
}

void PaletteDialog::getCode()
{
    QString str;
    QMap<QString, ColorName>::iterator iter;
    for(iter=newclr.begin(); iter!=newclr.end(); iter++) {
        QString clrRoleText = iter.key();
        ColorName cname = iter.value();
        if (!cname.clr[0].isEmpty()) {
            str += "palette.setColor(QPalette.Active, QPalette." + clrRoleText + ", QColor(" + cname.clr[0] + "))\n";
        }
        if (!cname.clr[1].isEmpty()) {
            str += "palette.setColor(QPalette.Inactive, QPalette." + clrRoleText + ", QColor(" + cname.clr[1] + "))\n";
        }
        if (!cname.clr[2].isEmpty()) {
            str += "palette.setColor(QPalette.Disabled, QPalette." + clrRoleText + ", QColor(" + cname.clr[2] + "))\n";
        }
    }

    codeDialog->showDialog(str);
}

void PaletteDialog::apply()
{
    QMap<QString, ColorName>::iterator iter;
    for(iter=newclr.begin(); iter!=newclr.end(); iter++) {
        QString clrRoleText = iter.key();
        ColorName cname = iter.value();
        if (!cname.clr[0].isEmpty()) {
            palette.setColor(QPalette::Active, (QPalette::ColorRole)tabRole[clrRoleText], QColor(cname.clr[0]));
            //palette.setColor(QPalette::Active, (QPalette::ColorRole))
            oldclr[clrRoleText].clr[0] = cname.clr[0];
        }
        if (!cname.clr[1].isEmpty()) {
            palette.setColor(QPalette::Inactive, (QPalette::ColorRole)tabRole[clrRoleText], QColor(cname.clr[0]));
            oldclr[clrRoleText].clr[1] = cname.clr[1];
        }
        if (!!cname.clr[2].isEmpty()) {
            palette.setColor(QPalette::Disabled, (QPalette::ColorRole)tabRole[clrRoleText], QColor(cname.clr[0]));
            oldclr[clrRoleText].clr[2] = cname.clr[2];
        }
    }

    qApp->setPalette(palette);
    close();
}

void PaletteDialog::cancel()
{
    newclr.clear();
    close();
}
