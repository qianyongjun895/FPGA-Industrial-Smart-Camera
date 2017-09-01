#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T08:36:18
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = UdpComm
TEMPLATE = lib

DEFINES += UDPCOMM_LIBRARY
DESTDIR=../../bin
SOURCES += UdpComm.cpp \
    UdpCommWidget.cpp

INCLUDEPATH +=../../../include \
              ../../../include/comm_include

HEADERS += UdpComm.h\
        udpcomm_global.h \
    UdpCommWidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    UdpCommWidget.ui

LIBS += -lxml2
LIBS += -llzma
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/communicate/ -lProtocolManage
LIBS += -L../../../lib/sszn/communicate/ -lUdp
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
