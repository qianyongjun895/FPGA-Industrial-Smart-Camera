#include "UserDefinedWidget.h"
#include "ui_UserDefinedWidget.h"
#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QListWidgetItem>
#include <QMessageBox>
#include "UserDefinedDataItem.h"
#include "UserDefineSelectDialog.h"
#include "UserDefinedGlobal.h"
#include "CommunicateBase.h"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
UserDefinedWidget::UserDefinedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDefinedWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    list_cnt = 0;
    Change_Flag = 0;
    ui->txtLable->setText("Label");

    ui->checkBoxIncludeLabel->setChecked(false);

    ui->checkBox_Now_send->setChecked(false);
    ui->comboBoxTask->setEnabled(false);

    ui->checkBoxFixWidth->setChecked(false);
    ui->lineEditFieldWidth->setEnabled(false);
    ui->comboBoxFill->setEnabled(false);
    ui->tabWidget->setCurrentIndex(0);
    IniData();
}

void UserDefinedWidget::IniData()
{
    Standard.insert(tr("逗号,"), SEPARATOR_COMMA);
    Standard.insert(tr("空格 "), SEPARATOR_SPACE);
    Standard.insert(tr("冒号:"), SEPARATOR_COLON);
    Standard.insert(tr("斜杠/"), SEPARATOR_SLASH);
    Standard.insert(tr("竖杠|"), SEPARATOR_VERTICAL_BAR);
    Standard.insert(tr("下划线_"), SEPARATOR_UNDERLINE);
    Standard.insert(tr("分号;"), SEPARATOR_SEMICOLON);

    Data_type.insert(tr("整型"), DATA_SINT);
    Data_type.insert(tr("无符号整型"), DATA_UINT);
    Data_type.insert(tr("浮点型"), DATA_FLT);
    Data_type.insert(tr("双精度型"), DATA_DBL);

    Data_Fill.insert(tr("前导空格"), FILL_TYPE_LEADING_SPACE);
    Data_Fill.insert(tr("尾随空格"), FILL_TYPE_TRAILING_SPACE);
    Data_Fill.insert(tr("前导零"), FILL_TYPE_LEADING_ZERO);

    ui->txtStartString->installEventFilter(this);
    ui->txtEndString->installEventFilter(this);
    ui->txtLable->installEventFilter(this);
    ui->lineEditFieldWidth->installEventFilter(this);
    ui->txtOther->installEventFilter(this);

    ui->comboBoxEndSymbol->addItem(tr("无"));
    ui->comboBoxEndSymbol->addItem(tr("回车CR"));
    ui->comboBoxEndSymbol->addItem(tr("换行LF"));
    ui->comboBoxEndSymbol->addItem(tr("CR+LF"));

    ui->comboBoxStandard->addItem(tr("逗号,"));
    ui->comboBoxStandard->addItem(tr("空格 "));
    ui->comboBoxStandard->addItem(tr("冒号:"));
    ui->comboBoxStandard->addItem(tr("斜杠/"));
    ui->comboBoxStandard->addItem(tr("竖杠|"));
    ui->comboBoxStandard->addItem(tr("下划线_"));
    ui->comboBoxStandard->addItem(tr("分号;"));

    ui->comboBoxFill->addItem(tr("前导空格"));
    ui->comboBoxFill->addItem(tr("尾随空格"));
    ui->comboBoxFill->addItem(tr("前导零"));

    char taskName[40];
    char separator[2];

    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(i+1, taskName);
        if(ret != -1)
        {
            ui->comboBoxTask->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
        }
    }

    char txt[USER_DEFINE_TEXT_SIZE];
    memset(txt, 0, USER_DEFINE_TEXT_SIZE);
    user_defined_start_text_get(txt);
    if(strlen(txt) != 0)
        ui->txtStartString->setText(QString::fromUtf8(txt));



    memset(txt, 0, USER_DEFINE_TEXT_SIZE);
    user_defined_end_text_get(txt);
    if(strlen(txt) != 0)
        ui->txtEndString->setText(QString::fromUtf8(txt));

    separator[0] = user_defined_separator_enable_get();
    if(separator[0] == SEPARATOR_ENABLE)
    {
        ui->checkBoxSplit->setChecked(true);
        separator[0] = user_defined_separator_character_get();
        char i = user_defined_separator_type_get();
        if(i == SEPARATOR_TYPE_STANDARD)
        {
            ui->radioButtonStandard->setChecked(true);
            ui->comboBoxStandard->setEnabled(true);
            ui->radioButtonOther->setChecked(false);
            ui->txtOther->setEnabled(false);
            if(Standard.key((int)separator[0]) != NULL)
                ui->comboBoxStandard->setCurrentText(Standard.key((int)separator[0]));
        }
        else
        {
            separator[1] = 0;
            ui->radioButtonStandard->setChecked(false);
            ui->comboBoxStandard->setEnabled(false);
            ui->radioButtonOther->setChecked(true);
            ui->txtOther->setEnabled(true);
            ui->txtOther->setText(QString::fromUtf8(separator));
        }
    }
    else
    {
        ui->checkBoxSplit->setChecked(false);
        ui->radioButtonStandard->setEnabled(false);
        ui->comboBoxStandard->setEnabled(false);
        ui->radioButtonOther->setEnabled(false);
        ui->txtOther->setEnabled(false);
    }
    separator[0] =  user_defined_special_end_character_get();
    if(separator[0] >= SPECIAL_END_CHARACTER_NONE && separator[0] <= SPECIAL_END_CHARACTER_CR_LF)
        ui->comboBoxEndSymbol->setCurrentIndex(separator[0]);

    QStringList DataList;
    unsigned int Data_List_Num = user_defined_data_cnt_get();
    for(unsigned int List_index = 0; List_index < Data_List_Num; List_index++)
    {
        DataVector.clear();
        unsigned int Data_Num = user_defined_source_item_cnt_get(List_index);

        for(unsigned int Data_index = 0; Data_index < Data_Num; Data_index++)
        {
            unsigned int type = user_defined_data_source_type_get(List_index, Data_index);
            if(type == DATA_SOURCE_TYPE_LINK_STEP){
                DataList = InitTaskData(List_index, Data_index);
            }else if(type == DATA_SOURCE_TYPE_G_DATA){
                DataList = InitGData(List_index, Data_index);
            }else{
                DataList = InitManualData(List_index, Data_index);
            }
            if(!DataList.isEmpty())
                DataVector.append(DataList);
        }

        UserDefinedDataItem *userDataItem = new UserDefinedDataItem;
        userDataItem->setAttribute(Qt::WA_DeleteOnClose);
        userDataItem->SetTaskString(DataVector.at(0).at(0));

        char Label[USER_LABEL_DATA_SIZE];
        memset(Label, 0, USER_LABEL_DATA_SIZE);
        user_defined_label_str_get(List_index, Label);
        userDataItem->List_index = List_index;
        userDataItem->m_Label_string = QString::fromUtf8(Label);
        userDataItem->SetLabelString(userDataItem->m_Label_string);
        userDataItem->m_include_Label_flag = user_defined_label_enable_get(List_index);
        userDataItem->m_link_step = user_defined_send_step_get(List_index);

        userDataItem->m_width_flag = user_defined_fixed_width_enable_get(List_index);
        userDataItem->m_data_width = user_defined_fixed_width_get(List_index);
        userDataItem->m_fill = user_defined_fill_type_get(List_index);

        QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetData);
        ui->listWidgetData->setItemWidget(mItem,(QWidget*)userDataItem);
        ui->listWidgetData->item(List_index)->setSizeHint(QSize(240,40));
    }
    if(ui->listWidgetData->count() > 0)
        ui->listWidgetData->setCurrentRow(0);
}

