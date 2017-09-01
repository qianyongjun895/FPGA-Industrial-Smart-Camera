#include "IntercomWRMultiCoilDialog.h"
#include "ui_IntercomWRMultiCoilDialog.h"
#include <QDebug>
#include <QMessageBox>
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
#include "LinkDataGlobal.h"

IntercomWRMultiCoilDialog::IntercomWRMultiCoilDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntercomWRMultiCoilDialog)
{
    ui->setupUi(this);
    Ini_Flag = 0;
    LoadKeyBoardLib();
    IniData();
}

IntercomWRMultiCoilDialog::~IntercomWRMultiCoilDialog()
{
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_Length->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}


void IntercomWRMultiCoilDialog::IniData()
{
    Page_cnt = 1;
    current_page = 1;
    memset(&WR_Coil_Data, 0, sizeof(WR_Coil_Data));
    memset(&WR_Discrete_Data, 0, sizeof(WR_Discrete_Data));
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
}

void IntercomWRMultiCoilDialog::IniMultiCoilData()
{
    ui->lineEdit_StartAddr->setText("1");
    ui->lineEdit_Length->setText("10");
    ui->comboBox_TaskList->setCurrentIndex(0);
    CoilCofingChanged(1, 1, 10);
}

void IntercomWRMultiCoilDialog::IniSlaveWriteCoilData()
{
    intercom_modbus_data_list_get(Data_List_Index, &WR_Coil_Data);
    ui->lineEdit_StartAddr->setText(QString::number(WR_Coil_Data.address));
    ui->lineEdit_Length->setText(QString::number(WR_Coil_Data.length));

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

void IntercomWRMultiCoilDialog::IniSlaveWriteDiscreteData()
{
    intercom_modbus_data_list_get(Data_List_Index, &WR_Discrete_Data);
    ui->lineEdit_StartAddr->setText(QString::number(WR_Discrete_Data.address));
    ui->lineEdit_Length->setText(QString::number(WR_Discrete_Data.length));
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

void IntercomWRMultiCoilDialog::IniHostReadCoilData()
{
    intercom_modbus_data_list_get(Data_List_Index, &H_RD_Coil_Data);
    ui->lineEdit_StartAddr->setText(QString::number(H_RD_Coil_Data.address));
    ui->lineEdit_Length->setText(QString::number(H_RD_Coil_Data.length));
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

void IntercomWRMultiCoilDialog::IniHostWriteCoilData()
{
    intercom_modbus_data_list_get(Data_List_Index, &H_WR_Coil_Data);
    ui->lineEdit_StartAddr->setText(QString::number(H_WR_Coil_Data.address));
    ui->lineEdit_Length->setText(QString::number(H_WR_Coil_Data.length));
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

void IntercomWRMultiCoilDialog::IniHostReadDiscreteData()
{
    intercom_modbus_data_list_get(Data_List_Index, &H_RD_Discrete_Data);
    ui->lineEdit_StartAddr->setText(QString::number(H_RD_Discrete_Data.address));
    ui->lineEdit_Length->setText(QString::number(H_RD_Discrete_Data.length));
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

void IntercomWRMultiCoilDialog::GetMultiCoilData()
{
    Ini_Flag = 1;
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_WR_COILS)
        {
            IniSlaveWriteCoilData();
        }
        else if(tool_type == SLAVE_WR_DISCRETE)
        {
            IniSlaveWriteDiscreteData();
        }
    }
    else
    {
        if(tool_type == HOST_RD_COILS)
        {
            IniHostReadCoilData();
        }
        else if(tool_type == HOST_WR_COILS)
        {
            IniHostWriteCoilData();
        }
        else if(tool_type == HOST_RD_DISCRETE)
        {
            IniHostReadDiscreteData();
        }
    }
    Ini_Flag = 0;
}

void IntercomWRMultiCoilDialog::SetModbusMode(int mode)
{
    slave_or_host = mode;
}

void IntercomWRMultiCoilDialog::SetDataListIndex(int List_Index)
{
    Data_List_Index = List_Index;
}

void IntercomWRMultiCoilDialog::SetToolType(int tool)
{
    tool_type = tool;
}

void IntercomWRMultiCoilDialog::LoadKeyBoardLib()
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

void IntercomWRMultiCoilDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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


bool IntercomWRMultiCoilDialog::eventFilter(QObject *watched, QEvent *event)
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
                if(tool_type == SLAVE_WR_COILS || tool_type == SLAVE_WR_DISCRETE)
                {
                    if(2000 + ui->lineEdit_StartAddr->text().toInt() < 65536)
                    {
                        NumKeyBoardDlg(watched, event, 1, 2000);
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
                if(tool_type == HOST_RD_COILS || tool_type == HOST_RD_DISCRETE)
                {
                    if(2000 + ui->lineEdit_StartAddr->text().toInt() < 65536)
                    {
                        NumKeyBoardDlg(watched, event, 1, 2000);
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
                else if(tool_type == HOST_WR_COILS)
                {
                    if(1968 + ui->lineEdit_StartAddr->text().toInt() < 65536)
                    {
                        NumKeyBoardDlg(watched, event, 1, 1968);
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
    }
    return QWidget::eventFilter(watched, event);
}

void IntercomWRMultiCoilDialog::AddMultiColiItem(IntercomMultiCoilItem* CoilItem)
{
    CoilItem->setAttribute(Qt::WA_DeleteOnClose);
    int size =ui->listWidget->count();
    QListWidgetItem *list_Item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(list_Item, CoilItem);
    ui->listWidget->item(size)->setSizeHint(QSize(240,35));
//    ui->listWidget->setCurrentRow(size);
}

void IntercomWRMultiCoilDialog::CoilCofingChanged(int number, int coil_addr, int data_cnts)
{
    ui->listWidget->clear();
    for(int i = 1; i <= data_cnts; i++)
    {
        IntercomMultiCoilItem *item = new IntercomMultiCoilItem;
        item->SetNumber(number++);
        item->setCoilAddr(coil_addr++);
        item->SetModbusMode(slave_or_host);
        item->SetToolType(tool_type);
        if(slave_or_host == MODBUS_SLAVE_TYPE)
        {
            if(tool_type == SLAVE_WR_COILS)
            {
                item->SetDataSource(&WR_Coil_Data);
            }
            else if(tool_type == SLAVE_WR_DISCRETE)
            {
                item->SetDataSource(&WR_Discrete_Data);
            }
        }
        else if(slave_or_host == MODBUS_HOST_TYPE)
        {
            if(tool_type == HOST_RD_COILS)
            {
                item->SetDataSource(&H_RD_Coil_Data);
            }
            else if(tool_type == HOST_WR_COILS)
            {
                item->SetDataSource(&H_WR_Coil_Data);
            }
            else if(tool_type == HOST_RD_DISCRETE)
            {
                item->SetDataSource(&H_RD_Discrete_Data);
            }
        }
        AddMultiColiItem(item);
    }
}

void IntercomWRMultiCoilDialog::on_lineEdit_StartAddr_textChanged(const QString &arg1)
{
    CoilSetChanged();
}

void IntercomWRMultiCoilDialog::on_lineEdit_Length_textChanged(const QString &arg1)
{
    CoilSetChanged();
    CalcPageData();
}

void IntercomWRMultiCoilDialog::CoilSetChanged()
{
    if(Ini_Flag == 0)
    {
        memset(&WR_Coil_Data, 0, sizeof(WR_Coil_Data));
        memset(&WR_Discrete_Data, 0, sizeof(WR_Discrete_Data));
        memset(&H_RD_Coil_Data, 0, sizeof(H_RD_Coil_Data));
        memset(&H_WR_Coil_Data, 0, sizeof(H_WR_Coil_Data));
        memset(&H_RD_Discrete_Data, 0, sizeof(H_RD_Discrete_Data));
    }
    int start_addr = ui->lineEdit_StartAddr->text().toInt();
    int length = ui->lineEdit_Length->text().toInt();
    ui->label_currentIndex->setText("1");
    current_page = 1;
    if(length > 10)
    {
        CoilCofingChanged(1, start_addr, 10);
    }
    else
    {
        CoilCofingChanged(1, start_addr, length);
    }
}

void IntercomWRMultiCoilDialog::CalcPageData()
{
    int length = ui->lineEdit_Length->text().toInt();
    if(length > 10)
    {
        Page_cnt = ((length -1) / 10) + 1;
        ui->label_PageCnt->setText(QString::number(Page_cnt));
    }
}

void IntercomWRMultiCoilDialog::on_btnPrePage_clicked()
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
        CoilCofingChanged(number, coilAddr, 10);
    }
}

void IntercomWRMultiCoilDialog::on_btnNextPage_clicked()
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
            CoilCofingChanged(number, coilAddr, 10);
        }
        else
        {
            int item_count = length - (current_page - 1)*10;
            CoilCofingChanged(number, coilAddr, item_count);
        }
    }
}

void IntercomWRMultiCoilDialog::on_btnOk_clicked()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_WR_COILS)
        {
            WR_Coil_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            WR_Coil_Data.length = ui->lineEdit_Length->text().toUInt();
            intercom_modbus_data_list_set(slave_or_host, Data_List_Index, &WR_Coil_Data, tool_type);
        }
        else if(tool_type == SLAVE_WR_DISCRETE)
        {
            WR_Discrete_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            WR_Discrete_Data.length = ui->lineEdit_Length->text().toUInt();
            intercom_modbus_data_list_set(slave_or_host, Data_List_Index, &WR_Discrete_Data, tool_type);
        }
    }
    else
    {
        if(tool_type == HOST_RD_COILS)
        {
            H_RD_Coil_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            H_RD_Coil_Data.length = ui->lineEdit_Length->text().toUInt();
            intercom_modbus_data_list_set(slave_or_host, Data_List_Index, &H_RD_Coil_Data, tool_type);
        }
        else if(tool_type == HOST_WR_COILS)
        {
            H_WR_Coil_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            H_WR_Coil_Data.length = ui->lineEdit_Length->text().toUInt();
            intercom_modbus_data_list_set(slave_or_host, Data_List_Index, &H_WR_Coil_Data, tool_type);
        }
        else if(tool_type == HOST_RD_DISCRETE)
        {
            H_RD_Discrete_Data.address = ui->lineEdit_StartAddr->text().toUInt();
            H_RD_Discrete_Data.length = ui->lineEdit_Length->text().toUInt();
            intercom_modbus_data_list_set(slave_or_host, Data_List_Index, &H_RD_Discrete_Data, tool_type);
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

void IntercomWRMultiCoilDialog::on_btnquit_clicked()
{
    QDialog::reject();
}
