#include "IntercomMultiRegDialog.h"
#include "ui_IntercomMultiRegDialog.h"
#include "CommunicateBase.h"
#include "ProtocolManageGlobal.h"
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"
#include <QDebug>
#include <QMessageBox>
#include "IntercomMultiRegItem.h"
#include "stdio.h"
IntercomMultiRegDialog::IntercomMultiRegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntercomMultiRegDialog)
{
    ui->setupUi(this);
    Ini_Flag = 0;
    LoadKeyBoardLib();
    IniData();
}

IntercomMultiRegDialog::~IntercomMultiRegDialog()
{
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_Length->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void IntercomMultiRegDialog::IniData()
{
    Page_cnt = 1;
    current_page = 1;
    ui->lineEdit_StartAddr->installEventFilter(this);
    ui->lineEdit_Length->installEventFilter(this);

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
    ui->comboBox_DataType->addItem("int");
    ui->comboBox_DataType->addItem("int inverse");
    ui->comboBox_DataType->addItem("uint");
    ui->comboBox_DataType->addItem("uint inverse");
    ui->comboBox_DataType->addItem("float");
    ui->comboBox_DataType->addItem("float inverse");
    ui->comboBox_DataType->addItem("long");
    ui->comboBox_DataType->addItem("long inverse");
    ui->comboBox_DataType->addItem("double");
    ui->comboBox_DataType->addItem("double inverse");
}

void IntercomMultiRegDialog::IniRegData()
{
    ui->lineEdit_StartAddr->setText("1");
    ui->lineEdit_Length->setText("8");

    ui->comboBox_DataType->setCurrentIndex(0);
    ui->comboBox_TaskList->setCurrentIndex(0);
    ui->checkBox_Pre->setChecked(false);
}

void IntercomMultiRegDialog::GetRegData()
{
    Ini_Flag = 1;

    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_WR_HOLD_REG)
        {
            intercom_modbus_data_list_get(Data_List_Index, &S_WR_Hold_Reg_Data);

            ui->lineEdit_StartAddr->setText(QString::number(S_WR_Hold_Reg_Data.address));
            ui->lineEdit_Length->setText(QString::number(S_WR_Hold_Reg_Data.length));
            ui->comboBox_DataType->setCurrentIndex(S_WR_Hold_Reg_Data.data_type);
        }
        else if(tool_type == SLAVE_WR_INPUT_REG)
        {
            intercom_modbus_data_list_get(Data_List_Index, &S_WR_Input_Reg_Data);

            ui->lineEdit_StartAddr->setText(QString::number(S_WR_Input_Reg_Data.address));
            ui->lineEdit_Length->setText(QString::number(S_WR_Input_Reg_Data.length));
            ui->comboBox_DataType->setCurrentIndex(S_WR_Input_Reg_Data.data_type);
        }
    }
    else
    {
        if(tool_type == HOST_WR_HOLD_REG)
        {
            intercom_modbus_data_list_get(Data_List_Index, &H_WR_Hold_Reg_Data);

            ui->lineEdit_StartAddr->setText(QString::number(H_WR_Hold_Reg_Data.address));
            ui->lineEdit_Length->setText(QString::number(H_WR_Hold_Reg_Data.length));
            ui->comboBox_DataType->setCurrentIndex(H_WR_Hold_Reg_Data.data_type);
        }
    }


    ui->comboBox_TaskList->setCurrentIndex(intercom_modbus_list_exec_step_get(Data_List_Index) - 1);

    if(intercom_modbus_list_pre_post_exec_step_get(Data_List_Index) == MODBUS_EXEC_PRE_STEP)
    {
        ui->checkBox_Pre->setChecked(true);
    }
    else
    {
        ui->checkBox_Pre->setChecked(false);
    }
}

void IntercomMultiRegDialog::SetDataListIndex(int List_Index)
{
    Data_List_Index = List_Index;
}

void IntercomMultiRegDialog::LoadKeyBoardLib()
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

void IntercomMultiRegDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

void IntercomMultiRegDialog::SetModbusMode(int mode)
{
    slave_or_host = mode;
}

