#include "UserDefineSelectDialog.h"
#include "ui_UserDefineSelectDialog.h"
#include <QAbstractItemView>
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include "UserDefinedGlobal.h"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include "TaskRstGlobal.h"
#include <QMessageBox>
#include "RstData.h"
UserDefineSelectDialog::UserDefineSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDefineSelectDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    List_Index = 0;
    current_Data_index = 0;
    task_pre_index = 0;
    detail_pre_index = 0;
    Edit_Flag = 0;
    task_type = 0;
    multi_flag = 0;
    ui->radioButt_data_link->setChecked(true);

    Data_Type.insert(DATA_SINT, "int");
    Data_Type.insert(DATA_UINT, "unsigned int");
    Data_Type.insert(DATA_FLT, "float");
    Data_Type.insert(DATA_LONG, "long");
    Data_Type.insert(DATA_DBL, "double");

    ui->comboBox_Data_type->addItem("int");
    ui->comboBox_Data_type->addItem("unsigned int");
    ui->comboBox_Data_type->addItem("float");
    ui->comboBox_Data_type->addItem("long");
    ui->comboBox_Data_type->addItem("double");

    ui->pushButton_ADD->setDisabled(true);
    ui->lineEdit_decimals->installEventFilter(this);
    ui->lineEdit_Manual->installEventFilter(this);
    ui->lineEdit_G_data_addr->installEventFilter(this);
    IniData();
}
void UserDefineSelectDialog::IniData()
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

