#include "ConfDialog.h"
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QScrollArea>
#include <QColorDialog>
#include <QFontComboBox>
#include <QDebug>

ConfDialog::ConfDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowFlags(Qt::Tool /*| Qt::WindowStaysOnTopHint*/);
    leftList = NULL;
    rightStack = NULL;
    cancelbtn = NULL;
    okbtn = NULL;
    langCombo = NULL;
    recentcountspin = NULL;
    checkboxAutoExportQss = NULL;
    skinCombo = NULL;
    checkboxUpdate = NULL;
    updateCombo = NULL;


    initUI();
}

ConfDialog::~ConfDialog()
{

}

void ConfDialog::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
//*
    QHBoxLayout *layH1 = new QHBoxLayout();
    QHBoxLayout *layH2 = new QHBoxLayout();
    leftList = new QListWidget();
    // left list
    leftList->addItem(tr("General"));
    leftList->addItem(tr("Editor"));
    leftList->addItem(tr("Update"));
    leftList->setMaximumWidth(150);

    rightStack = new QStackedWidget();
    rightStack->setMaximumHeight(306);
    layH1->addWidget(leftList);
    layH1->addWidget(rightStack);
    cancelbtn = new QPushButton(tr("Cancel"));
    okbtn = new QPushButton(tr("OK"));
    okbtn->setDefault(true);
    layH2->addStretch(1);
    layH2->addWidget(cancelbtn);
    layH2->addWidget(okbtn);
    mainLayout->addLayout(layH1);
    mainLayout->addLayout(layH2);
//*/
    setLayout(mainLayout);



    // right stack
//*
    QWidget *w = new QWidget();
    QVBoxLayout *layw = new QVBoxLayout();
//*/
//*
    // general
    QGroupBox *g11 = new QGroupBox(tr("General"));
    QFormLayout *glayout = new QFormLayout();
    QLabel *label1 = new QLabel(tr("Select UI language:"));
    langCombo = new QComboBox();
    fillLangItems(langCombo);
    langCombo->setMinimumWidth(150);
    QLabel *label2 = new QLabel(tr("Number of recent files:"));
    recentcountspin = new QSpinBox();
    recentcountspin->setMinimumWidth(50);
    recentcountspin->setMinimum(1);
    recentcountspin->setMaximum(30);
    glayout->addRow(label1, langCombo);
    glayout->addRow(label2, recentcountspin);
    g11->setLayout(glayout);
    layw->addWidget(g11);

    // advanced
    QGroupBox *g12 = new QGroupBox(tr("Advanced"));
    QLabel *labeladv1 = new QLabel(tr("Export qss When save qsst:"));
    checkboxAutoExportQss = new QCheckBox();
    checkboxAutoExportQss->setToolTip(tr("Option for whether export qss when save qsst file each time."));
    QHBoxLayout *layh121 = new QHBoxLayout();
    layh121->addWidget(labeladv1);
    layh121->addStretch(1);
    layh121->addWidget(checkboxAutoExportQss);
    QVBoxLayout *layv12 = new QVBoxLayout();
    layv12->addLayout(layh121);
    g12->setLayout(layv12);
    layw->addWidget(g12);

    // UI Skin
    QGroupBox *g13 = new QGroupBox(tr("UI Skin"));
    QLabel *labelSkin1 = new QLabel(tr("Select the ui skin:"));
    skinCombo = new QComboBox();
    skinCombo->setToolTip(tr("Select the ui skin."));
    skindir = "skin";
    QDir dir(skindir);
    QStringList filename;
    filename<<"*.qss"<<"*.QSS";
    QStringList results;
    if (dir.exists()) {
        results = dir.entryList(filename, QDir::Files|QDir::Readable, QDir::Name);
    }
    skinCombo->addItems(results);
    QHBoxLayout *layh131 = new QHBoxLayout();
    layh131->addWidget(labelSkin1);
    layh131->addStretch(1);
    layh131->addWidget(skinCombo);
    QLabel *labelSkin2 = new QLabel(tr("Manage skins:"));
    QPushButton *skinaddr = new QPushButton(tr("Skin Management"));
    skinaddr->setToolTip(tr("Open the skin directory."));
    connect(skinaddr, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl::fromLocalFile(skindir));
    });
    QHBoxLayout *layh132 = new QHBoxLayout();
    layh132->addWidget(labelSkin2);
    layh132->addStretch(1);
    layh132->addWidget(skinaddr);

    QVBoxLayout *layv13 = new QVBoxLayout();
    layv13->addLayout(layh131);
    layv13->addLayout(layh132);
    g13->setLayout(layv13);
    layw->addWidget(g13);

    layw->addStretch(1);
    w->setLayout(layw);
    rightStack->addWidget(w);
