#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T10:51:49
#
#-------------------------------------------------

QT       += core gui sql
QT       += charts
QT       += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InfernoUI
TEMPLATE = app
CONFIG += qt warn_on release

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR=../bin
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH  += ../../include \
                ../../include/function \
                ../../include/function/sszn \
                ../../include/function/third_party \
                ../../include/lfpga_include \
                ../../include/lzynq_include \
                ../../include/comm_include \
                ../../include/task

SOURCES += main.cpp\
        InfernoUI.cpp \
    Comm/ControlStyle.cpp \
    Comm/FileIniControl.cpp \
    Home/HomeWidget.cpp \
    Tool/MainPanel/TaskMainToolEditDlg.cpp \
    Tool/MainPanel/ToolIconMenuMainWnd.cpp \
    Tool/MainPanel/ToolMainTypeDialog.cpp \
    ImageSet/ImageSetWidget.cpp \
    SystemSet/SystemSetWiget.cpp \
    Tool/MainPanel/TaskListStepWidget.cpp \
    BusinessData/InterfaceLib/UIToolLibFun.cpp \
    Comm/GlobalParameter.cpp \
    SystemSet/UserManage/LoginDialog.cpp \
    BusinessData/InterfaceLib/LibTaskXMLParse.cpp \
    BusinessData/InterfaceLib/BaseLibInterface.cpp \
    BusinessData/InterfaceLib/LibInitCamera.cpp \
    BusinessData/RunData/CRunDataThread.cpp \
    Home/HomeWidgetPicLabel.cpp \
    BusinessData/InterfaceLib/PretreatmentLibFun.cpp \
    BusinessData/InterfaceLib/RelationLibFun.cpp \
    BusinessData/InterfaceLib/LibTaskFun.cpp \
    CalibrationWidget/CalibrationParamReference.cpp \
    CalibrationWidget/CalibrationParamSelect.cpp \
    CalibrationWidget/CalibrationWidget.cpp \
    CalibrationWidget/Demarcate/MultipointsDemarcate.cpp \
    CalibrationWidget/Calibration/ScaleCalibration.cpp \
    DataOutput/DataOutputWidget.cpp \
    DataOutput/ExternalCommWidget.cpp \
    CalibrationWidget/Calibration/ScaleImageLabel.cpp \
    CalibrationWidget/Demarcate/MultipointDemarcateImageLabel.cpp \
    SystemSet/TouchScreenCalibrate/TouchScreenCalibrate.cpp \
    SystemSet/VersionInfo/VersionInfo.cpp \
    ../Global/UtilitiesFun.cpp \
    BusinessData/InterfaceLib/BaseImageData.cpp \
    Home/RegisterImageDlg.cpp \
    Tool/MainPanel/BasicImageSelect.cpp \
    SystemSet/LicenseInfo/LicenseInfo.cpp \
    ImageSet/ImageSetLabelEdit.cpp \
    SystemSet/NetWork/NetWork.cpp \
    SystemSet/UserManage/UserInfo.cpp \
    SystemSet/UserManage/AdminWidget.cpp \
    SystemSet/Upgrade/UpgradeWidget.cpp \
    SystemSet/Upgrade/UpgradeStatusDialog.cpp \
    DataOutput/IOSetWidget.cpp \
    SystemSet/TaskImportExport/TaskImportExport.cpp \
    Home/TaskLoadDlg.cpp \
    Home/TaskSaveDlg.cpp \
    ResetCameraDialog.cpp \
    SystemSet/ScriptImportExport/ScriptImportExport.cpp \
    Home/ToolEnable/ToolEnableDialog.cpp \
    Home/ToolEnable/ToolEnableItem.cpp \
    Home/RunStatistics/RunStatistics.cpp \
    Tool/MainPanel/Roi/StepExcuteLabel.cpp \
    SystemSet/UpdateProgressBarDlg.cpp \
    Home/TendencyGraph/TendencyGraph.cpp \
    Tool/MainPanel/Roi/ToolIconMenuMainWndLabel.cpp \
    Home/SimulationTool/SimulationSelsetDog.cpp \
    Tool/MainPanel/CommPara/CommPara.cpp \
    Tool/MainPanel/CommPara/IOPortSelectDialog.cpp \
    Comm/MessageDlg.cpp \
    Tool/MainPanel/Roi/StepEditExcuteLabel.cpp \
    Home/SyntheticJudgment/SyntheticJudgment.cpp \
    BusinessData/InterfaceLib/KeyBoardLib.cpp \
    SystemSet/AddToolFiles/AddToolFiles.cpp \
    Comm/keyBoard/frminput.cpp \
    Comm/CommonRowInput/CommonRowInput.cpp \
    Home/SimulationTool/ImageManagemnet.cpp \
    Comm/OSDStyle.cpp \
    Home/RunOsdStyle/RunOsdStyleDlg.cpp \
    Home/RunOsdStyle/RunOsdStyleItem.cpp \
    Tool/MainPanel/LearnOneRoundDialog.cpp \
    Tool/MainPanel/OSDColorSetDlg.cpp \
    Home/RenameTool/RenameToolWidget.cpp \
    Home/RenameTool/ToolNameItem.cpp \
    DataOutput/DataInputWidget.cpp \
    DataOutput/DataInputItem.cpp \
    ImageSet/ImageParamSelectDialog.cpp \
    DataOutput/InsideComm/InsideComm.cpp \
    DataOutput/InsideComm/IntercomModbusDataListItem.cpp \
    DataOutput/InsideComm/IntercomModbusSelectDataDialog.cpp \
    DataOutput/InsideComm/IntercomMultiCoilItem.cpp \
    DataOutput/InsideComm/IntercomMultiRegDialog.cpp \
    DataOutput/InsideComm/IntercomMultiRegItem.cpp \
    DataOutput/InsideComm/IntercomRDSingleCoilDialog.cpp \
    DataOutput/InsideComm/IntercomReadRegDialog.cpp \
    DataOutput/InsideComm/IntercomWRMultiCoilDialog.cpp \
    DataOutput/HeartBeatWidget.cpp \
    CalibrationWidget/MatchineLabel.cpp \
    Comm/CheckMouse.cpp \
    Comm/FileView.cpp


