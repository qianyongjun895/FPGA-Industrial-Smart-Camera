#-------------------------------------------------
#
# Project created by QtCreator 2017-06-19T15:50:43
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolLogicDataJudge
TEMPLATE = lib

DEFINES += TOOLLOGICDATAJUDGE_LIBRARY

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

SOURCES += ToolLogicDataJudge.cpp \
    DataJudgeWidget.cpp \
    ResolveRunData.cpp \
    SelectDataDialog.cpp

HEADERS += ToolLogicDataJudge.h\
        toollogicdatajudge_global.h \
    DataJudgeWidget.h \
    ResolveRunData.h \
    SelectDataDialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    DataJudgeWidget.ui \
    SelectDataDialog.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
