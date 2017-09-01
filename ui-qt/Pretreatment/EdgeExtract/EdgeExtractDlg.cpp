#include <qdebug.h>
#include "EdgeExtractDlg.h"
#include "ui_EdgeExtractDlg.h"
#include <QMessageBox>
#include <QKeyEvent>
#include "AcceCommon.h"
//#include "System.h"
#include "../../Global/UtilitiesFun.h"
EdgeExtractDlg::EdgeExtractDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdgeExtractDlg)
{
    ui->setupUi(this);
    //qApp->installEventFilter(this);
    m_auto_repeat_count = 0;
    m_self_inc = 1;

    ui->groupBoxLimit->setLayoutDirection(Qt::LeftToRight);
    ui->groupBoxScale->setLayoutDirection(Qt::LeftToRight);
    ui->groupBoxDirection->setLayoutDirection(Qt::LeftToRight);
    ui->subPixelEnableCheckBox->setLayoutDirection(Qt::LeftToRight);

    ui->highLimitSilder->setRange(0,2000);
    ui->lowLimitSlider->setRange(0,2000);
}

EdgeExtractDlg::~EdgeExtractDlg()
{
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    CheckedTypeSignals("");
    //qApp->removeEventFilter(this);
    delete ui;
}
void EdgeExtractDlg::InitData()
{
    this->m_ifirst = 0;

    SIDE_SELECT_MODEL_CFG cfg;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        cfg = ptr->image_acce_param.side_sel_model_cfg;
        m_cfg = cfg;
        ui->xRadioBtn->setEnabled(true);
        ui->yRadioBtn->setEnabled(true);
        if(cfg.kernel_type == 0)
        {
            ui->sobelRadioBtn->setChecked(true);
            CheckedTypeSignals("sobel:更明显地抽取X与Y方向的边缘，进行合成处理");
        }
        else if (cfg.kernel_type == 1)
        {
            ui->prewittRadioBtn->setChecked(true);
            CheckedTypeSignals("prewitt:抽取X与Y方向的边缘，进行合成处理");
        }
        else if (cfg.kernel_type == 2)
        {
            ui->laplacianRadioBtn->setChecked(true);
            CheckedTypeSignals("laplacian:仅计算边缘的强度，不分方向均匀的抽取边缘");
            ui->xRadioBtn->setEnabled(false);
            ui->yRadioBtn->setEnabled(false);
        }
        else if (cfg.kernel_type == 3)
        {
            ui->robertsRadioBtn->setChecked(true);
            CheckedTypeSignals("roberts:抽取X与Y方向的边缘能力较弱，适用于抽取倾斜方向的边缘");
            ui->xRadioBtn->setEnabled(false);
            ui->yRadioBtn->setEnabled(false);
        }

        if (cfg.scan_dir == 0)
        {
            ui->xyRadioBtn->setChecked(true);
        }
        else if (cfg.scan_dir == 1)
        {
            ui->xRadioBtn->setChecked(true);
        }
        else if (cfg.scan_dir == 2)
        {
            ui->yRadioBtn->setChecked(true);
        }

        if (cfg.sub_pixel_en == 0)
        {
            ui->subPixelEnableCheckBox->setChecked(false);
        }
        else if (cfg.sub_pixel_en == 1)
        {
            ui->subPixelEnableCheckBox->setChecked(true);
        }

        ui->highLimitValueLabel->setText(QString::number(cfg.amplitude_high_th, 'f', 2));
        ui->lowLimitValueLabel->setText(QString::number(cfg.amplitude_low_th, 'f', 2));

        int sliderValue = (int)(cfg.amplitude_high_th * 20);
        ui->highLimitSilder->setValue(sliderValue);
        sliderValue = (int)(cfg.amplitude_low_th * 20);
        ui->lowLimitSlider->setValue(sliderValue);

        if(ptr->image_acce_param.side_sel_model_cfg.side_mode_sel == 0)
        {
            ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ptr->image_acce_param.side_sel_model_cfg.side_sel_src_sel;
            ui->RadioBtnPoint->setChecked(true);
            ui->RadioBtnPic->setChecked(false);
        }else
        {
            ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_EDGE_EXTRACT_MODLE_ID;
            ui->RadioBtnPoint->setChecked(false);
            ui->RadioBtnPic->setChecked(true);
        }

        /*if( m_task_id == TASK_ID_MATCH_LINE)
        {
            ui->laplacianRadioBtn->setEnabled(false);
            ui->robertsRadioBtn->setEnabled(false);
        }
        else if(m_task_id == TASK_ID_MATCH_CIRCLE)
        {
            ui->laplacianRadioBtn->setEnabled(false);
            ui->robertsRadioBtn->setEnabled(false);
        } */
        //ptr->image_acce_param.side_sel_model_cfg.side_sel_src_sel= ACCE_EDGE_EXTRACT_MODLE_ID;
        //ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ptr->image_acce_param.side_sel_model_cfg.side_sel_src_sel;
        AcceleratorModuleConfig(ACCE_EDGE_EXTRACT_MODLE_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_EDGE_EXTRACT_MODLE_ID);
    }
    this->m_ifirst = 1;
}
void EdgeExtractDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void EdgeExtractDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_EDGE_EXTRACT_MODLE_ID,m_step);
        }

        QDialog::reject();
    }

}

