# The project file for the QScintilla library.
#
# Copyright (c) 2020 Riverbank Computing Limited <info@riverbankcomputing.com>
# 
# This file is part of QScintilla.
# 
# This file may be used under the terms of the GNU General Public License
# version 3.0 as published by the Free Software Foundation and appearing in
# the file LICENSE included in the packaging of this file.  Please review the
# following information to ensure the GNU General Public License version 3.0
# requirements will be met: http://www.gnu.org/copyleft/gpl.html.
# 
# If you do not wish to use this file under the terms of the GPL version 3.0
# then you may purchase a commercial license.  For more information contact
# info@riverbankcomputing.com.
# 
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

# use qscintilla 2.14.1 defined in src/Qsci/qsciglobal.h

!win32:VERSION = 15.2.1

TEMPLATE = lib
CONFIG += qt warn_off thread exceptions hide_symbols

DESTDIR = ../bin
OBJECTS_DIR = obj

CONFIG(debug, debug|release) {
    mac: {
        TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}_debug
    } else {
        win32: {
            TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}
        } else {
            TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}
        }
    }
} else {
    TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}
}

macx:!CONFIG(staticlib) {
    QMAKE_POST_LINK += install_name_tool -id @rpath/$(TARGET1) $(TARGET)
}

INCLUDEPATH += . scintilla/include scintilla/lexlib scintilla/src src

!CONFIG(staticlib) {
    DEFINES += QSCINTILLA_MAKE_DLL

    # Comment this in to build a dynamic library supporting multiple
    # architectures on macOS.
    #QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64
}
DEFINES += SCINTILLA_QT SCI_LEXER INCLUDE_DEPRECATED_FEATURES

QT += widgets
!ios:QT += printsupport
macx:lessThan(QT_MAJOR_VERSION, 6) {
    QT += macextras
}

# Work around QTBUG-39300.
CONFIG -= android_install

# For old versions of GCC.
unix:!macx {
    CONFIG += c++11
}

# Comment this in if you want the internal Scintilla classes to be placed in a
# Scintilla namespace rather than pollute the global namespace.
#DEFINES += SCI_NAMESPACE

target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target

header.path = $$[QT_INSTALL_HEADERS]
header.files = Qsci
INSTALLS += header

trans.path = $$[QT_INSTALL_TRANSLATIONS]
trans.files = qscintilla_*.qm
INSTALLS += trans

qsci.path = $$[QT_INSTALL_DATA]
qsci.files = qsci
INSTALLS += qsci

features.path = $$[QT_HOST_DATA]/mkspecs/features
CONFIG(staticlib) {
    features.files = $$PWD/src/features_staticlib/qscintilla2.prf
} else {
    features.files = $$PWD/src/features/qscintilla2.prf
}
INSTALLS += features

