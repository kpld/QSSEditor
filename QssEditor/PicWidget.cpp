#include "PicWidget.h"
#include <QPainter>


PicWidget::PicWidget(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(QSize(100,100));
}

void PicWidget::paintEvent(QPaintEvent *event)
{
    QPainter *p = new QPainter();
    p->begin(this);
    QPixmap *img = new QPixmap(":res/img/cup.jpg");
    QRect rc(0, 0, img->width(), img->height());
    setFixedSize(img->size());
    p->drawPixmap(rc, *img, rc);
    p->end();
}
