#include "ToolEnableItem.h"
#include "ui_ToolEnableItem.h"

ToolEnableItem::ToolEnableItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolEnableItem)
{
    ui->setupUi(this);
}

ToolEnableItem::~ToolEnableItem()
{
    delete ui;
}

void ToolEnableItem::SetEnaFlag(bool flag)
{
    ui->checkBox->setChecked(flag);
}

void ToolEnableItem::SetTaskName(QString name)
{
    ui->label->setText(name);
}


char  ToolEnableItem::GetEnaFlag()
{
    if(ui->checkBox->isChecked())
        return 0;
    else
        return 1;
}
