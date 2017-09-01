#include <qdebug.h>
#include "BinaryzationDlg.h"
#include "ui_BinaryzationDlg.h"
#include <QMessageBox>
#include "PretreatMentListCollect/PretreatmentModuleItem.h"
#include "../../Global/UtilitiesFun.h"
#include "BinLimitDlg.h"
#include "ErosionDilateDlg.h"
#include "AcceCommon.h"
//#include "fpga_global.h"
#include "BwProcess.h"
void SetBinEnable(int flag,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_bin->m_pre_ptr;
    if(ptr == NULL)
        return;

    if(flag == 1)
    {
        ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_BW_MODEL_ID);

    }else
    {
        return;
        ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_BW_MODEL_ID);

    }
}
void SetBinDDREnable(int flag,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_BW_MODEL_ID,p_bin->m_step,flag);
}
void ListBinDlg(int itaskKind,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    BinLimitDlg dlg;
    dlg.m_task_id = itaskKind;
    dlg.m_step = p_bin->m_step;
    dlg.m_pre_ptr = p_bin->m_pre_ptr;
    dlg.m_listX = p_bin->m_listX;
    dlg.m_listY = p_bin->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    dlg.exec();
}
void SetErosionDilateAEnable(int flag,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_bin->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_EROSION_DILATE_MODEL1_ID);
        qDebug()<<"ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable =1;";

    }else
    {
        ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_EROSION_DILATE_MODEL1_ID);
        qDebug()<<"ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable =0;";
    }
}
void SetErosionDilateADDREnable(int flag,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_EROSION_DILATE_MODEL1_ID,p_bin->m_step,flag);
}
void ListErosionDilateADlg(int itaskKind,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    ErosionDilateDlg dlg;
    dlg.m_task_id = itaskKind;
    dlg.m_step = p_bin->m_step;
    dlg.m_pre_ptr = p_bin->m_pre_ptr;
    dlg.m_listX = p_bin->m_listX;
    dlg.m_listY = p_bin->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    dlg.exec();
}
void SetErosionDilateBEnable(int flag,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_bin->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_EROSION_DILATE_MODEL2_ID);

    }else
    {
        ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_EROSION_DILATE_MODEL2_ID);

    }
}
void SetErosionDilateBDDREnable(int flag,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_EROSION_DILATE_MODEL2_ID,p_bin->m_step,flag);
}
void ListErosionDilateBDlg(int itaskKind,void *Pdata)
{
    BinaryzationDlg *p_bin = (BinaryzationDlg*)Pdata;
    ErosionDilateDlg dlg;
    dlg.m_task_id = itaskKind;
    dlg.m_step = p_bin->m_step;
    dlg.m_pre_ptr = p_bin->m_pre_ptr;
    dlg.m_listX = p_bin->m_listX;
    dlg.m_listY = p_bin->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    dlg.exec();
}
BinaryzationDlg::BinaryzationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinaryzationDlg)
{
    ui->setupUi(this);
    m_image_out_src = 0;
    this->move(660,0);
    InitFunPtr();
}

