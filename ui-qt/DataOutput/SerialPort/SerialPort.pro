#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T16:46:46
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = SerialPort
TEMPLATE = lib

DEFINES += SERIALPORT_LIBRARY
DESTDIR=../../bin
SOURCES += SerialPort.cpp \
    SerialPortWidget.cpp

INCLUDEPATH +=../../../include \
              ../../../include/comm_include \

HEADERS += SerialPort.h\
        serialport_global.h \
    SerialPortWidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    SerialPortWidget.ui

LIBS += -lxml2
LIBS += -llzma
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/communicate -lUart
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
