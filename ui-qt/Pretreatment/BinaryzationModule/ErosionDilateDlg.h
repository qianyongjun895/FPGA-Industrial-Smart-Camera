/**
  * @file  [ErosionDilateDlg.h]
  * @brief  ErosionDilateDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef EROSIONDILATEDLG_H
#define EROSIONDILATEDLG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class ErosionDilateDlg;
}
/**
  * @class  <ErosionDilateDlg>  [ErosionDilateDlg.h]  [ErosionDilateDlg]
  * @brief  腐蚀膨胀
  * @author  <szj>
  * @note
  * detailed  description
  */
class ErosionDilateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ErosionDilateDlg(QWidget *parent = 0);
    ~ErosionDilateDlg();
    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化腐蚀膨胀数据
     */
    void InitData();
    int m_task_id;
    int m_step;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;
private slots:
    void LimitSub(int value =1);

    void LimitAdd(int value = 1);

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_btnLimitSub_pressed();

    void on_btnLimitSub_released();

    void on_btnLimitAdd_pressed();

    void on_btnLimitAdd_released();

    void on_horizontalSliderLimit_valueChanged(int value);

    void on_horizontalSliderLimit_sliderReleased();

    void on_radioButton3_clicked();

    void on_radioButton5_clicked();

    void on_radioButton7_clicked();

    void on_radioButton9_clicked();

    void on_radioButton11_clicked();

    void on_radioButton13_clicked();

    void on_checkBoxedSideDelEnable_clicked();

    void on_radioButtonErosion_clicked();

    void on_radioButtonDilate_clicked();

    void on_btnExpant_clicked();

    void on_btnNumSub_clicked();

    void on_btnNumAdd_clicked();

    void on_checkBoxedEdgeCalcu_clicked();

private:
    Ui::ErosionDilateDlg *ui;
    int m_bflag_ini;
    ERD_DIL_MODEL_CFG m_cfg;
    /**
     * @brief SetLibToData
     * @author szj
     * @date 2017/05/08
     * @note 保存腐蚀膨胀数据
     */
    void SetLibToData();
    /**
     * @brief Clear_filter_mask
     * @param type 腐蚀膨胀模板类型
     * @param value 腐蚀膨胀模板值
     * @author szj
     * @date 2017/05/08
     * @note 重新设置腐蚀膨胀滤波器的掩码
     */
    void Clear_filter_mask(int type,int value);
};

#endif // EROSIONDILATEDLG_H
