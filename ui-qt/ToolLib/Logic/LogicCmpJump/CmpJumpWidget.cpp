#include <QDebug>
#include "CmpJumpWidget.h"
#include "ui_CmpJumpWidget.h"
#include "QMessageBox"

CmpJumpWidget::CmpJumpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CmpJumpWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    ui->comboBoxJudgeType->addItem("A = B");
    ui->comboBoxJudgeType->addItem("A > B");
    ui->comboBoxJudgeType->addItem("A >= B");
    ui->comboBoxJudgeType->addItem("A < B");
    ui->comboBoxJudgeType->addItem("A <= B");


    ui->txtExpressionA->setReadOnly(true);
    ui->radioButtonInput->setChecked(true);
    ui->btnSelectB->setEnabled(false);
    ui->comboBoxNGJudge->addItem("无");
    ui->comboBoxOKJudge->addItem("无");
    ui->txtExpressionB->installEventFilter(this);
}

CmpJumpWidget::~CmpJumpWidget()
{
    ui->txtExpressionB->removeEventFilter(this);
    delete ui;
}

/**
 * @brief CmpJumpWidget::Init_Input_Ptr
 * @param ptr
 * @param i_step_index
 * @param new_flag
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void CmpJumpWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (CMP_JUMP_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("pInputPara"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->cmp_way = COMPARE_EQUAL;
        pInputPara->cmp_data = 0;
        pInputPara->ok_jump_step = 0;
        pInputPara->ng_jump_step = 0;
    }
    InitData(i_step_index);
}


/**
 * @brief CmpJumpWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 取样
 */
int CmpJumpWidget::Set_Parameter_To_Ram()
{
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    pInputPara->ok_jump_step = atoi(ui->comboBoxOKJudge->currentText().toStdString().c_str());
    pInputPara->ng_jump_step = atoi(ui->comboBoxNGJudge->currentText().toStdString().c_str());
    pInputPara->cmp_way = ui->comboBoxJudgeType->currentIndex()+1;

    int i_task_index = 0;
    int i_result_index = 0;
    QString QuoteInfo = ui->txtExpressionA->text();
    if(QuoteInfo.isEmpty())
    {
        return 0;
    }
    GetQuoteDataIndex(&i_task_index,&i_result_index,QuoteInfo);
    pStephead->step_link.link_info[0].step_index = i_task_index;
    pStephead->step_link.link_info[0].result_index = i_result_index;
    printf("i_result_index === %d\n",i_result_index);
    if(ui->radioButtonInput->isChecked())
    {
        pStephead->step_link.link_count = 1;
        pInputPara->cmp_data = ui->txtExpressionB->text().toDouble();
    }
    else
    {
        pStephead->step_link.link_count = 2;
        QuoteInfo = ui->txtExpressionB->text();
        if(QuoteInfo.isEmpty())
        {
            return 0;
        }
        GetQuoteDataIndex(&i_task_index,&i_result_index,QuoteInfo);
        printf("i_result_index === %d\n",i_result_index);
        pStephead->step_link.link_info[1].step_index = i_task_index;
        pStephead->step_link.link_info[1].result_index = i_result_index;
    }
    return 1;
}

/**
 * @brief CmpJumpWidget::GetQuoteDataIndex
 * @param task_index
 * @param result_index
 * @param info
 * @author dgq
 * @note 获取引用数据的索引
 */
void CmpJumpWidget::GetQuoteDataIndex(int *task_index,int *result_index,QString info)
{
    int task_id = 0;
    int result_id = 0;

    QStringList Select_Data_List = info.split(";");
    QString strTask = Select_Data_List.at(0);
    QString strResult = Select_Data_List.at(1);
    QString strData;
    QString Data_Index;
    if(Select_Data_List.count() == 4)
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
            result_id = UIId_Change_ResultID(Cmp_jump_index, task_type, Result_Index.toInt(), Data_Index.toInt());
        }
        else
        {
            result_id = UIId_Change_ResultID(Cmp_jump_index, task_type, -1, Result_Index.toInt());
        }
    }
    *task_index = task_id;
    *result_index = result_id;
}

