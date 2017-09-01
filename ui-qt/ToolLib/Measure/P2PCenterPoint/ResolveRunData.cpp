#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
#include <QTime>
ResolveRunData::ResolveRunData()
{
    m_ok_cnt = 0;
    m_ng_cnt = 0;
    m_excute_flag = 1;
}
ResolveRunData::~ResolveRunData()
{

}

/**
 * @brief ResolveRunData::Paint
 * @param paint
 * @param step 任务步骤号
 * @author dgq
 * @note 运行画OSD
 */
void ResolveRunData::Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    PEN_STYLE_RUN *pen = (PEN_STYLE_RUN *)penStyle;
    if(!m_excute_flag)
    {
        return;
    }
    paint->setPen(pen->pen_ok_solidLine);
    paint->drawEllipse(m_line.p1(),10,10);
    paint->drawLine(m_line.p1().x()+20,m_line.p1().y(),m_line.p1().x()-20,m_line.p1().y());
    paint->drawLine(m_line.p1().x(),m_line.p1().y()+20,m_line.p1().x(),m_line.p1().y()-20);
    paint->drawEllipse(m_line.p2(),10,10);
    paint->drawLine(m_line.p2().x()+20,m_line.p2().y(),m_line.p2().x()-20,m_line.p2().y());
    paint->drawLine(m_line.p2().x(),m_line.p2().y()+20,m_line.p2().x(),m_line.p2().y()-20);

    paint->setPen(pen->pen_ok_dashLine);
    paint->drawLine(m_line);
    paint->drawLine(QPoint(m_mid_point.x()-10,m_mid_point.y()-10),QPoint(m_mid_point.x()+10,m_mid_point.y()+10));
    paint->drawLine(QPoint(m_mid_point.x()+10,m_mid_point.y()-10),QPoint(m_mid_point.x()-10,m_mid_point.y()+10));

}

/**
 * @brief ResolveRunData::GetHead
 * @param step 任务步骤号
 * @author dgq
 * @return 返回任务运行通用输出数据信息
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    PPMP_OUTPUT_PARAM* pRunPara = (PPMP_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:两点中点";
    info.strValue = "\r\n";
    vt.append(info);

    if(pRunPara->common_param.err_type_id != 0)
    {
        info.strName = "执行结果:";
        info.strValue = "NG";
    }else
    {

        info.strName = "执行结果:";
        info.strValue = "OK";
    }
    vt.append(info);
    info.strName = "OK计数:";
    info.strValue = QString::number(pRunPara->common_param.OK_count);
    vt.append(info);
    info.strName = "NG计数:";
    info.strValue = QString::number(pRunPara->common_param.NG_count);
    vt.append(info);
    info.strName = "运行时间:";
    info.strValue = QString::number(pRunPara->common_param.step_cost_time)+"ms";
    vt.append(info);

    if((m_ok_cnt == 0 && m_ng_cnt == 0) || (m_ok_cnt > pRunPara->common_param.OK_count || m_ng_cnt > pRunPara->common_param.NG_count))
    {
        m_ok_cnt = pRunPara->common_param.OK_count;
        m_ng_cnt = pRunPara->common_param.NG_count;
        m_excute_flag = 0;
        return vt;
    }
    if(m_ok_cnt < (int)pRunPara->common_param.OK_count)
    {
        m_ok_cnt = pRunPara->common_param.OK_count;
        m_excute_flag = 1;
    }
    else if(m_ng_cnt < (int)pRunPara->common_param.NG_count)
    {
        m_ng_cnt = pRunPara->common_param.NG_count;
        m_excute_flag = 1;
    }else
    {
        m_excute_flag = 0;
    }

    return vt;
}

/**
 * @brief ResolveRunData::GetContent
 * @param step 任务步骤号
 * @return 返回运行时数据信息字符串
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    *count =1;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
//    if(pRstData->resultflag)//该数据有效
    {
        int pix_vga_x = 0;
        int pix_vga_y = 0;
        int pix_real_x = 0;
        int pix_real_y = 0;
        float pix_sub_x = 0.0;
        float pix_sub_y = 0.0;
        info.strName = "中点坐标(像素):";
        pix_sub_x = pRstData[PPMP_POINT_M_X_ID].value.F32_Value;
        pix_sub_y = pRstData[PPMP_POINT_M_Y_ID].value.F32_Value;
        PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
        PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
        PixelCvt(&pix_sub_x,&pix_real_x,CVT_SUB2REAL|CVT_F2I|CVT_DATA);
        PixelCvt(&pix_sub_y,&pix_real_y,CVT_SUB2REAL|CVT_F2I|CVT_DATA);
        m_mid_point.setX(pix_vga_x);
        m_mid_point.setY(pix_vga_y);
        info.strValue = "("+QString::number(pix_real_x)+","+\
                QString::number(pix_real_y)+")";
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);

        info.strName = "中点坐标(物理):";
        info.strValue = "("+QString::number(pRstData[PPMP_POINT_M_X_PHY_ID].value.F32_Value)+","+\
                QString::number(pRstData[PPMP_POINT_M_Y_PHY_ID].value.F32_Value)+")";
        vt.append(info);
        GetMesureOsdData(step);
    }
    return vt;
}

/**
 * @brief ResolveRunData::GetMesureOsdData
 * @author dgq
 * @note 获取测量任务运行时的OSD数据
 */
void ResolveRunData::GetMesureOsdData(int i_step)
{

    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step);
    int i_task1_index = pStephead->step_link.link_info[0].step_index;
    int i_result1_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = pStephead->step_link.link_info[1].step_index;
    int i_result2_index = pStephead->step_link.link_info[1].result_index;
    float point_pix_vga_x = 0.0;
    float point_pix_vga_y = 0.0;
    float point_pix_sub_x = 0.0;
    float point_pix_sub_y = 0.0;
    POINT_F pointf;
    int ret = measure_ref_point_result_get(i_task1_index,i_result1_index,&pointf,0);
    if(ret != 0)
    {
        return;
    }
    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    m_line.setP1(QPoint(point_pix_vga_x,point_pix_vga_y));
    ret = measure_ref_point_result_get(i_task2_index,i_result2_index,&pointf,0);
    if(ret != 0)
    {
        return;
    }
    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    m_line.setP2(QPoint(point_pix_vga_x,point_pix_vga_y));
}

