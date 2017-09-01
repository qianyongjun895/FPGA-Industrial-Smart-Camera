/**
  * @file  [ContrastStrengthenDlg.h]
  * @brief  ContrastStrengthenDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef CONTRASTSTRENGTHENDLG_H
#define CONTRASTSTRENGTHENDLG_H

#include <QDialog>
#include <QTimer>
#include <stdbool.h>
#include "AcceCommon.h"

namespace Ui {
class ContrastStrengthenDlg;
}
/**
  * @class  <ContrastStrengthenDlg>  [ContrastStrengthenDlg.h]  [ContrastStrengthenDlg]
  * @brief  对比度增强
  * @author  <szj>
  * @note
  * detailed  description
  */
class ContrastStrengthenDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastStrengthenDlg(QWidget *parent = 0);
    ~ContrastStrengthenDlg();
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
private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void sendBlancedDataSlot();
    void on_radioButton_sixteen_clicked(bool checked);
    void on_radioButton_eight_clicked(bool checked);
    void on_radioButton_four_clicked(bool checked);
    void on_radioButton_two_clicked(bool checked);
    void on_btnMoveUp_pressed();

    void on_btnMoveDown_pressed();

    void on_btnMoveLeft_pressed();

    void on_btnMoveRight_pressed();

    void PointChangeSlot(int num, QPoint point);
    void on_btnMoveUp_released();

    void on_btnMoveDown_released();

    void on_btnMoveLeft_released();

    void on_btnMoveRight_released();

    void ClickTimerSlot();

    void on_radioButtonBasic_clicked();

    void on_radioButtonAdvanced_clicked();

    void on_btnSupPointSelect_pressed();

    void on_btnSupPointSelect_released();

    void on_btnAddPointSelect_pressed();

    void on_btnAddPointSelect_released();

    void on_btnSubPointY_pressed();

    void on_btnSubPointY_released();

    void on_btnAddPointY_pressed();

    void on_btnAddPointY_released();

    void AddPointSelect();
    void SubPointselect();
    void AddPointY();
    void SubPointY();
    void on_horizontalSliderPointY_valueChanged(int value);
    void on_horizontalSliderPointSelect_valueChanged(int value);

    void on_horizontalSliderPointSelect_sliderReleased();

    void on_horizontalSliderPointY_sliderReleased();

private:
    Ui::ContrastStrengthenDlg *ui;
    QVector<QPoint> m_Points;
    int m_smooth_mode;
    QTimer ClickTimer;
    int btn;//0:up 1:down 2:left 3:righr
    char m_gray_num[255];
    BALANCE_MODEL_CFG m_cfg;
    void GetGrayVt();
    /**
     * @brief SetDataToLib
     * @author szj
     * @date 2017/05/08
     * @note 保存数据
     */
    void SetDataToLib();
    void DealPicGray();
//    void IniData();
    /**
     * @brief IniAdvancedData
     * @author szj
     * @date 2017/05/08
     * @note 初始化数据(高级模式)
     */
    void IniAdvancedData();
    int iTimes;
    int m_x; //高级模式点x坐标
};

#endif // CONTRASTSTRENGTHENDLG_H