QStringList UserDefinedWidget::InitTaskData(unsigned int List_index, unsigned int Data_index)
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

QStringList UserDefinedWidget::InitGData(unsigned int List_index, unsigned int Data_index)
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

QStringList UserDefinedWidget::InitManualData(unsigned int List_index, unsigned int Data_index)
{
    QStringList DataList;
    DataList.clear();
    float data =0;
    user_defined_manual_input_value_get(List_index, Data_index, &data);

    DataList.append("手动输入");
    DataList.append(QString::number(data, 'g', 3));
    return DataList;
}

UserDefinedWidget::~UserDefinedWidget()
{
    ui->txtStartString->removeEventFilter(this);
    ui->txtEndString->removeEventFilter(this);
    ui->txtLable->removeEventFilter(this);
    ui->lineEditFieldWidth->removeEventFilter(this);
    ui->txtOther->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void UserDefinedWidget::LoadKeyBoardLib()
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

void UserDefinedWidget::on_btnAdd_clicked()
{
    if(ui->listWidgetData->count() >= USER_DEFINE_DATA_LIST_NUM_MAX)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("数据流达到最大限制")+QString::number(USER_DEFINE_DATA_LIST_NUM_MAX)+tr("条,不能继续添加"), QMessageBox::Yes);
        return;
    }

    UserDefineSelectDialog *UserDefinedDlg = new UserDefineSelectDialog();
    UserDefinedDlg->SetDataListIndex(ui->listWidgetData->count());
    int ret = UserDefinedDlg->exec();
    if(ret == QDialog::Accepted)
    {
        UserDefinedDataItem *userDataItem = new UserDefinedDataItem;
        userDataItem->setAttribute(Qt::WA_DeleteOnClose);
        userDataItem->select_data = UserDefinedDlg->GetSelectData();
        QString taskName = userDataItem->select_data;
        userDataItem->SetLabelString("Label");
        userDataItem->SetTaskString(taskName);
        userDataItem->List_index = ui->listWidgetData->count();
        userDataItem->m_include_Label_flag = FALSE;
        userDataItem->m_link_step = SEND_NOW_DISABLE;
        userDataItem->m_width_flag = FALSE;
        int size =ui->listWidgetData->count();
        list_cnt = size + 1;
        QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetData);
        ui->listWidgetData->setItemWidget(mItem,(QWidget*)userDataItem);
        ui->listWidgetData->item(size)->setSizeHint(QSize(240,40));

        ui->listWidgetData->setCurrentRow(size);
        ui->comboBoxFill->setCurrentIndex(0);

        ui->txtLable->setText("Label");

        ui->checkBoxIncludeLabel->setChecked(false);

        ui->checkBox_Now_send->setChecked(false);
        ui->comboBoxTask->setEnabled(false);

        ui->checkBoxFixWidth->setChecked(false);
        ui->lineEditFieldWidth->setEnabled(false);
        ui->comboBoxFill->setEnabled(false);
    }
    delete UserDefinedDlg;
    UserDefinedDlg = NULL;
}

