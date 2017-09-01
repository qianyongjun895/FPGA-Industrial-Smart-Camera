#-------------------------------------------------
#
# Project created by QtCreator 2017-06-12T16:55:21
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = Modbus
TEMPLATE = lib

DEFINES += MODBUS_LIBRARY
DESTDIR=../../bin
SOURCES += Modbus.cpp \
    ModbusWidget.cpp \
    RDSingleCoilDialog.cpp \
    ModbusDataListItem.cpp \
    WRMultiCoilDialog.cpp \
    MultiCoilItem.cpp \
    ReadRegDialog.cpp \
    MultiRegDialog.cpp \
    MultiRegItem.cpp \
    ModbusSelectDataDialog.cpp

INCLUDEPATH  += ../../../include \
                ../../../include/task \
                ../../../include/comm_include \

HEADERS += Modbus.h\
        modbus_global.h \
    ModbusWidget.h \
    RDSingleCoilDialog.h \
    ModbusDataListItem.h \
    WRMultiCoilDialog.h \
    MultiCoilItem.h \
    ReadRegDialog.h \
    MultiRegDialog.h \
    MultiRegItem.h \
    ModbusSelectDataDialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L../../../lib/sszn/communicate/ -lProtocolManage
LIBS += -L../../../lib/sszn/communicate/ -lmodbus
LIBS += -L../../../lib/sszn/communicate/ -lModbusComm
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/ -ltask
LIBS += -L../../../lib/sszn/ -llinkdata

FORMS += \
    ModbusWidget.ui \
    RDSingleCoilDialog.ui \
    ModbusDataListItem.ui \
    WRMultiCoilDialog.ui \
    MultiCoilItem.ui \
    ReadRegDialog.ui \
    MultiRegDialog.ui \
    MultiRegItem.ui \
    ModbusSelectDataDialog.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
