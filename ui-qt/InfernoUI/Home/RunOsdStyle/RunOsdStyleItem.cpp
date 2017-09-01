#include "RunOsdStyleItem.h"
#include "ui_RunOsdStyleItem.h"
#include "Comm/GlobalParameter.h"
#include "AcceCommon.h"
#include <qdebug.h>
#include "BasicDefine.h"
RunOsdStyleItem::RunOsdStyleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunOsdStyleItem)
{
    ui->setupUi(this);
}

RunOsdStyleItem::~RunOsdStyleItem()
{
    delete ui;
}

QString RunOsdStyleItem::GetTaskStep()
{
    QString strTaskName = ui->checkBoxTaskName->text();
    int index = strTaskName.indexOf('.');
    return strTaskName.left(index);

}
void RunOsdStyleItem::SetTaskName(QString strName,int value)
{
    ui->checkBoxTaskName->setText(strName);
    if(value ==1)
        ui->checkBoxTaskName->setChecked(true);
    else
        ui->checkBoxTaskName->setChecked(false);


    int istate = GlobalParameter::m_area_select_state.value(GetTaskStep().toInt());

    if(istate==LIST_NG_ROI)
    {
        ui->checkBoxListNG->setChecked(true);
        ui->checkBoxListOK->setChecked(false);

    }else if(istate==LIST_OK_ROI)
    {
        ui->checkBoxListNG->setChecked(false);
        ui->checkBoxListOK->setChecked(true);
    }else if(istate==LIST_NG_OK_ROI)
    {
        ui->checkBoxListNG->setChecked(true);
        ui->checkBoxListOK->setChecked(true);
    }else if(istate==HIDE_NG_OK_ROI)
    {
        ui->checkBoxListNG->setChecked(false);
        ui->checkBoxListOK->setChecked(false);
    }


}

void RunOsdStyleItem::on_checkBoxTaskName_clicked()
{
    QString strStept;
    int ret = IsHasPreModule();
    if(ui->checkBoxTaskName->isChecked())
    {
        strStept = GetTaskStep();
        ui->checkBoxListNG->setEnabled(true);
        ui->checkBoxListOK->setEnabled(true);
        ChangeItemCheck(1,strStept);
    }
    else
    {
        strStept = GetTaskStep();
        ui->checkBoxListNG->setEnabled(false);
        ui->checkBoxListOK->setEnabled(false);
        ChangeItemCheck(0,strStept);
    }
}
int RunOsdStyleItem::IsHasPreModule()
{
    int ret = 0;
    ACCE_MODEL *m_pre_ptr = (ACCE_MODEL*)GetStepAcceModelPointer(GetTaskStep().toInt());

    for(int i = 0; i < m_pre_ptr->accelerator_num; i++)
    {
        if(m_pre_ptr->accelerator[i] == ACCE_AREA_SELECT_MODEL_ID)
        {
            ret =1;
            break;
        }
    }

    return ret;
}
void RunOsdStyleItem::on_checkBoxListOK_clicked()
{
    GetROIState();
}

void RunOsdStyleItem::on_checkBoxListNG_clicked()
{
    GetROIState();
}

int RunOsdStyleItem::GetROIState()
{
    QString strStep = GetTaskStep();

    if(ui->checkBoxListNG->isChecked() && ui->checkBoxListOK->isChecked())
    {
        GlobalParameter::m_area_select_state[strStep.toInt()] = LIST_NG_OK_ROI;

    }else if( (!ui->checkBoxListNG->isChecked()) && (!ui->checkBoxListOK->isChecked()))
    {
        GlobalParameter::m_area_select_state[strStep.toInt()] = HIDE_NG_OK_ROI;

    }else if(ui->checkBoxListNG->isChecked() && (!ui->checkBoxListOK->isChecked()))
    {
        GlobalParameter::m_area_select_state[strStep.toInt()] = LIST_NG_ROI;


    }else if((!ui->checkBoxListNG->isChecked()) && ui->checkBoxListOK->isChecked())
    {
        GlobalParameter::m_area_select_state[strStep.toInt()] = LIST_OK_ROI;

    }
}
