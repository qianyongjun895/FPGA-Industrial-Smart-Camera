#include "BaseImageData.h"
#include "TaskBaseImageSelectGlobal.h"
#include "image_include/ImageManageGlobal.h"
#include "image_include/ImageSimulationGlobal.h"
#include <stdio.h>
BaseImageData::BaseImageData()
{

}

int BaseImageData::SaveBaseImage(QString ImageName)
{
    if(ImageName == QString::null)
    {
        return -1;
    }
    int ret =image_save_to_file(BASE_IMAGE_DIR,ImageName.toLocal8Bit().data());
    return ret;
}

int BaseImageData::LoadBaseImage(QString ImageName)
{
    if(ImageName == QString::null)
    {
        return -1;
    }

    int ret = image_load_to_mem(BASE_IMAGE_DIR,ImageName.toLocal8Bit().data());
    return ret;
}

int BaseImageData::DeleteBaseImage(QString ImageName)
{
    if(ImageName == QString::null)
    {
        return -1;
    }
    int ret = image_file_delete(BASE_IMAGE_DIR,ImageName.toLocal8Bit().data());
    return ret;
}

int BaseImageData::CleanBaseImage()
{
    int ret = image_file_clean(BASE_IMAGE_DIR);
    return ret;
}

QVector<QString> BaseImageData::GetBaseImageDirAllName()
{
    char imageName[100][IMAGE_FILE_NAME_SIZE_MAX];
    QVector<QString> ImageStr;

    int iNum = image_dir_all_file_name_get(BASE_IMAGE_DIR,imageName);

    for(int j = 0; j < iNum; j++)
    {
        ImageStr.append(QString::fromLocal8Bit(imageName[j]));
    }

    return ImageStr;
}
void BaseImageData::SetStepMsFileNameValue(int step,QString strName)
{
    QString strNameTemp = strName;
    if(strNameTemp=="")
        strNameTemp="ffffff";
    task_step_select_base_image_set(step, strName.toLocal8Bit().data());
}
QString BaseImageData::GetStepMsFileNameValue(int step)
{
     char imagename[20];
    int ret =task_step_select_base_image_get(step, imagename);

    if(ret ==1)
    {
        return  QString::fromLocal8Bit((char *)imagename);
    }else
    {
        return "";
    }
    return "";
}
QString BaseImageData::GetSimulationDir()
{
    QString str="";
    unsigned int ret = simulation_dir_type_get();

    switch (ret) {
    case 0:
        str = "ImageSave";
        simulation_run_init(IMAGE_SAVE_DIR);
        break;
    case 1:
        str = "BaseImage";
        simulation_run_init(BASE_IMAGE_DIR);
        break;
    case 2:
        str = "OKImage";
        simulation_run_init(OK_IMAGE_DIR);
        break;
    case 3:
        str = "FailedImage";
        simulation_run_init(NG_IMAGE_DIR);
        break;
    default:
        break;
    }
    return str;
}
void BaseImageData::SetSimulationDir(QString Str)
{
    /*if(str == "ImageImport")
        ui->radioButton_Import->setChecked(true);
    else if(str == "ImageSave")
        ui->radioButton_Save->setChecked(true);
    else if(str == "FailedImage")
        ui->radioButton_Failed->setChecked(true);
    else if(str == "OKImage")
        ui->radioButton_OK->setChecked(true);
    else if(str == "BaseImage")
        ui->radioButton_Base->setChecked(true);*/
}
void BaseImageData::SimulationRunInit(QString str)
{
    if(str == "ImageImport")
        simulation_run_init(IMAGE_DIR_TYPE_MAX);
    else if(str == "ImageSave")
        simulation_run_init(IMAGE_SAVE_DIR);
    else if(str == "FailedImage")
        simulation_run_init(NG_IMAGE_DIR);
    else if(str == "OKImage")
        simulation_run_init(OK_IMAGE_DIR);
    else if(str == "BaseImage")
        simulation_run_init(BASE_IMAGE_DIR);
}
int  BaseImageData::SaveImage(QString str)
{
    int ret=0;
    if(str == "ImageImport")
        ret = image_save_to_default_file_name(IMAGE_DIR_TYPE_MAX);
    else if(str == "ImageSave")
        ret = image_save_to_default_file_name(IMAGE_SAVE_DIR);
    else if(str == "FailedImage")
        ret = image_save_to_default_file_name(NG_IMAGE_DIR);
    else if(str == "OKImage")
        ret = image_save_to_default_file_name(OK_IMAGE_DIR);
    else if(str == "BaseImage")
        ret = image_save_to_default_file_name(BASE_IMAGE_DIR);
    return ret;
}


