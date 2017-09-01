#include <qdebug.h>
#include "ImagepreprocessDlg.h"
#include "ui_ImagepreprocessDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "PretreatMentListCollect/PretreatmentModuleItem.h"
#include "ContrastStrengthenDlg.h"
#include "ContrastSwitchDlg.h"
#include "GaussDlg.h"
#include "SharpnessDlg.h"
#include "PeakFilterDlg.h"
#include "ShadingDialog.h"
#include "DefectDialog.h"
#include "BlurDialog.h"
#include "AcceCommon.h"
//#include "fpga_global.h"
#include "Preprocess.h"

void SetGaussEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable = 1;
        AcceleratorModuleEnable(ACCE_GAUSS_FILTER_ID);
    }else
    {
        ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable = 0;
        AcceleratorModuleDisable(ACCE_GAUSS_FILTER_ID);

    }
}
void SetGaussDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_GAUSS_FILTER_ID,preDlg->m_step,flag);
}
void ListGaussDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    GaussDlg dlg;
    dlg.m_task_id = preDlg->m_task_id;
    dlg.m_step = preDlg->m_step;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    dlg.exec();
}
void SetContrastStrengthenEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;

    if(flag == 1)
    {   
        ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable = 1;
        AcceleratorModuleEnable(ACCE_BALANCE_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable = 0;
        AcceleratorModuleDisable(ACCE_BALANCE_MODEL_ID);

    }
    //AcceleratorModuleCfgShow(ACCE_BALANCE_MODEL_ID);
}
void SetContrastStrengthenDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_BALANCE_MODEL_ID,preDlg->m_step,flag);
}
void ListContrastStrengthenDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ContrastStrengthenDlg dlg;
    dlg.m_task_id = preDlg->m_task_id;
    dlg.m_step = preDlg->m_step;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.InitData();
    dlg.exec();
}
void SetContrastSwitchEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_CONTRAST_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_CONTRAST_MODEL_ID);

    }
}
void SetContrastSwitchDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_CONTRAST_MODEL_ID,preDlg->m_step,flag);
}
void ListContrastSwitchDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ContrastSwitchDlg dlg;
    dlg.m_task_id = preDlg->m_task_id;
    dlg.m_step = preDlg->m_step;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.IniData();
    dlg.move(660,0);
    dlg.exec();
}
//边缘强调
void SetSharpnessEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;

    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.model_enable = 1;
        AcceleratorModuleEnable(ACCE_SHARPNESS_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.model_enable = 0;
        AcceleratorModuleDisable(ACCE_SHARPNESS_MODEL_ID);

    }
}
void SetSharpnessDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_SHARPNESS_MODEL_ID,preDlg->m_step,flag);
}
void ListSharpnessDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    SharpnessDlg dlg;
    dlg.m_task_id = preDlg->m_task_id;
    dlg.m_step = preDlg->m_step;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.move(660,0);
    dlg.InitData();
    dlg.exec();
}
//原图膨胀腐蚀A
void SetPeakFilterAEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;

    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_PEAK_FILTER_A_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_PEAK_FILTER_A_MODEL_ID);
    }
}
void SetPeakFilterADDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_PEAK_FILTER_A_MODEL_ID,preDlg->m_step,flag);
}
void ListPeakFilterADlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    PeakFilterDlg dlg;
    dlg.m_task_id = preDlg->m_task_id;
    dlg.m_step = preDlg->m_step;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_SharpnessKind = PeakFilterDlg::SharpnessA;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    dlg.exec();
}
//原图膨胀腐蚀B
void SetPeakFilterBEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;

    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_PEAK_FILTER_B_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.model_enable = 0;
        AcceleratorModuleDisable(ACCE_PEAK_FILTER_B_MODEL_ID);

    }
}
void SetPeakFilterBDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_PEAK_FILTER_B_MODEL_ID,preDlg->m_step,flag);
}
void ListPeakFilterBDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    PeakFilterDlg dlg;
    dlg.m_task_id = preDlg->m_task_id;
    dlg.m_step = preDlg->m_step;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_SharpnessKind = PeakFilterDlg::SharpnessB;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    dlg.exec();
}

