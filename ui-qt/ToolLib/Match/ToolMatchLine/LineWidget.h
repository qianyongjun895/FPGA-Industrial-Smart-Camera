#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>
#include "FWMatchLineLabel.h"
#include <QLabel>
#include <QTimer>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "PixelConvert.h"
#include "LineGlobal.h"
#include "../BaseStruct.h"
#define VGA_WIDTH 640
#define VGA_HEIGHT 480
#define SUB_PIXEL_FACTOR	16
#define PIXEL_THAN_30W  1
#define PIXEL_THAN_130W 2
#define PIXEL_THAN_500W 4
#define X_Y_CONVERT_SUB2UI(point) ((point)/(PIXEL_THAN_30W*SUB_PIXEL_FACTOR))
namespace Ui {
class LineWidget;
}

class LineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineWidget(QWidget *parent = 0);
    ~LineWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();
private slots:
    void Point1ChangeSlot(QPoint point1,int kind );
    void Point2ChangeSlot(QPoint point2,int kind );

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void on_btnPreLine_clicked();

    void on_btnNextLine_clicked();

    void on_btnLineSub_clicked();

    void on_btnLineAdd_clicked();

    void on_btnMoveUp_pressed();

    void on_btnMoveUp_released();

    void on_btnMoveDown_pressed();

    void on_btnMoveDown_released();

    void on_btnMoveLeft_pressed();

    void on_btnMoveLeft_released();

    void on_btnMoveRight_pressed();

    void on_btnMoveRight_released();
    void SubSensitivity();
    void AddSensitivity();
    void RangeDown();
    void RangeUp();
    void SubAngleLimit();
    void AddAngleLimit();

    void on_btnSubSensitivity_pressed();

    void on_btnSubSensitivity_released();

    void on_btnAddSensitivity_pressed();

    void on_btnAddSensitivity_released();

    void on_horizontalSliderSensitivity_sliderReleased();

    void on_btnRangeDown_pressed();

    void on_btnRangeDown_released();

    void on_btnRangeUp_pressed();

    void on_btnRangeUp_released();

    void on_horizontalSliderRange_sliderReleased();

    void on_btnSubAngleLimit_pressed();

    void on_btnSubAngleLimit_released();

    void on_btnAddAngleLimit_pressed();

    void on_btnAddAngleLimit_released();

    void on_horizontalSliderAngleLimit_sliderReleased();

    void on_radioButtonPositiveDir_clicked();

    void on_radioButtonNegativeDir_clicked();

    void on_radioButtonW2B_clicked();

    void on_radioButtonB2W_clicked();

    void on_horizontalSliderSensitivity_valueChanged(int value);

    void on_horizontalSliderRange_valueChanged(int value);

    void on_horizontalSliderAngleLimit_valueChanged(int value);

private:
    Ui::LineWidget *ui;
    QLabel *m_label;
    QPoint m_point1;
    QPoint m_point2;
    QPoint m_points1[20];
    QPoint m_points2[20];
    QLine m_line[20];
    int m_num;
    int m_step_index;//当前步骤索引
    int m_iPresstimes;
    QTimer *m_timer;
    LINE_INPUT_PARAM *pInputPara;
    LineParameter m_line_para[20];
    LINE_INPUT_PARAM m_line_input;


    void InitData();
    void InitNewAddControlData();
    void SetDataToLib();
    void SetDataToLibByIndex(int index);
    int GetStepValue();
    void GetLinePara(int index);
    void Vertical_Line_Paint(unsigned int sub_pixel_x, QLine *pOsd_line);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);

};

#endif // LINEWIDGET_H
