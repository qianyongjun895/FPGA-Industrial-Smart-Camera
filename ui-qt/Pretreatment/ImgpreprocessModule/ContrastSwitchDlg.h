/**
  * @file  [ContrastSwitchDlg.h]
  * @brief  ContrastSwitchDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef CONTRASTSWITCHDLG_H
#define CONTRASTSWITCHDLG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class ContrastSwitchDlg;
}
/**
  * @class  <ContrastSwitchDlg>  [ContrastSwitchDlg.h]  [ContrastSwitchDlg]
  * @brief  对比度转换
  * @author  <szj>
  * @note
  * detailed  description
  */
class ContrastSwitchDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastSwitchDlg(QWidget *parent = 0);
    ~ContrastSwitchDlg();

    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据
     */void IniData();
    int m_task_id;
    int m_step;
    int m_listX;
    int m_listY;
    void *m_pre_ptr;

private slots:
    void on_btnOk_clicked();

    void on_btnSubGainMask_pressed();

    void on_btnSubGainMask_released();

    void on_btnAddGainMask_pressed();

    void on_btnAddGainMask_released();

    void on_btnSubGrayMask_pressed();

    void on_btnSubGrayMask_released();

    void on_btnAddGrayMask_pressed();

    void on_btnAddGrayMask_released();

    void on_horizontalSliderGainMask_sliderReleased();

    void on_horizontalSliderGainMask_valueChanged(int value);

    void on_horizontalSliderGrayMask_sliderReleased();

    void on_horizontalSliderGrayMask_valueChanged(int value);
    void AddGainMask(int value =1);
    void SubGainMask(int value =1);
    void AddGrayMask(int value =1);
    void SubGrayMask(int value =1);


    void on_btnQuit_clicked();

private:
    Ui::ContrastSwitchDlg *ui;
    CT_MODEL_CFG m_cfg;
};

#endif // CONTRASTSWITCHDLG_H
