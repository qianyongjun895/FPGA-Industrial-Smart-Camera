#include <QDebug>
#include "IoJumpWidget.h"
#include "ui_IoJumpWidget.h"
#include <QMessageBox>
#include "LinkDataGlobal.h"

IoJumpWidget::IoJumpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IoJumpWidget)
{
    ui->setupUi(this);
}

IoJumpWidget::~IoJumpWidget()
{
    delete ui;
}

void IoJumpWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (IO_JUMP_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->io1_step_index = 0;
        pInputPara->io2_step_index = 0;
        pInputPara->io_enable_bitmask = 0;
        pInputPara->io1_trigger_mode = 0;
        pInputPara->io2_trigger_mode = 0;
    }
    InitData(i_step_index);
}


int IoJumpWidget::Set_Parameter_To_Ram()
{
    if(ui->checkBoxIO1->isChecked())
    {
        if(ui->checkBoxIO2->isChecked())
        {
            pInputPara->io_enable_bitmask = 3;
            SetIO1TriggerMode();
            SetIO2TriggerMode();
        }else
        {
            pInputPara->io_enable_bitmask = 1;
            SetIO1TriggerMode();
        }
    }else
    {
        if(ui->checkBoxIO2->isChecked())
        {
            pInputPara->io_enable_bitmask = 2;
            SetIO2TriggerMode();
        }else
        {
            pInputPara->io_enable_bitmask = 0;
        }
    }
    int io1_step;
    int io2_step;
    io1_step = atoi(ui->comboBoxIO1Jump->currentText().toStdString().c_str());
    io2_step = atoi(ui->comboBoxIO2Jump->currentText().toStdString().c_str());

    pInputPara->io1_step_index = io1_step;
    pInputPara->io2_step_index = io2_step;
    return 1;

}

//设置io1触发模式
void IoJumpWidget::SetIO1TriggerMode()
{
    if(ui->radioButtonIO1Raise->isChecked())
    {
        pInputPara->io1_trigger_mode = RISE_EDGE_TRIGGER;
    }else if(ui->radioButtonIO1Fall->isChecked())
    {
        pInputPara->io1_trigger_mode = FALL_EDGE_TRIGGER;
    }else if(ui->radioButtonIO1High->isChecked())
    {
        pInputPara->io1_trigger_mode = HIGH_LEVEL_TRIGGER;
    }else if(ui->radioButtonIO1Low->isChecked())
    {
        pInputPara->io1_trigger_mode = LOW_LEVEL_TRIGGER;
    }

}
//设置io2触发模式
void IoJumpWidget::SetIO2TriggerMode()
{
    if(ui->radioButtonIO2Raise->isChecked())
    {
        pInputPara->io2_trigger_mode = RISE_EDGE_TRIGGER;
    }else if(ui->radioButtonIO2Fall->isChecked())
    {
        pInputPara->io2_trigger_mode = FALL_EDGE_TRIGGER;
    }else if(ui->radioButtonIO2High->isChecked())
    {
        pInputPara->io2_trigger_mode = HIGH_LEVEL_TRIGGER;
    }else if(ui->radioButtonIO2Low->isChecked())
    {
        pInputPara->io2_trigger_mode = LOW_LEVEL_TRIGGER;
    }

}

void IoJumpWidget::InitData(int i_step_index)
{
    unsigned int task_cnt = GetTaskStepCount();
    char taskName[40];
    unsigned int task_type;
    for(unsigned int i = 0; i < task_cnt; i ++)
    {
        if(i == m_step_index-1)
        {
            continue;
        }
        if(Task_Step_Type_ID_Get(i+1, &task_type) == 0)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                if(i > i_step_index - 1)
                {
                    ui->comboBoxIO1Jump->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                    ui->comboBoxIO2Jump->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                }
            }
        }
    }
    ui->groupBoxIO1->setEnabled(false);
    ui->groupBoxIO2->setEnabled(false);
    ui->radioButtonIO1Raise->setChecked(true);
    ui->radioButtonIO2Raise->setChecked(true);
    unsigned int io_enable_bitmask = pInputPara->io_enable_bitmask;
    IniIoEnableBitmask(io_enable_bitmask);
    unsigned int io1_trigger_mode = pInputPara->io1_trigger_mode;
    IniIo1TriggerMode(io1_trigger_mode);
    unsigned int io2_trigger_mode = pInputPara->io2_trigger_mode;
    IniIo2TriggerMode(io2_trigger_mode);
    int io1_step_index = pInputPara->io1_step_index;
    int io2_step_index = pInputPara->io2_step_index;

    for(int i = 0; i< ui->comboBoxIO1Jump->count();i++)
    {
        QString strTask_io1 = ui->comboBoxIO1Jump->itemText(i);
        if(atoi(strTask_io1.toStdString().c_str()) == io1_step_index)
        {
            ui->comboBoxIO1Jump->setCurrentIndex(i);
        }
    }
    for(int i = 0; i< ui->comboBoxIO2Jump->count();i++)
    {
        QString strTask_io2 = ui->comboBoxIO2Jump->itemText(i);
        if(atoi(strTask_io2.toStdString().c_str()) == io2_step_index)
        {
            ui->comboBoxIO2Jump->setCurrentIndex(i);
        }
    }
}

