#include "CalibrationParamReference.h"
#include <QDebug>
#include "ui_CalibrationParamReference.h"
#include "CalibrationParamSelect.h"
#include "task/TaskGlobal.h"
#include "MultipointDemarcate.h"

CalibrationParamReference::CalibrationParamReference(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationParamReference)
{
    ui->setupUi(this);
    m_step_index = 0;
}

CalibrationParamReference::~CalibrationParamReference()
{
    delete ui;
}

void CalibrationParamReference::SetParamData(QString &stepName, int curStepIndex)
{
    ui->labelStepName->setText(stepName);
    m_step_index = curStepIndex;
}

void CalibrationParamReference::UpdateParamReference(int paramIndex)
{
    m_param_index = paramIndex;
    char* paramName = NULL;

    if (paramIndex > 0)
    {
        paramName = GetHomoParamName(paramIndex - 1);
        ui->lineEditParamName->setText(QString::number(paramIndex)+"."+QString::fromUtf8(paramName));
    }
    else
    {
        ui->lineEditParamName->setText("");
    }
}

void CalibrationParamReference::UpdateScaleParamRef(int paramIndex, float curFloat)
{
    m_scale_param_index = paramIndex;
    m_scale_value = curFloat;

    if (paramIndex > 0)
    {
        ui->lineEditScaleParamName->setText(tr("参数")+QString::number(paramIndex)+"("+QString::number(curFloat)+")");
    }
    else
    {
        ui->lineEditScaleParamName->setText("");
    }
}

void CalibrationParamReference::on_btnChangeParam_clicked()
{
    CalibrationParamSelect dlg;
    dlg.MpdParamListInit();
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
//        qDebug() << dlg.m_cur_param_index;
        UpdateParamReference(dlg.m_cur_param_index);
        Task_Step_Homo_Param_Index_Set(m_step_index, dlg.m_cur_param_index);
    }
}

void CalibrationParamReference::on_btnScaleChangeParam_clicked()
{
    CalibrationParamSelect dlg;
    dlg.ScaleParamListInit();
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
        if (dlg.m_scale_param_index > 0)
        {
            UpdateScaleParamRef(dlg.m_scale_param_index, dlg.m_scale_value[dlg.m_scale_param_index - 1]);
        }
        else
        {
            UpdateScaleParamRef(0, 0.0);
        }
        Task_Step_Scale_Cali_Param_Index_Set(m_step_index, dlg.m_scale_param_index);
    }
}
