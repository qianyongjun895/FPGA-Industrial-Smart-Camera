#ifndef CONDJUMPWIDGET_H
#define CONDJUMPWIDGET_H

#include <QWidget>
#include <CondJumpGlobal.h>

namespace Ui {
class CondJumpWidget;
}

class CondJumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CondJumpWidget(QWidget *parent = 0);
    ~CondJumpWidget();

    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();

private slots:
    //void LinkComboBoxChangeSlot(int);
    //void AddTaskToJumpListSlot();
    void OKComboBoxChangeSlot(int);
    void NGComboBoxChangeSlot(int);
    void OKCheckBoxSlot();
    void NGCheckBoxSlot();

    void CheckButtonOKIO1Slot();
    void CheckButtonOKIO2Slot();
    void CheckButtonOKIO3Slot();
    void CheckButtonOKIO4Slot();

    void CheckButtonNGIO1Slot();
    void CheckButtonNGIO2Slot();
    void CheckButtonNGIO3Slot();
    void CheckButtonNGIO4Slot();
    //增加关联步骤列表数据
    void on_btnAdd_clicked();
    //删除关联步骤列表中的数据
    void on_btnDelete_clicked();
private:
    Ui::CondJumpWidget *ui;
    void *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;//
    int m_ok_io;
    int m_ng_io;


    int GetCorrelationStepNegation(unsigned int step);
    int SetCorrelationStepNegation(unsigned int step, unsigned int flag);
    int GetCorrelationStep(unsigned int step);
    void SetCorrelationStep(unsigned int bitmap, unsigned int step);
    void SetOKChecked(unsigned int IO_index);
    void SetNGChecked(unsigned int IO_index);
    int IsTaskStepInTable(QString StrTask);
};

#endif // CONDJUMPWIDGET_H