void IoJumpWidget::IniIoEnableBitmask(unsigned int ioEnableBitmask)
{
    switch (ioEnableBitmask) {
    case 0:
        ui->groupBoxIO1->setEnabled(false);
        ui->groupBoxIO2->setEnabled(false);
        ui->checkBoxIO1->setChecked(false);
        ui->checkBoxIO2->setChecked(false);
        break;
    case 1:
        ui->groupBoxIO1->setEnabled(true);
        ui->groupBoxIO2->setEnabled(false);
        ui->checkBoxIO1->setChecked(true);
        ui->checkBoxIO2->setChecked(false);
        break;
    case 2:
        ui->groupBoxIO1->setEnabled(false);
        ui->groupBoxIO2->setEnabled(true);
        ui->checkBoxIO1->setChecked(false);
        ui->checkBoxIO2->setChecked(true);
        break;
    case 3:
        ui->groupBoxIO1->setEnabled(true);
        ui->groupBoxIO2->setEnabled(true);
        ui->checkBoxIO1->setChecked(true);
        ui->checkBoxIO2->setChecked(true);
        break;
    default:
        ui->groupBoxIO1->setEnabled(false);
        ui->groupBoxIO2->setEnabled(false);
        ui->checkBoxIO1->setChecked(false);
        ui->checkBoxIO2->setChecked(false);
        break;
    }
}

void IoJumpWidget::IniIo1TriggerMode(unsigned int io1_trigger_mode)
{
    switch (io1_trigger_mode) {
    case RISE_EDGE_TRIGGER:
        ui->radioButtonIO1Raise->setChecked(true);
        break;
    case FALL_EDGE_TRIGGER:
        ui->radioButtonIO1Fall->setChecked(true);
        break;
    case HIGH_LEVEL_TRIGGER:
        ui->radioButtonIO1High->setChecked(true);
        break;
    case LOW_LEVEL_TRIGGER:
        ui->radioButtonIO1Low->setChecked(true);
        break;
    default:
        break;
    }
}

void IoJumpWidget::IniIo2TriggerMode(unsigned int io2_trigger_mode)
{
    switch (io2_trigger_mode) {
    case RISE_EDGE_TRIGGER:
        ui->radioButtonIO2Raise->setChecked(true);
        break;
    case FALL_EDGE_TRIGGER:
        ui->radioButtonIO2Fall->setChecked(true);
        break;
    case HIGH_LEVEL_TRIGGER:
        ui->radioButtonIO2High->setChecked(true);
        break;
    case LOW_LEVEL_TRIGGER:
        ui->radioButtonIO2Low->setChecked(true);
        break;
    default:
        break;
    }
}

void IoJumpWidget::on_comboBoxIO1Jump_activated(int index)
{

}

void IoJumpWidget::on_comboBoxIO2Jump_activated(int index)
{

}

void IoJumpWidget::on_checkBoxIO1_clicked()
{
    if(ui->checkBoxIO1->isChecked())
    {
        ui->groupBoxIO1->setEnabled(true);
    }else
    {
        ui->groupBoxIO1->setEnabled(false);
    }

}

void IoJumpWidget::on_checkBoxIO2_clicked()
{
    if(ui->checkBoxIO2->isChecked())
    {
        ui->groupBoxIO2->setEnabled(true);
    }else
    {
        ui->groupBoxIO2->setEnabled(false);
    }
}