/**
 * @brief CmpJumpWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化界面显示
 */
void CmpJumpWidget::InitData(int i_step_index)
{
    int i_task_count = GetTaskStepCount();
    int i = 0;
//    ui->comboBoxOKJudge->clear();
//    ui->comboBoxNGJudge->clear();
//    ui->comboBoxOKJudge->addItem(tr("无"));
//    ui->comboBoxNGJudge->addItem(tr("无"));
    for(i = 0; i < i_task_count;i++)
    {
        if(i == i_step_index-1)
            continue;

        unsigned int task_type = 0;
        char taskName[40];
        if(Task_Step_Type_ID_Get(i+1, &task_type) == 0)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                if(i+1 > i_step_index)
                {
                    ui->comboBoxOKJudge->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                    ui->comboBoxNGJudge->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                }
            }
        }
    }
    for(i = 0; i < ui->comboBoxOKJudge->count();i++)
    {
        QString task_ok = ui->comboBoxOKJudge->itemText(i);
        if(atoi(task_ok.toStdString().c_str()) == pInputPara->ok_jump_step)
        {
            ui->comboBoxOKJudge->setCurrentIndex(i);
        }
    }
    for(i = 0; i < ui->comboBoxNGJudge->count();i++)
    {
        QString task_ng = ui->comboBoxNGJudge->itemText(i);
        if(atoi(task_ng.toStdString().c_str()) == pInputPara->ng_jump_step)
        {
            ui->comboBoxNGJudge->setCurrentIndex(i);
        }
    }
    int cmp_way = pInputPara->cmp_way - 1;
    if(cmp_way >=0 && cmp_way <=4)
    {
        ui->comboBoxJudgeType->setCurrentIndex(cmp_way);
    }else
    {
        ui->comboBoxJudgeType->setCurrentIndex(0);
    }

    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int taskA_index = pStephead->step_link.link_info[0].step_index;
    int i_resultA_index = pStephead->step_link.link_info[0].result_index;
//    qDebug()<<"taskA_index = "<<taskA_index;
//    qDebug()<<"i_resultA_index = "<<i_resultA_index;

    QString str_info_a = SetQuoteString(taskA_index,i_resultA_index);
    ui->txtExpressionA->setText(str_info_a);
//    qDebug()<<"link_count = "<<pStephead->step_link.link_count;
    if(pStephead->step_link.link_count == 1)
    {
        ui->radioButtonInput->setChecked(true);
        ui->btnSelectB->setEnabled(false);
        ui->txtExpressionB->setReadOnly(false);
        ui->txtExpressionB->setText(QString::number(pInputPara->cmp_data));
    }else if(pStephead->step_link.link_count == 2)
    {
        ui->radioButtonQuote->setChecked(true);
        ui->btnSelectB->setEnabled(true);
        ui->txtExpressionB->setReadOnly(true);
        int taskB_index = pStephead->step_link.link_info[1].step_index;
        int i_resultB_index = pStephead->step_link.link_info[1].result_index;
//        qDebug()<<"taskB_index = "<<taskB_index;
//        qDebug()<<"i_resultB_index = "<<i_resultB_index;
        QString str_info_b = SetQuoteString(taskB_index,i_resultB_index);
        ui->txtExpressionB->setText(str_info_b);
    }
}

/**
 * @brief CmpJumpWidget::SetQuoteString
 * @param task_index
 * @param result_index
 * @return
 * @author dgq
 * @note 根据任务索引跟结果索引获取引用数据的信息
 */
