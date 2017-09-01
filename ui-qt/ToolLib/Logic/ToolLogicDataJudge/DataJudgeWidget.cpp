#include "QDebug"
#include "DataJudgeWidget.h"
#include "ui_DataJudgeWidget.h"
#include "QMessageBox"

DataJudgeWidget::DataJudgeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataJudgeWidget)
{
    ui->setupUi(this);
}

DataJudgeWidget::~DataJudgeWidget()
{
    delete ui;
}

void DataJudgeWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("pInputPara"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        COND_JUDGE_PRIVATE_PARAM *pPrivate = (COND_JUDGE_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
        pPrivate->data_number = 0;
        pPrivate->logic_type = 0;
    }
    InitData(i_step_index);
}

int DataJudgeWidget::Set_Parameter_To_Ram()
{
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    if(ui->radioButton_and->isChecked())
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->logic_type = 0;
    else
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->logic_type = 1;
    int data_count = ui->tableWidget->rowCount();
    ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data_number = data_count;
    for(int i = 0; i < data_count; i++)
    {
        QTableWidgetItem *item0 = ui->tableWidget->item(i,0);
        QTableWidgetItem *item1 = ui->tableWidget->item(i,1);
        QTableWidgetItem *item2 = ui->tableWidget->item(i,2);
        QTableWidgetItem *item3 = ui->tableWidget->item(i,3);
        if(item0 !=NULL)
        {
            int task_id,result_id;
            GetQuoteDataIndex(&task_id,&result_id,item0->text());
            ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].task_index = task_id;
            ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].result_index = result_id;

        }
        if(item1 !=NULL && item2 != NULL && item3 != NULL)
        {
            int data_type = item3->text().toInt();
            ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].data_type = data_type;
            SetLimitData(i,item1->text(),item2->text(),data_type);
        }
    }
    return 1;
}
void DataJudgeWidget::SetLimitData(int index,QString strUpLimit,QString strDwonLimit,int iDataType)
{
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    if(iDataType == DATA_SINT)
    {
        int upLimitInt = strUpLimit.toInt();
        int downLimitInt = strDwonLimit.toInt();
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].max.inum = upLimitInt;
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].min.inum = downLimitInt;

    }else if(iDataType == DATA_UINT)
    {
       unsigned int upLimitUint = strUpLimit.toUInt();
       unsigned int downLimitUint = strDwonLimit.toUInt();
       ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].max.unum = upLimitUint;
       ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].min.unum = downLimitUint;

    }else if(iDataType == DATA_FLT)
    {
        float upLimitFloat = strUpLimit.toFloat();
        float DownLimitFloat = strDwonLimit.toFloat();
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].max.fnum = upLimitFloat;
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].min.fnum = DownLimitFloat;

    }else if(iDataType == DATA_DBL)
    {
        double upLimitDouble =  strUpLimit.toDouble();
        double DownLimitDouble = strDwonLimit.toDouble();
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].max.dnum = upLimitDouble;
        ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[index].min.dnum = DownLimitDouble;
    }
}


void DataJudgeWidget::GetQuoteDataIndex(int *task_index,int *result_index,QString info)
{
    int task_id = 0;
    int result_id = 0;

    QStringList Select_Data_List = info.split(";");
    QString strTask = Select_Data_List.at(0);
    QString strResult = Select_Data_List.at(1);
    QString strData;
    QString Data_Index;
    if(Select_Data_List.count() >= 3)
    {
        strData = Select_Data_List.at(2);
        Data_Index = strData.split(".").at(0);
    }else
    {
        Data_Index = "0";
    }
    unsigned int task_type = 0;
    task_id = strTask.split(".").at(0).toInt();
    QString Result_Index = strResult.split(".").at(0);
    if(Task_Step_Type_ID_Get(task_id, &task_type) == 0)
    {
        if(Get_Multi_Result_Task_Flag(task_type) == 1)
        {
            result_id = UIId_Change_ResultID(Data_judge_index, task_type, Result_Index.toInt(), Data_Index.toInt());
        }
        else
        {
            result_id = UIId_Change_ResultID(Data_judge_index, task_type, -1, Result_Index.toInt());
        }
    }
    *task_index = task_id;
    *result_index = result_id;
}

