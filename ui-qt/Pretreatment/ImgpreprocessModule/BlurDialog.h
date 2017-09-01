/**
  * @file  [BlurDialog.h]
  * @brief  BlurDialog
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */

#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class BlurDialog;
}
/**
  * @class  <BlurDialog>  [BlurDialog.h]  [BlurDialog]
  * @brief  模糊处理模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class BlurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlurDialog(QWidget *parent = 0);
    ~BlurDialog();
    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据
     */
    void InitData();
    int m_task_id;
    int m_step;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;

private slots:
    void on_btnNumSub_clicked();

    void on_btnNumAdd_clicked();

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::BlurDialog *ui;
    BLUR_MODEL_CFG m_cfg;
};

#endif // BLURDIALOG_H