UserDefineSelectDialog::~UserDefineSelectDialog()
{
    ui->lineEdit_decimals->removeEventFilter(this);
    ui->lineEdit_Manual->removeEventFilter(this);
    ui->lineEdit_G_data_addr->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void UserDefineSelectDialog::InitTaskListTableWidget(int index, QString taskName)
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

void UserDefineSelectDialog::on_pushButton_OK_clicked()
{
    if(ui->tableWidget_FA->rowCount() == 0)
    {
        QMessageBox::warning(NULL, tr("警告"), tr("请选择数据！"), QMessageBox::Ok);
        return;
    }
    Select_Data = ui->tableWidget_FA->item(0, 0)->text();
    user_defined_source_item_cnt_set(List_Index, ui->tableWidget_FA->rowCount());
    QStringList TaskParam;
    for(int row_index = 0; row_index < ui->tableWidget_FA->rowCount(); row_index++)
    {
        TaskParam.clear();
        for(int i = 0; i < 3; i++){
            if(!ui->tableWidget_FA->item(row_index, i)->text().isEmpty()){
                TaskParam.append(ui->tableWidget_FA->item(row_index, i)->text());
            }
        }
        QString TaskString = ui->tableWidget_FA->item(row_index, 0)->text();
        if(TaskString != "动态G_Data" && TaskString != "静态G_Data" && TaskString != "手动输入"){
            SetTaskData(List_Index, row_index, TaskParam, TaskString);
        }else if(TaskString == "动态G_Data" || TaskString == "静态G_Data"){
            unsigned int type = 0;
            if(TaskString == "动态G_Data"){
                type = 1;
            }
            QString addr_str = ui->tableWidget_FA->item(row_index, 1)->text();
            SetGData(List_Index, row_index, type, addr_str.toUInt());
        }else{
            QString Manual_Value = ui->tableWidget_FA->item(row_index, 1)->text();
            SetManualData(List_Index, row_index, Manual_Value.toFloat());
        }
        QString data_type_string = ui->tableWidget_FA->item(row_index, 3)->text();
        unsigned int data_type = Data_Type.key(data_type_string);
        user_defined_data_type_set(List_Index, row_index, data_type);

        QString decimal_string = ui->tableWidget_FA->item(row_index, 4)->text();
        user_defined_data_decimal_set(List_Index, row_index, decimal_string.toUInt());
    }
    QDialog::accept();
}

void UserDefineSelectDialog::SetTaskData(unsigned int list_index, unsigned int data_index, QStringList list_string, QString task_string)
{
    unsigned int Task_type = 0;
    int result_id = 0;
    QString TaskIndex = task_string.split(".").at(0);
    int ret = Task_Step_Type_ID_Get(TaskIndex.toInt(), &Task_type);
    if(ret == 0)
    {
        if(Get_Multi_Result_Task_Flag(Task_type) == 1)
        {
            int Result_Num = 0;
            int Data_Num = 0;
            if(list_string.count() == 3){
                QString TaskResult = list_string.at(1);
                QString TaskResultIndex = TaskResult.split(".").at(0);
                Result_Num = TaskResultIndex.toInt();

                QString TaskData = list_string.at(2);
                QString TaskDatatIndex = TaskData.split(".").at(0);
                Data_Num = TaskDatatIndex.toInt();
            }else{
                QString TaskResult = list_string.at(1);
                QString TaskResultIndex = TaskResult.split(".").at(0);
                Result_Num = TaskResultIndex.toInt();
                Data_Num = 0;
            }
            result_id = UIId_Change_ResultID(Free_pro_index, Task_type, Result_Num, Data_Num);
        }
        else
        {
            QString TaskResult = list_string.at(1);
            QString TaskResultIndex = TaskResult.split(".").at(0);
            result_id = UIId_Change_ResultID(Free_pro_index, Task_type, -1, TaskResultIndex.toInt());
        }
        if(result_id != -1)
        {
            user_defined_link_step_info_set(list_index, data_index, TaskIndex.toInt(), result_id);///<设置数据流中的数据任务索引、任务结果索引
            user_defined_data_source_type_set(list_index, data_index, DATA_SOURCE_TYPE_LINK_STEP);
        }
    }
}

void UserDefineSelectDialog::SetGData(unsigned int list_index, unsigned int data_index, unsigned int type, unsigned int addr)
{
    user_defined_g_data_info_set(list_index, data_index, type, addr);
    user_defined_data_source_type_set(list_index, data_index, DATA_SOURCE_TYPE_G_DATA);
}

void UserDefineSelectDialog::SetManualData(unsigned int list_index, unsigned int data_index, float data)
{
    user_defined_manual_input_value_set(list_index, data_index, data);
    user_defined_data_source_type_set(list_index, data_index, DATA_SOURCE_TYPE_MANUAL_INPUT);
}

void UserDefineSelectDialog::EditModeInit()
{
    Edit_Flag = 1;
    unsigned int Data_Num = user_defined_source_item_cnt_get(List_Index);
    QStringList DataList;
    for(unsigned int Data_index = 0; Data_index < Data_Num; Data_index++)
    {
        unsigned int type = user_defined_data_source_type_get(List_Index, Data_index);
        if(type == DATA_SOURCE_TYPE_LINK_STEP){
            DataList = InitTaskData(List_Index, Data_index);
        }else if(type == DATA_SOURCE_TYPE_G_DATA){
            DataList = InitGData(List_Index, Data_index);
        }else{
            DataList = InitManualData(List_Index, Data_index);
        }
        if(DataList.isEmpty())
            return;

        current_Data_index = Data_index + 1;
        QStringList detaillist = DataList;
        ui->tableWidget_FA->setShowGrid(false);
        ui->tableWidget_FA->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_FA->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_FA->setRowCount(Data_index+1);
        ui->tableWidget_FA->setColumnCount(5);
        ui->tableWidget_FA->setColumnWidth(0,190);
        ui->tableWidget_FA->setColumnWidth(1,200);
        ui->tableWidget_FA->setColumnWidth(2,180);
        ui->tableWidget_FA->setColumnWidth(3, 150);
        ui->tableWidget_FA->setColumnWidth(4, 60);

        QStringList header;
        header<<tr("任务/G_Data/数据来源")<<tr("结果/G_Data地址/输入值")<<tr("数据")<<tr("类型")<<tr("小数位");   //表头
        ui->tableWidget_FA->setHorizontalHeaderLabels(header);
        ui->tableWidget_FA->setItem(Data_index, 0, new QTableWidgetItem(detaillist[0]));
        ui->tableWidget_FA->setItem(Data_index, 1, new QTableWidgetItem(detaillist[1]));
        if(detaillist.count() == 3){
            ui->tableWidget_FA->setItem(Data_index, 2, new QTableWidgetItem(detaillist[2]));
        }else{
            ui->tableWidget_FA->setItem(Data_index, 2, new QTableWidgetItem(""));
        }
        unsigned int data_type = user_defined_data_type_get(List_Index, Data_index);
        ui->tableWidget_FA->setItem(Data_index, 3, new QTableWidgetItem(Data_Type.value(data_type)));
        ui->tableWidget_FA->setItem(Data_index, 4, new QTableWidgetItem(QString::number(user_defined_data_decimal_get(List_Index, Data_index))));
    }
    Edit_Flag = 0;
}


QStringList UserDefineSelectDialog::InitTaskData(unsigned int List_index, unsigned int Data_index)
{
    QString TaskNameString = QString::null;
    QString TaskResultString = QString::null;
    QString TaskDataString = QString::null;
    QStringList DataList;
    DataList.clear();
    char TaskName[40];
    memset(TaskName, 0, 40);
    unsigned int Task_index = 0;
    unsigned int Task_Result_index = 0;
    user_defined_link_step_info_get(List_index, Data_index, &Task_index, &Task_Result_index);
    int Result_Count = 0;
    unsigned int Task_type = 0;
    int ret = Task_Step_Type_ID_Get(Task_index, &Task_type);
    if(ret == 0)
    {
        Task_Result_index = ResultId_Change_UIID(&Result_Count, Free_pro_index, Task_type, Task_Result_index);
    }
    else
    {
        return DataList;
    }
    Get_Task_Name(Task_index, TaskName);
    TaskNameString = QString::fromUtf8(TaskName);
    DataList.append(QString::number(Task_index) + tr(".") + TaskNameString);

    if(Result_Count != -1)
    {
        RESULT_NAME Result_String[250];
        memset(Result_String, 0, sizeof(RESULT_NAME)*250);
        Get_Multi_Result_Task_Result_String(Free_pro_index, Task_type, Result_Count, Result_String);
        TaskResultString = QString::fromUtf8(Result_String[Result_Count -1].Result_Name);
        DataList.append(QString::number(Result_Count) + tr(".") + TaskResultString);

        char TaskResult[100];
        memset(TaskResult, 0, 100);
        int rst_index = UI_ID_Change_Array_Index(Free_pro_index, Task_type, Result_Count, Task_Result_index);
        if(rst_index == -1){
            return DataList;
        }
        int result = Get_Task_Result_String(Free_pro_index, Task_type, Result_Count, rst_index, TaskResult);
        if(result == 1)
        {
            TaskDataString = QString::fromUtf8(TaskResult);
            DataList.append(QString::number(Task_Result_index) + tr(".") + TaskDataString);
        }
        else
        {
            printf("line = %d Get_Task_Result_String result = %d\n",__LINE__, result);
        }
    }
    else
    {

        char TaskResult[100];
        memset(TaskResult, 0, 100);
        int rst_index = UI_ID_Change_Array_Index(Free_pro_index, Task_type, Result_Count, Task_Result_index);
        if(rst_index == -1){
            return DataList;
        }
        int result = Get_Task_Result_String(Free_pro_index, Task_type, Result_Count, rst_index, TaskResult);
        if(result == 1)
        {
            TaskResultString = QString::fromUtf8(TaskResult);
            DataList.append(QString::number(Task_Result_index) + tr(".") + TaskResultString);
        }
        else
        {
            printf("line = %d Get_Task_Result_String result = %d\n",__LINE__, result);
        }
    }
    return DataList;
}

QStringList UserDefineSelectDialog::InitGData(unsigned int List_index, unsigned int Data_index)
{
    QStringList DataList;
    DataList.clear();
    unsigned int type =0;
    unsigned int addr =0;
    user_defined_g_data_info_get(List_index, Data_index, &type, &addr);
    if(type == 1){
        DataList.append("动态G_Data");
    }else{
        DataList.append("静态G_Data");
    }
    DataList.append(QString::number(addr));
    return DataList;
}

QStringList UserDefineSelectDialog::InitManualData(unsigned int List_index, unsigned int Data_index)
{
    QStringList DataList;
    DataList.clear();
    float data =0;
    user_defined_manual_input_value_get(List_index, Data_index, &data);

    DataList.append("手动输入");
    DataList.append(QString::number(data, 'g', 3));
    return DataList;
}

void UserDefineSelectDialog::on_tableWidget_task_cellClicked(int row, int column)
{
    if(row < 0)
        return;

    if(Edit_Flag == 1)
        return;

    int curr_row = 0;
    char TaskResult[100];
    ui->tableWidget_task->setItem(task_pre_index, 1, new QTableWidgetItem(""));
    ui->tableWidget_task->setItem(row, 1, new QTableWidgetItem("▶"));
    task_pre_index = row;
    ui->tableWidget_detail->clear();
    ui->tableWidget_data->clear();
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
                ret =  Get_Task_Result_String(Free_pro_index, task_type, -1, index, TaskResult);
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
                ret = Get_Multi_Result_Task_Result_String(Free_pro_index, task_type, ResultCount, MultiResult);
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

void UserDefineSelectDialog::InitTaskResultListTableWidget(int index, QString taskResult)
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

void UserDefineSelectDialog::on_tableWidget_detail_cellClicked(int row, int column)
{
    if(row < 0)
        return;

    char TaskResult[100];
    int curr_row = 0;
    ui->pushButton_ADD->setEnabled(false);


    ui->tableWidget_data->clear();
    ui->tableWidget_data->setRowCount(0);
    if(multi_flag == 0)
    {
        ui->pushButton_ADD->setEnabled(true);
    }
    else
    {
        for(int index = 0; index >= 0; index++)
        {
            memset(TaskResult, 0, 100);
            int ret =  Get_Task_Result_String(Free_pro_index, task_type, row+1, index, TaskResult);
            if(ret == 0)
            {
                continue;
            }
            else if(ret == -1)
            {
                if(ui->tableWidget_data->rowCount() == 0)
                {
                    ui->pushButton_ADD->setEnabled(true);
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


void UserDefineSelectDialog::InitTaskDataListTableWidget(int index, QString taskResult)
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

void UserDefineSelectDialog::on_tableWidget_data_cellClicked(int row, int column)
{
    if(row < 0)
        return;
    ui->pushButton_ADD->setEnabled(true);
}

void UserDefineSelectDialog::on_pushButton_ADD_clicked()
{
    if(ui->tableWidget_FA->rowCount() >= USER_lINK_DATA_SIZE)
    {
        QMessageBox::warning(NULL, tr("警告"), tr("数据量达到最大限制，无法继续添加！如要继续添加数据，请新添加一条数据流。"), QMessageBox::Ok);
        return;
    }
    if(ui->radioButt_data_link->isChecked()){
        QString strTask = QString::null;
        QString strResult = QString::null;
        QString strData = QString::null;

        strTask = ui->tableWidget_task->item(ui->tableWidget_task->currentRow(), 0)->text();
        if(multi_flag == 1 && ui->tableWidget_detail->currentRow() >= 0)
        {
            strResult = ui->tableWidget_detail->item(ui->tableWidget_detail->currentRow(), 0)->text();
            if(ui->tableWidget_data->rowCount() > 0)
                strData = ui->tableWidget_data->currentItem()->text();
            else
                strData = "";
        }
        else
        {
            strResult = ui->tableWidget_detail->currentItem()->text();
            strData = "";
        }
        InitSelectDataListTableWidget(strTask, strResult, strData);
    }else if(ui->radioButton_G_data->isChecked()){
        QString type_string;
        if(ui->radioButton_dynamic->isChecked()){
            type_string = "动态G_Data";
        }else{
            type_string = "静态G_Data";
        }
        InitGDataDataListTableWidget(type_string, ui->lineEdit_G_data_addr->text());
    }else{
        InitManualDataListTableWidget(ui->lineEdit_Manual->text());
    }
}


void UserDefineSelectDialog::InitSelectDataListTableWidget(QString strTask, QString strResult, QString strData)
{
    ui->tableWidget_FA->setShowGrid(false);
    ui->tableWidget_FA->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_FA->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_FA->setRowCount(current_Data_index+1);
    ui->tableWidget_FA->setColumnCount(5);
    ui->tableWidget_FA->setColumnWidth(0,190);
    ui->tableWidget_FA->setColumnWidth(1,200);
    ui->tableWidget_FA->setColumnWidth(2,180);
    ui->tableWidget_FA->setColumnWidth(3, 150);
    ui->tableWidget_FA->setColumnWidth(4, 60);

    QStringList header;
    header<<tr("任务/G_Data/数据来源")<<tr("结果/G_Data地址/输入值")<<tr("数据")<<tr("类型")<<tr("小数位");   //表头
    ui->tableWidget_FA->setHorizontalHeaderLabels(header);

    if(strTask != QString::null)
        ui->tableWidget_FA->setItem(current_Data_index, 0, new QTableWidgetItem(strTask));
    else
        ui->tableWidget_FA->setItem(current_Data_index, 0, new QTableWidgetItem(""));

    if(strResult != QString::null)
        ui->tableWidget_FA->setItem(current_Data_index, 1, new QTableWidgetItem(strResult));
    else
        ui->tableWidget_FA->setItem(current_Data_index, 1, new QTableWidgetItem(""));

    if(strData != QString::null)
        ui->tableWidget_FA->setItem(current_Data_index, 2, new QTableWidgetItem(strData));
    else
        ui->tableWidget_FA->setItem(current_Data_index, 2, new QTableWidgetItem(""));

    int task_data_type = 0;
    QString task_String = strTask.split(".").at(0);
    unsigned int task_index = task_String.toUInt();
    QString task_result_string = strResult.split(".").at(0);
    unsigned int task_result_index = task_result_string.toUInt();
    unsigned int task_type = 0;
    int ret = Task_Step_Type_ID_Get(task_index, &task_type);
    if(ret == 0){
        if(Get_Multi_Result_Task_Flag(task_type) == 1){
            QString task_data_string = strData.split(".").at(0);
            unsigned int task_data_index = task_data_string.toUInt();
            task_data_type = Get_TaskResult_Type_Flag(Free_pro_index, task_type, task_result_index, task_data_index);
        }else{
            task_data_type = Get_TaskResult_Type_Flag(Free_pro_index, task_type, -1, task_result_index);
        }
        if(Data_Type.value(task_data_type) != NULL){
            ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem(Data_Type.value(task_data_type)));
            if(task_data_type == DATA_FLT || task_data_type == DATA_DBL){
                ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("3"));
            }else{
                ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("0"));
            }
        }else{
            ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem("int"));
            ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("0"));
        }
    }else{
        ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem("int"));
        ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("0"));
    }
    current_Data_index++;
}