void IntercomMultiRegDialog::SetToolType(int tool)
{
    tool_type = tool;
}

bool IntercomMultiRegDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_StartAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 65536);
        }
    }
    if(watched == ui->lineEdit_Length)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(slave_or_host == MODBUS_SLAVE_TYPE)
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
            else
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

void IntercomMultiRegDialog::AddMultiRegItem(IntercomMultiRegItem *item)
{
    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->listWidget_Reg->count();
    QListWidgetItem *list_item = new QListWidgetItem(ui->listWidget_Reg);
    ui->listWidget_Reg->setItemWidget(list_item, item);
    ui->listWidget_Reg->item(size)->setSizeHint(QSize(240,45));
}
void IntercomMultiRegDialog::RegSetChanged()
{
    if(Ini_Flag == 0)
    {
        memset(&H_WR_Hold_Reg_Data, 0, sizeof(H_WR_Hold_Reg_Data));
        memset(&S_WR_Hold_Reg_Data, 0, sizeof(H_WR_Hold_Reg_Data));
        memset(&S_WR_Input_Reg_Data, 0, sizeof(H_WR_Hold_Reg_Data));
    }
    int start_addr = ui->lineEdit_StartAddr->text().toInt();
    int length = ui->lineEdit_Length->text().toInt();
    ui->current_Page_label->setText("1");
    current_page = 1;
    if(length > 8)
    {
        RegCofingChanged(1, start_addr, 8);
    }
    else
    {
        RegCofingChanged(1, start_addr, length);
    }
}

void IntercomMultiRegDialog::RegCofingChanged(int number, int coil_addr, int data_cnts)
{
    ui->listWidget_Reg->clear();
    for(int i = 1; i <= data_cnts; i++)
    {
        IntercomMultiRegItem * item = new IntercomMultiRegItem;
        item->SetNumber(number++);
        item->SetRegAddr(coil_addr++);
        item->SetDataType(ui->comboBox_DataType->currentIndex(), ui->lineEdit_Length->text().toInt());
        item->SetModbusMode(slave_or_host);
        item->SetToolType(tool_type);
        if(slave_or_host == MODBUS_SLAVE_TYPE)
        {
            if(tool_type == SLAVE_WR_HOLD_REG)
            {
                item->SetDataSource(&S_WR_Hold_Reg_Data, Dlg_Type);
            }
            else if(tool_type == SLAVE_WR_INPUT_REG)
            {
                item->SetDataSource(&S_WR_Input_Reg_Data, Dlg_Type);
            }
        }
        else
        {
            if(tool_type == HOST_WR_HOLD_REG)
            {
                item->SetDataSource(&H_WR_Hold_Reg_Data, Dlg_Type);
            }
        }
        AddMultiRegItem(item);
    }
}

void IntercomMultiRegDialog::CalcPageData()
{
    int length = ui->lineEdit_Length->text().toInt();
    if(length > 8)
    {
        Page_cnt = ((length -1) / 8) + 1;
    }
    else
    {
        Page_cnt = 1;
    }
    ui->Page_cnt_label->setText(QString::number(Page_cnt));
}

void IntercomMultiRegDialog::on_pushButton_pre_clicked()
{
    if(current_page == 1)
    {
        return;
    }
    else
    {
        current_page--;
        ui->current_Page_label->setText(QString::number(current_page));
        int number = current_page * 8 - 8 + 1;
        int start_addr = ui->lineEdit_StartAddr->text().toInt();
        int coilAddr = start_addr + number - 1;
        RegCofingChanged(number, coilAddr, 8);
    }
}

void IntercomMultiRegDialog::on_pushButton_next_clicked()
{
    if(current_page < Page_cnt)
    {
        current_page++;
        ui->current_Page_label->setText(QString::number(current_page));
        int number = current_page * 8 - 8 + 1;
        int start_addr = ui->lineEdit_StartAddr->text().toInt();
        int coilAddr = start_addr + number - 1;
        int length = ui->lineEdit_Length->text().toInt();
        if(length > current_page*8)
        {
            RegCofingChanged(number, coilAddr, 8);
        }
        else
        {
            int item_count = length - (current_page - 1)*8;
            RegCofingChanged(number, coilAddr, item_count);
        }
    }
}