///<标签
void UserDefinedWidget::on_txtLable_textChanged(const QString &arg1)
{
    if(Change_Flag == 1)
        return;

    if(ui->listWidgetData->currentRow() >= 0){
        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        ((UserDefinedDataItem*)DataWidget)->SetLabelString(arg1);
        ListOutPutdata();
    }
}

void UserDefinedWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
                if(num.toInt() > Max_value || num.toInt() < Min_value)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                    return;
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

void UserDefinedWidget::KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, QString str, int String_Len)
{
    Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
    Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
    Fun_SetInputString SetInputString = (Fun_SetInputString)m_keyBoard_Lib.resolve("SetInputString");
    if(GetKeyBoardDlg)
    {
        m_dlg = GetKeyBoardDlg();
        if(!(dlg_x == 0 && dlg_y == 0))
            m_dlg->move(dlg_x, dlg_y);
        if(SetInputString){
            SetInputString(str);
        }
        int ret = m_dlg->exec();
        if(ret == QDialog::Accepted)
        {
            if(GetInputString)
            {
                QString labelString =  GetInputString();
                if(labelString.length() > String_Len)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("请输入长度小于")+QString::number(String_Len + 1)+tr("的字符串"));
                }
                else
                {
                    ((QLineEdit *)watched)->setText(labelString);
                }
            }
        }
        delete m_dlg;
        m_dlg = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

bool UserDefinedWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtStartString || watched == ui->txtEndString)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 0, ((QLineEdit *)watched)->text(), USER_DEFINE_TEXT_SIZE);
            }
        }
    }

    if(watched == ui->txtOther)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 0, ((QLineEdit *)watched)->text(), 1);
            }
        }
    }

    if(watched == ui->txtLable)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 150, ((QLineEdit *)watched)->text(), USER_LABEL_DATA_SIZE);
            }
        }
    }
    if(watched == ui->lineEditFieldWidth)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                NumKeyBoardDlg(watched, event, 1, 30);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}


///<数据流的索引变化
void UserDefinedWidget::on_listWidgetData_currentRowChanged(int currentRow)
{
    if(currentRow < 0)
    {

        return;
    }

    Change_Flag = 1;

    QListWidgetItem *dataItem = ui->listWidgetData->currentItem();
    if(dataItem == NULL)
    {
        return;
    }

    QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);

    ui->txtLable->setText(((UserDefinedDataItem*)DataWidget)->m_Label_string);


    if(((UserDefinedDataItem*)DataWidget)->m_include_Label_flag == TRUE)
    {
        ui->checkBoxIncludeLabel->setChecked(true);
    }
    else
    {
        ui->checkBoxIncludeLabel->setChecked(false);
    }
    if(((UserDefinedDataItem*)DataWidget)->m_link_step == SEND_NOW_DISABLE)
    {
        ui->checkBox_manual_send->setChecked(false);
        ui->checkBox_Now_send->setChecked(false);
        ui->checkBox_Now_send->setEnabled(true);
        ui->comboBoxTask->setEnabled(false);
    }else if((((UserDefinedDataItem*)DataWidget)->m_link_step == 0)){
        ui->checkBox_manual_send->setChecked(true);
        ui->checkBox_Now_send->setChecked(false);
        ui->checkBox_Now_send->setEnabled(false);
        ui->comboBoxTask->setEnabled(false);
    }else{
        ui->checkBox_manual_send->setChecked(false);
        ui->checkBox_Now_send->setEnabled(true);
        ui->checkBox_Now_send->setChecked(true);
        ui->comboBoxTask->setEnabled(true);
        ui->comboBoxTask->setCurrentIndex(((UserDefinedDataItem*)DataWidget)->m_link_step - 1);
    }

    if(((UserDefinedDataItem*)DataWidget)->m_width_flag == TRUE)
    {

        ui->checkBoxFixWidth->setChecked(true);
        ui->lineEditFieldWidth->setEnabled(true);
        ui->lineEditFieldWidth->setText(QString::number(((UserDefinedDataItem*)DataWidget)->m_data_width));

        ui->comboBoxFill->setEnabled(true);
        if(Data_Fill.key(((UserDefinedDataItem*)DataWidget)->m_fill) != NULL)
            ui->comboBoxFill->setCurrentText(Data_Fill.key(((UserDefinedDataItem*)DataWidget)->m_fill));
    }
    else
    {

        ui->checkBoxFixWidth->setChecked(false);
        ui->lineEditFieldWidth->setEnabled(false);
        ui->comboBoxFill->setEnabled(false);
    }
    ListOutPutdata();
    Change_Flag = 0;

}


