#include "ContrastSwitchDlg.h"
#include "ui_ContrastSwitchDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
//#include "System.h"

ContrastSwitchDlg::ContrastSwitchDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastSwitchDlg)
{
    ui->setupUi(this);
}

ContrastSwitchDlg::~ContrastSwitchDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void ContrastSwitchDlg::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        m_cfg = ptr->image_acce_param.pre_model_cfg.contrast_model_cfg;
        int ret = ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_gain;
        ui->horizontalSliderGainMask->setValue(ret);
        ui->txtGainMask->setText(QString::number(ret));

        ret = ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_median_gray;
        ui->horizontalSliderGrayMask->setValue(ret);
        ui->txtGrayMask->setText(QString::number(ret));
        ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en = 1;
        ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable =1;
        ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_CONTRAST_MODEL_ID;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
        AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        //ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_wr_ddr_en = 1;
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_CONTRAST_MODEL_ID);
    }
}
void ContrastSwitchDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void ContrastSwitchDlg::on_btnSubGainMask_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::SubGainMask);
    UtilitiesFun::Instance()->StartTimer(100);

}

void ContrastSwitchDlg::on_btnSubGainMask_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::SubGainMask);
    SubGainMask();
}

void ContrastSwitchDlg::on_btnAddGainMask_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::AddGainMask);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ContrastSwitchDlg::on_btnAddGainMask_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::AddGainMask);
    AddGainMask();
}

void ContrastSwitchDlg::on_btnSubGrayMask_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::SubGrayMask);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ContrastSwitchDlg::on_btnSubGrayMask_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::SubGrayMask);
    SubGrayMask();
}

void ContrastSwitchDlg::on_btnAddGrayMask_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::AddGrayMask);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ContrastSwitchDlg::on_btnAddGrayMask_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ContrastSwitchDlg::AddGrayMask);
    AddGrayMask();
}

void ContrastSwitchDlg::on_horizontalSliderGainMask_sliderReleased()
{
    int value = ui->horizontalSliderGainMask->value();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr !=NULL)
    {
        ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_gain = value;
        AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
    }
}

void ContrastSwitchDlg::on_horizontalSliderGainMask_valueChanged(int value)
{
    ui->txtGainMask->setText(QString::number(value));
}

void ContrastSwitchDlg::on_horizontalSliderGrayMask_sliderReleased()
{
    int value = ui->horizontalSliderGrayMask->value();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr !=NULL)
    {
        ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_median_gray = value;
        AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
    }
}

void ContrastSwitchDlg::on_horizontalSliderGrayMask_valueChanged(int value)
{
    ui->txtGrayMask->setText(QString::number(value));
}
void ContrastSwitchDlg::AddGainMask(int value)
{
    int current_value  = ui->horizontalSliderGainMask->value();
    int max = ui->horizontalSliderGainMask->maximum();

    if(current_value+value <= max)
    {
        ui->horizontalSliderGainMask->setValue(current_value+value);
        ui->txtGainMask->setText(QString::number(current_value+value));

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr !=NULL)
        {
            ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_gain = current_value+value;
            AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
        }
    }
}
void ContrastSwitchDlg::SubGainMask(int value)
{
    int current_value  = ui->horizontalSliderGainMask->value();

    if(current_value-value >= 0)
    {
        ui->horizontalSliderGainMask->setValue(current_value - value);
        ui->txtGainMask->setText(QString::number(current_value - value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr !=NULL)
        {
            ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_gain = current_value - value;
            AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
        }
    }
}
void ContrastSwitchDlg::AddGrayMask(int value)
{
    int current_value  = ui->horizontalSliderGrayMask->value();
    int max = ui->horizontalSliderGrayMask->maximum();

    if(current_value+value <= max)
    {
        ui->horizontalSliderGrayMask->setValue(current_value+value);
        ui->txtGrayMask->setText(QString::number(current_value+value));

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr !=NULL)
        {
            ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_median_gray = current_value + value;
            AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
        }
    }
}
void ContrastSwitchDlg::SubGrayMask(int value)
{
    int current_value  = ui->horizontalSliderGrayMask->value();

    if(current_value-value >= 0)
    {
        ui->horizontalSliderGrayMask->setValue(current_value - value);
        ui->txtGrayMask->setText(QString::number(current_value - value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr !=NULL)
        {
            ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.ct_median_gray = current_value - value;
            AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
        }
    }
}


void ContrastSwitchDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.contrast_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_CONTRAST_MODEL_ID,m_step);
        }

        QDialog::reject();
    }


}
