#include "BlurDialog.h"
#include "ui_BlurDialog.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
BlurDialog::BlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlurDialog)
{
    ui->setupUi(this);

}

BlurDialog::~BlurDialog()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void BlurDialog::InitData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        m_cfg = ptr->image_acce_param.pre_model_cfg.blur_model_cfg;
       unsigned char value = ptr->image_acce_param.pre_model_cfg.blur_model_cfg.blur_mode_sel;
       ui->txtNum->setText(QString::number(value));
       ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en = 1;
       ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_BLUR_MODEL_ID;
       ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
       ptr->image_acce_param.pre_model_cfg.blur_model_cfg.model_enable =1;
       AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
       AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
       UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_BLUR_MODEL_ID);
    }

}
void BlurDialog::on_btnNumSub_clicked()
{
    int value = ui->txtNum->text().toInt();
    if(value > 1)
    {
        value--;
        ui->txtNum->setText(QString::number(value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.blur_model_cfg.blur_mode_sel = value;
            AcceleratorModuleConfig(ACCE_BLUR_MODEL_ID,m_step);
        }
    }
}
void BlurDialog::on_btnNumAdd_clicked()
{
    int value = ui->txtNum->text().toInt();
    if(value < 9)
    {
        value++;
        ui->txtNum->setText(QString::number(value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.blur_model_cfg.blur_mode_sel = value;
            AcceleratorModuleConfig(ACCE_BLUR_MODEL_ID,m_step);
        }
    }
}

void BlurDialog::on_btnOk_clicked()
{
    QDialog::accept();
}

void BlurDialog::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.blur_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_BLUR_MODEL_ID,m_step);
        }

        QDialog::reject();
    }


}
