#include "PeakFilterDlg.h"
#include "ui_PeakFilterDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
PeakFilterDlg::PeakFilterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PeakFilterDlg)
{
    ui->setupUi(this);
}

PeakFilterDlg::~PeakFilterDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void PeakFilterDlg::InitData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        int iMode = 0;
        int iNum =1;
        if(m_SharpnessKind == SharpnessA)
        {
            m_a_cfg = ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg;
            iMode = ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.peak_A_mode;
            iNum = ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.peak_A_loop_num;
            ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_PEAK_FILTER_A_MODEL_ID;
            ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.model_enable =1;

        }else if(m_SharpnessKind == SharpnessB)
        {
            m_b_cfg = ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg;
            iMode = ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.peak_B_mode;
            iNum = ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.peak_B_loop_num;
            ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_PEAK_FILTER_B_MODEL_ID;
            ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.model_enable =1;
        }

        ui->txtNum->setText(QString::number(iNum));
        switch (iMode) {
        case 0:
            ui->radioButtonDilate->setChecked(true);
            ui->radioButtonErosion->setChecked(false);
            break;
        case 1:
            ui->radioButtonDilate->setChecked(false);
            ui->radioButtonErosion->setChecked(true);
            break;
        default:
            ui->radioButtonDilate->setChecked(true);
            ui->radioButtonErosion->setChecked(false);
            break;
        }
        ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en = 1;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
        AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_SHARPNESS_MODEL_ID);
    }
}
void PeakFilterDlg::on_radioButtonErosion_clicked()
{
     ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
     if(ptr != NULL)
     {
         if(m_SharpnessKind == SharpnessA)
         {
             ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.peak_A_mode = 1;
             AcceleratorModuleConfig(ACCE_PEAK_FILTER_A_MODEL_ID,m_step);
         }else if(m_SharpnessKind == SharpnessB)
         {
             ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.peak_B_mode = 1;
             AcceleratorModuleConfig(ACCE_PEAK_FILTER_B_MODEL_ID,m_step);
         }
     }

}

void PeakFilterDlg::on_radioButtonDilate_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_SharpnessKind == SharpnessA)
        {
            ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.peak_A_mode = 0;
            AcceleratorModuleConfig(ACCE_PEAK_FILTER_A_MODEL_ID,m_step);
        }else if(m_SharpnessKind == SharpnessB)
        {
            ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.peak_B_mode = 0;
            AcceleratorModuleConfig(ACCE_PEAK_FILTER_B_MODEL_ID,m_step);
        }
    }
}
void PeakFilterDlg::on_btnNumSub_clicked()
{
    int  iNum = ui->txtNum->text().toInt();
    if(iNum >1)
    {
        iNum--;
        ui->txtNum->setText(QString::number(iNum));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            if(m_SharpnessKind == SharpnessA)
            {
                ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.peak_A_loop_num = iNum;
                AcceleratorModuleConfig(ACCE_PEAK_FILTER_A_MODEL_ID,m_step);
            }else if(m_SharpnessKind == SharpnessB)
            {
                ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.peak_B_loop_num = iNum;
                AcceleratorModuleConfig(ACCE_PEAK_FILTER_B_MODEL_ID,m_step);
            }
        }
    }
}

void PeakFilterDlg::on_btnNumAdd_clicked()
{
    int  iNum = ui->txtNum->text().toInt();
    if(iNum <5)
    {
        iNum++;
        ui->txtNum->setText(QString::number(iNum));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            if(m_SharpnessKind == SharpnessA)
            {
                ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.peak_A_loop_num = iNum;
                AcceleratorModuleConfig(ACCE_PEAK_FILTER_A_MODEL_ID,m_step);
            }else if(m_SharpnessKind == SharpnessB)
            {
                ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.peak_B_loop_num = iNum;
                AcceleratorModuleConfig(ACCE_PEAK_FILTER_B_MODEL_ID,m_step);
            }
        }
    }
}

void PeakFilterDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void PeakFilterDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            if(m_SharpnessKind == SharpnessA)
            {
                ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg = m_a_cfg;
                AcceleratorModuleConfig(ACCE_PEAK_FILTER_A_MODEL_ID,m_step);

            }else if(m_SharpnessKind == SharpnessB)
            {
                ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg = m_b_cfg;
                AcceleratorModuleConfig(ACCE_PEAK_FILTER_B_MODEL_ID,m_step);
            }
        }

        QDialog::reject();
    }

}
