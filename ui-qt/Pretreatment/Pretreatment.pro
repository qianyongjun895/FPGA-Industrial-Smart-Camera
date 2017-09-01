#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T14:29:43
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = Pretreatment
TEMPLATE = lib

DEFINES += PRETREATMENT_LIBRARY
DESTDIR=../bin
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH  +=../../include \
                             ../../include/function \
                             ../../include/function/sszn \
                             ../../include/function/third_party \
                             ../../include/lfpga_include \
                             ../../include/lzynq_include \
                             ../../include/task  \
                             ../ \
                             ColorSelect/Roi \
                             AreaSelect/Roi   \
                             LibInclued     \
                             PretreatMentListCollect

SOURCES += Pretreatment.cpp \
    PreMain.cpp \
    ImgpreprocessModule/ImagepreprocessDlg.cpp \
    PretreatMentListCollect/PretreatmentModuleItem.cpp \
    PretreatMentListCollect/PretreatmentSummaryDialog.cpp \
    ImgpreprocessModule/GaussDlg.cpp \
    ImgpreprocessModule/ContrastSwitchDlg.cpp \
    ImgpreprocessModule/ContrastStrengthenDlg.cpp \
    BinaryzationModule/BinaryzationDlg.cpp \
    BinaryzationModule/BinLimitDlg.cpp \
    BinaryzationModule/ErosionDilateDlg.cpp \
    SkeletonThreshold/SkeletonThresholdDlg.cpp \
    EdgeExtract/EdgeExtractDlg.cpp \
    AreaSelect/AreaSelectDialog.cpp \
    ColorSelect/AreaCenterColorExtractDeal.cpp \
    ColorSelect/ColorSelectDialog.cpp \
    AreaSelect/Roi/FWAreaSelect.cpp \
    AreaSelect/Roi/PolygonTool.cpp \
    AreaSelect/Roi/RectTool.cpp \
    AreaSelect/Roi/RingTool.cpp \
    ColorSelect/Roi/LabelHeightAdjust.cpp \
    ColorSelect/Roi/LabelHSIPicAdjust.cpp \
    ColorSelect/Roi/LabelRGBPicSelect.cpp \
    ImgpreprocessModule/Roi/CptPreLabel.cpp \
    ../Global/UtilitiesFun.cpp \
    ImgpreprocessModule/SharpnessDlg.cpp \
    ImgpreprocessModule/PeakFilterDlg.cpp \
    ImgpreprocessModule/Roi/ContrastStrengthenGrayLabel.cpp \
    ImgpreprocessModule/Roi/ContrastStrengthenAdjustLabel.cpp \
    BinaryzationModule/ErrosionRectDialog.cpp \
    BinaryzationModule/Roi/LabelErosionDilatePoints.cpp \
    LabelMain.cpp \
    ColorSelect/CGetImageThread.cpp \
    GrayHistogram/GrayHistogramDialog.cpp \
    GrayHistogram/Roi/LabelGrayHistogram.cpp \
    ImgpreprocessModule/DefectDialog.cpp \
    ImgpreprocessModule/ShadingDialog.cpp \
    Cpt/CptDlg.cpp \
    ImgpreprocessModule/BlurDialog.cpp

HEADERS += Pretreatment.h\
        pretreatment_global.h \
    PreMain.h \
    ImgpreprocessModule/ImagepreprocessDlg.h \
    PretreatMentListCollect/PretreatmentModuleItem.h \
    PretreatMentListCollect/PretreatmentSummaryDialog.h \
    ImgpreprocessModule/GaussDlg.h \
    ImgpreprocessModule/ContrastSwitchDlg.h \
    ImgpreprocessModule/ContrastStrengthenDlg.h \
    BinaryzationModule/BinaryzationDlg.h \
    BinaryzationModule/BinLimitDlg.h \
    BinaryzationModule/ErosionDilateDlg.h \
    SkeletonThreshold/SkeletonThresholdDlg.h \
    EdgeExtract/EdgeExtractDlg.h \
    AreaSelect/AreaSelectDialog.h \
    ColorSelect/AreaCenterColorExtractDeal.h \
    ColorSelect/ColorSelectDialog.h \
    AreaSelect/Roi/FWAreaSelect.h \
    AreaSelect/Roi/PolygonTool.h \
    AreaSelect/Roi/RectTool.h \
    AreaSelect/Roi/RingTool.h \
    PreBasicHead.h \
    ColorSelect/Roi/LabelHeightAdjust.h \
    ColorSelect/Roi/LabelHSIPicAdjust.h \
    ColorSelect/Roi/LabelRGBPicSelect.h \
    ImgpreprocessModule/Roi/CptPreLabel.h \
    ../Global/UtilitiesFun.h \
    ImgpreprocessModule/SharpnessDlg.h \
    ImgpreprocessModule/PeakFilterDlg.h \
    ImgpreprocessModule/Roi/ContrastStrengthenGrayLabel.h \
    ImgpreprocessModule/Roi/ContrastStrengthenAdjustLabel.h \
    BinaryzationModule/ErrosionRectDialog.h \
    BinaryzationModule/Roi/LabelErosionDilatePoints.h \
    LabelMain.h \
    ColorSelect/CGetImageThread.h \
    GrayHistogram/GrayHistogramDialog.h \
    GrayHistogram/Roi/LabelGrayHistogram.h \
    ImgpreprocessModule/DefectDialog.h \
    ImgpreprocessModule/ShadingDialog.h \
    Cpt/CptDlg.h \
    ImgpreprocessModule/BlurDialog.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    PreMain.ui \
    ImgpreprocessModule/ImagepreprocessDlg.ui \
    PretreatMentListCollect/PretreatmentModule.ui \
    PretreatMentListCollect/PretreatmentModuleItem.ui \
    PretreatMentListCollect/PretreatmentSummaryDialog.ui \
    ImgpreprocessModule/GaussDlg.ui \
    ImgpreprocessModule/ContrastSwitchDlg.ui \
    ImgpreprocessModule/ContrastStrengthenDlg.ui \
    BinaryzationModule/BinaryzationDlg.ui \
    BinaryzationModule/BinLimitDlg.ui \
    BinaryzationModule/ErosionDilateDlg.ui \
    SkeletonThreshold/SkeletonThresholdDlg.ui \
    EdgeExtract/EdgeExtractDlg.ui \
    AreaSelect/AreaSelectDialog.ui \
    ColorSelect/ColorSelectDialog.ui \
    ImgpreprocessModule/SharpnessDlg.ui \
    ImgpreprocessModule/PeakFilterDlg.ui \
    BinaryzationModule/ErrosionRectDialog.ui \
    GrayHistogram/GrayHistogramDialog.ui \
    ImgpreprocessModule/DefectDialog.ui \
    ImgpreprocessModule/ShadingDialog.ui \
    Cpt/CptDlg.ui \
    ImgpreprocessModule/BlurDialog.ui

LIBS += -L../../lib/sszn/ -lfpga
LIBS += -L../../lib/sszn/ -lzynq
LIBS += -L../../lib/sszn/ -lssznbasic
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
