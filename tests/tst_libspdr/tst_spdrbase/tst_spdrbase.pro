QT = core testlib

CONFIG += testcase

include(../../../libraryIncludes.pri)
include(../../../definitions.pri)

SOURCES += tst_spdrbase.cpp

mac {
    QMAKE_POST_LINK = ln -f $${BUILDDIR}/../spdr/libspdr.0.dylib $${BUILDDIR}/$${TARGET}.app/Contents/MacOS/
}