void DataJudgeWidget::InitData(int i_step_index)
{
    Initable();
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    int iType= ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->logic_type;
    int iCount = ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data_number;
    for(int i = 0; i < iCount; i++)
    {
        QString StrName,strUpLimit,strDownLimit,strDatakind;
        unsigned short task_id = ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].task_index;
        unsigned short result_id = ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].result_index;
        StrName = GetQuoteString(task_id,result_id);
        int data_type = ((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].data_type;
        strDatakind = QString::number(data_type);
        if(data_type == DATA_SINT)
        {
            strUpLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].max.inum);
            strDownLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].min.inum);
        }else if(data_type == DATA_UINT)
        {
            strUpLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].max.unum);
            strDownLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].min.unum);
        }else if(data_type == DATA_FLT)
        {
            strUpLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].max.fnum);
            strDownLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].min.fnum);
        }else if(data_type == DATA_DBL)
        {
            strUpLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].max.dnum);
            strDownLimit = QString::number(((COND_JUDGE_PRIVATE_PARAM*)pPrivate)->data[i].min.dnum);
        }
        AddTableData(StrName,strUpLimit,strDownLimit,strDatakind);
    }

    if(iType==0)
    {
        ui->radioButton_and->setChecked(true);
    }else
    {
        ui->radioButton_or->setChecked(true);
    }
}

QString DataJudgeWidget::GetQuoteString(unsigned short task_index, unsigned short result_index)
{
    QString TaskNameString = QString::null;
    QString TaskResultString = QString::null;
    QString TaskDataString = "";
    unsigned int task_type = 0;
    int Task_Result_Count = 0;
    char taskName[40];
    if(Task_Step_Type_ID_Get(task_index, &task_type) == 0)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(task_index, taskName);
        if(ret != -1)
        {
            TaskNameString = QString::number(task_index) +"."+ QString::fromUtf8(taskName) + ";";
        }
    }
    else
    {
        return NULL;
    }

    int task_Result_index = ResultId_Change_UIID(&Task_Result_Count, Data_judge_index, task_type, result_index);

    if(Task_Result_Count != -1)
    {
        RESULT_NAME Result_String[250];
        memset(Result_String, 0, sizeof(Result_String));
        Get_Multi_Result_Task_Result_String(Data_judge_index, task_type, Task_Result_Count, Result_String);
        TaskResultString = QString::number(Task_Result_Count) + tr(".") + QString::fromUtf8(Result_String[Task_Result_Count -1].Result_Name) + ";";

        char TaskResult[100];
        memset(TaskResult, 0, sizeof(TaskResult));
        int rst_index = UI_ID_Change_Array_Index(Data_judge_index, task_type, Task_Result_Count, task_Result_index);
        if(rst_index == -1){
            return NULL;
        }
        int result = Get_Task_Result_String(Data_judge_index, task_type, Task_Result_Count, rst_index, TaskResult);
        if(result == 1)
        {
            TaskDataString = QString::number(task_Result_index) + tr(".") + QString::fromUtf8(TaskResult) + ";";
        }
        else
        {
            printf("Get_Task_Result_String result = %d\n",result);
        }

    }
    else
    {
        char TaskResult[100];
        memset(TaskResult, 0, sizeof(TaskResult));
        int rst_index = UI_ID_Change_Array_Index(Data_judge_index, task_type, Task_Result_Count, task_Result_index);
        if(rst_index == -1){
            return NULL;
        }
        int result = Get_Task_Result_String(Data_judge_index, task_type, Task_Result_Count, rst_index, TaskResult);
        if(result == 1)
        {
            TaskResultString = QString::number(task_Result_index) + tr(".") + QString::fromUtf8(TaskResult) + ";";
        }
        else
        {
            printf("Get_Task_Result_String result = %d\n",result);
        }
    }
    QString ret = TaskNameString + TaskResultString + TaskDataString;
    return ret;
}

