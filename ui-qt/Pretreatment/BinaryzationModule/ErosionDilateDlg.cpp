#include <qdebug.h>
#include "ErosionDilateDlg.h"
#include <QMessageBox>
#include "ui_ErosionDilateDlg.h"
#include "../../Global/UtilitiesFun.h"
#include "ErrosionRectDialog.h"
#include "AcceCommon.h"


ErosionDilateDlg::ErosionDilateDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErosionDilateDlg)
{
    ui->setupUi(this);
}

ErosionDilateDlg::~ErosionDilateDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void ErosionDilateDlg::InitData()
{
    m_bflag_ini = 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr == NULL)
    {
        m_bflag_ini = 1;
        return;
    }

    ERD_DIL_MODEL_CFG cfg;

    if(this->m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
    {
        cfg =  ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg;
    }
    else if(this->m_task_id == ACCE_EROSION_DILATE_MODEL2_ID) //膨胀模块1中断索引
    {
        cfg =  ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg;
    }
    m_cfg = cfg;
    unsigned int iType = cfg.ed_model_type;

    switch (iType) {
    case ED_MODEL_TYPE_3x3:
        ui->radioButton3->setChecked(true);
        ui->radioButton5->setChecked(false);
        ui->radioButton7->setChecked(false);
        ui->radioButton9->setChecked(false);
        ui->radioButton11->setChecked(false);
        ui->radioButton13->setChecked(false);
        ui->horizontalSliderLimit->setRange(1,9);
        ui->horizontalSliderLimit->setPageStep(1);
        ui->horizontalSliderLimit->setSingleStep(1);

        break;
    case ED_MODEL_TYPE_5x5:
        ui->radioButton3->setChecked(false);
        ui->radioButton5->setChecked(true);
        ui->radioButton7->setChecked(false);
        ui->radioButton9->setChecked(false);
        ui->radioButton11->setChecked(false);
        ui->radioButton13->setChecked(false);
        ui->horizontalSliderLimit->setRange(1,25);
        ui->horizontalSliderLimit->setPageStep(1);
        ui->horizontalSliderLimit->setSingleStep(1);
        break;
    case ED_MODEL_TYPE_7x7:
        ui->radioButton3->setChecked(false);
        ui->radioButton5->setChecked(false);
        ui->radioButton7->setChecked(true);
        ui->radioButton9->setChecked(false);
        ui->radioButton11->setChecked(false);
        ui->radioButton13->setChecked(false);
        ui->horizontalSliderLimit->setRange(1,49);
        ui->horizontalSliderLimit->setPageStep(1);
        ui->horizontalSliderLimit->setSingleStep(1);
        break;
    case ED_MODEL_TYPE_9x9:
        ui->radioButton3->setChecked(false);
        ui->radioButton5->setChecked(false);
        ui->radioButton7->setChecked(false);
        ui->radioButton9->setChecked(true);
        ui->radioButton11->setChecked(false);
        ui->radioButton13->setChecked(false);
        ui->horizontalSliderLimit->setRange(1,81);
        ui->horizontalSliderLimit->setPageStep(1);
        ui->horizontalSliderLimit->setSingleStep(1);
        break;
    case ED_MODEL_TYPE_11x11:
        ui->radioButton3->setChecked(false);
        ui->radioButton5->setChecked(false);
        ui->radioButton7->setChecked(false);
        ui->radioButton9->setChecked(false);
        ui->radioButton11->setChecked(true);
        ui->radioButton13->setChecked(false);
        ui->horizontalSliderLimit->setRange(1,121);
        ui->horizontalSliderLimit->setPageStep(1);
        ui->horizontalSliderLimit->setSingleStep(1);
        break;
    case ED_MODEL_TYPE_13x13:
        ui->radioButton3->setChecked(false);
        ui->radioButton5->setChecked(false);
        ui->radioButton7->setChecked(false);
        ui->radioButton9->setChecked(false);
        ui->radioButton11->setChecked(false);
        ui->radioButton13->setChecked(true);
        ui->horizontalSliderLimit->setRange(1,169);
        ui->horizontalSliderLimit->setPageStep(1);
        ui->horizontalSliderLimit->setSingleStep(1);
        break;
    default:
        break;
    }

    if(cfg.ed_side_del_enable == 1)
        ui->checkBoxedSideDelEnable->setChecked(true);
    else
        ui->checkBoxedSideDelEnable->setChecked(false);

    if(cfg.ed_mode == 1)
    {
        ui->radioButtonErosion->setChecked(true);
        ui->radioButtonDilate->setChecked(false);
    }else
    {
        ui->radioButtonErosion->setChecked(false);
        ui->radioButtonDilate->setChecked(true);
    }

    int iLimit = (int)cfg.ed_th;
    ui->horizontalSliderLimit->setValue(iLimit);
    ui->labelLimit->setText(QString::number(iLimit));

    int inum = (int)cfg.ed_loop_cnt;

    if(inum <=0 || inum > 5)
        inum = 5;

    ui->txtNum->setText(QString::number(inum));

    if(cfg.ed_boundary_extr_enable == 1)
    {
        ui->checkBoxedEdgeCalcu->setChecked(true);
        ui->groupBoxLimit->setEnabled(false);
        ui->groupBoxMode->setEnabled(false);
        ui->groupBoxModeType->setEnabled(false);
        ui->groupBoxNum->setEnabled(false);
        ui->btnExpant->setEnabled(false);
    }
    else
    {
        ui->checkBoxedEdgeCalcu->setChecked(false);
        ui->groupBoxLimit->setEnabled(true);
        ui->groupBoxMode->setEnabled(true);
        ui->groupBoxModeType->setEnabled(true);
        ui->groupBoxNum->setEnabled(true);
        ui->btnExpant->setEnabled(true);
    }
    if(this->m_task_id == ACCE_EROSION_DILATE_MODEL1_ID) //腐蚀模块1中断索引
    {
        ptr->image_acce_param.bw_proc_model_cfg.bw_proc_wr_ddr_en = 1;
        ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable = 1;
        ptr->image_acce_param.bw_proc_model_cfg.bw_proc_src_sel = ACCE_EROSION_DILATE_MODEL1_ID;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_BW_PROC_MODEL_ID;
        AcceleratorModuleConfig(ACCE_BW_PROC_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_EROSION_DILATE_MODEL1_ID);
    }
    else if(this->m_task_id == ACCE_EROSION_DILATE_MODEL2_ID) //膨胀模块1中断索引
    {
        ptr->image_acce_param.bw_proc_model_cfg.bw_proc_wr_ddr_en = 1;
        ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.model_enable = 1;
        ptr->image_acce_param.bw_proc_model_cfg.bw_proc_src_sel = ACCE_EROSION_DILATE_MODEL2_ID;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_BW_PROC_MODEL_ID;
        AcceleratorModuleConfig(ACCE_BW_PROC_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_EROSION_DILATE_MODEL2_ID);
    }
    m_bflag_ini = 1;

}
void ErosionDilateDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void ErosionDilateDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            if(this->m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg = m_cfg;
            }
            else if(this->m_task_id == ACCE_EROSION_DILATE_MODEL2_ID) //膨胀模块1中断索引
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg = m_cfg;
            }
            SetLibToData();
        }

        QDialog::reject();
    }
}
void ErosionDilateDlg::LimitSub(int value)
{
    int iValue = ui->horizontalSliderLimit->value();

    if(iValue-value >= 1)
    {
        iValue -= value;
        ui->horizontalSliderLimit->setValue(iValue);
        ui->labelLimit->setText(QString::number(iValue));
        SetLibToData();
    }
}
void ErosionDilateDlg::LimitAdd(int value)
{
    int iMax = ui->horizontalSliderLimit->maximum();
    int ivalue = ui->horizontalSliderLimit->value();

    if(ivalue+value <= iMax)
    {
        ivalue += value;
        ui->horizontalSliderLimit->setValue(ivalue);
        ui->labelLimit->setText(QString::number(ivalue));
        SetLibToData();
    }
}
void ErosionDilateDlg::on_btnLimitSub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ErosionDilateDlg::LimitSub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ErosionDilateDlg::on_btnLimitSub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ErosionDilateDlg::LimitSub);
    LimitSub(1);
}

