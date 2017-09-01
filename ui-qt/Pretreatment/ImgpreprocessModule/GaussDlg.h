/**
  * @file  [GaussDlg.h]
  * @brief  GaussDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef GAUSSDLG_H
#define GAUSSDLG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class GaussDlg;
}
/**
  * @class  <GaussDlg>  [GaussDlg.h]  [GaussDlg]
  * @brief  高斯模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class GaussDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GaussDlg(QWidget *parent = 0);
    ~GaussDlg();
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
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_btnAdd_pressed();

    void on_btnAdd_released();

    void on_btnSub_pressed();

    void on_btnSub_released();
    void on_horizontalSliderSigma_sliderReleased();

    void on_horizontalSliderSigma_valueChanged(int value);
    void AddSigma(int value = 1);
    void SubSigma(int value = 1);

private:
    Ui::GaussDlg *ui;
    GAUSS_MODEL_CFG m_cfg;
};

#endif // GAUSSDLG_H