void IntercomMultiRegDialog::on_lineEdit_StartAddr_textChanged(const QString &arg1)
{
    RegSetChanged();
}

void IntercomMultiRegDialog::on_lineEdit_Length_textChanged(const QString &arg1)
{
    RegSetChanged();
    CalcPageData();
}

void IntercomMultiRegDialog::on_comboBox_DataType_currentIndexChanged(int index)
{
    Ini_Flag = 0;
    RegSetChanged();
    Ini_Flag = 1;
}

void IntercomMultiRegDialog::on_btn_Finish_clicked()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_WR_HOLD_REG)
        {
            S_WR_Hold_Reg_Data.address = ui->lineEdit_StartAddr->text().toInt();
            S_WR_Hold_Reg_Data.length = ui->lineEdit_Length->text().toInt();
            S_WR_Hold_Reg_Data.data_type = ui->comboBox_DataType->currentIndex();
            S_WR_Hold_Reg_Data.link_cnt = 0;
            for(int i = 0; i < S_WR_Hold_Reg_Data.length; i++)
            {
                if(S_WR_Hold_Reg_Data.data_source[i] == 1)
                {
                    S_WR_Hold_Reg_Data.link_cnt++;
                }
            }
            intercom_modbus_data_list_set(MODBUS_SLAVE_TYPE, Data_List_Index, &S_WR_Hold_Reg_Data, SLAVE_WR_HOLD_REG);
        }
        else if(tool_type == SLAVE_WR_INPUT_REG)
        {
            S_WR_Input_Reg_Data.address = ui->lineEdit_StartAddr->text().toInt();
            S_WR_Input_Reg_Data.length = ui->lineEdit_Length->text().toInt();
            S_WR_Input_Reg_Data.data_type = ui->comboBox_DataType->currentIndex();
            S_WR_Input_Reg_Data.link_cnt = 0;
            for(int i = 0; i < S_WR_Input_Reg_Data.length; i++)
            {
                if(S_WR_Input_Reg_Data.data_source[i] == 1)
                {
                    S_WR_Input_Reg_Data.link_cnt++;
                }
            }
            intercom_modbus_data_list_set(MODBUS_SLAVE_TYPE, Data_List_Index, &S_WR_Input_Reg_Data, SLAVE_WR_INPUT_REG);
        }
    }
    else
    {
        if(tool_type == HOST_WR_HOLD_REG)
        {
            H_WR_Hold_Reg_Data.address = ui->lineEdit_StartAddr->text().toInt();
            H_WR_Hold_Reg_Data.length = ui->lineEdit_Length->text().toInt();
            H_WR_Hold_Reg_Data.data_type = ui->comboBox_DataType->currentIndex();
            H_WR_Hold_Reg_Data.link_cnt = 0;
            for(int i = 0; i < H_WR_Hold_Reg_Data.length; i++)
            {
                if(H_WR_Hold_Reg_Data.data_source[i] == 1)
                {
                    H_WR_Hold_Reg_Data.link_cnt++;
                }
            }
            intercom_modbus_data_list_set(MODBUS_SLAVE_TYPE, Data_List_Index, &H_WR_Hold_Reg_Data, HOST_WR_HOLD_REG);
        }
    }


    intercom_modbus_list_exec_step_set(Data_List_Index, ui->comboBox_TaskList->currentIndex()+1);

    if(ui->checkBox_Pre->isChecked())
    {
        intercom_modbus_list_pre_post_exec_step_set(Data_List_Index, MODBUS_EXEC_PRE_STEP);
    }
    else
    {
        intercom_modbus_list_pre_post_exec_step_set(Data_List_Index, MODBUS_EXEC_POST_STEP);
    }

    QDialog::accept();
}

void IntercomMultiRegDialog::on_btn_Quit_clicked()
{
    QDialog::reject();
}
