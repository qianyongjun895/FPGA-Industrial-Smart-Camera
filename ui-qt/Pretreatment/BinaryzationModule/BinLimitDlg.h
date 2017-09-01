/**
  * @file  [BinLimitDlg.h]
  * @brief  BinLimitDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef BINLIMITDLG_H
#define BINLIMITDLG_H

#include <QDialog>
#include "AcceCommon.h"
namespace Ui {
class BinLimitDlg;
}
/**
  * @class  <BinLimitDlg>  [BinLimitDlg.h]  [BinLimitDlg]
  * @brief  二值化
  * @author  <szj>
  * @note
  * detailed  description
  */
class BinLimitDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BinLimitDlg(QWidget *parent = 0);
    ~BinLimitDlg();
    /**
     * @brief InitData
     * @author szj
     * @date 2017/05/08
     * @note 初始化二值化数据
     */
    void InitData();
    int m_task_id;
    int m_step;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;
private slots:

    void SubUpBin(int value =1);
    void AddUpbBin(int value =1);
    void SubDownBin(int value =1);
    void AddDownBin(int value =1);

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_checkBoxBinaryzationReverse_clicked();

    void on_btnUpSubBinaryzation_pressed();

    void on_btnUpSubBinaryzation_released();

    void on_btnAddUpBinaryzation_pressed();

    void on_btnAddUpBinaryzation_released();

    void on_horizontalSliderUpBin_valueChanged(int value);

    void on_btnSupDownBinaryzation_pressed();

    void on_btnSupDownBinaryzation_released();

    void on_btnAddDownBinaryzation_pressed();

    void on_btnAddDownBinaryzation_released();

    void on_horizontalSliderDownBin_valueChanged(int value);


    void on_btnAuto_clicked();

private:
    Ui::BinLimitDlg *ui;
    BW_MODEL_CFG m_bw_cfg;
    int m_First;
};

#endif // BINLIMITDLG_H