void UserDefineSelectDialog::InitGDataDataListTableWidget(QString type, QString Id)
{
    ui->tableWidget_FA->setShowGrid(false);
    ui->tableWidget_FA->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_FA->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_FA->setRowCount(current_Data_index+1);
    ui->tableWidget_FA->setColumnCount(5);
    ui->tableWidget_FA->setColumnWidth(0,190);
    ui->tableWidget_FA->setColumnWidth(1,200);
    ui->tableWidget_FA->setColumnWidth(2,180);
    ui->tableWidget_FA->setColumnWidth(3, 150);
    ui->tableWidget_FA->setColumnWidth(4, 60);

    QStringList header;
    header<<tr("任务/G_Data/数据来源")<<tr("结果/G_Data地址/输入值")<<tr("数据")<<tr("类型")<<tr("小数位");   //表头
    ui->tableWidget_FA->setHorizontalHeaderLabels(header);

    if(type != QString::null)
        ui->tableWidget_FA->setItem(current_Data_index, 0, new QTableWidgetItem(type));
    else
        ui->tableWidget_FA->setItem(current_Data_index, 0, new QTableWidgetItem(""));

    if(Id != QString::null)
        ui->tableWidget_FA->setItem(current_Data_index, 1, new QTableWidgetItem(Id));
    else
        ui->tableWidget_FA->setItem(current_Data_index, 1, new QTableWidgetItem(""));

    ui->tableWidget_FA->setItem(current_Data_index, 2, new QTableWidgetItem(""));

    if(type == "静态G_Data"){
        RST_VALUE_STRUCT rst_config;
        int ret = G_Data_Get(G_DATA_MANUAL, Id.toUInt()-1, &rst_config);
        if(ret == 0 && rst_config.resultflag == TASK_RESULT_VALID_FLAG){
            if(Data_Type.value(rst_config.resulttype) != NULL){
                ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem(Data_Type.value(rst_config.resulttype)));
                if(rst_config.resulttype == DATA_FLT || rst_config.resulttype == DATA_DBL){
                    ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("3"));
                }else{
                    ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("0"));
                }
            }
        }else{
            ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem("int"));
            ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("0"));
        }
    }else{
        ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem("int"));
        ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("0"));
    }
    current_Data_index++;
}

