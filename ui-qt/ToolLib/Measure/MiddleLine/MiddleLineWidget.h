#ifndef MIDDLELINEWIDGET_H
#define MIDDLELINEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "TaskStepGlobal.h"
#include "PixelConvert.h"
#include "TaskRstGlobal.h"
#include "MiddleLineGlobal.h"

#define VGA_WIDTH 640
#define VGA_HEIGHT 480

namespace Ui {
class MiddleLineWidget;
}

class MiddleLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MiddleLineWidget(QWidget *parent = 0);
    ~MiddleLineWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    void Get_Result_From_Ram();
private slots:
    void Line1TaskChangeSlot(int index);
    void Line2TaskChangeSlot(int index);
    void Line1ResultChangeSlot(int index);
    void Line2ResultChangeSlot(int index);


private:
    Ui::MiddleLineWidget *ui;
    QLabel *m_label;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;//
    QString InitLineCombobox(int TaskIndex, int id);
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);
};


#endif // MIDDLELINEWIDGET_H
