#ifndef MULTIPOINTSDEMARCATE_H
#define MULTIPOINTSDEMARCATE_H

#include <QDialog>
#include <QKeyEvent>
#include "sszn_basic.h"
#include "MultipointDemarcateImageLabel.h"
#include "MultipointDemarcate.h"
#include "BusinessData/InterfaceLib/KeyBoardLib.h"

namespace Ui {
class MultipointsDemarcate;
}

class MultipointsDemarcate : public QDialog
{
    Q_OBJECT

public:
    explicit MultipointsDemarcate(QWidget *parent = 0);
    ~MultipointsDemarcate();

    int ParamDataInit(int paramIndex);
    void SetParamIndex(int paramIndex);
    void SetCurRobotID(int id);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void ShowCurPointCoordinate(QPoint &curPoint);
    void CurPointIndexChangedSlot(int curIndex);
    void UpdateCoordinateTableSlot();

    void on_btnQuit_clicked();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_btnPointNumInc_clicked();

    void on_btnPointNumDec_clicked();

    void on_btnMoveUp_clicked();

    void on_btnMoveDown_clicked();

    void on_btnMoveLeft_clicked();

    void on_btnMoveRight_clicked();

    void on_btnCalc_clicked();

    void on_tableWidgetPhysical_cellClicked(int row, int column);

//    void on_btnSave_clicked();

    void on_btnImportTestData_clicked();

    void on_comboBox_CameraInstallMode_currentIndexChanged(int index);

    void on_comboBox_PointStep_currentIndexChanged(int index);

    void on_comboBox_LineStep_currentIndexChanged(int index);

    void on_comboBox_PointResult_currentIndexChanged(int index);

    void on_comboBox_LineResult_currentIndexChanged(int index);

    void on_btnClearAllData_clicked();

    void on_btnStartDemarcate_clicked();

    void on_btnDeleteLastOne_clicked();

    void on_btnCenterAxisR_clicked();

    void on_btnDemarcateData_clicked();

    void on_btnGetOnePointAxisR_clicked();

    void on_btnClearAllDataAxisR_clicked();

    void on_btnDeleteLastOneAxisR_clicked();

    void on_rBtnArmPicDirSame_clicked();

    void on_rBtnArmPicDirReverse_clicked();

private:
    Ui::MultipointsDemarcate *ui;
    MultipointDemarcateImageLabel *m_image_label;
    KeyBoardLib m_KeyBoardLib;
    int m_auto_repeat_count; // 长按计数
    int m_self_inc; // 长按自增长值
    POINT_F phy_points[9];    
    QPoint m_real_point[9]; // 真实像素坐标(显示用)
    int param_index; // 参数索引 0:表示新参数
    HOMO_T m_homo;
//    int homo_calc_flag; // 标定参数计算标志 0:失败 1:成功
    unsigned int m_point_step;
    unsigned int m_point_result;
    unsigned int m_line_step;
    unsigned int m_line_result;
    int m_robot_id;
    float m_theta;
    float m_sub_theta[9];
    POINT_F ccc_point[3]; // 用于计算R轴中心的三个点(AGV模式)
    int m_arm_pic_dir;

    void SetTablePixelData(int row, QPoint& pixPoint);
    void SetTablePhyicalData(int row, POINT_F &phyPoint);    
    void SetTablePixelDataAxisR(int row, QPoint& pixPoint);
    void SetTableRealPixelDataAxisR(int row, POINT_F& realPixPoint);
    void ClearTablePixelDataAxisR(int row);
    void PointsParamAdjustEnable(bool bValue);
    void SeleIncValuePro();
    void GetPhyDataFromTable();
    void CameraInstallModeComboboxSet(int installMode);
    void AgvLinkInfoComboboxInit();
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    void SetButtonStyle(QPushButton *pre, QPushButton *current);
    void ShowAgvPrivateBtn(bool bValue);
    void RbtnArmPicDirInit(int armPicDir);
};

#endif // MULTIPOINTSDEMARCATE_H
