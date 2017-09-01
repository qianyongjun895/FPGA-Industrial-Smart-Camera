#-------------------------------------------------
#
# Project created by QtCreator 2017-07-08T16:45:42
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolCalculator
TEMPLATE = lib

DEFINES += CALCULATOR_LIBRARY
DESTDIR=../../../bin
INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/comm_include \
                ../../../../include/task
SOURCES += Calculator.cpp \
    CalcDataSelectDialog.cpp \
    CalcOperatorSelectDialog.cpp \
    CalcuatorData.cpp \
    SSTaskEditCalculator.cpp \
    ResolveRunData.cpp

HEADERS += Calculator.h\
        calculator_global.h \
    CalcDataSelectDialog.h \
    CalcOperatorSelectDialog.h \
    CalcuatorData.h \
    SSTaskEditCalculator.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable

FORMS += \
    CalcDataSelectDialog.ui \
    CalcOperatorSelectDialog.ui \
    SSTaskEditCalculator.ui

LIBS += -L../../../../lib/sszn/communicate/ -lProtocolManage
LIBS += -L../../../../lib/sszn/communicate/ -lmodbus
LIBS += -L../../../../lib/sszn/communicate/ -lModbusComm
