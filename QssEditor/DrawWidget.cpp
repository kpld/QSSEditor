#include "DrawWidget.h"
#include <QPainter>


DrawWidget::DrawWidget(QWidget *parent)
    : QWidget{parent}
{
    setMinimumHeight(170);
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter *p = new QPainter();
    p->begin(this);

    QPen *pen = new QPen(Qt::black, 2, Qt::SolidLine);
    p->setPen(*pen);
    p->drawLine(20, 15, 150, 15);
    pen->setStyle(Qt::DashLine);
    p->setPen(*pen);
    p->drawLine(20, 35, 150, 35);
    pen->setStyle(Qt::DotLine);
    p->setPen(*pen);
    p->drawLine(20, 55, 150, 55);
    pen->setStyle(Qt::DashDotLine);
    p->setPen(*pen);
    p->drawLine(20, 75, 150, 75);
    pen->setStyle(Qt::DashDotDotLine);
    p->setPen(*pen);
    p->drawLine(20, 95, 150, 95);
    pen->setStyle(Qt::CustomDashLine);
    pen->setDashPattern(QVector<qreal>{1, 4, 5, 4});
    p->setPen(*pen);
    p->drawLine(20, 115, 150, 115);

    pen->setWidth(1);
    pen->setStyle(Qt::SolidLine);
    p->setPen(*pen);
    QBrush *brush = new QBrush(Qt::SolidPattern);
    p->setBrush(*brush);
    p->drawRect(180, 10, 40, 30);
    brush->setStyle(Qt::Dense5Pattern);
    p->setBrush(*brush);
    p->drawRect(240, 10, 40, 30);
    brush->setStyle(Qt::Dense7Pattern);
    p->setBrush(*brush);
    p->drawRect(300, 10, 40, 30);

    brush->setColor(Qt::green);
    brush->setStyle(Qt::HorPattern);
    p->setBrush(*brush);
    p->drawRect(180, 50, 40, 30);
    brush->setStyle(Qt::VerPattern);
    p->setBrush(*brush);
    p->drawRect(240, 50, 40, 30);
    //brush->setStyle(Qt::Dense6Pattern);
    brush->setStyle(Qt::CrossPattern);
    p->setBrush(*brush);
    p->drawRect(300, 50, 40, 30);

    brush->setColor(Qt::blue);
    brush->setStyle(Qt::BDiagPattern);
    p->setBrush(*brush);
    p->drawRect(180, 90, 40, 30);
    brush->setStyle(Qt::FDiagPattern);
    p->setBrush(*brush);
    p->drawRect(240, 90, 40, 30);
    brush->setStyle(Qt::DiagCrossPattern);
    p->setBrush(*brush);
    p->drawRect(300, 90, 40, 30);

    QGradient *g = new QLinearGradient(180, 180, 220, 160);
    g->setColorAt(0, Qt::red);
    g->setColorAt(1, Qt::blue);
    QBrush *brush2 = new QBrush(*g);
    p->setBrush(*brush2);
    p->drawRect(180, 130, 40, 30);
    g = new QRadialGradient(260, 145, 20);
    g->setColorAt(0, Qt::red);
    g->setColorAt(0.5, Qt::yellow);
    g->setColorAt(1, Qt::blue);
    p->setBrush(*g);
    p->drawRect(240, 130, 40, 30);
    g = new QConicalGradient(320, 145, 0);
    g->setColorAt(0, Qt::red);
    g->setColorAt(0.4, Qt::yellow);
    g->setColorAt(0.8, Qt::blue);
    g->setColorAt(1, Qt::red);
    p->setBrush(*g);
    p->drawRect(300, 130, 40, 30);

    brush = new QBrush();
    brush->setTexture(QPixmap(":res/img/texture.jpg"));
    p->setBrush(*brush);
    pen->setColor(Qt::transparent);
    p->setPen(*pen);
    p->drawRect(15, 130, 135, 35);

    p->end();
}
