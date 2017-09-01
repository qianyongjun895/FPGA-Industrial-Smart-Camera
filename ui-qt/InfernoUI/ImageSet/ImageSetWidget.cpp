#include <qdebug.h>
#include "ImageSetWidget.h"
#include "ui_ImageSetWidget.h"
#include "Comm/ControlStyle.h"
#include "Comm/GlobalParameter.h"
#include "Comm/FileIniControl.h"
#include "../Global/UtilitiesFun.h"
#include "System.h"
#include "../Global/UtilitiesFun.h"
#include "cmos_common.h"
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>
#include "MultiCmosParam.h"
#include "TaskStepGlobal.h"
#include "TaskHeaderGlobal.h"
ImageSetWidget::ImageSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageSetWidget)
{
    ui->setupUi(this);
    ControlStyle::SetTabBar(ui->tabWidget);
    ui->tabWidget->setCurrentIndex(0);
    ui->radioButtonUpLineLimit->setChecked(true);
    timerUpData = new QTimer(this);
    m_key_state = 0;
    IniData();
    UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y());
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
    connect(ui->labelPic,&ImageSetLabelEdit::signaleValue,this,&ImageSetWidget::LabelLineSlot);

    if(Get_HWC_Color_Type()!=1)//彩色相机
    {
        ui->tabWidget->removeTab(1);
    }
    for(int i = 0; i < CMOS_PARAM_NUM_MAX; i++){
        M_CMOS_PARAM ComsParam;
        int ret = M_Cmos_Param_Get(i, &ComsParam);
        if(ret != 0){
            continue;
        }
        QLabel *label = new QLabel;
        label->setText("参数"+QString::number(i+1));
        QFont font;
        font.setPixelSize(20);
        label->setFont(font);
        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        ui->listWidget->setItemWidget(listItem, (QWidget*)label);
        ui->listWidget->item(i)->setSizeHint(QSize(200,31));
    }
}

