#include <qdebug.h>
#include "ColorSelectDialog.h"
#include "ui_ColorSelectDialog.h"
#include <QMessageBox>
#include "CGetImageThread.h"
#define PI 3.1415926
#include <math.h>
#include <stdio.h>
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"

ColorSelectDialog::ColorSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorSelectDialog)
{
    ui->setupUi(this);

    timerUpData = new QTimer(this);
    ui->checkBoxSetMultiple->setChecked(true);

    for (int i=0; i<8;i++)
        InirgbLimt(&rgbLimt[i]);

    this->m_Imag = QImage(640,480,QImage::Format_RGB888);
    m_ColorExtractDeal.m_Imag = &m_Imag;
    connect(ui->LabColorSelect,&LabelHSIPicAdjust::SignalHS,this,&ColorSelectDialog::SlotHS);
    connect(ui->labColorResult,&LabelHeightAdjust::SignalI,this,&ColorSelectDialog::SlotI);
    connect(ui->labPic,&LabelRGBPicSelect::SignalsRect,this,&ColorSelectDialog::SlotRGBRect);
    IniHSI();
    m_i_copy_image = 0;
    ui->checkBoxAutoSet->setChecked(true);
    connect(CGetImageThread::Instance(),&CGetImageThread::SignalPic,this,&ColorSelectDialog::updatImage);


}
void ColorSelectDialog::IniCheckBoxEnable(int index)
{
    if(index == 0)
    {
        ui->checkBoxColor0->setChecked(true);
    }else if(index ==1)
    {
        ui->checkBoxColor1->setChecked(true);
    }else if(index ==2)
    {
        ui->checkBoxColor2->setChecked(true);
    }else if(index ==3)
    {
        ui->checkBoxColor3->setChecked(true);
    }else if(index ==4)
    {
        ui->checkBoxColor4->setChecked(true);
    }else if(index ==5)
    {
        ui->checkBoxColor5->setChecked(true);
    }else if(index ==6)
    {
        ui->checkBoxColor6->setChecked(true);
    }else if(index ==7)
    {
        ui->checkBoxColor7->setChecked(true);
    }
}
void ColorSelectDialog::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr == NULL)
    {
        return ;
    }

    COLOR_DRAW_MODEL_CFG cfg;
    cfg = ptr->image_acce_param.color_draw_model_cfg;
    m_cfg = cfg;
    m_ini_data = 0;
    if(cfg.all_rev ==1)
        ui->checkBoxColorReverse->setChecked(true);
    else
        ui->checkBoxColorReverse->setChecked(false);

    unsigned char zoneRev = cfg.zone_rev;
    unsigned char zone_sel = cfg.zone_sel;

    RGBLIMITUNION rgbUnion;
    int i;
    for( i = 0; i<8;i++)
    {
        if(GetBitEnable(i,(int)zoneRev))
        {
            rgbLimt[i].bFlagColorExcept = true;
        }else
        {
            rgbLimt[i].bFlagColorExcept = false;
        }
        if(GetBitEnable(i,(int)zone_sel))
        {
            ui->checkBoxSetMultiple->setChecked(true);
            rgbLimt[i].flag = true;
            IniCheckBoxEnable(i);

        }else
        {
            rgbLimt[i].flag = false;
        }

        rgbUnion.value = cfg.red_th[i];
        rgbLimt[i].m_r_min = rgbUnion.buf[0];
        rgbLimt[i].m_r_max = rgbUnion.buf[1];
        rgbUnion.value = cfg.green_th[i];
        rgbLimt[i].m_g_min = rgbUnion.buf[0];
        rgbLimt[i].m_g_max = rgbUnion.buf[1];
        rgbUnion.value = cfg.blue_th[i];
        rgbLimt[i].m_b_min = rgbUnion.buf[0];
        rgbLimt[i].m_b_max = rgbUnion.buf[1];

        rgbLimt[i].m_h_max = cfg.hue_th_high[i];
        if(rgbLimt[i].m_h_max<=0)
            rgbLimt[i].m_h_max = 360;
        rgbLimt[i].m_h_min = cfg.hue_th_low[i];
        if(rgbLimt[i].m_h_min<=0)
            rgbLimt[i].m_h_min = 0;
        rgbLimt[i].m_s_max = cfg.saturation_th_high[i];
        if(rgbLimt[i].m_s_max<=0)
            rgbLimt[i].m_s_max = 100;
        rgbLimt[i].m_s_min = cfg.saturation_th_low[i];
        if(rgbLimt[i].m_s_min<= 0)
            rgbLimt[i].m_s_min = 0;
        rgbLimt[i].m_i_max = cfg.intensity_th_high[i];
        if(rgbLimt[i].m_i_max<=0)
            rgbLimt[i].m_i_max =255;
        rgbLimt[i].m_i_min = cfg.intensity_th_low[i];
        if(rgbLimt[i].m_i_min<=0)
            rgbLimt[i].m_i_min=0;
        if( rgbLimt[i].flag)
        {
            rgbLimt[i].m_r_Average = (rgbLimt[i].m_r_min+rgbLimt[i].m_r_max)/2;
            rgbLimt[i].m_g_Average = (rgbLimt[i].m_g_min+rgbLimt[i].m_g_max)/2;
            rgbLimt[i].m_b_Average = (rgbLimt[i].m_b_min+rgbLimt[i].m_b_max)/2;
        }

    }
    ui->radioButtonColor0->setChecked(true);
    ui->checkBoxColor0->setChecked(true);
    rgbLimt[0].flag = true;

    SetControlValueByColor(&rgbLimt[0]);

    if(cfg.rgb_bck ==0x000000000)
    {
        ui->comboBoxBackGroundColor->setCurrentIndex(0);
    }else if(cfg.rgb_bck ==0x00ffffff)
    {
        ui->comboBoxBackGroundColor->setCurrentIndex(1);
    }else if(cfg.rgb_bck == 0x00ff0000)
    {
        ui->comboBoxBackGroundColor->setCurrentIndex(2);
    }else if(cfg.rgb_bck == 0x0000ff00)
    {
        ui->comboBoxBackGroundColor->setCurrentIndex(3);
    }else if(cfg.rgb_bck == 0x000000ff)
    {
        ui->comboBoxBackGroundColor->setCurrentIndex(4);
    }else
    {
        ui->comboBoxBackGroundColor->setCurrentIndex(0);
    }
    ptr->image_acce_param.color_draw_model_cfg.result_wr_ddr_en =1;
    ptr->image_acce_param.color_draw_model_cfg.model_enable =1;
    ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_CPT_MODEL_ID;
    AcceleratorModuleConfig(ACCE_COLOR_EXTRACT_MODLE_ID,m_step);
    AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
    UtilitiesFun::Instance()->ListVGA(ui->labPic->x(),ui->labPic->y(),ACCE_CPT_MODEL_ID);
    m_ini_data= 1;
    CGetImageThread::Instance()->GetSingleImag();
}
ColorSelectDialog::~ColorSelectDialog()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        ptr->image_acce_param.color_draw_model_cfg.result_wr_ddr_en =0;
        AcceleratorModuleConfig(ACCE_COLOR_EXTRACT_MODLE_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(ui->labPic->x(),ui->labPic->y(),0xffffffff);
    }

    disconnect(this,0,0,0);
    delete timerUpData;
    delete ui;
}

