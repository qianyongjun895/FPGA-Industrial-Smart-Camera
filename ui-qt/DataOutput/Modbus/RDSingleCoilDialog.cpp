#include "RDSingleCoilDialog.h"
#include "ui_RDSingleCoilDialog.h"
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"
#include "ModbusGlobal.h"
#include <QDebug>
#include <QMessageBox>
RDSingleCoilDialog::RDSingleCoilDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RDSingleCoilDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    IniData();
}

void RDSingleCoilDialog::IniData()
{
    ui->lineEdit_CoilAddr->installEventFilter(this);
    ui->lineEdit_CoilAddr->setText("1");

    ui->comboBox_TriggerState->addItem(tr("OFF"));
    ui->comboBox_TriggerState->addItem(tr("ON"));

    ui->comboBox_TriggerAction->addItem(tr("无"));
    ui->comboBox_TriggerAction->addItem(tr("清零"));
    ui->comboBox_TriggerAction->addItem(tr("取反"));
    char taskName[40];
    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(i+1, taskName);
        if(ret != -1)
        {
            ui->comboBox_TaskList->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
        }
    }
}

RDSingleCoilDialog::~RDSingleCoilDialog()
{
    ui->lineEdit_CoilAddr->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void RDSingleCoilDialog::IniSingleCoilData()
{
    ui->lineEdit_CoilAddr->setText("1");
    ui->comboBox_TriggerAction->setCurrentIndex(0);
    ui->comboBox_TriggerState->setCurrentIndex(0);
    ui->comboBox_TaskList->setCurrentIndex(0);
    ui->checkBox_Pre->setChecked(true);
}

void RDSingleCoilDialog::GetSingleCoilData()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_RD_COILS)
        {
            MBS_RD_SINGLE_COIL coil_Data;
            modbus_data_list_get(Data_List_Index, &coil_Data);

            ui->lineEdit_CoilAddr->setText(QString::number(coil_Data.address));
            ui->comboBox_TriggerAction->setCurrentIndex(coil_Data.action_after_rd);
            ui->comboBox_TriggerState->setCurrentIndex(coil_Data.trigger_value);

            ui->comboBox_TaskList->setCurrentIndex(modbus_list_exec_step_get(Data_List_Index) - 1);

            if(modbus_list_pre_post_exec_step_get(Data_List_Index) == MODBUS_EXEC_PRE_STEP)
            {
                ui->checkBox_Pre->setChecked(true);
            }
            else
            {
                ui->checkBox_Pre->setChecked(false);
            }
        }
    }
}

void RDSingleCoilDialog::SetDataListIndex(unsigned int List_Index)
{
    Data_List_Index = List_Index;
}

void RDSingleCoilDialog::SetModbusMode(int mode)
{
    slave_or_host = mode;
}


void RDSingleCoilDialog::SetToolType(int tool)
{
    tool_type = tool;
}
void RDSingleCoilDialog::LoadKeyBoardLib()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void RDSingleCoilDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}


bool RDSingleCoilDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_CoilAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 65536);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void RDSingleCoilDialog::on_btn_Finished_clicked()
{
    MBS_RD_SINGLE_COIL coil_Data;
    coil_Data.address = ui->lineEdit_CoilAddr->text().toInt();
    coil_Data.action_after_rd = ui->comboBox_TriggerAction->currentIndex();
    coil_Data.trigger_value = ui->comboBox_TriggerState->currentIndex();
    modbus_data_list_set(MODBUS_SLAVE_TYPE, Data_List_Index, &coil_Data, SLAVE_RD_COILS);
    modbus_list_exec_step_set(Data_List_Index, ui->comboBox_TaskList->currentIndex()+1);
    if(ui->checkBox_Pre->isChecked())
        modbus_list_pre_post_exec_step_set(Data_List_Index, MODBUS_EXEC_PRE_STEP);
    else
        modbus_list_pre_post_exec_step_set(Data_List_Index, MODBUS_EXEC_POST_STEP);
    QDialog::accept();
}

void RDSingleCoilDialog::on_btn_Cancel_clicked()
{
    QDialog::reject();
}
