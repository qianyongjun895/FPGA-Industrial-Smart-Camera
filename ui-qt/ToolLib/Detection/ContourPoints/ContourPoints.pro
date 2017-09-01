#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T16:38:25
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolDetectionContourPoints
TEMPLATE = lib

DEFINES += CONTOURPOINTS_LIBRARY
DESTDIR=../../../bin
INCLUDEPATH  += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task
SOURCES += ContourPoints.cpp \
    ContourPointsWidget.cpp \
    FWContourPointLabel.cpp \
    ResolveRunData.cpp

HEADERS += ContourPoints.h\
        contourpoints_global.h \
    ContourPointsWidget.h \
    FWContourPointLabel.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    ContourPointsWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