void ColorSelectDialog::on_btnOk_clicked()
{
    SetDataToMonkeyLib();
    QDialog::accept();
}

void ColorSelectDialog::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.color_draw_model_cfg = m_cfg;
        }

        QDialog::reject();
    }

}
void ColorSelectDialog::SlotHS(int hMax,int hMin,int sMax,int sMin)
{
    int hMaxValue;
    int hMinValue;
    int sMaxValue;
    int sMinValue;

    hMaxValue = hMax*2;
    hMinValue = hMin*2;

    if(hMaxValue > 360)
        hMaxValue = 360;
    if(hMinValue > 360)
        hMinValue = 360;

    sMaxValue = 100 - sMin;
    if(sMaxValue > 100)
        sMaxValue =100;
    sMinValue = 100-sMax;
    if(sMinValue > 100)
        sMaxValue = 100;

    ui->txtHMax->setText(QString::number(hMaxValue));
    ui->txtHMin->setText(QString::number(hMinValue));
    ui->txtSMax->setText(QString::number(sMaxValue));
    ui->txtSMin->setText(QString::number(sMinValue));
    int HMax = ui->txtHMax->text().toInt();
    int HMin = ui->txtHMin->text().toInt();
    int SMax = ui->txtSMax->text().toInt();
    int SMin = ui->txtSMin->text().toInt();
    int IMax = ui->txtIMax->text().toInt();
    int IMin = ui->txtIMin->text().toInt();

    m_ColorExtractDeal.FindHSIPicFlag(HMax,HMin,SMax,SMin,IMax,IMin);

    m_ColorExtractDeal.SetImgByHSI();//(ui->labPic,rgbLimt);
    SetRgbLimt();
    UpdateIColor();
    SetDataToMonkeyLib();
}
void ColorSelectDialog::SlotI(int iMax,int iMin)
{
    int iMaxValue = 256-iMin*2;

    if(iMaxValue > 255)
        iMaxValue = 255;

    int iMinValue = 256 -iMax*2;

    if(iMinValue > 255)
        iMinValue = iMax*2;

    ui->txtIMax->setText(QString::number(iMaxValue));
    ui->txtIMin->setText(QString::number(iMinValue));
    int HMax = ui->txtHMax->text().toInt();
    int HMin = ui->txtHMin->text().toInt();
    int SMax = ui->txtSMax->text().toInt();
    int SMin = ui->txtSMin->text().toInt();
    int IMax = ui->txtIMax->text().toInt();
    int IMin = ui->txtIMin->text().toInt();
    m_ColorExtractDeal.FindHSIPicFlag(HMax,HMin,SMax,SMin,IMax,IMin);
    m_ColorExtractDeal.SetImgByHSI();//(ui->labPic,rgbLimt);
    SetRgbLimt();
    UpdateIColor();
    SetDataToMonkeyLib();
}
void ColorSelectDialog::SlotRGBRect()
{
    QRect rect = ui->labPic->GetRect();
    m_ColorExtractDeal.RGBPicToHSI(rect);

    ui->LabColorSelect->SetHSs(m_ColorExtractDeal.m_H,m_ColorExtractDeal.m_S);
    ui->labColorResult->SetVtPic(m_ColorExtractDeal.m_I);
    if(ui->checkBoxAutoSet->isChecked())
    {
        ui->txtHMax->setText(QString::number(m_ColorExtractDeal.hMax));
        ui->txtHMin->setText(QString::number(m_ColorExtractDeal.hMin));
        ui->txtSMax->setText(QString::number(m_ColorExtractDeal.sMax));
        ui->txtSMin->setText(QString::number(m_ColorExtractDeal.sMin));
        ui->txtIMax->setText(QString::number(m_ColorExtractDeal.iMax));
        ui->txtIMin->setText(QString::number(m_ColorExtractDeal.iMin));

        m_ColorExtractDeal.hMax = m_ColorExtractDeal.hMax/2 +10+5;
        m_ColorExtractDeal.hMin = m_ColorExtractDeal.hMin/2 +10;
        int SMaxValue = 100 -m_ColorExtractDeal.sMin+10;
        int SminValue = 100-m_ColorExtractDeal.sMax +10;
        int iMaxValue = (256-m_ColorExtractDeal.iMin)/2+10;
        int iMinValue = (256-m_ColorExtractDeal.iMax)/2+10;

        ui->LabColorSelect->SetHS(m_ColorExtractDeal.hMax,SMaxValue,m_ColorExtractDeal.hMin,SminValue);
        ui->labColorResult->SetLowHighYValue(iMinValue,iMaxValue);
        ui->labColorResult->SetRGB(m_ColorExtractDeal.m_r_Average,m_ColorExtractDeal.m_g_Average,m_ColorExtractDeal.m_b_Average);

        int HMax = ui->txtHMax->text().toInt();
        int HMin = ui->txtHMin->text().toInt();
        int SMax = ui->txtSMax->text().toInt();
        int SMin = ui->txtSMin->text().toInt();
        int IMax = ui->txtIMax->text().toInt();
        int IMin = ui->txtIMin->text().toInt();
        m_ColorExtractDeal.FindHSIPicFlag(HMax,HMin,SMax,SMin,IMax,IMin);
        m_ColorExtractDeal.SetImgByHSI();//(ui->labPic,rgbLimt);
        SetRgbLimt();
        UpdateIColor();
        SetDataToMonkeyLib();
    }
}
void ColorSelectDialog::UpdateIColor()
{
    int R,G,B;
    int H,S,I;
    if(ui->txtHMax->text().toInt() >= ui->txtHMin->text().toInt())
    {
        H = (ui->txtHMax->text().toInt()+ui->txtHMin->text().toInt())/2;
    }
    else
    {
        H = (ui->txtHMax->text().toInt()+360-ui->txtHMin->text().toInt())/2+ui->txtHMin->text().toInt();
        if(H > 360)
            H= H-360;
    }
    S = (ui->txtSMax->text().toInt()+ui->txtSMin->text().toInt())/2;
    I = (ui->txtIMax->text().toInt()+ui->txtIMin->text().toInt())/2;
    m_ColorExtractDeal.HSIToRgb(H,S,I,&R,&G,&B);
    ui->labColorResult->SetRGB(R,G,B);
    int index = 0;
    if(ui->radioButtonColor0->isChecked())
        index = 0;
    else if(ui->radioButtonColor1->isChecked())
        index = 1;
    else if(ui->radioButtonColor2->isChecked())
        index = 2;
    else if(ui->radioButtonColor3->isChecked())
        index = 3;
    else if(ui->radioButtonColor4->isChecked())
        index = 4;
    else if(ui->radioButtonColor5->isChecked())
        index = 5;
    else if(ui->radioButtonColor6->isChecked())
        index = 6;
    else if(ui->radioButtonColor7->isChecked())
        index = 7;
    rgbLimt[index].m_r_Average = R;
    rgbLimt[index].m_g_Average = G;
    rgbLimt[index].m_b_Average = B;
    SetLabelsColor();
}
void ColorSelectDialog::IniHSI()
{
    ui->txtHMax->setText(tr("300"));
    ui->txtHMin->setText(tr("100"));
    ui->txtSMax->setText(tr("80"));
    ui->txtSMin->setText(tr("50"));
    ui->txtIMax->setText(tr("200"));
    ui->txtIMin->setText(tr("60"));
    int H = (100+300)/2;
    int S = (50+80)/2;
    int I = (60+200)/2;
    int R,G,B;
    m_ColorExtractDeal.HSIToRgb(H,S,I,&R,&G,&B);
    ui->labColorResult->SetRGB(R,G,B);
    SetLabelsColor();
}
void ColorSelectDialog::ListImageBySelect()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
    {
     return ;
    }
    int index = ui->comboBoxImageType->currentIndex();
    if(index == 0) //原图
    {
        CGetImageThread::Instance()->GetSingleImag();
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_CPT_MODEL_ID;
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(ui->labPic->x(),ui->labPic->y(),ACCE_COLOR_EXTRACT_MODLE_ID);
        SetDataToMonkeyLib();
        ui->btnUpdataImage->setEnabled(true);
    }else if(index ==1) //全抽取图像
    {
        ui->labPic->clear();
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_COLOR_EXTRACT_MODLE_ID;
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(ui->labPic->x(),ui->labPic->y(),ACCE_COLOR_EXTRACT_MODLE_ID);
        SetDataToMonkeyLib();
        ui->btnUpdataImage->setEnabled(false);

    }
}
void ColorSelectDialog::SetDataToMonkeyLib()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr == NULL)
    {
        return ;
    }
    ptr->image_acce_param.color_draw_model_cfg.result_wr_ddr_en =1;
    ptr->image_acce_param.color_draw_model_cfg.zone_rev = 0;
    ptr->image_acce_param.color_draw_model_cfg.zone_sel = 0;

    if(ui->checkBoxColorReverse->isChecked())
        ptr->image_acce_param.color_draw_model_cfg.all_rev =1;
    else
        ptr->image_acce_param.color_draw_model_cfg.all_rev = 0;

    int i ;
    unsigned char uEnabel = 0;
    unsigned char uColorExcept = 0;
    RGBLIMITUNION rgbUnion;

    for( i = 0; i<8;i++)
    {
        GetBitValue(i,uEnabel);
        GetBitValue(i,uEnabel);

        if(rgbLimt[i].flag)
        {
            uEnabel = GetBitValue(i,uEnabel);
        }
        if(rgbLimt[i].bFlagColorExcept)
        {
            uColorExcept = GetBitValue(i,uColorExcept);
        }

        rgbUnion.buf[0] = rgbLimt[i].m_r_min;
        rgbUnion.buf[1] = rgbLimt[i].m_r_max;

        ptr->image_acce_param.color_draw_model_cfg.red_th[i] =  rgbUnion.value;
        rgbUnion.buf[0] = rgbLimt[i].m_g_min;
        rgbUnion.buf[1] = rgbLimt[i].m_g_max;

        ptr->image_acce_param.color_draw_model_cfg.green_th[i] =  rgbUnion.value;
        rgbUnion.buf[0] = rgbLimt[i].m_b_min;
        rgbUnion.buf[1] = rgbLimt[i].m_b_max;

        ptr->image_acce_param.color_draw_model_cfg.blue_th[i] =  rgbUnion.value;
        ptr->image_acce_param.color_draw_model_cfg.hue_th_high[i] = rgbLimt[i].m_h_max;
        ptr->image_acce_param.color_draw_model_cfg.hue_th_low[i] = rgbLimt[i].m_h_min;
        ptr->image_acce_param.color_draw_model_cfg.saturation_th_high[i] = rgbLimt[i].m_s_max;
        ptr->image_acce_param.color_draw_model_cfg.saturation_th_low[i]= rgbLimt[i].m_s_min;
        ptr->image_acce_param.color_draw_model_cfg.intensity_th_high[i] = rgbLimt[i].m_i_max;
        ptr->image_acce_param.color_draw_model_cfg.intensity_th_low[i]= rgbLimt[i].m_i_min;

    }
    ptr->image_acce_param.color_draw_model_cfg.rgb_bck= GetBlackColor();
    ptr->image_acce_param.color_draw_model_cfg.zone_rev = uColorExcept;
    ptr->image_acce_param.color_draw_model_cfg.zone_sel = uEnabel;
    AcceleratorModuleConfig(ACCE_COLOR_EXTRACT_MODLE_ID,m_step);

}
int ColorSelectDialog::GetBlackColor()
{
    int ret = 0;
    int index = ui->comboBoxBackGroundColor->currentIndex();
    switch (index) {
    case 0:
        ret = 0;
        break;
    case 1:
        ret = 0x00ffffff;
        break;
    case 2:
        ret = 0x00ff0000;
        break;
    case 3:
        ret = 0x0000ff00;
        break;
    case 4:
        ret = 0x000000ff;
        break;
    default:
        break;
    }
    return ret;
}
unsigned char ColorSelectDialog::GetBitValue(int index,unsigned char value)
{
    unsigned char ret = 0;
    if(index == 0)
    {
        ret = value | 1;

    }else if(index ==1)
    {
        ret = value | (1 << 1);
    }
    else if(index==2)
    {
        ret = value | (1 << 2);
    }else if(index==3)
    {
        ret = value | (1 << 3);
    }else if(index==4)
    {
        ret = value | (1 << 4);
    }else if(index==5)
    {
        ret = value | (1 << 5);
    }else if(index==6)
    {
        ret = value | (1 << 6);
    }else if(index==7)
    {
        ret = value | (1 << 7);
    }
    return ret;

}
int ColorSelectDialog::GetBitEnable(int num,int value)
{
    int ret = 0;

    if(num == 0)
    {
        ret = (value) & 0x1;

    }else if(num ==1)
    {
        ret = (value) & (0x1 << 1);
    }
    else if(num == 2)
    {
        ret = (value) & (0x1 << 2);

    }
    else if(num == 3)
    {
        ret = (value) & (0x1 << 3);
    }
    else if(num == 4)
    {
        ret = (value) & (0x1 << 4);
    }
    else if(num == 5)
    {
        ret = (value) & (0x1 << 5);

    }else if(num == 6)
    {
        ret = (value) & (0x1 << 6);

    }else if(num == 7)
    {
        ret = (value) & (0x1 << 7);

    }else
    {
        ret = 0;
    }
    return ret;
}