//*/
//*
    // Code Editor Setting Pannel
    QScrollArea *area = new QScrollArea();
    QWidget *w2 = new QWidget();
    QVBoxLayout *layw2 = new QVBoxLayout();
    // colors
    QGroupBox *g21 = new QGroupBox(tr("Colors"));
    QLabel *labelTxtColor = new QLabel(tr("Text color"));
    QPushButton *btnTxtColor = new QPushButton();
    btnTxtColor->setMinimumWidth(80);
    btnTxtColor->setStyleSheet("background-color: rgb(0, 0, 0);");
    connect(btnTxtColor, &QPushButton::clicked, [=](){
        QColor color = QColorDialog::getColor(Qt::black);
        if (color.isValid()) {
            QString colorName = color.name();
            colorName.prepend("background-color:");
            btnTxtColor->setStyleSheet(colorName);
        }
    });
    QHBoxLayout *layh211 = new QHBoxLayout();
    layh211->addWidget(labelTxtColor);
    layh211->addStretch(1);
    layh211->addWidget(btnTxtColor);

    QLabel *labelPaperColor = new QLabel(tr("Paper color"));
    QPushButton *btnPaperColor = new QPushButton();
    btnPaperColor->setMinimumWidth(80);
    btnPaperColor->setStyleSheet("background-color: rgb(255, 255, 255);");
    connect(btnPaperColor, &QPushButton::clicked, [=](){
        QColor color = QColorDialog::getColor(Qt::white);
        if (color.isValid()) {
            QString colorName = color.name();
            colorName.prepend("background-color:");
            btnPaperColor->setStyleSheet(colorName);
        }
    });
    QHBoxLayout *layh212 = new QHBoxLayout();
    layh212->addWidget(labelPaperColor);
    layh212->addStretch(1);
    layh212->addWidget(btnPaperColor);

    QVBoxLayout *layv21 = new QVBoxLayout();
    layv21->addLayout(layh211);
    layv21->addLayout(layh212);
    g21->setLayout(layv21);
    layw2->addWidget(g21);
    // text
    QGroupBox *g22 = new QGroupBox(tr("Text"));
    QLabel *labelFontFamily = new QLabel(tr("Font Family"));
    QFontComboBox *comboFontFamily = new QFontComboBox();
    comboFontFamily->setMinimumWidth(100);
    comboFontFamily->setMaximumWidth(150);
    comboFontFamily->setFontFilters(QFontComboBox::AllFonts);
    connect(comboFontFamily, &QFontComboBox::currentFontChanged, [=](){
        QString  family = comboFontFamily->currentFont().family();
        qDebug()<<family;
    });
    QHBoxLayout *layh221 = new QHBoxLayout();
    layh221->addWidget(labelFontFamily);
    layh221->addStretch(1);
    layh221->addWidget(comboFontFamily);

    QLabel *labelFontSize = new QLabel(tr("Font Size"));
    QSpinBox *spbFontSize = new QSpinBox();
    spbFontSize->setMinimumWidth(50);
    spbFontSize->setRange(1, 30);
    spbFontSize->setValue(11);
    QHBoxLayout *layh222 = new QHBoxLayout();
    layh222->addWidget(labelFontSize);
    layh222->addStretch(1);
    layh222->addWidget(spbFontSize);

    QVBoxLayout *layv22 = new QVBoxLayout();
    layv22->addLayout(layh221);
    layv22->addLayout(layh222);
    g22->setLayout(layv22);
    layw2->addWidget(g22);
    // indentation
    QGroupBox *g23 = new QGroupBox(tr("Indentation"));
    QLabel *labelTabWidth = new QLabel(tr("Tab width"));
    QSpinBox *spbTabWidth = new QSpinBox();
    spbTabWidth->setMinimumWidth(50);
    spbTabWidth->setRange(1, 8);
    spbTabWidth->setValue(4);
    QHBoxLayout *layh231 = new QHBoxLayout();
    layh231->addWidget(labelTabWidth);
    layh231->addStretch(1);
    layh231->addWidget(spbTabWidth);

    QLabel *labelTabIndents = new QLabel(tr("Tab indents"));
    QCheckBox *chkTabIndents = new QCheckBox();
    QHBoxLayout *layh232 = new QHBoxLayout();
    layh232->addWidget(labelTabIndents);
    layh232->addStretch(1);
    layh232->addWidget(chkTabIndents);

    QLabel *labelBackspace = new QLabel(tr("Backspace unindents"));
    QCheckBox *chkBackspace = new QCheckBox();
    QHBoxLayout *layh233 = new QHBoxLayout();
    layh233->addWidget(labelBackspace);
    layh233->addStretch(1);
    layh233->addWidget(chkBackspace);

    QLabel *labelAutoIndent = new QLabel(tr("Auto-indent"));
    QCheckBox *chkAutoIndent = new QCheckBox();
    QHBoxLayout *layh234 = new QHBoxLayout();
    layh234->addWidget(labelAutoIndent);
    layh234->addStretch(1);
    layh234->addWidget(chkAutoIndent);

    QLabel *labelIndentGuides = new QLabel(tr("Indentation guides"));
    QCheckBox *chkIndentGuides = new QCheckBox();
    QHBoxLayout *layh235 = new QHBoxLayout();
    layh235->addWidget(labelIndentGuides);
    layh235->addStretch(1);
    layh235->addWidget(chkIndentGuides);

    QLabel *labelUseTab = new QLabel(tr("Use Tab character"));
    QCheckBox *chkUseTab = new QCheckBox();
    QHBoxLayout *layh236 = new QHBoxLayout();
    layh236->addWidget(labelUseTab);
    layh236->addStretch(1);
    layh236->addWidget(chkUseTab);

    QVBoxLayout *layv23 = new QVBoxLayout();
    layv23->addLayout(layh231);
    layv23->addLayout(layh232);
    layv23->addLayout(layh233);
    layv23->addLayout(layh234);
    layv23->addLayout(layh235);
    layv23->addLayout(layh236);
    g23->setLayout(layv23);
    layw2->addWidget(g23);
    // wrapping
    QGroupBox *g24 = new QGroupBox(tr("Wrapping"));
    QLabel *labelWrapMode = new QLabel(tr("Wrap Mode"));
    QComboBox *comboWrapMode = new QComboBox();
    comboWrapMode->setMinimumWidth(100);
    comboWrapMode->addItems({"None", "Word", "Character"});
    comboWrapMode->setCurrentIndex(0);
    QHBoxLayout *layh241 = new QHBoxLayout();
    layh241->addWidget(labelWrapMode);
    layh241->addStretch(1);
    layh241->addWidget(comboWrapMode);

    QLabel *labelEdgeMode = new QLabel(tr("Edge Mode"));
    QComboBox *comboEdgeMode = new QComboBox();
    comboEdgeMode->setMinimumWidth(100);
    comboEdgeMode->addItems({"None", "Line", "Background"});
    comboEdgeMode->setCurrentIndex(1);
    QHBoxLayout *layh242 = new QHBoxLayout();
    layh242->addWidget(labelEdgeMode);
    layh242->addStretch(1);
    layh242->addWidget(comboEdgeMode);

    QLabel *labelTxtWidth = new QLabel(tr("Text width"));
    QSpinBox *spbTxtWidth = new QSpinBox();
    spbTxtWidth->setMinimumWidth(50);
    spbTxtWidth->setRange(1, 100);
    spbTxtWidth->setValue(80);
    QHBoxLayout *layh243 = new QHBoxLayout();
    layh243->addWidget(labelTxtWidth);
    layh243->addStretch(1);
    layh243->addWidget(spbTxtWidth);

    QVBoxLayout *layv24 = new QVBoxLayout();
    layv24->addLayout(layh241);
    layv24->addLayout(layh242);
    layv24->addLayout(layh243);
    g24->setLayout(layv24);
    layw2->addWidget(g24);
    // formatting
    QGroupBox *g25 = new QGroupBox(tr("Formatting"));
    QLabel *labelWhiteSpace = new QLabel(tr("Whitespace"));
    QComboBox *comboWhiteSpace = new QComboBox();
    comboWhiteSpace->setMinimumWidth(100);
    comboWhiteSpace->addItems({"Invisible", "Visible", "VisibleAfterIndent"});
    QHBoxLayout *layh251 = new QHBoxLayout();
    layh251->addWidget(labelWhiteSpace);
    layh251->addStretch(1);
    layh251->addWidget(comboWhiteSpace);

    QLabel *labelLineEndings = new QLabel(tr("Line Endings"));
    QComboBox *comboLineEndings = new QComboBox();
    comboLineEndings->setMinimumWidth(100);
    comboLineEndings->addItems({"Windows", "Unix", "Mac"});
    QHBoxLayout *layh252 = new QHBoxLayout();
    layh252->addWidget(labelLineEndings);
    layh252->addStretch(1);
    layh252->addWidget(comboLineEndings);

    QLabel *labelShowCRLF = new QLabel(tr("Show CR/LF"));
    QCheckBox *chkShowCRLF = new QCheckBox();
    QHBoxLayout *layh253 = new QHBoxLayout();
    layh253->addWidget(labelShowCRLF);
    layh253->addStretch(1);
    layh253->addWidget(chkShowCRLF);

    QVBoxLayout *layv25 = new QVBoxLayout();
    layv25->addLayout(layh251);
    layv25->addLayout(layh252);
    layv25->addLayout(layh253);
    g25->setLayout(layv25);
    layw2->addWidget(g25);
    // coding aids
    QGroupBox *g26 = new QGroupBox(tr("Coding aids"));
    QLabel *labelLang = new QLabel(tr("Language"));
    QComboBox *comboLang = new QComboBox();
    comboLang->setMinimumWidth(100);
    comboLang->addItems({"Text", "QSS", "Bash", "Batch", "CMake", "CPP"});
    comboLang->setCurrentIndex(1);
    QHBoxLayout *layh261 = new QHBoxLayout();
    layh261->addWidget(labelLang);
    layh261->addStretch(1);
    layh261->addWidget(comboLang);

    QLabel *labelFolding = new QLabel(tr("Folding"));
    QComboBox *comboFolding = new QComboBox();
    comboFolding->setMinimumWidth(100);
    comboFolding->addItems({"No", "Plain", "Circled", "Boxed", "CircledTree", "BoxedTree"});
    comboFolding->setCurrentIndex(5);
    QHBoxLayout *layh262 = new QHBoxLayout();
    layh262->addWidget(labelFolding);
    layh262->addStretch(1);
    layh262->addWidget(comboFolding);

    QLabel *labelBraceMatch = new QLabel(tr("Brace Matching"));
    QComboBox *comboBraceMatch = new QComboBox();
    comboBraceMatch->setMinimumWidth(100);
    comboBraceMatch->addItems({"No", "Strict", "Sloppy"});
    comboBraceMatch->setCurrentIndex(2);
    QHBoxLayout *layh263 = new QHBoxLayout();
    layh263->addWidget(labelBraceMatch);
    layh263->addStretch(1);
    layh263->addWidget(comboBraceMatch);

    QVBoxLayout *layv26 = new QVBoxLayout();
    layv26->addLayout(layh261);
    layv26->addLayout(layh262);
    layv26->addLayout(layh263);
    g26->setLayout(layv26);
    layw2->addWidget(g26);

    layw2->addStretch(1);
    w2->setLayout(layw2);
    area->setWidget(w2);
    area->setWidgetResizable(true);
    rightStack->addWidget(area);
