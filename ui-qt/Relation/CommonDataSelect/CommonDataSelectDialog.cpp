#include "CommonDataSelectDialog.h"
#include "ui_CommonDataSelectDialog.h"
#include <QMessageBox>
#include "stdio.h"

#include "PublicLinkData.h"
CommonDataSelectDialog::CommonDataSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommonDataSelectDialog)
{
    ui->setupUi(this);
    connect(ui->listWidget_DataList,&QListWidget::doubleClicked,this,&CommonDataSelectDialog::on_btnOk_clicked);
}

CommonDataSelectDialog::~CommonDataSelectDialog()
{
    delete ui;
}

void CommonDataSelectDialog::InitTaskList(int type, int current_index)
{

    data_type = type;
    int i = 0;
    QString Task_Str;
    for(i = 0; i < current_index-1; i++)
    {
        if(data_type == 0 || data_type ==1)
        {
            Task_Str = PublicLinkData::GetPublicLinkInstance()->GetLinkDataPointTaskStr(i+1);
        }
        else
        {
            Task_Str = PublicLinkData::GetPublicLinkInstance()->GetLinkDataAngleString(i+1);
        }

        if(Task_Str!= QString::null)
        {
            ui->listWidget_TaskList->addItem(QString::number(i+1).append(".").append(Task_Str));
        }
    }

    ui->listWidget_TaskList->setCurrentRow(0);
}

void CommonDataSelectDialog::on_btnOk_clicked()
{
    if(ui->listWidget_TaskList->count()!=0 &&ui->listWidget_DataList->count()!=0)
    {
        m_data_list = ui->listWidget_TaskList->currentItem()->text()+";"+ui->listWidget_DataList->currentItem()->text();
        QDialog::accept();
    }
    else
    {
        QMessageBox::warning(NULL, tr("警告"), tr("请选择关联数据"), QMessageBox::Ok);
        return;
    }
}

void CommonDataSelectDialog::on_btnCancel_clicked()
{
    m_data_list = QString::null;
    QDialog::reject();
}

void CommonDataSelectDialog::on_listWidget_TaskList_currentTextChanged(const QString &currentText)
{
    m_task = currentText;
    QStringList strdata;
    int m_task_index = m_task.split(".")[0].toInt();
    if(data_type == 0)
        strdata = PublicLinkData::GetPublicLinkInstance()->GetLinkDataXResultStr(m_task_index);
    if(data_type == 1)
        strdata = PublicLinkData::GetPublicLinkInstance()->GetLinkDataYResultStr(m_task_index);
    if(data_type == 2)
        strdata = PublicLinkData::GetPublicLinkInstance()->GetLinkDataAngleStr(m_task_index);
    int i = 0;
    ui->listWidget_DataList->clear();
    ui->btnOk->setEnabled(false);
    for(i = 0; i < strdata.count(); i++)
    {
        ui->listWidget_DataList->addItem(QString::number(i+1)+"."+strdata[i]);
    }
}

void CommonDataSelectDialog::on_listWidget_DataList_itemClicked(QListWidgetItem *item)
{
    QString iresult = item->text();
    m_data_list = m_task + ";" + iresult;
    ui->btnOk->setEnabled(true);
}
