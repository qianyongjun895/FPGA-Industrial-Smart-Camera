/**
  * @file  [EdgeExtractDlg.h]
  * @brief  EdgeExtractDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */

#ifndef EDGEEXTRACTDLG_H
#define EDGEEXTRACTDLG_H

#include <QDialog>
#include <stdbool.h>
#include <QTime>
#include "AcceCommon.h"

namespace Ui {
class EdgeExtractDlg;
}
/**
  * @class  <EdgeExtractDlg>  [EdgeExtractDlg.h]  [EdgeExtractDlg]
  * @brief  边沿提取模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class EdgeExtractDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EdgeExtractDlg(QWidget *parent = 0);
    ~EdgeExtractDlg();
    int m_step;
    int m_task_id;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;
    SIDE_SELECT_MODEL_CFG m_cfg;
    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化边沿提取模块数据
     */
    void InitData();

private slots:
    void HighLimitDecBtnKeepPressProc(int speed);
    void HighLimitIncBtnKeepPressProc(int speed);
    void LowLimitDecBtnKeepPressProc(int speed);
    void LowLimitIncBtnKeepPressProc(int speed);

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_sobelRadioBtn_clicked();

    void on_prewittRadioBtn_clicked();

    void on_laplacianRadioBtn_clicked();

    void on_robertsRadioBtn_clicked();

    void on_xyRadioBtn_clicked();

    void on_xRadioBtn_clicked();

    void on_yRadioBtn_clicked();

    void on_subPixelEnableCheckBox_clicked();

    void on_highLimitSilder_sliderReleased();

    void on_lowLimitSlider_sliderReleased();

    void on_highLimitSilder_sliderMoved(int position);

    void on_lowLimitSlider_sliderMoved(int position);

    void on_RadioBtnPoint_clicked();

    void on_RadioBtnPic_clicked();

    void on_highLimitDecBtn_pressed();

    void on_highLimitDecBtn_released();

    void on_highLimitIncBtn_pressed();

    void on_highLimitIncBtn_released();

    void on_lowLimitDecBtn_pressed();

    void on_lowLimitDecBtn_released();

    void on_lowLimitIncBtn_pressed();

    void on_lowLimitIncBtn_released();

signals:
    void SignalEdgeCfgPoints(int enable, QString str);
    void CheckedTypeSignals(QString str);
    void SignalSwitchListPoint(int value);
private:
    Ui::EdgeExtractDlg *ui;
    int m_ifirst;
    int m_auto_repeat_count; // 长按计数
    int m_self_inc; // 长按自增长值

    void SetPreproccessData();
    void SeleIncValuePro();

};

#endif // EDGEEXTRACTDLG_H
