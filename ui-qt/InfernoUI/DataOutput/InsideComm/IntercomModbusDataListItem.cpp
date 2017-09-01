#include "IntercomModbusDataListItem.h"
#include "ui_IntercomModbusDataListItem.h"
#include "IntercomRDSingleCoilDialog.h"
//#include "ModbusGlobal.h"
#include "IntercomWRMultiCoilDialog.h"
#include "stdio.h"
#include "IntercomReadRegDialog.h"
#include "IntercomMultiRegDialog.h"
#include <QDebug>
IntercomModbusDataListItem::IntercomModbusDataListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntercomModbusDataListItem)
{
    ui->setupUi(this);
}

IntercomModbusDataListItem::~IntercomModbusDataListItem()
{
    delete ui;
}

void IntercomModbusDataListItem::SetLabelText(QString test)
{
    ui->labelName->setText(test);
}

void IntercomModbusDataListItem::SetCurrentIndex(int index)
{
    current_index = index;
}

void IntercomModbusDataListItem::SetModbusMode(int mode)
{
    slave_or_host = mode;
}

void IntercomModbusDataListItem::SetToolType(int type)
{
    tool_type = type;
}

QString IntercomModbusDataListItem::GetLabelText()
{
    return ui->labelName->text();
}

int IntercomModbusDataListItem::GetModbusMode()
{
    return slave_or_host;
}

int IntercomModbusDataListItem::GetToolType()
{
    return tool_type;
}

void IntercomModbusDataListItem::on_btnDetail_clicked()
{
    int ret = 0;
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_RD_COILS)
        {
            IntercomRDSingleCoilDialog *SlaveRDCoil_dlg = new IntercomRDSingleCoilDialog;
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
            IntercomWRMultiCoilDialog *SlaveWRMulti_dlg = new IntercomWRMultiCoilDialog;
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
            IntercomReadRegDialog *SlaveRDHost_dlg = new IntercomReadRegDialog;
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
            IntercomMultiRegDialog *SlaveWRHost_dlg = new IntercomMultiRegDialog;
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
            IntercomWRMultiCoilDialog *HostWRMulti_dlg = new IntercomWRMultiCoilDialog;
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
            IntercomReadRegDialog *HostRDHost_dlg = new IntercomReadRegDialog;
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
            IntercomMultiRegDialog *HostWRHost_dlg = new IntercomMultiRegDialog;
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
