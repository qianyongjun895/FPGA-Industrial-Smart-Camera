#include <QDebug>
#include "ToolEnableDialog.h"
#include "ui_ToolEnableDialog.h"
#include "ToolEnableItem.h"

ToolEnableDialog::ToolEnableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolEnableDialog)
{
    ui->setupUi(this);
}

ToolEnableDialog::~ToolEnableDialog()
{
    delete ui;
}

void ToolEnableDialog::on_okButton_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        TASK_STEP_HEADER *pHead = Task_Step_Head_Get(i+1);
        ToolEnableItem *tmpItem = static_cast<ToolEnableItem *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
        char enFlag = tmpItem->GetEnaFlag();
        pHead->step_exec_flag = enFlag;
    }
    QDialog::accept();
}

void ToolEnableDialog::InitList(QStringList task_list)
{
//    int i_task_count = GetTaskStepCount();
    if(task_list.count() > 0)
    {
        char enFlag = 0;
        int cnt = 0;
        for(int i = 0; i < task_list.count(); i++)
        {
            TASK_STEP_HEADER *pHead = Task_Step_Head_Get(i+1);

            ToolEnableItem *newItem = new ToolEnableItem;
            enFlag = pHead->step_exec_flag;
            if(enFlag == 1)
            {
                newItem->SetEnaFlag(false);
            }else if(enFlag == 0)
            {
                newItem->SetEnaFlag(true);
                cnt++;
            }
            newItem->SetTaskName(task_list[i]);
            QListWidgetItem *tmpItem = new QListWidgetItem;
            ui->listWidget->addItem(tmpItem);
            ui->listWidget->setItemWidget(tmpItem, (QWidget *)newItem);
            ui->listWidget->item(i)->setSizeHint(QSize(300,30));
        }
        if(cnt == ui->listWidget->count())
        {
            ui->checkBox_SelectAll->setChecked(true);
            ui->checkBox_SelectAll->setText(tr("全不选"));
        }
    }
}

void ToolEnableDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}



void ToolEnableDialog::on_checkBox_SelectAll_clicked()
{
    if(ui->checkBox_SelectAll->isChecked())
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            ToolEnableItem *tmpItem = static_cast<ToolEnableItem *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
            tmpItem->SetEnaFlag(true);
        }
        ui->checkBox_SelectAll->setText(tr("全不选"));
    }else
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            ToolEnableItem *tmpItem = static_cast<ToolEnableItem *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
            tmpItem->SetEnaFlag(false);
        }
        ui->checkBox_SelectAll->setText(tr("全选"));
    }
}

void ToolEnableDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ToolEnableItem *tmpItem = static_cast<ToolEnableItem *>(ui->listWidget->itemWidget(item));
    char enFlag = tmpItem->GetEnaFlag();
    if(enFlag == 1)
    {
        tmpItem->SetEnaFlag(true);
        int cnt= 0;
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            ToolEnableItem *iItem = static_cast<ToolEnableItem *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
            if(iItem->GetEnaFlag() == 0)
                cnt++;
        }
        if(cnt == ui->listWidget->count())
        {
            ui->checkBox_SelectAll->setChecked(true);
            ui->checkBox_SelectAll->setText(tr("全不选"));
        }
    }
    else
    {
        tmpItem->SetEnaFlag(false);
        ui->checkBox_SelectAll->setChecked(false);
        ui->checkBox_SelectAll->setText(tr("全选"));
    }
}
