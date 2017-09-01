#include "ListWidgetIOOutputItem.h"
#include "ui_ListWidgetIOOutputItem.h"
#include "IOPortSelectDialog.h"
#include <stdio.h>
#include "TaskStepGlobal.h"
ListWidgetIOOutputItem::ListWidgetIOOutputItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidgetIOOutputItem)
{
    ui->setupUi(this);
    OK_IO_Port = -1;
    NG_IO_Port = -1;
    ui->OKIOOutputProtEdit->installEventFilter(this);
    ui->NGIOOutputProtEdit->installEventFilter(this);
}

ListWidgetIOOutputItem::~ListWidgetIOOutputItem()
{
    ui->OKIOOutputProtEdit->removeEventFilter(this);
    ui->NGIOOutputProtEdit->removeEventFilter(this);
    delete ui;
}


void ListWidgetIOOutputItem::SetLabelText(QString str)
{
    ui->TaskNamelabel->setText(str);
    QString task_index_string = str.split(".").at(0);
    unsigned int  task_index = task_index_string.toUInt();
    if(task_index < TS_MAX_NUM){
        int OK_index = Task_Step_OK_IO_Output_Index_Get(task_index);
        if(OK_index > 0 && OK_index < 16){
            ui->OKIOOutputProtEdit->setText("IO"+QString::number(OK_index));
        }else if(OK_index == 0){
            ui->OKIOOutputProtEdit->setText("NULL");
        }

        int NG_index = Task_Step_NG_IO_Output_Index_Get(task_index);
        if(NG_index > 0 && NG_index < 16){
            ui->NGIOOutputProtEdit->setText("IO"+QString::number(NG_index));
        }else if(NG_index == 0){
            ui->NGIOOutputProtEdit->setText("NULL");
        }
    }
}

bool ListWidgetIOOutputItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->OKIOOutputProtEdit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            IOPortSelectDialog* dlg = new IOPortSelectDialog;
            dlg->SetOKOrNGFlag(1);
            dlg->SetModel(Model_Flag, NG_IO_Port);
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                OK_IO_Port = dlg->GetSelectPortNumber();
                QString task_index_string = ui->TaskNamelabel->text().split(".").at(0);
                unsigned int  task_index = task_index_string.toUInt();
                Task_Step_OK_IO_Output_Index_Set(task_index, OK_IO_Port);
                ((QLineEdit*)watched)->setText(dlg->GetSelectString());
            }
        }
    }
    if(watched == ui->NGIOOutputProtEdit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            IOPortSelectDialog* dlg = new IOPortSelectDialog;
            dlg->SetOKOrNGFlag(0);
            dlg->SetModel(Model_Flag, OK_IO_Port);
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                NG_IO_Port = dlg->GetSelectPortNumber();
                QString task_index_string = ui->TaskNamelabel->text().split(".").at(0);
                unsigned int  task_index = task_index_string.toUInt();
                Task_Step_NG_IO_Output_Index_Set(task_index, NG_IO_Port);
                ((QLineEdit*)watched)->setText(dlg->GetSelectString());
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
