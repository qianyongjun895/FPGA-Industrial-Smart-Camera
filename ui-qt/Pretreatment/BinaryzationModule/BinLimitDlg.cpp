#include <qdebug.h>
#include "BinLimitDlg.h"
#include <QMessageBox>
#include "ui_BinLimitDlg.h"
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
#include "Binary.h"

BinLimitDlg::BinLimitDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinLimitDlg)
{
    ui->setupUi(this);
}

BinLimitDlg::~BinLimitDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void BinLimitDlg::InitData()
{
    m_First = 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        m_bw_cfg = ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg;

        if(ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_inv_en == 1)
        {
            ui->checkBoxBinaryzationReverse->setChecked(true);
        }else
        {
            ui->checkBoxBinaryzationReverse->setChecked(false);
        }

        unsigned  int ivalue;
        ivalue = ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_th_low;
        ui->horizontalSliderDownBin->setValue(ivalue);
        ui->txtDownBin->setText(QString::number(ivalue));
        ivalue = ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_th_high;
        ui->horizontalSliderUpBin->setValue(ivalue);
        ui->txtUpBin->setText(QString::number(ivalue));
        ptr->image_acce_param.bw_proc_model_cfg.bw_proc_wr_ddr_en = 1;
        ptr->image_acce_param.bw_proc_model_cfg.bw_proc_src_sel = ACCE_BW_MODEL_ID;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_BW_PROC_MODEL_ID;
        ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.model_enable = 1;
        AcceleratorModuleConfig(ACCE_BW_PROC_MODEL_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_BW_MODEL_ID);
        m_First = 1;
    }
}
void BinLimitDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void BinLimitDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg = m_bw_cfg;
            AcceleratorModuleConfig(ACCE_BW_MODEL_ID,m_step);
        }

        QDialog::reject();
    }

}

void BinLimitDlg::on_checkBoxBinaryzationReverse_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        if(ui->checkBoxBinaryzationReverse->isChecked())
        {
            ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_inv_en = 1;
            AcceleratorModuleConfig(ACCE_BW_MODEL_ID,m_step);
        }else
        {
            ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_inv_en = 0;
            AcceleratorModuleConfig(ACCE_BW_MODEL_ID,m_step);
        }
    }
}
void BinLimitDlg::SubUpBin(int value)
{
    int imin = ui->horizontalSliderUpBin->minimum();
    int iBin = ui->horizontalSliderUpBin->value()-value;
    if(iBin < imin)
        return;
    if(iBin < ui->horizontalSliderDownBin->value())
    {
        int ivalue;
        ivalue = ui->horizontalSliderDownBin->value()+1;
        ui->txtUpBin->setText(QString::number(ivalue));
        ui->horizontalSliderUpBin->setValue(ivalue);

    }else
    {
        ui->txtUpBin->setText(QString::number(iBin));
        ui->horizontalSliderUpBin->setValue(iBin);
    }
}
void BinLimitDlg::AddUpbBin(int value)
{
    int imax = ui->horizontalSliderUpBin->maximum();
    int iBin = ui->horizontalSliderUpBin->value()+value;
    if(iBin > imax)
        return;
    ui->txtUpBin->setText(QString::number(iBin));
    ui->horizontalSliderUpBin->setValue(iBin);
}
void BinLimitDlg::SubDownBin(int value)
{
    int imin = ui->horizontalSliderDownBin->minimum();
    int iBin = ui->horizontalSliderDownBin->value()-value;

    if(iBin < imin)
        return;
    ui->txtDownBin->setText(QString::number(iBin));
    ui->horizontalSliderDownBin->setValue(iBin);
}
void BinLimitDlg::AddDownBin(int value)
{
    int imax = ui->horizontalSliderDownBin->maximum();
    int iBin = ui->horizontalSliderDownBin->value()+value;

    if(imax < iBin)
        return;
    if(iBin > ui->horizontalSliderUpBin->value())
    {
        int ivalue = ui->horizontalSliderUpBin->value()-1;
        ui->txtDownBin->setText(QString::number(ivalue));
        ui->horizontalSliderDownBin->setValue(ivalue);
    }else
    {
        ui->txtDownBin->setText(QString::number(iBin));
        ui->horizontalSliderDownBin->setValue(iBin);
    }
}
void BinLimitDlg::on_btnUpSubBinaryzation_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::SubUpBin);
    UtilitiesFun::Instance()->StartTimer(100);
}

void BinLimitDlg::on_btnUpSubBinaryzation_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::SubUpBin);
    SubUpBin();
}

void BinLimitDlg::on_btnAddUpBinaryzation_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::AddUpbBin);
    UtilitiesFun::Instance()->StartTimer(100);
}

void BinLimitDlg::on_btnAddUpBinaryzation_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::AddUpbBin);
    AddUpbBin();
}

void BinLimitDlg::on_horizontalSliderUpBin_valueChanged(int value)
{
    if(m_First==1)
    {
        int ivalue;
        ivalue = value;
        if(value < ui->horizontalSliderDownBin->value())
        {
            ivalue = ui->horizontalSliderDownBin->value()+1;
            ui->horizontalSliderUpBin->setValue(ivalue);
            ui->txtUpBin->setText(QString::number(ivalue));
        }else
        {
            ui->txtUpBin->setText(QString::number(ivalue));
        }

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_th_high = ivalue;
            AcceleratorModuleConfig(ACCE_BW_MODEL_ID,m_step);
        }
    }
}

void BinLimitDlg::on_btnSupDownBinaryzation_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::SubDownBin);
    UtilitiesFun::Instance()->StartTimer(100);
}

void BinLimitDlg::on_btnSupDownBinaryzation_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::SubDownBin);
    SubDownBin();
}

void BinLimitDlg::on_btnAddDownBinaryzation_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::AddDownBin);
    UtilitiesFun::Instance()->StartTimer(100);
}

void BinLimitDlg::on_btnAddDownBinaryzation_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&BinLimitDlg::AddDownBin);
    AddDownBin();
}

void BinLimitDlg::on_horizontalSliderDownBin_valueChanged(int value)
{
    if(m_First == 1)
    {
        int iValue;
        iValue = value;

        if(value > ui->horizontalSliderUpBin->value())
        {
            iValue = ui->horizontalSliderUpBin->value() -1;
            ui->txtDownBin->setText(QString::number(iValue));
            ui->horizontalSliderDownBin->setValue(iValue);
        }else
        {
            ui->txtDownBin->setText(QString::number(value));
        }
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_th_low = iValue;
            AcceleratorModuleConfig(ACCE_BW_MODEL_ID,m_step);
        }
    }
}

void BinLimitDlg::on_btnAuto_clicked()
{
    m_First = 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    BW_Model_Auto_TH_Trigger(m_step);

    if(ptr != NULL)
    {
        unsigned int ivalue;
        ivalue = ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_th_low;

        ui->horizontalSliderDownBin->setValue(ivalue);
        ui->txtDownBin->setText(QString::number(ivalue));
        ivalue = ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.bw_th_high;

        ui->horizontalSliderUpBin->setValue(ivalue);
        ui->txtUpBin->setText(QString::number(ivalue));
    }
    m_First = 1;
}