void ErosionDilateDlg::on_btnLimitAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ErosionDilateDlg::LimitAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ErosionDilateDlg::on_btnLimitAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ErosionDilateDlg::LimitAdd);
    LimitAdd(1);
}

void ErosionDilateDlg::on_horizontalSliderLimit_valueChanged(int value)
{
    if (m_bflag_ini == 1)
    {
        ui->labelLimit->setText(QString::number(value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        //ACCE_MODEL *ptr = (ACCE_MODEL*)GetStepAcceModelPointer(1);

        if(ptr != NULL)
        {
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_th =value;
            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_th =value;
            }
        }
    }
}

void ErosionDilateDlg::on_horizontalSliderLimit_sliderReleased()
{
     SetLibToData();
}
void ErosionDilateDlg::on_radioButton3_clicked()
{
    ui->horizontalSliderLimit->setRange(1,9);
    ui->horizontalSliderLimit->setPageStep(1);
    ui->horizontalSliderLimit->setSingleStep(1);
    ui->horizontalSliderLimit->setValue(5);
    ui->labelLimit->setText(QString::number(5));
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type =ED_MODEL_TYPE_3x3;
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type =ED_MODEL_TYPE_3x3;
        }

    }
    Clear_filter_mask(ED_MODEL_TYPE_3x3,ED_MODEL_MASK_3x3);
    SetLibToData();
}

