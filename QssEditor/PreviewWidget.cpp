#include "PreviewWidget.h"
#include "DrawWidget.h"
#include "PicWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>
#include <QStandardItemModel>
#include <QCompleter>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QCommandLinkButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QCalendarWidget>
#include <QSlider>
#include <QProgressBar>
#include <QScrollBar>
#include <QDial>
#include <QSplitter>
#include <QMdiArea>
#include <QDockWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QToolBox>
#include <QTableWidget>
#include <QTreeWidget>
#include <QFileSystemModel>

PreviewWidget::PreviewWidget(QWidget *parent)
    : QTabWidget(parent)
{
//*
    tab1 = new QWidget(this);
    tab2 = new QWidget(this);
    tab3 = new QWidget(this);
    tab4 = new QWidget(this);
    tab5 = new QWidget(this);
    tab6 = new QWidget(this);

    addTab(tab1, tr("Basic"));
    addTab(tab2, tr("Special"));
    addTab(tab3, tr("Drawing"));
    addTab(tab4, tr("Layout"));
    addTab(tab5, tr("Container"));
    addTab(tab6, tr("Advance"));

    setupTab1();
    setupTab2();
    setupTab3();
    setupTab4();
    setupTab5();
    setupTab6();
//*/
}

void PreviewWidget::setupTab1()
{
//*
    QVBoxLayout *scrollContainer = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *mainWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    mainWidget->setLayout(layout);
    mainWidget->setMinimumSize(QSize(420, 800));
    scrollArea->setWidget(mainWidget);
    scrollContainer->addWidget(scrollArea);
    tab1->setLayout(scrollContainer);

    // Label TextBox
    QGroupBox *group1 = new QGroupBox(tr("Text"));
    group1->setCheckable(true);
    QHBoxLayout *group1Layout = new QHBoxLayout();
    group1->setLayout(group1Layout);
    layout->addWidget(group1);
    QFormLayout *layoutCol1 = new QFormLayout();
    QFormLayout *layoutCol2 = new QFormLayout();
    group1Layout->addLayout(layoutCol1);
    group1Layout->addLayout(layoutCol2);

    QLabel *label1 = new QLabel(tr("User Name(&Id):"));
    QLineEdit *text1 = new QLineEdit(tr("default"));
    label1->setBuddy(text1);
    QLabel *label2 = new QLabel(tr("data 1:"));
    QLineEdit *text2 = new QLineEdit();
    text2->setPlaceholderText(tr("input"));
    QLabel *label3 = new QLabel(tr("<b>Password</b>:"));
    QLineEdit* text3 = new QLineEdit("******");
    text3->setEchoMode(QLineEdit::Password);
    QLabel *label4 = new QLabel(tr("link label:"));
    QLabel *label5 = new QLabel("<a href='https://github.com/kpld/'>blog</a>");
    label5->setOpenExternalLinks(true);
    QLabel *label6 = new QLabel(tr("icon label:"));
    QLabel *label7 = new QLabel("icon");
    label7->setPixmap(QPixmap(":res/img/book_address.png"));
    layoutCol1->addRow(label1, text1);
    layoutCol1->addRow(label2, text2);
    layoutCol1->addRow(label3, text3);
    layoutCol1->addRow(label4, label5);
    layoutCol1->addRow(label6, label7);

    QLineEdit *text4 = new QLineEdit();
    text4->setInputMask("0000-00-00");
    QLineEdit *text5 = new QLineEdit();
    text5->setInputMask("HH:HH:HH:HH:HH:HH;_");
    QLineEdit *text6 = new QLineEdit();
    text6->setInputMask("XXXXXX");
    QLineEdit *text7 = new QLineEdit();
    QDoubleValidator *validator1 = new QDoubleValidator();
    validator1->setRange(0, 100);
    validator1->setDecimals(2);
    text7->setValidator(validator1);
    QLineEdit *text8 = new QLineEdit();
    QRegularExpressionValidator *validator2 = new QRegularExpressionValidator();
    QRegularExpression *reg = new QRegularExpression("[a-zA-Z0-9]+$");
    validator2->setRegularExpression(*reg);
    text8->setValidator(validator2);
    layoutCol2->addRow(tr("Date Mask:"), text4);
    layoutCol2->addRow(tr("Mac Mask"), text5);
    layoutCol2->addRow(tr("String Mask"), text6);
    layoutCol2->addRow(tr("Double Validate:"), text7);
    layoutCol2->addRow(tr("Regexp Validate:"), text8);

    QLineEdit *text9 = new QLineEdit();
    text9->setPlaceholderText("input email");
    text9->setToolTip("please input a email address.");
    QStandardItemModel *model = new QStandardItemModel(0, 1, this);
    QCompleter *completer = new QCompleter(model, this);
    text9->setCompleter(completer);
    connect(text9, &QLineEdit::textChanged, this, [&](QString texts){
        if (texts.contains("@")) return;

        QStringList strList = {"@163.com", "@qq.com", "@gmail.com", "@hotmail.com", "@126.com"};
        model->removeRows(0, model->rowCount());
        foreach(QString str, strList) {
            model->insertRow(0);
            model->setData(model->index(0, 0), texts+str);
        }
    });
    QLineEdit *text10 = new QLineEdit("ReadOnly");
    text10->setReadOnly(true);
    layoutCol1->addRow(tr("auto complete:"), text9);
    layoutCol2->addRow("Readonly:", text10);

    // Button
    QGroupBox *group2 = new QGroupBox("Button");
    group2->setCheckable(true);
    QVBoxLayout *group2Layout = new QVBoxLayout();
    group2->setLayout(group2Layout);
    layout->addWidget(group2);
    QHBoxLayout *layoutRow1 = new QHBoxLayout();
    QHBoxLayout* layoutRow2 = new QHBoxLayout();
    group2Layout->addLayout(layoutRow1);
    group2Layout->addLayout(layoutRow2);

    QPushButton *btn1 = new QPushButton("Button");
    QPushButton *btn2 = new QPushButton("IconButton");
    btn2->setIcon(QIcon(":res/img/yes.png"));
    QPushButton *btn3 = new QPushButton("Disabled");
    btn3->setEnabled(false);
    QPushButton *btn4 = new QPushButton("Default");
    btn4->setDefault(true);
    QPushButton *btn5 = new QPushButton("Switch");
    btn5->setCheckable(true);
    QToolButton *btn6 = new QToolButton();
    btn6->setText("ToolButton");
    btn6->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *m = new QMenu();
    m->addAction("action1");
    m->addAction("action2");
    m->addAction("action3");
    btn6->setMenu(m);
    QCommandLinkButton *btn7 = new QCommandLinkButton("LinkBtn");
    layoutRow1->addWidget(btn1);
    layoutRow1->addWidget(btn2);
    layoutRow1->addWidget(btn3);
    layoutRow1->addWidget(btn4);
    layoutRow2->addWidget(btn5);
    layoutRow2->addWidget(btn6);
    layoutRow2->addWidget(btn7);

    // Checkable Item
    QGroupBox *group3 = new QGroupBox("Checkable");
    QVBoxLayout *group3Layout = new QVBoxLayout();
    QHBoxLayout *layoutRow3 = new QHBoxLayout();
    QHBoxLayout *layoutRow4 = new QHBoxLayout();
    group3Layout->addLayout(layoutRow3);
    group3Layout->addLayout(layoutRow4);
    group3->setLayout(group3Layout);
    layout->addWidget(group3);

    group3->setCheckable(true);
    QRadioButton *ch1 = new QRadioButton("Radio");
    QRadioButton *ch2 = new QRadioButton("IconRadio");
    ch2->setIcon(QIcon(":res/img/Flag_blueHS.png"));
    QRadioButton *ch3 = new QRadioButton("IconRadio");
    ch3->setIcon(QIcon(":res/img/Flag_greenHS.png"));
    QRadioButton *ch4 = new QRadioButton("Disable");
    ch4->setEnabled(false);
    QCheckBox *ch5 = new QCheckBox("CheckBox");
    QCheckBox *ch6 = new QCheckBox("CheckBox");
    ch6->setIcon(QIcon(":res/img/Flag_blueHS.png"));
    QCheckBox *ch7 = new QCheckBox("TriState");
    ch7->setTristate(true);
    ch7->setCheckState(Qt::PartiallyChecked);
    QCheckBox *ch8 = new QCheckBox("Disable");
    ch8->setEnabled(false);
    layoutRow3->addWidget(ch1);
    layoutRow3->addWidget(ch2);
    layoutRow3->addWidget(ch3);
    layoutRow3->addWidget(ch4);
    layoutRow4->addWidget(ch5);
    layoutRow4->addWidget(ch6);
    layoutRow4->addWidget(ch7);
    layoutRow4->addWidget(ch8);

    // Selecting Input
    QGroupBox *group4 = new QGroupBox("Selectable");
    group4->setCheckable(true);
    QVBoxLayout *group4Layout = new QVBoxLayout();
    QHBoxLayout *layoutRow5 = new QHBoxLayout();
    group4Layout->addLayout(layoutRow5);
    group4->setLayout(group4Layout);
    layout->addWidget(group4);

    QSpinBox *s1 = new QSpinBox();
    s1->setValue(50);
    QDoubleSpinBox *s2 = new QDoubleSpinBox();
    s2->setRange(0, 1);
    s2->setValue(0.5);
    QComboBox *s3 = new QComboBox();
    s3->addItems(QStringList{"aaa", "bbb", "ccc"});
    s3->setEditable(true);
    s3->setCurrentIndex(2);
    QComboBox *s4 = new QComboBox();
    s4->addItems(QStringList{"aaa", "bbb", "ccc"});
    layoutRow5->addWidget(s1);
    layoutRow5->addWidget(s2);
    layoutRow5->addWidget(s3);
    layoutRow5->addWidget(s4);

    // TextEdit
    QGroupBox *group5 = new QGroupBox("TextEdit");
    group5->setCheckable(true);
    QVBoxLayout *group5Layout = new QVBoxLayout();
    group5->setLayout(group5Layout);
    layout->addWidget(group5);

    QTextEdit *te1 = new QTextEdit(tr("If you do not leave me, I will be by your side until the end."));
    group5Layout->addWidget(te1);

    layout->addStretch(1);
//*/
}

