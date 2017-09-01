/**
  * @file  [SkeletonThresholdDlg.h]
  * @brief  SkeletonThresholdDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef SKELETONTHRESHOLDDLG_H
#define SKELETONTHRESHOLDDLG_H

#include <QDialog>
#include <QTime>
#include "AcceCommon.h"
namespace Ui {
class SkeletonThresholdDlg;
}
/**
  * @class  <SkeletonThresholdDlg>  [SkeletonThresholdDlg.h]  [SkeletonThresholdDlg]
  * @brief  轮廓匹配预处理模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class SkeletonThresholdDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SkeletonThresholdDlg(QWidget *parent = 0);
    ~SkeletonThresholdDlg();
    int m_step;
    int m_task_id;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据
     */
    void InitData();
private slots:
    void on_btnOk_clicked();
    void on_btnQuit_clicked();
    void on_horizontalSliderUpSobel_valueChanged(int value);
    void on_horizontalSliderUpSobel_sliderPressed();
    void on_horizontalSliderUpSobel_sliderReleased();
    void on_btnUpSubSobel_clicked();
    void on_btnAddSobel_clicked();
signals:
    void SignalMatchModelCfgPoints(int enable);
private:
    Ui::SkeletonThresholdDlg *ui;
    int m_ifirst;
    QTime stopTime;
    QTime startTime;
    MATCH_MODEL_CFG m_cfg;
    /**
     * @brief SetSobelDataToLib
     * @return 返回操作是否超时 1超时
     * @author szj
     * @date 2017/05/08
     * @note 操作是否超时
     */
    int IsTimeOut();
    /**
     * @brief SetSobelDataToLib
     * @author szj
     * @date 2017/05/08
     * @note 保存Sobel参数
     */
    void SetSobelDataToLib();
};

#endif // SKELETONTHRESHOLDDLG_H