//实时浓淡补正
void ListShadingDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ShadingDialog dlg;
    dlg.m_step_id = preDlg->m_step;
    dlg.m_task_id= preDlg->m_task_id;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.move(660,0);
    dlg.IniData();
    dlg.exec();
}
void SetShadingEnable(int flag,void *Pdata)
{
     ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.shading_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_SHADING_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.shading_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_SHADING_MODEL_ID);

    }
}
void SetShadingDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_SHADING_MODEL_ID,preDlg->m_step,flag);
}
void SetShadingSrcValue(int taskId,void *pData)
{

}
//缺陷提取
void ListDefectDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    DefectDialog dlg;
    dlg.m_step_id = preDlg->m_step;
    dlg.m_task_id= preDlg->m_task_id;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.move(660,0);
    dlg.IniData();
    dlg.exec();
}
void SetDefectEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.defect_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_DEFECT_MODEL_ID);
    }else
    {
        ptr->image_acce_param.pre_model_cfg.defect_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_DEFECT_MODEL_ID);
    }
}
void SetDefectDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_DEFECT_MODEL_ID,preDlg->m_step,flag);
}
void SetDefectSrcValue(int taskId,void *pData)
{

}
//模糊处理
void ListBlurDlg(int itaskKind,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    BlurDialog dlg;
    dlg.m_step = preDlg->m_step;
    dlg.m_task_id= preDlg->m_task_id;
    dlg.m_pre_ptr = preDlg->m_pre_ptr;
    dlg.m_listX = preDlg->m_listX;
    dlg.m_listY = preDlg->m_listY;
    dlg.move(660,0);
    dlg.InitData();
    dlg.exec();
}
void SetBlurEnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)preDlg->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.blur_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_BLUR_MODEL_ID);

    }else
    {
        ptr->image_acce_param.pre_model_cfg.blur_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_BLUR_MODEL_ID);

    }
}
void SetBlurDDREnable(int flag,void *Pdata)
{
    ImagepreprocessDlg *preDlg = (ImagepreprocessDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_BLUR_MODEL_ID,preDlg->m_step,flag);
}
void SetBlurSrcValue(int taskId,void *pData)
{

}

ImagepreprocessDlg::ImagepreprocessDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagepreprocessDlg)
{
    ui->setupUi(this);
    m_listX = ui->labelPic->x();
    m_listY = ui->labelPic->y();
    IniDefalutPattern();
    InitFunPtr();
}

