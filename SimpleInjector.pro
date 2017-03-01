#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T00:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleInjector
TEMPLATE = app

#-------------------------------------------------

INCLUDEPATH += \
    src \
    src/gui

SOURCES += \
    src/main.cpp \
    src/gui/MainWindow.cpp \
    src/gui/InjectWidget.cpp \
    src/gui/LazyLoadedComboBox.cpp \
    src/core.cpp

HEADERS  += \
    src/gui/MainWindow.h \
    src/gui/InjectWidget.h \
    src/gui/LazyLoadedComboBox.h \
    src/core.h

FORMS    += \
    src/forms/MainWindow.ui \
    src/forms/InjectWidget.ui

RC_FILE = src/resources/si.rc

#-------------------------------------------------

CONFIG(debug, debug|release) {
    BIN_DIR_SUFFIX = -Debug
} else {
    BIN_DIR_SUFFIX =
}

DESTDIR = ../../bin/x64$${BIN_DIR_SUFFIX}

LIBS += -ladvapi32