ImageSetWidget::~ImageSetWidget()
{
    QString strTaskPath = "/mnt/emmc2/task/tmp/ImageSet.ini";
    FileIniControl::WriteSettings(strTaskPath,"imageSet","mExplosion",ui->txtMsExplosion->text());
    FileIniControl::WriteSettings(strTaskPath,"imageSet","uExplosion",ui->txtExplosion->text());
    FileIniControl::WriteSettings(strTaskPath,"imageSet","gain",ui->txtGain->text());
    int iStartY =ui->labelPic->GetStartY();
    int iEndY = ui->labelPic->GetEndY();
    FileIniControl::WriteSettings(strTaskPath,"imageSet","startY",QString::number(iStartY));
    FileIniControl::WriteSettings(strTaskPath,"imageSet","endY",QString::number(iEndY));
    FileIniControl::WriteSettings(strTaskPath,"imageSet","R",ui->txtR->text());
    FileIniControl::WriteSettings(strTaskPath,"imageSet","B",ui->txtB->text());
    FileIniControl::WriteSettings(strTaskPath,"imageSet","ImageRollovers",QString::number(m_rotate_type));
    M_Cmos_Param_Save();
    if(timerUpData !=NULL)
    {
        delete timerUpData;
        timerUpData = NULL;
    }
    delete ui;
}
void ImageSetWidget::IniData()
{
    m_ini_first = 0;

    QString strTaskPath = "/mnt/emmc2/task/tmp/ImageSet.ini";
    QFile file(strTaskPath);

    if(!file.exists())
    {
        strTaskPath = "./Config/UIIcon.ini";
    }

    QString strMsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","mExplosion");
    QString strUsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","uExplosion");
    ui->horizontalSliderMsExplosion->setValue(strMsExposure.toInt());
    ui->txtMsExplosion->setText(strMsExposure);

    /*if(ui->horizontalSliderMsExplosion->value() == 0)
    {
        ui->horizontalSliderExplosion->setMinimum(99);
    }
    else
    {
        ui->horizontalSliderExplosion->setMinimum(0);
    }*/
    ui->horizontalSliderExplosion->setMinimum(0);
    ui->horizontalSliderExplosion->setValue(strUsExposure.toInt());
    ui->txtExplosion->setText(strUsExposure);
    int value = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(value);

    int istartY = FileIniControl::ReadSettings(strTaskPath,"imageSet","startY").toInt();
    int iendY =FileIniControl::ReadSettings(strTaskPath,"imageSet","endY").toInt();
    ui->labelPic->SetLine(istartY,iendY);
    ui->labelLineUp->setText("Y:"+QString::number(istartY));
    ui->labelLineDown->setText("Y:"+QString::number(iendY));
    UtilitiesFun::Instance()->SetCmosLimit(istartY,iendY);
    m_rotate_type = (unsigned char)FileIniControl::ReadSettings(strTaskPath,"imageSet","ImageRollovers").toInt();

    if(m_rotate_type == 0)
    {
        ui->radioButton_Normal->setChecked(true);
        on_radioButton_Normal_clicked();
    }
    else if(m_rotate_type == 1)
    {
        ui->radioButton_Left_Right->setChecked(true);
        on_radioButton_Left_Right_clicked();
    }
    else if(m_rotate_type == 2)
    {
        ui->radioButton_Up_Down->setChecked(true);
        on_radioButton_Up_Down_clicked();
    }
    else if(m_rotate_type == 3)
    {
        ui->radioButton_Both->setChecked(true);
        on_radioButton_Both_clicked();
    }
    int iGain = FileIniControl::ReadSettings(strTaskPath,"imageSet","gain").toInt();
    ui->horizontalSliderGain->setValue(iGain);
    ui->txtGain->setText(QString::number(iGain));
    GlobalParameter::g_lib_zynq.Set_Gain(iGain);
    unsigned int iR = FileIniControl::ReadSettings(strTaskPath,"imageSet","R").toInt();
    ui->horizontalSliderRWB->setValue(iR);
    ui->txtR->setText(QString::number(iR));

    unsigned  int iB = FileIniControl::ReadSettings(strTaskPath,"imageSet","B").toInt();
    ui->horizontalSliderBWB->setValue(iR);
    ui->txtB->setText(QString::number(iB));
    White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
    m_ini_first = 1;
}
void ImageSetWidget::on_btnSubGain_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int iret = ui->horizontalSliderGain->value();
    int imin = ui->horizontalSliderGain->minimum();
    if(iret-value < imin)
        return;
    ui->horizontalSliderGain->setValue(iret-value);
    ui->txtGain->setText(QString::number(iret-value));
    GlobalParameter::g_lib_zynq.Set_Gain(iret-value);
    SetImageParam();
}

