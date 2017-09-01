#-------------------------------------------------
#
# Project created by QtCreator 2017-07-19T16:14:44
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = QrCode
TEMPLATE = lib

DEFINES += QRCODE_LIBRARY
DESTDIR=../../../bin
SOURCES += QrCode.cpp \
    ToolQrCode.cpp \
    ResolveRunData.cpp \
    FWQRCodeLabel.cpp
INCLUDEPATH += ../../../../include  \
                ../../../../include/function \
                ../../../../include/function/sszn  \
                ../../../../include/function/third_party \
                ../../../../include/lfpga_include \
                ../../../../include/lzynq_include \
                ../../../../include/task
HEADERS += QrCode.h\
        qrcode_global.h \
    ToolQrCode.h \
    ResolveRunData.h \
    FWQRCodeLabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    ToolQrCode.ui