void UserDefineSelectDialog::InitManualDataListTableWidget(QString data)
{
    ui->tableWidget_FA->setShowGrid(false);
    ui->tableWidget_FA->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_FA->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_FA->setRowCount(current_Data_index+1);
    ui->tableWidget_FA->setColumnCount(5);
    ui->tableWidget_FA->setColumnWidth(0,190);
    ui->tableWidget_FA->setColumnWidth(1,200);
    ui->tableWidget_FA->setColumnWidth(2,180);
    ui->tableWidget_FA->setColumnWidth(3, 150);
    ui->tableWidget_FA->setColumnWidth(4, 60);

    QStringList header;
    header<<tr("任务/G_Data/数据来源")<<tr("结果/G_Data地址/输入值")<<tr("数据")<<tr("类型")<<tr("小数位");   //表头
    ui->tableWidget_FA->setHorizontalHeaderLabels(header);

    ui->tableWidget_FA->setItem(current_Data_index, 0, new QTableWidgetItem("手动输入"));

    if(data != QString::null)
        ui->tableWidget_FA->setItem(current_Data_index, 1, new QTableWidgetItem(data));
    else
        ui->tableWidget_FA->setItem(current_Data_index, 1, new QTableWidgetItem(""));

    ui->tableWidget_FA->setItem(current_Data_index, 2, new QTableWidgetItem(""));
    ui->tableWidget_FA->setItem(current_Data_index, 3, new QTableWidgetItem("float"));
    ui->tableWidget_FA->setItem(current_Data_index, 4, new QTableWidgetItem("3"));
    current_Data_index++;
}