///<字段宽度
void UserDefinedWidget::on_lineEditFieldWidth_textChanged(const QString &arg1)
{
    if(Change_Flag == 1)
        return;


    if(ui->listWidgetData->currentRow() >= 0)
    {

        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        ((UserDefinedDataItem*)DataWidget)->m_data_width = arg1.toInt();
        ListOutPutdata();
    }

}

///<填充
void UserDefinedWidget::on_comboBoxFill_currentIndexChanged(int index)
{
    if(Change_Flag == 1)
        return;

    if(ui->listWidgetData->currentRow() >= 0)
    {

        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        ((UserDefinedDataItem*)DataWidget)->m_fill = Data_Fill.value(ui->comboBoxFill->currentText());
        ListOutPutdata();
    }
}


///<关联步骤
void UserDefinedWidget::on_comboBoxTask_currentIndexChanged(int index)
{
    if(Change_Flag == 1)
        return;

    if(ui->listWidgetData->currentRow() >= 0)
    {
        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        QString TaskIndex = ui->comboBoxTask->currentText().split(".").at(0);
        ((UserDefinedDataItem*)DataWidget)->m_link_step = TaskIndex.toInt();
    }

}

void UserDefinedWidget::on_checkBoxFixWidth_clicked()
{
    if(Change_Flag == 1)
        return;

    if(ui->listWidgetData->currentRow() >= 0)
    {
        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        if(ui->checkBoxFixWidth->isChecked())
        {
            ((UserDefinedDataItem*)DataWidget)->m_width_flag = TRUE;
            ((UserDefinedDataItem*)DataWidget)->m_fill = Data_Fill.value(ui->comboBoxFill->currentText());
            ((UserDefinedDataItem*)DataWidget)->m_data_width = 8;
            ui->lineEditFieldWidth->setEnabled(true);
            ui->comboBoxFill->setEnabled(true);
        }
        else
        {
            ((UserDefinedDataItem*)DataWidget)->m_width_flag = FALSE;
            ui->lineEditFieldWidth->setEnabled(false);
            ui->comboBoxFill->setEnabled(false);
        }
        ListOutPutdata();
    }
}

void UserDefinedWidget::on_checkBox_Now_send_clicked()
{
    if(Change_Flag == 1)
        return;

    if(ui->listWidgetData->currentRow() >= 0)
    {
        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        if(ui->checkBox_Now_send->isChecked())
        {
            ui->comboBoxTask->setEnabled(true);
            QString TaskIndex = ui->comboBoxTask->currentText().split(".").at(0);
            ((UserDefinedDataItem*)DataWidget)->m_link_step = TaskIndex.toInt();;
        }
        else
        {
            ui->comboBoxTask->setEnabled(false);
            ((UserDefinedDataItem*)DataWidget)->m_link_step = SEND_NOW_DISABLE;
        }
    }
}

void UserDefinedWidget::on_checkBoxIncludeLabel_clicked()
{
    if(Change_Flag == 1)
        return;

    if(ui->listWidgetData->currentRow() >= 0)
    {
        QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
        QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
        if(ui->checkBoxIncludeLabel->isChecked())
        {
            ((UserDefinedDataItem*)DataWidget)->m_include_Label_flag = TRUE;
        }
        else
        {
            ((UserDefinedDataItem*)DataWidget)->m_include_Label_flag = FALSE;
        }
        ListOutPutdata();
    }
}

