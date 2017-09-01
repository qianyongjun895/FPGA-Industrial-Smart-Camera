#-------------------------------------------------
#
# Project created by QtCreator 2017-06-19T08:55:34
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = MitFxPlc
TEMPLATE = lib

DEFINES += MITFXPLC_LIBRARY
DESTDIR=../../bin
SOURCES += MitFxPlc.cpp \
    MitFxPlcWidget.cpp \
    MitFxPlcListWidgetItem.cpp \
    WRMRegDialog.cpp \
    WRMRegItem.cpp \
    RDDRegDialog.cpp \
    WRDRegDialog.cpp \
    WRDRegItem.cpp \
    WRDRegSelectDataDialog.cpp

HEADERS += MitFxPlc.h\
        mitfxplc_global.h \
    MitFxPlcWidget.h \
    MitFxPlcListWidgetItem.h \
    WRMRegDialog.h \
    WRMRegItem.h \
    RDDRegDialog.h \
    WRDRegDialog.h \
    WRDRegItem.h \
    WRDRegSelectDataDialog.h

INCLUDEPATH  += ../../../include \
                ../../../include/task \
                ../../../include/comm_include \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L../../../lib/sszn/communicate/ -lMitFxComm
LIBS += -L../../../lib/sszn/ -ltaskparse
LIBS += -L../../../lib/sszn/ -ltask
LIBS += -L../../../lib/sszn/ -llinkdata

FORMS += \
    MitFxPlcWidget.ui \
    MitFxPlcListWidgetItem.ui \
    WRMRegDialog.ui \
    WRMRegItem.ui \
    RDDRegDialog.ui \
    WRDRegDialog.ui \
    WRDRegItem.ui \
    WRDRegSelectDataDialog.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
