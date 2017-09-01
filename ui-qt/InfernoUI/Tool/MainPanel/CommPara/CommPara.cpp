#include "CommPara.h"
#include "ui_CommPara.h"
#include <qdebug.h>
#include <QMessageBox>
#include "CalibrationWidget/CalibrationParamSelect.h"
#include "IOPortSelectDialog.h"
#include "TaskStepGlobal.h"
#include "ImageSet/ImageParamSelectDialog.h"
CommPara::CommPara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommPara)
{
    ui->setupUi(this);
    OK_IO_Port = -1;
    NG_IO_Port = -1;
    Model_Flag = 0;
    ui->OKIOOutputProtEdit->installEventFilter(this);
    ui->NGIOOutputProtEdit->installEventFilter(this);
    ui->lineEditParamName->installEventFilter(this);
    ui->lineEditScaleParamName->installEventFilter(this);

    Ini_Flag = 1;
    ui->IOTriggerPortCbB->addItem(tr("IO1"));
    ui->IOTriggerPortCbB->addItem(tr("IO2"));

    ui->IOTriggerWayCbB->addItem(tr("上升沿"));
    ui->IOTriggerWayCbB->addItem(tr("下降沿"));
    ui->IOTriggerWayCbB->addItem(tr("高电平"));
    ui->IOTriggerWayCbB->addItem(tr("低电平"));
    ui->lineEdit_Cmd_trigger_string->installEventFilter(this);

    ui->lineEdit_Coms_Param->installEventFilter(this);
}

