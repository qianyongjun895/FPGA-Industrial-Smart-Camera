#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T17:10:26
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = HansRobothProtocol
TEMPLATE = lib

DEFINES += HANSROBOTHPROTOCOL_LIBRARY
DESTDIR=../../bin
SOURCES += HansRobothProtocol.cpp \
    HansRobothWidget.cpp

INCLUDEPATH  += ../../../include \
                ../../../include/task \
                ../../../include/comm_include \

HEADERS += HansRobothProtocol.h\
        hansrobothprotocol_global.h \
    HansRobothWidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L../../../lib/sszn/communicate/ -lProtocolManage
LIBS += -L../../../lib/sszn/communicate/ -lHansRobotComm
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/ -ltask
LIBS += -L../../../lib/sszn/ -llinkdata

FORMS += \
    HansRobothWidget.ui