void ImageSetWidget::on_btnAddGain_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;
    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;
    int iret = ui->horizontalSliderGain->value();
    int imax = ui->horizontalSliderGain->maximum();
    if(iret+value > imax)
        return;
    ui->horizontalSliderGain->setValue(iret+value );
    ui->txtGain->setText(QString::number(iret+value ));
    GlobalParameter::g_lib_zynq.Set_Gain(iret+value);
    SetImageParam();
}
void ImageSetWidget::on_btnSubExplosion_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;
    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int iRet = ui->horizontalSliderExplosion->value();
    int imin = ui->horizontalSliderExplosion->minimum();

    if(iRet-value < imin)
        return;
    if(ui->horizontalSliderMsExplosion->value() == 0)
    {
        if(iRet-value < 99)
        {
           ui->horizontalSliderExplosion->setValue(99);
            return;
        }
    }
    ui->horizontalSliderExplosion->setValue(iRet-value);
    ui->txtExplosion->setText(QString::number(iRet-value));
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    SetImageParam();
}
void ImageSetWidget::on_btnAddExplosion_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;
    int iRet = ui->horizontalSliderExplosion->value()+1;
    int imax= ui->horizontalSliderExplosion->maximum();
    if(iRet + value > imax)
        return;
    ui->horizontalSliderExplosion->setValue(iRet + value);
    ui->txtExplosion->setText(QString::number(iRet + value));
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    SetImageParam();
}
void ImageSetWidget::on_btnMsSubExplosion_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int imin = ui->horizontalSliderMsExplosion->minimum();
    int iRet = ui->horizontalSliderMsExplosion->value();
    if(iRet - value < imin)
        return;
    ui->txtMsExplosion->setText(QString::number(iRet - value));
    ui->horizontalSliderMsExplosion->setValue(iRet - value);
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    SetImageParam();
}
void ImageSetWidget::on_btnMsAddExplosion_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int imax = ui->horizontalSliderMsExplosion->maximum();
    int iRet = ui->horizontalSliderMsExplosion->value()+1;
    if(iRet +value > imax)
        return;

    ui->txtMsExplosion->setText(QString::number(iRet +value ));
    ui->horizontalSliderMsExplosion->setValue(iRet +value );
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    SetImageParam();
}
void ImageSetWidget::on_horizontalSliderGain_valueChanged(int value)
{
    ui->txtGain->setText(QString::number(value));

    if(m_ini_first ==1)
    {
        if(IsTimeOut() ==1)
        {
            GlobalParameter::g_lib_zynq.Set_Gain(value);
            SetImageParam();
        }
    }
}
//爆光
void ImageSetWidget::on_horizontalSliderExplosion_valueChanged(int value)
{
    ui->txtExplosion->setText(QString::number(value));
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ value;
    if(m_ini_first ==1)
    {
        if(ui->horizontalSliderMsExplosion->value() == 0)
        {
            if(value < 99)
            {
                ui->txtExplosion->setText("99");
                ui->horizontalSliderExplosion->setValue(99);
                return;
            }
        }
        if(IsTimeOut() ==1)
        {
            GlobalParameter::g_lib_zynq.Set_Exposure(ret);
            SetImageParam();
        }

    }
}
void ImageSetWidget::on_horizontalSliderMsExplosion_valueChanged(int value)
{
    if(value == 0)
    {
        //ui->horizontalSliderExplosion->setMinimum(99);
        int value = ui->horizontalSliderExplosion->value();
        if(value < 99)
            ui->horizontalSliderExplosion->setValue(99);
    }
    /*else
    {
        ui->horizontalSliderExplosion->setMinimum(0);
    }*/
    ui->txtMsExplosion->setText(QString::number(value));
    int ret = ui->horizontalSliderExplosion->value()+ value*1000;

    if(m_ini_first ==1)
    {
        if(IsTimeOut() ==1)
        {
            GlobalParameter::g_lib_zynq.Set_Exposure(ret);
            SetImageParam();
        }

    }
}
int ImageSetWidget::IsTimeOut()
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
void ImageSetWidget::on_horizontalSliderMsExplosion_sliderPressed()
{
    startTime = QTime::currentTime();
}

void ImageSetWidget::on_horizontalSliderMsExplosion_sliderReleased()
{
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    SetImageParam();
}

void ImageSetWidget::on_horizontalSliderExplosion_sliderPressed()
{
    startTime = QTime::currentTime();
}

void ImageSetWidget::on_horizontalSliderExplosion_sliderReleased()
{
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    SetImageParam();
}

void ImageSetWidget::on_horizontalSliderGain_sliderPressed()
{
    startTime = QTime::currentTime();
}

void ImageSetWidget::on_horizontalSliderGain_sliderReleased()
{
    int value = ui->horizontalSliderGain->value();
    GlobalParameter::g_lib_zynq.Set_Gain(value);
    SetImageParam();
}
void ImageSetWidget::on_btnSubGain_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSubGain_clicked()));
    m_iPresstimes =1;

    int value = ui->horizontalSliderGain->value()-1;
    int imin = ui->horizontalSliderGain->minimum();
    if(value < imin)
        return;
    ui->horizontalSliderGain->setValue(value);
    ui->txtGain->setText(QString::number(value));
    GlobalParameter::g_lib_zynq.Set_Gain(value);
    timerUpData->start(100);
}

void ImageSetWidget::on_btnSubGain_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSubGain_clicked()));
}