void DataJudgeWidget::on_btnAdd_clicked()
{
    SelectDataDialog *dlg = new SelectDataDialog(m_step_index);
    int ret = dlg->exec();

    if(ret == QDialog::Accepted)
    {
        QString StrName,strUpLimit,strDownLimit,strDatakind;
        StrName = dlg->GetSelectDataList();
        strUpLimit = dlg->GetUpLimit();
        strDownLimit = dlg->GetDownLimit();
        strDatakind = QString::number(dlg->GetDataType());
        if(!JudgeDataIntable(StrName))
            AddTableData(StrName,strUpLimit,strDownLimit,strDatakind);
        else
            QMessageBox::warning(NULL, tr("警告"), tr("您选的数据已经在列表中!"), QMessageBox::Yes);
    }

   if(dlg !=NULL)
    {
        delete dlg;
        dlg = NULL;
    }
}
//增加表格数据
void DataJudgeWidget::AddTableData(QString StrName,QString strUpLimit,QString strDownLimit,QString strDatakind)
{
    int icount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(icount + 1);//总行数增加1
    ui->tableWidget->setItem(icount, 0, new QTableWidgetItem(StrName));
    ui->tableWidget->setItem(icount , 1, new QTableWidgetItem(strUpLimit));
    ui->tableWidget->setItem(icount , 2, new QTableWidgetItem(strDownLimit));
    ui->tableWidget->setItem(icount , 3, new QTableWidgetItem(strDatakind));

}
//判断数据在不在数据表格中
bool DataJudgeWidget::JudgeDataIntable(QString strName)
{
    bool bflag;
    bflag = false;
    int i;
    int count = ui->tableWidget->rowCount();

    for(i =0;i<count;i++)
    {
        QString strNameItem = ui->tableWidget->item(i,0)->text();

        if(strName == strNameItem)
        {
            bflag = true;
            break;

        }
    }

    return bflag;
}

//初始化表格
void DataJudgeWidget::Initable()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    QStringList horizontalHeader;
    horizontalHeader<<QObject::tr("变量")<<QObject::tr("上限")<<QObject::tr("下限")<<QObject::tr("数据类型");
    QStringList verticalHeader;
    //verticalHeader<<QObject::tr("line")<<QObject::tr("circle")<<QObject::tr("baseline");
    ui->tableWidget->setColumnWidth(0,300);
    ui->tableWidget->setColumnWidth(1,260);
    ui->tableWidget->setColumnWidth(2,260);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnHidden(3,true);
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableWidget->setVerticalHeaderLabels(verticalHeader);

    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DataJudgeWidget::on_btnEdit_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        SelectDataDialog *dlg = new SelectDataDialog(m_step_index);
        dlg->DetailInitData(ui->tableWidget->item(row,0)->text(),
                            ui->tableWidget->item(row,1)->text(),
                            ui->tableWidget->item(row,2)->text(),
                            ui->tableWidget->item(row,3)->text());
        int ret = dlg->exec();

        if(ret == QDialog::Accepted)
        {
            QString StrName,strUpLimit,strDownLimit,strDatakind;
            StrName = dlg->GetSelectDataList();
            strUpLimit = dlg->GetUpLimit();
            strDownLimit = dlg->GetDownLimit();
            strDatakind = QString::number(dlg->GetDataType());
            ui->tableWidget->item(row,0)->setText(StrName);
            ui->tableWidget->item(row,1)->setText(strUpLimit);
            ui->tableWidget->item(row,2)->setText(strDownLimit);
            ui->tableWidget->item(row,3)->setText(strDatakind);
        }
        if(dlg != NULL)
        {
            delete dlg;
            dlg = NULL;
        }
    }
}

void DataJudgeWidget::on_btnDell_clicked()
{
    int iIndex = ui->tableWidget->currentRow();

    if(iIndex >= 0)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定要删除选中行数据，确定退出?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            ui->tableWidget->removeRow(iIndex);
        }

    }else
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("请选中表格中的某行数据!"), QMessageBox::Yes);
    }
}
