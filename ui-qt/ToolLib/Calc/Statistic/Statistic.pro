#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T16:26:40
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolStatistic
TEMPLATE = lib

DEFINES += STATISTIC_LIBRARY
DESTDIR=../../../bin
INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task
SOURCES += Statistic.cpp \
    ToolStatistic.cpp \
    ResolveRunData.cpp

HEADERS += Statistic.h\
        statistic_global.h \
    ToolStatistic.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    ToolStatistic.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
