#ifndef L2LDISTANCEWIDGET_H
#define L2LDISTANCEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QComboBox>
#include <QTimer>
#include "TaskStepGlobal.h"
#include "PixelConvert.h"
#include "TaskRstGlobal.h"
#include "ParallelLinesDistGlobal.h"

#define VGA_WIDTH 640
#define VGA_HEIGHT 480

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);
typedef QString (*Fun_GetRangeNum)();
typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);

namespace Ui {
class L2LDistanceWidget;
}

class L2LDistanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit L2LDistanceWidget(QWidget *parent = 0);
    ~L2LDistanceWidget();
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
    void on_radioButton_pix_clicked();
    void on_radioButton_phy_clicked();
    void on_btnCalculation_clicked();
    void CalcTimerSlot();



private:
    Ui::L2LDistanceWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;//
    int pix_phy_flag;
    QLibrary m_keyBoard_Lib;
    int m_line1_rst_offset;
    int m_line2_rst_offset;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;
    int Calc_rst_flag;//当前是否是计算的结果

    void InitData(int i_step_index);
    QString InitLineCombobox(int TaskIndex, int id);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    void LoadKeyBoardLib();
    int SetRangetoLib();
    void InitRangeData();
    void LoadLearnLib();
    void LineResulChangetSlot(int task_index, QComboBox *mCom, QLine *line);
};

#endif // L2LDISTANCEWIDGET_H
