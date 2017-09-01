#include "ToolStatistic.h"
#include "ui_ToolStatistic.h"
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"
#include <QDebug>
#include <QMessageBox>
ToolStatistic::ToolStatistic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolStatistic)
{
    ui->setupUi(this);
    QList<QLineEdit*> lineEdit = this->findChildren<QLineEdit*>();
    foreach(QLineEdit* L, lineEdit){
        L->installEventFilter(this);
    }
    LoadKeyBoardLib();
}

ToolStatistic::~ToolStatistic()
{
    QList<QLineEdit*> lineEdit = this->findChildren<QLineEdit*>();
    foreach(QLineEdit* L, lineEdit){
        L->removeEventFilter(this);
    }
    delete ui;
}

void ToolStatistic::on_listWidget_Task_currentRowChanged(int currentRow)
{
    QString TaskIndex = ui->listWidget_Task->item(currentRow)->text().split(".").at(0);
    unsigned int TaskType = 0;
    int Current_index = 0;
    int ret = Task_Step_Type_ID_Get(TaskIndex.toInt(), &TaskType);
    if(ret == 0){
        if(Get_Multi_Result_Task_Flag(TaskType) == 1){
            ui->groupBox_Result->setVisible(true);
            ui->label_Result->setVisible(true);
            RESULT_NAME TaskResult[250];
            unsigned int ResultNum = 0;
            ret = TaskMultiRstNumGet(TaskIndex.toInt(), 1, &ResultNum);
            if(ret == 0){
                memset(TaskResult, 0, sizeof(TaskResult));
                int rst = Get_Multi_Result_Task_Result_String(Stat_indedx, TaskType, ResultNum, TaskResult);
                ui->listWidget_Result->clear();
                ui->listWidget_Data->clear();
                printf("TaskMultiRstNumGet rst = %d\n",rst);
                for(int i = 0; i < rst; i++){
                    ui->listWidget_Result->addItem(QString::number(i+1)+"."+QString::fromUtf8(TaskResult[i].Result_Name));
                }
            }else{
                printf("TaskMultiRstNumGet ret < 0\n");
            }
        }else{
            ui->groupBox_Result->setVisible(false);
            ui->label_Result->setVisible(false);
            ui->listWidget_Data->clear();
            char TaskData[100];
            for(int i = 0; ; i++){
                memset(TaskData, 0, 100);
                ret = Get_Task_Result_String(Stat_indedx, TaskType, -1, i, TaskData);
                if(ret == 1){
                    Current_index++;
                    ui->listWidget_Data->addItem(QString::number(Current_index)+"."+QString::fromUtf8(TaskData));
                }else if(ret == -1){
                    break;
                }
            }
        }
    }
}

void ToolStatistic::InitTaskListItem()
{
    ui->listWidget_Task->clear();
    Task_List_Hash.clear();
    char TaskName[40];
    for(int i = 1; i < Current_Step; i++){
        unsigned int TaskType = 0;
        int ret = Task_Step_Type_ID_Get(i, &TaskType);
        if(ret == 0){
            ret = Get_Task_Link_Type_Flag(TaskType, Stat_indedx);
            if(ret == 1){
                memset(TaskName, 0, 40);
                ret = Get_Task_Name(i, TaskName);
                if(ret == 0){
                    ui->listWidget_Task->addItem(QString::number(i)+"."+QString::fromUtf8(TaskName));
                    Task_List_Hash.insert(i, ui->listWidget_Task->count()-1);
                }
            }
        }
    }
}

void ToolStatistic::LoadKeyBoardLib()
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

void ToolStatistic::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
                if(Min_value != -1)
                {
                    if(num.toInt() <= Min_value)
                    {
                        QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入大于")+QString::number(Min_value)+tr("的值"));
                        return;
                    }
                }
                if(Max_value != -1)
                {
                    if(num.toInt() >= Max_value)
                    {
                        QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入小于")+QString::number(Max_value)+tr("的值"));
                        return;
                    }
                }
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

void ToolStatistic::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (DATASTST_INPUT_PARAM*)ptr;
    Current_Step = i_step_index;
    InitTaskListItem();
    if(new_flag){
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ui->checkBox_ValidValue->setChecked(false);
        ui->lineEdit_DownLimit->setEnabled(false);
        ui->lineEdit_UpLimit->setEnabled(false);
    }else{
        TASK_STEP_HEADER * step_Header = Task_Step_Head_Get(Current_Step);
        if(step_Header != NULL){
            int row = Task_List_Hash.value(step_Header->step_link.link_info[0].step_index);
            if(row >= 0 && row < Current_Step - 1){
                ui->listWidget_Task->setCurrentRow(row);
            }
            int Result_count = 0;
            unsigned int Task_type;
            int ret = Task_Step_Type_ID_Get(step_Header->step_link.link_info[0].step_index, &Task_type);
            if(ret != 0)
                return;
            ret = ResultId_Change_UIID(&Result_count, Stat_indedx, Task_type, step_Header->step_link.link_info[0].result_index);
            if(!(ret == -1 && Result_count == -1)){
                if(Result_count != -1){
                    if(ret == -1){
                        ui->listWidget_Result->setCurrentRow(0);
                    }
                    else{
                        ui->listWidget_Result->setCurrentRow(Result_count - 1);
                        ui->listWidget_Data->setCurrentRow(ret - 1);
                    }
                }else if(ret > 0 && Result_count == -1){
                    ui->listWidget_Data->setCurrentRow(ret - 1);
                }
            }
        }

        if(pInputPara != NULL){
            if(pInputPara->valid_range_check == 1){
                ui->checkBox_ValidValue->setChecked(true);
                ui->lineEdit_DownLimit->setText(QString::number(pInputPara->low_threshold));
                ui->lineEdit_UpLimit->setText(QString::number(pInputPara->high_threshold));
            }else{
                ui->checkBox_ValidValue->setChecked(false);
                ui->lineEdit_DownLimit->setEnabled(false);
                ui->lineEdit_UpLimit->setEnabled(false);
            }
        }
    }
}

