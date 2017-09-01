#include "ReadRegDialog.h"
#include "ui_ReadRegDialog.h"
#include "CommunicateBase.h"
#include "ProtocolManageGlobal.h"
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"
#include <QDebug>
#include <QMessageBox>

ReadRegDialog::ReadRegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadRegDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    IniData();
}

ReadRegDialog::~ReadRegDialog()
{
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_ReadNum->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void ReadRegDialog::IniData()
{
    Data_type.insert(tr("int"), DATA_SINT);
    Data_type.insert(tr("float"), DATA_FLT);
    Data_type.insert(tr("double"), DATA_DBL);
    ui->comboBox_DataType->addItem(tr("int"));
    ui->comboBox_DataType->addItem(tr("float"));
    ui->comboBox_DataType->addItem(tr("double"));
    char taskName[40];
    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(i+1, taskName);
        if(ret != -1)
        {
            ui->comboBox_TaskType->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
        }
    }

    ui->lineEdit_StartAddr->installEventFilter(this);
    ui->lineEdit_ReadNum->installEventFilter(this);
}

void ReadRegDialog::IniRegData()
{
    ui->lineEdit_StartAddr->setText("1");
    ui->lineEdit_ReadNum->setText("4");
    ui->comboBox_DataType->setCurrentIndex(0);
    ui->comboBox_TaskType->setCurrentIndex(0);
    ui->checkBox_Pre->setChecked(true);

}

void ReadRegDialog::GetRegData()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_RD_HOLD_REG)
        {
            modbus_data_list_get(Data_List_Index, &S_RD_Hold_Reg_Data);
            ui->lineEdit_StartAddr->setText(QString::number(S_RD_Hold_Reg_Data.address));
            ui->lineEdit_ReadNum->setText(QString::number(S_RD_Hold_Reg_Data.length));
            ui->comboBox_DataType->setCurrentText(Data_type.key(S_RD_Hold_Reg_Data.data_type));
        }
    }
    else if(slave_or_host == MODBUS_HOST_TYPE)
    {
        if(tool_type == HOST_RD_HOLD_REG)
        {
            modbus_data_list_get(Data_List_Index, &H_RD_Hold_Reg_Data);
            ui->lineEdit_StartAddr->setText(QString::number(H_RD_Hold_Reg_Data.address));
            ui->lineEdit_ReadNum->setText(QString::number(H_RD_Hold_Reg_Data.length));
            ui->comboBox_DataType->setCurrentText(Data_type.key(H_RD_Hold_Reg_Data.data_type));
        }
        else if(tool_type == HOST_RD_INPUT_REG)
        {
            modbus_data_list_get(Data_List_Index, &H_RD_Input_Reg_Data);
            ui->lineEdit_StartAddr->setText(QString::number(H_RD_Input_Reg_Data.address));
            ui->lineEdit_ReadNum->setText(QString::number(H_RD_Input_Reg_Data.length));
            ui->comboBox_DataType->setCurrentText(Data_type.key(H_RD_Input_Reg_Data.data_type));
        }
    }
    int index = modbus_list_exec_step_get(Data_List_Index) - 1;
    if(index >= 0)
        ui->comboBox_TaskType->setCurrentIndex(index);
    if(modbus_list_pre_post_exec_step_get(Data_List_Index) == MODBUS_EXEC_PRE_STEP)
    {
        ui->checkBox_Pre->setChecked(true);
    }
    else
    {
        ui->checkBox_Pre->setChecked(false);
    }
}

void ReadRegDialog::SetDataListIndex(int List_Index)
{
    Data_List_Index = List_Index;
}

void ReadRegDialog::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void ReadRegDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

void ReadRegDialog::SetModbusMode(int mode)
{
    slave_or_host = mode;
}

void ReadRegDialog::SetToolType(int tool)
{
    tool_type = tool;
}

bool ReadRegDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_StartAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 65536);
        }
    }
    if(watched == ui->lineEdit_ReadNum)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(slave_or_host == MODBUS_SLAVE_TYPE)
            {
                if(tool_type == SLAVE_RD_HOLD_REG)
                {
                    if(125 + ui->lineEdit_StartAddr->text().toInt() < 65536)
                    {
                        NumKeyBoardDlg(watched, event, 1, 125);
                    }
                    else if(ui->lineEdit_StartAddr->text().toInt() == 65536)
                    {
                        NumKeyBoardDlg(watched, event, 1, 1);
                    }
                    else
                    {
                        NumKeyBoardDlg(watched, event, 1, 65536 - ui->lineEdit_StartAddr->text().toInt());
                    }
                }
            }
            else if(slave_or_host == MODBUS_HOST_TYPE)
            {
                if(123 + ui->lineEdit_StartAddr->text().toInt() < 65536)
                {
                    NumKeyBoardDlg(watched, event, 1, 123);
                }
                else if(ui->lineEdit_StartAddr->text().toInt() == 65536)
                {
                    NumKeyBoardDlg(watched, event, 1, 1);
                }
                else
                {
                    NumKeyBoardDlg(watched, event, 1, 65536 - ui->lineEdit_StartAddr->text().toInt());
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void ReadRegDialog::on_btn_Finish_clicked()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_RD_HOLD_REG)
        {
            S_RD_Hold_Reg_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            S_RD_Hold_Reg_Data.length = ui->lineEdit_ReadNum->text().toUInt();
            S_RD_Hold_Reg_Data.data_type = Data_type.value(ui->comboBox_DataType->currentText());
            modbus_data_list_set(slave_or_host, Data_List_Index, &S_RD_Hold_Reg_Data, tool_type);
        }
    }
    else if(slave_or_host == MODBUS_HOST_TYPE)
    {
        if(tool_type == HOST_RD_HOLD_REG)
        {
            H_RD_Hold_Reg_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            H_RD_Hold_Reg_Data.length = ui->lineEdit_ReadNum->text().toUInt();
            H_RD_Hold_Reg_Data.data_type = Data_type.value(ui->comboBox_DataType->currentText());
            modbus_data_list_set(slave_or_host, Data_List_Index, &H_RD_Hold_Reg_Data, tool_type);
        }
        else if(tool_type == HOST_RD_INPUT_REG)
        {
            H_RD_Input_Reg_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            H_RD_Input_Reg_Data.length = ui->lineEdit_ReadNum->text().toUInt();
            H_RD_Input_Reg_Data.data_type = Data_type.value(ui->comboBox_DataType->currentText());
            modbus_data_list_set(slave_or_host, Data_List_Index, &H_RD_Input_Reg_Data, tool_type);
        }
    }
    modbus_list_exec_step_set(Data_List_Index, ui->comboBox_TaskType->currentIndex()+1);
    if(ui->checkBox_Pre->isChecked())
    {
        modbus_list_pre_post_exec_step_set(Data_List_Index, MODBUS_EXEC_PRE_STEP);
    }
    else
    {
        modbus_list_pre_post_exec_step_set(Data_List_Index, MODBUS_EXEC_POST_STEP);
    }
    QDialog::accept();
}

void ReadRegDialog::on_btn_Cancel_clicked()
{
    QDialog::reject();
}
