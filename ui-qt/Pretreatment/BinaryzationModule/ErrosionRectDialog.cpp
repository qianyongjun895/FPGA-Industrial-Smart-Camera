#include <qdebug.h>
#include "ErrosionRectDialog.h"
#include "ui_ErrosionRectDialog.h"
#include <stdio.h>
#include <math.h>
#include "AcceCommon.h"
ErrosionRectDialog::ErrosionRectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrosionRectDialog)
{
    ui->setupUi(this);
    ui->radioButtonOther->setChecked(true);
    ui->radioButtonCirclee->setChecked(false);
    ui->radioButtonDiamond->setChecked(false);
}

ErrosionRectDialog::~ErrosionRectDialog()
{
    delete ui;
}

void ErrosionRectDialog::IniData()
{
    int max = sqrt(m_num);
    int h;
    int w;
    if(m_num == 9)
    {
        h = 30+50*(max+1)+5+100;
        w = 30+50*(max+1)+5+60+ui->groupBoxBtn->width();
    }else
    {
        h = 30+50*(max+1)+5+40;
        w = 30+50*(max+1)+5+60+ui->groupBoxBtn->width();
    }

    this->setFixedHeight(h);
    this->setFixedWidth(w);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr == NULL)
    {
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

    ui->labelRectPoint->IniRectPoints(this->m_num);
    ui->labelRectPoint->iniRect(cfg.ed_filter_mask);
}

void ErrosionRectDialog::on_btnQuit_clicked()
{
    int max =0;

    char buf[13*13];
    ui->labelRectPoint->GetbufFlag(buf);
    max = sqrt(m_num);

    int i,j;
    int i_num_temp = 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        for(i = 0; i<max;i++)
        {
            i_num_temp =0;

            for(j=0;j<max;j++)
            {

                if((int)buf[i*max+j] == 1)
                {
                    i_num_temp = (0x01 << j) | i_num_temp;
                }
            }
            if(this->m_task_id == ACCE_EROSION_DILATE_MODEL1_ID)
                ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.ed_filter_mask[i] = i_num_temp;
            else
                ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.ed_filter_mask[i] = i_num_temp;
        }

        if(this->m_task_id == ACCE_EROSION_DILATE_MODEL1_ID) //腐蚀模块1中断索引
        {
            AcceleratorModuleConfig(ACCE_EROSION_DILATE_MODEL1_ID,m_step);
        }
        else if(this->m_task_id == ACCE_EROSION_DILATE_MODEL2_ID) //膨胀模块1中断索引
        {
            AcceleratorModuleConfig(ACCE_EROSION_DILATE_MODEL2_ID,m_step);
        }

    }
    QDialog::reject();
}
//全选
void ErrosionRectDialog::on_btnSelectAll_clicked()
{
    ui->labelRectPoint->SelectAll();
}
//全不选
void ErrosionRectDialog::on_btnSelectAllNo_clicked()
{
    ui->labelRectPoint->SelectNoAll();
}

void ErrosionRectDialog::on_radioButtonCirclee_clicked()
{
    if(ui->radioButtonCirclee->isChecked())
        ui->labelRectPoint->DefaultCirclePara();
}

void ErrosionRectDialog::on_radioButtonDiamond_clicked()
{
    if(ui->radioButtonDiamond->isChecked())
        ui->labelRectPoint->DefaultDiamondPara();
}

void ErrosionRectDialog::on_radioButtonOther_clicked()
{
    if(ui->radioButtonOther->isChecked())
        ui->labelRectPoint->ClearDefaultPara();
}
