#include "ModbusWidget.h"
#include "ui_ModbusWidget.h"
#include "ModbusGlobal.h"
#include "ProtocolManageGlobal.h"
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include "RDSingleCoilDialog.h"
#include "WRMultiCoilDialog.h"
#include "ReadRegDialog.h"
#include "MultiRegDialog.h"
ModbusWidget::ModbusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModbusWidget)
{
    ui->setupUi(this);
    list_cnt = 0;
    LoadKeyBoardLib();
}

ModbusWidget::~ModbusWidget()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}


void ModbusWidget::IniData()
{
    ui->listWidgetData->clear();
    list_cnt = modbus_data_list_cnt_get();
    for(int i = 0; i < list_cnt; i++)
    {
        int tool_type = modbus_list_data_type_get(i);
        AddListWidgetItem(ui->comboBoxModbusTool->itemText(tool_type), i, slave_or_host, tool_type);
    }
}

void ModbusWidget::IniSlaveOrHost()
{
    slave_or_host = modbus_slave_or_host_get();
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        ui->comboBoxModbusTool->clear();
        ui->comboBoxModbusTool->addItem("读线圈");
        ui->comboBoxModbusTool->addItem("写线圈");
        ui->comboBoxModbusTool->addItem("写离散量");
        ui->comboBoxModbusTool->addItem("读保持寄存器");
        ui->comboBoxModbusTool->addItem("写保持寄存器");
        ui->comboBoxModbusTool->addItem("写输入寄存器");
    }
    else
    {
        ui->comboBoxModbusTool->clear();
        ui->comboBoxModbusTool->addItem("读线圈");
        ui->comboBoxModbusTool->addItem("写线圈");
        ui->comboBoxModbusTool->addItem("读离散量");
        ui->comboBoxModbusTool->addItem("读保持寄存器");
        ui->comboBoxModbusTool->addItem("写保持寄存器");
        ui->comboBoxModbusTool->addItem("读输入寄存器");
    }
    IniData();
}


void ModbusWidget::LoadKeyBoardLib()
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

void ModbusWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

void ModbusWidget::SetModbusData()
{

}


void ModbusWidget::AddCommandItemData(ModbusDataListItem *pListWidgeModbusItem)
{
    pListWidgeModbusItem->setAttribute(Qt::WA_DeleteOnClose);
    int size =ui->listWidgetData->count();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidgetData);
    ui->listWidgetData->setItemWidget(mItem,(QWidget*)pListWidgeModbusItem);
    ui->listWidgetData->item(size)->setSizeHint(QSize(240,40));
    ui->listWidgetData->setCurrentRow(size);
}

void ModbusWidget::AddListWidgetItem(QString String, int Current_index, int Host_Or_Slave, int Tool_type)
{
    ModbusDataListItem *Data_List = new ModbusDataListItem;
    Data_List->SetLabelText(String);
    Data_List->SetModbusMode(Host_Or_Slave);
    Data_List->SetCurrentIndex(Current_index);
    Data_List->SetToolType(Tool_type);
    AddCommandItemData(Data_List);
}

void ModbusWidget::AddSlaveReadCoil()
{
    int current_index = ui->listWidgetData->count();
    RDSingleCoilDialog *SlaveReadCoil_dlg = new RDSingleCoilDialog;
    SlaveReadCoil_dlg->SetDataListIndex(current_index);
    SlaveReadCoil_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveReadCoil_dlg->SetToolType(SLAVE_RD_COILS);
    SlaveReadCoil_dlg->IniSingleCoilData();
    int ret = SlaveReadCoil_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_RD_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_RD_COILS);
    }
    delete SlaveReadCoil_dlg;
}

void ModbusWidget::AddSlaveWriteCoil()
{
    int current_index = ui->listWidgetData->count();
    WRMultiCoilDialog *SlaveWriteCoil_dlg = new WRMultiCoilDialog;
    SlaveWriteCoil_dlg->SetDataListIndex(current_index);
    SlaveWriteCoil_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteCoil_dlg->SetToolType(SLAVE_WR_COILS);
    SlaveWriteCoil_dlg->IniMultiCoilData();
    int ret = SlaveWriteCoil_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_COILS);
    }
    delete SlaveWriteCoil_dlg;
}