void PreviewWidget::setupTab2()
{
    QVBoxLayout *scrollContainer = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *mainWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    mainWidget->setLayout(layout);
    mainWidget->setMinimumSize(QSize(420, 800));
    scrollArea->setWidget(mainWidget);
    scrollContainer->addWidget(scrollArea);
    tab2->setLayout(scrollContainer);

    // Dialog
    QGroupBox *group0 = new QGroupBox("Dialog");
    QVBoxLayout *group0Layout = new QVBoxLayout();
    QHBoxLayout *layoutRow1 = new QHBoxLayout();
    QHBoxLayout *layoutRow2 = new QHBoxLayout();
    group0Layout->addLayout(layoutRow1);
    group0Layout->addLayout(layoutRow2);
    group0->setLayout(group0Layout);
    layout->addWidget(group0);

    QPushButton *b1 = new QPushButton(tr("Info"));
    connect(b1, &QPushButton::clicked, [=](){
        QMessageBox::information(this,
                                 "Info",
                                 tr("This is a message."),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
    });
    QPushButton *b2 = new QPushButton(tr("Question"));
    connect(b2, &QPushButton::clicked, [=](){
        QMessageBox::question(this,
                              "Question",
                              tr("Are you sure?"),
                              QMessageBox::No|QMessageBox::Yes,
                              QMessageBox::Yes);
    });
    QPushButton *b3 = new QPushButton(tr("Warning"));
    connect(b3, &QPushButton::clicked, [=](){
        QMessageBox::warning(this,
                             "Warning",
                             tr("This is a warning."),
                             QMessageBox::No|QMessageBox::Yes,
                             QMessageBox::Yes);
    });
    QPushButton *b4 = new QPushButton(tr("Error"));
    connect(b4, &QPushButton::clicked, [=](){
        QMessageBox::critical(this,
                              "Error",
                              tr("It's a error."),
                              QMessageBox::No|QMessageBox::Yes,
                              QMessageBox::Yes);
    });
    QPushButton *b5 = new QPushButton(tr("About"));
    connect(b5, &QPushButton::clicked, [=](){
        QMessageBox::about(this,
                           "About",
                           tr("About this software"));
    });
    QPushButton *b6 = new QPushButton(tr("Input"));
    connect(b6, &QPushButton::clicked, [=](){
        QInputDialog::getInt(this,
                             "Input",
                            tr("please input int"));
    });
    connect(b6, &QPushButton::clicked, [=](){
        QInputDialog::getDouble(this,
                                "Input",
                                tr("please input float"));
    });
    connect(b6, &QPushButton::clicked, [=](){
        QInputDialog::getItem(this,
                              "Input",
                              tr("please select"),
                              QStringList{"aaa", "bbb"});
    });
    QPushButton *b7 = new QPushButton(tr("Color"));
    connect(b7, &QPushButton::clicked, [=](){
        QColorDialog::getColor();
    });
    QPushButton *b8 = new QPushButton(tr("Font"));
    connect(b8, &QPushButton::clicked, [=](){
        bool bOk;
        QFontDialog::getFont(&bOk);
    });
    QPushButton *b9 = new QPushButton(tr("OpenFile"));
    connect(b9, &QPushButton::clicked, [=](){
        QFileDialog::getOpenFileName(this, "open", "", "Text(*.txt *.text)");
    });
    QPushButton *b10 = new QPushButton(tr("SaveFile"));
    connect(b10, &QPushButton::clicked, [=](){
        QFileDialog::getSaveFileName();
    });
    layoutRow1->addWidget(b1);
    layoutRow1->addWidget(b2);
    layoutRow1->addWidget(b3);
    layoutRow1->addWidget(b4);
    layoutRow1->addWidget(b5);
    layoutRow2->addWidget(b6);
    layoutRow2->addWidget(b7);
    layoutRow2->addWidget(b8);
    layoutRow2->addWidget(b9);
    layoutRow2->addWidget(b10);

    // DateTime
    QGroupBox *group1 = new QGroupBox("DateTime");
    group1->setCheckable(true);
    QHBoxLayout *group1Layout = new QHBoxLayout();
    QVBoxLayout *layoutRow3 = new QVBoxLayout();
    QVBoxLayout *layoutRow4 = new QVBoxLayout();
    group1Layout->addLayout(layoutRow3);
    group1Layout->addLayout(layoutRow4);
    group1->setLayout(group1Layout);
    layout->addWidget(group1);

    group1->setMaximumHeight(240);
    QDateEdit *dt1 = new QDateEdit();
    dt1->setDate(QDate::currentDate());
    QTimeEdit *dt2 = new QTimeEdit();
    dt2->setTime(QTime::currentTime());
    QDateTimeEdit *dt3 = new QDateTimeEdit();
    dt3->setDateTime(QDateTime::currentDateTime());
    QDateTimeEdit *dt4 = new QDateTimeEdit();
    dt4->setCalendarPopup(true);
    QCalendarWidget *dt5 = new QCalendarWidget();
    dt5->setMaximumSize(QSize(250, 240));
    layoutRow3->addWidget(dt1);
    layoutRow3->addWidget(dt2);
    layoutRow3->addWidget(dt3);
    layoutRow3->addWidget(dt4);
    layoutRow4->addWidget(dt5);

    // Slider
    QGroupBox *group2 = new QGroupBox("Sliders");
    group2->setCheckable(true);
    QVBoxLayout *group2Layout = new QVBoxLayout();
    QHBoxLayout *layoutRow5 = new QHBoxLayout();
    QHBoxLayout *layoutRow6 = new QHBoxLayout();
    group2Layout->addLayout(layoutRow5);
    group2Layout->addLayout(layoutRow6);
    group2->setLayout(group2Layout);
    layout->addWidget(group2);

    QSlider *slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setMaximum(100);
    QProgressBar *progress = new QProgressBar();
    connect(slider, &QSlider::valueChanged, progress, &QProgressBar::setValue);
    slider->setValue(50);
    QScrollBar *scroll1 = new QScrollBar();
    QScrollBar *scroll2 = new QScrollBar();
    QScrollBar *scroll3 = new QScrollBar();
    scroll1->setMaximum(255);
    scroll2->setMaximum(255);
    scroll3->setMaximum(255);
    scroll1->setOrientation(Qt::Horizontal);
    scroll2->setOrientation(Qt::Horizontal);
    scroll3->setOrientation(Qt::Horizontal);
    QLabel *c = new QLabel(tr("Slide to change color"));
    c->setAutoFillBackground(true);
    c->setAlignment(Qt::AlignCenter);
    c->setStyleSheet("background:rgba(0, 0, 0,100);");
    connect(scroll1, &QScrollBar::valueChanged, [=](){
        QString clr = QString("background: rgba(%1,%2,%3,100);").arg(scroll1->value()).arg(scroll2->value()).arg(scroll3->value());
        c->setStyleSheet(clr);
    });
    connect(scroll2, &QScrollBar::valueChanged, [=](){
        QString clr = QString("background: rgba(%1,%2,%3,100);").arg(scroll1->value()).arg(scroll2->value()).arg(scroll3->value());
        c->setStyleSheet(clr);
    });
    connect(scroll3, &QScrollBar::valueChanged, [=](){
        QString clr = QString("background: rgba(%1,%2,%3,100);").arg(scroll1->value()).arg(scroll2->value()).arg(scroll3->value());
        c->setStyleSheet(clr);
    });
    scroll1->setValue(128);
    layoutRow5->addWidget(slider);
    layoutRow5->addWidget(progress);
    QVBoxLayout *layCol1 = new QVBoxLayout();
    layCol1->addWidget(scroll1);
    layCol1->addWidget(scroll2);
    layCol1->addWidget(scroll3);
    layoutRow6->addLayout(layCol1);
    layoutRow6->addWidget(c);

    // Meter
    QGroupBox *group3 = new QGroupBox("Meters");
    group3->setCheckable(true);
    QHBoxLayout *layRow = new QHBoxLayout();
    group3->setLayout(layRow);
    layout->addWidget(group3);

    QDial *dial1 = new QDial();
    QDial *dial2 = new QDial();
    dial2->setNotchesVisible(true);
    connect(dial1, &QDial::valueChanged, dial2, &QDial::setValue);
    layRow->addWidget(dial1);
    layRow->addWidget(dial2);

    layout->addStretch(1);
}

void PreviewWidget::setupTab3()
{
    QVBoxLayout *scrollContainer = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *mainWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    mainWidget->setLayout(layout);
    mainWidget->setMinimumSize(QSize(420,500));
    scrollArea->setWidget(mainWidget);
    scrollContainer->addWidget(scrollArea);
    tab3->setLayout(scrollContainer);

    // Graphics
    QGroupBox *group1 = new QGroupBox("DrawGraphics");
    group1->setCheckable(true);
    QHBoxLayout *group1Layout = new QHBoxLayout();
    group1->setLayout(group1Layout);
    layout->addWidget(group1);

    DrawWidget *draw = new DrawWidget();
    group1Layout->addWidget(draw);

    // picture
    QGroupBox *group2 = new QGroupBox("Pictures");
    group2->setCheckable(true);
    QHBoxLayout *group2Layout = new QHBoxLayout();
    group2->setLayout(group2Layout);
    layout->addWidget(group2);

    QLabel *pic1 = new QLabel();
    pic1->setPixmap(QPixmap(":res/img/cup.jpg"));
    QLabel *pic1text = new QLabel("QLabel");
    pic1text->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *pic1Layout = new QVBoxLayout();
    pic1Layout->addWidget(pic1);
    pic1Layout->addWidget(pic1text);
    group2Layout->addLayout(pic1Layout);
    group2Layout->addStretch(1);

    QLabel *pic2text = new QLabel("QWidget Paint");
    pic2text->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *pic2Layout = new QVBoxLayout();
    pic2Layout->addWidget(new PicWidget());
    pic2Layout->addWidget(pic2text);
    group2Layout->addLayout(pic2Layout);
    group2Layout->addStretch(1);

    layout->addStretch(1);
}

void PreviewWidget::setupTab4()
{
    QVBoxLayout *scrollContainer = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *mainWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    mainWidget->setLayout(layout);
    mainWidget->setMinimumSize(QSize(420, 500));
    scrollArea->setWidget(mainWidget);
    scrollContainer->addWidget(scrollArea);
    tab4->setLayout(scrollContainer);

    QGroupBox *group1 = new QGroupBox(tr("QHboxLayout"));
    QHBoxLayout *hbox = new QHBoxLayout();
    for(int i=0; i<=5; i++) {
        hbox->addWidget(new QPushButton(QString(tr("Button") + QString::number(i))));
    }
    group1->setLayout(hbox);
    layout->addWidget(group1);

    QGroupBox *group2 = new QGroupBox(tr("QGridLayout"));
    group2->setCheckable(true);
    QGridLayout *gbox = new QGridLayout();
    gbox->addWidget(new QLabel(tr("First line:")), 0, 0);
    gbox->addWidget(new QLabel(tr("Second line:")), 1, 0);
    gbox->addWidget(new QLabel(tr("Third line:")), 2, 0);
    gbox->addWidget(new QLineEdit(), 0, 1);
    gbox->addWidget(new QLineEdit("0"), 1, 1);
    QLineEdit *inputText = new QLineEdit();
    inputText->setPlaceholderText(tr("please input"));
    gbox->addWidget(inputText, 2, 1);
    QTextEdit *text = new QTextEdit(tr("This is a textedit, span 3 rows and 2 columns."));
    gbox->addWidget(text, 0, 2, 3, 2);
    group2->setLayout(gbox);
    layout->addWidget(group2);

    QGroupBox *group3 = new QGroupBox(tr("QFormLayout"));
    group3->setCheckable(true);
    QFormLayout *fbox = new QFormLayout();

    fbox->addRow(tr("please input data"), new QLineEdit());
    fbox->addRow(new QLabel(tr("please select data")), new QSpinBox());
    QComboBox *box = new QComboBox();
    box->addItem("Item1");
    box->addItem("Item2");
    box->addItem("Item3");
    fbox->addRow(tr("Please select item"), box);
    group3->setLayout(fbox);
    layout->addWidget(group3);

    QGroupBox *group4 = new QGroupBox("Splitter MDI Dock");
    group4->setCheckable(true);
    QHBoxLayout *hbox2 = new QHBoxLayout();
    group4->setLayout(hbox2);
    layout->addWidget(group4);

    QSplitter *splitter1 = new QSplitter(Qt::Horizontal);
    QSplitter *splitter2 = new QSplitter(Qt::Vertical);
    splitter1->resize(420, 350);
    splitter2->resize(350, 350);
    splitter2->setStretchFactor(0, 1);

    QMdiArea *mdi = new QMdiArea();
    mdi->addSubWindow(new QWidget());
    mdi->addSubWindow(new QWidget());
    mdi->cascadeSubWindows();
    QWidget *w1 = new QWidget();
    QWidget *w2 = new QWidget();
    QDockWidget *d1 = new QDockWidget("dock1", w1);
    QDockWidget *d2 = new QDockWidget("dock2", w1);
    d1->setAllowedAreas(Qt::LeftDockWidgetArea);
    d1->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetVerticalTitleBar);
    d2->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);
    QDockWidget *d3 = new QDockWidget("dock3", w2);
    d3->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::TopDockWidgetArea);
    w1->resize(120, 120);
    splitter2->addWidget(w1);
    splitter2->addWidget(w2);
    splitter1->addWidget(mdi);
    splitter1->addWidget(splitter2);
    hbox2->addWidget(splitter1);

    layout->addStretch(1);
}

