/**
  * @file  [ToolMainTypeDialog.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/09>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef TOOLMAINTYPEDIALOG_H
#define TOOLMAINTYPEDIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class ToolMainTypeDialog;
}
/**
  * @class  <ToolMainTypeDialog>  [ToolMainTypeDialog.h]  [ToolMainTypeDialog]
  * @brief  图像工具分类
  * @author  <szj>
  * @note
  * detailed  description
  */
class ToolMainTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolMainTypeDialog(QWidget *parent = 0);
    ~ToolMainTypeDialog();
    int GetTaskId();
private slots:
    void on_addToolBtn_clicked();
    void on_insertToolBtn_clicked();
    void on_cancelBtn_clicked();
    void on_listWidgetType_clicked(const QModelIndex &index);

    void on_listWidgetDetail_clicked(const QModelIndex &index);

public:
    int m_tool_id; // 当前选中的工具类型ID
    int m_btn_operation;
    QString m_lib_path;
    QString m_icon_path;
    QString m_task_name;
    QString m_fun_lib_path;
private:
    Ui::ToolMainTypeDialog *ui;
    void ToolTypeInit(QString strName,QString strPic);
    void ToolDetailInit(QString strName,QString strPic);
    void InitTask();
    void ToolDetailListItem(int iSelect);
    void ListDetailInfo();
};

#endif // TOOLMAINTYPEDIALOG_H