void UserDefinedWidget::on_checkBoxSplit_clicked()
{
    if(Change_Flag == 1)
        return;

    if(ui->checkBoxSplit->isChecked())
    {
        ui->radioButtonOther->setEnabled(true);
        ui->radioButtonStandard->setEnabled(true);
        ui->radioButtonStandard->setChecked(true);
        ui->comboBoxStandard->setEnabled(true);
    }
    else
    {
        ui->radioButtonOther->setEnabled(false);
        ui->txtOther->setEnabled(false);

        ui->radioButtonStandard->setEnabled(false);
        ui->comboBoxStandard->setEnabled(false);
    }
    ListOutPutdata();
}
//上移
void UserDefinedWidget::on_btnUp_clicked()
{

    int iIndex = ui->listWidgetData->currentRow();

    if(iIndex > 0)
    {
        user_defined_data_list_move_up(iIndex);
        QListWidgetItem *item =  ui->listWidgetData->item(iIndex);
        QWidget *qWidget = ui->listWidgetData->itemWidget(item);

        QListWidgetItem *itemPrev=  ui->listWidgetData->item(iIndex-1);
        QWidget *qWidgetPrev = ui->listWidgetData->itemWidget(itemPrev);

        QString Pre_m_Label_string = ((UserDefinedDataItem*)qWidgetPrev)->m_Label_string;
        int Pre_m_include_Label_flag = ((UserDefinedDataItem*)qWidgetPrev)->m_include_Label_flag;
        int Pre_m_link_step = ((UserDefinedDataItem*)qWidgetPrev)->m_link_step;
        int Pre_m_width_flag = ((UserDefinedDataItem*)qWidgetPrev)->m_width_flag;
        int Pre_m_data_width = ((UserDefinedDataItem*)qWidgetPrev)->m_data_width;
        int Pre_m_fill = ((UserDefinedDataItem*)qWidgetPrev)->m_fill;
        QString Pre_m_Output_string = ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string;
        QString Pre_m_Output_string_num = ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string_num;
        int Pre_List_index = ((UserDefinedDataItem*)qWidgetPrev)->List_index;

        ((UserDefinedDataItem*)qWidgetPrev)->m_Label_string = ((UserDefinedDataItem*)qWidget)->m_Label_string;
        ((UserDefinedDataItem*)qWidgetPrev)->m_include_Label_flag = ((UserDefinedDataItem*)qWidget)->m_include_Label_flag;
        ((UserDefinedDataItem*)qWidgetPrev)->m_link_step = ((UserDefinedDataItem*)qWidget)->m_link_step;
        ((UserDefinedDataItem*)qWidgetPrev)->m_width_flag = ((UserDefinedDataItem*)qWidget)->m_width_flag;
        ((UserDefinedDataItem*)qWidgetPrev)->m_data_width = ((UserDefinedDataItem*)qWidget)->m_data_width;
        ((UserDefinedDataItem*)qWidgetPrev)->m_fill = ((UserDefinedDataItem*)qWidget)->m_fill;
        ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string = ((UserDefinedDataItem*)qWidget)->m_Output_string;
        ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string_num = ((UserDefinedDataItem*)qWidget)->m_Output_string_num;
        ((UserDefinedDataItem*)qWidgetPrev)->List_index = ((UserDefinedDataItem*)qWidget)->List_index;
        ((UserDefinedDataItem*)qWidgetPrev)->SetLabelString(((UserDefinedDataItem*)qWidgetPrev)->m_Label_string);
        ((UserDefinedDataItem*)qWidgetPrev)->SetTaskString(((UserDefinedDataItem*)qWidgetPrev)->select_data);


        ((UserDefinedDataItem*)qWidget)->m_Label_string = Pre_m_Label_string;
        ((UserDefinedDataItem*)qWidget)->m_include_Label_flag = Pre_m_include_Label_flag;///<包括标签
        ((UserDefinedDataItem*)qWidget)->m_link_step = Pre_m_link_step;///<关联步骤
        ((UserDefinedDataItem*)qWidget)->m_width_flag = Pre_m_width_flag;///<固定宽度
        ((UserDefinedDataItem*)qWidget)->m_data_width = Pre_m_data_width;///<字段宽度
        ((UserDefinedDataItem*)qWidget)->m_fill = Pre_m_fill;///填充
        ((UserDefinedDataItem*)qWidget)->m_Output_string = Pre_m_Output_string;
        ((UserDefinedDataItem*)qWidget)->m_Output_string_num = Pre_m_Output_string_num;
        ((UserDefinedDataItem*)qWidget)->List_index = Pre_List_index;
        ((UserDefinedDataItem*)qWidget)->SetLabelString(((UserDefinedDataItem*)qWidget)->m_Label_string);
        ((UserDefinedDataItem*)qWidget)->SetTaskString(((UserDefinedDataItem*)qWidget)->select_data);

        ui->listWidgetData->setCurrentRow(iIndex-1);
    }
}

