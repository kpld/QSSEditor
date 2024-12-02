#ifndef PALETTEDIALOG_H
#define PALETTEDIALOG_H

#include <QDialog>
#include <QMap>

class QTableWidget;
class CodeDialog;


class PaletteDialog : public QDialog
{
    Q_OBJECT

public:
    PaletteDialog(QWidget *parent = nullptr);
    ~PaletteDialog();

private:
    CodeDialog *codeDialog;
    QPalette palette;
    QMap<QString, int> tabRole;
    //QVector<QPair<QString,int>> tabRole;

    typedef struct ColorName {
        QString clr[3];

        ColorName() {
            clr[0] = "";
            clr[1] = "";
            clr[2] = "";
        }
        ColorName(QString s1, QString s2, QString s3) {
            clr[0] = s1;
            clr[1] = s2;
            clr[2] = s3;
        }
    } ColorName;
    QMap<QString, ColorName> oldclr;
    QMap<QString, ColorName> newclr;

private:
    QTableWidget *tblWgt;

public:
    void initUI();

signals:

public slots:
    void changeClr();
    void resetRow();

    void getCode();
    void apply();
    void cancel();
};

#endif // PALETTEDIALOG_H