void UserDefineSelectDialog::on_pushButton_del_clicked()
{
    if(ui->tableWidget_FA->rowCount() > 1)
    {
        ui->tableWidget_FA->removeRow(ui->tableWidget_FA->currentRow());
        if(current_Data_index > 0)
            current_Data_index--;
        else
        {
            current_Data_index = 0;
        }
    }
}

void UserDefineSelectDialog::on_pushButton_Down_clicked()
{
    DownListData();
}

void UserDefineSelectDialog::DownListData()
{
    int crtRow = ui->tableWidget_FA->currentRow();
    QString strTask,strResult,strData;
    if(crtRow < (ui->tableWidget_FA->rowCount()-1))
    {
        strTask = ui->tableWidget_FA->item(crtRow,0)->text();
        strResult = ui->tableWidget_FA->item(crtRow,1)->text();
        strData = ui->tableWidget_FA->item(crtRow,2)->text();

        ui->tableWidget_FA->setItem(crtRow, 0, new QTableWidgetItem(ui->tableWidget_FA->item(crtRow+1,0)->text()));
        ui->tableWidget_FA->setItem(crtRow, 1, new QTableWidgetItem(ui->tableWidget_FA->item(crtRow+1,1)->text()));
        ui->tableWidget_FA->setItem(crtRow, 2, new QTableWidgetItem(ui->tableWidget_FA->item(crtRow+1,2)->text()));

        ui->tableWidget_FA->setItem(crtRow+1, 0, new QTableWidgetItem(strTask));
        ui->tableWidget_FA->setItem(crtRow+1, 1, new QTableWidgetItem(strResult));
        ui->tableWidget_FA->setItem(crtRow+1, 2, new QTableWidgetItem(strData));
        ui->tableWidget_FA->setCurrentCell(crtRow+1,0);
    }
}