//*/
//*
    // right stack for update
    QWidget *w3 = new QWidget();
    QVBoxLayout *layw3 = new QVBoxLayout();
    // update setting
    QGroupBox *g31 = new QGroupBox(tr("Update check"));
    checkboxUpdate = new QCheckBox(tr("Auto check for update"));
    QLabel *labtmp = new QLabel(tr("Update checking frequency:"));
    updateCombo = new QComboBox();
    updateCombo->setToolTip(tr("setup frequency for checking update"));
    updateCombo->addItem(tr("Each startup"), "start");
    updateCombo->addItem(tr("Every day"), "day");
    updateCombo->addItem(tr("Every week"), "week");
    updateCombo->addItem(tr("Every month"), "month");
    updateCombo->setEnabled(false);
    connect(checkboxUpdate, &QCheckBox::stateChanged, updateCombo, &QComboBox::setEnabled);

    QVBoxLayout *layv31 = new QVBoxLayout();
    QHBoxLayout *layh311 = new QHBoxLayout();
    layv31->addWidget(checkboxUpdate);
    layv31->addLayout(layh311);
    layh311->addWidget(labtmp);
    layh311->addStretch(1);
    layh311->addWidget(updateCombo);
    g31->setLayout(layv31);
    // other todo

    layw3->addWidget(g31);
    layw3->addStretch(1);
    w3->setLayout(layw3);
    rightStack->addWidget(w3);
//*/
    // action for dialog
    connect(leftList, &QListWidget::currentRowChanged, rightStack, &QStackedWidget::setCurrentIndex);
    connect(cancelbtn, &QPushButton::clicked, [=](){
        cancel();
        close();
    });
    connect(okbtn, &QPushButton::clicked, [=](){
        apply();
        close();
    });

    // actions

}

void ConfDialog::fillLangItems(QComboBox *box)
{

}

void ConfDialog::apply()
{

}

void ConfDialog::cancel()
{

}
