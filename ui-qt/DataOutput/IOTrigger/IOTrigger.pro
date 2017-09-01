#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T16:46:13
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = IOTrigger
TEMPLATE = lib

DEFINES += IOTRIGGER_LIBRARY
DESTDIR=../../bin
SOURCES += IOTrigger.cpp \
    IOTriggerWidget.cpp \
    ListWidgetIOTriggerItem.cpp

INCLUDEPATH += ../../../include \
               ../../../include/task

HEADERS += IOTrigger.h\
        iotrigger_global.h \
    IOTriggerWidget.h \
    ListWidgetIOTriggerItem.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    IOTriggerWidget.ui \
    ListWidgetIOTriggerItem.ui
LIBS += -L../../../lib/sszn/ -lzynq

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
