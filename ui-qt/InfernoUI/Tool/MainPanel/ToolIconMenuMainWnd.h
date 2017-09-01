/**
  * @file  [ToolIconMenuMainWnd.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef TOOLICONMENUMAINWND_H
#define TOOLICONMENUMAINWND_H

#include <QWidget>
//#include "Comm/UIBasicDefine.h"
#include "BasicDefine.h"
#include "TaskMainToolEditDlg.h"
namespace Ui {
class ToolIconMenuMainWnd;
}
/**
  * @class  <ToolIconMenuMainWnd>  [ToolIconMenuMainWnd.h]  [ToolIconMenuMainWnd]
  * @brief  已添加的图像工具栏
  * @author  <szj>
  * @note
  * detailed  description
  */
class ToolIconMenuMainWnd : public QWidget
{
    Q_OBJECT

public:
    explicit ToolIconMenuMainWnd(QWidget *parent = 0);
    ~ToolIconMenuMainWnd();
    void StepExcecute();
private slots:
    void ExitSlot();
    void SingleExcuteSlot(QVector<STRU_KEY_VALUE> vtHead,QVector<STRU_KEY_VALUE> vtBody,int cnt,QVector<QVector<STRU_KEY_VALUE> >vt);
    void OsdUpdteSlot(QPixmap pix);

    void on_toolViewBtn_clicked();

    void on_stepEditBtn_clicked();

    void on_taskListWidget_clicked(const QModelIndex &index);

    void on_stepDeleteBtn_clicked();

    void on_clearTaskBtn_clicked();

    void on_btnPrevPage_clicked();

    void on_btnNextPage_clicked();

    void on_btnDataPre_clicked();

    void on_btnDataNext_clicked();
    void on_LearnOneRound_clicked();

signals:
    void TaskRunSignal(bool flag);

private:
    Ui::ToolIconMenuMainWnd *ui;
    int m_current_index; // 当前任务列表选中项索引
    int m_task_id;
    int m_i_add;
    int m_execute;
    int m_template_flag;
    TaskMainToolEditDlg *m_TaskMainToolEditDlg;
    void AddStepToTaskListWidget(int stepIndex, int stepType, QString strName, QString strPath, QString strIcon,QString libFunPaht);
    void AddStepItem(int stepType, QString strName, QString strPath, QString strIcon,QString libFunPaht);
    void InitTaskList();
    QVector<QString> GetTaskNameVt();
    int CheckTaskParamInvalidInfo();
    void InitStepExcuteLib();
    void SetStatusLabelOK();
    void SetStatusLabelNG();
    void SetStatusLabelNone();
    void SetExecuteTimeLabel(double exeTime);
    void SetOneRoundTimeLabel(double exeTime);
    void StepExecuteTimeLabelInit();
    void OneRoundTimeLabelInit();
    void UpdateListItemsStatus(int index,int ok);
    void SetControlEnable(int flag);
    void LoadToolBasicImage();
};

#endif // TOOLICONMENUMAINWND_H