void UserDefineSelectDialog::on_pushButton_Up_clicked()
{
    UpListData();
}

void UserDefineSelectDialog::UpListData()
{
    int crtRow = ui->tableWidget_FA->currentRow();
    QString strTask,strResult,strData;
    if(crtRow > 0)
    {
        strTask = ui->tableWidget_FA->item(crtRow,0)->text();
        strResult = ui->tableWidget_FA->item(crtRow,1)->text();
        strData = ui->tableWidget_FA->item(crtRow,2)->text();

        ui->tableWidget_FA->setItem(crtRow, 0, new QTableWidgetItem(ui->tableWidget_FA->item(crtRow-1,0)->text()));
        ui->tableWidget_FA->setItem(crtRow, 1, new QTableWidgetItem(ui->tableWidget_FA->item(crtRow-1,1)->text()));
        ui->tableWidget_FA->setItem(crtRow, 2, new QTableWidgetItem(ui->tableWidget_FA->item(crtRow-1,2)->text()));
        ui->tableWidget_FA->setItem(crtRow-1, 0, new QTableWidgetItem(strTask));
        ui->tableWidget_FA->setItem(crtRow-1, 1, new QTableWidgetItem(strResult));
        ui->tableWidget_FA->setItem(crtRow-1, 2, new QTableWidgetItem(strData));
        ui->tableWidget_FA->setCurrentCell(crtRow-1,0);
    }
}