void ImageSetWidget::on_btnAddGain_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddGain_clicked()));
    m_iPresstimes =1;

    int value = ui->horizontalSliderGain->value()+1;
    int imax = ui->horizontalSliderGain->maximum();
    if(value > imax)
        return;
    ui->horizontalSliderGain->setValue(value);
    ui->txtGain->setText(QString::number(value));
    GlobalParameter::g_lib_zynq.Set_Gain(value);
    timerUpData->start(100);
}

void ImageSetWidget::on_btnAddGain_released()
{

    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddGain_clicked()));
    //m_iPresstimes =0;
}
void ImageSetWidget::on_btnSubExplosion_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSubExplosion_clicked()));
    m_iPresstimes =1;
    int value = ui->horizontalSliderExplosion->value()-1;
    int imin = ui->horizontalSliderExplosion->minimum();
    if(value < imin)
        return;
    if(ui->horizontalSliderMsExplosion->value() == 0)
    {
        if(value < 99)
        {
            ui->horizontalSliderExplosion->setValue(99);
            ui->txtExplosion->setText(QString::number(99));
            return;
        }
    }
    ui->horizontalSliderExplosion->setValue(value);
    ui->txtExplosion->setText(QString::number(value));
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    timerUpData->start(100);
}

void ImageSetWidget::on_btnSubExplosion_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSubExplosion_clicked()));
    //m_iPresstimes =0;
}

void ImageSetWidget::on_btnAddExplosion_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddExplosion_clicked()));
    m_iPresstimes =1;
    int value = ui->horizontalSliderExplosion->value()+1;
    int imax= ui->horizontalSliderExplosion->maximum();
    if(value > imax)
        return;
    ui->horizontalSliderExplosion->setValue(value);
    ui->txtExplosion->setText(QString::number(value));
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    timerUpData->start(100);
}

void ImageSetWidget::on_btnAddExplosion_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddExplosion_clicked()));
    //m_iPresstimes =0;
}
void ImageSetWidget::on_btnMsSubExplosion_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnMsSubExplosion_clicked()));
    m_iPresstimes =1;
    int imin = ui->horizontalSliderMsExplosion->minimum();
    int value = ui->horizontalSliderMsExplosion->value()-1;
    if(value < imin)
        return;
    ui->txtMsExplosion->setText(QString::number(value));
    ui->horizontalSliderMsExplosion->setValue(value);
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    timerUpData->start(100);
}

void ImageSetWidget::on_btnMsSubExplosion_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnMsSubExplosion_clicked()));
    //m_iPresstimes =0;
}

void ImageSetWidget::on_btnMsAddExplosion_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnMsAddExplosion_clicked()));
    m_iPresstimes =1;

    int imax = ui->horizontalSliderMsExplosion->maximum();
    int value = ui->horizontalSliderMsExplosion->value()+1;
    if(value > imax)
        return;
    ui->txtMsExplosion->setText(QString::number(value));
    ui->horizontalSliderMsExplosion->setValue(value);
    int ret = ui->horizontalSliderMsExplosion->value()*1000+ui->horizontalSliderExplosion->value();
    GlobalParameter::g_lib_zynq.Set_Exposure(ret);
    timerUpData->start(100);
}

void ImageSetWidget::on_btnMsAddExplosion_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnMsAddExplosion_clicked()));
    //m_iPresstimes =0;
}
void ImageSetWidget::on_btnStartTriger_clicked()
{
    unsigned int iR = 0;
    unsigned int iB = 0;
    White_Balance_Param_Set(AUTO_WHITE_BALANCE,&iR,&iB);
    startTime = QTime::currentTime();
    ui->txtB->setText(QString::number(iB));
    ui->horizontalSliderBWB->setValue(iB);
    ui->txtR->setText(QString::number(iR));
    ui->horizontalSliderRWB->setValue(iR);
}
//手动设置白平
void ImageSetWidget::on_btnByManual_clicked()
{
    unsigned int iR = ui->txtR->text().toInt();
    unsigned int iB = ui->txtB->text().toInt();
    White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
}