void ErosionDilateDlg::on_radioButton5_clicked()
{
    ui->horizontalSliderLimit->setRange(1,25);
    ui->horizontalSliderLimit->setPageStep(1);
    ui->horizontalSliderLimit->setSingleStep(1);
    ui->horizontalSliderLimit->setValue(13);
    ui->labelLimit->setText(QString::number(13));
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type =ED_MODEL_TYPE_5x5;
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type =ED_MODEL_TYPE_5x5;
        }

    }
    Clear_filter_mask(ED_MODEL_TYPE_5x5,ED_MODEL_MASK_5x5);
    SetLibToData();
}

void ErosionDilateDlg::on_radioButton7_clicked()
{
    ui->horizontalSliderLimit->setRange(1,49);
    ui->horizontalSliderLimit->setPageStep(1);
    ui->horizontalSliderLimit->setSingleStep(1);
    ui->horizontalSliderLimit->setValue(25);
    ui->labelLimit->setText(QString::number(25));
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type =ED_MODEL_TYPE_7x7;
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type =ED_MODEL_TYPE_7x7;
        }

    }
    Clear_filter_mask(ED_MODEL_TYPE_7x7,ED_MODEL_MASK_7x7);
    SetLibToData();
}

void ErosionDilateDlg::on_radioButton9_clicked()
{
    ui->horizontalSliderLimit->setRange(1,81);
    ui->horizontalSliderLimit->setPageStep(1);
    ui->horizontalSliderLimit->setSingleStep(1);
    ui->horizontalSliderLimit->setValue(41);
    ui->labelLimit->setText(QString::number(41));
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type =ED_MODEL_TYPE_9x9;
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type =ED_MODEL_TYPE_9x9;
        }

    }
    Clear_filter_mask(ED_MODEL_TYPE_9x9,ED_MODEL_MASK_9x9);
    SetLibToData();

}

void ErosionDilateDlg::on_radioButton11_clicked()
{
    ui->horizontalSliderLimit->setRange(1,121);
    ui->horizontalSliderLimit->setPageStep(1);
    ui->horizontalSliderLimit->setSingleStep(1);
    ui->horizontalSliderLimit->setValue(61);
    ui->labelLimit->setText(QString::number(61));
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type =ED_MODEL_TYPE_11x11;
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type =ED_MODEL_TYPE_11x11;
        }

    }
    Clear_filter_mask(ED_MODEL_TYPE_11x11,ED_MODEL_MASK_11x11);
    SetLibToData();

}

void ErosionDilateDlg::on_radioButton13_clicked()
{
    ui->horizontalSliderLimit->setRange(1,169);
    ui->horizontalSliderLimit->setPageStep(1);
    ui->horizontalSliderLimit->setSingleStep(1);
    ui->horizontalSliderLimit->setValue(85);
    ui->labelLimit->setText(QString::number(85));
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type =ED_MODEL_TYPE_13x13;
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type =ED_MODEL_TYPE_13x13;
        }

    }
    Clear_filter_mask(ED_MODEL_TYPE_13x13,ED_MODEL_MASK_13x13);
    SetLibToData();
}
void ErosionDilateDlg::on_checkBoxedSideDelEnable_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            if(ui->checkBoxedSideDelEnable->isChecked())
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_side_del_enable = 1;
                SetLibToData();
            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_side_del_enable = 0;
                SetLibToData();
            }
        }else
        {
            if(ui->checkBoxedSideDelEnable->isChecked())
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_side_del_enable = 1;
                SetLibToData();
            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_side_del_enable = 0;
                SetLibToData();
            }
        }
    }
}

void ErosionDilateDlg::on_radioButtonErosion_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            if(ui->radioButtonErosion->isChecked())
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_mode = 1;
                SetLibToData();
            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_mode = 0;
                SetLibToData();
            }
        }else
        {
            if(ui->radioButtonErosion->isChecked())
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_mode = 1;
                SetLibToData();

            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_mode = 0;
                SetLibToData();
            }
        }
    }
}