ImagepreprocessDlg::~ImagepreprocessDlg()
{
    delete ui;
}
void ImagepreprocessDlg::InitFunPtr()
{

    STRUCT_FUN_PTR blurMode;
    blurMode.List_model_dlg=ListBlurDlg;
    blurMode.Set_ddr_enable=SetBlurDDREnable;
    blurMode.Set_model_enable = SetBlurEnable;
    m_fun_ptr.insert(ACCE_BLUR_MODEL_ID,blurMode);

    STRUCT_FUN_PTR gaussMode;
    gaussMode.List_model_dlg=ListGaussDlg;
    gaussMode.Set_ddr_enable=SetGaussDDREnable;
    gaussMode.Set_model_enable = SetGaussEnable;
    m_fun_ptr.insert(ACCE_GAUSS_FILTER_ID,gaussMode);

    STRUCT_FUN_PTR contrastStrengthenMode;
    contrastStrengthenMode.List_model_dlg=ListContrastStrengthenDlg;
    contrastStrengthenMode.Set_ddr_enable=SetContrastStrengthenDDREnable;
    contrastStrengthenMode.Set_model_enable = SetContrastStrengthenEnable;
    m_fun_ptr.insert(ACCE_BALANCE_MODEL_ID,contrastStrengthenMode);

    STRUCT_FUN_PTR contrastSwitchMode;
    contrastSwitchMode.List_model_dlg=ListContrastSwitchDlg;
    contrastSwitchMode.Set_ddr_enable=SetContrastSwitchDDREnable;
    contrastSwitchMode.Set_model_enable = SetContrastSwitchEnable;
    m_fun_ptr.insert(ACCE_CONTRAST_MODEL_ID,contrastSwitchMode);

    STRUCT_FUN_PTR sharpness; //边缘强调
    sharpness.List_model_dlg=ListSharpnessDlg;
    sharpness.Set_ddr_enable=SetSharpnessDDREnable;
    sharpness.Set_model_enable = SetSharpnessEnable;
    m_fun_ptr.insert(ACCE_SHARPNESS_MODEL_ID,sharpness);

    STRUCT_FUN_PTR peakFilterA; //原图膨胀腐蚀a
    peakFilterA.List_model_dlg=ListPeakFilterADlg;
    peakFilterA.Set_ddr_enable=SetPeakFilterADDREnable;
    peakFilterA.Set_model_enable = SetPeakFilterAEnable;
    m_fun_ptr.insert(ACCE_PEAK_FILTER_A_MODEL_ID,peakFilterA);

    STRUCT_FUN_PTR peakFilterB; //原图膨胀腐蚀b
    peakFilterB.List_model_dlg=ListPeakFilterBDlg;
    peakFilterB.Set_ddr_enable=SetPeakFilterBDDREnable;
    peakFilterB.Set_model_enable = SetPeakFilterBEnable;
    m_fun_ptr.insert(ACCE_PEAK_FILTER_B_MODEL_ID,peakFilterB);

    STRUCT_FUN_PTR shadingMode;
    shadingMode.List_model_dlg=ListShadingDlg;
    shadingMode.Set_ddr_enable=SetShadingDDREnable;
    shadingMode.Set_model_enable =SetShadingEnable;
    shadingMode.SetPicSrc = SetShadingSrcValue;
    m_fun_ptr.insert(ACCE_SHADING_MODEL_ID,shadingMode);

    STRUCT_FUN_PTR defectMode;
    defectMode.List_model_dlg=ListDefectDlg;
    defectMode.Set_ddr_enable=SetDefectDDREnable;
    defectMode.Set_model_enable =SetDefectEnable;
    defectMode.SetPicSrc = SetDefectSrcValue;
    m_fun_ptr.insert(ACCE_DEFECT_MODEL_ID,defectMode);

}
void ImagepreprocessDlg::IniDefalutPattern()
{
    int width = ui->listWidgetPattern->width();
    int height = 50;

    ui->listWidgetPattern->addItem("默认模式1");
    ui->listWidgetPattern->addItem("默认模式2");
    ui->listWidgetPattern->addItem("默认模式3");

    for (int i=0;i<ui->listWidgetPattern->count();i++)
    {
        QListWidgetItem * pItem = ui->listWidgetPattern->item(i);
        pItem->setSizeHint(QSize(width,height));
    }
}
void ImagepreprocessDlg::ClearList(QListWidget *pListWidget)
{
    int count = pListWidget->count();

    for(int i= 0; i<count;i++)
    {
        int row = pListWidget->count()-1;
        QListWidgetItem *itemdel= pListWidget->takeItem(row);
        delete itemdel;
    }
}
void ImagepreprocessDlg::on_listWidgetPattern_clicked(const QModelIndex &index)
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        int iRow = index.row();
        switch (iRow) {
        case 0:
            DefalutOne();
            ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel = 0;
            AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
            break;
        case 1:
            DefalutTwo();
            ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel = 1;
            AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
            break;
        case 2:
            DefalutThree();
            ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel = 2;
            AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
            break;
        case 3:

            break;
        case 4:
            break;
        default:
            break;
        }
        GetImageOutPut();
        ListInformation("设定适用于图像预处理种类，指定了复数个种类，以从上往下的方式进行处理");
    }
}
void ImagepreprocessDlg::DefalutOne()
{
    ClearList(ui->listWidget);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    AddItemData(tr("模糊处理"),ACCE_BLUR_MODEL_ID,ptr->image_acce_param.pre_model_cfg.blur_model_cfg.model_enable,0);
    m_fun_ptr.value(ACCE_BLUR_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.blur_model_cfg.model_enable,this);

    AddItemData(tr("高斯滤波"),ACCE_GAUSS_FILTER_ID,ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable,1);
    m_fun_ptr.value(ACCE_GAUSS_FILTER_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable,this);

    AddItemData(tr("对比度增强"),ACCE_BALANCE_MODEL_ID,ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable,2);
    m_fun_ptr.value(ACCE_BALANCE_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable,this);

    AddItemData(tr("对比度转换"),ACCE_CONTRAST_MODEL_ID,ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable,3);
    m_fun_ptr.value(ACCE_CONTRAST_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable,this);

    AddItemData(tr("边缘强调"),ACCE_SHARPNESS_MODEL_ID,ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.model_enable,4);
    m_fun_ptr.value(ACCE_SHARPNESS_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.sharpness_model_cfg.model_enable,this);

    AddItemData(tr("原图膨胀腐蚀A"),ACCE_PEAK_FILTER_A_MODEL_ID,ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.model_enable,5);
    m_fun_ptr.value(ACCE_PEAK_FILTER_A_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.peak_a_model_cfg.model_enable,this);

    AddItemData(tr("原图膨胀腐蚀B"),ACCE_PEAK_FILTER_B_MODEL_ID,ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.model_enable,6);
    m_fun_ptr.value(ACCE_PEAK_FILTER_B_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.peak_b_model_cfg.model_enable,this);

}
void ImagepreprocessDlg::DefalutTwo()
{
    ClearList(ui->listWidget);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;

    AddItemData(tr("高斯滤波"),ACCE_GAUSS_FILTER_ID,ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable,0);
    m_fun_ptr.value(ACCE_GAUSS_FILTER_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable,this);

    AddItemData(tr("对比度增强"),ACCE_BALANCE_MODEL_ID,ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable,1);
    m_fun_ptr.value(ACCE_BALANCE_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable,this);

    AddItemData(tr("对比度转换"),ACCE_CONTRAST_MODEL_ID,ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable,2);
    m_fun_ptr.value(ACCE_CONTRAST_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable,this);

    AddItemData(tr("缺陷提取"),ACCE_DEFECT_MODEL_ID,ptr->image_acce_param.pre_model_cfg.defect_model_cfg.model_enable,3);
    m_fun_ptr.value(ACCE_DEFECT_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.defect_model_cfg.model_enable,this);

}
void ImagepreprocessDlg::DefalutThree()
{
    ClearList(ui->listWidget);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    AddItemData(tr("高斯滤波"),ACCE_GAUSS_FILTER_ID,ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable,0);
    m_fun_ptr.value(ACCE_GAUSS_FILTER_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.gauss_model_cfg.model_enable,this);

    AddItemData(tr("对比度转换"),ACCE_CONTRAST_MODEL_ID,ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable,1);
    m_fun_ptr.value(ACCE_CONTRAST_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.contrast_model_cfg.model_enable,this);

    AddItemData(tr("对比度增强"),ACCE_BALANCE_MODEL_ID,ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable,2);
    m_fun_ptr.value(ACCE_BALANCE_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable,this);

    AddItemData(tr("实时浓淡补正"),ACCE_SHADING_MODEL_ID,ptr->image_acce_param.pre_model_cfg.shading_model_cfg.model_enable,3);
    m_fun_ptr.value(ACCE_SHADING_MODEL_ID).Set_model_enable(ptr->image_acce_param.pre_model_cfg.shading_model_cfg.model_enable,this);
}
void ImagepreprocessDlg::AddItemData(QString strName,int index,int bCheck,int current)
{
    PretreatmentModuleItem *p_PretreatmentModuleItem = new PretreatmentModuleItem;
    p_PretreatmentModuleItem->setAttribute(Qt::WA_DeleteOnClose);
    p_PretreatmentModuleItem->SetInfoName(strName);
    p_PretreatmentModuleItem->m_taskKind = index;
    p_PretreatmentModuleItem->m_current_row = current;
    p_PretreatmentModuleItem->SetCheckdevalue(bCheck);
    int size =ui->listWidget->count();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(mItem,(QWidget*)p_PretreatmentModuleItem);
    ui->listWidget->item(size)->setSizeHint(QSize(340,50));
    ui->listWidget->setCurrentRow(size);
    connect(p_PretreatmentModuleItem,&PretreatmentModuleItem::SignalOperate,this,&ImagepreprocessDlg::OperateSlots);
}
void ImagepreprocessDlg::OperateSlots(int iOperate, int itaskKind, int value, int current)
{
    ui->listWidget->setCurrentRow(current);
    switch (iOperate) {
    case PREENABLE:
        m_fun_ptr.value(itaskKind).Set_model_enable(value,this);
        break;
    case PREDETAIL:
        m_fun_ptr.value(itaskKind).List_model_dlg(itaskKind,this);
        break;
    default:
        break;
    }
    GetImageOutPut();
    ListInformation(GetInfoByTaskID(itaskKind));
}

