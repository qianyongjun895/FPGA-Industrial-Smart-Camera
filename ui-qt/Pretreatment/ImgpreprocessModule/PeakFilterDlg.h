/**
  * @file  [PeakFilterDlg.h]
  * @brief  PeakFilterDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef PEAKFILTERDLG_H
#define PEAKFILTERDLG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class PeakFilterDlg;
}
/**
  * @class  <PeakFilterDlg>  [PeakFilterDlg.h]  [PeakFilterDlg]
  * @brief  原图腐蚀膨胀
  * @author  <szj>
  * @note
  * detailed  description
  */
class PeakFilterDlg : public QDialog
{
    Q_OBJECT

public:
    typedef enum
    {
        SharpnessA = 0,
        SharpnessB
    }SharpnessKind;
    explicit PeakFilterDlg(QWidget *parent = 0);
    ~PeakFilterDlg();
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
    SharpnessKind m_SharpnessKind;
private slots:
    void on_radioButtonErosion_clicked();

    void on_radioButtonDilate_clicked();

    void on_btnNumSub_clicked();

    void on_btnNumAdd_clicked();

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::PeakFilterDlg *ui;
    PEAK_A_MODEL_CFG m_a_cfg;
    PEAK_B_MODEL_CFG m_b_cfg;
};

#endif // PEAKFILTERDLG_H
