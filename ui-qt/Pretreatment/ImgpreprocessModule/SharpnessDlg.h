/**
  * @file  [SharpnessDlg.h]
  * @brief  SharpnessDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef SHARPNESSDLG_H
#define SHARPNESSDLG_H

#include <QDialog>
#include "AcceCommon.h"

namespace Ui {
class SharpnessDlg;
}
/**
  * @class  <SharpnessDlg>  [SharpnessDlg.h]  [SharpnessDlg]
  * @brief  边缘强调模块
  * @author  <szj>
  * @note
  * detailed  description
  */

class SharpnessDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SharpnessDlg(QWidget *parent = 0);
    ~SharpnessDlg();
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
    void AddSharpness(int value = 1);
    void SubSharpness(int value = 1);

    void on_btnSubSharpness_pressed();

    void on_btnSubSharpness_released();

    void on_btnAddSharpness_pressed();

    void on_btnAddSharpness_released();

    void on_horizontalSliderSharpness_sliderReleased();

    void on_horizontalSliderSharpness_valueChanged(int value);



    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::SharpnessDlg *ui;
    SHARPNESS_MODEL_CFG m_cfg;

};

#endif // SHARPNESSDLG_H
