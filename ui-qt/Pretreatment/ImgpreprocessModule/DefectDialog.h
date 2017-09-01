/**
  * @file  [DefectDialog.h]
  * @brief  DefectDialog
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef DEFECTDIALOG_H
#define DEFECTDIALOG_H

#include <QDialog>
#include <QTimer>
#include "AcceCommon.h"
namespace Ui {
class DefectDialog;
}
/**
  * @class  <DefectDialog>  [DefectDialog.h]  [DefectDialog]
  * @brief  缺陷提取
  * @author  <szj>
  * @note
  * detailed  description
  */
class DefectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DefectDialog(QWidget *parent = 0);
    ~DefectDialog();
    int m_task_id;
    int m_step_id;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;
    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化模块数据
     */
    void IniData();
private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_horizontalSliderGain_sliderReleased();

    void on_btnSubGain_pressed();

    void on_btnSubGain_released();

    void on_btnAddGain_pressed();

    void on_btnAddGain_released();

    void on_horizontalSliderGain_valueChanged(int value);

    void AddGain(int value =1);

    void SubGain(int value =1);

private:
    Ui::DefectDialog *ui;
    DEFECT_MODEL_CFG m_cfg;;
};

#endif // DEFECTDIALOG_H
