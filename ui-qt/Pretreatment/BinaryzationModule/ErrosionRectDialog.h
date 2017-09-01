/**
  * @file  [ErrosionRectDialog.h]
  * @brief  ErrosionRectDialog
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef ERROSIONRECTDIALOG_H
#define ERROSIONRECTDIALOG_H

#include <QDialog>

namespace Ui {
class ErrosionRectDialog;
}
/**
  * @class  <ErrosionRectDialog>  [ErrosionRectDialog.h]  [ErrosionRectDialog]
  * @brief  腐蚀膨胀高级选项
  * @author  <szj>
  * @note
  * detailed  description
  */
class ErrosionRectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrosionRectDialog(QWidget *parent = 0);
    ~ErrosionRectDialog();
    int m_num;
    int m_task_id;
    int m_step;
    void *m_pre_ptr;
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据
     */
    void IniData();
private slots:
    void on_btnQuit_clicked();

    void on_btnSelectAll_clicked();

    void on_btnSelectAllNo_clicked();

    void on_radioButtonCirclee_clicked();

    void on_radioButtonDiamond_clicked();

    void on_radioButtonOther_clicked();

private:
    Ui::ErrosionRectDialog *ui;
};

#endif // ERROSIONRECTDIALOG_H
