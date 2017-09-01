#include "WRMRegItem.h"
#include "ui_WRMRegItem.h"
#include "stdio.h"
WRMRegItem::WRMRegItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WRMRegItem)
{
    ui->setupUi(this);
}

WRMRegItem::~WRMRegItem()
{
    RD_M_Reg = NULL;
    WR_M_Reg = NULL;
    delete ui;
}


void WRMRegItem::SetNumber(int num)
{
    ui->label_number->setText(QString::number(num));
}

void WRMRegItem::SetMRegAddr(int addr)
{
    ui->label_reg_addr->setText(QString::number(addr));
}

void WRMRegItem::SetToolType(int tool)
{
    tool_type = tool;
}

void WRMRegItem::SetDataSource(PLC_READ_M_REG* reg)
{
    RD_M_Reg = reg;
    if(RD_M_Reg->expecte_value[ui->label_number->text().toInt()] == 1)
    {
        ui->radioButton_no->setChecked(true);
    }
    else
    {
        ui->radioButton_off->setChecked(true);
    }
}

void WRMRegItem::SetDataSource(PLC_WRITE_M_REG* reg)
{
    WR_M_Reg = reg;
    if(WR_M_Reg->reg_value[ui->label_number->text().toInt()] == 1)
    {
        ui->radioButton_no->setChecked(true);
    }
    else
    {
        ui->radioButton_off->setChecked(true);
    }
}


void WRMRegItem::on_radioButton_no_clicked()
{
    if(tool_type == M_REG_READ)
    {
        RD_M_Reg->expecte_value[ui->label_number->text().toInt()] = 1;
    }
    else if(tool_type == M_REG_WRITE)
    {
        WR_M_Reg->reg_value[ui->label_number->text().toInt()] = 1;
    }
}

void WRMRegItem::on_radioButton_off_clicked()
{
    if(tool_type == M_REG_READ)
    {
        RD_M_Reg->expecte_value[ui->label_number->text().toInt()] = 0;
    }
    else if(tool_type == M_REG_WRITE)
    {
        WR_M_Reg->reg_value[ui->label_number->text().toInt()] = 0;
    }
}