void UserDefineSelectDialog::on_pushButton_quit_clicked()
{
    QDialog::reject();
}

void UserDefineSelectDialog::on_radioButt_data_link_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
//    int ret = QMessageBox::warning(NULL, "警告", "切换数据来源会导致现有数据被清空！", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
//    if(ret == QMessageBox::Yes){
//        int count = ui->tableWidget_FA->rowCount();
//        for(int i = count; i >= 0; i--){
//            ui->tableWidget_FA->removeRow(i);
//        }
//        current_Data_index = 0;
//        ui->stackedWidget->setCurrentIndex(0);
//    }
}

void UserDefineSelectDialog::on_radioButton_G_data_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->radioButton_dynamic->setChecked(true);
    ui->lineEdit_G_data_addr->setText("1");
    ui->pushButton_ADD->setEnabled(true);
//    int ret = QMessageBox::warning(NULL, "警告", "切换数据来源会导致现有数据被清空！", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
//    if(ret == QMessageBox::Yes){
//        int count = ui->tableWidget_FA->rowCount();
//        for(int i = count; i >= 0; i--){
//            ui->tableWidget_FA->removeRow(i);
//        }
//        current_Data_index = 0;
//        ui->stackedWidget->setCurrentIndex(1);
//        ui->radioButton_dynamic->setChecked(true);
//        ui->lineEdit_G_data_addr->setText("1");
//        ui->pushButton_ADD->setEnabled(true);
//    }
}