void ImageSetWidget::on_btnSuBRWB_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int iRet = ui->txtR->text().toInt();
    if(iRet - value>= 1)
    {
        ui->txtR->setText(QString::number(iRet - value));
        ui->horizontalSliderRWB->setValue(iRet - value);
    }

}

void ImageSetWidget::on_btnAddRWB_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int iRet = ui->txtR->text().toInt();
    if(iRet + value <= 2047)
    {
        ui->txtR->setText(QString::number(iRet + value));
        ui->horizontalSliderRWB->setValue(iRet + value);
    }
}

void ImageSetWidget::on_btnSubBWB_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;
    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;
    int iRet= ui->txtB->text().toInt();

    if(iRet - value >=1)
    {
        ui->txtB->setText(QString::number(iRet - value));
        ui->horizontalSliderBWB->setValue(iRet - value);
    }
}

void ImageSetWidget::on_btnAddBWB_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    int iRet = ui->txtB->text().toInt();
    if(iRet +value <= 2047)
    {
        ui->txtB->setText(QString::number(iRet +value));
        ui->horizontalSliderBWB->setValue(iRet +value);
    }
}

void ImageSetWidget::on_horizontalSliderRWB_valueChanged(int value)
{
    ui->txtR->setText(QString::number(value));
    if(m_ini_first ==1)
    {
        if(IsTimeOut() ==1)
        {
            unsigned int iR = value;
            unsigned int iB = ui->horizontalSliderBWB->value();
            White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
        }
    }
}

void ImageSetWidget::on_horizontalSliderRWB_sliderPressed()
{
    startTime = QTime::currentTime();
}

void ImageSetWidget::on_horizontalSliderRWB_sliderReleased()
{
    int value = ui->horizontalSliderRWB->value();
    unsigned int iR = value;
    unsigned int iB = ui->horizontalSliderBWB->value();
    White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
}

void ImageSetWidget::on_horizontalSliderBWB_sliderPressed()
{
    startTime = QTime::currentTime();
}

void ImageSetWidget::on_horizontalSliderBWB_sliderReleased()
{
    int value = ui->horizontalSliderBWB->value();
    unsigned int iR = ui->horizontalSliderRWB->value();
    unsigned int iB = value;
    White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
}

void ImageSetWidget::on_horizontalSliderBWB_valueChanged(int value)
{
    ui->txtB->setText(QString::number(value));
    if(m_ini_first ==1)
    {
        if(IsTimeOut() ==1)
        {
            unsigned int iR = ui->horizontalSliderRWB->value();
            unsigned int iB = value;
            White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
        }
    }
}

void ImageSetWidget::on_btnSuBRWB_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSuBRWB_clicked()));
    m_iPresstimes =1;

    int value = ui->txtR->text().toInt();
    if(value>1)
    {
        value--;
        ui->txtR->setText(QString::number(value));
        ui->horizontalSliderRWB->setValue(value);
        unsigned int iR = value;
        unsigned int iB = ui->horizontalSliderBWB->value();
        White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
    }

    timerUpData->start(100);
}

void ImageSetWidget::on_btnSuBRWB_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSuBRWB_clicked()));
}

void ImageSetWidget::on_btnAddRWB_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddRWB_clicked()));
    m_iPresstimes =1;

    int value = ui->txtR->text().toInt();
    if(value < 2047)
    {
        value++;
        ui->txtR->setText(QString::number(value));
        ui->horizontalSliderRWB->setValue(value);
        unsigned int iR = value;
        unsigned int iB = ui->horizontalSliderBWB->value();
        White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
    }

    timerUpData->start(100);
}

void ImageSetWidget::on_btnAddRWB_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddRWB_clicked()));
}

void ImageSetWidget::on_btnSubBWB_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSubBWB_clicked()));
    m_iPresstimes =1;
    int value = ui->txtB->text().toInt();

    if(value>1)
    {
        value--;
        ui->txtB->setText(QString::number(value));
        ui->horizontalSliderBWB->setValue(value);
        unsigned int iR = ui->horizontalSliderRWB->value();
        unsigned int iB = value;
        White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
    }
    timerUpData->start(100);
}

