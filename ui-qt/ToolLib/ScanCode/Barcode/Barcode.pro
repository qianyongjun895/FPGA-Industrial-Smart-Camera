#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T17:50:20
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = Barcode
TEMPLATE = lib

DEFINES += BARCODE_LIBRARY
DESTDIR=../../../bin
SOURCES += Barcode.cpp \
    BarcodeWidget.cpp \
    FWBarcodeLabel.cpp \
    ResolveRunData.cpp
INCLUDEPATH += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task
HEADERS += Barcode.h\
        barcode_global.h \
    BarcodeWidget.h \
    FWBarcodeLabel.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    BarcodeWidget.ui
