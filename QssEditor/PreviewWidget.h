#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QTabWidget>
#include <QWidget>

class PreviewWidget : public QTabWidget
{
    Q_OBJECT
public:
    PreviewWidget(QWidget *parent = nullptr);

private:
    QWidget* tab1;
    QWidget* tab2;
    QWidget* tab3;
    QWidget* tab4;
    QWidget* tab5;
    QWidget* tab6;

private:
    void setupTab1();
    void setupTab2();
    void setupTab3();
    void setupTab4();
    void setupTab5();
    void setupTab6();

signals:

public slots:

};

#endif // PREVIEWWIDGET_H