CommPara::~CommPara()
{
    ui->OKIOOutputProtEdit->removeEventFilter(this);
    ui->NGIOOutputProtEdit->removeEventFilter(this);
    ui->lineEditParamName->removeEventFilter(this);
    ui->lineEditScaleParamName->removeEventFilter(this);
    ui->lineEdit_Cmd_trigger_string->removeEventFilter(this);
    ui->lineEdit_Coms_Param->removeEventFilter(this);

    delete ui;
}
void CommPara::InitData()
{
    Ini_Flag = 1;
    InitIoOutputPara();//初始化io输出参数
    InitIoTriggerParam();//初始化io触发
    InitCalibration();
    InitCmdData();
    InitComsParam();
    ui->txtModifyTaskName->setText(m_strName);
    ui->labelStep->setText(QString::number(task_index)+".");


    Ini_Flag = 0;
}
void CommPara::InitIoOutputPara()
{
    //ui->TaskNamelabel->setText(m_strName);
    unsigned int mode = 0;
    Task_IO_OutPut_Mode_Get(&mode);
    if(mode == 0){
        ui->BasisButton->setChecked(true);
        ui->AdvancedButton->setChecked(false);
        Model_Flag = 0;
    }else{
        ui->BasisButton->setChecked(false);
        ui->AdvancedButton->setChecked(true);
        Model_Flag = 1;
    }

    if(task_index < TS_MAX_NUM){
        int OK_index = Task_Step_OK_IO_Output_Index_Get(task_index);
        if(OK_index > 0 && OK_index < 16){
            ui->OKIOOutputProtEdit->setText("IO"+QString::number(OK_index));
        }else if(OK_index == 0){
            ui->OKIOOutputProtEdit->setText("NULL");
        }

        int NG_index = Task_Step_NG_IO_Output_Index_Get(task_index);
        if(NG_index > 0 && NG_index < 16){
            ui->NGIOOutputProtEdit->setText("IO"+QString::number(NG_index));
        }else if(NG_index == 0){
            ui->NGIOOutputProtEdit->setText("NULL");
        }
    }
}
//基础
void CommPara::on_BasisButton_clicked()
{
    if(ui->BasisButton->isChecked())
    {
        if(Model_Flag == 1)
        {
            QMessageBox::StandardButton rb =
                    QMessageBox::warning(NULL,tr("警告"), tr("切换I/O输出模式将会清除当前的配置数据！请确认是否切换"),
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::Yes)
            {
                Model_Flag = 0;
                Task_IO_OutPut_Mode_Set(0);
                //unsigned int Task_Count = GetTaskStepCount();
                Task_Step_OK_IO_Output_Index_Set(task_index, 0);
                Task_Step_NG_IO_Output_Index_Set(task_index, 0);
                InitIoOutputPara();
            }
            else
            {
                ui->BasisButton->setChecked(false);
                ui->AdvancedButton->setChecked(true);
            }
        }
    }
}
//高级
void CommPara::on_AdvancedButton_clicked()
{
    if(ui->AdvancedButton->isChecked())
    {
        if(Model_Flag == 0)
        {
            QMessageBox::StandardButton rb =
                    QMessageBox::warning(NULL,tr("警告"), tr("切换I/O输出模式将会清除当前的配置数据！请确认是否切换"),
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::Yes)
            {
                Model_Flag = 1;
                Task_IO_OutPut_Mode_Set(1);
                //unsigned int Task_Count = GetTaskStepCount();
                Task_Step_OK_IO_Output_Index_Set(task_index, 0);
                Task_Step_NG_IO_Output_Index_Set(task_index, 0);
            }
            else
            {
                ui->AdvancedButton->setChecked(false);
                ui->BasisButton->setChecked(true);
            }
        }
    }
}
bool CommPara::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->OKIOOutputProtEdit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            IOPortSelectDialog* dlg = new IOPortSelectDialog;
            dlg->SetOKOrNGFlag(1);
            dlg->SetModel(Model_Flag, NG_IO_Port);
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                OK_IO_Port = dlg->GetSelectPortNumber();
                Task_Step_OK_IO_Output_Index_Set(task_index, OK_IO_Port);
                ((QLineEdit*)watched)->setText(dlg->GetSelectString());
            }
            if(dlg !=NULL)
            {
                delete dlg;
                dlg =NULL;
            }
        }
    }
    if(watched == ui->NGIOOutputProtEdit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            IOPortSelectDialog* dlg = new IOPortSelectDialog;
            dlg->SetOKOrNGFlag(0);
            dlg->SetModel(Model_Flag, OK_IO_Port);
            int ret = dlg->exec();
            if(ret == QDialog::Accepted)
            {
                NG_IO_Port = dlg->GetSelectPortNumber();
                Task_Step_NG_IO_Output_Index_Set(task_index, NG_IO_Port);
                ((QLineEdit*)watched)->setText(dlg->GetSelectString());
            }
            if(dlg !=NULL)
            {
                delete dlg;
                dlg =NULL;
            }
        }
    }
    if(watched == ui->lineEditParamName)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            ChangeParam();
        }
    }
    if(watched == ui->lineEditScaleParamName)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            ScaleChangeParam();
        }
    }
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
    if(watched == ui->lineEdit_Coms_Param)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            ComsSelectParam();
        }
    }
    return QWidget::eventFilter(watched, event);
}
void CommPara::InitIoTriggerParam()
{
    if(task_index >= TS_MAX_NUM){
        return;
    }
    unsigned int Trigger_Type = 0;
    int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
    if(ret != 0){
        return;
    }
    else if(Trigger_Type == IO_TRIGGER_TYPE){
        ui->groupBoxTrigger->setChecked(true);
        //ui->IOTriggerPortCbB->setEnabled(true);
        //ui->IOTriggerWayCbB->setEnabled(true);
        unsigned short IO_Port = 0;
        unsigned short IO_Trigger_Type = 0;
        ret = Task_Step_Trigger_IO_Get(task_index, &IO_Port, &IO_Trigger_Type);
        if(ret == 0){
            ui->IOTriggerPortCbB->setCurrentIndex(IO_Port - 1);
            ui->IOTriggerWayCbB->setCurrentIndex(IO_Trigger_Type - 1);
        }
    }else{
        ui->groupBoxTrigger->setChecked(false);
        //ui->IOTriggerPortCbB->setEnabled(false);
        //ui->IOTriggerWayCbB->setEnabled(false);
    }
}

void CommPara::SetTaskIOTriggerParam()
{
    if(task_index >= TS_MAX_NUM)
        return;
    Task_Step_Trigger_IO_Set(task_index, ui->IOTriggerPortCbB->currentIndex()+1, ui->IOTriggerWayCbB->currentIndex()+1);
}

void CommPara::on_IOTriggerWayCbB_currentIndexChanged(int index)
{
    if(Ini_Flag == 1)
        return;
    SetTaskIOTriggerParam();
}

void CommPara::on_IOTriggerPortCbB_currentIndexChanged(int index)
{
    if(Ini_Flag == 1)
        return;
    SetTaskIOTriggerParam();
}
void CommPara::InitCalibration()
{
    unsigned int demarcateRefIndex;
    unsigned int scaleRefIndex;
    //ui->labelStepName->setText(m_strName);
    Task_Step_Homo_Param_Index_Get(task_index, &demarcateRefIndex);
    //SetParamData(strName, i+1);
    UpdateParamReference(demarcateRefIndex);

    Task_Step_Scale_Cali_Param_Index_Get(task_index, &scaleRefIndex);
    if ((scaleRefIndex > 0) && (scaleRefIndex < 17))
    {
        float ratio = GetScaleRatioByIndex(scaleRefIndex - 1);
        UpdateScaleParamRef(scaleRefIndex, ratio);
    }
    else
    {
        UpdateScaleParamRef(0, 0.0);
    }
}

