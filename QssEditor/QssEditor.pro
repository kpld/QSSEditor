QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17

windows {
        # MinGW
        *-g++* {
                QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
        }
        # MSVC
        *-msvc* {
                QMAKE_CXXFLAGS += /utf-8
        }
}


DESTDIR = ../bin
OBJECTS_DIR = obj
# RCC_DIR = rcc
# MOC_DIR = moc
# UI_DIR  = ui

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../qscintilla/src #../qscintilla/include
LIBS += -L$$OUT_PWD/../bin -lqscintilla2_qt$${QT_MAJOR_VERSION}

CONFIG      += qscintilla2

DEFINES += QSCINTILLA_DLL

SOURCES += \
    CodeDialog.cpp \
    ColorPanelWidget.cpp \
    ConfDialog.cpp \
    DrawWidget.cpp \
    Editor.cpp \
    PaletteDialog.cpp \
    PicWidget.cpp \
    PreviewWidget.cpp \
    QsciLexerText.cpp \
    SearchDialog.cpp \
    flowlayout.cpp \
    main.cpp \
    MainWnd.cpp \
    QsciLexerQSS.cpp

HEADERS += \
    CodeDialog.h \
    ColorPanelWidget.h \
    ConfDialog.h \
    DrawWidget.h \
    Editor.h \
    MainWnd.h \
    PaletteDialog.h \
    PicWidget.h \
    PreviewWidget.h \
    QsciLexerQSS.h \
    QsciLexerText.h \
    SearchDialog.h \
    flowlayout.h

FORMS += \
    MainWnd.ui

TRANSLATIONS += \
    QssEditor_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