void EdgeExtractDlg::SetPreproccessData()
{
    AcceleratorModuleConfig(ACCE_EDGE_EXTRACT_MODLE_ID,m_step);
    //SignalEdgeCfgPoints(1,QString::null);
}

void EdgeExtractDlg::HighLimitDecBtnKeepPressProc(int speed)
{
    int curValue = ui->highLimitSilder->value();
    int cmpValue = ui->lowLimitSlider->value();

    if (curValue > cmpValue)
    {
        curValue -= speed;
        if (curValue < cmpValue)
        {
            curValue = cmpValue;
        }
        float tmpValue = (float)curValue / 20.0;
        ui->highLimitValueLabel->setText(QString::number(tmpValue, 'f', 2));
        ui->highLimitSilder->setValue(curValue);

        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th = ui->highLimitValueLabel->text().toFloat();
            ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th = ui->lowLimitValueLabel->text().toFloat();
            qDebug()<<"ui->highLimitValueLabel->text().toFloat()==="<<ui->highLimitValueLabel->text().toFloat();
            qDebug()<<"ui->lowLimitValueLabel->text().toFloat()=="<<ui->lowLimitValueLabel->text().toFloat();
            SetPreproccessData();
        }

    }
}

void EdgeExtractDlg::HighLimitIncBtnKeepPressProc(int speed)
{
    int curValue = ui->highLimitSilder->value();
//    int cmpValue = ui->lowLimitSlider->value();

    if (curValue < 2000)
    {
        curValue += speed;
        if (curValue > 2000)
        {
            curValue = 2000;
        }
        float tmpValue = (float)curValue / 20.0;
        ui->highLimitValueLabel->setText(QString::number(tmpValue, 'f', 2));
        ui->highLimitSilder->setValue(curValue);
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th = ui->highLimitValueLabel->text().toFloat();
            ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th = ui->lowLimitValueLabel->text().toFloat();
            qDebug()<<"ui->highLimitValueLabel->text().toFloat()==="<<ui->highLimitValueLabel->text().toFloat();
            qDebug()<<"ui->lowLimitValueLabel->text().toFloat()=="<<ui->lowLimitValueLabel->text().toFloat();
            SetPreproccessData();
        }
    }
}

void EdgeExtractDlg::LowLimitDecBtnKeepPressProc(int speed)
{
    int curValue = ui->lowLimitSlider->value();
//    int cmpValue = ui->highLimitSilder->value();

    if (curValue > 0)
    {
        curValue -= speed;
        if (curValue < 0)
        {
            curValue = 0;
        }
        float tmpValue = (float)curValue / 20.0;
        ui->lowLimitValueLabel->setText(QString::number(tmpValue, 'f', 2));
        ui->lowLimitSlider->setValue(curValue);
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th = ui->highLimitValueLabel->text().toFloat();
            ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th = ui->lowLimitValueLabel->text().toFloat();
            qDebug()<<"ui->highLimitValueLabel->text().toFloat()==="<<ui->highLimitValueLabel->text().toFloat();
            qDebug()<<"ui->lowLimitValueLabel->text().toFloat()=="<<ui->lowLimitValueLabel->text().toFloat();
            SetPreproccessData();
        }
    }
}

