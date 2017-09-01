/**
  * @file  [TaskListStepWidget.h]
  * @brief  TaskListStepWidget
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef TASKLISTSTEPWIDGET_H
#define TASKLISTSTEPWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class TaskListStepWidget;
}
/**
  * @class  <TaskListStepWidget>  [TaskListStepWidget.h]  [TaskListStepWidget]
  * @brief  任务列表单项
  * @author  <szj>
  * @note
  * detailed  description
  */
class TaskListStepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskListStepWidget(QWidget *parent = 0);
    ~TaskListStepWidget();
    /**
     * @brief SetStepIcon
     * @param iconPath 任务图标
     * @author szj
     * @date 2017/05/08
     * @note 设置图标
     */
    void SetStepIcon(QString iconPath);
    /**
     * @brief SetStepStatus
     * @param color 任务状态颜色
     * @author szj
     * @date 2017/05/08
     * @note 设置任务状态颜色
     */
    void SetStepStatus(QString color);
    /**
     * @brief SetStepName
     * @param name 任务名称
     * @author szj
     * @date 2017/05/08
     * @note 设置任务名称
     */
    void SetStepName(QString name);
    /**
     * @brief GetStepName
     * @return 返回任务名称
     * @author szj
     * @date 2017/05/08
     * @note 获取任务名称
     */
    QString GetStepName();

public:
    int m_step_type; // 记录步骤类型ID
    QString m_lib_path; //记录控件lib
    QString m_fun_lib_path;
private:
    Ui::TaskListStepWidget *ui;
};

#endif // TASKLISTSTEPWIDGET_H
