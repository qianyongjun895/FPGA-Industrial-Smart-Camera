#include "GrayHistogramDialog.h"
#include "ui_GrayHistogramDialog.h"
#include <qdebug.h>
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
#include "Histogram.h"
#include "cmos_common.h"
GrayHistogramDialog::GrayHistogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrayHistogramDialog)
{
    ui->setupUi(this);
}

GrayHistogramDialog::~GrayHistogramDialog()
{
    delete ui;
}
void GrayHistogramDialog::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        m_cfg = ptr->image_acce_param.hist_model_cfg;
        unsigned char iHistSel = ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel;

        if(iHistSel == 0x00)
        {
            ui->radioButtonColumn->setChecked(true);
            ui->radioButtonRow->setChecked(false);
        }else
        {
            ui->radioButtonColumn->setChecked(false);
            ui->radioButtonRow->setChecked(true);
        }
        iHistSel = ptr->image_acce_param.hist_model_cfg.hist_bw_color_sel;
        if(iHistSel == 0x00)
        {
            ui->radioButtonWhhiltePix->setChecked(true);
            ui->radioButtonBlackPix->setChecked(false);
        }else
        {
            ui->radioButtonWhhiltePix->setChecked(false);
            ui->radioButtonBlackPix->setChecked(true);
        }
        iHistSel = ptr->image_acce_param.hist_model_cfg.hist_mode_sel;
        if(iHistSel == 0x00)
        {
            ui->groupBoxHW->setEnabled(false);
            ui->groupBoxPix->setEnabled(false);
            ui->radioButtonPic->setChecked(true);
        }else
        {
            ui->radioButtonBin->setChecked(true);
            ui->groupBoxHW->setEnabled(true);
            ui->groupBoxPix->setEnabled(true);
        }
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ptr->image_acce_param.hist_model_cfg.hist_stat_src_sel;
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step_id);
        UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y(),ACCE_HIST_MODEL_ID);
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(ptr->image_acce_param.hist_model_cfg.hist_mode_sel,ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel);
    }
}
void GrayHistogramDialog::on_btnOk_clicked()
{
    QDialog::accept();
}

void GrayHistogramDialog::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.hist_model_cfg = m_cfg ;
            AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        }

        QDialog::reject();
    }
}
//全图统计
void GrayHistogramDialog::on_radioButtonPic_clicked()
{
    ui->groupBoxHW->setEnabled(false);
    ui->groupBoxPix->setEnabled(false);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.hist_model_cfg.hist_mode_sel = 0;
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(0,0);
    }

}
//二值化统计
void GrayHistogramDialog::on_radioButtonBin_clicked()
{
    ui->groupBoxHW->setEnabled(true);
    ui->groupBoxPix->setEnabled(true);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.hist_model_cfg.hist_mode_sel = 1;
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(1,ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel);
    }
}
//按列统计
void GrayHistogramDialog::on_radioButtonColumn_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel = 0;
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(1,0);
    }
}
//按行统计
void GrayHistogramDialog::on_radioButtonRow_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel = 1;
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(1,1);
    }
}
//按白像素统计
void GrayHistogramDialog::on_radioButtonWhhiltePix_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {        
        ptr->image_acce_param.hist_model_cfg.hist_bw_color_sel = 0;
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(1,ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel);
    }
}
//按黑像素统计
void GrayHistogramDialog::on_radioButtonBlackPix_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.hist_model_cfg.hist_bw_color_sel = 1;
        AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,m_step_id);
        PaintPic(1,ptr->image_acce_param.hist_model_cfg.hist_bw_dir_sel);
    }
}
void GrayHistogramDialog::PaintPic(int mode_sel, int bw_dir_sel)
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    //DLLSHARED_EXPORT s32 Get_Hist_Rd_Data(u32 *hist, u32 size, u32 mode_sel, u32 bw_dir_sel);
    unsigned int grade[2560];
    //0x02表示30W像素，0x04表示130W像素，0x10表示500W像素
    int pixel = Get_HWC_Pixel_Size();
    int size = 256;
    int grayMode = 0;
    int times =1;
    if(mode_sel == 0)
    {
        size = 256;
        grayMode = 0;
    }else
    {
        if(pixel == 0x02)
        {
            times = 1;
        }else if(pixel == 0x04)
        {
            times = 2;
        }else if(pixel == 0x10)
        {
            times = 4;
        }
        if(bw_dir_sel == 0)//列
        {
            size = 640*times;
            grayMode = 1;
        }else if(bw_dir_sel == 1)//行
        {
            size = 480*times;
            grayMode = 2;
        }
    }
    int ret;

    ret = Get_Hist_Rd_Data(grade,size,mode_sel,bw_dir_sel);
    if(ret == 0)
    {
        ui->labelPic->SetGrade(grade,size,grayMode,times);
    }else if(ret == -2)
    {
        QMessageBox::about(NULL,tr("提示"),tr("查询直方图数据超时"));
    }
}
