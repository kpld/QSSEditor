#include "MainWnd.h"
//#include "qscintilla.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //int c = test(1, 2);
    //qDebug("c=%d", c);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QssEditor_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWnd *w = new MainWnd;
    w->showMaximized();
    int ret = a.exec();

    delete w;

    return ret;
}
