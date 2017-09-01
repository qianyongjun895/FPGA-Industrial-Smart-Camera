/**
  * @file  [GrayHistogramDialog.h]
  * @brief  GrayHistogramDialog
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef GRAYHISTOGRAMDIALOG_H
#define GRAYHISTOGRAMDIALOG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class GrayHistogramDialog;
}
/**
  * @class  <GrayHistogramDialog>  [GrayHistogramDialog.h]  [GrayHistogramDialog]
  * @brief  灰度直方图
  * @author  <szj>
  * @note
  * detailed  description
  */
class GrayHistogramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GrayHistogramDialog(QWidget *parent = 0);
    ~GrayHistogramDialog();
    int m_task_id;
    int m_step_id;
    void *m_pre_ptr;
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 灰度直方图模块初始化数据
     */
    void IniData();
    /**
     * @brief PaintPic
     * @param mode_sel  0表示全图统计，1表示只统计二值化数
     * @param bw_dir_sel 统计方向（二值化统计模式下生效） 0表示按列统计二值化数据，1表示按行统计二值化数据
     * @author szj
     * @date 2017/05/08
     * @note 灰度直方图模块初始化数据
     */
    void PaintPic(int mode_sel =0 , int bw_dir_sel = 0);
private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_radioButtonPic_clicked();

    void on_radioButtonBin_clicked();

    void on_radioButtonColumn_clicked();

    void on_radioButtonRow_clicked();

    void on_radioButtonWhhiltePix_clicked();

    void on_radioButtonBlackPix_clicked();

private:
    Ui::GrayHistogramDialog *ui;
    HIST_MODEL_CFG m_cfg;
};

#endif // GRAYHISTOGRAMDIALOG_H