void ErosionDilateDlg::on_radioButtonDilate_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
        {
            if(ui->radioButtonDilate->isChecked())
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_mode = 0;
                SetLibToData();
            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_mode = 1;
                SetLibToData();
            }
        }
        else
        {
            if(ui->radioButtonDilate->isChecked())
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_mode = 0;
                SetLibToData();

            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_mode = 1;
                SetLibToData();
            }
        }
    }
}
void ErosionDilateDlg::SetLibToData()
{

    if(this->m_task_id == ACCE_EROSION_DILATE_MODEL1_ID) //腐蚀模块1中断索引
    {
        AcceleratorModuleConfig(ACCE_EROSION_DILATE_MODEL1_ID,m_step);
        //AcceleratorModuleCfgShow(ACCE_EROSION_DILATE_MODEL1_ID);
    }
    else if(this->m_task_id == ACCE_EROSION_DILATE_MODEL2_ID) //膨胀模块1中断索引
    {
        AcceleratorModuleConfig(ACCE_EROSION_DILATE_MODEL2_ID,m_step);
        //AcceleratorModuleCfgShow(ACCE_EROSION_DILATE_MODEL1_ID);
    }
}
void ErosionDilateDlg::on_btnExpant_clicked()
{
    int inum = 0;

    if(ui->radioButton3->isChecked())
    {
        inum = 3*3;

    }else if(ui->radioButton5->isChecked())
    {
        inum = 5*5;
    }
    else if(ui->radioButton7->isChecked())
    {
        inum = 7*7;
    }else if(ui->radioButton9->isChecked())
    {
        inum = 9*9;
    }else if(ui->radioButton11->isChecked())
    {
        inum = 11*11;
    }
    else if(ui->radioButton13->isChecked())
    {
        inum = 13*13;
    }
    ErrosionRectDialog dlg;
    dlg.m_num = inum;
    dlg.m_task_id = m_task_id;
    dlg.m_pre_ptr = m_pre_ptr;
    dlg.m_step = this->m_step;
    dlg.IniData();
    dlg.exec();

}

void ErosionDilateDlg::on_btnNumSub_clicked()
{
    int value = ui->txtNum->text().toInt();
    if(value > 1)
    {
        value--;
        ui->txtNum->setText(QString::number(value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_loop_cnt = value;
            else
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_loop_cnt = value;
            SetLibToData();
        }
    }
}

void ErosionDilateDlg::on_btnNumAdd_clicked()
{
    int value = ui->txtNum->text().toInt();
    if(value < 5)
    {
        value++;
        ui->txtNum->setText(QString::number(value));
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
        if(ptr != NULL)
        {
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_loop_cnt = value;
            else
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_loop_cnt = value;
            SetLibToData();
        }
    }
}

void ErosionDilateDlg::on_checkBoxedEdgeCalcu_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        if(ui->checkBoxedEdgeCalcu->isChecked())
        {
            ui->radioButtonDilate->setChecked(true);
            ui->radioButton3->setChecked(true);
            ui->horizontalSliderLimit->setValue(1);
            ui->labelLimit->setText("1");
            ui->txtNum->setText("1");
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_model_type = ED_MODEL_TYPE_3x3;
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_th = 1;
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_loop_cnt = 1;
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_mode = 0;
            }else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_model_type = ED_MODEL_TYPE_3x3;
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_th = 1;
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_loop_cnt = 1;
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_mode = 0;
            }


            Clear_filter_mask(ED_MODEL_TYPE_3x3,ED_MODEL_MASK_3x3);

            if(ui->checkBoxedEdgeCalcu->isChecked())
            {
                if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
                {
                    ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_filter_mask[0] = 2;
                    ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_filter_mask[1] = 5;
                    ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_filter_mask[2] = 2;
                }else
                {
                    ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_filter_mask[0] = 2;
                    ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_filter_mask[1] = 5;
                    ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_filter_mask[2] = 2;
                }

            }
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_boundary_extr_enable = 1;
            }
            else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_boundary_extr_enable = 1;
            }
            SetLibToData();
            ui->groupBoxLimit->setEnabled(false);
            ui->groupBoxMode->setEnabled(false);
            ui->groupBoxModeType->setEnabled(false);
            ui->groupBoxNum->setEnabled(false);
            ui->btnExpant->setEnabled(false);

        }else
        {
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_boundary_extr_enable = 0;
            }
            else
            {
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_boundary_extr_enable = 0;
            }
            SetLibToData();
            ui->groupBoxLimit->setEnabled(true);
            ui->groupBoxMode->setEnabled(true);
            ui->groupBoxModeType->setEnabled(true);
            ui->groupBoxNum->setEnabled(true);
            ui->btnExpant->setEnabled(true);
        }
    }
}
void ErosionDilateDlg::Clear_filter_mask(int type,int value)
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        int i;
        for(i=0; i< 16;i++)
        {
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_filter_mask[i] = 0;
            else
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_filter_mask[i] = 0;
        }
        for(i=0; i< type;i++)
        {
            if(m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_filter_mask[i] = value;
            else
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_filter_mask[i] = value;
        }
    }

}
