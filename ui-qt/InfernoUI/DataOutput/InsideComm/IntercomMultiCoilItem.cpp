#include "IntercomMultiCoilItem.h"
#include "ui_IntercomMultiCoilItem.h"
#include <stdio.h>
IntercomMultiCoilItem::IntercomMultiCoilItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntercomMultiCoilItem)
{
    ui->setupUi(this);
    ui->radioButton_OFF->setChecked(true);
}

IntercomMultiCoilItem::~IntercomMultiCoilItem()
{
    delete ui;
}

void IntercomMultiCoilItem::SetCurrentIndex(int index)
{
    Current_index = index;
}

void IntercomMultiCoilItem::SetModbusMode(int mode)
{
    slave_or_host = mode;
}

void IntercomMultiCoilItem::SetToolType(int tool)
{
    tool_type = tool;
}

void IntercomMultiCoilItem::SetNumber(int index)
{
    ui->txt_SerialNum->setText(QString::number(index));
}

void IntercomMultiCoilItem::setCoilAddr(int addr)
{
    ui->txt_CoilAddr->setText(QString::number(addr));
}

void IntercomMultiCoilItem::SetDataSource(MBS_WR_COIL* Data)
{
    WR_Coil_Data = Data;
    if(WR_Coil_Data->coil_value[ui->txt_SerialNum->text().toUInt() - 1] == MODBUS_COIL_ZERO_TRIGGER)
    {
        ui->radioButton_OFF->setChecked(true);
    }
    else
    {
        ui->radioButton_ON->setChecked(true);
    }
}

void IntercomMultiCoilItem::SetDataSource(MBS_WR_DISCRETE* Data)
{
    WR_Discrete_Data = Data;
    if(WR_Discrete_Data->discrete_value[ui->txt_SerialNum->text().toUInt() - 1] == MODBUS_COIL_ZERO_TRIGGER)
    {
        ui->radioButton_OFF->setChecked(true);
    }
    else
    {
        ui->radioButton_ON->setChecked(true);
    }
}

void IntercomMultiCoilItem::SetDataSource(MBH_RD_COILS* Data)
{
    H_RD_Coil_Data = Data;
    if(H_RD_Coil_Data->expecte_value[ui->txt_SerialNum->text().toUInt() - 1] == MODBUS_COIL_ZERO_TRIGGER)
    {
        ui->radioButton_OFF->setChecked(true);
    }
    else
    {
        ui->radioButton_ON->setChecked(true);
    }
}

void IntercomMultiCoilItem::SetDataSource(MBH_WR_COILS* Data)
{
    H_WR_Coil_Data = Data;
    if(H_WR_Coil_Data->coil_value[ui->txt_SerialNum->text().toUInt() - 1] == MODBUS_COIL_ZERO_TRIGGER)
    {
        ui->radioButton_OFF->setChecked(true);
    }
    else
    {
        ui->radioButton_ON->setChecked(true);
    }
}


void IntercomMultiCoilItem::SetDataSource(MBH_RD_DISCRETE* Data)
{
    H_RD_Discrete_Data = Data;
    if(H_RD_Discrete_Data->expecte_value[ui->txt_SerialNum->text().toUInt() - 1] == MODBUS_COIL_ZERO_TRIGGER)
    {
        ui->radioButton_OFF->setChecked(true);
    }
    else
    {
        ui->radioButton_ON->setChecked(true);
    }
}

void IntercomMultiCoilItem::on_radioButton_OFF_clicked()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_WR_COILS)
        {
            WR_Coil_Data->coil_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ZERO_TRIGGER;
        }
        else if(tool_type == SLAVE_WR_DISCRETE)
        {
            WR_Discrete_Data->discrete_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ZERO_TRIGGER;
        }
    }
    else if(slave_or_host == MODBUS_HOST_TYPE)
    {
        if(tool_type == HOST_RD_COILS)
        {
            H_RD_Coil_Data->expecte_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ZERO_TRIGGER;
        }
        else if(tool_type == HOST_WR_COILS)
        {
            H_WR_Coil_Data->coil_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ZERO_TRIGGER;
        }
        else if(tool_type == HOST_RD_DISCRETE)
        {
            H_RD_Discrete_Data->expecte_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ZERO_TRIGGER;
        }

    }
}

void IntercomMultiCoilItem::on_radioButton_ON_clicked()
{
    if(slave_or_host == MODBUS_SLAVE_TYPE)
    {
        if(tool_type == SLAVE_WR_COILS)
        {
            WR_Coil_Data->coil_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ONE_TRIGGER;
        }
        else if(tool_type == SLAVE_WR_DISCRETE)
        {
            WR_Discrete_Data->discrete_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ONE_TRIGGER;
        }
    }
    else if(slave_or_host == MODBUS_HOST_TYPE)
    {
        if(tool_type == HOST_RD_COILS)
        {
            H_RD_Coil_Data->expecte_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ONE_TRIGGER;
        }
        else if(tool_type == HOST_WR_COILS)
        {
            H_WR_Coil_Data->coil_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ONE_TRIGGER;
        }
        else if(tool_type == HOST_RD_DISCRETE)
        {
            H_RD_Discrete_Data->expecte_value[ui->txt_SerialNum->text().toUInt() - 1] = MODBUS_COIL_ONE_TRIGGER;
        }
    }
}