void ImageSetWidget::on_btnSubBWB_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSubBWB_clicked()));
}

void ImageSetWidget::on_btnAddBWB_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddBWB_clicked()));
    m_iPresstimes =1;

    int value = ui->txtB->text().toInt();
    if(value < 2047)
    {
        value++;
        ui->txtB->setText(QString::number(value));
        ui->horizontalSliderBWB->setValue(value);
        unsigned int iR = ui->horizontalSliderRWB->value();
        unsigned int iB = value;
        White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);
    }
    timerUpData->start(100);
}

void ImageSetWidget::on_btnAddBWB_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnAddBWB_clicked()));
}
void ImageSetWidget::LabelLineSlot(int kind)
{
    int iHeight = ui->labelPic->GetLineHeigth();
    int iStartY = ui->labelPic->GetStartY();
    int iEndY = ui->labelPic->GetEndY();
    ui->labelLineUp->setText("(Y:"+QString::number(iStartY)+")");
    ui->labelLineDown->setText("(Y:"+QString::number(iEndY)+")");
    UtilitiesFun::Instance()->SetCmosLimit(iStartY,iEndY);
    UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);

    if(kind == 1)
    {
        if(m_key_state ==0)
        {
            if(m_rotate_type == 2 || m_rotate_type == 3)
            {
                UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
            }
            else
            {
                UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
            }
        }
    }
    SetImageParam();
}
void ImageSetWidget::on_btnSkeletonUpLine_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;
    int value =2;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    if(ui->radioButtonUpLineLimit->isChecked())
    {
        ui->labelPic->UpAdjustLine(ImageSetLabelEdit::UPLINE,value);
    }else if(ui->radioButtonDownLineLimit->isChecked())
    {
        ui->labelPic->UpAdjustLine(ImageSetLabelEdit::DOWNLIN,value);
    }
}

void ImageSetWidget::on_btnSkeletonUpLine_pressed()
{
    m_key_state = 1;
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSkeletonUpLine_clicked()));
    m_iPresstimes =1;
    timerUpData->start(100);

    if(ui->radioButtonUpLineLimit->isChecked())
    {
        ui->labelPic->UpAdjustLine(ImageSetLabelEdit::UPLINE);
    }else if(ui->radioButtonDownLineLimit->isChecked())
    {
        ui->labelPic->UpAdjustLine(ImageSetLabelEdit::DOWNLIN);
    }

}

void ImageSetWidget::on_btnSkeletonUpLine_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSkeletonUpLine_clicked()));
    m_key_state = 0;
    LabelLineSlot(1);
}

void ImageSetWidget::on_btnSkeletonDownLine_clicked()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;
    int value =2;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;
    if(ui->radioButtonUpLineLimit->isChecked())
    {
        ui->labelPic->DownAdjustmentLine(ImageSetLabelEdit::UPLINE,value);

    }else if(ui->radioButtonDownLineLimit->isChecked())
    {
        ui->labelPic->DownAdjustmentLine(ImageSetLabelEdit::DOWNLIN,value);
    }
}

void ImageSetWidget::on_btnSkeletonDownLine_pressed()
{
    m_key_state = 1;
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSkeletonDownLine_clicked()));
    m_iPresstimes =1;
    timerUpData->start(100);

    if(ui->radioButtonUpLineLimit->isChecked())
    {
        ui->labelPic->DownAdjustmentLine(ImageSetLabelEdit::UPLINE);
    }else if(ui->radioButtonDownLineLimit->isChecked())
    {
        ui->labelPic->DownAdjustmentLine(ImageSetLabelEdit::DOWNLIN);
    }
}

void ImageSetWidget::on_btnSkeletonDownLine_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnSkeletonDownLine_clicked()));
    m_key_state = 0;
    LabelLineSlot(1);
}

void ImageSetWidget::on_radioButtonUpLineLimit_clicked()
{
    ui->radioButtonUpLineLimit->setChecked(true);
    ui->radioButtonDownLineLimit->setChecked(false);
}

