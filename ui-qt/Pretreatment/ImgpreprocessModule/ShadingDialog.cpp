#include "ShadingDialog.h"
#include "ui_ShadingDialog.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"

ShadingDialog::ShadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShadingDialog)
{
    ui->setupUi(this);
    ui->groupBoxMiddleValue->setVisible(false);
}

ShadingDialog::~ShadingDialog()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_ddr_wr_en= 0;
        AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    }
    delete ui;
}

void ShadingDialog::on_btnOk_clicked()
{
    QDialog::accept();
}

void ShadingDialog::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.shading_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
        }

        QDialog::reject();
    }

}
void ShadingDialog::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;

    SHADING_MODEL_CFG cfg;
    cfg = ptr->image_acce_param.pre_model_cfg.shading_model_cfg;
    m_cfg = cfg;
    int ret;
    ret = cfg.shading_bright_gain;
    ui->txtGain->setText(QString::number(ret));
    ui->horizontalSliderGain->setValue(ret);

    ret = cfg.shading_kernel;
    switch (ret) {
    case 1:
        ui->radioButton3->setChecked(true);
        break;
    case 2:
        ui->radioButton5->setChecked(true);
        break;
    case 3:
        ui->radioButton7->setChecked(true);
        break;
    case 4:
        ui->radioButton9->setChecked(true);
        break;
    case 5:
        ui->radioButton11->setChecked(true);
        break;
    case 6:
        ui->radioButton13->setChecked(true);
        break;
    default:
        ui->radioButton3->setChecked(true);
        break;
    }

    ret = cfg.shading_vh_sel;
    switch (ret) {
    case 0:
        ui->radioButtonXY->setChecked(true);
        break;
    case 1:
        ui->radioButtonX->setChecked(true);
        break;
    case 2:
         ui->radioButtonY->setChecked(true);
        break;
    default:
         ui->radioButtonXY->setChecked(true);
        break;
    }
    ret = cfg.shading_mode;
    switch (ret) {
    case 0:
        ui->groupBoxScale->setEnabled(false);
        ui->radioButtonX->setEnabled(false);
        ui->radioButtonY->setEnabled(false);
        ui->radioButtonAverage->setChecked(true);
        break;
    case 1:
        ui->groupBoxScale->setEnabled(false);
        ui->radioButtonX->setEnabled(false);
        ui->radioButtonY->setEnabled(false);
        ui->radioButtonMiddle->setChecked(true);
        break;
    case 2:
        ui->groupBoxScale->setEnabled(true);
        ui->radioButtonX->setEnabled(true);
        ui->radioButtonY->setEnabled(true);
        ui->radioButtonShade->setChecked(true);
        break;
    default:
        ui->groupBoxScale->setEnabled(false);
        ui->radioButtonX->setEnabled(false);
        ui->radioButtonY->setEnabled(false);
        ui->radioButtonAverage->setChecked(true);
        break;
    }
    ret = cfg.shading_dir;
    switch (ret) {
    case 0:
        ui->radioButtonB->setChecked(true);
        ui->groupBoxGainDark->setVisible(false);
        ui->groupBoxGain->setTitle("缺陷增益");
        break;
    case 1:
        ui->radioButtonD->setChecked(true);
        ui->groupBoxGainDark->setVisible(false);
        ui->groupBoxGain->setTitle("缺陷增益");
        break;
    case 2:
        ui->radioButtonBD->setChecked(true);
        ui->groupBoxGainDark->setVisible(false);
        ui->groupBoxGain->setTitle("缺陷增益");
        break;
    case 3:
        ui->radioButtonBDRand->setChecked(true);
        ui->groupBoxGainDark->setVisible(true);
        ui->groupBoxGain->setTitle("缺陷增益");
        break;
    default:
        ui->radioButtonB->setChecked(true);
        ui->groupBoxGainDark->setVisible(false);
        ui->groupBoxGain->setTitle("明缺陷增益");
        break;
    }

    ret = cfg.shading_dark_gain;
    ui->txtGainDark->setText(QString::number(ret));
    ui->horizontalSliderGainDark->setValue(ret);

    ret = cfg.shading_th;
    ui->txtTh->setText(QString::number(ret));
    ui->horizontalSliderTH->setValue(ret);

    ret = cfg.shading_base_value;
    ui->txtMiddleValue->setText(QString::number(ret));

    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_ddr_wr_en =1;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.model_enable =1;
    ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step_id);
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_SHADING_MODEL_ID);

}

void ShadingDialog::on_horizontalSliderGain_sliderPressed()
{

}

void ShadingDialog::on_horizontalSliderGain_sliderReleased()
{
    int value = ui->horizontalSliderGain->value();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_bright_gain = value;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::AddGain(int value)
{
    int current_value  = ui->horizontalSliderGain->value();
    int max = ui->horizontalSliderGain->maximum();

    if(current_value+value <= max)
    {
        ui->horizontalSliderGain->setValue(current_value+value);
        ui->txtGain->setText(QString::number(current_value+value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr == NULL)
            return;
        ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_bright_gain = current_value+value;
        AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    }
}
void ShadingDialog::SubGain(int value)
{
    int current_value  = ui->horizontalSliderGain->value();

    if(current_value-value >= 0)
    {
        ui->horizontalSliderGain->setValue(current_value - value);
        ui->txtGain->setText(QString::number(current_value - value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr == NULL)
            return;
        ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_bright_gain = current_value-value;
        AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    }
}

void ShadingDialog::on_btnSubGain_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::SubGain);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ShadingDialog::on_btnSubGain_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::SubGain);
    SubGain();
}