void EdgeExtractDlg::LowLimitIncBtnKeepPressProc(int speed)
{
    int curValue = ui->lowLimitSlider->value();
    int cmpValue = ui->highLimitSilder->value();

    if (curValue < cmpValue)
    {
        curValue += speed;
        if (curValue > cmpValue)
        {
            curValue = cmpValue;
        }
        float tmpValue = (float)curValue / 20.0;
        ui->lowLimitValueLabel->setText(QString::number(tmpValue, 'f', 2));
        ui->lowLimitSlider->setValue(curValue);
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th = ui->highLimitValueLabel->text().toFloat();
            ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th = ui->lowLimitValueLabel->text().toFloat();
            qDebug()<<"ui->highLimitValueLabel->text().toFloat()==="<<ui->highLimitValueLabel->text().toFloat();
            qDebug()<<"ui->lowLimitValueLabel->text().toFloat()=="<<ui->lowLimitValueLabel->text().toFloat();
            SetPreproccessData();
        }
    }
}

void EdgeExtractDlg::SeleIncValuePro()
{
    if (m_self_inc < 20)
    {
        ++ m_auto_repeat_count;
        m_self_inc += m_auto_repeat_count / 10;
    }
    else
    {
        m_self_inc = 20;
    }
}

void EdgeExtractDlg::on_sobelRadioBtn_clicked()
{
    if(ui->sobelRadioBtn->isChecked())
    {
        CheckedTypeSignals("sobel:更明显地抽取X与Y方向的边缘，进行合成处理");
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.kernel_type = 0;
            SetPreproccessData();
        }
        ui->xRadioBtn->setEnabled(true);
        ui->yRadioBtn->setEnabled(true);
    }
}

void EdgeExtractDlg::on_prewittRadioBtn_clicked()
{
    if(ui->prewittRadioBtn->isChecked())
    {
        CheckedTypeSignals("prewitt:抽取X与Y方向的边缘，进行合成处理");
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.kernel_type = 1;
            SetPreproccessData();
        }
        ui->xRadioBtn->setEnabled(true);
        ui->yRadioBtn->setEnabled(true);
    }
}

void EdgeExtractDlg::on_laplacianRadioBtn_clicked()
{
    if(ui->laplacianRadioBtn->isChecked())
    {
        CheckedTypeSignals("laplacian:仅计算边缘的强度，不分方向均匀的抽取边缘");
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.kernel_type = 2;
            SetPreproccessData();
        }

        on_xyRadioBtn_clicked();
        ui->xRadioBtn->setEnabled(false);
        ui->yRadioBtn->setEnabled(false);
    }
}

void EdgeExtractDlg::on_robertsRadioBtn_clicked()
{
    if(ui->robertsRadioBtn->isChecked())
    {
        CheckedTypeSignals("roberts:抽取X与Y方向的边缘能力较弱，适用于抽取倾斜方向的边缘");
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.kernel_type = 3;
            SetPreproccessData();
        }

        on_xyRadioBtn_clicked();
        ui->xRadioBtn->setEnabled(false);
        ui->yRadioBtn->setEnabled(false);
    }
}

void EdgeExtractDlg::on_xyRadioBtn_clicked()
{
    if(ui->xyRadioBtn->isChecked())
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.scan_dir = 0;
            SetPreproccessData();
        }
    }
}

void EdgeExtractDlg::on_xRadioBtn_clicked()
{
    if(ui->xRadioBtn->isChecked())
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.scan_dir = 1;
            SetPreproccessData();
        }
    }
}

void EdgeExtractDlg::on_yRadioBtn_clicked()
{
    if(ui->yRadioBtn->isChecked())
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.scan_dir = 2;
            SetPreproccessData();
        }
    }
}

