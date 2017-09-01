#include <qdebug.h>
#include "UtilitiesFun.h"
#include "System.h"
#include "Capture.h"
UtilitiesFun* UtilitiesFun::m_UtilitiesFun = NULL;
UtilitiesFun::UtilitiesFun(QObject *parent) : QObject(parent)
{
   timerUpData = new QTimer(this);
   connect(timerUpData,&QTimer::timeout,this,&UtilitiesFun::timeOutSlot);
   m_iPresstimes = 1;
   m_startx = 0;
   m_starty =0;
   m_endx = 640;
   m_endy = 480;
   m_cmos_starty = 0;
   m_coms_endy = 480;
   m_rotate_type = 0;
}
UtilitiesFun::~UtilitiesFun()
{
    if(NULL != timerUpData)
    {
        delete timerUpData;
        timerUpData = NULL;
    }
}
UtilitiesFun * UtilitiesFun::Instance()
{
    if(m_UtilitiesFun == NULL)
    {
        m_UtilitiesFun = new UtilitiesFun;
    }
    return m_UtilitiesFun;
}

void UtilitiesFun::timeOutSlot()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
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
    signalValue(value);

}
void UtilitiesFun::StartTimer(int time)
{
    m_iPresstimes = 0;

    if(!timerUpData->isActive())
    {
        timerUpData->start(time);
    }
}
void UtilitiesFun::StopTimer()
{
    m_iPresstimes = 1;
    if(timerUpData->isActive())
    {
        timerUpData->stop();
    }
}
void UtilitiesFun::ListVGA(int x,int y,int edited_status)
{
    /*SYSTEM_MODEL_CFG cfg;
    System_Model_Param_Init(&cfg);
    cfg.start_x = x;
    cfg.start_y = y;
    cfg.edited_status = edited_status;
    System_Model_Param_Set(&cfg);*/
    qDebug()<<"listVga x==="<<x<<"y==="<<y;
    Vga_XY_Edit_Status_Set(x, y,edited_status);
}
void UtilitiesFun::Set_rotate_type(int type)
{
    this->m_rotate_type = type;
}
void UtilitiesFun::SetStartX(int x)
{
    this->m_startx = x;
}
void UtilitiesFun::SetStartY(int y)
{
    this->m_starty = y;
}
void UtilitiesFun::SetEndX(int x)
{
    this->m_endx = x;
}
void UtilitiesFun::SetEndY(int y)
{
    this->m_endy = y;
}
void UtilitiesFun::SetCmosLimit(int starty,int endy)
{
    this->m_cmos_starty = starty;
    this->m_coms_endy = endy;
}
void UtilitiesFun::SetCptType(int type)
{
    this->m_cpt_type = type;
}
void UtilitiesFun::SetCPTCmosStartYAndHeight(int startx,int hegith,int type)
{
    Set_CPT_Cmos_Start_Y_And_Height(startx,hegith,type);
}
void UtilitiesFun::SetCPT(int flag, int x, int y, int w, int h)
{
    if(flag == CPT_CMOS_PIC)
    {
        Set_CPT_Model_Enable(1);
        Set_CPT_Roi_Enable(0);
        Set_CPT_Color_Wr_Ddr(1);
        Set_CPT_Mono_Wr_Ddr(1);
        Set_CPT_Pic_Src_Sel(0);

        if(m_rotate_type == 0 || m_rotate_type == 1)
            SetCPTCmosStartYAndHeight(m_cmos_starty,m_coms_endy-m_cmos_starty,m_rotate_type);
        else if(m_rotate_type == 2 || m_rotate_type == 3)
            SetCPTCmosStartYAndHeight(480-m_coms_endy,m_coms_endy-m_cmos_starty,m_rotate_type);

    }else if(flag == CPT_DDR_PIC)
    {
        Set_CPT_Model_Enable(1);
        Set_CPT_Roi_Enable(1);
        Set_CPT_Mono_Wr_Ddr(0);
        Set_CPT_Color_Wr_Ddr(0);
        Set_CPT_Pic_Src_Sel(1);
        SetCPTCmosStartYAndHeight(0,480,m_rotate_type);
    }

    if(flag == CPT_DDR_PIC)
    {
        Set_CPT_Pic_In_Src_A_Start_X(x);
        Set_CPT_Pic_In_Src_A_Start_Y(y);
        Set_CPT_Pic_In_Src_A_Width(w);
        Set_CPT_Pic_In_Src_A_Height(h);
    }else
    {
        Set_CPT_Pic_In_Src_A_Start_X(0);
        Set_CPT_Pic_In_Src_A_Start_Y(0);
        Set_CPT_Pic_In_Src_A_Width(640);
        Set_CPT_Pic_In_Src_A_Height(480);
    }
    Set_CPT_Pic_In_Src_B_Start_X(0);
    Set_CPT_Pic_In_Src_B_Start_Y(0);
    Set_CPT_Pic_In_Src_B_Width(640);
    Set_CPT_Pic_In_Src_B_Height(480);
}

