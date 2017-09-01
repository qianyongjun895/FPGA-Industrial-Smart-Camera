#include "QDebug"
#include "QMessageBox"
#include "SelectDataDialog.h"
#include "ui_SelectDataDialog.h"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include "TaskRstGlobal.h"
SelectDataDialog::SelectDataDialog(int currentIndex,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDataDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    task_pre_index = 0;
    detail_pre_index = 0;
    task_type = 0;
    multi_flag = 0;
    m_step_index = currentIndex;
    IniData(currentIndex);
    ui->lineEdit_Data->setReadOnly(true);
    ui->pushButton_OK->setDisabled(true);
    ui->lineEdit_DownLimit->installEventFilter(this);
    ui->lineEdit_UpLimit->installEventFilter(this);
}

SelectDataDialog::~SelectDataDialog()
{
    ui->lineEdit_DownLimit->removeEventFilter(this);
    ui->lineEdit_UpLimit->removeEventFilter(this);
    delete ui;
}

void SelectDataDialog::IniData(int currentIndex)
{
    char taskName[40];
    ui->tableWidget_task->setRowCount(currentIndex-1);
    for(unsigned int i = 0; i < currentIndex-1; i ++)
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


void SelectDataDialog::DetailInitData(QString datalist, QString uplimit, QString downlimit, QString datatype)
{
    int i;
    IniData(m_step_index);
//    QStringList idatalist = datalist.split(";");
//    if(idatalist.count() == 2)
//    {
//        for(i = 0;i<ui->listWidget_TaskList->count();i++)
//        {
//            if(idatalist[0] == ui->listWidget_TaskList->item(i)->text())
//                ui->listWidget_TaskList->setCurrentRow(i);
//        }
//        for(i = 0;i<ui->listWidget_DataList->count();i++)
//        {
//            if(idatalist[1] == ui->listWidget_DataList->item(i)->text())
//                ui->listWidget_DataList->setCurrentRow(i);
//        }
//    }
    ui->pushButton_OK->setEnabled(true);
    ui->lineEdit_Data->setText(datalist);
    ui->lineEdit_UpLimit->setText(uplimit);
    ui->lineEdit_DownLimit->setText(downlimit);
    m_data_type = datatype.toInt();
    SetLineEditLimit();

}


void SelectDataDialog::InitTaskListTableWidget(int index, QString taskName)
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

void SelectDataDialog::InitTaskResultListTableWidget(int index, QString taskResult)
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

void SelectDataDialog::InitTaskDataListTableWidget(int index, QString taskResult)
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

QString SelectDataDialog::GetUpLimit()
{
    return ui->lineEdit_UpLimit->text();
}

QString SelectDataDialog::GetDownLimit()
{
    return ui->lineEdit_DownLimit->text();
}

void SelectDataDialog::on_tableWidget_task_cellClicked(int row, int column)
{
    int curr_row = 0;
    char TaskResult[100];
    ui->tableWidget_task->setItem(task_pre_index, 1, new QTableWidgetItem(""));
    ui->tableWidget_task->setItem(row, 1, new QTableWidgetItem("▶"));
    task_pre_index = row;
    ui->tableWidget_data->clear();
    ui->tableWidget_detail->clear();
    ui->lineEdit_Data->clear();
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
                ret =  Get_Task_Result_String(Data_judge_index, task_type, -1, index, TaskResult);
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
                ret = Get_Multi_Result_Task_Result_String(Data_judge_index, task_type, ResultCount, MultiResult);
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

void SelectDataDialog::on_tableWidget_detail_cellClicked(int row, int column)
{
    char TaskResult[100];
    int curr_row = 0;
    ui->pushButton_OK->setEnabled(false);
    ui->lineEdit_Data->clear();


    ui->tableWidget_data->clear();
    ui->tableWidget_data->setRowCount(0);
    if(multi_flag == 0)
    {
        ui->pushButton_OK->setEnabled(true);
        GetDataInfo();
        ui->lineEdit_Data->setText(Select_Data_List);
    }
    else
    {
        for(int index = 0; index >= 0; index++)
        {
            memset(TaskResult, 0, 100);
            int ret =  Get_Task_Result_String(Data_judge_index, task_type, row+1, index, TaskResult);
            if(ret == 0)
            {
                continue;
            }
            else if(ret == -1)
            {
                if(ui->tableWidget_data->rowCount() == 0)
                {
                    ui->pushButton_OK->setEnabled(true);
                    GetDataInfo();
                    ui->lineEdit_Data->setText(Select_Data_List);
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

void SelectDataDialog::on_tableWidget_data_cellClicked(int row, int column)
{
    ui->pushButton_OK->setEnabled(true);
    GetDataInfo();
    ui->lineEdit_Data->clear();
    ui->lineEdit_Data->setText(Select_Data_List);
}

void SelectDataDialog::on_pushButton_OK_clicked()
{
//    GetDataInfo();
    Select_Data_List = ui->lineEdit_Data->text();
    RangeJudge();
}

void SelectDataDialog::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}

void SelectDataDialog::GetDataInfo()
{
    QString strTask = QString::null;
    QString strResult = QString::null;
    QString strData = QString::null;
    Select_Data_List.clear();
    strTask = ui->tableWidget_task->currentItem()->text() + ";";
    strResult = ui->tableWidget_detail->currentItem()->text() + ";";
    if(multi_flag == 1 && ui->tableWidget_detail->currentRow() >= 0)
    {
        if(ui->tableWidget_data->rowCount() > 0)
            strData = ui->tableWidget_data->currentItem()->text();
        else
            strData = "";
    }
    else
    {
        strData = "";
    }
    int task_index = 0;
    int resul_index = 0;
    int detail_index = 0;
    if(strTask != QString::null)
    {
        Select_Data_List.append(strTask);
        task_index = strTask.split(".")[0].toInt();
    }

    if(strResult != QString::null)
    {
        Select_Data_List.append(strResult);
        resul_index = strResult.split(".")[0].toInt();
    }

    if(strData != QString::null)
    {
        Select_Data_List.append(strData);
        detail_index = strData.split(".")[0].toInt();
    }

    if(Task_Step_Type_ID_Get(task_index, &task_type) == 0)
    {
        if(multi_flag)
        {
            m_data_type = Get_TaskResult_Type_Flag(Data_judge_index,task_type,resul_index,detail_index);
        }
        else
        {
            m_data_type = Get_TaskResult_Type_Flag(Data_judge_index,task_type,-1,resul_index);
        }
        SetLineEditLimit();
    }
}

void SelectDataDialog::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        qDebug()<<"load libFrmInputKeyBoard.so isLoaded";
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

bool SelectDataDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_DownLimit ||watched == ui->lineEdit_UpLimit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(!((QLineEdit *)watched)->isReadOnly())
            {
                Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
                if(GetNumKeyBoardDlg)
                {
                    QDialog *Numkey = GetNumKeyBoardDlg();
                    int ret = Numkey->exec();
                    if(ret == QDialog::Accepted)
                    {
                        Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
                        if(GetNumString)
                        {
                            QString num = GetNumString();
                            ((QLineEdit *)watched)->setText(num);
                        }
                    }
                    delete Numkey;
                }
            }
        }
    }
    return QDialog::eventFilter(watched,event);

}

void SelectDataDialog::SetLineEditLimit()
{

    if(m_data_type == -1)
    {
        ui->TXTDataType->setText("unknow data type");
        return;
    }
    else if(m_data_type == DATA_SINT)
    {
        ui->lineEdit_DownLimit->setValidator(new QIntValidator(-100000000, 100000000, this));
        ui->lineEdit_UpLimit->setValidator(new QIntValidator(-100000000, 100000000, this));
        ui->TXTDataType->setText("int");
    }
    else if(m_data_type == DATA_UINT)
    {
        ui->lineEdit_DownLimit->setValidator(new QIntValidator(0, 100000000, this));
        ui->lineEdit_UpLimit->setValidator(new QIntValidator(0, 100000000, this));
        ui->TXTDataType->setText("unsigned int");
    }
    else if(m_data_type == DATA_FLT)
    {
        ui->lineEdit_DownLimit->setValidator(new QDoubleValidator(-1000000000.0, 1000000000.0,6, this));
        ui->lineEdit_UpLimit->setValidator(new QDoubleValidator(-1000000000.0, 1000000000.0,6, this));
        ui->TXTDataType->setText("float");
    }
    else if(m_data_type == DATA_DBL)
    {
        ui->lineEdit_DownLimit->setValidator(new QDoubleValidator(-1000000000.0, 1000000000.0,6, this));
        ui->lineEdit_UpLimit->setValidator(new QDoubleValidator(-1000000000.0, 1000000000.0,6, this));
        ui->TXTDataType->setText("double");
    }
}

void SelectDataDialog::RangeJudge()
{
    bool ok_up;
    bool ok_dw;
    if(m_data_type == DATA_SINT)
    {

        int uplimit= ui->lineEdit_UpLimit->text().toInt(&ok_up);
        int downlimit = ui->lineEdit_DownLimit->text().toInt(&ok_dw);
        if(!ok_up || !ok_dw)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("请输入正确的上下限值！"), QMessageBox::Ok);
            return;
        }
        if(downlimit >= uplimit)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("下限不能大于或等于上限，请重新输入！"), QMessageBox::Ok);
            return;
        }
        else
            QDialog::accept();
    }
    else if(m_data_type == DATA_UINT)
    {
        unsigned int uplimit= ui->lineEdit_UpLimit->text().toInt(&ok_up);
        unsigned int downlimit = ui->lineEdit_DownLimit->text().toInt(&ok_dw);
        if(!ok_up || !ok_dw)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("请输入正确的上下限值！"), QMessageBox::Ok);
            return;
        }
        if(downlimit >= uplimit)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("下限不能大于上限，请重新输入！"), QMessageBox::Ok);
            return;
        }
        else
            QDialog::accept();
    }
    else if(m_data_type == DATA_FLT)
    {
        float uplimit= ui->lineEdit_UpLimit->text().toFloat(&ok_up);
        float downlimit = ui->lineEdit_DownLimit->text().toFloat(&ok_dw);
        if(!ok_up || !ok_dw)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("请输入正确的上下限值！"), QMessageBox::Ok);
            return;
        }

        if(downlimit >= uplimit)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("下限不能大于上限，请重新输入！"), QMessageBox::Ok);
            return;
        }
        else
            QDialog::accept();
    }
    else if(m_data_type == DATA_DBL)
    {
        double uplimit = ui->lineEdit_UpLimit->text().toDouble(&ok_up);
        double downlimit = ui->lineEdit_DownLimit->text().toDouble(&ok_dw);
        if(!ok_up || !ok_dw)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("请输入正确的上下限值！"), QMessageBox::Ok);
            return;
        }

        if(downlimit >= uplimit)
        {
            QMessageBox::warning(NULL, tr("警告"), tr("下限不能大于上限，请重新输入！"), QMessageBox::Ok);
            return;
        }
        else
            QDialog::accept();
    }

}