void ImageSetWidget::on_radioButtonDownLineLimit_clicked()
{
    ui->radioButtonUpLineLimit->setChecked(false);
    ui->radioButtonDownLineLimit->setChecked(true);
}

void ImageSetWidget::on_tabWidget_tabBarClicked(int index)
{
    switch (index) {
    case 0:
        ui->labelPic->SetListAdjustLine(1);
        break;
    case 1:
        ui->labelPic->SetListAdjustLine(0);
        break;
    default:
        break;
    }
}

void ImageSetWidget::on_radioButton_Normal_clicked()
{
    this->m_rotate_type = 0;
    Set_HWC_CMOS_Flip(IMAGE_NORMAL);
    int iHeight = ui->labelPic->GetLineHeigth();
    int iStartY = ui->labelPic->GetStartY();
    UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
    UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
    SetImageParam();
}

void ImageSetWidget::on_radioButton_Left_Right_clicked()
{
    this->m_rotate_type = 1;
    Set_HWC_CMOS_Flip(IMAGE_LEFT_RIGHT_INVERT);
    int iHeight = ui->labelPic->GetLineHeigth();
    int iStartY = ui->labelPic->GetStartY();
    UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
    UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
    SetImageParam();
}

void ImageSetWidget::on_radioButton_Up_Down_clicked()
{
    this->m_rotate_type = 2;
    Set_HWC_CMOS_Flip(IMAGE_UP_DOWN_INVERT);
    int iHeight = ui->labelPic->GetLineHeigth();
    int iEndY = ui->labelPic->GetEndY();
    UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
    UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
    SetImageParam();
}

void ImageSetWidget::on_radioButton_Both_clicked()
{
    this->m_rotate_type = 3;
    Set_HWC_CMOS_Flip(IMAGE_TWO_DIR_INVERT);
    int iHeight = ui->labelPic->GetLineHeigth();
    int iEndY = ui->labelPic->GetEndY();
    UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
    UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
    SetImageParam();
}

void ImageSetWidget::SetImageParam()
{
    M_CMOS_PARAM coms_param;
    int current_index = ui->listWidget->currentRow();
    if(current_index < 0){
        return;
    }
    coms_param.param_valid_flag = CMOS_PARAM_VALID;
    coms_param.exposure_ms = ui->horizontalSliderMsExplosion->value();
    coms_param.exposure_us = ui->horizontalSliderExplosion->value();
    coms_param.gain = ui->horizontalSliderGain->value();
    coms_param.flip_mode = m_rotate_type;
    coms_param.clip_startY = ui->labelPic->GetStartY();
    coms_param.clip_height = ui->labelPic->GetLineHeigth();
    M_Cmos_Param_Set(current_index, &coms_param);
}

void ImageSetWidget::on_pushButton_Param_Save_clicked()
{
    int row_count = ui->listWidget->count();
    M_CMOS_PARAM coms_param;
    int ret = M_Cmos_Param_Get(row_count, &coms_param);
    if(ret != 0){
        coms_param.param_valid_flag = CMOS_PARAM_VALID;
        coms_param.exposure_ms = ui->horizontalSliderMsExplosion->value();
        coms_param.exposure_us = ui->horizontalSliderExplosion->value();
        coms_param.gain = ui->horizontalSliderGain->value();
        coms_param.flip_mode = m_rotate_type;
        coms_param.clip_startY = ui->labelPic->GetStartY();
        coms_param.clip_height = ui->labelPic->GetLineHeigth();
        ret = M_Cmos_Param_Set(row_count, &coms_param);
        if(ret == 0){
            QLabel *label = new QLabel;
            label->setText("参数"+QString::number(row_count + 1));
            QFont font;
            font.setPixelSize(20);
            label->setFont(font);
            QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
            ui->listWidget->setItemWidget(listItem, (QWidget*)label);
            ui->listWidget->item(row_count)->setSizeHint(QSize(200,31));
            QMessageBox::about(NULL, "提示", "添加参数"+QString::number(row_count+1)+"成功");
            return;
        }
    }
    QMessageBox::about(NULL, "提示", "添加参数失败");
    return;
}