HEADERS = \
    ./src/Qsci/qsciglobal.h \
    ./src/Qsci/qsciscintilla.h \
    ./src/Qsci/qsciscintillabase.h \
    ./src/Qsci/qsciabstractapis.h \
    ./src/Qsci/qsciapis.h \
    ./src/Qsci/qscicommand.h \
    ./src/Qsci/qscicommandset.h \
    ./src/Qsci/qscidocument.h \
    ./src/Qsci/qscilexer.h \
    ./src/Qsci/qscilexerasm.h \
    ./src/Qsci/qscilexeravs.h \
    ./src/Qsci/qscilexerbash.h \
    ./src/Qsci/qscilexerbatch.h \
    ./src/Qsci/qscilexercmake.h \
    ./src/Qsci/qscilexercoffeescript.h \
    ./src/Qsci/qscilexercpp.h \
    ./src/Qsci/qscilexercsharp.h \
    ./src/Qsci/qscilexercss.h \
    ./src/Qsci/qscilexercustom.h \
    ./src/Qsci/qscilexerd.h \
    ./src/Qsci/qscilexerdiff.h \
    ./src/Qsci/qscilexeredifact.h \
    ./src/Qsci/qscilexerfortran.h \
    ./src/Qsci/qscilexerfortran77.h \
    ./src/Qsci/qscilexerhex.h \
    ./src/Qsci/qscilexerhtml.h \
    ./src/Qsci/qscilexeridl.h \
    ./src/Qsci/qscilexerintelhex.h \
    ./src/Qsci/qscilexerjava.h \
    ./src/Qsci/qscilexerjavascript.h \
    ./src/Qsci/qscilexerjson.h \
    ./src/Qsci/qscilexerlua.h \
    ./src/Qsci/qscilexermakefile.h \
    ./src/Qsci/qscilexermarkdown.h \
    ./src/Qsci/qscilexermasm.h \
    ./src/Qsci/qscilexermatlab.h \
    ./src/Qsci/qscilexernasm.h \
    ./src/Qsci/qscilexeroctave.h \
    ./src/Qsci/qscilexerpascal.h \
    ./src/Qsci/qscilexerperl.h \
    ./src/Qsci/qscilexerpostscript.h \
    ./src/Qsci/qscilexerpo.h \
    ./src/Qsci/qscilexerpov.h \
    ./src/Qsci/qscilexerproperties.h \
    ./src/Qsci/qscilexerpython.h \
    ./src/Qsci/qscilexerruby.h \
    ./src/Qsci/qscilexerspice.h \
    ./src/Qsci/qscilexersql.h \
    ./src/Qsci/qscilexersrec.h \
    ./src/Qsci/qscilexertcl.h \
    ./src/Qsci/qscilexertekhex.h \
    ./src/Qsci/qscilexertex.h \
    ./src/Qsci/qscilexerverilog.h \
    ./src/Qsci/qscilexervhdl.h \
    ./src/Qsci/qscilexerxml.h \
    ./src/Qsci/qscilexeryaml.h \
    ./src/Qsci/qscimacro.h \
    ./src/Qsci/qscistyle.h \
    ./src/Qsci/qscistyledtext.h \
    ./src/ListBoxQt.h \
    ./src/SciAccessibility.h \
    ./src/SciClasses.h \
    ./src/ScintillaQt.h \
    ./scintilla/include/ILexer.h \
    ./scintilla/include/ILoader.h \
    ./scintilla/include/Platform.h \
    ./scintilla/include/Sci_Position.h \
    ./scintilla/include/SciLexer.h \
    ./scintilla/include/Scintilla.h \
    ./scintilla/include/ScintillaWidget.h \
    ./scintilla/lexlib/Accessor.h \
    ./scintilla/lexlib/CharacterCategory.h \
    ./scintilla/lexlib/CharacterSet.h \
    ./scintilla/lexlib/DefaultLexer.h \
    ./scintilla/lexlib/LexAccessor.h \
    ./scintilla/lexlib/LexerBase.h \
    ./scintilla/lexlib/LexerModule.h \
    ./scintilla/lexlib/LexerNoExceptions.h \
    ./scintilla/lexlib/LexerSimple.h \
    ./scintilla/lexlib/OptionSet.h \
    ./scintilla/lexlib/PropSetSimple.h \
    ./scintilla/lexlib/SparseState.h \
    ./scintilla/lexlib/StringCopy.h \
    ./scintilla/lexlib/StyleContext.h \
    ./scintilla/lexlib/SubStyles.h \
    ./scintilla/lexlib/WordList.h \
    ./scintilla/src/AutoComplete.h \
    ./scintilla/src/CallTip.h \
    ./scintilla/src/CaseConvert.h \
    ./scintilla/src/CaseFolder.h \
    ./scintilla/src/Catalogue.h \
    ./scintilla/src/CellBuffer.h \
    ./scintilla/src/CharClassify.h \
    ./scintilla/src/ContractionState.h \
    ./scintilla/src/DBCS.h \
    ./scintilla/src/Decoration.h \
    ./scintilla/src/Document.h \
    ./scintilla/src/EditModel.h \
    ./scintilla/src/Editor.h \
    ./scintilla/src/EditView.h \
    ./scintilla/src/ElapsedPeriod.h \
    ./scintilla/src/ExternalLexer.h \
    ./scintilla/src/FontQuality.h \
    ./scintilla/src/Indicator.h \
    ./scintilla/src/IntegerRectangle.h \
    ./scintilla/src/KeyMap.h \
    ./scintilla/src/LineMarker.h \
    ./scintilla/src/MarginView.h \
    ./scintilla/src/Partitioning.h \
    ./scintilla/src/PerLine.h \
    ./scintilla/src/Position.h \
    ./scintilla/src/PositionCache.h \
    ./scintilla/src/RESearch.h \
    ./scintilla/src/RunStyles.h \
    ./scintilla/src/ScintillaBase.h \
    ./scintilla/src/Selection.h \
    ./scintilla/src/SparseVector.h \
    ./scintilla/src/SplitVector.h \
    ./scintilla/src/Style.h \
    ./scintilla/src/UniConversion.h \
    ./scintilla/src/UniqueString.h \
    ./scintilla/src/ViewStyle.h \
    ./scintilla/src/XPM.h

