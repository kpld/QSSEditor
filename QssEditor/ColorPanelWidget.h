#ifndef COLORPANELWIDGET_H
#define COLORPANELWIDGET_H

#include <QWidget>

class ColorPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPanelWidget(QWidget *parent = nullptr);

public:
    //virtual QSize sizeHint() const override;

signals:
};

#endif // COLORPANELWIDGET_H
