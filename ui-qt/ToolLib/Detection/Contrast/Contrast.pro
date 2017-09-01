#-------------------------------------------------
#
# Project created by QtCreator 2017-06-24T16:22:56
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolDetectionContrast
TEMPLATE = lib
DEFINES += CONTRAST_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR=../../../bin

INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task

SOURCES += Contrast.cpp \
    ContrastWidget.cpp \
    ResolveRunData.cpp \
    FWContrastLabel.cpp

HEADERS += Contrast.h\
        contrast_global.h \
    ContrastWidget.h \
    ResolveRunData.h \
    FWContrastLabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    ContrastWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
