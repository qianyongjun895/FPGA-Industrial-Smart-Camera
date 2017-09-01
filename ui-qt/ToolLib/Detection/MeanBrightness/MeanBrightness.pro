#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T19:54:31
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolDetectionMeanBrightness
TEMPLATE = lib

DEFINES += TOOLDETECTIONMEANBRIGHTNESS_LIBRARY
DESTDIR=../../../bin

SOURCES += MeanBrightness.cpp \
    MeanBrightnessWidget.cpp \
    ResolveRunData.cpp \
    FWMeanBrightnessLabel.cpp

INCLUDEPATH += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task

HEADERS += MeanBrightness.h\
        meanbrightness_global.h \
    MeanBrightnessWidget.h \
    ResolveRunData.h \
    FWMeanBrightnessLabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    MeanBrightnessWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