void PreviewWidget::setupTab5()
{
    QVBoxLayout *scrollContainer = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *mainWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    mainWidget->setLayout(layout);
    mainWidget->setMinimumSize(QSize(420, 600));
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(mainWidget);
    scrollContainer->addWidget(scrollArea);
    tab5->setLayout(scrollContainer);

    QGroupBox *group1 = new QGroupBox(tr("QGroupBox"));
    QHBoxLayout *hbox1 = new QHBoxLayout();
    hbox1->addWidget(new QLabel(tr("this is a QGroupBox widget")));
    group1->setLayout(hbox1);
    layout->addWidget(group1);

    QGroupBox *group2 = new QGroupBox(tr("QGroupBox"));
    group2->setCheckable(true);
    QHBoxLayout *hbox2 = new QHBoxLayout();
    hbox2->addWidget(new QLabel(tr("this is a checkable QGroupBox widget")));
    group2->setLayout(hbox2);
    layout->addWidget(group2);

    QGroupBox *group3 = new QGroupBox(tr("StackLayout"));
    group3->setCheckable(true);
    QHBoxLayout *hbox3 = new QHBoxLayout();
    group3->setLayout(hbox3);
    QListWidget *listWidget = new QListWidget();
    QStackedWidget *stack = new QStackedWidget();
    hbox3->addWidget(listWidget);
    hbox3->addWidget(stack);
    connect(listWidget, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);
    listWidget->addItem("stack1");
    listWidget->addItem("stack2");
    listWidget->addItem("stack3");
    QGroupBox *s1 = new QGroupBox("stack1");
    QGroupBox *s2 = new QGroupBox("stack1");
    QGroupBox *s3 = new QGroupBox("stack1");
    QLabel *l1 = new QLabel("stack1");
    QLabel *l2 = new QLabel("stack1");
    QLabel *l3 = new QLabel("stack1");
    QLineEdit *t1 = new QLineEdit();
    QLineEdit *t2 = new QLineEdit();
    QLineEdit *t3 = new QLineEdit();
    QHBoxLayout *lay1 = new QHBoxLayout();
    QHBoxLayout *lay2 = new QHBoxLayout();
    QHBoxLayout *lay3 = new QHBoxLayout();
    lay1->addWidget(l1);
    lay2->addWidget(l2);
    lay3->addWidget(l3);
    lay1->addWidget(t1);
    lay2->addWidget(t2);
    lay3->addWidget(t3);
    s1->setLayout(lay1);
    s2->setLayout(lay2);
    s3->setLayout(lay3);
    stack->addWidget(s1);
    stack->addWidget(s2);
    stack->addWidget(s3);
    layout->addWidget(group3);

    QGroupBox *group4 = new QGroupBox("ToolBox");
    group4->setCheckable(true);
    QVBoxLayout *lay = new QVBoxLayout();
    group4->setLayout(lay);
    layout->addWidget(group4);

    QToolBox *tool1 = new QToolBox();
    QWidget *w1 = new QWidget();
    QWidget *w2 = new QWidget();
    QVBoxLayout *i1 = new QVBoxLayout();
    QVBoxLayout *i2 = new QVBoxLayout();
    w1->setLayout(i1);
    w2->setLayout(i2);
    i1->addWidget(new QLabel("aaaaa"));
    i1->addWidget(new QLabel("bbbbb"));
    i1->addWidget(new QLabel("ccccc"));
    i2->addWidget(new QLabel("aaaaa"));
    i2->addWidget(new QLabel("bbbbb"));
    i1->addStretch(1);
    tool1->addItem(w1, "Tab1");
    tool1->addItem(w2, "Tab2");
    tool1->addItem(new QWidget(), "tab3");
    lay->addWidget(tool1);

    QGroupBox *group5 = new QGroupBox("TabWidget");
    group5->setCheckable(true);
    QVBoxLayout *vlay = new QVBoxLayout();
    QHBoxLayout *hlay1 = new QHBoxLayout();
    QHBoxLayout *hlay2 = new QHBoxLayout();
    vlay->addLayout(hlay1);
    vlay->addLayout(hlay2);
    group5->setLayout(vlay);
    layout->addWidget(group5);

    QTabWidget *tw1 = new QTabWidget();
    tw1->addTab(new QWidget(), "tab1");
    tw1->addTab(new QWidget(), "tab2");
    tw1->setTabsClosable(true);
    tw1->setMinimumHeight(200);
    QTabWidget *tw2 = new QTabWidget();
    tw2->addTab(new QWidget(), "tab1");
    tw2->addTab(new QWidget(), "tab2");
    tw2->setTabPosition(QTabWidget::South);
    tw2->setTabShape(QTabWidget::Triangular);
    QTabWidget *tw3 = new QTabWidget();
    tw3->addTab(new QWidget(), "tab1");
    tw3->addTab(new QWidget(), "tab2");
    tw3->setTabPosition(QTabWidget::West);
    QTabWidget *tw4 = new QTabWidget();
    tw4->addTab(new QWidget(), "tab1");
    tw4->addTab(new QWidget(), "tab2");
    tw4->setTabPosition(QTabWidget::East);
    tw3->setMinimumHeight(300);
    hlay1->addWidget(tw1);
    hlay1->addWidget(tw2);
    hlay2->addWidget(tw3);
    hlay2->addWidget(tw4);

    //layout->addStretch(1);
}

