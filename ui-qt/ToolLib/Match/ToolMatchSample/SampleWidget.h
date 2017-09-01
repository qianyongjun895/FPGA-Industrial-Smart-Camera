#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "tool_testGlobal.h"
#include "../BaseStruct.h"

namespace Ui {
class SampleWidget;
}

class SampleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SampleWidget(QWidget *parent = 0);
    ~SampleWidget();

    QPoint Get_Image_Pos();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();
    void Get_Result_From_Ram();

private slots:

private:
    Ui::SampleWidget *ui;
    QLabel *m_label;
    TOOLTEST_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData();
};

#endif // SAMPLEWIDGET_H