//下移
void UserDefinedWidget::on_btnDown_clicked()
{

    int iIndex = ui->listWidgetData->currentRow();
    if(iIndex >= 0 && iIndex < ui->listWidgetData->count() - 1)
    {
        user_defined_data_list_move_down(iIndex);
        QListWidgetItem *item =  ui->listWidgetData->item(iIndex);
        QWidget *qWidget = ui->listWidgetData->itemWidget(item);

        QListWidgetItem *itemPrev=  ui->listWidgetData->item(iIndex+1);
        QWidget *qWidgetPrev = ui->listWidgetData->itemWidget(itemPrev);

        QString Pre_m_Label_string = ((UserDefinedDataItem*)qWidgetPrev)->m_Label_string;
        int Pre_m_include_Label_flag = ((UserDefinedDataItem*)qWidgetPrev)->m_include_Label_flag;
        int Pre_m_link_step = ((UserDefinedDataItem*)qWidgetPrev)->m_link_step;
        int Pre_m_width_flag = ((UserDefinedDataItem*)qWidgetPrev)->m_width_flag;
        int Pre_m_data_width = ((UserDefinedDataItem*)qWidgetPrev)->m_data_width;
        int Pre_m_fill = ((UserDefinedDataItem*)qWidgetPrev)->m_fill;
        QString Pre_m_Output_string = ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string;
        QString Pre_m_Output_string_num = ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string_num;
        int Pre_List_index = ((UserDefinedDataItem*)qWidgetPrev)->List_index;

        ((UserDefinedDataItem*)qWidgetPrev)->m_Label_string = ((UserDefinedDataItem*)qWidget)->m_Label_string;
        ((UserDefinedDataItem*)qWidgetPrev)->m_include_Label_flag = ((UserDefinedDataItem*)qWidget)->m_include_Label_flag;
        ((UserDefinedDataItem*)qWidgetPrev)->m_link_step = ((UserDefinedDataItem*)qWidget)->m_link_step;
        ((UserDefinedDataItem*)qWidgetPrev)->m_width_flag = ((UserDefinedDataItem*)qWidget)->m_width_flag;
        ((UserDefinedDataItem*)qWidgetPrev)->m_data_width = ((UserDefinedDataItem*)qWidget)->m_data_width;
        ((UserDefinedDataItem*)qWidgetPrev)->m_fill = ((UserDefinedDataItem*)qWidget)->m_fill;
        ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string = ((UserDefinedDataItem*)qWidget)->m_Output_string;
        ((UserDefinedDataItem*)qWidgetPrev)->m_Output_string_num = ((UserDefinedDataItem*)qWidget)->m_Output_string_num;
        ((UserDefinedDataItem*)qWidgetPrev)->List_index = ((UserDefinedDataItem*)qWidget)->List_index;
        ((UserDefinedDataItem*)qWidgetPrev)->SetLabelString(((UserDefinedDataItem*)qWidgetPrev)->m_Label_string);
        ((UserDefinedDataItem*)qWidgetPrev)->SetTaskString(((UserDefinedDataItem*)qWidgetPrev)->select_data);


        ((UserDefinedDataItem*)qWidget)->m_Label_string = Pre_m_Label_string;
        ((UserDefinedDataItem*)qWidget)->m_include_Label_flag = Pre_m_include_Label_flag;///<包括标签
        ((UserDefinedDataItem*)qWidget)->m_link_step = Pre_m_link_step;///<关联步骤
        ((UserDefinedDataItem*)qWidget)->m_width_flag = Pre_m_width_flag;///<固定宽度
        ((UserDefinedDataItem*)qWidget)->m_data_width = Pre_m_data_width;///<字段宽度
        ((UserDefinedDataItem*)qWidget)->m_fill = Pre_m_fill;///填充
        ((UserDefinedDataItem*)qWidget)->m_Output_string = Pre_m_Output_string;
        ((UserDefinedDataItem*)qWidget)->m_Output_string_num = Pre_m_Output_string_num;
        ((UserDefinedDataItem*)qWidget)->List_index = Pre_List_index;
        ((UserDefinedDataItem*)qWidget)->SetLabelString(((UserDefinedDataItem*)qWidget)->m_Label_string);
        ((UserDefinedDataItem*)qWidget)->SetTaskString(((UserDefinedDataItem*)qWidget)->select_data);

        ui->listWidgetData->setCurrentRow(iIndex+1);
    }
}

void UserDefinedWidget::on_btnDelete_clicked()
{

    int iIndex = ui->listWidgetData->currentRow();
    if(iIndex !=-1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定要删除列表中数据?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            QListWidgetItem *Listitem = ui->listWidgetData->takeItem(iIndex);
            delete Listitem;
            user_defined_data_list_del(iIndex);
            list_cnt--;
        }
        if(ui->listWidgetData->count() == 0)
        {
            ui->txtOutput->setText("");
        }
    }else
    {
        QMessageBox::about(NULL,tr("提示"),tr("请选中行，然后删除"));
    }

}