HEADERS  += InfernoUI.h \
    Comm/ControlStyle.h \
    Comm/FileIniControl.h \
    Home/HomeWidget.h \
    Tool/MainPanel/TaskMainToolEditDlg.h \
    Tool/MainPanel/ToolIconMenuMainWnd.h \
    Tool/MainPanel/ToolMainTypeDialog.h \
    ImageSet/ImageSetWidget.h \
    SystemSet/SystemSetWiget.h \
    Tool/MainPanel/TaskListStepWidget.h \
    BusinessData/InterfaceLib/UIToolLibFun.h \
    Comm/GlobalParameter.h \
    SystemSet/UserManage/LoginDialog.h \
    BusinessData/InterfaceLib/LibTaskXMLParse.h \
    BusinessData/InterfaceLib/BaseLibInterface.h \
    BusinessData/InterfaceLib/LibInitCamera.h \
    BusinessData/RunData/CRunDataThread.h \
    Home/HomeWidgetPicLabel.h \
    BusinessData/InterfaceLib/PretreatmentLibFun.h \
    BusinessData/InterfaceLib/RelationLibFun.h \
    BusinessData/InterfaceLib/LibTaskFun.h \
    CalibrationWidget/CalibrationParamReference.h \
    CalibrationWidget/CalibrationParamSelect.h \
    CalibrationWidget/CalibrationWidget.h \
    CalibrationWidget/Demarcate/MultipointsDemarcate.h \
    CalibrationWidget/Calibration/ScaleCalibration.h \
    DataOutput/DataOutputWidget.h \
    DataOutput/ExternalCommWidget.h \
    CalibrationWidget/Calibration/ScaleImageLabel.h \
    CalibrationWidget/Demarcate/MultipointDemarcateImageLabel.h \
    SystemSet/TouchScreenCalibrate/TouchScreenCalibrate.h \
    SystemSet/VersionInfo/VersionInfo.h \
    ../Global/UtilitiesFun.h \
    BusinessData/InterfaceLib/BaseImageData.h \
    Home/RegisterImageDlg.h \
    Tool/MainPanel/BasicImageSelect.h \
    SystemSet/LicenseInfo/LicenseInfo.h \
    ImageSet/ImageSetLabelEdit.h \
    SystemSet/NetWork/NetWork.h \
    SystemSet/UserManage/UserInfo.h \
    SystemSet/UserManage/AdminWidget.h \
    SystemSet/Upgrade/UpgradeWidget.h \
    SystemSet/Upgrade/UpgradeStatusDialog.h \
    DataOutput/IOSetWidget.h \
    SystemSet/TaskImportExport/TaskImportExport.h \
    Home/TaskLoadDlg.h \
    Home/TaskSaveDlg.h \
    ResetCameraDialog.h \
    SystemSet/ScriptImportExport/ScriptImportExport.h \
    Home/ToolEnable/ToolEnableDialog.h \
    Home/ToolEnable/ToolEnableItem.h \
    Home/RunStatistics/RunStatistics.h \
    Tool/MainPanel/Roi/StepExcuteLabel.h \
    SystemSet/UpdateProgressBarDlg.h \
    Home/TendencyGraph/TendencyGraph.h \
    Tool/MainPanel/Roi/ToolIconMenuMainWndLabel.h \
    Home/SimulationTool/SimulationSelsetDog.h \
    Tool/MainPanel/CommPara/CommPara.h \
    Tool/MainPanel/CommPara/IOPortSelectDialog.h \
    Comm/MessageDlg.h \
    Tool/MainPanel/Roi/StepEditExcuteLabel.h \
    Home/SyntheticJudgment/SyntheticJudgment.h \
    BusinessData/InterfaceLib/KeyBoardLib.h \
    SystemSet/AddToolFiles/AddToolFiles.h \
    Comm/keyBoard/frminput.h \
    Comm/CommonRowInput/CommonRowInput.h \
    Home/SimulationTool/ImageManagemnet.h \
    Comm/OSDStyle.h \
    Home/RunOsdStyle/RunOsdStyleDlg.h \
    Home/RunOsdStyle/RunOsdStyleItem.h \
    Tool/MainPanel/LearnOneRoundDialog.h \
    Tool/MainPanel/OSDColorSetDlg.h \
    Home/RenameTool/RenameToolWidget.h \
    Home/RenameTool/ToolNameItem.h \
    DataOutput/DataInputWidget.h \
    DataOutput/DataInputItem.h \
    ImageSet/ImageParamSelectDialog.h \
    DataOutput/InsideComm/InsideComm.h \
    DataOutput/InsideComm/IntercomModbusDataListItem.h \
    DataOutput/InsideComm/IntercomModbusSelectDataDialog.h \
    DataOutput/InsideComm/IntercomMultiCoilItem.h \
    DataOutput/InsideComm/IntercomMultiRegDialog.h \
    DataOutput/InsideComm/IntercomMultiRegItem.h \
    DataOutput/InsideComm/IntercomRDSingleCoilDialog.h \
    DataOutput/InsideComm/IntercomReadRegDialog.h \
    DataOutput/InsideComm/IntercomWRMultiCoilDialog.h \
    DataOutput/HeartBeatWidget.h \
    CalibrationWidget/MatchineLabel.h \
    Comm/CheckMouse.h \
    Comm/FileView.h


