#include "MitFxPlcListWidgetItem.h"
#include "ui_MitFxPlcListWidgetItem.h"
#include "MitFxPlcGlobal.h"
#include "WRMRegDialog.h"
#include "stdio.h"
#include "RDDRegDialog.h"
#include "WRDRegDialog.h"
MitFxPlcListWidgetItem::MitFxPlcListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MitFxPlcListWidgetItem)
{
    ui->setupUi(this);
}

MitFxPlcListWidgetItem::~MitFxPlcListWidgetItem()
{
    delete ui;
}


void MitFxPlcListWidgetItem::SetLableText(QString text)
{
    ui->label->setText(text);
}

QString MitFxPlcListWidgetItem::GetLabelText()
{
    return ui->label->text();
}

void MitFxPlcListWidgetItem::SetCurrentIndex(int index)
{
    Current_index = index;
}

void MitFxPlcListWidgetItem::SetToolType(int type)
{
    tool_type = type;
}

void MitFxPlcListWidgetItem::on_pushButton_clicked()
{
    if(tool_type == M_REG_READ || tool_type == M_REG_WRITE)
    {
        WRMRegDialog *dlg = new WRMRegDialog;
        dlg->SetCurrentIndex(Current_index);
        dlg->SetToolType(tool_type);
        dlg->GetWRMRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            return;
        }
        delete dlg;
    }
    else if(tool_type == D_REG_READ)
    {
        RDDRegDialog *dlg = new RDDRegDialog;
        dlg->SetToolType(D_REG_READ);
        dlg->SetCurrentIndex(Current_index);
        dlg->GetRDDRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            return;
        }
        delete dlg;
    }
    else if(tool_type == D_REG_WRITE)
    {
        WRDRegDialog *dlg = new WRDRegDialog;
        dlg->SetDlgType(1);
        dlg->SetDataListIndex(Current_index);
        dlg->GetRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            return;
        }
        delete dlg;
    }
}