void CommPara::InitComsParam()
{
    int Param_index = Task_Step_Cmos_Param_Index_Get(task_index);
    ShowSelctImageParam(Param_index);
}

void CommPara::UpdateParamReference(int paramIndex)
{
    m_param_index = paramIndex;
    char* name = NULL;
    QString nameString;

    if (paramIndex > 0)
    {
        name = GetHomoParamName(paramIndex - 1);
        nameString = QString::fromUtf8(name);
        ui->lineEditParamName->setText(QString::number(paramIndex) + "." + nameString);
    }
    else
    {
        ui->lineEditParamName->setText("");
    }
}

void CommPara::UpdateScaleParamRef(int paramIndex, float curFloat)
{
    m_scale_param_index = paramIndex;
    m_scale_value = curFloat;

    if (paramIndex > 0)
    {
        ui->lineEditScaleParamName->setText(tr("参数")+QString::number(paramIndex)+"("+QString::number(curFloat)+")");
    }
    else
    {
        ui->lineEditScaleParamName->setText("");
    }
}
void CommPara::ChangeParam()
{
    CalibrationParamSelect dlg;
    dlg.MpdParamListInit();
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
        //        qDebug() << dlg.m_cur_param_index;
        UpdateParamReference(dlg.m_cur_param_index);
        Task_Step_Homo_Param_Index_Set(task_index, dlg.m_cur_param_index);
    }
}
void CommPara::ScaleChangeParam()
{
    CalibrationParamSelect dlg;
    dlg.ScaleParamListInit();
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
        if (dlg.m_scale_param_index > 0)
        {
            UpdateScaleParamRef(dlg.m_scale_param_index, dlg.m_scale_value[dlg.m_scale_param_index - 1]);
        }
        else
        {
            UpdateScaleParamRef(0, 0.0);
        }
        Task_Step_Scale_Cali_Param_Index_Set(task_index, dlg.m_scale_param_index);
    }
}
void CommPara::ShowSelctImageParam(int Param_index)
{
    if(Param_index == 0){
        ui->lineEdit_Coms_Param->setText("");
    }else{
        ui->lineEdit_Coms_Param->setText("参数"+QString::number(Param_index));
    }
}

void CommPara::ComsSelectParam()
{
    ImageParamSelectDialog dlg;
    int ret = dlg.exec();
    if(ret == QDialog::Accepted){
        int index = dlg.GetSelectParamIndex();
        ShowSelctImageParam(index);
        printf("index ===== %d\n",index);
        Task_Step_Cmos_Param_Index_Set(task_index, index);
    }
}

void CommPara::on_groupBoxTrigger_clicked()
{
    if(Ini_Flag == 1)
        return;
    if(task_index >= TS_MAX_NUM)
        return;

    if(ui->groupBoxTrigger->isChecked())
    {
        unsigned int Trigger_Type = 0;
        int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
        if(ret != 0){
            return;
        }else if(Trigger_Type == CMD_TRIGGER_TYPE || Trigger_Type == CON_TRIGGER_TYPE){
            QMessageBox::about(NULL, tr("提示"), tr("该任务已有其他触发,无法设置IO触发!"));
            Ini_Flag = 1;
            ui->groupBoxTrigger->setChecked(false);
            Ini_Flag = 0;
            return;
        }
        ret = Task_Step_Trigger_Type_Set(task_index, IO_TRIGGER_TYPE);
        if(ret != 0)
            return;
        //ui->IOTriggerPortCbB->setEnabled(true);
        //ui->IOTriggerWayCbB->setEnabled(true);
        //ui->groupBoxTrigger->setChecked(true);
        SetTaskIOTriggerParam();
    }
    else
    {
        int ret = Task_Step_Trigger_Type_Set(task_index, NONE_TRIGGER_TYPE);
        if(ret != 0)
            return;
        //ui->IOTriggerPortCbB->setEnabled(false);
        //ui->IOTriggerWayCbB->setEnabled(false);
        //ui->groupBoxTrigger->setChecked(false);
    }
}

