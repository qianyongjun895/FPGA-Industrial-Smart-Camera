/**
  * @file  [ShadingDialog.h]
  * @brief  ShadingDialog
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef SHADINGDIALOG_H
#define SHADINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include "AcceCommon.h"
namespace Ui {
class ShadingDialog;
}
/**
  * @class  <ShadingDialog>  [ShadingDialog.h]  [ShadingDialog]
  * @brief  实时浓淡补正模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class ShadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShadingDialog(QWidget *parent = 0);
    ~ShadingDialog();
    int m_task_id;
    int m_step_id;
    int m_listX;
    int m_listY;
    void *m_pre_ptr;
    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据
     */
    void IniData();
private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_horizontalSliderGain_sliderPressed();

    void on_horizontalSliderGain_sliderReleased();

    void on_btnSubGain_pressed();

    void on_btnSubGain_released();

    void on_btnAddGain_pressed();

    void on_btnAddGain_released();

    void on_horizontalSliderGain_valueChanged(int value);

    void AddGain(int value =1);
    void SubGain(int value =1);

    void on_radioButton3_clicked();
    void on_radioButton5_clicked();
    void on_radioButton7_clicked();
    void on_radioButton9_clicked();
    void on_radioButton11_clicked();
    void on_radioButton13_clicked();

    void on_radioButtonXY_clicked();

    void on_radioButtonX_clicked();

    void on_radioButtonY_clicked();

    void on_radioButtonAverage_clicked();

    void on_radioButtonMiddle_clicked();

    void on_radioButtonShade_clicked();

    void on_radioButtonB_clicked();

    void on_radioButtonD_clicked();

    void on_radioButtonBD_clicked();

    void on_radioButtonBDRand_clicked();

    void on_btnSubTH_pressed();

    void on_btnSubTH_released();

    void on_btnAddTH_pressed();

    void on_btnAddTH_released();

    void on_horizontalSliderTH_valueChanged(int value);

    void on_horizontalSliderTH_sliderReleased();

    void SubTH(int value =1);
    void AddTH(int value =1);

    void on_btnSubGainDark_pressed();

    void on_btnSubGainDark_released();

    void on_btnAddGainDark_pressed();

    void on_btnAddGainDark_released();

    void on_horizontalSliderGainDark_sliderReleased();

    void on_horizontalSliderGainDark_valueChanged(int value);

    void SubGainDark(int value =1);
    void AddGainDark(int value =1);
private:
    Ui::ShadingDialog *ui;
    SHADING_MODEL_CFG m_cfg;
};

#endif // SHADINGDIALOG_H