int ImagepreprocessDlg::GetImageOutPut()
{
    Pre_Model_Out_Src_Auto_Set(m_step);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr !=NULL)
    ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
    AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
    UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y(),0xffffffff);
    return 0;
    int count = ui->listWidget->count();

    for(int i = 0; i<count;i++)
    {
        QListWidgetItem *item =  ui->listWidget->item(count-i-1);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        QString strName= ((PretreatmentModuleItem*)qWidget)->GetInfoName();
        int bChecek =((PretreatmentModuleItem*)qWidget)->GetCheckedValue();
        int taskIndex= ((PretreatmentModuleItem*)qWidget)->m_taskKind;

        if(bChecek == 1)
        {
            m_image_out_src = taskIndex;
            ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
            if(ptr !=NULL)
            {
                //ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en =1;
                ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = m_image_out_src;
                qDebug()<<"m_image_out_src==="<<m_image_out_src;
                ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
                AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
                AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
                AcceleratorModuleWriteDdrCfg(ACCE_PRE_MODEL_ID,m_step,1);
                //AcceleratorModuleEnable(ACCE_PRE_MODEL_ID);
            }

            UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y(),0xffffffff);
            break;
        }
    }
    return m_image_out_src;
}
void ImagepreprocessDlg::on_btnOk_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        int row = ui->listWidgetPattern->currentRow();
        switch (row) {
        case 0:
            ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel = 0;
            break;
        case 1:
            ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel = 1;
            break;
        case 2:
            ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel = 2;
            break;
        default:
            break;
        }
        AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
    }
    QDialog::accept();
}

void ImagepreprocessDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg= m_cfg;
            AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
        }

        QDialog::reject();
    }

}
void ImagepreprocessDlg::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        m_cfg = ptr->image_acce_param.pre_model_cfg;
        int iLineMode = ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel;
        qDebug()<<"ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel="<<ptr->image_acce_param.pre_model_cfg.pipeline_mode_sel;
        switch (iLineMode) {
        case 0:
            DefalutOne();
            ui->listWidgetPattern->setCurrentRow(0);
            break;
        case 1:
            DefalutTwo();
            ui->listWidgetPattern->setCurrentRow(1);
            break;
        case 2:
            DefalutThree();
            ui->listWidgetPattern->setCurrentRow(2);
            break;
        default:
            break;
        }
        GetImageOutPut();
    }
    ListInformation("设定适用于图像预处理种类，指定了复数个种类，以从上往下的方式进行处理");
}
void ImagepreprocessDlg::ListInformation(QString strInfo)
{
    ui->txtInfo->clear();
    ui->txtInfo->append(strInfo);
}
QString ImagepreprocessDlg::GetInfoByTaskID(int taskId)
{

    QString strRet = "";
    switch (taskId) {
    case ACCE_BLUR_MODEL_ID: //模糊处理
        strRet = "模糊图像后进行平滑处理,可达到排除干扰的目的.另外,当检测对象内存在复数个块状物时，通过该处理，可以将块状物连接在一起，使检测达到稳定化的效果。";
        break;
    case ACCE_GAUSS_FILTER_ID: //< 5*5卷积(高斯)滤波模块
        strRet = "高斯滤波是一种线性平滑滤波，适用于消除高斯噪声，应用于图像处理的减噪过程。";
        break;
    case ACCE_BALANCE_MODEL_ID: //均衡直方图模块
        strRet = "对比度增强并不以图像保真为准则，而是有选择地突出某些对人或机器分析有意义的信息，抑制无用信息，提高图像的使用价值。";
        break;
    case ACCE_CONTRAST_MODEL_ID: //对比度转换模块
        strRet = "进行增益调整。调整图像的明暗和浓淡变化的倾斜。";
        break;
    case ACCE_SHARPNESS_MODEL_ID: //边缘强调模块
        strRet = "图像锐化功能，用于增强图像锐利度。";
        break;
    case ACCE_PEAK_FILTER_A_MODEL_ID: //原图腐蚀膨胀A模块
        strRet = "腐蚀是用来消除边界点，使边界向内部收缩的过程，可以用来消除小且无意义的物体，膨胀是将与物体接触的所有背景点合并到该物体中，使边界向外部扩张的过程，可以用来填补物体中的空洞。";
        break;
    case ACCE_PEAK_FILTER_B_MODEL_ID: //原图腐蚀膨胀B模块
        strRet = "腐蚀是用来消除边界点，使边界向内部收缩的过程，可以用来消除小且无意义的物体，膨胀是将与物体接触的所有背景点合并到该物体中，使边界向外部扩张的过程，可以用来填补物体中的空洞。";
        break;
    case ACCE_DEFECT_MODEL_ID: //缺陷提取模块
        strRet = "用于提取均匀背景下的缺陷。";
        break;
    case ACCE_SHADING_MODEL_ID: //实时浓淡补正模块
        strRet = "排除背景的浓淡渐变，只抽取对比度较大的部分。另外，还能使用检测范围内的浓度平均值及中间值，对图像整体的对比度进行平均补正。";
        break;
    default:
        break;
    }
    return strRet;

}


void ImagepreprocessDlg::on_listWidget_clicked(const QModelIndex &index)
{

     int iRow = index.row();

     if(iRow >=0)
     {
         QListWidgetItem *item =  ui->listWidget->item(iRow);
         QWidget *qWidget = ui->listWidget->itemWidget(item);
         int itaskKind= ((PretreatmentModuleItem*)qWidget)->m_taskKind;
         ListInformation(GetInfoByTaskID(itaskKind));
     }

}