void ImageSetWidget::on_pushButton_Param_del_clicked()
{
    int row_count = ui->listWidget->count();
    if(row_count <= 0){
        return;
    }
    int current_index = ui->listWidget->currentRow();
    if(current_index >= 0){
        M_CMOS_PARAM coms_param;
        for(int i = current_index; i < row_count - 1; i++){
            M_Cmos_Param_Get(i+1, &coms_param);
            M_Cmos_Param_Set(i, &coms_param);
        }
        coms_param.param_valid_flag = CMOS_PARAM_INVALID;
        M_Cmos_Param_Set(row_count - 1, &coms_param);
        ui->listWidget->clear();
        for(int i = 0; i < row_count-1; i++){
            QLabel *label = new QLabel;
            label->setText("参数"+QString::number(i+1));
            QFont font;
            font.setPixelSize(20);
            label->setFont(font);
            QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
            ui->listWidget->setItemWidget(listItem, (QWidget*)label);
            ui->listWidget->item(i)->setSizeHint(QSize(200,31));
        }
        int Task_Count = GetTaskStepCount();
        for(int i = 1; i <= Task_Count; i ++){
            int ret = Task_Step_Cmos_Param_Index_Get(i);
            if(ret == current_index+1){
                Task_Step_Cmos_Param_Index_Set(i, 0);
            }
        }
        QMessageBox::about(NULL, "提示", "删除参数"+QString::number(current_index+1)+"成功");
        return;
    }
    QMessageBox::about(NULL, "提示", "删除参数失败");
}

void ImageSetWidget::on_listWidget_currentRowChanged(int currentRow)
{
    M_CMOS_PARAM coms_param;
    if(currentRow >= 0){
        int ret = M_Cmos_Param_Get(currentRow, &coms_param);
        if(ret == 0 && coms_param.param_valid_flag == CMOS_PARAM_VALID){
            ui->labelPic->SetLine(coms_param.clip_startY, coms_param.clip_startY+coms_param.clip_height);
            ui->labelLineUp->setText("Y:"+QString::number(coms_param.clip_startY));
            ui->labelLineDown->setText("Y:"+QString::number(coms_param.clip_startY+coms_param.clip_height));

            ui->horizontalSliderMsExplosion->setValue(coms_param.exposure_ms);
            ui->horizontalSliderExplosion->setValue(coms_param.exposure_us);
            GlobalParameter::g_lib_zynq.Set_Exposure(coms_param.exposure_ms*1000+coms_param.exposure_us);

            ui->horizontalSliderGain->setValue(coms_param.gain);
            ui->txtGain->setText(QString::number(coms_param.gain));
            GlobalParameter::g_lib_zynq.Set_Gain(coms_param.gain);

            m_rotate_type = coms_param.flip_mode;
            if(m_rotate_type == 0){
                ui->radioButton_Normal->setChecked(true);
                on_radioButton_Normal_clicked();
            }else if(m_rotate_type == 1){
                ui->radioButton_Left_Right->setChecked(true);
                on_radioButton_Left_Right_clicked();
            }else if(m_rotate_type == 2){
                ui->radioButton_Up_Down->setChecked(true);
                on_radioButton_Up_Down_clicked();
            }else if(m_rotate_type == 3){
                ui->radioButton_Both->setChecked(true);
                on_radioButton_Both_clicked();
            }
        }
    }
}

void ImageSetWidget::on_pushButton_clear_Param_clicked()
{
    int row_count = ui->listWidget->count();
    if(row_count <= 0){
        return;
    }
    for(int i = 0; i < row_count; i++){
        M_CMOS_PARAM coms_param;
        coms_param.param_valid_flag = CMOS_PARAM_INVALID;
        M_Cmos_Param_Set(i, &coms_param);
    }
    int Task_Count = GetTaskStepCount();
    for(int i = 1; i <= Task_Count; i ++){
        Task_Step_Cmos_Param_Index_Set(i, 0);
    }
    ui->listWidget->clear();
}
