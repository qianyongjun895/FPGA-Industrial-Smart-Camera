#include <qdebug.h>
#include "CptDlg.h"
#include "ui_CptDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
//#include "Hardware_Init.h"
#include "cmos_common.h"

CptDlg::CptDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CptDlg)
{
    ui->setupUi(this);
    m_pre_ptr = NULL;
    m_img_scale =1;
    m_startY = 0;
    m_endY = 480;
    connect(ui->labelPic,&CptPreLabel::SingalUpdateXY,this,&CptDlg::SlotUpdateXY);
    ui->labelPic->UpdateTwoLineY(UtilitiesFun::Instance()->GetCmosStartY(),UtilitiesFun::Instance()->GetCmosEndY());
    m_startY = UtilitiesFun::Instance()->GetCmosStartY();
    m_endY = UtilitiesFun::Instance()->GetCmosEndY();
    pen = NULL;
}
CptDlg::~CptDlg()
{
    disconnect(this,0,0,0);
    UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y(),0xffffffff);
    delete ui;
}
void CptDlg::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {

        m_cfg = ptr->image_acce_param.cpt_model_cfg;

        if(ptr->image_acce_param.cpt_model_cfg.mono_pic_wr_ddr_en == 1)
        {
            ui->checkBoxGray->setChecked(true);
        }else
        {
            ui->checkBoxGray->setChecked(false);
        }
        iLeftTopX = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_start_x / m_img_scale ;
        iLeftTopY = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_start_y / m_img_scale ;

        if(iLeftTopX < 0 || iLeftTopX > 640)
            iLeftTopX= 10;
        if(iLeftTopY < m_startY || iLeftTopY > m_endY)
            iLeftTopY= m_startY;

        iBottomRightX = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_width / m_img_scale + iLeftTopX;
        iBottomRightY = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_height/ m_img_scale + iLeftTopY;

        if(iBottomRightX<=iLeftTopX+10 || iBottomRightX > 640)
        {
            if(iLeftTopX==10)
                iBottomRightX =iLeftTopX+620;
            else
                iBottomRightX = 630-iLeftTopX;
        }

        if(iBottomRightY <=iLeftTopY+10 || iBottomRightY > m_endY)
            iBottomRightY =m_endY;

        if(ptr->image_acce_param.cpt_model_cfg.pic_src_sel==0)
        {
            ui->radioButtonCmos->setChecked(true);
            ui->radioButtonDDR->setChecked(false);
            ui->radioButtonBottomRight->setChecked(false);
            ui->radioButtonLeftTop->setChecked(false);

            ui->labelPic->SetCptFlag(2);
            ui->labelPic->SetARect(-10,-10,-10,-10);
            ui->groupBoxAdjustMent->setVisible(false);
        }else
        {
            ui->radioButtonCmos->setChecked(false);
            ui->radioButtonDDR->setChecked(true);
            ui->labelPic->SetCptFlag(0);
            ui->labelPic->SetARect(iLeftTopX,iLeftTopY,iBottomRightX,iBottomRightY);
            ui->groupBoxAdjustMent->setVisible(true);
            SetLefTopXY(iLeftTopX,iLeftTopY);
            SetBottomRightXY(iBottomRightX,iBottomRightY);
            ui->radioButtonBottomRight->setChecked(false);
            ui->radioButtonLeftTop->setChecked(true);
        }

        int pic_channel = ptr->image_acce_param.cpt_model_cfg.pic_channel ;
        switch (pic_channel) {
        case 0:
            ui->radioButtonBrightWay->setChecked(true);
            ui->radioButtonRWay->setChecked(false);
            ui->radioButtonGWay->setChecked(false);
            ui->radioButtonBWay->setChecked(false);
            break;
        case 1:
            ui->radioButtonBrightWay->setChecked(false);
            ui->radioButtonRWay->setChecked(true);
            ui->radioButtonGWay->setChecked(false);
            ui->radioButtonBWay->setChecked(false);
            break;
        case 2:
            ui->radioButtonBrightWay->setChecked(false);
            ui->radioButtonRWay->setChecked(false);
            ui->radioButtonGWay->setChecked(true);
            ui->radioButtonBWay->setChecked(false);
            break;
        case 3:
            ui->radioButtonBrightWay->setChecked(false);
            ui->radioButtonRWay->setChecked(false);
            ui->radioButtonGWay->setChecked(false);
            ui->radioButtonBWay->setChecked(true);
            break;
        default:
            break;
        }

        if(Get_HWC_Color_Type()==1)//彩色相机
        {
            ui->groupBoxWay->setVisible(true);
        }else
        {
            ui->groupBoxWay->setVisible(false);
        }
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_CPT_MODEL_ID;
        ptr->image_acce_param.cpt_model_cfg.model_enable =1;
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(ui->labelPic->x(),ui->labelPic->y(),ACCE_CPT_MODEL_ID);
        ui->labelPic->SetPen(pen);
    }
}
void CptDlg::on_btnOk_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr != NULL)
    {
        int ix =  ui->labelPic->GetALeftTopX() * m_img_scale;
        int iy = ui->labelPic->GetALeftTopY() * m_img_scale;
        int iWidth = ui->labelPic->GetARectWidth() * m_img_scale;
        int iHeight = ui->labelPic->GetARectHeight() * m_img_scale;

        if(ui->radioButtonDDR->isChecked())
        {
            /*if(m_task_id == TASK_ID_MATCH_SKELETON)
            {
                ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.pic_in_src_a_start_x = 0;
                ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.pic_in_src_a_start_y = 0;
                ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.pic_in_src_a_width = 640*m_img_scale;
                ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.pic_in_src_a_height = 480*m_img_scale;

            }else*/
            {
                ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_start_x = ix;
                ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_start_y= iy;
                ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_width= iWidth;
                ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_height= iHeight;
            }
            qDebug()<<"iWidth ==="<<iWidth<<"iHeigth=="<<iHeight;
            UtilitiesFun::Instance()->SetStartX(ix);
            UtilitiesFun::Instance()->SetStartY(iy);
            UtilitiesFun::Instance()->SetEndX(iWidth+ix);
            UtilitiesFun::Instance()->SetEndY(iHeight+iy);
            UtilitiesFun::Instance()->SetCptType(CPT_DDR_PIC);
            ptr->image_acce_param.cpt_model_cfg.roi_model_en = 1;

        }else
        {
            ptr->image_acce_param.cpt_model_cfg.roi_model_en = 0;
            UtilitiesFun::Instance()->SetStartX(0);
            UtilitiesFun::Instance()->SetStartY(UtilitiesFun::Instance()->GetCmosStartY());
            UtilitiesFun::Instance()->SetEndX(640);
            UtilitiesFun::Instance()->SetEndY(UtilitiesFun::Instance()->GetCmosEndY());
            UtilitiesFun::Instance()->SetCptType(CPT_DDR_PIC);
        }

        /*if(m_CGetImageThread->m_iSensorType != SENSORTYPERGB)
            ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.mono_pic_save_addr =m_CGetImageThread->m_image_adr.cpt_mono_pic_addr;*/
        AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
    }
    QDialog::accept();
}
void CptDlg::SetAreaLimit()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        iLeftTopX = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_start_x / m_img_scale ;
        iLeftTopY = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_start_y / m_img_scale ;

        if(iLeftTopX < 0 || iLeftTopX > 640)
            iLeftTopX= 10;
        if(iLeftTopY < m_startY || iLeftTopY > m_endY)
            iLeftTopY= m_startY;

        iBottomRightX = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_width / m_img_scale + iLeftTopX;
        iBottomRightY = ptr->image_acce_param.cpt_model_cfg.ddr_src_a_roi.roi_height/ m_img_scale + iLeftTopY;

        if(iBottomRightX<=iLeftTopX+10 || iBottomRightX > 640)
        {
            if(iLeftTopX==10)
                iBottomRightX =iLeftTopX+620;
            else
                iBottomRightX = 630-iLeftTopX;
        }

        if(iBottomRightY <=iLeftTopY+10 || iBottomRightY > m_endY)
            iBottomRightY =m_endY;

        if(ptr->image_acce_param.cpt_model_cfg.pic_src_sel==0)
        {
            UtilitiesFun::Instance()->SetStartX(0);
            UtilitiesFun::Instance()->SetStartY(UtilitiesFun::Instance()->GetCmosStartY());
            UtilitiesFun::Instance()->SetEndX(640);
            UtilitiesFun::Instance()->SetEndY(UtilitiesFun::Instance()->GetCmosEndY());

        }else
        {
            UtilitiesFun::Instance()->SetStartX(iLeftTopX);
            UtilitiesFun::Instance()->SetStartY(iLeftTopY);
            UtilitiesFun::Instance()->SetEndX(iBottomRightX);
            UtilitiesFun::Instance()->SetEndY(iBottomRightY);
        }
    }
}
void CptDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.cpt_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
        }

        QDialog::reject();
    }
    QDialog::reject();
}
void CptDlg::SlotUpdateXY()
{
    iLeftTopX =  ui->labelPic->GetALeftTopX();
    iLeftTopY =  ui->labelPic->GetALeftTopY();
    iBottomRightX = ui->labelPic->GetABottomRightX();
    iBottomRightY = ui->labelPic->GetABottomRightY();
    SetLefTopXY(iLeftTopX,iLeftTopY);
    SetBottomRightXY(iBottomRightX,iBottomRightY);
}
//cmos
void CptDlg::on_radioButtonCmos_clicked()
{
   ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

   if(ptr !=NULL)
   {
       ptr->image_acce_param.cpt_model_cfg.pic_src_sel = 0;
       AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
   }

    ui->labelPic->SetCptFlag(1);
    if(ui->checkBoxGray->isChecked())
    {
        SetPreDataColor(1);
    }else
    {
        SetPreDataColor(0);
    }

    ui->radioButtonBottomRight->setChecked(false);
    ui->radioButtonLeftTop->setChecked(false);
    ui->groupBoxAdjustMent->setVisible(false);
    ui->labelPic->SetCptFlag(2);
    ui->labelPic->SetARect(-10,-10,-10,-10);

}
//ddr
void CptDlg::on_radioButtonDDR_clicked()
{
    ui->labelPic->SetCptFlag(0);
    ui->labelPic->SetARect(iLeftTopX,iLeftTopY,iBottomRightX,iBottomRightY);
    SetLefTopXY(iLeftTopX,iLeftTopY);
    SetBottomRightXY(iBottomRightX,iBottomRightY);
    ui->radioButtonBottomRight->setChecked(false);
    ui->radioButtonLeftTop->setChecked(true);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr !=NULL)
    {
        ptr->image_acce_param.cpt_model_cfg.pic_src_sel = 1;
        ptr->image_acce_param.cpt_model_cfg.mono_pic_wr_ddr_en = 0;
        ptr->image_acce_param.cpt_model_cfg.color_pic_wr_ddr_en = 0;
        AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
    }
    /*if(m_task_id == TASK_ID_MATCH_SKELETON)
    {
        ui->groupBoxAdjustMent->setVisible(false);
    }else*/
    {
        ui->groupBoxAdjustMent->setVisible(true);
    }
}
void CptDlg::SetLefTopXY(int x,int y)
{
    QString strTemp = "(";
    strTemp += QString::number(x);
    strTemp +=",";
    strTemp += QString::number(y);
    strTemp +=")";
    ui->labelLeftTop->setText(strTemp);
}
void CptDlg::SetBottomRightXY(int x,int y)
{
    QString strTemp = "(";
    strTemp += QString::number(x);
    strTemp +=",";
    strTemp += QString::number(y);
    strTemp +=")";
    ui->labelBottomRight->setText(strTemp);
}
void CptDlg::on_btnSkeletonUp_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::keyUp);
    UtilitiesFun::Instance()->StartTimer(100);
}

