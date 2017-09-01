/**
  * @file  [TaskMainToolEditDlg.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef TASKMAINTOOLEDITDLG_H
#define TASKMAINTOOLEDITDLG_H

#include <QDialog>
#include <QTimer>
#include <QGridLayout>
#include <stdbool.h>
#include "BusinessData/InterfaceLib/UIToolLibFun.h"
#include "BusinessData/InterfaceLib/PretreatmentLibFun.h"
#include "BusinessData/InterfaceLib/RelationLibFun.h"
#include "TaskGlobal.h"

typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

namespace Ui {
class TaskMainToolEditDlg;
}
/**
  * @class  <TaskMainToolEditDlg>  [TaskMainToolEditDlg.h]  [TaskMainToolEditDlg]
  * @brief  工具编辑主框架
  * @author  <szj>
  * @note
  * detailed  description
  */
class TaskMainToolEditDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TaskMainToolEditDlg(QWidget *parent = 0);
    ~TaskMainToolEditDlg();
    int IniData();
    /**
     * @brief AddPreWidget
     * @return 空
     * @author szj
     * @date 2017/05/22
     * @note 增加预处理界面
     */
    void AddPreWidget();
    /**
     * @brief AddRLWidget
     * @return 空
     * @author szj
     * @date 2017/05/22
     * @note 增加关联定位界面
     */
    void AddRLWidget();
    /**
     * @brief AddParaWidget
     * @return 空
     * @author szj
     * @date 2017/05/22
     * @note 增加任务工具参数界面
     */
    int AddParaWidget();

    void AddCommWidget();
    int m_task_id; //任务id
    int m_task_step; //任务步骤
    QString m_taskName;
    QString m_lib_path; //任务界面库
    QString m_fun_lib_path; //任务界面库需调用其他库的路径
    QVector<QString> vt_name;
    int m_i_add;
private slots:
    void OsdUpdteSlot(QPixmap pix);

    void on_btnOK_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_btnQuit_clicked();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();
    void LearnTimerSlot();
    void on_btnExcute_clicked();

    void on_btnOSDSet_clicked();
signals:
    void SignalExit();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::TaskMainToolEditDlg *ui;
    int m_para_x;
    int m_para_y;
    int m_rl_x;
    int m_rl_y;
    int m_current;
    int m_need__ReloadModeFiles;
    char input_bak[2560];
    QVector<int>m_vt_tab_index;
    TASK_STEP_HEADER task_step_header_bak;
    QVector<QString> m_strNameList;
    QGridLayout *MainViewLayout; //参数
    QWidget *m_pWidget; //参数界面
    QGridLayout *MainViewLayout_pre; //预处理
    QWidget *m_pWidget_pre; //预处理界面
    QGridLayout *MainViewLayout_RL; //关联定位
    QWidget *m_pWidget_RL; //关联定位界面
    QGridLayout *MainViewLayout_comm; //公共
    QWidget *m_pWidget_comm; //公共


    UIToolLibFun m_ToolLibFun;
    PretreatmentLibFun m_preLibFun;
    RelationLibFun m_RLFun;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;
    int m_learn_result;//取样结果1成功，0失败
    void SetListVga(int x,int y);
    void SelectImg();
    void LoadLearnLib();
    void IniImageList(QString strName);
    int CheckTaskParamInvalidInfo();
    void StepExcecute();
    void InitStepExcuteLib();
};

#endif // TASKMAINTOOLEDITDLG_H
