#include "RunStatistics.h"
#include "ui_RunStatistics.h"
#include "QMessageBox"

RunStatistics::RunStatistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunStatistics)
{
    ui->setupUi(this);

    ui->tableWidget_TaskRunInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_TaskRunInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

RunStatistics::~RunStatistics()
{
    delete ui;
}

void RunStatistics::on_btnClear_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("确定清空之前的统计信息?"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {

        int i = 0;
        int row = ui->tableWidget_TaskRunInfo->rowCount();
        for(i = 0; i < row;i++)
        {
            OUTPUT_COMMON_PARAM *pData =  Task_Step_Output_Common_Para_Get(i+1);
            memset(pData,0,sizeof(OUTPUT_COMMON_PARAM));
            ui->tableWidget_TaskRunInfo->setItem(i,1,new QTableWidgetItem("0"));
            ui->tableWidget_TaskRunInfo->setItem(i,2,new QTableWidgetItem("0"));
            ui->tableWidget_TaskRunInfo->setItem(i,3,new QTableWidgetItem("0"));
            ui->tableWidget_TaskRunInfo->setItem(i,4,new QTableWidgetItem("0"));
            ui->tableWidget_TaskRunInfo->setItem(i,5,new QTableWidgetItem("0"));
        }
    }
}


/**
 * @brief RunInfoDialog::InitTable
 * @ 初始化列表
 */
void RunStatistics::InitTable(QStringList task_list)
{
    ui->tableWidget_TaskRunInfo->setRowCount(task_list.count());
    int i = 0;
    for(i = 0; i < task_list.count();i++)
    {
        OUTPUT_COMMON_PARAM *pData =  Task_Step_Output_Common_Para_Get(i+1);
        ui->tableWidget_TaskRunInfo->setItem(i,0,new QTableWidgetItem(task_list[i]));
        ui->tableWidget_TaskRunInfo->setItem(i,1,new QTableWidgetItem(QString::number(pData->OK_count)));
        ui->tableWidget_TaskRunInfo->setItem(i,2,new QTableWidgetItem(QString::number(pData->NG_count)));
        ui->tableWidget_TaskRunInfo->setItem(i,3,new QTableWidgetItem(QString::number(pData->step_cost_time)));
        if(pData->OK_count != 0)
        {
            ui->tableWidget_TaskRunInfo->setItem(i,4,new QTableWidgetItem(QString::number(pData->total_ok_cost_time/pData->OK_count)));
        }
        else
        {
            ui->tableWidget_TaskRunInfo->setItem(i,4,new QTableWidgetItem(QString::number(pData->total_ok_cost_time,'f',3)));
        }
        if(pData->NG_count != 0)
        {
            ui->tableWidget_TaskRunInfo->setItem(i,5,new QTableWidgetItem(QString::number(pData->total_ng_cost_time/pData->NG_count)));
        }
        else
        {
            ui->tableWidget_TaskRunInfo->setItem(i,5,new QTableWidgetItem(QString::number(pData->total_ng_cost_time,'f',3)));
        }

    }
}

void RunStatistics::on_btnQuite_clicked()
{
    QDialog::accept();
}
