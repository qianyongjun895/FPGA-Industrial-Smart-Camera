#ifndef L2LANGLEWIDGET_H
#define L2LANGLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QTimer>
#include <QComboBox>
#include "TaskStepGlobal.h"
#include "PixelConvert.h"
#include "TaskRstGlobal.h"
#include "LinesAngleGlobal.h"


#define VGA_WIDTH 640
#define VGA_HEIGHT 480

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();
typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

namespace Ui {
class L2LAngleWidget;
}

class L2LAngleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit L2LAngleWidget(QWidget *parent = 0);
    ~L2LAngleWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void Line1TaskChangeSlot(int index);
    void Line2TaskChangeSlot(int index);
    void Line1ResultChangeSlot(int index);
    void Line2ResultChangeSlot(int index);
    void on_btnCalculation_clicked();

    void on_radioButtonAcuteAngel_clicked();
    void on_radioButtonObtuseAngle_clicked();

    void on_checkBox_AutoSet_windowIconChanged(const QIcon &icon);
    void CalcTimerSlot();

private:
    Ui::L2LAngleWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;//
    int m_angle_flag;
    QLibrary m_keyBoard_Lib;
    int m_line1_rst_offset;
    int m_line2_rst_offset;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;
    int Calc_rst_flag;//当前是否是计算的结果
    OSD_ARC m_arc;

    void InitData(int i_step_index);
    QString InitLineCombobox(int TaskIndex, int id);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    void LoadKeyBoardLib();
    int SetRangetoLib();
    void InitRangeData();
    void LineResulChangetSlot(int task_index, QComboBox *mCom, QLine *line);
    void LoadLearnLib();
    int ArcAngleGet(pOSD_ARC arc, LineParameter *pLine1Param, LineParameter *pLine2Param, L2L_ANGLE_RESULT *pAngleCalcRst);
    void GetMesureOsdData(int i_step, L2L_ANGLE_RESULT *rst);
};

#endif // L2LANGLEWIDGET_H
