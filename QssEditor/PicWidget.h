#ifndef PICWIDGET_H
#define PICWIDGET_H

#include <QWidget>

class PicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PicWidget(QWidget *parent = nullptr);


protected:
    virtual void paintEvent(QPaintEvent *event) override;


signals:

public slots:

};

#endif // PICWIDGET_H
