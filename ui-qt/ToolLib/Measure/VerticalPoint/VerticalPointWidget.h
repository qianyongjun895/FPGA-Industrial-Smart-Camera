#ifndef VERTICALPOINTWIDGET_H
#define VERTICALPOINTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "TaskStepGlobal.h"
#include "PixelConvert.h"
#include "TaskRstGlobal.h"
#include "StrokePointGlobal.h"

#define VGA_WIDTH 640
#define VGA_HEIGHT 480
namespace Ui {
class VerticalPointWidget;
}

class VerticalPointWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VerticalPointWidget(QWidget *parent = 0);
    ~VerticalPointWidget();

    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();
    QPoint Get_Image_Pos();
private slots:
    void PointTaskChangeSlot(int index);
    void LineTaskChangeSlot(int index);
    void PointResultChangeSlot(int index);
    void LineResultChangeSlot(int index);
private:
    Ui::VerticalPointWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;
    void InitData(int i_step_index);
    int m_i_load_first;
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    QString InitPointCombobox(int TaskIndex, int id);
    QString InitLineCombobox(int TaskIndex, int id);
    void GetRefPara(int ref_step, int ref_result, QPoint *point);
};


#endif // VERTICALPOINTWIDGET_H