void EdgeExtractDlg::on_subPixelEnableCheckBox_clicked()
{
    if(ui->subPixelEnableCheckBox->isChecked())
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.sub_pixel_en = 1;
            SetPreproccessData();
        }
    }
    else
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.side_sel_model_cfg.sub_pixel_en = 0;
            SetPreproccessData();
        }
    }
}
void EdgeExtractDlg::on_highLimitSilder_sliderReleased()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        int curValue = ui->highLimitSilder->value();
        int cmpValue = (int)(ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th * 20);

        if (curValue < cmpValue)
        {
            curValue = cmpValue;
            ui->highLimitSilder->setValue(curValue);
        }

        ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th = (float)curValue / 20.0;
        ui->highLimitValueLabel->setText(QString::number(ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th, 'f', 2));

        SetPreproccessData();
    }

}

void EdgeExtractDlg::on_lowLimitSlider_sliderReleased()
{

    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        int curValue = ui->lowLimitSlider->value();

        int cmpValue = (int)( ptr->image_acce_param.side_sel_model_cfg.amplitude_high_th * 20);

        if (curValue > cmpValue)
        {
            curValue = cmpValue;
            ui->lowLimitSlider->setValue(curValue);
        }

        ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th = (float)curValue / 20.0;
        ui->lowLimitValueLabel->setText(QString::number(ptr->image_acce_param.side_sel_model_cfg.amplitude_low_th, 'f', 2));
        SetPreproccessData();
    }
}
void EdgeExtractDlg::on_highLimitSilder_sliderMoved(int position)
{
    float tmpValue = (float)position / 20.0;
    ui->highLimitValueLabel->setText(QString::number(tmpValue, 'f', 2));
}

void EdgeExtractDlg::on_lowLimitSlider_sliderMoved(int position)
{
    float tmpValue = (float)position / 20.0;
    ui->lowLimitValueLabel->setText(QString::number(tmpValue, 'f', 2));
}

void EdgeExtractDlg::on_RadioBtnPoint_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.side_sel_model_cfg.side_mode_sel = 0;
        ptr->image_acce_param.side_sel_model_cfg.side_edge_pic_we_en = 0;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ptr->image_acce_param.side_sel_model_cfg.side_sel_src_sel;
        AcceleratorModuleConfig(ACCE_EDGE_EXTRACT_MODLE_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_EDGE_EXTRACT_MODLE_ID);
        SignalSwitchListPoint(1);
    }
}

void EdgeExtractDlg::on_RadioBtnPic_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.side_sel_model_cfg.side_mode_sel = 1;
        ptr->image_acce_param.side_sel_model_cfg.side_edge_pic_we_en = 1;
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_EDGE_EXTRACT_MODLE_ID;
        AcceleratorModuleConfig(ACCE_EDGE_EXTRACT_MODLE_ID,m_step);
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,ACCE_EDGE_EXTRACT_MODLE_ID);
        SignalSwitchListPoint(0);

    }
}

void EdgeExtractDlg::on_highLimitDecBtn_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::HighLimitDecBtnKeepPressProc);
    UtilitiesFun::Instance()->StartTimer(100);
}

void EdgeExtractDlg::on_highLimitDecBtn_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::HighLimitDecBtnKeepPressProc);
    HighLimitDecBtnKeepPressProc(1);
}

void EdgeExtractDlg::on_highLimitIncBtn_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::HighLimitIncBtnKeepPressProc);
    UtilitiesFun::Instance()->StartTimer(100);
}

void EdgeExtractDlg::on_highLimitIncBtn_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::HighLimitIncBtnKeepPressProc);
    HighLimitIncBtnKeepPressProc(1);
}

void EdgeExtractDlg::on_lowLimitDecBtn_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::LowLimitDecBtnKeepPressProc);
    UtilitiesFun::Instance()->StartTimer(100);
}

void EdgeExtractDlg::on_lowLimitDecBtn_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::LowLimitDecBtnKeepPressProc);
    LowLimitDecBtnKeepPressProc(1);
}

void EdgeExtractDlg::on_lowLimitIncBtn_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::LowLimitIncBtnKeepPressProc);
    UtilitiesFun::Instance()->StartTimer(100);
}

void EdgeExtractDlg::on_lowLimitIncBtn_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&EdgeExtractDlg::LowLimitIncBtnKeepPressProc);
    LowLimitIncBtnKeepPressProc(1);
}
