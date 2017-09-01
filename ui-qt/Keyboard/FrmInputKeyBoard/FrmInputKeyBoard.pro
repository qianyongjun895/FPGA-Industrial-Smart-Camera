#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T09:02:10
#
#-------------------------------------------------

QT       += widgets sql

QT       -= gui

TARGET = FrmInputKeyBoard
TEMPLATE = lib

DEFINES += FRMINPUTKEYBOARD_LIBRARY
DESTDIR=../../bin
SOURCES += FrmInputKeyBoard.cpp \
    frminput.cpp \
    KeyboardDlg.cpp \
    NumKeyBoard.cpp

HEADERS += FrmInputKeyBoard.h\
        frminputkeyboard_global.h \
    frminput.h \
    KeyboardDlg.h \
    NumKeyBoard.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    frminput.ui \
    KeyboardDlg.ui \
    NumKeyBoard.ui

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