void CommPara::on_groupBoxCmd_clicked()
{
    if(Ini_Flag == 1)
        return;
    if(task_index >= TS_MAX_NUM)
        return;

    if(ui->groupBoxCmd->isChecked())
    {
        unsigned int Trigger_Type = 0;
        int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
        if(ret != 0){
            return;
        }else if(Trigger_Type == IO_TRIGGER_TYPE || Trigger_Type == CON_TRIGGER_TYPE){
            QMessageBox::about(NULL, tr("提示"), tr("该任务已有其他触发,无法设置命令触发!"));
            Ini_Flag = 1;
            ui->groupBoxCmd->setChecked(false);
            Ini_Flag = 0;
            return;
        }
        ret = Task_Step_Trigger_Type_Set(task_index, CMD_TRIGGER_TYPE);
        if(ret != 0)
            return;

        ui->lineEdit_Cmd_trigger_string->setText("");
    }
    else
    {
        int ret = Task_Step_Trigger_Type_Set(task_index, NONE_TRIGGER_TYPE);
        if(ret != 0)
            return;
        //ui->lineEdit_Cmd_trigger_string->setEnabled(false);
        //ui->groupBoxTrigger->setChecked(false);
    }
}
void CommPara::InitCmdData()
{
    if(task_index >= TS_MAX_NUM){
        return;
    }
    unsigned int Trigger_Type = 0;
    int ret = Task_Step_Trigger_Type_Get(task_index, &Trigger_Type);
    if(ret != 0){
        return;
    }
    else if(Trigger_Type == CMD_TRIGGER_TYPE){
        //ui->checkBox_Task->setChecked(true);
        ui->groupBoxCmd->setChecked(true);
        char Trigger_cmd[16];
        memset(Trigger_cmd, 0, 16);
        int ret = Task_Step_Trigger_Cmd_Get(task_index, Trigger_cmd);
        if(ret != 0){
            return;
        }
        QString Trigger_String = QString::fromUtf8(Trigger_cmd);
        ui->lineEdit_Cmd_trigger_string->setText(Trigger_String);
    }else{
        ui->groupBoxCmd->setChecked(false);
    }
}

void CommPara::KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len)
{

    m_dlg = m_keyBoard_Lib.GetKeyBoardDialog();
    if(!(dlg_x == 0 && dlg_y == 0))
        m_dlg->move(dlg_x, dlg_y);

    int ret = m_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString labelString =  m_keyBoard_Lib.GetInputString();
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
void CommPara::SetCmdTriggerParam()
{
    if(task_index >= TS_MAX_NUM)
        return;

    QString Trigger_string = ui->lineEdit_Cmd_trigger_string->text();
    QByteArray ba = Trigger_string.toUtf8();
    char *trigger_cmd = ba.data();
    int ret = Task_Step_Trigger_Cmd_Set(task_index, trigger_cmd);
    if(ret != 0)
        return;
}

void CommPara::on_btnModifyTaskName_clicked()
{

    if(ui->txtModifyTaskName->text() == "")
    {
        SetInfor("别名不能为空",0);
        return;
    }

    if(isLegal(ui->txtModifyTaskName->text()))
    {
        SetInfor("别名中含有非法字符",0);
        return;
    }
    if(ui->txtModifyTaskName->text().length() > 16)
    {
        SetInfor("最多支持8个汉字或16字母",0);
        return ;
    }

    QString str = ui->txtModifyTaskName->text();
    const char *buf = str.toUtf8().data();
    int ret =Task_Step_Alias_Set(task_index, buf);
    if(ret == 0)
    {
         SetInfor("别名数据下发成功",1);
    }else
    {
        SetInfor("别名数据下发失败",0);
    }
}

void CommPara::on_btnResetTaskName_clicked()
{
    const char *buf = m_taskNameOrigin.toUtf8().data();
    int ret =Task_Step_Alias_Set(task_index, buf);
    if(ret == 0)
    {
        SetInfor("别名数据下发成功",1);
         ui->txtModifyTaskName->setText(m_taskNameOrigin);
    }else
    {
        SetInfor("别名数据下发失败",0);
    }
}
void CommPara::SetTaskName()
{
    const char *buf = m_taskNameOrigin.toUtf8().data();
    int ret =Task_Step_Alias_Set(task_index, buf);
}

bool CommPara::isLegal(QString text)
{
    if(text.isEmpty())
    {
        return true;
    }

    // 正则表达式判断特殊字符
    //QString pattern("[\\\\/:*?\"<>\\.\\s]");
    QString pattern("[`~!@#$^&*()=|{}':;',\\[\\].<>/?~！@#￥……&*（）——|{}【】‘；：”“'。，、？]");
    QRegExp rx(pattern);
    int match = text.indexOf(rx);
//    qDebug()<<"match:"<<match;
    if(match >= 0)
    {
        return true;
    }

    return false;
}
void CommPara::SetInfor(QString str,int flag)
{
    QPalette pa;

    if(flag == 1)
    {
        pa.setColor(QPalette::WindowText,Qt::darkGreen);
        ui->labelInfor->setPalette(pa);

    }else
    {
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->labelInfor->setPalette(pa);

    }
   ui->labelInfor->setText(str);
}