void PreviewWidget::setupTab6()
{
    QHBoxLayout *container = new QHBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *w = new QWidget();
    w->setMinimumSize(QSize(400, 500));
    QVBoxLayout *layout = new QVBoxLayout();
    w->setLayout(layout);
    scrollArea->setWidget(w);
    container->addWidget(scrollArea);
    tab6->setLayout(container);

    // List
    QHBoxLayout *lay = new QHBoxLayout();
    layout->addLayout(lay);
    QListWidget *list1 = new QListWidget();
    list1->addItems(QStringList{"aaa", "bbb", "ccc"});
    QListWidget *list2 = new QListWidget();
    list2->addItem(new QListWidgetItem(QIcon(":res/img/Flag_blueHS.png"), "blue"));
    list2->addItem(new QListWidgetItem(QIcon(":res/img/Flag_redHS.png"), "red"));
    list2->addItem(new QListWidgetItem(QIcon(":res/img/Flag_greenHS.png"), "green"));
    list2->setViewMode(QListWidget::IconMode);
    lay->addWidget(list1);
    lay->addWidget(list2);

    // Table
    lay = new QHBoxLayout();
    layout->addLayout(lay);
    QTableWidget *t1 = new QTableWidget();
    t1->setRowCount(3);
    t1->setColumnCount(3);
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            t1->setItem(i, j, new QTableWidgetItem(QString::number((i+1)*(j+1))));
            t1->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    t1->setColumnWidth(0, 50);
    t1->setColumnWidth(1, 50);
    t1->setColumnWidth(2, 50);
    t1->setEditTriggers(QTableWidget::AllEditTriggers);
    QTableWidget *t2 = new QTableWidget();
    t2->setRowCount(3);
    t2->setColumnCount(3);
    t2->setHorizontalHeaderLabels(QStringList{"Name", "Gender", "Age"});
    t2->setVerticalHeaderLabels(QStringList{"1st", "2rd", "3th"});
    t2->setItem(0, 0, new QTableWidgetItem("july"));
    QComboBox *c = new QComboBox();
    c->addItems(QStringList{"Male", "Female"});
    t2->setCellWidget(0, 1, c);
    ((QComboBox*)t2->cellWidget(0,1))->setCurrentIndex(1);
    t2->setItem(0, 2, new QTableWidgetItem("10"));
    t2->setItem(1, 0, new QTableWidgetItem("john"));
    QComboBox *c2 = new QComboBox();
    c2->addItems(QStringList{"Male", "FeMale"});
    c2->setEditable(true);
    t2->setCellWidget(1, 1, c2);
    t2->setItem(1, 2, new QTableWidgetItem("11"));
    t2->resizeColumnsToContents();
    t2->setEditTriggers(QTableWidget::EditKeyPressed|QTableWidget::SelectedClicked|
                        QTableWidget::AnyKeyPressed|QTableWidget::DoubleClicked);
    lay->addWidget(t1);
    lay->addWidget(t2);

    // Tree
    lay = new QHBoxLayout();
    layout->addLayout(lay);
    QTreeWidget *tree1 = new QTreeWidget();
    tree1->setColumnCount(2);
    tree1->setHeaderLabels(QStringList{"Key", "Value"});
    QTreeWidgetItem *node1 = new QTreeWidgetItem();
    node1->setText(0, "root");
    node1->setText(1, "0");
    node1->setIcon(0, QIcon(":res/img/home.png"));
    tree1->addTopLevelItem(node1);
    QTreeWidgetItem *node11 = new QTreeWidgetItem();
    node11->setText(0, "child1");
    QIcon *icon = new QIcon(":res/img/book_angle.png");
    icon->addPixmap(QPixmap(":res/img/book_open.png"), QIcon::Normal, QIcon::On);
    node11->setIcon(0, *icon);
    QTreeWidgetItem *nodea = new QTreeWidgetItem();
    nodea->setText(0, "red");
    nodea->setBackground(1, QBrush(Qt::red));
    QTreeWidgetItem *nodeb = new QTreeWidgetItem();
    nodeb->setText(0, "gray");
    nodeb->setBackground(1, QBrush(Qt::gray));
    QTreeWidgetItem *nodec = new QTreeWidgetItem();
    nodec->setText(0, "green");
    nodec->setBackground(1, QBrush(Qt::green));
    node11->addChildren(QList<QTreeWidgetItem*>{nodea, nodeb, nodec});
    QTreeWidgetItem *node12 = new QTreeWidgetItem();
    node12->setText(0, "child2");
    node12->setText(1, "child2");
    QTreeWidgetItem *node13 = new QTreeWidgetItem();
    node13->setText(0, "child3");
    node13->setText(1, "child3");
    node12->setIcon(0, *icon);
    node13->setIcon(0, *icon);
    node1->addChild(node11);
    node1->addChild(node12);
    node1->addChild(node13);
    tree1->expand(tree1->model()->index(0, 0));
    tree1->expandItem(node11);
    QTreeView *tree2 = new QTreeView();
    QFileSystemModel *folder = new QFileSystemModel(this);
    folder->setRootPath(QDir::rootPath());
    tree2->setModel(folder);
    lay->addWidget(tree1);
    lay->addWidget(tree2);
}
