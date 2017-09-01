#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T16:27:01
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = ToolL2LAngle
TEMPLATE = lib

DEFINES += L2LANGLE_LIBRARY

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

SOURCES += L2LAngle.cpp \
    L2LAngleWidget.cpp \
    FWL2LAngleLabel.cpp \
    ResolveRunData.cpp

HEADERS += L2LAngle.h\
        l2langle_global.h \
    L2LAngleWidget.h \
    FWL2LAngleLabel.h \
    ResolveRunData.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    L2LAngleWidget.ui
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