FORMS    += InfernoUI.ui \
    Home/HomeWidget.ui \
    Tool/MainPanel/TaskMainToolEditDlg.ui \
    Tool/MainPanel/ToolIconMenuMainWnd.ui \
    Tool/MainPanel/ToolMainTypeDialog.ui \
    ImageSet/ImageSetWidget.ui \
    SystemSet/SystemSetWiget.ui \
    Tool/MainPanel/TaskListStepWidget.ui \
    SystemSet/UserManage/LoginDialog.ui \
    CalibrationWidget/CalibrationParamReference.ui \
    CalibrationWidget/CalibrationParamSelect.ui \
    CalibrationWidget/CalibrationWidget.ui \
    CalibrationWidget/Demarcate/MultipointsDemarcate.ui \
    CalibrationWidget/Calibration/ScaleCalibration.ui \
    DataOutput/DataOutputWidget.ui \
    DataOutput/ExternalCommWidget.ui \
    SystemSet/VersionInfo/VersionInfo.ui \
    SystemSet/TouchScreenCalibrate/TouchScreenCalibrate.ui \
    Home/RegisterImageDlg.ui \
    Tool/MainPanel/BasicImageSelect.ui \
    SystemSet/LicenseInfo/LicenseInfo.ui \
    SystemSet/NetWork/NetWork.ui \
    SystemSet/UserManage/AdminWidget.ui \
    SystemSet/Upgrade/UpgradeWidget.ui \
    SystemSet/Upgrade/UpgradeStatusDialog.ui \
    DataOutput/IOSetWidget.ui \
    SystemSet/TaskImportExport/TaskImportExport.ui \
    Home/TaskLoadDlg.ui \
    Home/TaskSaveDlg.ui \
    ResetCameraDialog.ui \
    SystemSet/ScriptImportExport/ScriptImportExport.ui \
    Home/ToolEnable/ToolEnableDialog.ui \
    Home/ToolEnable/ToolEnableItem.ui \
    Home/RunStatistics/RunStatistics.ui \
    SystemSet/UpdateProgressBarDlg.ui \
    Home/TendencyGraph/TendencyGraph.ui \
    Home/SimulationTool/SimulationSelsetDog.ui \
    Tool/MainPanel/CommPara/CommPara.ui \
    Tool/MainPanel/CommPara/IOPortSelectDialog.ui \
    Comm/MessageDlg.ui \
    Home/SyntheticJudgment/SyntheticJudgment.ui \
    SystemSet/AddToolFiles/AddToolFiles.ui \
    Comm/keyBoard/frminput.ui \
    Comm/CommonRowInput/CommonRowInput.ui \
    Home/SimulationTool/ImageManagemnet.ui \
    Home/RunOsdStyle/RunOsdStyleDlg.ui \
    Home/RunOsdStyle/RunOsdStyleItem.ui \
    Tool/MainPanel/LearnOneRoundDialog.ui \
    Tool/MainPanel/OSDColorSetDlg.ui \
    Home/RenameTool/RenameToolWidget.ui \
    Home/RenameTool/ToolNameItem.ui \
    DataOutput/DataInputWidget.ui \
    DataOutput/DataInputItem.ui \
    ImageSet/ImageParamSelectDialog.ui \
    DataOutput/InsideComm/InsideComm.ui \
    DataOutput/InsideComm/IntercomModbusDataListItem.ui \
    DataOutput/InsideComm/IntercomModbusSelectDataDialog.ui \
    DataOutput/InsideComm/IntercomMultiCoilItem.ui \
    DataOutput/InsideComm/IntercomMultiRegDialog.ui \
    DataOutput/InsideComm/IntercomMultiRegItem.ui \
    DataOutput/InsideComm/IntercomRDSingleCoilDialog.ui \
    DataOutput/InsideComm/IntercomReadRegDialog.ui \
    DataOutput/InsideComm/IntercomWRMultiCoilDialog.ui \
    DataOutput/HeartBeatWidget.ui \
    Comm/FileView.ui



