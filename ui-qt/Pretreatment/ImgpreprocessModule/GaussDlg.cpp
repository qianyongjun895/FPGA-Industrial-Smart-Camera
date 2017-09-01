#include "GaussDlg.h"
#include "ui_GaussDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
GaussDlg::GaussDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussDlg)
{
    ui->setupUi(this);
}

GaussDlg::~GaussDlg()
{
     UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}

void GaussDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void GaussDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.gauss_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_GAUSS_FILTER_ID,m_step);
        }

        QDialog::reject();
    }

}
void GaussDlg::InitData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        m_cfg = ptr->image_acce_param.pre_model_cfg.gauss_model_cfg;
        float vlaue = 0.0;
        vlaue = ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.sigma;
        ui->txtSigma->setText(QString::number(vlaue));
        ui->horizontalSliderSigma->setValue(vlaue*100);
        ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en = 1;
        ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_GAUSS_FILTER_ID;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
        ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable =1;
        AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_GAUSS_FILTER_ID);
    }
}
void GaussDlg::AddSigma(int value)
{
   int iSigma = ui->horizontalSliderSigma->value();

   if(iSigma +value <= 1000)
   {
       float fSigma = (iSigma +value)*1.0/100.0;
       ui->txtSigma->setText(QString::number(fSigma,'f',3));
       ui->horizontalSliderSigma->setValue(iSigma +value);

       ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
       if(ptr != NULL)
       {
           ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.sigma = fSigma;
           AcceleratorModuleConfig(ACCE_GAUSS_FILTER_ID,m_step);
       }
   }

}
void GaussDlg::SubSigma(int value)
{
   int iSigma = ui->horizontalSliderSigma->value();

   if(iSigma -value > 0)
   {
       ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
       float fSigma = (iSigma -value)*1.0/100.0;
       ui->txtSigma->setText(QString::number(fSigma,'f',3));
       ui->horizontalSliderSigma->setValue(iSigma -value);

       if(ptr != NULL)
       {
           ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.sigma = fSigma;
           AcceleratorModuleConfig(ACCE_GAUSS_FILTER_ID,m_step);
       }
   }
}
void GaussDlg::on_btnAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&GaussDlg::AddSigma);
    UtilitiesFun::Instance()->StartTimer(100);
}

void GaussDlg::on_btnAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&GaussDlg::AddSigma);
    AddSigma();
}

void GaussDlg::on_btnSub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&GaussDlg::SubSigma);
    UtilitiesFun::Instance()->StartTimer(100);
}

void GaussDlg::on_btnSub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&GaussDlg::SubSigma);
    SubSigma();
}
void GaussDlg::on_horizontalSliderSigma_sliderReleased()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.sigma = ui->horizontalSliderSigma->value()*1.0/100.0;
        AcceleratorModuleConfig(ACCE_GAUSS_FILTER_ID,m_step);
    }
}

void GaussDlg::on_horizontalSliderSigma_valueChanged(int value)
{
    ui->txtSigma->setText(QString::number(value*1.0/100.0));
}
