#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T11:20:18
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = UserDefined
TEMPLATE = lib

DEFINES += USERDEFINED_LIBRARY
DESTDIR=../../bin
SOURCES += UserDefined.cpp \
    UserDefinedWidget.cpp \
    UserDefinedDataItem.cpp \
    UserDefineSelectDialog.cpp \
    CmdTriggerItem.cpp

INCLUDEPATH  += ../../../include \
                ../../../include/task \
                ../../../include/comm_include \

HEADERS += UserDefined.h\
        userdefined_global.h \
    UserDefinedWidget.h \
    UserDefinedDataItem.h \
    UserDefineSelectDialog.h \
    CmdTriggerItem.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


FORMS += \
    UserDefinedWidget.ui \
    UserDefinedDataItem.ui \
    UserDefineSelectDialog.ui \
    CmdTriggerItem.ui


LIBS += -L../../../lib/sszn/communicate/ -lUserDefinedComm
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/ -ltask
LIBS += -L../../../lib/sszn/ -llinkdata
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
