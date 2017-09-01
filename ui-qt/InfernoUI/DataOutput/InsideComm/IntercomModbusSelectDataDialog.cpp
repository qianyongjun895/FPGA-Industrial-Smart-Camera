#include "IntercomModbusSelectDataDialog.h"
#include "ui_IntercomModbusSelectDataDialog.h"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include "TaskRstGlobal.h"
IntercomModbusSelectDataDialog::IntercomModbusSelectDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntercomModbusSelectDataDialog)
{
    ui->setupUi(this);
    task_pre_index = 0;
    detail_pre_index = 0;
    task_type = 0;
    multi_flag = 0;
    IniData();
    ui->pushButton_OK->setDisabled(true);
}

IntercomModbusSelectDataDialog::~IntercomModbusSelectDataDialog()
{
    delete ui;
}

void IntercomModbusSelectDataDialog::IniData()
{
    char taskName[40];
    ui->tableWidget_task->setRowCount(GetTaskStepCount());
    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        if(Task_Step_Type_ID_Get(i+1, &task_type) == 0)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                InitTaskListTableWidget(i, QString::number(i+1) +"."+ QString::fromUtf8(taskName));
            }
        }
    }
    ui->tableWidget_task->setCurrentCell(0,0);
}

void IntercomModbusSelectDataDialog::InitTaskListTableWidget(int index, QString taskName)
{
    ui->tableWidget_task->horizontalHeader()->setVisible(false);
    ui->tableWidget_task->setShowGrid(false);
    ui->tableWidget_task->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_task->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_task->setColumnCount(2);
    ui->tableWidget_task->setColumnWidth(0,170);
    ui->tableWidget_task->setColumnWidth(1,20);
    ui->tableWidget_task->setItem(index, 0, new QTableWidgetItem(taskName));
    ui->tableWidget_task->setCurrentCell(0,0);
}

void IntercomModbusSelectDataDialog::InitTaskResultListTableWidget(int index, QString taskResult)
{
    ui->tableWidget_detail->setRowCount(index+1);
    ui->tableWidget_detail->horizontalHeader()->setVisible(false);
    ui->tableWidget_detail->verticalHeader()->setVisible(false);
    ui->tableWidget_detail->setShowGrid(false);
    ui->tableWidget_detail->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_detail->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_detail->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_detail->setColumnCount(2);
    ui->tableWidget_detail->setColumnWidth(0,170);
    ui->tableWidget_detail->setColumnWidth(1,20);
    ui->tableWidget_detail->setItem(index, 0, new QTableWidgetItem(taskResult));
    ui->tableWidget_detail->setItem(index, 1, new QTableWidgetItem(""));
    ui->tableWidget_detail->setCurrentCell(0,0);
}

void IntercomModbusSelectDataDialog::InitTaskDataListTableWidget(int index, QString taskResult)
{
    ui->tableWidget_data->setRowCount(index+1);
    ui->tableWidget_data->horizontalHeader()->setVisible(false);
    ui->tableWidget_data->verticalHeader()->setVisible(false);
    ui->tableWidget_data->setShowGrid(false);
    ui->tableWidget_data->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_data->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_data->setColumnCount(1);
    ui->tableWidget_data->setColumnWidth(0,190);
    ui->tableWidget_data->setItem(index, 0, new QTableWidgetItem(taskResult));
    ui->tableWidget_data->setCurrentCell(0,0);
}