void ModbusWidget::AddSlaveWriteDiscrete()
{
    int current_index = ui->listWidgetData->count();
    WRMultiCoilDialog *SlaveWriteDiscrete_dlg = new WRMultiCoilDialog;
    SlaveWriteDiscrete_dlg->SetDataListIndex(current_index);
    SlaveWriteDiscrete_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteDiscrete_dlg->SetToolType(SLAVE_WR_DISCRETE);
    SlaveWriteDiscrete_dlg->IniMultiCoilData();
    int ret = SlaveWriteDiscrete_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_DISCRETE);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_DISCRETE);
    }
    delete SlaveWriteDiscrete_dlg;
}

void ModbusWidget::AddSlaveReadHoldReg()
{
    int current_index = ui->listWidgetData->count();
    ReadRegDialog *SlaveReadHoldReg_dlg = new ReadRegDialog;
    SlaveReadHoldReg_dlg->SetDataListIndex(current_index);
    SlaveReadHoldReg_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveReadHoldReg_dlg->SetToolType(SLAVE_RD_HOLD_REG);
    SlaveReadHoldReg_dlg->IniRegData();
    int ret = SlaveReadHoldReg_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_RD_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_RD_HOLD_REG);
    }
    delete SlaveReadHoldReg_dlg;
}

void ModbusWidget::AddSlaveWriteHoldReg()
{
    int current_index = ui->listWidgetData->count();
    MultiRegDialog *SlaveWriteHoldReg_dlg = new MultiRegDialog;
    SlaveWriteHoldReg_dlg->SetDlgType(0);
    SlaveWriteHoldReg_dlg->SetDataListIndex(current_index);
    SlaveWriteHoldReg_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteHoldReg_dlg->SetToolType(SLAVE_WR_HOLD_REG);
    SlaveWriteHoldReg_dlg->IniRegData();
    int ret = SlaveWriteHoldReg_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_HOLD_REG);
    }
    delete SlaveWriteHoldReg_dlg;
}

void ModbusWidget::AddSlaveWriteInputReg()
{
    int current_index = ui->listWidgetData->count();
    MultiRegDialog *SlaveWriteInputReg_dlg = new MultiRegDialog;
    SlaveWriteInputReg_dlg->SetDlgType(0);
    SlaveWriteInputReg_dlg->SetDataListIndex(current_index);
    SlaveWriteInputReg_dlg->SetModbusMode(MODBUS_SLAVE_TYPE);
    SlaveWriteInputReg_dlg->SetToolType(SLAVE_WR_INPUT_REG);
    SlaveWriteInputReg_dlg->IniRegData();
    int ret = SlaveWriteInputReg_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(SLAVE_WR_INPUT_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_SLAVE_TYPE, SLAVE_WR_INPUT_REG);
    }
    delete SlaveWriteInputReg_dlg;
}

void ModbusWidget::AddHostReadCoil()
{
    int current_index = ui->listWidgetData->count();
    WRMultiCoilDialog *HostReadCoil_dlg = new WRMultiCoilDialog;
    HostReadCoil_dlg->SetDataListIndex(current_index);
    HostReadCoil_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadCoil_dlg->SetToolType(HOST_RD_COILS);
    HostReadCoil_dlg->IniMultiCoilData();
    int ret = HostReadCoil_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_COILS);
    }
    delete HostReadCoil_dlg;
}

void ModbusWidget::AddHostWriteCoil()
{
    int current_index = ui->listWidgetData->count();
    WRMultiCoilDialog *HostWriteCoil_dlg = new WRMultiCoilDialog;
    HostWriteCoil_dlg->SetDataListIndex(current_index);
    HostWriteCoil_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostWriteCoil_dlg->SetToolType(HOST_WR_COILS);
    HostWriteCoil_dlg->IniMultiCoilData();
    int ret = HostWriteCoil_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_WR_COILS);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_WR_COILS);
    }
    delete HostWriteCoil_dlg;
}