RESOURCES += \
    Resource/resource.qrc
LIBS += -lxml2
LIBS += -llzma
LIBS += -L../../lib/sszn/ -ltaskparse
LIBS += -L../../lib/sszn/ -ltask
LIBS += -L../../lib/sszn/ -lSsznAlg
LIBS += -L../../lib/sszn/ -lzynq
LIBS += -L../../lib/sszn/ -lfpga
LIBS += -L../../lib/sszn/ -lssznbasic
LIBS += -L../../lib/sszn/ -lEmmc
LIBS += -L../../lib/sszn/communicate/ -lUart
LIBS += -L../../lib/sszn/communicate/ -lTcp
LIBS += -L../../lib/sszn/communicate/ -lUdp
LIBS += -L../../lib/sszn/communicate/ -lProtocolManage
LIBS += -L../../lib/sszn/communicate/ -lmodbus
LIBS += -L../../lib/sszn/communicate/ -lModbusComm
LIBS += -L../../lib/sszn/communicate/ -lUserDefinedComm
LIBS += -L../../lib/sszn/communicate/ -lMitFxComm
LIBS += -L../../lib/sszn/communicate/ -lIntercomModbusComm
LIBS += -L../../lib/sszn/ -llinkdata
LIBS += -L../../lib/sszn/ -lImageManage
LIBS += -L../../lib/sszn/ -lHansRobotComm



QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
