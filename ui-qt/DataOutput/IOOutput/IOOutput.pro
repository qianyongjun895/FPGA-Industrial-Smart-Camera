#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T16:45:10
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = IOOutput
TEMPLATE = lib

DEFINES += IOOUTPUT_LIBRARY
DESTDIR=../../bin
SOURCES += IOOutput.cpp \
    IOOutputWidget.cpp \
    IOPortSelectDialog.cpp \
    ListWidgetIOOutputItem.cpp

INCLUDEPATH += ../../../include \
               ../../../include/task

HEADERS += IOOutput.h\
        iooutput_global.h \
    IOOutputWidget.h \
    IOPortSelectDialog.h \
    ListWidgetIOOutputItem.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    IOOutputWidget.ui \
    IOPortSelectDialog.ui \
    ListWidgetIOOutputItem.ui

LIBS += -L../../../lib/sszn/ -lzynq

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
