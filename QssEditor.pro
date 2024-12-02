TEMPLATE = subdirs

SUBDIRS += \
    qscintilla \
    QssEditor

QssEditor.depends = qscintilla

#CONFIG += ordered
