#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T15:05:59
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolMonoArea
TEMPLATE = lib

DEFINES += TOOLMONOAREA_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR=../../../bin
INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += ToolMonoArea.cpp \
    MonoAreaWidget.cpp \
    FWMonoAreaLabel.cpp \
    ResolveRunData.cpp

HEADERS += ToolMonoArea.h\
        toolmonoarea_global.h \
    MonoAreaWidget.h \
    FWMonoAreaLabel.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    MonoAreaWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