void ColorSelectDialog::InirgbLimt(RGB_LIMIT *rgbLimt)
{
    rgbLimt->m_r_max = 255;
    rgbLimt->m_r_min = 0;
    rgbLimt->m_g_max = 255;
    rgbLimt->m_g_min = 0;
    rgbLimt->m_b_max = 255;
    rgbLimt->m_b_min = 0;

    rgbLimt->m_h_max =360;
    rgbLimt->m_h_min = 0;
    rgbLimt->m_s_max =100;
    rgbLimt->m_s_min = 0;
    rgbLimt->m_i_max = 255;
    rgbLimt->m_i_min = 0;
    rgbLimt->flag = false;
    rgbLimt->bFlagColorExcept = false;
}
void ColorSelectDialog::SetRgbLimt()
{
    if(ui->radioButtonColor0->isChecked())
    {
        SetRgbLimt(&rgbLimt[0]);

    }else if(ui->radioButtonColor1->isChecked())
    {
        SetRgbLimt(&rgbLimt[1]);

    }else if(ui->radioButtonColor2->isChecked())
    {
        SetRgbLimt(&rgbLimt[2]);
    }else if(ui->radioButtonColor3->isChecked())
    {
        SetRgbLimt(&rgbLimt[3]);
    }else if(ui->radioButtonColor4->isChecked())
    {
        SetRgbLimt(&rgbLimt[4]);
    }else if(ui->radioButtonColor5->isChecked())
    {
        SetRgbLimt(&rgbLimt[5]);
    }else if(ui->radioButtonColor6->isChecked())
    {
        SetRgbLimt(&rgbLimt[6]);
    }else if(ui->radioButtonColor7->isChecked())
    {
        SetRgbLimt(&rgbLimt[7]);
    }
}
void ColorSelectDialog::SetRgbLimt(RGB_LIMIT *rgbLimt)
{
    int HMax = ui->txtHMax->text().toInt();
    int HMin = ui->txtHMin->text().toInt();
    int SMax = ui->txtSMax->text().toInt();
    int SMin = ui->txtSMin->text().toInt();
    int IMax = ui->txtIMax->text().toInt();
    int IMin = ui->txtIMin->text().toInt();
    bool bExcept = ui->checkBoxExceptColor->isChecked();

    rgbLimt->m_r_max = m_ColorExtractDeal.m_r_max;
    rgbLimt->m_r_min = m_ColorExtractDeal.m_r_min;
    rgbLimt->m_g_max = m_ColorExtractDeal.m_g_max;
    rgbLimt->m_g_min = m_ColorExtractDeal.m_g_min;
    rgbLimt->m_b_max = m_ColorExtractDeal.m_b_max;
    rgbLimt->m_b_min = m_ColorExtractDeal.m_b_min;

    rgbLimt->m_h_max =HMax;
    rgbLimt->m_h_min = HMin;
    rgbLimt->m_s_max =SMax;
    rgbLimt->m_s_min = SMin;
    rgbLimt->m_i_max = IMax;
    rgbLimt->m_i_min = IMin;

    rgbLimt->m_r_Average = m_ColorExtractDeal.m_r_Average;
    rgbLimt->m_g_Average = m_ColorExtractDeal.m_g_Average;
    rgbLimt->m_b_Average = m_ColorExtractDeal.m_b_Average;

    rgbLimt->m_list_r = m_ColorExtractDeal.m_list_r;
    rgbLimt->m_list_g = m_ColorExtractDeal.m_list_g;
    rgbLimt->m_list_b = m_ColorExtractDeal.m_list_b;

    rgbLimt->flag = ui->checkBoxColor0->isChecked();
    rgbLimt->bFlagColorExcept = bExcept;

}
void ColorSelectDialog::SetControlValueByColor(RGB_LIMIT *rgbLimt)
{

    ui->txtHMax->setText(QString::number(rgbLimt->m_h_max));
    ui->txtHMin->setText(QString::number(rgbLimt->m_h_min));
    ui->txtSMax->setText(QString::number(rgbLimt->m_s_max));
    ui->txtSMin->setText(QString::number(rgbLimt->m_s_min));
    ui->txtIMax->setText(QString::number(rgbLimt->m_i_max));
    ui->txtIMin->setText(QString::number(rgbLimt->m_i_min));
    ui->checkBoxExceptColor->setChecked(rgbLimt->bFlagColorExcept);

    int HMax = ui->txtHMax->text().toInt();
    int HMin = ui->txtHMin->text().toInt();
    int SMax = ui->txtSMax->text().toInt();
    int SMin = ui->txtSMin->text().toInt();
    int IMax = ui->txtIMax->text().toInt();
    int IMin = ui->txtIMin->text().toInt();
    HMax = HMax/2 +10+5;
    HMin = HMin/2 +10;
    int SMaxValue = 100 -SMin+10;
    int SminValue = 100-SMax+10;
    int iMaxValue = (256-IMin)/2+10;
    int iMinValue = (256-IMax)/2+10;
    ui->LabColorSelect->SetHS(HMax,SMaxValue,HMin,SMin);
    ui->labColorResult->SetLowHighYValue(iMinValue,iMaxValue);
    UpdateIColor();
}
void ColorSelectDialog::SetLabelColor(int bflag,QLabel *label,int index)
{
    if(bflag)
    {
        /*QPalette palette;
        palette.setColor(QPalette::Background,QColor(rgbLimt[index].m_r_Average,rgbLimt[index].m_g_Average,rgbLimt[index].m_b_Average, 255));
        label->setPalette(palette);
        label->setAutoFillBackground(true);*/
        QString strClolor;
        strClolor = "background:rgb(";
        strClolor += QString::number(rgbLimt[index].m_r_Average);
        strClolor += ",";
        strClolor += QString::number(rgbLimt[index].m_g_Average);
        strClolor += ",";
        strClolor += QString::number(rgbLimt[index].m_b_Average);
        strClolor += ");";
        label->setStyleSheet(strClolor);
        rgbLimt[index].flag = true;
    }else
    {
        //label->setAutoFillBackground(false);
        if(m_ini_data==1)
        {
            QWidget *widget = (QWidget*)(label->parent());
            QPalette pal    = widget->palette();
            QBrush brush = pal.background();
            QColor col      = brush.color();
            int r,g,b,a;
            col.getRgb(&r,&g,&b,&a);
            QString strClolor;
            strClolor = "background:rgb(";
            strClolor += QString::number(r);
            strClolor += ",";
            strClolor += QString::number(g);
            strClolor += ",";
            strClolor += QString::number(b);
            strClolor += ");";
            label->setStyleSheet(strClolor);
        }
        rgbLimt[index].flag = false;
    }
}
void ColorSelectDialog::on_radioButtonColor0_clicked()
{
    SetControlValueByColor(&rgbLimt[0]);
    //ui->checkBoxColor0->setChecked(rgbLimt[0].flag);
    SetDataToMonkeyLib();
}
void ColorSelectDialog::on_radioButtonColor1_clicked()
{
    SetControlValueByColor(&rgbLimt[1]);
    //ui->checkBoxColor1->setChecked(rgbLimt[1].flag);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_radioButtonColor2_clicked()
{
    SetControlValueByColor(&rgbLimt[2]);
    //ui->checkBoxColor2->setChecked(rgbLimt[2].flag);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_radioButtonColor3_clicked()
{
    SetControlValueByColor(&rgbLimt[3]);
    //ui->checkBoxColor3->setChecked(rgbLimt[3].flag);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_radioButtonColor4_clicked()
{
    SetControlValueByColor(&rgbLimt[4]);
    //ui->checkBoxColor4->setChecked(rgbLimt[4].flag);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_radioButtonColor5_clicked()
{
    SetControlValueByColor(&rgbLimt[5]);
    //ui->checkBoxColor5->setChecked(rgbLimt[5].flag);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_radioButtonColor6_clicked()
{
    SetControlValueByColor(&rgbLimt[6]);
    //ui->checkBoxColor6->setChecked(rgbLimt[6].flag);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_radioButtonColor7_clicked()
{
    SetControlValueByColor(&rgbLimt[7]);
    //ui->checkBoxColor7->setChecked(rgbLimt[7].flag);
    SetDataToMonkeyLib();
}
void ColorSelectDialog::on_checkBoxColor0_clicked()
{
    SetLabelColor(ui->checkBoxColor0->isChecked(),ui->labelColor0,0);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor1_clicked()
{
    SetLabelColor(ui->checkBoxColor1->isChecked(),ui->labelColor1,1);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor2_clicked()
{
    SetLabelColor(ui->checkBoxColor2->isChecked(),ui->labelColor2,2);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor3_clicked()
{
    SetLabelColor(ui->checkBoxColor3->isChecked(),ui->labelColor3,3);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor4_clicked()
{
    SetLabelColor(ui->checkBoxColor4->isChecked(),ui->labelColor4,4);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor5_clicked()
{
    SetLabelColor(ui->checkBoxColor5->isChecked(),ui->labelColor5,5);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor6_clicked()
{
    SetLabelColor(ui->checkBoxColor6->isChecked(),ui->labelColor6,6);
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColor7_clicked()
{
    SetLabelColor(ui->checkBoxColor7->isChecked(),ui->labelColor7,7);
    SetDataToMonkeyLib();
}
void ColorSelectDialog::on_comboBoxBackGroundColor_currentIndexChanged(int index)
{
    SetDataToMonkeyLib();
}
void ColorSelectDialog::on_checkBoxSetMultiple_clicked()
{
    ui->checkBoxExceptColor->setChecked(false);
    ui->checkBoxColor0->setChecked(true);
    ui->radioButtonColor0->setChecked(true);
    SetRgbLimt();
    SetDataToMonkeyLib();
}
void ColorSelectDialog::on_comboBoxImageType_currentIndexChanged(int index)
{
    ListImageBySelect();
    //SetDataToMonkeyLib();
}
void ColorSelectDialog::updatImage(QPixmap pix)
{
    ui->labPic->setPixmap(pix);
    this->m_Imag = CGetImageThread::Instance()->GetImage();
    m_ColorExtractDeal.m_Imag = &m_Imag;
    m_ColorExtractDeal.RGBToHSIPic();
}

void ColorSelectDialog::on_btnClear_clicked()
{

    if(ui->radioButtonColor0->isChecked())
    {
        InirgbLimt(&rgbLimt[0]);
        SetControlValueByColor(&rgbLimt[0]);
    }else if(ui->radioButtonColor1->isChecked())
    {
        InirgbLimt(&rgbLimt[1]);
        SetControlValueByColor(&rgbLimt[1]);
    }else if(ui->radioButtonColor2->isChecked())
    {
        InirgbLimt(&rgbLimt[2]);
        SetControlValueByColor(&rgbLimt[2]);
    }else if(ui->radioButtonColor3->isChecked())
    {
        InirgbLimt(&rgbLimt[3]);
        SetControlValueByColor(&rgbLimt[3]);
    }else if(ui->radioButtonColor4->isChecked())
    {
        InirgbLimt(&rgbLimt[4]);
        SetControlValueByColor(&rgbLimt[4]);
    }else if(ui->radioButtonColor5->isChecked())
    {
        InirgbLimt(&rgbLimt[5]);
        SetControlValueByColor(&rgbLimt[5]);
    }else if(ui->radioButtonColor6->isChecked())
    {
        InirgbLimt(&rgbLimt[6]);
        SetControlValueByColor(&rgbLimt[6]);
    }else if(ui->radioButtonColor7->isChecked())
    {
        InirgbLimt(&rgbLimt[7]);
        SetControlValueByColor(&rgbLimt[7]);
    }
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxExceptColor_clicked()
{
    if(ui->radioButtonColor0->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[0].bFlagColorExcept = true;
        else
            rgbLimt[0].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor1->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[1].bFlagColorExcept = true;
        else
            rgbLimt[1].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor2->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[2].bFlagColorExcept = true;
        else
            rgbLimt[2].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor3->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[3].bFlagColorExcept = true;
        else
            rgbLimt[3].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor4->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[4].bFlagColorExcept = true;
        else
            rgbLimt[4].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor5->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[5].bFlagColorExcept = true;
        else
            rgbLimt[5].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor6->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[6].bFlagColorExcept = true;
        else
            rgbLimt[6].bFlagColorExcept = false;
    }
    if(ui->radioButtonColor7->isChecked())
    {
        if(ui->checkBoxExceptColor->isChecked())
            rgbLimt[7].bFlagColorExcept = true;
        else
            rgbLimt[7].bFlagColorExcept = false;
    }
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxColorReverse_clicked()
{
    SetDataToMonkeyLib();
}

void ColorSelectDialog::on_checkBoxAutoSet_clicked()
{

}
void ColorSelectDialog::SetLabelsColor()
{
    SetLabelColor(ui->checkBoxColor0->isChecked(),ui->labelColor0,0);
    SetLabelColor(ui->checkBoxColor1->isChecked(),ui->labelColor1,1);
    SetLabelColor(ui->checkBoxColor2->isChecked(),ui->labelColor2,2);
    SetLabelColor(ui->checkBoxColor3->isChecked(),ui->labelColor3,3);
    SetLabelColor(ui->checkBoxColor4->isChecked(),ui->labelColor4,4);
    SetLabelColor(ui->checkBoxColor5->isChecked(),ui->labelColor5,5);
    SetLabelColor(ui->checkBoxColor6->isChecked(),ui->labelColor6,6);
    SetLabelColor(ui->checkBoxColor7->isChecked(),ui->labelColor7,7);

}



void ColorSelectDialog::on_btnUpdataImage_clicked()
{
    /*m_CGetImageThread->SetImageAddr(VGADISPLAY_PHYADDR);
    m_CGetImageThread->GetSingleImag();*/
}

void ColorSelectDialog::btnMinHSub(int value)
{
    int iH = ui->txtHMin->text().toInt();

    if(iH-value >=0)
    {
        ui->txtHMin->setText(QString::number(iH-value ));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMinHAdd(int value)
{
    int iH = ui->txtHMin->text().toInt();

    if(iH + value<= 360)
    {
        ui->txtHMin->setText(QString::number(iH + value));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMaxHSub(int value)
{
    int iH = ui->txtHMax->text().toInt();

    if(iH-value >=0)
    {
        ui->txtHMax->setText(QString::number(iH-value ));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMaxHAdd(int value)
{
    int iH = ui->txtHMax->text().toInt();

    if(iH+value <= 360)
    {
        ui->txtHMax->setText(QString::number(iH+value));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMinSSub(int value)
{

    int iS = ui->txtSMin->text().toInt();
    if(iS-value >= 0)
    {
        ui->txtSMin->setText(QString::number(iS-value));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMinSAdd(int value)
{

    int iS = ui->txtSMin->text().toInt();
    if(iS+value <= ui->txtSMax->text().toInt())
    {
        ui->txtSMin->setText(QString::number(iS+value));
        //SetHSIData();
    }

}

void ColorSelectDialog::btnMaxSSub(int value)
{
    int iS = ui->txtSMax->text().toInt();

    if(iS -value >= ui->txtSMin->text().toInt())
    {
        ui->txtSMax->setText(QString::number(iS-value));
        //SetHSIData();
    }

}

void ColorSelectDialog::btnMaxSAdd(int value)
{
    int iS = ui->txtSMax->text().toInt();
    if(iS+value <= 100)
    {
        ui->txtSMax->setText(QString::number(iS+value));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMinISub(int value)
{
    int iI = ui->txtIMin->text().toInt();

    if(iI-value >= 0)
    {
        ui->txtIMin->setText(QString::number(iI-value));
       // SetHSIData();
    }

}

void ColorSelectDialog::btnMinIAdd(int value)
{
    int iI = ui->txtIMin->text().toInt();

    if(iI +value <= ui->txtIMax->text().toInt())
    {
        ui->txtIMin->setText(QString::number(iI+value));
        //SetHSIData();
    }
}

void ColorSelectDialog::btnMaxISub(int value)
{
    int iI= ui->txtIMax->text().toInt();

    if(iI -value >= ui->txtIMin->text().toInt())
    {
        ui->txtIMax->setText(QString::number(iI-value));
        //SetHSIData();
    }

}

void ColorSelectDialog::btnMaxIAdd(int value)
{
    int iI = ui->txtIMax->text().toInt();

    if(iI +value <= 255)
    {
        ui->txtIMax->setText(QString::number(iI+value));
        //SetHSIData();
    }
}
void ColorSelectDialog::SetHSIData()
{
    if(ui->checkBoxAutoSet->isChecked())
    {

        int HMax = ui->txtHMax->text().toInt();
        int HMin = ui->txtHMin->text().toInt();
        int SMax = ui->txtSMax->text().toInt();
        int SMin = ui->txtSMin->text().toInt();
        int IMax = ui->txtIMax->text().toInt();
        int IMin = ui->txtIMin->text().toInt();
        int iHMaxValue = HMax/2 + 10;
        int iHMinValue = HMin/2 +10;
        int SMaxValue = 100 -SMin+10;
        int SminValue = 100-SMax +10;
        int iMaxValue = (256-IMin)/2+10;
        int iMinValue = (256-IMax)/2+10;

        ui->LabColorSelect->SetHS(iHMaxValue,SMaxValue,iHMinValue,SminValue);
        ui->labColorResult->SetLowHighYValue(iMinValue,iMaxValue);

        m_ColorExtractDeal.FindHSIPicFlag(HMax,HMin,SMax,SMin,IMax,IMin);
        m_ColorExtractDeal.SetImgByHSI();//(ui->labPic,rgbLimt);
        SetRgbLimt();
        UpdateIColor();
        SetDataToMonkeyLib();
    }
}

void ColorSelectDialog::on_btnMinHSub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinHSub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMinHSub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinHSub);
    btnMinHSub();
    SetHSIData();
}

void ColorSelectDialog::on_btnMinHAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinHAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMinHAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinHAdd);
    btnMinHAdd();
    SetHSIData();
}

void ColorSelectDialog::on_btnMaxHSub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxHSub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMaxHSub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxHSub);
    btnMaxHSub();
    SetHSIData();
}

void ColorSelectDialog::on_btnMaxHAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxHAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMaxHAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxHAdd);
    btnMaxHAdd();
    SetHSIData();
}

void ColorSelectDialog::on_btnMinSSub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinSSub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMinSSub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinSSub);
    btnMinSSub();
    SetHSIData();
}

void ColorSelectDialog::on_btnMinSAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinSAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMinSAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinSAdd);
    btnMinSAdd();
    SetHSIData();
}

void ColorSelectDialog::on_btnMaxSSub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxSSub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMaxSSub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxSSub);
    btnMaxSSub();
    SetHSIData();
}

void ColorSelectDialog::on_btnMaxSAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxSAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMaxSAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxSAdd);
    btnMaxSAdd();
    SetHSIData();
}

void ColorSelectDialog::on_btnMinISub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinISub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMinISub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinISub);
    btnMinISub();
    SetHSIData();
}

void ColorSelectDialog::on_btnMinIAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinIAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMinIAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMinIAdd);
    btnMinIAdd();
    SetHSIData();
}

void ColorSelectDialog::on_btnMaxISub_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxISub);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMaxISub_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxISub);
    btnMaxISub();
    SetHSIData();
}

void ColorSelectDialog::on_btnMaxIAdd_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxIAdd);
    UtilitiesFun::Instance()->StartTimer(100);
}

void ColorSelectDialog::on_btnMaxIAdd_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&ColorSelectDialog::btnMaxIAdd);
    btnMaxIAdd();
    SetHSIData();
}