void ShadingDialog::on_btnAddGain_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::AddGain);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ShadingDialog::on_btnAddGain_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::AddGain);
    AddGain();
}

void ShadingDialog::on_horizontalSliderGain_valueChanged(int value)
{
    ui->txtGain->setText(QString::number(value));
}

void ShadingDialog::on_radioButton3_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_kernel = 1;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}
void ShadingDialog::on_radioButton5_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_kernel = 2;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}
void ShadingDialog::on_radioButton7_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_kernel = 3;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}
void ShadingDialog::on_radioButton9_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_kernel = 4;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}
void ShadingDialog::on_radioButton11_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_kernel = 5;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}
void ShadingDialog::on_radioButton13_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_kernel = 6;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonXY_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_vh_sel = 0;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonX_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_vh_sel = 1;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonY_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_vh_sel = 2;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonAverage_clicked()
{
    ui->groupBoxScale->setEnabled(false);
    ui->radioButtonX->setEnabled(false);
    ui->radioButtonY->setEnabled(false);
    ui->radioButtonXY->setChecked(true);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_vh_sel = 0;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_mode = 0;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonMiddle_clicked()
{
    ui->groupBoxScale->setEnabled(false);
    ui->radioButtonX->setEnabled(false);
    ui->radioButtonY->setEnabled(false);
    ui->radioButtonXY->setChecked(true);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_vh_sel = 0;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_mode = 1;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonShade_clicked()
{
    ui->groupBoxScale->setEnabled(true);
    ui->radioButtonX->setEnabled(true);
    ui->radioButtonY->setEnabled(true);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_mode = 2;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_radioButtonB_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dir = 0;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    ui->groupBoxGainDark->setVisible(false);
    ui->groupBoxGain->setTitle("缺陷增益");
}

void ShadingDialog::on_radioButtonD_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dir = 1;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    ui->groupBoxGainDark->setVisible(false);
    ui->groupBoxGain->setTitle("缺陷增益");
}

void ShadingDialog::on_radioButtonBD_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dir = 2;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    ui->groupBoxGainDark->setVisible(false);
    ui->groupBoxGain->setTitle("缺陷增益");
}

void ShadingDialog::on_radioButtonBDRand_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dir = 3;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    ui->groupBoxGainDark->setVisible(true);
    ui->groupBoxGain->setTitle("明缺陷增益");
}

void ShadingDialog::on_btnSubTH_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::SubTH);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ShadingDialog::on_btnSubTH_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::SubTH);
    SubTH();

}

void ShadingDialog::on_btnAddTH_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::AddTH);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ShadingDialog::on_btnAddTH_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::AddTH);
    AddTH();
}

void ShadingDialog::on_horizontalSliderTH_valueChanged(int value)
{
    ui->txtTh->setText(QString::number(value));
}

void ShadingDialog::on_horizontalSliderTH_sliderReleased()
{
    int value = ui->horizontalSliderTH->value();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_th = value;
    AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}
void ShadingDialog::SubTH(int value)
{
    int current_value  = ui->horizontalSliderTH->value();

    if(current_value-value >= 0)
    {
        ui->horizontalSliderTH->setValue(current_value - value);
        ui->txtTh->setText(QString::number(current_value - value));

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr == NULL)
            return;
         ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_th = current_value - value;
         AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);

    }
}
void ShadingDialog::AddTH(int value)
{
    int current_value  = ui->horizontalSliderTH->value();
    int max = ui->horizontalSliderTH->maximum();

    if(current_value+value <= max)
    {
        ui->horizontalSliderTH->setValue(current_value+value);
        ui->txtTh->setText(QString::number(current_value+value));

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr == NULL)
            return;
         ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_th = current_value + value;
         AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    }
}

void ShadingDialog::on_btnSubGainDark_pressed()
{
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::SubGainDark);
    UtilitiesFun::Instance()->startTimer(100);
}

void ShadingDialog::on_btnSubGainDark_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::SubGainDark);
    SubGainDark();
}

void ShadingDialog::on_btnAddGainDark_pressed()
{
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::AddGainDark);
    UtilitiesFun::Instance()->startTimer(100);
}

void ShadingDialog::on_btnAddGainDark_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ShadingDialog::AddGainDark);
    AddGainDark();
}

void ShadingDialog::on_horizontalSliderGainDark_sliderReleased()
{
    int value = ui->horizontalSliderGainDark->value();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
     ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dark_gain =  value;
     AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
}

void ShadingDialog::on_horizontalSliderGainDark_valueChanged(int value)
{
    ui->txtGainDark->setText(QString::number(value));
}
void ShadingDialog::SubGainDark(int value)
{
    int current_value  = ui->horizontalSliderGainDark->value();

    if(current_value-value >= 0)
    {
        ui->horizontalSliderGainDark->setValue(current_value - value);
        ui->txtGainDark->setText(QString::number(current_value - value));

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr == NULL)
            return;
         ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dark_gain =  current_value - value;
         AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    }
}
void ShadingDialog::AddGainDark(int value)
{
    int current_value  = ui->horizontalSliderGainDark->value();
    int max = ui->horizontalSliderGainDark->maximum();

    if(current_value+value <= max)
    {
        ui->horizontalSliderGainDark->setValue(current_value+value);
        ui->txtGainDark->setText(QString::number(current_value+value));

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr == NULL)
            return;
         ptr->image_acce_param.pre_model_cfg.shading_model_cfg.shading_dark_gain =  current_value+value;
         AcceleratorModuleConfig(ACCE_SHADING_MODEL_ID,m_step_id);
    }
}