void UserDefinedWidget::on_radioButtonStandard_clicked()
{
    if(Change_Flag == 1)
        return;

    if(ui->radioButtonStandard->isChecked())
    {
        ui->txtOther->setEnabled(false);
        ui->comboBoxStandard->setEnabled(true);
    }
    else
    {
        ui->comboBoxStandard->setEnabled(false);
    }
    ListOutPutdata();
}

void UserDefinedWidget::on_radioButtonOther_clicked()
{
    if(Change_Flag == 1)
        return;

    if(ui->radioButtonOther->isChecked())
    {
        ui->txtOther->setEnabled(true);
        ui->comboBoxStandard->setEnabled(false);
    }
    else
    {
        ui->txtOther->setEnabled(false);
    }
    ListOutPutdata();
}

QString UserDefinedWidget::FillOutPutdata(QString str,QString strNumber)
{
    int i = 0;
    QString strRet = "";
    strRet = str;
    if(ui->checkBoxFixWidth->isChecked())
    {
        int width = ui->lineEditFieldWidth->text().toInt();
        if(width > 0)
        {
            if(ui->comboBoxFill->currentIndex() == 0)
            {
                for(i = 0; i<width;i++)
                    strRet = " "+ strRet;

            }else if(ui->comboBoxFill->currentIndex() == 1)
            {
                for(i = 0; i<width;i++)
                    strRet = strRet + " ";

            }else if(ui->comboBoxFill->currentIndex() == 2)
            {
                for(i = 0; i<width;i++)
                    strRet = "0"+strRet ;
            }
        }
    }
    return strRet;
}

//显示输出字符串
void UserDefinedWidget::ListOutPutdata()
{
    int i;
    QString strSplit = "";
    if(ui->checkBoxSplit->isChecked())
    {
        if(ui->radioButtonStandard->isChecked())
        {
            if(ui->comboBoxStandard->currentIndex() ==0)
            {
                strSplit = ",";

            }else if(ui->comboBoxStandard->currentIndex() ==1)
            {
                strSplit = " ";
            }else if(ui->comboBoxStandard->currentIndex() ==2)
            {
                strSplit = ":";
            }else if(ui->comboBoxStandard->currentIndex() ==3)
            {
                strSplit = "/";
            }else if(ui->comboBoxStandard->currentIndex() ==4)
            {
                strSplit = "|";
            }else if(ui->comboBoxStandard->currentIndex() ==5)
            {
                strSplit = ";";
            }
        }else
        {
            if(ui->radioButtonOther->isChecked())
            {
                strSplit = ui->txtOther->text();
            }
        }

    }else
    {
        strSplit = "";
    }

    QString strdata="";

    int ipos = ui->listWidgetData->currentRow();
    if(ipos >= 0)
    {
        QListWidgetItem *item =  ui->listWidgetData->item(ipos);
        QWidget *qWidget = ui->listWidgetData->itemWidget(item);
        unsigned int count = user_defined_source_item_cnt_get(ipos);
        QString stTemp;
        QString strData;
        QString strListData;
        for(i = 0; i<count;i++)
        {

            stTemp = FillOutPutdata("Data"+QString::number(i),QString::number(i));

            if(i == 0)
            {
                strData = stTemp;

            }else
            {
                strData += strSplit;
                strData += stTemp;
            }
        }
        if(ui->checkBoxIncludeLabel->isChecked())
        {
            strListData = ui->txtStartString->text()+((UserDefinedDataItem*)qWidget)->m_Label_string+strData+ui->txtEndString->text();
        }
        else
        {
            strListData = ui->txtStartString->text()+strData+ui->txtEndString->text();
        }

        ui->txtOutput->setText(strListData);
        int len = ui->txtOutput->toPlainText().length();
        ui->labelNum->setText(QString::number(len));
    }
}

