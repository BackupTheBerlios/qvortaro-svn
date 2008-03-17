TEMPLATE = app
CONFIG += qt \
    release
TARGET = qvortaro
QT += core \
    gui \
    sql
HEADERS += src/configviewdgl.h \
    src/qvortaroueber.h \
    src/configdglview.h \
    src/configdglsearch.h \
    src/configdglklipper.h \
    src/configdgllexika.h \
    src/configdglfont.h \
    src/configdglvorlage.h \
    src/configdglallgemein.h \
    src/configdgl.h \
    src/config.h \
    src/eolistbrowser.h \
    src/eolineeditvalidator.h \
    src/eolineedit.h \
    src/searchlayout1.h \
    src/qvortaro.h
SOURCES += src/configviewdgl.cpp \
    src/qvortaroueber.cpp \
    src/configdglview.cpp \
    src/configdglsearch.cpp \
    src/configdglklipper.cpp \
    src/configdgllexika.cpp \
    src/configdglfont.cpp \
    src/configdglvorlage.cpp \
    src/configdglallgemein.cpp \
    src/configdgl.cpp \
    src/config.cpp \
    src/eolistbrowser.cpp \
    src/eolineeditvalidator.cpp \
    src/eolineedit.cpp \
    src/searchlayout1.cpp \
    src/qvortaro.cpp \
    src/main.cpp
FORMS += src/ui/configviewdgl.ui \
    src/ui/qvortaroueber.ui \
    src/ui/configdglview.ui \
    src/ui/configdglsearch.ui \
    src/ui/configdglklipper.ui \
    src/ui/configdgllexika.ui \
    src/ui/configdglfont.ui \
    src/ui/configdglallgemein.ui \
    src/ui/configdgl.ui \
    src/ui/eolistbrowser.ui \
    src/ui/searchlayout1.ui \
    src/ui/qvortaro.ui
RESOURCES += src/qvortaro.qrc
MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp
INCLUDEPATH += tmp/ \
    src/
