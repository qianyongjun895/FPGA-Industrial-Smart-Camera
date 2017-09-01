#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T16:47:23
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = EthernetPort
TEMPLATE = lib

DEFINES += ETHERNETPORT_LIBRARY
DESTDIR=../../bin
SOURCES += EthernetPort.cpp \
    EthernetPortWidget.cpp

INCLUDEPATH +=../../../include \
              ../../../include/comm_include

HEADERS += EthernetPort.h\
        ethernetport_global.h \
    EthernetPortWidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    EthernetPortWidget.ui

LIBS += -lxml2
LIBS += -llzma
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/communicate/ -lProtocolManage
LIBS += -L../../../lib/sszn/communicate/ -lTcp

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