bool ToolStatistic::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_UpLimit){
        if(event->type() == QEvent::MouseButtonPress && ui->lineEdit_UpLimit->isEnabled()){
            if(ui->lineEdit_DownLimit->text() != ""){
                NumKeyBoardDlg(watched, event, ui->lineEdit_DownLimit->text().toInt(), -1);
            }else{
                NumKeyBoardDlg(watched, event, -1, -1);
            }
        }
    }
    if(watched == ui->lineEdit_DownLimit){
        if(event->type() == QEvent::MouseButtonPress && ui->lineEdit_DownLimit->isEnabled()){
            if(ui->lineEdit_UpLimit->text() != ""){
                NumKeyBoardDlg(watched, event, -1, ui->lineEdit_UpLimit->text().toInt());
            }else{
                NumKeyBoardDlg(watched, event, -1, -1);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}


int ToolStatistic::Set_Parameter_To_Ram()
{
    int Task_Curr_Row = ui->listWidget_Task->currentRow();
    if(Task_Curr_Row >= 0){
        QString TaskIndex = ui->listWidget_Task->item(Task_Curr_Row)->text().split(".").at(0);
        int Result_Curr_Row = -1;
        if(ui->listWidget_Result->isVisible()){
            Result_Curr_Row = ui->listWidget_Result->currentRow();
            if(Result_Curr_Row < 0){
                return 0;
            }
            Result_Curr_Row = Result_Curr_Row+1;
        }
        int Data_Curr_Row = ui->listWidget_Data->currentRow();
        if(Data_Curr_Row < 0){
            if(Select_Finish_Flag == 1){
                Data_Curr_Row = -1;
            }else{
                return 0;
            }
        }
        unsigned int TaskType = 0;
        int ret = Task_Step_Type_ID_Get(TaskIndex.toInt(), &TaskType);
        if(ret == 0){
            ret = UIId_Change_ResultID(Stat_indedx, TaskType, Result_Curr_Row, Data_Curr_Row+1);
            if(ret == -1){
                return 0;
            }else{
                TASK_STEP_HEADER * step_Header = Task_Step_Head_Get(Current_Step);
                if(step_Header != NULL){
                    step_Header->step_link.link_count = 1;
                    step_Header->step_link.link_info[0].step_index = TaskIndex.toInt();
                    step_Header->step_link.link_info[0].result_index = ret;
                }
                if(ui->checkBox_ValidValue->isChecked()){
                    pInputPara->valid_range_check = 1;
                    pInputPara->high_threshold = ui->lineEdit_UpLimit->text().toFloat();
                    pInputPara->low_threshold = ui->lineEdit_DownLimit->text().toFloat();
                }else{
                    pInputPara->valid_range_check = 0;
                }
            }
        }
    }
    return 1;
}

void ToolStatistic::on_listWidget_Result_currentRowChanged(int currentRow)
{
    Select_Finish_Flag = 0;
    int Task_Curr_Row = ui->listWidget_Task->currentRow();
    if(Task_Curr_Row >= 0){
        QString TaskIndex = ui->listWidget_Task->item(Task_Curr_Row)->text().split(".").at(0);
        unsigned int TaskType = 0;
        int Current_index = 0;
        int ret = Task_Step_Type_ID_Get(TaskIndex.toInt(), &TaskType);
        if(ret == 0){
            if(Get_Multi_Result_Task_Flag(TaskType) == 1){
                ui->listWidget_Data->clear();
                char TaskData[100];
                for(int i = 0; ; i++){
                    memset(TaskData, 0, 100);
                    ret = Get_Task_Result_String(Stat_indedx, TaskType, currentRow + 1, i, TaskData);
                    if(ret == 1){
                        Current_index++;
                        ui->listWidget_Data->addItem(QString::number(Current_index)+"."+QString::fromUtf8(TaskData));
                    }else if(ret == -1){
                        if(ui->listWidget_Data->count() == 0){
                            Select_Finish_Flag = 1;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void ToolStatistic::on_checkBox_ValidValue_clicked()
{
    if(ui->checkBox_ValidValue->isChecked()){
        ui->lineEdit_UpLimit->setEnabled(true);
        ui->lineEdit_DownLimit->setEnabled(true);
    }else{
        ui->lineEdit_UpLimit->setEnabled(false);
        ui->lineEdit_DownLimit->setEnabled(false);
    }
}
