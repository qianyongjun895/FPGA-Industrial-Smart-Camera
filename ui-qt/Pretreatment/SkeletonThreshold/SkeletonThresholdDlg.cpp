#include "SkeletonThresholdDlg.h"
#include "ui_SkeletonThresholdDlg.h"
#include <QMessageBox>
#include "AcceCommon.h"
#include "../../Global/UtilitiesFun.h"
SkeletonThresholdDlg::SkeletonThresholdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkeletonThresholdDlg)
{
    ui->setupUi(this);
    ui->groupBox_3->setVisible(false);
}

SkeletonThresholdDlg::~SkeletonThresholdDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    delete ui;
}
void SkeletonThresholdDlg::InitData()
{
    m_ifirst = 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        m_cfg = ptr->image_acce_param.match_model_cfg;
        /*int value = ptr->image_acce_param.match_model_cfg.match_sobel_th;
        ui->horizontalSliderUpSobel->setValue(value );
        ui->txtUpSobel->setText(QString::number(value));*/
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ptr->image_acce_param.match_model_cfg.match_src_sel;
        //AcceleratorModuleConfig(ACCE_SKE_MATCH_MODLE_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_SKE_MATCH_MODLE_ID);
    }

    m_ifirst =1;

}
void SkeletonThresholdDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void SkeletonThresholdDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.match_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_SKE_MATCH_MODLE_ID,m_step);
        }

        QDialog::reject();
    }

}
void SkeletonThresholdDlg::on_btnUpSubSobel_clicked()
{
    int value = ui->horizontalSliderUpSobel->value();

    if(value > 0)
    {
        ui->horizontalSliderUpSobel->setValue(value-1);
        ui->txtUpSobel->setText(QString::number(value-1));
    }
}

void SkeletonThresholdDlg::on_btnAddSobel_clicked()
{
    int value = ui->horizontalSliderUpSobel->value();

    if(value < 100)
    {
        ui->horizontalSliderUpSobel->setValue(value+1);
        ui->txtUpSobel->setText(QString::number(value+1));
    }
}
void SkeletonThresholdDlg::SetSobelDataToLib()
{
    /*unsigned int sobel_para = 0;
    sobel_para = ui->horizontalSliderUpSobel->value();

    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.match_model_cfg.match_sobel_th = sobel_para;
        AcceleratorModuleConfig(ACCE_SKE_MATCH_MODLE_ID,m_step);
    }*/

}
void SkeletonThresholdDlg::on_horizontalSliderUpSobel_sliderPressed()
{
    startTime = QTime::currentTime();
}

void SkeletonThresholdDlg::on_horizontalSliderUpSobel_sliderReleased()
{
    SetSobelDataToLib();
}
void SkeletonThresholdDlg::on_horizontalSliderUpSobel_valueChanged(int value)
{
    if(m_ifirst !=0)
    {
        ui->txtUpSobel->setText(QString::number(value));

        if(IsTimeOut() == 1)
        {
            SetSobelDataToLib();
        }
    }
}
int SkeletonThresholdDlg::IsTimeOut()
{
    int bFlag = 0;
    stopTime = QTime::currentTime();
    int elapsed = startTime.msecsTo(stopTime);
    if(elapsed>1000)
    {
        startTime = stopTime;
        bFlag = 1;
    }
    return bFlag;
}
