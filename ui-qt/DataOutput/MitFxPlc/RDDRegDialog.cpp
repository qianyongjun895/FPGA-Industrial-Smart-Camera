#include "RDDRegDialog.h"
#include "ui_RDDRegDialog.h"
#include <QMessageBox>
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"
#include "ProtocolManageGlobal.h"
#include "CommunicateBase.h"
#include <QDebug>
RDDRegDialog::RDDRegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RDDRegDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    ui->lineEdit_StartAddr->installEventFilter(this);
    ui->lineEdit_ReadNum->installEventFilter(this);

    Data_type.insert(tr("int"), DATA_SINT);
    Data_type.insert(tr("float"), DATA_FLT);
    Data_type.insert(tr("double"), DATA_DBL);

    ui->comboBox_DataType->addItem("int");
    ui->comboBox_DataType->addItem("float");
    ui->comboBox_DataType->addItem("double");

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

RDDRegDialog::~RDDRegDialog()
{
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_ReadNum->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void RDDRegDialog::IniRDDRegData()
{
    ui->lineEdit_StartAddr->setText("1");
    ui->lineEdit_ReadNum->setText("4");
    ui->comboBox_DataType->setCurrentIndex(0);
    ui->comboBox_TaskList->setCurrentIndex(0);
}

void RDDRegDialog::GetRDDRegData()
{
    mit_fx_plc_data_list_get(Current_index, &RD_D_Reg);
    ui->lineEdit_StartAddr->setText(QString::number(RD_D_Reg.reg_start));
    ui->lineEdit_ReadNum->setText(QString::number(RD_D_Reg.reg_num));
    ui->comboBox_DataType->setCurrentText(Data_type.key(RD_D_Reg.data_type));

    int index = mit_fx_plc_list_exec_step_get(Current_index) - 1;
    if(index > 0)
        ui->comboBox_TaskList->setCurrentIndex(index);

    if(mit_fx_plc_list_pre_post_exec_step_get(Current_index) == DATA_EXEC_PRE_STEP)
    {
        ui->checkBox_Pre->setChecked(true);
    }
    else
    {
        ui->checkBox_Pre->setChecked(false);
    }
}

bool RDDRegDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_StartAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 10000);
        }
    }
    if(watched == ui->lineEdit_ReadNum)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 64);
        }
    }
    QWidget::eventFilter(watched, event);
}

void RDDRegDialog::LoadKeyBoardLib()
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

void RDDRegDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
                if(Max_value == 0 && Min_value == 0)
                {
                }
                else if(num.toInt() > Max_value || num.toInt() < Min_value)
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


void RDDRegDialog::SetToolType(int tool)
{
    tool_type = tool;
}

void RDDRegDialog::SetCurrentIndex(int index)
{
    Current_index = index;
}

void RDDRegDialog::on_btn_Finish_clicked()
{
    RD_D_Reg.reg_start = ui->lineEdit_StartAddr->text().toInt();
    RD_D_Reg.reg_num = ui->lineEdit_ReadNum->text().toInt();
    RD_D_Reg.data_type = Data_type.value(ui->comboBox_DataType->currentText());
    mit_fx_plc_data_list_set(Current_index, &RD_D_Reg, D_REG_READ);

    mit_fx_plc_list_exec_step_set(Current_index, ui->comboBox_TaskList->currentIndex()+1);

    if(ui->checkBox_Pre->isChecked())
    {
        mit_fx_plc_list_pre_post_exec_step_set(Current_index, DATA_EXEC_PRE_STEP);
    }
    else
    {
        mit_fx_plc_list_pre_post_exec_step_set(Current_index, DATA_EXEC_POST_STEP);
    }
    QDialog::accept();
}

void RDDRegDialog::on_btn_Cancel_clicked()
{
    QDialog::reject();
}
