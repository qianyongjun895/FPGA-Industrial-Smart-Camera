#include "ListWidgetIOTriggerItem.h"
#include "ui_ListWidgetIOTriggerItem.h"
#include "TaskStepGlobal.h"
#include <QMessageBox>
#include <QDebug>
ListWidgetIOTriggerItem::ListWidgetIOTriggerItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidgetIOTriggerItem)
{
    ui->setupUi(this);
    Ini_Flag = 1;
    ui->IOTriggerPortCbB->addItem(tr("IO1"));
    ui->IOTriggerPortCbB->addItem(tr("IO2"));

    ui->IOTriggerWayCbB->addItem(tr("上升沿"));
    ui->IOTriggerWayCbB->addItem(tr("下降沿"));
    ui->IOTriggerWayCbB->addItem(tr("高电平"));
    ui->IOTriggerWayCbB->addItem(tr("低电平"));
}

ListWidgetIOTriggerItem::~ListWidgetIOTriggerItem()
{
    delete ui;
}

void ListWidgetIOTriggerItem::SetTaskName(QString str)
{
    Ini_Flag = 1;
    ui->TaskNameCheckBox->setText(str);
    QString task_index_string = str.split(".").at(0);
    unsigned int task_index = task_index_string.toUInt();
    if(task_index >= TS_MAX_NUM){
        Ini_Flag = 0;
        return;
    }
    unsigned int Trigger_Type = 0;
    int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
    if(ret != 0){
        Ini_Flag = 0;
        return;
    }
    else if(Trigger_Type == IO_TRIGGER_TYPE){
        ui->TaskNameCheckBox->setChecked(true);
        ui->IOTriggerPortCbB->setEnabled(true);
        ui->IOTriggerWayCbB->setEnabled(true);
        unsigned short IO_Port = 0;
        unsigned short IO_Trigger_Type = 0;
        ret = Task_Step_Trigger_IO_Get(task_index, &IO_Port, &IO_Trigger_Type);
        if(ret == 0){
            ui->IOTriggerPortCbB->setCurrentIndex(IO_Port - 1);
            ui->IOTriggerWayCbB->setCurrentIndex(IO_Trigger_Type - 1);
        }
    }else{
        ui->IOTriggerPortCbB->setEnabled(false);
        ui->IOTriggerWayCbB->setEnabled(false);
    }
    Ini_Flag = 0;
}

void ListWidgetIOTriggerItem::on_TaskNameCheckBox_clicked()
{
    if(Ini_Flag == 1)
        return;
    QString task_index_string = ui->TaskNameCheckBox->text().split(".").at(0);
    unsigned int task_index = task_index_string.toUInt();
    if(task_index >= TS_MAX_NUM)
        return;

    if(ui->TaskNameCheckBox->isChecked())
    {
        unsigned int Trigger_Type = 0;
        int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
        if(ret != 0){
            return;
        }else if(Trigger_Type == CMD_TRIGGER_TYPE || Trigger_Type == CON_TRIGGER_TYPE){
            QMessageBox::about(NULL, tr("提示"), tr("该任务已有其他触发,无法设置IO触发!"));
            Ini_Flag = 1;
            ui->TaskNameCheckBox->setChecked(false);
            Ini_Flag = 0;
            return;
        }
        ret = Task_Step_Trigger_Type_Set(task_index, IO_TRIGGER_TYPE);
        if(ret != 0)
            return;
        ui->IOTriggerPortCbB->setEnabled(true);
        ui->IOTriggerWayCbB->setEnabled(true);
        SetTaskIOTriggerParam();
    }
    else
    {
        int ret = Task_Step_Trigger_Type_Set(task_index, NONE_TRIGGER_TYPE);
        if(ret != 0)
            return;
        ui->IOTriggerPortCbB->setEnabled(false);
        ui->IOTriggerWayCbB->setEnabled(false);
    }
}

void ListWidgetIOTriggerItem::SetTaskIOTriggerParam()
{
    QString task_index_string = ui->TaskNameCheckBox->text().split(".").at(0);
    unsigned int task_index = task_index_string.toUInt();
    if(task_index >= TS_MAX_NUM)
        return;
    Task_Step_Trigger_IO_Set(task_index, ui->IOTriggerPortCbB->currentIndex()+1, ui->IOTriggerWayCbB->currentIndex()+1);
}

void ListWidgetIOTriggerItem::on_IOTriggerWayCbB_currentIndexChanged(int index)
{
    if(Ini_Flag == 1)
        return;
    SetTaskIOTriggerParam();
}

void ListWidgetIOTriggerItem::on_IOTriggerPortCbB_currentIndexChanged(int index)
{
    if(Ini_Flag == 1)
        return;
    SetTaskIOTriggerParam();
}
