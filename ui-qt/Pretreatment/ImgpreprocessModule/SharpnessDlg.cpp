#include "SharpnessDlg.h"
#include "ui_SharpnessDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"

SharpnessDlg::SharpnessDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SharpnessDlg)
{
    ui->setupUi(this);
}

SharpnessDlg::~SharpnessDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void SharpnessDlg::InitData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        int iLevel = 0;
        iLevel = ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.sharpness_level;
        m_cfg = ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg;
        ui->txtSharpness->setText(QString::number(iLevel));
        ui->horizontalSliderSharpness->setValue(iLevel);
        ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en = 1;
        ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_SHARPNESS_MODEL_ID;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
        ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.model_enable =1;
        AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_SHARPNESS_MODEL_ID);
    }
}
void SharpnessDlg::on_btnSubSharpness_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&SharpnessDlg::SubSharpness);
    UtilitiesFun::Instance()->StartTimer(100);
}

void SharpnessDlg::on_btnSubSharpness_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&SharpnessDlg::SubSharpness);
    SubSharpness();
}

void SharpnessDlg::on_btnAddSharpness_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&SharpnessDlg::AddSharpness);
    UtilitiesFun::Instance()->StartTimer(100);
}

void SharpnessDlg::on_btnAddSharpness_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&SharpnessDlg::AddSharpness);
    AddSharpness();
}

void SharpnessDlg::on_horizontalSliderSharpness_sliderReleased()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        int value = ui->horizontalSliderSharpness->value();
        ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.sharpness_level = value;
        AcceleratorModuleConfig(ACCE_SHARPNESS_MODEL_ID,m_step);
    }
}

void SharpnessDlg::on_horizontalSliderSharpness_valueChanged(int value)
{
    ui->txtSharpness->setText(QString::number(value));
}
void SharpnessDlg::AddSharpness(int value )
{
    int iLevel = ui->horizontalSliderSharpness->value();
    int max = ui->horizontalSliderSharpness->maximum();
    if(iLevel +value <= max)
    {
        ui->txtSharpness->setText(QString::number(iLevel +value));
        ui->horizontalSliderSharpness->setValue(iLevel +value);

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.sharpness_level = iLevel +value;
            AcceleratorModuleConfig(ACCE_SHARPNESS_MODEL_ID,m_step);
        }
    }
}
void SharpnessDlg::SubSharpness(int value )
{
    int iLevel = ui->horizontalSliderSharpness->value();

    if(iLevel -value >= 0)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        ui->txtSharpness->setText(QString::number(iLevel -value));
        ui->horizontalSliderSharpness->setValue(iLevel -value);

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.sharpness_level = iLevel -value;
            AcceleratorModuleConfig(ACCE_SHARPNESS_MODEL_ID,m_step);
        }
    }
}


void SharpnessDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void SharpnessDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_SHARPNESS_MODEL_ID,m_step);
        }

        QDialog::reject();
    }

}