void CptDlg::on_btnSkeletonDown_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::KeyDown);
    UtilitiesFun::Instance()->StartTimer(100);
}

void CptDlg::on_btnSkeletonLeft_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::KeyLeft);
    UtilitiesFun::Instance()->StartTimer(100);
}

void CptDlg::on_btnSkeletonRight_pressed()
{
    connect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::KeyRight);
    UtilitiesFun::Instance()->StartTimer(100);
}
void CptDlg::keyUp(int value)
{
    if(ui->radioButtonLeftTop->isChecked())
    {
        ui->labelPic->UpAdjustment(CptPreLabel::LeftTop,value);

    }else if(ui->radioButtonBottomRight->isChecked())
    {
         ui->labelPic->UpAdjustment(CptPreLabel::RightBottom,value);
    }
}
void CptDlg::KeyDown(int value)
{
    if(ui->radioButtonLeftTop->isChecked())
    {
       ui->labelPic->DownAdjustment(CptPreLabel::LeftTop,value);

    }else if(ui->radioButtonBottomRight->isChecked())
    {
        ui->labelPic->DownAdjustment(CptPreLabel::RightBottom,value);
    }
}
void CptDlg::KeyLeft(int value)
{
    if(ui->radioButtonLeftTop->isChecked())
    {
        ui->labelPic->LeftAdjustment(CptPreLabel::LeftTop,value);

    }else if(ui->radioButtonBottomRight->isChecked())
    {
        ui->labelPic->LeftAdjustment(CptPreLabel::RightBottom,value);
    }
}
void CptDlg::KeyRight(int value)
{
    if(ui->radioButtonLeftTop->isChecked())
    {
        ui->labelPic->RightAdjustment(CptPreLabel::LeftTop,value);
    }else if(ui->radioButtonBottomRight->isChecked())
    {
        ui->labelPic->RightAdjustment(CptPreLabel::RightBottom,value);
    }
}
void CptDlg::on_btnSkeletonUp_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::keyUp);
    keyUp();
}
void CptDlg::on_btnSkeletonDown_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::KeyDown);
    KeyDown();
}
void CptDlg::on_btnSkeletonLeft_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::KeyLeft);
    KeyLeft();
}
void CptDlg::on_btnSkeletonRight_released()
{
    UtilitiesFun::Instance()->StopTimer();
    disconnect(UtilitiesFun::Instance(),&UtilitiesFun::signalValue,this,&CptDlg::KeyRight);
    KeyRight();
}
void CptDlg::SetPreDataColor(int bColor)
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr !=NULL)
    {
        if(bColor ==0)
        {
            ptr->image_acce_param.cpt_model_cfg.mono_en = 0;
            qDebug()<<"ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.mono_en = 0;";
            if(Get_HWC_Color_Type()==1)//彩色相机
            //if(1)
            {
                ptr->image_acce_param.cpt_model_cfg.mono_pic_wr_ddr_en = 0;
                ptr->image_acce_param.cpt_model_cfg.color_pic_wr_ddr_en = 1;
                //ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.color_pic_save_addr =m_CGetImageThread->m_image_adr.cpt_color_pic_addr;
                ptr->image_acce_param.cpt_model_cfg.pic_channel = 0;
                ui->radioButtonBrightWay->setChecked(true);
            }
            else
            {
                ptr->image_acce_param.cpt_model_cfg.mono_pic_wr_ddr_en = 1;
                ptr->image_acce_param.cpt_model_cfg.color_pic_wr_ddr_en = 0;
                //ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.mono_pic_save_addr =m_CGetImageThread->m_image_adr.cpt_mono_pic_addr;
            }
        }
        else
        {
            ptr->image_acce_param.cpt_model_cfg.mono_en = 1;
            qDebug()<<"ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.mono_en = 1;";
            if(Get_HWC_Color_Type()==1)//彩色相机
            //if(1)
            {
                ptr->image_acce_param.cpt_model_cfg.mono_pic_wr_ddr_en = 1;
                ptr->image_acce_param.cpt_model_cfg.color_pic_wr_ddr_en = 1;
            }else
            {
                ptr->image_acce_param.cpt_model_cfg.mono_pic_wr_ddr_en = 1;
                ptr->image_acce_param.cpt_model_cfg.color_pic_wr_ddr_en = 0;
            }
            //ptr->image_acce_param.pre_model_cfg.cpt_model_cfg.mono_pic_save_addr =m_CGetImageThread->m_image_adr.cpt_mono_pic_addr;
        }
         qDebug()<<"AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);";
        AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
    }
}

void CptDlg::on_checkBoxGray_clicked()
{
    if(ui->checkBoxGray->isChecked())
    {

        SetPreDataColor(1);

    }else
    {

        SetPreDataColor(0);
    }
}

void CptDlg::on_radioButtonBrightWay_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr ==NULL)
    {
        return;
    }
    ptr->image_acce_param.cpt_model_cfg.pic_channel =0;
    AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
}

void CptDlg::on_radioButtonRWay_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr ==NULL)
    {
        return;
    }
    ptr->image_acce_param.cpt_model_cfg.pic_channel =1;
    AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
}

void CptDlg::on_radioButtonGWay_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr ==NULL)
    {
        return;
    }
    ptr->image_acce_param.cpt_model_cfg.pic_channel =2;
    AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
}

void CptDlg::on_radioButtonBWay_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr ==NULL)
    {
        return;
    }
    ptr->image_acce_param.cpt_model_cfg.pic_channel =3;
    AcceleratorModuleConfig(ACCE_CPT_MODEL_ID,m_step);
}