BinaryzationDlg::~BinaryzationDlg()
{
    ClearList(ui->listWidget);
    delete ui;
}
void BinaryzationDlg::InitFunPtr()
{
    STRUCT_FUN_PTR binMode;
    binMode.List_model_dlg=ListBinDlg;
    binMode.Set_ddr_enable=SetBinDDREnable;
    binMode.Set_model_enable = SetBinEnable;
    m_fun_ptr.insert(ACCE_BW_MODEL_ID,binMode);

    STRUCT_FUN_PTR erosionDilateAMode;
    erosionDilateAMode.List_model_dlg=ListErosionDilateADlg;
    erosionDilateAMode.Set_ddr_enable=SetErosionDilateADDREnable;
    erosionDilateAMode.Set_model_enable = SetErosionDilateAEnable;
    m_fun_ptr.insert(ACCE_EROSION_DILATE_MODEL1_ID,erosionDilateAMode);

    STRUCT_FUN_PTR erosionDilateBMode;
    erosionDilateBMode.List_model_dlg=ListErosionDilateBDlg;
    erosionDilateBMode.Set_ddr_enable=SetErosionDilateBDDREnable;
    erosionDilateBMode.Set_model_enable = SetErosionDilateBEnable;
    m_fun_ptr.insert(ACCE_EROSION_DILATE_MODEL2_ID,erosionDilateBMode);

}
void BinaryzationDlg::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr ==NULL)
        return;
    m_bw_cfg = ptr->image_acce_param.bw_proc_model_cfg;
    AddItemData(tr("二值化"),ACCE_BW_MODEL_ID,ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.model_enable,0);
    SetBinEnable(ptr->image_acce_param.bw_proc_model_cfg.bw_model_cfg.model_enable,this);
    AddItemData(tr("腐蚀膨胀A"),ACCE_EROSION_DILATE_MODEL1_ID,ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable,1);
    SetErosionDilateAEnable(ptr->image_acce_param.bw_proc_model_cfg.ed_a_model_cfg.model_enable,this);
    AddItemData(tr("腐蚀膨胀B"),ACCE_EROSION_DILATE_MODEL2_ID,ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.model_enable,2);
    SetErosionDilateBEnable(ptr->image_acce_param.bw_proc_model_cfg.ed_b_model_cfg.model_enable,this);
    GetImageOutPut();

}
void BinaryzationDlg::OperateSlots(int iOperate, int itaskKind, int value, int current)
{
    ui->listWidget->setCurrentRow(current);

    switch (iOperate) {
    case PREENABLE:
        if(current == 0)
        {
            /*QListWidgetItem *item =  ui->listWidget->item(current);
            QWidget *qWidget = ui->listWidget->itemWidget(item);
            ((PretreatmentModuleItem*)qWidget)->SetControlEnable(1);*/
            ;

        }else
        {
            m_fun_ptr.value(itaskKind).Set_model_enable(value,this);
        }
        break;
    case PREDETAIL:
        m_fun_ptr.value(itaskKind).List_model_dlg(itaskKind,this);
        break;
    default:
        break;
    }
    GetImageOutPut();
}
void BinaryzationDlg::on_btnOk_clicked()
{
    QDialog::accept();
}
void BinaryzationDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.bw_proc_model_cfg = m_bw_cfg;
            AcceleratorModuleConfig(ACCE_BW_PROC_MODEL_ID,m_step);
        }

        QDialog::reject();
    }

}
void BinaryzationDlg::ClearList(QListWidget *pListWidget)
{
    int count = pListWidget->count();

    for(int i= 0; i<count;i++)
    {
        int row = pListWidget->count()-1;
        QListWidgetItem *itemdel= pListWidget->takeItem(row);
        delete itemdel;
    }
}
void BinaryzationDlg::AddItemData(QString strName, int index, int bCheck, int current)
{
    PretreatmentModuleItem *p_PretreatmentModuleItem = new PretreatmentModuleItem;
    p_PretreatmentModuleItem->setAttribute(Qt::WA_DeleteOnClose);
    p_PretreatmentModuleItem->SetInfoName(strName);
    p_PretreatmentModuleItem->m_taskKind = index;
    p_PretreatmentModuleItem->SetCheckdevalue(bCheck);
    p_PretreatmentModuleItem->m_current_row = current;
    int size =ui->listWidget->count();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(mItem,(QWidget*)p_PretreatmentModuleItem);
    ui->listWidget->item(size)->setSizeHint(QSize(340,50));
    ui->listWidget->setCurrentRow(size);
    connect(p_PretreatmentModuleItem,&PretreatmentModuleItem::SignalOperate,this,&BinaryzationDlg::OperateSlots);
}
int BinaryzationDlg::GetImageOutPut()
{
    BW_Process_Model_Out_Src_Auto_Set(m_step);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr !=NULL)
    {
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_BW_PROC_MODEL_ID;
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
    }
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
                //ptr->image_acce_param.bw_proc_model_cfg.bw_proc_wr_ddr_en=1;
                ptr->image_acce_param.bw_proc_model_cfg.bw_proc_src_sel = m_image_out_src;
                ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_BW_PROC_MODEL_ID;
                AcceleratorModuleConfig(ACCE_BW_PROC_MODEL_ID,m_step);
                AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
                //AcceleratorModuleCfgShow(ACCE_BW_PROC_MODEL_ID);
                AcceleratorModuleWriteDdrCfg(ACCE_BW_PROC_MODEL_ID,m_step,1);
                AcceleratorModuleEnable(ACCE_BW_PROC_MODEL_ID);
            }

            UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
            qDebug()<<"BinaryzationDlg x="<<m_listX<<","<<m_listY;
            break;
        }
    }
    return m_image_out_src;
}