void UserDefinedWidget::SetUserDefinedData()
{

    char *text = NULL;

    /** 设置开头文本 */
    QString StartString = ui->txtStartString->text();
    QByteArray start_ba = StartString.toUtf8();
    text = start_ba.data();
    user_defined_start_text_set(text);
    /** @brief 设置结束文本 */
    QString EndString = ui->txtEndString->text();
    QByteArray end_ba = EndString.toUtf8();
    text = end_ba.data();
    user_defined_end_text_set(text);
    /** @brief 设置分隔符 */
    if(ui->checkBoxSplit->isChecked())
    {
        user_defined_separator_enable_set(SEPARATOR_ENABLE);
        if(ui->radioButtonStandard->isChecked())
        {
            user_defined_separator_type_set(SEPARATOR_TYPE_STANDARD);
            user_defined_separator_character_set(Standard.value(ui->comboBoxStandard->currentText()));
        }
        else
        {
            user_defined_separator_type_set(SEPARATOR_TYPE_OTHER);
            char * separator = ui->txtOther->text().toUtf8().data();
            user_defined_separator_character_set(*separator);
        }
    }
    else
    {
        user_defined_separator_enable_set(SEPARATOR_DISABLE);
    }
    /** @brief 设置结束符 */
    user_defined_special_end_character_set(ui->comboBoxEndSymbol->currentIndex());

    user_defined_data_cnt_set(ui->listWidgetData->count());///<设置数据流数量
    for(unsigned int i = 0; i < (unsigned int)ui->listWidgetData->count(); i++)
    {
        QListWidgetItem *widgetItem = ui->listWidgetData->item(i);
        QWidget *data_Widget = ui->listWidgetData->itemWidget(widgetItem);

        QByteArray Label_ba =  ((UserDefinedDataItem*)data_Widget)->m_Label_string.toUtf8();
        char *Label = Label_ba.data();
        user_defined_label_str_set(i, Label);
        user_defined_label_enable_set(i, ((UserDefinedDataItem*)data_Widget)->m_include_Label_flag);
        user_defined_send_step_set(i, ((UserDefinedDataItem*)data_Widget)->m_link_step);
        user_defined_fixed_width_enable_set(i, ((UserDefinedDataItem*)data_Widget)->m_width_flag);
        user_defined_fixed_width_set(i, ((UserDefinedDataItem*)data_Widget)->m_data_width);
        user_defined_fill_type_set(i, ((UserDefinedDataItem*)data_Widget)->m_fill);
    }
}

void UserDefinedWidget::SetTaskData(unsigned int list_index, unsigned int data_index, QStringList list_string, QString task_string)
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
        }
        user_defined_data_source_type_set(list_index, data_index, DATA_SOURCE_TYPE_LINK_STEP);
    }
}

void UserDefinedWidget::SetGData(unsigned int list_index, unsigned int data_index, unsigned int type, unsigned int addr)
{
    user_defined_g_data_info_set(list_index, data_index, type, addr);
    user_defined_data_source_type_set(list_index, data_index, DATA_SOURCE_TYPE_G_DATA);
}

void UserDefinedWidget::SetManualData(unsigned int list_index, unsigned int data_index, float data)
{
    user_defined_manual_input_value_set(list_index, data_index, data);
    user_defined_data_source_type_set(list_index, data_index, DATA_SOURCE_TYPE_MANUAL_INPUT);
}

void UserDefinedWidget::on_comboBoxStandard_currentIndexChanged(int index)
{
    if(Change_Flag == 1)
        return;

    ListOutPutdata();
}

void UserDefinedWidget::on_txtOther_textChanged(const QString &arg1)
{
    if(Change_Flag == 1)
        return;

    ListOutPutdata();

}

void UserDefinedWidget::AddCmdTriggerItem(CmdTriggerItem* item)
{

    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->listWidget_Cmd_Trigger->count();
    QListWidgetItem *List_item = new QListWidgetItem(ui->listWidget_Cmd_Trigger);
    ui->listWidget_Cmd_Trigger->setItemWidget(List_item, (QWidget*)item);
    ui->listWidget_Cmd_Trigger->item(size)->setSizeHint(QSize(240, 45));
    ui->listWidget_Cmd_Trigger->setCurrentRow(0);
}

void UserDefinedWidget::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        char taskName[40];
        ui->listWidget_Cmd_Trigger->clear();
        for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
        {
            memset(taskName, 0, 40);
            int ret = Get_Task_Name(i+1, taskName);
            if(ret != -1)
            {
                CmdTriggerItem* item = new CmdTriggerItem;
                item->SetTaskName(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
                AddCmdTriggerItem(item);
            }
        }
    }
}

void UserDefinedWidget::on_txtEndString_textChanged(const QString &arg1)
{
    if(Change_Flag == 1)
        return;

    ListOutPutdata();
}

void UserDefinedWidget::on_txtStartString_textChanged(const QString &arg1)
{
    if(Change_Flag == 1)
        return;

    ListOutPutdata();
}

void UserDefinedWidget::on_checkBox_manual_send_clicked()
{
    if(Change_Flag == 1)
        return;
    if(ui->listWidgetData->currentRow() < 0){
        return;
    }
    QListWidgetItem *dataItem =  ui->listWidgetData->item(ui->listWidgetData->currentRow());
    QWidget *DataWidget = ui->listWidgetData->itemWidget(dataItem);
    if(ui->checkBox_manual_send->isChecked()){
        ((UserDefinedDataItem*)DataWidget)->m_link_step = 0;
        ui->checkBox_Now_send->setChecked(false);
        ui->checkBox_Now_send->setEnabled(false);
        ui->comboBoxTask->setEnabled(false);
    }else{
        ui->checkBox_Now_send->setEnabled(true);
        ((UserDefinedDataItem*)DataWidget)->m_link_step = SEND_NOW_DISABLE;
    }
}
