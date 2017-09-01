/**
  * @file  [CptDlg.h]
  * @brief  CptDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef PRETREATMENTSUMMARYDIALOG_H
#define PRETREATMENTSUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class PretreatmentSummaryDialog;
}
/**
  * @class  <PretreatmentSummaryDialog>  [PretreatmentSummaryDialog.h]  [PretreatmentSummaryDialog]
  * @brief  预处理模块数据列表对话框
  * @author  <szj>
  * @note
  * detailed  description
  */
class PretreatmentSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PretreatmentSummaryDialog(QWidget *parent = 0);
    ~PretreatmentSummaryDialog();
    /**
     * @brief SetLocation
     * @param x 对话框显示的x坐标
     * @param y 对话框显示的y坐标
     * @author szj
     * @date 2017/05/08
     * @note cpt模块初始化数据
     */
    void SetLocation(int x, int y);
    /**
     * @brief GetStrName
     * @return 返回预处理模块名称
     * @author szj
     * @date 2017/05/08
     * @note 获取预处理模块名称
     */
    QString GetStrName(){return m_str_name;}
    /**
     * @brief GetIndex
     * @return 返回预处理模块ID
     * @author szj
     * @date 2017/05/08
     * @note 获取预处理模块ID
     */
    int GetIndex(){return m_index;}
    /**
     * @brief GetNameIndexById
     * @param id 预处理模块ID
     * @return 返回预处理模块名称
     * @author szj
     * @date 2017/05/08
     * @note 根据预处理模块ID查找预处理模块名称
     */
    int GetNameIndexById(int id);
    /**
     * @brief GetStrNameByArrIndex
     * @param index 数组下标
     * @return 返回预处理模块名称
     * @author szj
     * @date 2017/05/08
     * @note 根据数组下标查找预处理模块名称
     */
    QString GetStrNameByArrIndex(int index);

private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::PretreatmentSummaryDialog *ui;
    QString m_str_name;
    QVector<int> m_vt_index;
    QVector<QString>m_vt_strName;
    int m_index;
    /**
     * @brief IniListData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据
     */
    void IniListData();
};

#endif // PRETREATMENTSUMMARYDIALOG_H
