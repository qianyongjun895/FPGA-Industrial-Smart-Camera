#include "CmdTriggerItem.h"
#include "ui_CmdTriggerItem.h"
#include <QDebug>
#include <QMessageBox>
#include "TaskStepGlobal.h"
CmdTriggerItem::CmdTriggerItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CmdTriggerItem)
{
    ui->setupUi(this);
    Ini_Flag = 1;
    ui->lineEdit_Cmd_trigger_string->installEventFilter(this);
    ui->txtAddr->installEventFilter(this);
    ui->txtEndSymbol->installEventFilter(this);
    ui->txtNum->installEventFilter(this);
    ui->txtSplit->installEventFilter(this);
    LoadKeyBoardLib();
    ui->comboBoxDataType->addItem(tr("整型"));
    ui->comboBoxDataType->addItem(tr("无符号整型"));
    ui->comboBoxDataType->addItem(tr("浮点型"));
    ui->comboBoxDataType->addItem(tr("双精度型"));
    ui->txtNum->setText("0");
    ui->txtAddr->setText("1");
}

CmdTriggerItem::~CmdTriggerItem()
{
    ui->lineEdit_Cmd_trigger_string->removeEventFilter(this);
    ui->txtAddr->removeEventFilter(this);
    ui->txtEndSymbol->removeEventFilter(this);
    ui->txtNum->removeEventFilter(this);
    ui->txtSplit->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void CmdTriggerItem::SetTaskName(QString TaskName)
{
    Ini_Flag = 1;
    ui->checkBox_Task->setText(TaskName);
    QString task_index_string = TaskName.split(".").at(0);
    unsigned int task_index = task_index_string.toUInt();
    if(task_index >= TS_MAX_NUM){
        Ini_Flag = 0;
        return;
    }

    unsigned int Trigger_Type = 0;
    int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
    if(ret != 0){
        Ini_Flag = 0;
        return;
    }
    else if(Trigger_Type == CMD_TRIGGER_TYPE){
        ui->checkBox_Task->setChecked(true);
        char Trigger_cmd[16];
        memset(Trigger_cmd, 0, 16);
        int ret = Task_Step_Trigger_Cmd_Get(task_index, Trigger_cmd);
        if(ret != 0){
            Ini_Flag = 0;
            return;
        }
        QString Trigger_String = QString::fromUtf8(Trigger_cmd);
        ui->lineEdit_Cmd_trigger_string->setEnabled(true);
        ui->txtAddr->setEnabled(true);
        ui->txtEndSymbol->setEnabled(true);
        ui->txtNum->setEnabled(true);
        ui->txtSplit->setEnabled(true);
        ui->comboBoxDataType->setEnabled(true);
        ui->lineEdit_Cmd_trigger_string->setText(Trigger_String);
    }else{
        ui->lineEdit_Cmd_trigger_string->setEnabled(false);
        ui->txtAddr->setEnabled(false);
        ui->txtEndSymbol->setEnabled(false);
        ui->txtNum->setEnabled(false);
        ui->txtSplit->setEnabled(false);
        ui->comboBoxDataType->setEnabled(false);
    }
    m_data_ptr = Task_Step_Trigger_Cmd_Pointer_Get(task_index);

    STEP_COMMAND_INPUT_INFO *p_input = (STEP_COMMAND_INPUT_INFO*)m_data_ptr;
    int count = (int) p_input->data_cnt;
    QString strCount = QString::number(count);
    ui->txtNum->setText(strCount);
    int iAddr = p_input->addr;
    QString strAddr = QString::number(iAddr);
    ui->txtAddr->setText(strAddr);
    int data_type = p_input->data_type;

    if(data_type == DATA_SINT)
    {
        ui->comboBoxDataType->setCurrentIndex(0);
    }else if(data_type == DATA_UINT)
    {
        ui->comboBoxDataType->setCurrentIndex(1);
    }else if(data_type == DATA_FLT)
    {
        ui->comboBoxDataType->setCurrentIndex(2);
    }else if(data_type == DATA_DBL)
    {
        ui->comboBoxDataType->setCurrentIndex(3);
    }

    char buf[2];
    memset(buf,0,sizeof(buf));
    buf[0]= p_input->separator;
    QString strSplit = QString::fromUtf8(buf);
    ui->txtSplit->setText(strSplit);
    buf[0] = p_input->end_char;
    QString strEnd = QString::fromUtf8(buf);
    ui->txtEndSymbol->setText(strEnd);

    Ini_Flag = 0;
}
QString CmdTriggerItem::GetStrDataType(int index)
{
    QString str = "";
    if(index == DATA_SINT)
    {
        str = "整型";
    }else if(index == DATA_UINT)
    {
        str = "无符号整型";
    }else if(index == DATA_FLT)
    {
        str = "浮点型";
    }else if(index == DATA_DBL)
    {
        str = "双精度型";
    }else
    {
        str = "整型";
    }
    return str;
}
int CmdTriggerItem::GetDataTypeIndex(QString strName)
{
    int  index = 0;
    if(strName == "整型")
    {
        index = DATA_SINT;
    }else if(strName == "无符号整型")
    {
        index = DATA_UINT;
    }else if(strName == "浮点型")
    {
        index = DATA_FLT;
    }else if(strName == "双精度型")
    {
        index = DATA_DBL;
    }else
    {
        index = DATA_SINT;
    }
    return index;
}
void CmdTriggerItem::SetCmdTriggerParam()
{
    QString task_index_string = ui->checkBox_Task->text().split(".").at(0);
    unsigned int task_index = task_index_string.toUInt();
    if(task_index >= TS_MAX_NUM)
        return;

    QString Trigger_string = ui->lineEdit_Cmd_trigger_string->text();
    QByteArray ba = Trigger_string.toUtf8();
    char *trigger_cmd = ba.data();
    int ret = Task_Step_Trigger_Cmd_Set(task_index, trigger_cmd);
    if(ret != 0)
        return;
    STEP_COMMAND_INPUT_INFO *p_input = (STEP_COMMAND_INPUT_INFO*)m_data_ptr;
    p_input->addr = ui->txtAddr->text().toInt();
    p_input->data_cnt = ui->txtNum->text().toInt();
    p_input->data_type = GetDataTypeIndex(ui->comboBoxDataType->currentText());
    p_input->end_char = ui->txtEndSymbol->text().toUtf8().data()[0];
    p_input->separator = ui->txtSplit->text().toUtf8().data()[0];

}

bool CmdTriggerItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_Cmd_trigger_string)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 0, 16);
                SetCmdTriggerParam();
            }
        }
    }
    if(watched == ui->txtEndSymbol || watched == ui->txtSplit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 0, 1);
                SetCmdTriggerParam();
            }
        }
    }
    if(watched == ui->txtNum)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 0, 3);
                SetCmdTriggerParam();
            }
        }
    }
    if(watched == ui->txtAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(((QLineEdit *)watched)->isEnabled())
            {
                KeyBoardDlg(watched, event, 0, 0, 4);
                SetCmdTriggerParam();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}


void CmdTriggerItem::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
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

void CmdTriggerItem::KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len)
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
            SetInputString(((QLineEdit *)watched)->text());
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
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void CmdTriggerItem::on_checkBox_Task_clicked()
{
    if(Ini_Flag == 1)
        return;
    QString task_index_string = ui->checkBox_Task->text().split(".").at(0);
    unsigned int task_index = task_index_string.toUInt();
    if(task_index >= TS_MAX_NUM)
        return;

    if(ui->checkBox_Task->isChecked())
    {
        unsigned int Trigger_Type = 0;
        int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
        if(ret != 0){
            return;
        }else if(Trigger_Type == IO_TRIGGER_TYPE || Trigger_Type == CON_TRIGGER_TYPE){
            QMessageBox::about(NULL, tr("提示"), tr("该任务已有其他触发,无法设置命令触发!"));
            Ini_Flag = 1;
            ui->checkBox_Task->setChecked(false);
            Ini_Flag = 0;
            return;
        }
        ret = Task_Step_Trigger_Type_Set(task_index, CMD_TRIGGER_TYPE);
        if(ret != 0)
            return;

        ui->lineEdit_Cmd_trigger_string->setEnabled(true);
        ui->txtAddr->setEnabled(true);
        ui->txtEndSymbol->setEnabled(true);
        ui->txtNum->setEnabled(true);
        ui->txtSplit->setEnabled(true);
        ui->comboBoxDataType->setEnabled(true);
        ui->lineEdit_Cmd_trigger_string->setText("");
    }
    else
    {
        int ret = Task_Step_Trigger_Type_Set(task_index, NONE_TRIGGER_TYPE);
        if(ret != 0)
            return;
        ui->lineEdit_Cmd_trigger_string->setEnabled(false);
        ui->txtAddr->setEnabled(false);
        ui->txtEndSymbol->setEnabled(false);
        ui->txtNum->setEnabled(false);
        ui->txtSplit->setEnabled(false);
        ui->comboBoxDataType->setEnabled(false);
    }
}


void CmdTriggerItem::on_comboBoxDataType_currentIndexChanged(int index)
{
    if(Ini_Flag == 1)
        return;

    SetCmdTriggerParam();
}
