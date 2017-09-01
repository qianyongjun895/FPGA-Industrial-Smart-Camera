#include "VersionInfo.h"
#include "ui_VersionInfo.h"
#include "zynq_global.h"

VersionInfo::VersionInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VersionInfo)
{
    ui->setupUi(this);

    unsigned int ramType = Get_HWC_RAM_Config();
    unsigned int sensorType = Get_HWC_Sensor_Type();
    unsigned int shutterType = Get_HWC_Shutter_Mode();
    unsigned int colorType = Get_HWC_Color_Type();
    unsigned int pixelType = Get_HWC_Pixel_Size();
    unsigned int fpgaType = Get_HWC_Fpga_Type();


    if (ramType == 0x01)
    {
        ui->lineEditMemorySize->setText("512MB");
    }
    else if (ramType == 0x02)
    {
        ui->lineEditMemorySize->setText("1GB");
    }

    if (sensorType == 1)
    {
        ui->lineEditSensorType->setText("MT9M031I12STC");
    }
    else if (sensorType == 2)
    {
        ui->lineEditSensorType->setText("MT9M031I12STM");
    }
    else if (sensorType == 3)
    {
        ui->lineEditSensorType->setText("MT9P031");
    }
    else if (sensorType == 4)
    {
        ui->lineEditSensorType->setText("SN5000A");
    }

    if (shutterType == 0)
    {
        ui->lineEditShutterType->setText("卷帘");
    }
    else if (shutterType == 1)
    {
        ui->lineEditShutterType->setText("全局");
    }

    if (colorType == 0)
    {
        ui->lineEditCameraType->setText("黑白");
    }
    else if (colorType == 1)
    {
        ui->lineEditCameraType->setText("彩色");
    }

    if (pixelType == 0x02)
    {
        ui->lineEditPixelType->setText("30W");
    }
    else if (pixelType == 0x04)
    {
        ui->lineEditPixelType->setText("130W");
    }
    else if (pixelType == 0x10)
    {
        ui->lineEditPixelType->setText("500W");
    }

    ui->lineEditFpgaVersion->setText(QString::number(fpgaType, 16));
}

VersionInfo::~VersionInfo()
{
    delete ui;
}
