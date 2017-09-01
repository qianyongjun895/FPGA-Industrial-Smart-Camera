/**
  * @file  [CptDlg.h]
  * @brief  CptDlg
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef CPTDLG_H
#define CPTDLG_H

#include <QDialog>
#include <QTime>
#include "AcceCommon.h"
namespace Ui {
class CptDlg;
}
/**
  * @class  <CptDlg>  [CptDlg.h]  [CptDlg]
  * @brief  预处理cpt模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class CptDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CptDlg(QWidget *parent = 0);
    ~CptDlg();
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note cpt模块初始化数据
     */
    void IniData();
    void SetAreaLimit();
    int m_task_id;
    int m_step;
    void *m_pre_ptr;
    void *pen;
private slots:
    void SlotUpdateXY();

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_radioButtonCmos_clicked();

    void on_radioButtonDDR_clicked();

    void on_btnSkeletonUp_pressed();

    void on_btnSkeletonDown_pressed();

    void on_btnSkeletonLeft_pressed();

    void on_btnSkeletonRight_pressed();

    void on_btnSkeletonUp_released();

    void on_btnSkeletonDown_released();

    void on_btnSkeletonLeft_released();

    void on_btnSkeletonRight_released();

    void on_checkBoxGray_clicked();

    void keyUp(int value = 1);
    void  KeyDown(int value =1);
    void KeyLeft(int value =1);
    void KeyRight(int value =1);

    void on_radioButtonBrightWay_clicked();

    void on_radioButtonRWay_clicked();

    void on_radioButtonGWay_clicked();

    void on_radioButtonBWay_clicked();

private:
    Ui::CptDlg *ui;
    int iLeftTopX;
    int iLeftTopY;
    int iBottomRightX;
    int iBottomRightY;
    int m_img_scale;
    int m_startY;
    int m_endY;
    CPT_MODEL_CFG m_cfg;
    /**
     * @brief SetLefTopXY
     * @param x 左上顶点x坐标
     * @param y 左上顶点y坐标
     * @author szj
     * @date 2017/05/08
     * @note 显示左顶点坐标
     */
    void SetLefTopXY(int x,int y);
    /**
     * @brief SetBottomRightXY
     * @param x 右下点x坐标
     * @param y 右下点y坐标
     * @author szj
     * @date 2017/05/08
     * @note 显示右下点坐标
     */
    void SetBottomRightXY(int x,int y);
    /**
     * @brief SetPreDataColor
     * @param bColor 1灰度 0彩色
     * @author szj
     * @date 2017/05/08
     * @note 设置cpt模快出图使能
     */
    void SetPreDataColor(int bColor);

};

#endif // CPTDLG_H