void ModbusWidget::AddHostReadDiscrete()
{
    int current_index = ui->listWidgetData->count();
    WRMultiCoilDialog *HostReadDiscrete_dlg = new WRMultiCoilDialog;
    HostReadDiscrete_dlg->SetDataListIndex(current_index);
    HostReadDiscrete_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadDiscrete_dlg->SetToolType(HOST_RD_DISCRETE);
    HostReadDiscrete_dlg->IniMultiCoilData();
    int ret = HostReadDiscrete_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_DISCRETE);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_DISCRETE);
    }
    delete HostReadDiscrete_dlg;
}

void ModbusWidget::AddHostReadHoldReg()
{
    int current_index = ui->listWidgetData->count();
    ReadRegDialog *HostReadHoldReg_dlg = new ReadRegDialog;
    HostReadHoldReg_dlg->SetDataListIndex(current_index);
    HostReadHoldReg_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadHoldReg_dlg->SetToolType(HOST_RD_HOLD_REG);
    HostReadHoldReg_dlg->IniRegData();
    int ret = HostReadHoldReg_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_HOLD_REG);
    }
    delete HostReadHoldReg_dlg;
}

void ModbusWidget::AddHostWriteHoldReg()
{
    int current_index = ui->listWidgetData->count();
    MultiRegDialog *HostWriteHoldReg_dlg = new MultiRegDialog;
    HostWriteHoldReg_dlg->SetDlgType(0);
    HostWriteHoldReg_dlg->SetDataListIndex(current_index);
    HostWriteHoldReg_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostWriteHoldReg_dlg->SetToolType(HOST_WR_HOLD_REG);
    HostWriteHoldReg_dlg->IniRegData();
    int ret = HostWriteHoldReg_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_WR_HOLD_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_WR_HOLD_REG);
    }
    delete HostWriteHoldReg_dlg;
}

void ModbusWidget::AddHostReadInputReg()
{
    int current_index = ui->listWidgetData->count();
    ReadRegDialog *HostReadInputReg_dlg = new ReadRegDialog;
    HostReadInputReg_dlg->SetDataListIndex(current_index);
    HostReadInputReg_dlg->SetModbusMode(MODBUS_HOST_TYPE);
    HostReadInputReg_dlg->SetToolType(HOST_RD_INPUT_REG);
    HostReadInputReg_dlg->IniRegData();
    int ret = HostReadInputReg_dlg->exec();
    if(ret == QDialog::Accepted)
    {
        QString lable_string = ui->comboBoxModbusTool->itemText(HOST_RD_INPUT_REG);
        AddListWidgetItem(lable_string, current_index, MODBUS_HOST_TYPE, HOST_RD_INPUT_REG);
    }
    delete HostReadInputReg_dlg;
}

void ModbusWidget::on_btnAdd_clicked()
{
    if(ui->listWidgetData->count() >= MB_DATA_LIST_NUM_MAX)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("数据流达到最大限制100条,不能再添加"), QMessageBox::Yes);
        return;
    }
    int size =ui->listWidgetData->count();
    list_cnt = size + 1;
    modbus_data_list_cnt_set(list_cnt);
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(ui->comboBoxModbusTool->currentIndex() == SLAVE_RD_COILS)
        {
            AddSlaveReadCoil();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_COILS)
        {
            AddSlaveWriteCoil();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_DISCRETE)
        {
            AddSlaveWriteDiscrete();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_RD_HOLD_REG)
        {
            AddSlaveReadHoldReg();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_HOLD_REG)
        {
            AddSlaveWriteHoldReg();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == SLAVE_WR_INPUT_REG)
        {
            AddSlaveWriteInputReg();
        }
    }
    if(slave_or_host == MODBUS_HOST_TYPE)
    {
        if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_COILS)
        {
            AddHostReadCoil();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == HOST_WR_COILS)
        {
            AddHostWriteCoil();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_DISCRETE)
        {
            AddHostReadDiscrete();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_HOLD_REG)
        {
            AddHostReadHoldReg();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == HOST_WR_HOLD_REG)
        {
            AddHostWriteHoldReg();
        }
        else if(ui->comboBoxModbusTool->currentIndex() == HOST_RD_INPUT_REG)
        {
            AddHostReadInputReg();
        }
    }
}