void IntercomModbusSelectDataDialog::on_tableWidget_task_cellClicked(int row, int column)
{
    int curr_row = 0;
    char TaskResult[100];
    ui->tableWidget_task->setItem(task_pre_index, 1, new QTableWidgetItem(""));
    ui->tableWidget_task->setItem(row, 1, new QTableWidgetItem("▶"));
    task_pre_index = row;
    ui->tableWidget_detail->clear();
    ui->tableWidget_detail->setRowCount(0);

    QString TaskName = ui->tableWidget_task->item(row, 0)->text();
    QStringList TaskNameList = TaskName.split(".");
    QString TaskIndex = TaskNameList.at(0);
    int ret = Task_Step_Type_ID_Get(TaskIndex.toInt(), &task_type);
    if(ret == 0)
    {
        for(int index = 0; ; index++)
        {
            if(Get_Multi_Result_Task_Flag(task_type) == -1)
            {
                multi_flag = 0;
                memset(TaskResult, 0, 100);
                ret =  Get_Task_Result_String(Modbus_index, task_type, -1, index, TaskResult);
                if(ret == 1)
                {
                    InitTaskResultListTableWidget(curr_row, QString::number(curr_row+1)+"."+QString::fromUtf8(TaskResult));
                    curr_row++;
                }
                else if(ret == -1)
                {
                    break;
                }
            }
            else
            {
                multi_flag = 1;
                RESULT_NAME MultiResult[250];
                memset(MultiResult, 0, sizeof(MultiResult));
                unsigned int ResultCount = 0;
                ret = TaskMultiRstNumGet(TaskIndex.toInt(), 1, &ResultCount);
                if(ret != 0){
                    return;
                }
                ret = Get_Multi_Result_Task_Result_String(Modbus_index, task_type, ResultCount, MultiResult);
                for(int multiIndex = 0; multiIndex < ret; multiIndex++)
                {
                    InitTaskResultListTableWidget(curr_row, QString::number(curr_row+1)+"."+QString::fromUtf8(MultiResult[multiIndex].Result_Name));
                    curr_row++;
                }
                break;
            }
        }
    }
}

void IntercomModbusSelectDataDialog::on_tableWidget_detail_cellClicked(int row, int column)
{
    char TaskResult[100];
    int curr_row = 0;
    ui->pushButton_OK->setEnabled(false);


    ui->tableWidget_data->clear();
    ui->tableWidget_data->setRowCount(0);
    if(multi_flag == 0)
    {
        ui->pushButton_OK->setEnabled(true);
    }
    else
    {
        for(int index = 0; index >= 0; index++)
        {
            memset(TaskResult, 0, 100);
            int ret =  Get_Task_Result_String(Modbus_index, task_type, row+1, index, TaskResult);
            if(ret == 0)
            {
                continue;
            }
            else if(ret == -1)
            {
                if(ui->tableWidget_data->rowCount() == 0)
                {
                    ui->pushButton_OK->setEnabled(true);
                }
                break;
            }
            ui->tableWidget_detail->setItem(detail_pre_index, 1, new QTableWidgetItem(""));
            ui->tableWidget_detail->setItem(row, 1, new QTableWidgetItem("▶"));
            detail_pre_index = row;
            InitTaskDataListTableWidget(curr_row, QString::number(curr_row+1)+"."+QString::fromUtf8(TaskResult));
            curr_row++;
        }
    }
}

void IntercomModbusSelectDataDialog::on_tableWidget_data_cellClicked(int row, int column)
{
    ui->pushButton_OK->setEnabled(true);
}

void IntercomModbusSelectDataDialog::on_pushButton_OK_clicked()
{
    QString strTask = QString::null;
    QString strResult = QString::null;
    QString strData = QString::null;
    Select_Data_List.clear();
    strTask = ui->tableWidget_task->item(ui->tableWidget_task->currentRow(), 0)->text() + ";";
    if(multi_flag == 1 && ui->tableWidget_detail->currentRow() >= 0)
    {
        strResult = ui->tableWidget_detail->item(ui->tableWidget_detail->currentRow(), 0)->text() + ";";
        if(ui->tableWidget_data->rowCount() > 0)
            strData = ui->tableWidget_data->currentItem()->text() + ";";
        else
            strData = "";
    }
    else
    {
        strResult = ui->tableWidget_detail->currentItem()->text() + ";";
        strData = "";
    }
    if(strTask != QString::null)
        Select_Data_List.append(strTask);

    if(strResult != QString::null)
        Select_Data_List.append(strResult);

    if(strData != QString::null)
        Select_Data_List.append(strData);

    QDialog::accept();
}

void IntercomModbusSelectDataDialog::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
