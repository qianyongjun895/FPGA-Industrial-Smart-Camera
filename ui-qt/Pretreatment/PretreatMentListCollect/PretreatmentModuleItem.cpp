#include "PretreatmentModuleItem.h"
#include "ui_PretreatmentModuleItem.h"

PretreatmentModuleItem::PretreatmentModuleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PretreatmentModuleItem)
{
    ui->setupUi(this);
    ui->checkBox->setLayoutDirection(Qt::LeftToRight);
    ui->checkBox->move(11,1);
    m_taskKind = 0;
}
PretreatmentModuleItem::~PretreatmentModuleItem()
{
    delete ui;
}
//详细信息
void PretreatmentModuleItem::on_btnDetail_clicked()
{
    int value = 0;
    SignalOperate(PREDETAIL,m_taskKind,value,m_current_row);
}
void PretreatmentModuleItem::SetInfoName(QString strName)
{
    ui->checkBox->setText(strName);
}
QString  PretreatmentModuleItem::GetInfoName()
{
    return ui->checkBox->text();
}
//处理单击事件
void PretreatmentModuleItem::on_checkBox_clicked()
{
    int value = 0;

    if(ui->checkBox->isChecked())
    {
        value = 1;
        ui->btnDetail->setEnabled(true);
        SignalOperate(PREENABLE,m_taskKind,value,m_current_row);
        ui->btnDetail->setEnabled(true);
    }else
    {
        value = 0;
        ui->btnDetail->setEnabled(false);
        SignalOperate(PREENABLE,m_taskKind,value,m_current_row);
        ui->btnDetail->setEnabled(false);
    }
}
int PretreatmentModuleItem::GetCheckedValue()
{
    if(ui->checkBox->isChecked())
    {
        return 1;
    }else
    {
        return 0;
    }
}
void PretreatmentModuleItem::SetCheckdevalue(int bflag)
{
    ui->checkBox->setChecked(bflag);
    ui->btnDetail->setEnabled(bflag);
}
void PretreatmentModuleItem::SetControlEnable(int bflag)
{
    ui->btnDetail->setEnabled(bflag);
    ui->checkBox->setEnabled(bflag);
    ui->checkBox->setChecked(bflag);
}
int PretreatmentModuleItem::GetCheckBoxEnable()
{
    int ret = 0;
    if(ui->checkBox->isEnabled())
        ret =1;
    else
        ret = 0;
    return ret;
}