void UserDefineSelectDialog::on_radioButton_Manual_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->lineEdit_Manual->setText("1");
    ui->pushButton_ADD->setEnabled(true);

//    int ret = QMessageBox::warning(NULL, "警告", "切换数据来源会导致现有数据被清空！", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
//    if(ret == QMessageBox::Yes){
//        int count = ui->tableWidget_FA->rowCount();
//        for(int i = count; i >= 0; i--){
//            ui->tableWidget_FA->removeRow(i);
//        }
//        current_Data_index = 0;
//        ui->stackedWidget->setCurrentIndex(2);
//        ui->lineEdit_Manual->setText("");
//        ui->pushButton_ADD->setEnabled(true);
//    }
}

bool UserDefineSelectDialog::eventFilter(QObject *watched, QEvent *event)
{
   if(watched == ui->lineEdit_Manual){
       if(event->type() == QEvent::MouseButtonPress){
           if(((QLineEdit *)watched)->isEnabled())
           {
               NumKeyBoardDlg(watched, event);
           }
       }
   }
   if(watched == ui->lineEdit_G_data_addr){
       if(event->type() == QEvent::MouseButtonPress){
           if(((QLineEdit *)watched)->isEnabled())
           {
               NumKeyBoardDlg(watched, event);
           }
       }
   }
   if(watched == ui->lineEdit_decimals){
       if(event->type() == QEvent::MouseButtonPress){
           if(((QLineEdit *)watched)->isEnabled())
           {
               NumKeyBoardDlg(watched, event);
           }
       }
   }
   return QWidget::eventFilter(watched, event);
}

void UserDefineSelectDialog::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        qDebug()<<"libFrmInputKeyBoard.so OK";
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void UserDefineSelectDialog::NumKeyBoardDlg(QObject *watched, QEvent *event)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        Numkey = GetNumKeyBoardDlg();
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
        Numkey = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}


void UserDefineSelectDialog::on_comboBox_Data_type_currentIndexChanged(const QString &arg1)
{
    int crtRow = ui->tableWidget_FA->currentRow();
    if(crtRow >= 0){
        ui->tableWidget_FA->setItem(crtRow, 3, new QTableWidgetItem(arg1));
        if(arg1 == "int" || arg1 == "unsigned int"){
            ui->lineEdit_decimals->setEnabled(false);
            ui->tableWidget_FA->setItem(crtRow, 4, new QTableWidgetItem("0"));
        }else{
            ui->lineEdit_decimals->setEnabled(true);
        }
    }
}

void UserDefineSelectDialog::on_lineEdit_decimals_textChanged(const QString &arg1)
{
    int crtRow = ui->tableWidget_FA->currentRow();
    if(crtRow >= 0){
        QString type = ui->tableWidget_FA->item(crtRow, 3)->text();
        if(type == "float" || type == "double")
            ui->tableWidget_FA->setItem(crtRow, 4, new QTableWidgetItem(arg1));
    }
}


void UserDefineSelectDialog::on_tableWidget_FA_itemSelectionChanged()
{
    int crtRow = ui->tableWidget_FA->currentRow();
    if(crtRow >= 0){
        QString type = ui->tableWidget_FA->item(crtRow, 3)->text();
        ui->comboBox_Data_type->setCurrentText(type);

        QString decimals = ui->tableWidget_FA->item(crtRow, 4)->text();
        ui->lineEdit_decimals->setText(decimals);
    }
}