void ModbusWidget::on_btnDelete_clicked()
{
    int row = ui->listWidgetData->currentRow();
    if(row >= 0)
    {
        modbus_del_data_list(row);
        list_cnt--;
        modbus_data_list_cnt_set(list_cnt);
        QListWidgetItem *List_Item =  ui->listWidgetData->takeItem(row);
        delete List_Item;
    }
}

void ModbusWidget::on_btnUp_clicked()
{
    int row = ui->listWidgetData->currentRow();
    if(row > 0)
    {
        modbus_data_list_move_up(row);

        QListWidgetItem *List_Item = ui->listWidgetData->item(row);
        QWidget *m_Widget = ui->listWidgetData->itemWidget(List_Item);

        QListWidgetItem *Pre_List_Item = ui->listWidgetData->item(row - 1);
        QWidget *Pre_Widget = ui->listWidgetData->itemWidget(Pre_List_Item);
        QString Pre_String = ((ModbusDataListItem*)Pre_Widget)->GetLabelText();
        int Pre_Mode = ((ModbusDataListItem*)Pre_Widget)->GetModbusMode();
        int Pre_Tool = ((ModbusDataListItem*)Pre_Widget)->GetToolType();

        ((ModbusDataListItem*)Pre_Widget)->SetLabelText(((ModbusDataListItem*)m_Widget)->GetLabelText());
        ((ModbusDataListItem*)Pre_Widget)->SetModbusMode(((ModbusDataListItem*)m_Widget)->GetModbusMode());
        ((ModbusDataListItem*)Pre_Widget)->SetToolType(((ModbusDataListItem*)m_Widget)->GetToolType());

        ((ModbusDataListItem*)m_Widget)->SetLabelText(Pre_String);
        ((ModbusDataListItem*)m_Widget)->SetModbusMode(Pre_Mode);
        ((ModbusDataListItem*)m_Widget)->SetToolType(Pre_Tool);

        ui->listWidgetData->setCurrentRow(row-1);
    }
}

void ModbusWidget::on_btnDown_clicked()
{
    int row = ui->listWidgetData->currentRow();
    if(row >= 0 && row < ui->listWidgetData->count() - 1)
    {
        modbus_data_list_move_down(row);

        QListWidgetItem *List_Item = ui->listWidgetData->item(row);
        QWidget *m_Widget = ui->listWidgetData->itemWidget(List_Item);

        QListWidgetItem *Pre_List_Item = ui->listWidgetData->item(row + 1);
        QWidget *Pre_Widget = ui->listWidgetData->itemWidget(Pre_List_Item);
        QString Pre_String = ((ModbusDataListItem*)Pre_Widget)->GetLabelText();
        int Pre_Mode = ((ModbusDataListItem*)Pre_Widget)->GetModbusMode();
        int Pre_Tool = ((ModbusDataListItem*)Pre_Widget)->GetToolType();

        ((ModbusDataListItem*)Pre_Widget)->SetLabelText(((ModbusDataListItem*)m_Widget)->GetLabelText());
        ((ModbusDataListItem*)Pre_Widget)->SetModbusMode(((ModbusDataListItem*)m_Widget)->GetModbusMode());
        ((ModbusDataListItem*)Pre_Widget)->SetToolType(((ModbusDataListItem*)m_Widget)->GetToolType());

        ((ModbusDataListItem*)m_Widget)->SetLabelText(Pre_String);
        ((ModbusDataListItem*)m_Widget)->SetModbusMode(Pre_Mode);
        ((ModbusDataListItem*)m_Widget)->SetToolType(Pre_Tool);

        ui->listWidgetData->setCurrentRow(row+1);
    }
}
