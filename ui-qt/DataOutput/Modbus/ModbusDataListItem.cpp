#include "ModbusDataListItem.h"
#include "ui_ModbusDataListItem.h"
#include "RDSingleCoilDialog.h"
#include "ModbusGlobal.h"
#include "WRMultiCoilDialog.h"
#include "stdio.h"
#include "ReadRegDialog.h"
#include "MultiRegDialog.h"
#include <QDebug>
ModbusDataListItem::ModbusDataListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModbusDataListItem)
{
    ui->setupUi(this);
}

ModbusDataListItem::~ModbusDataListItem()
{
    delete ui;
}

void ModbusDataListItem::SetLabelText(QString test)
{
    ui->labelName->setText(test);
}

void ModbusDataListItem::SetCurrentIndex(int index)
{
    current_index = index;
}

void ModbusDataListItem::SetModbusMode(int mode)
{
    slave_or_host = mode;
}

void ModbusDataListItem::SetToolType(int type)
{
    tool_type = type;
}

QString ModbusDataListItem::GetLabelText()
{
    return ui->labelName->text();
}

int ModbusDataListItem::GetModbusMode()
{
    return slave_or_host;
}

int ModbusDataListItem::GetToolType()
{
    return tool_type;
}

void ModbusDataListItem::on_btnDetail_clicked()
{
    int ret = 0;
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_RD_COILS)
        {
            RDSingleCoilDialog *SlaveRDCoil_dlg = new RDSingleCoilDialog;
            SlaveRDCoil_dlg->SetDataListIndex(current_index);
            SlaveRDCoil_dlg->SetModbusMode(slave_or_host);
            SlaveRDCoil_dlg->SetToolType(tool_type);
            SlaveRDCoil_dlg->GetSingleCoilData();
            ret = SlaveRDCoil_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete SlaveRDCoil_dlg;
        }
        else if(tool_type == SLAVE_WR_COILS || tool_type == SLAVE_WR_DISCRETE)
        {
            WRMultiCoilDialog *SlaveWRMulti_dlg = new WRMultiCoilDialog;
            SlaveWRMulti_dlg->SetDataListIndex(current_index);
            SlaveWRMulti_dlg->SetModbusMode(slave_or_host);
            SlaveWRMulti_dlg->SetToolType(tool_type);
            SlaveWRMulti_dlg->GetMultiCoilData();
            ret = SlaveWRMulti_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete SlaveWRMulti_dlg;
        }
        else if(tool_type == SLAVE_RD_HOLD_REG)
        {
            ReadRegDialog *SlaveRDHost_dlg = new ReadRegDialog;
            SlaveRDHost_dlg->SetDataListIndex(current_index);
            SlaveRDHost_dlg->SetModbusMode(slave_or_host);
            SlaveRDHost_dlg->SetToolType(tool_type);
            SlaveRDHost_dlg->GetRegData();
            ret = SlaveRDHost_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete SlaveRDHost_dlg;
        }
        else if(tool_type == SLAVE_WR_HOLD_REG || tool_type == SLAVE_WR_INPUT_REG)
        {
            MultiRegDialog *SlaveWRHost_dlg = new MultiRegDialog;
            SlaveWRHost_dlg->SetDlgType(1);
            SlaveWRHost_dlg->SetDataListIndex(current_index);
            SlaveWRHost_dlg->SetModbusMode(slave_or_host);
            SlaveWRHost_dlg->SetToolType(tool_type);
            SlaveWRHost_dlg->GetRegData();
            ret = SlaveWRHost_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete SlaveWRHost_dlg;
        }
    }
    else if(slave_or_host == MODBUS_HOST_TYPE)
    {
        if(tool_type == HOST_RD_COILS || tool_type == HOST_WR_COILS || tool_type == HOST_RD_DISCRETE)
        {
            WRMultiCoilDialog *HostWRMulti_dlg = new WRMultiCoilDialog;
            HostWRMulti_dlg->SetDataListIndex(current_index);
            HostWRMulti_dlg->SetModbusMode(slave_or_host);
            HostWRMulti_dlg->SetToolType(tool_type);
            HostWRMulti_dlg->GetMultiCoilData();
            ret = HostWRMulti_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete HostWRMulti_dlg;
        }
        else if(tool_type == HOST_RD_HOLD_REG || tool_type == HOST_RD_INPUT_REG)
        {
            ReadRegDialog *HostRDHost_dlg = new ReadRegDialog;
            HostRDHost_dlg->SetDataListIndex(current_index);
            HostRDHost_dlg->SetModbusMode(slave_or_host);
            HostRDHost_dlg->SetToolType(tool_type);
            HostRDHost_dlg->GetRegData();
            ret = HostRDHost_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete HostRDHost_dlg;
        }
        else if(tool_type == HOST_WR_HOLD_REG)
        {
            MultiRegDialog *HostWRHost_dlg = new MultiRegDialog;
            HostWRHost_dlg->SetDlgType(1);
            HostWRHost_dlg->SetDataListIndex(current_index);
            HostWRHost_dlg->SetModbusMode(slave_or_host);
            HostWRHost_dlg->SetToolType(tool_type);
            HostWRHost_dlg->GetRegData();
            ret = HostWRHost_dlg->exec();
            if(ret == QDialog::Accepted)
            {
                return;
            }
            delete HostWRHost_dlg;
        }
    }
}
