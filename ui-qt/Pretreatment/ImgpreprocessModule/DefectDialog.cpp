#include "DefectDialog.h"
#include "ui_DefectDialog.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"

DefectDialog::DefectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefectDialog)
{
    ui->setupUi(this);

}

DefectDialog::~DefectDialog()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.pre_model_cfg.defect_model_cfg.defect_wr_ddr_en =0;
        AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
    }
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}

void DefectDialog::on_btnOk_clicked()
{
    QDialog::accept();
}

void DefectDialog::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.defect_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
        }

        QDialog::reject();
    }

}
void DefectDialog::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        DEFECT_MODEL_CFG cfg;
        cfg = ptr->image_acce_param.pre_model_cfg.defect_model_cfg;
        m_cfg = cfg;
        int defect_gain = cfg.defect_gain;
        ui->txtGain->setText(QString::number(defect_gain));
        ui->horizontalSliderGain->setValue(defect_gain);
        ptr->image_acce_param.pre_model_cfg.defect_model_cfg.defect_wr_ddr_en = 1;

        AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
        AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step_id);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_DEFECT_MODEL_ID);
    }
}

void DefectDialog::on_horizontalSliderGain_sliderReleased()
{
    int value = ui->horizontalSliderGain->value();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.pre_model_cfg.defect_model_cfg.defect_gain = value;
        AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
    }

}

void DefectDialog::AddGain(int value)
{

    int current_value  = ui->horizontalSliderGain->value();
    int max = ui->horizontalSliderGain->maximum();

    if(current_value+value <= max)
    {
        ui->horizontalSliderGain->setValue(current_value+value);
        ui->txtGain->setText(QString::number(current_value+value));

        //int value = ui->horizontalSliderGain->value();
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.defect_model_cfg.defect_gain = current_value+value;
            AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
        }
    }
}
void DefectDialog::SubGain(int value)
{
    int current_value  = ui->horizontalSliderGain->value();
    if(current_value-value > 0)
    {
        ui->horizontalSliderGain->setValue(current_value - value);
        ui->txtGain->setText(QString::number(current_value - value));
        //int value = ui->horizontalSliderGain->value();
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.defect_model_cfg.defect_gain = current_value-value;
            AcceleratorModuleConfig(ACCE_DEFECT_MODEL_ID,m_step_id);
        }
    }
}

void DefectDialog::on_btnSubGain_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&DefectDialog::SubGain);
    UtilitiesFun::Instance()->StartTimer(100);
}

void DefectDialog::on_btnSubGain_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&DefectDialog::SubGain);
    SubGain();
}

void DefectDialog::on_btnAddGain_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&DefectDialog::AddGain);
    UtilitiesFun::Instance()->StartTimer(100);
}

void DefectDialog::on_btnAddGain_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&DefectDialog::AddGain);
    AddGain();
}

void DefectDialog::on_horizontalSliderGain_valueChanged(int value)
{
    ui->txtGain->setText(QString::number(value));
}


