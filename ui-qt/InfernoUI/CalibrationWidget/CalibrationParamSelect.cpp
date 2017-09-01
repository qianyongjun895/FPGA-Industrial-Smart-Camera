#include "CalibrationParamSelect.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_CalibrationParamSelect.h"
#include "ScaleRatio.h"
#include "MultipointDemarcate.h"

CalibrationParamSelect::CalibrationParamSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationParamSelect)
{
    ui->setupUi(this);
}

CalibrationParamSelect::~CalibrationParamSelect()
{
    delete ui;
}

void CalibrationParamSelect::MpdParamListInit()
{
    unsigned int param_num = 0;
    char* paramName = NULL;
    // 获取参数个数
    param_num = GetHomoParamCount();

    if (param_num > HOMO_CONFIG_MAX)
    {
        QMessageBox::about(NULL, tr("提示"), tr("获取参数个数失败!"));
        return ;
    }

    ui->listWidget->clear();
    ui->listWidget->addItem(tr("无"));
    for (int i = 0; i < param_num; ++ i)
    {
        paramName = GetHomoParamName(i);
        ui->listWidget->addItem(QString::number(i+1)+"."+QString::fromUtf8(paramName));
    }

    if (param_num > 0)
    {
        ui->listWidget->setCurrentRow(1);
    }
    else
    {
        ui->listWidget->setCurrentRow(0);
    }
}

void CalibrationParamSelect::ScaleParamListInit()
{
    unsigned int param_num = 0;
    double ratio = 0.0;

    // 获取参数个数
    param_num = GetScaleRatioParamCount();

    if (param_num > SCALE_RATIO_PARAM_MAX)
    {
        QMessageBox::about(NULL, tr("提示"), tr("获取参数个数失败!"));
        return ;
    }

    ui->listWidget->clear();
    ui->listWidget->addItem(tr("无"));
    for (int i = 0; i < param_num; ++ i)
    {
        GetScaleRatioByIndex2(i, &ratio);
        m_scale_value[i] = ratio;
        ui->listWidget->addItem(tr("参数")+QString::number(i+1)+"("+QString::number(ratio)+")");
    }

    if (param_num > 0)
    {
        ui->listWidget->setCurrentRow(1);
    }
    else
    {
        ui->listWidget->setCurrentRow(0);
    }
}

void CalibrationParamSelect::on_btnCancel_clicked()
{
    QDialog::reject();
}

void CalibrationParamSelect::on_listWidget_currentRowChanged(int currentRow)
{
    m_cur_param_index = currentRow;
    m_scale_param_index = currentRow;
}

void CalibrationParamSelect::on_btnOk_clicked()
{
    QDialog::accept();
}
