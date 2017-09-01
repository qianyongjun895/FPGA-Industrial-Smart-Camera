#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T11:18:47
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolLineFlaw
TEMPLATE = lib

DEFINES += LINEFLAW_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR=../../../bin
INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task

SOURCES += LineFlaw.cpp \
    LineFlawWidget.cpp \
    FWLineFlawLabel.cpp \
    ResolveRunData.cpp

HEADERS += LineFlaw.h\
        lineflaw_global.h \
    LineFlawWidget.h \
    FWLineFlawLabel.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    LineFlawWidget.ui

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
