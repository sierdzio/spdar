lessThan(QT_MAJOR_VERSION, 5): message("Spdr requires Qt 5.2 as a minimum")

BUILDDIR = $$PWD/build/$$TARGET
BINDIR = $$PWD/bin

contains(CONFIG, testcase) {
    DESTDIR = $${BUILDDIR}
} else {
    DESTDIR = $${BINDIR}
}

OBJECTS_DIR = $${BUILDDIR}
MOC_DIR = $${BUILDDIR}
RCC_DIR = $${BUILDDIR}
UI_DIR = $${BUILDDIR}