!ios:HEADERS += ./src/Qsci/qsciprinter.h

SOURCES = \
    src/qsciscintilla.cpp \
    src/qsciscintillabase.cpp \
    src/qsciabstractapis.cpp \
    src/qsciapis.cpp \
    src/qscicommand.cpp \
    src/qscicommandset.cpp \
    src/qscidocument.cpp \
    src/qscilexer.cpp \
    src/qscilexerasm.cpp \
    src/qscilexeravs.cpp \
    src/qscilexerbash.cpp \
    src/qscilexerbatch.cpp \
    src/qscilexercmake.cpp \
    src/qscilexercoffeescript.cpp \
    src/qscilexercpp.cpp \
    src/qscilexercsharp.cpp \
    src/qscilexercss.cpp \
    src/qscilexercustom.cpp \
    src/qscilexerd.cpp \
    src/qscilexerdiff.cpp \
    src/qscilexeredifact.cpp \
    src/qscilexerfortran.cpp \
    src/qscilexerfortran77.cpp \
    src/qscilexerhex.cpp \
    src/qscilexerhtml.cpp \
    src/qscilexeridl.cpp \
    src/qscilexerintelhex.cpp \
    src/qscilexerjava.cpp \
    src/qscilexerjavascript.cpp \
    src/qscilexerjson.cpp \
    src/qscilexerlua.cpp \
    src/qscilexermakefile.cpp \
    src/qscilexermarkdown.cpp \
    src/qscilexermasm.cpp \
    src/qscilexermatlab.cpp \
    src/qscilexernasm.cpp \
    src/qscilexeroctave.cpp \
    src/qscilexerpascal.cpp \
    src/qscilexerperl.cpp \
    src/qscilexerpostscript.cpp \
    src/qscilexerpo.cpp \
    src/qscilexerpov.cpp \
    src/qscilexerproperties.cpp \
    src/qscilexerpython.cpp \
    src/qscilexerruby.cpp \
    src/qscilexerspice.cpp \
    src/qscilexersql.cpp \
    src/qscilexersrec.cpp \
    src/qscilexertcl.cpp \
    src/qscilexertekhex.cpp \
    src/qscilexertex.cpp \
    src/qscilexerverilog.cpp \
    src/qscilexervhdl.cpp \
    src/qscilexerxml.cpp \
    src/qscilexeryaml.cpp \
    src/qscimacro.cpp \
    src/qscistyle.cpp \
    src/qscistyledtext.cpp \
    src/InputMethod.cpp \
    src/ListBoxQt.cpp \
    src/MacPasteboardMime.cpp \
    src/PlatQt.cpp \
    src/SciAccessibility.cpp \
    src/SciClasses.cpp \
    src/ScintillaQt.cpp \
    ./scintilla/lexers/LexA68k.cpp \
    ./scintilla/lexers/LexAPDL.cpp \
    ./scintilla/lexers/LexASY.cpp \
    ./scintilla/lexers/LexAU3.cpp \
    ./scintilla/lexers/LexAVE.cpp \
    ./scintilla/lexers/LexAVS.cpp \
    ./scintilla/lexers/LexAbaqus.cpp \
    ./scintilla/lexers/LexAda.cpp \
    ./scintilla/lexers/LexAsm.cpp \
    ./scintilla/lexers/LexAsn1.cpp \
    ./scintilla/lexers/LexBaan.cpp \
    ./scintilla/lexers/LexBash.cpp \
    ./scintilla/lexers/LexBasic.cpp \
    ./scintilla/lexers/LexBatch.cpp \
    ./scintilla/lexers/LexBibTeX.cpp \
    ./scintilla/lexers/LexBullant.cpp \
    ./scintilla/lexers/LexCLW.cpp \
    ./scintilla/lexers/LexCOBOL.cpp \
    ./scintilla/lexers/LexCPP.cpp \
    ./scintilla/lexers/LexCSS.cpp \
    ./scintilla/lexers/LexCaml.cpp \
    ./scintilla/lexers/LexCmake.cpp \
    ./scintilla/lexers/LexCoffeeScript.cpp \
    ./scintilla/lexers/LexConf.cpp \
    ./scintilla/lexers/LexCrontab.cpp \
    ./scintilla/lexers/LexCsound.cpp \
    ./scintilla/lexers/LexD.cpp \
    ./scintilla/lexers/LexDMAP.cpp \
    ./scintilla/lexers/LexDMIS.cpp \
    ./scintilla/lexers/LexDiff.cpp \
    ./scintilla/lexers/LexECL.cpp \
    ./scintilla/lexers/LexEDIFACT.cpp \
    ./scintilla/lexers/LexEScript.cpp \
    ./scintilla/lexers/LexEiffel.cpp \
    ./scintilla/lexers/LexErlang.cpp \
    ./scintilla/lexers/LexErrorList.cpp \
    ./scintilla/lexers/LexFlagship.cpp \
    ./scintilla/lexers/LexForth.cpp \
    ./scintilla/lexers/LexFortran.cpp \
    ./scintilla/lexers/LexGAP.cpp \
    ./scintilla/lexers/LexGui4Cli.cpp \
    ./scintilla/lexers/LexHTML.cpp \
    ./scintilla/lexers/LexHaskell.cpp \
    ./scintilla/lexers/LexHex.cpp \
    ./scintilla/lexers/LexIndent.cpp \
    ./scintilla/lexers/LexInno.cpp \
    ./scintilla/lexers/LexJSON.cpp \
    ./scintilla/lexers/LexKVIrc.cpp \
    ./scintilla/lexers/LexKix.cpp \
    ./scintilla/lexers/LexLaTeX.cpp \
    ./scintilla/lexers/LexLisp.cpp \
    ./scintilla/lexers/LexLout.cpp \
    ./scintilla/lexers/LexLua.cpp \
    ./scintilla/lexers/LexMMIXAL.cpp \
    ./scintilla/lexers/LexMPT.cpp \
    ./scintilla/lexers/LexMSSQL.cpp \
    ./scintilla/lexers/LexMagik.cpp \
    ./scintilla/lexers/LexMake.cpp \
    ./scintilla/lexers/LexMarkdown.cpp \
    ./scintilla/lexers/LexMatlab.cpp \
    ./scintilla/lexers/LexMaxima.cpp \
    ./scintilla/lexers/LexMetapost.cpp \
    ./scintilla/lexers/LexModula.cpp \
    ./scintilla/lexers/LexMySQL.cpp \
    ./scintilla/lexers/LexNimrod.cpp \
    ./scintilla/lexers/LexNsis.cpp \
    ./scintilla/lexers/LexNull.cpp \
    ./scintilla/lexers/LexOScript.cpp \
    ./scintilla/lexers/LexOpal.cpp \
    ./scintilla/lexers/LexPB.cpp \
    ./scintilla/lexers/LexPLM.cpp \
    ./scintilla/lexers/LexPO.cpp \
    ./scintilla/lexers/LexPOV.cpp \
    ./scintilla/lexers/LexPS.cpp \
    ./scintilla/lexers/LexPascal.cpp \
    ./scintilla/lexers/LexPerl.cpp \
    ./scintilla/lexers/LexPowerPro.cpp \
    ./scintilla/lexers/LexPowerShell.cpp \
    ./scintilla/lexers/LexProgress.cpp \
    ./scintilla/lexers/LexProps.cpp \
    ./scintilla/lexers/LexPython.cpp \
    ./scintilla/lexers/LexR.cpp \
    ./scintilla/lexers/LexRebol.cpp \
    ./scintilla/lexers/LexRegistry.cpp \
    ./scintilla/lexers/LexRuby.cpp \
    ./scintilla/lexers/LexRust.cpp \
    ./scintilla/lexers/LexSAS.cpp \
    ./scintilla/lexers/LexSML.cpp \
    ./scintilla/lexers/LexSQL.cpp \
    ./scintilla/lexers/LexSTTXT.cpp \
    ./scintilla/lexers/LexScriptol.cpp \
    ./scintilla/lexers/LexSmalltalk.cpp \
    ./scintilla/lexers/LexSorcus.cpp \
    ./scintilla/lexers/LexSpecman.cpp \
    ./scintilla/lexers/LexSpice.cpp \
    ./scintilla/lexers/LexStata.cpp \
    ./scintilla/lexers/LexTACL.cpp \
    ./scintilla/lexers/LexTADS3.cpp \
    ./scintilla/lexers/LexTAL.cpp \
    ./scintilla/lexers/LexTCL.cpp \
    ./scintilla/lexers/LexTCMD.cpp \
    ./scintilla/lexers/LexTeX.cpp \
    ./scintilla/lexers/LexTxt2tags.cpp \
    ./scintilla/lexers/LexVB.cpp \
    ./scintilla/lexers/LexVHDL.cpp \
    ./scintilla/lexers/LexVerilog.cpp \
    ./scintilla/lexers/LexVisualProlog.cpp \
    ./scintilla/lexers/LexYAML.cpp \
    ./scintilla/lexlib/Accessor.cpp \
    ./scintilla/lexlib/CharacterCategory.cpp \
    ./scintilla/lexlib/CharacterSet.cpp \
    ./scintilla/lexlib/DefaultLexer.cpp \
    ./scintilla/lexlib/LexerBase.cpp \
    ./scintilla/lexlib/LexerModule.cpp \
    ./scintilla/lexlib/LexerNoExceptions.cpp \
    ./scintilla/lexlib/LexerSimple.cpp \
    ./scintilla/lexlib/PropSetSimple.cpp \
    ./scintilla/lexlib/StyleContext.cpp \
    ./scintilla/lexlib/WordList.cpp \
    ./scintilla/src/AutoComplete.cpp \
    ./scintilla/src/CallTip.cpp \
    ./scintilla/src/CaseConvert.cpp \
    ./scintilla/src/CaseFolder.cpp \
    ./scintilla/src/Catalogue.cpp \
    ./scintilla/src/CellBuffer.cpp \
    ./scintilla/src/CharClassify.cpp \
    ./scintilla/src/ContractionState.cpp \
    ./scintilla/src/DBCS.cpp \
    ./scintilla/src/Decoration.cpp \
    ./scintilla/src/Document.cpp \
    ./scintilla/src/EditModel.cpp \
    ./scintilla/src/Editor.cpp \
    ./scintilla/src/EditView.cpp \
    ./scintilla/src/ExternalLexer.cpp \
    ./scintilla/src/Indicator.cpp \
    ./scintilla/src/KeyMap.cpp \
    ./scintilla/src/LineMarker.cpp \
    ./scintilla/src/MarginView.cpp \
    ./scintilla/src/PerLine.cpp \
    ./scintilla/src/PositionCache.cpp \
    ./scintilla/src/RESearch.cpp \
    ./scintilla/src/RunStyles.cpp \
    ./scintilla/src/ScintillaBase.cpp \
    ./scintilla/src/Selection.cpp \
    ./scintilla/src/Style.cpp \
    ./scintilla/src/UniConversion.cpp \
    ./scintilla/src/ViewStyle.cpp \
    ./scintilla/src/XPM.cpp

!ios:SOURCES += ./src/qsciprinter.cpp

TRANSLATIONS = \
    ./src/qscintilla_cs.ts \
    ./src/qscintilla_de.ts \
    ./src/qscintilla_es.ts \
    ./src/qscintilla_fr.ts \
    ./src/qscintilla_pt_br.ts
