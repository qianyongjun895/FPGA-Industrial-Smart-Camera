/**
  * @file  [HomeWidget.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QTimer>
#include "RenameTool/RenameToolWidget.h"
#include "TaskSaveDlg.h"
#include "BusinessData/InterfaceLib/UIToolLibFun.h"
#include <QTimer>
#include <QTime>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"

namespace Ui {
class HomeWidget;
}
/**
  * @class  <ToolMainTypeDialog>  [ToolMainTypeDialog.h]  [ToolMainTypeDialog]
  * @brief  主界面
  * @author  <szj>
  * @note
  * detailed  description
  */
class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = 0);
    ~HomeWidget();

    void BeginRunTask();

    void SetBtnEnable(int flag);
private slots:
    void UpdateStateTimeOut();
    void SlotRename(int index, QString strName);
    void SlotModifyTaskName(int bexit, QString strName);

    void on_btnImageRun_clicked();

    void on_btnRecord_clicked();


    void ListOsdTimeOut();
    void ShowRunDataSlot(QStringList info, int cnt);
    void OsdUpdteSlot(QPixmap pix);
    void SlotOver();
    void on_listWidget_currentRowChanged(int currentRow);

    void on_btnMatchLineUp_clicked();

    void on_btnMatchLineDown_clicked();

    void on_btnSaveTask_clicked();

    void on_btnOpenTask_clicked();

    void on_btnToolEnable_clicked();

    void on_btnRunCount_clicked();

    void on_btnCheck_clicked();

    void on_checkBox_SimuSwitch_clicked();

    void on_btnImageSelect_clicked();

    void on_checkBoxSaveImage_clicked();

    void on_checkBoxSaveImageOK_clicked();

    void on_btnJudge_clicked();

    void on_btnFirst_clicked();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_btnLast_clicked();

    void on_btnSaveImage_clicked();

    void on_btnSelectImageSavePath_clicked();

    void on_btnViewImage_clicked();

    void on_tabWidgetResult_tabBarClicked(int index);

    void on_btnToolRename_clicked();

    void on_btnRun_pressed();

    void on_btnRun_released();



    void on_btnStop_pressed();

    void on_btnStop_released();



    void on_checkBox_Startrun_clicked();



    void on_btnToolOsdEdit_clicked();


protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void TaskRunSignal(bool flag);

private:
    Ui::HomeWidget *ui;
    int m_results_index;//多结果任务的结果索引
    int m_results_cnt;//多结果任务的结果数
    QIcon m_icon_ok;
    QIcon m_icon_ng;
    QIcon m_icon_noexcuse;
    QTimer *m_listOsd_timer;
    QTimer *m_update_state;
    RenameToolWidget *m_RenameToolWidget;
    TaskSaveDlg *m_TaskSaveDlg;
    KeyBoardLib m_keyBoardLib;
    QTime m_start;
    QTime m_end;
    void btnRun_clicked();
    void btnStop_clicked();
    /**
     * @brief IniTaskListWiget
     * @author szj
     * @date 2017/05/22
     * @note 初始化任务列表
     */
    void IniTaskListWiget();
    /**
     * @brief InitIconTask
     * @author szj
     * @date 2017/05/22
     * @note 初始化任务运行状态图标
     */
    void InitIconTask();
    /**
     * @brief SetItemTextColor
     * @param index 数组下标
     * @param flag  运行状态 1运行ok 2运行ng, 0 没有执行
     *@note 设置运行时状态图标
     */
    void SetItemTextColor(int index,int flag);
    void SetSimuControl(int iEnable);
    void GetTaskSimulateMode();
    void GetIp();
    void AddOkNgPicSave();
    void InitSimulationDir();
    int CheckParamInvalid();
    void InitUtilityToolIcon();
    void InitImageSetData();
    void InitCurTaskName();
    void run_clicked();
    void AddRunLib();
    void RemoveRunLib();

};

#endif // HOMEWIDGET_H
