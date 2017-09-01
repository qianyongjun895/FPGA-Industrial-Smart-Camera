/**
  * @file  [WHMeasureWidget.h]
  * @brief  WHMeasureWidget
  * @author  <dgq>
  * @date  <2017/7/13>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef WHMEASUREWIDGET_H
#define WHMEASUREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QLineEdit>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "PixelConvert.h"
#include "MapGlobal.h"

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();
typedef QString (*Fun_GetNumString)();

typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

#define THRESHOLD_LOW   0 //下门限
#define THRESHOLD_HIGH  1 //上门限
#define VGA_WIDTH 640 //图象显示区域的宽度
#define VGA_HEIGHT 480 //图像显示区域的高度

namespace Ui {
class WHMeasureWidget;
}

class WHMeasureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WHMeasureWidget(QWidget *parent = 0);
    ~WHMeasureWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();

private slots:
    void CalcTimerSlot();

    void on_btnCalculation_clicked();

//    void on_comboBoxLineStep_currentIndexChanged(int index);
//    void on_comboBoxLineIndex_activated(int index);
    void on_btnMoveUp_pressed();
    void on_btnMoveDown_pressed();
    void on_btnMoveLeft_pressed();
    void on_btnMoveRight_pressed();

    void on_radioButton_phy_clicked();
    void on_radioButton_pix_clicked();

    void GetCurrentTime();
    void LinePosChangeSlot(int x, int y);
protected:
    bool eventFilter(QObject *watched, QEvent *event);


private:
    Ui::WHMeasureWidget *ui;
    QLabel *m_label;
    int m_step_index;//当前步骤索引
    MAP_INPUT_PARAM *pInputPara;
    int m_i_load_first;
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;
    int Calc_rst_flag;//当前是否计算的结果
    QTime startTime;
    QTime stopTime;
    int pix_phy_flag;

    void InitData();
    void LoadKeyBoardLib();
    void LoadLearnLib();
    QString InitLineCombobox(int TaskIndex, int id);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
//    void InitComboBox(int i_step_index);
    int Set_Range_To_Ram();
    void RangeInputPro(QLineEdit *pEditMax, QLineEdit *pEditMin, QString calc_value, int flag);

    void SetBtnRepeatParam(QToolButton *btn);
    void InitRangeData();
};

#endif // WHMEASUREWIDGET_H
