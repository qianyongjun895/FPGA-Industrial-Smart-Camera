#ifndef IOJUMPWIDGET_H
#define IOJUMPWIDGET_H

#include <QWidget>
#include <QLabel>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "IoJumpGlobal.h"

#define RISE_EDGE_TRIGGER	1
#define FALL_EDGE_TRIGGER	2
#define HIGH_LEVEL_TRIGGER	3
#define LOW_LEVEL_TRIGGER	4
namespace Ui {
class IoJumpWidget;
}

class IoJumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IoJumpWidget(QWidget *parent = 0);
    ~IoJumpWidget();

    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();
private slots:

    void on_comboBoxIO1Jump_activated(int index);

    void on_comboBoxIO2Jump_activated(int index);

    void on_checkBoxIO1_clicked();

    void on_checkBoxIO2_clicked();

private:
    Ui::IoJumpWidget *ui;
    IO_JUMP_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    void InitData(int i_step_index);
    int m_i_load_first;//
    void IniIoEnableBitmask(unsigned int ioEnableBitmask);
    void IniIo1TriggerMode(unsigned int io1_trigger_mode);
    void IniIo2TriggerMode(unsigned int io2_trigger_mode);
    void SetIO1TriggerMode();
    void SetIO2TriggerMode();
};

#endif // IOJUMPWIDGET_H
