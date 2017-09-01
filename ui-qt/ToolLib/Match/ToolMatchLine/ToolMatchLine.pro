#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T18:56:00
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolMatchLine
TEMPLATE = lib

DEFINES += TOOLMATCHLINE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR=../../../bin
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task

SOURCES += ToolMatchLine.cpp \
    LineWidget.cpp \
    FWMatchLineLabel.cpp \
    ResolveRunData.cpp \
    LibLineInterface.cpp

HEADERS += ToolMatchLine.h\
        toolmatchline_global.h \
    LineWidget.h \
    FWMatchLineLabel.h \
    ResolveRunData.h \
    LibLineInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    LineWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
