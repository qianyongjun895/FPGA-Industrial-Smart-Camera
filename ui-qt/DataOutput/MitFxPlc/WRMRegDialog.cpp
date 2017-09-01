#include "WRMRegDialog.h"
#include "ui_WRMRegDialog.h"
#include "WRMRegItem.h"
#include <QMessageBox>
#include <QDebug>
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"
#include "ProtocolManageGlobal.h"
#include "stdio.h"

WRMRegDialog::WRMRegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WRMRegDialog)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    IniData();
}

WRMRegDialog::~WRMRegDialog()
{
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_Length->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void WRMRegDialog::IniData()
{
    memset(&RD_M_Reg, 0, sizeof(PLC_READ_M_REG));
    memset(&WR_M_Reg, 0, sizeof(PLC_WRITE_M_REG));
    ui->lineEdit_StartAddr->installEventFilter(this);
    ui->lineEdit_Length->installEventFilter(this);
    char taskName[40];
    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(i+1, taskName);
        if(ret != -1)
        {
            ui->comboBox_linkStep->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
        }
    }
    ui->comboBox_linkStep->setCurrentIndex(0);
}

void WRMRegDialog::IniWRMRegData()
{
    ui->lineEdit_StartAddr->setText("1");
    ui->lineEdit_Length->setText("10");
}

void WRMRegDialog::SetCurrentIndex(int index)
{
    Current_index = index;
}

void WRMRegDialog::SetToolType(int tool)
{
    tool_type = tool;
}

void WRMRegDialog::GetWRMRegData()
{
    if(tool_type == M_REG_READ)
    {
        mit_fx_plc_data_list_get(Current_index, &RD_M_Reg);
        ui->lineEdit_StartAddr->setText(QString::number(RD_M_Reg.reg_start));
        ui->lineEdit_Length->setText(QString::number(RD_M_Reg.reg_num));
    }
    else if(tool_type == M_REG_WRITE)
    {
        mit_fx_plc_data_list_get(Current_index, &WR_M_Reg);
        ui->lineEdit_StartAddr->setText(QString::number(WR_M_Reg.reg_start));
        ui->lineEdit_Length->setText(QString::number(WR_M_Reg.reg_num));
    }
    int index = mit_fx_plc_list_exec_step_get(Current_index) - 1;
    if(index > 0)
        ui->comboBox_linkStep->setCurrentIndex(index);

    if(mit_fx_plc_list_pre_post_exec_step_get(Current_index) == DATA_EXEC_PRE_STEP)
    {
        ui->checkBox_step_pre->setChecked(true);
    }
    else
    {
        ui->checkBox_step_pre->setChecked(false);
    }
}


void WRMRegDialog::LoadKeyBoardLib()
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

void WRMRegDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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


bool WRMRegDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_StartAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 10000);
        }
    }
    if(watched == ui->lineEdit_Length)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 256);
        }
    }
    QWidget::eventFilter(watched, event);
}

void WRMRegDialog::AddWRRegItem(WRMRegItem* item)
{
    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->listWidget->count();
    QListWidgetItem* list_item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(list_item, item);
    ui->listWidget->item(size)->setSizeHint(QSize(240, 35));
    ui->listWidget->setCurrentRow(0);
}

void WRMRegDialog::WRMRegCofingChanged(int number, int reg_addr, int data_cnts)
{
    ui->listWidget->clear();
    for(int i = 0; i < data_cnts; i++)
    {
        WRMRegItem* item = new WRMRegItem;
        item->SetNumber(number++);
        item->SetMRegAddr(reg_addr++);
        item->SetToolType(tool_type);
        if(tool_type == M_REG_READ)
        {
            item->SetDataSource(&RD_M_Reg);
        }
        else if(tool_type == M_REG_WRITE)
        {
            item->SetDataSource(&WR_M_Reg);
        }
        AddWRRegItem(item);
    }
}

void WRMRegDialog::WRMRegSetChange()
{
    int start_addr = ui->lineEdit_StartAddr->text().toInt();
    int length = ui->lineEdit_Length->text().toInt();
    ui->label_currentIndex->setText("1");
    current_page = 1;
    if(length > 10)
    {
        WRMRegCofingChanged(1, start_addr, 10);
    }
    else
    {
        WRMRegCofingChanged(1, start_addr, length);
    }
}

void WRMRegDialog::CalcPageData()
{
    int length = ui->lineEdit_Length->text().toInt();
    if(length > 10)
    {
        Page_cnt = ((length -1) / 10) + 1;
        ui->label_PageCnt->setText(QString::number(Page_cnt));
    }
}

void WRMRegDialog::on_lineEdit_StartAddr_textChanged(const QString &arg1)
{
    WRMRegSetChange();
}

void WRMRegDialog::on_lineEdit_Length_textChanged(const QString &arg1)
{
    WRMRegSetChange();
    CalcPageData();
}

void WRMRegDialog::on_btnPrePage_clicked()
{
    if(current_page == 1)
    {
        return;
    }
    else
    {
        current_page--;
        ui->label_currentIndex->setText(QString::number(current_page));
        int number = current_page * 10 - 10 + 1;
        int start_addr = ui->lineEdit_StartAddr->text().toInt();
        int coilAddr = start_addr + number - 1;
        WRMRegCofingChanged(number, coilAddr, 10);
    }
}

void WRMRegDialog::on_btnNextPage_clicked()
{
    if(current_page < Page_cnt)
    {
        current_page++;
        ui->label_currentIndex->setText(QString::number(current_page));
        int number = current_page * 10 - 10 + 1;
        int start_addr = ui->lineEdit_StartAddr->text().toInt();
        int coilAddr = start_addr + number - 1;
        int length = ui->lineEdit_Length->text().toInt();
        if(length > current_page*10)
        {
            WRMRegCofingChanged(number, coilAddr, 10);
        }
        else
        {
            int item_count = length - (current_page - 1)*10;
            WRMRegCofingChanged(number, coilAddr, item_count);
        }
    }
}

void WRMRegDialog::on_btnOk_clicked()
{
    if(tool_type == M_REG_READ)
    {
        RD_M_Reg.reg_start = ui->lineEdit_StartAddr->text().toInt();
        RD_M_Reg.reg_num = ui->lineEdit_Length->text().toInt();
        mit_fx_plc_data_list_set(Current_index, &RD_M_Reg, M_REG_READ);
    }
    else if(tool_type == M_REG_WRITE)
    {
        WR_M_Reg.reg_start = ui->lineEdit_StartAddr->text().toInt();
        WR_M_Reg.reg_num = ui->lineEdit_Length->text().toInt();
        mit_fx_plc_data_list_set(Current_index, &WR_M_Reg, M_REG_WRITE);
    }
    mit_fx_plc_list_exec_step_set(Current_index, ui->comboBox_linkStep->currentIndex() + 1);
    if(ui->checkBox_step_pre->isChecked())
    {
        mit_fx_plc_list_pre_post_exec_step_set(Current_index, DATA_EXEC_PRE_STEP);
    }
    else
    {
        mit_fx_plc_list_pre_post_exec_step_set(Current_index, DATA_EXEC_POST_STEP);
    }
    QDialog::accept();
}

void WRMRegDialog::on_btnquit_clicked()
{
    QDialog::reject();
}