QString CmpJumpWidget::SetQuoteString(unsigned short task_index, unsigned short result_index)
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

    int task_Result_index = ResultId_Change_UIID(&Task_Result_Count, Cmp_jump_index, task_type, result_index);

    if(Task_Result_Count != -1)
    {
        RESULT_NAME Result_String[250];
        memset(Result_String, 0, sizeof(Result_String));
        Get_Multi_Result_Task_Result_String(Cmp_jump_index, task_type, Task_Result_Count, Result_String);
        TaskResultString = QString::number(Task_Result_Count) + tr(".") + QString::fromUtf8(Result_String[Task_Result_Count -1].Result_Name) + ";";

        char TaskResult[100];
        memset(TaskResult, 0, sizeof(TaskResult));
        int rst_index = UI_ID_Change_Array_Index(Cmp_jump_index, task_type, Task_Result_Count, task_Result_index);
        if(rst_index == -1){
            return NULL;
        }
        int result = Get_Task_Result_String(Cmp_jump_index, task_type, Task_Result_Count, rst_index, TaskResult);
        if(result == 1)
        {
            TaskDataString = QString::number(task_Result_index) + tr(".") + QString::fromUtf8(TaskResult) + ";";
        }
        else
        {
            printf("line = %d Get_Task_Result_String result = %d\n",__LINE__, result);
        }
    }
    else
    {
        char TaskResult[100];
        memset(TaskResult, 0, sizeof(TaskResult));
        int rst_index = UI_ID_Change_Array_Index(Cmp_jump_index, task_type, Task_Result_Count, task_Result_index);
        if(rst_index == -1){
            return NULL;
        }
        int result = Get_Task_Result_String(Cmp_jump_index, task_type, Task_Result_Count, rst_index, TaskResult);
        if(result == 1)
        {
            TaskResultString = QString::number(task_Result_index) + tr(".") + QString::fromUtf8(TaskResult) + ";";
        }
        else
        {
            printf("line = %d Get_Task_Result_String result = %d\n",__LINE__, result);
        }
    }
    QString ret = TaskNameString + TaskResultString + TaskDataString;
    return ret;
}

/**
 * @brief CmpJumpWidget::on_radioButtonInput_clicked
 * @author dgq
 * @note 表达式B切换为手动输入的方式
 */
void CmpJumpWidget::on_radioButtonInput_clicked()
{
    if(dataComFrom != 1)
    {
        dataComFrom = 1;
        ui->txtExpressionB->clear();
    }
    if(ui->radioButtonInput->isChecked())
    {
        ui->btnSelectB->setEnabled(false);
        ui->txtExpressionB->setReadOnly(false);
    }
}

/**
 * @brief CmpJumpWidget::on_radioButtonQuote_clicked
 * @author dgq
 * @note 表达式B切换为引用其他结果的方式
 */
void CmpJumpWidget::on_radioButtonQuote_clicked()
{
    if(dataComFrom != 2)
    {
        dataComFrom = 2;
        ui->txtExpressionB->clear();
    }
    if(ui->radioButtonQuote->isChecked())
    {
        ui->btnSelectB->setEnabled(true);
        ui->txtExpressionB->setReadOnly(true);
    }
}

/**
 * @brief CmpJumpWidget::on_btnSelectA_clicked
 * @author dgq
 * @note 表达式A选择数据响应函数
 */
void CmpJumpWidget::on_btnSelectA_clicked()
{
    SelectDataDialog *dlg = new SelectDataDialog(m_step_index);
//    dlg->IniData();
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString list = dlg->GetSelectDataList();
        ui->txtExpressionA->setText(list);
    }
    if(dlg !=NULL)
    {
        delete dlg;
        dlg = NULL;
    }
}

/**
 * @brief CmpJumpWidget::on_btnSelectB_clicked
 * @author dgq
 * @note 表达式B选择数据响应函数
 */
void CmpJumpWidget::on_btnSelectB_clicked()
{
    SelectDataDialog *dlg = new SelectDataDialog(m_step_index);
//    dlg->IniData();
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString list = dlg->GetSelectDataList();
        ui->txtExpressionB->setText(list);
    }
    if(dlg !=NULL)
    {
        delete dlg;
        dlg = NULL;
    }
}

/**
 * @brief CmpJumpWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器，行文本编辑框模拟点击事件
 */
bool CmpJumpWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtExpressionB)
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

}

/**
 * @brief CmpJumpWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘的库
 */
void CmpJumpWidget::LoadKeyBoardLib()
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
