#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T10:36:35
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolDetectionBlobCount
TEMPLATE = lib

DEFINES += TOOLDETECTIONBLOBCOUNT_LIBRARY
DESTDIR=../../../bin
SOURCES += BlobCount.cpp \
    BlobCountWidget.cpp \
    ResolveRunData.cpp \
    FWBlobsCountLabel.cpp
INCLUDEPATH += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task

HEADERS += BlobCount.h\
        blobcount_global.h \
    BlobCountWidget.h \
    ResolveRunData.h \
    FWBlobsCountLabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    BlobCountWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
