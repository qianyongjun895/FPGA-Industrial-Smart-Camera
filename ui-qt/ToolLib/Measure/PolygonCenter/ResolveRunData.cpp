#include "QDebug"
#include "ResolveRunData.h"

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
    paint->drawLine(m_point.x()+10,m_point.y(),m_point.x()-10,m_point.y());
    paint->drawLine(m_point.x(),m_point.y()+10,m_point.x(),m_point.y()-10);
    paint->drawLine(line1);
    paint->drawLine(line2);
    paint->drawLine(line3);
    paint->drawLine(line4);
}

QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    PYG_CENTER_OUTPUT_PARAM *pRunPara = (PYG_CENTER_OUTPUT_PARAM *)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:多边形中心";
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
        info.strName = "中心坐标(像素):";
        pix_sub_x = pRstData[PYG_CENTER_POINT_X_ID].value.F32_Value;
        pix_sub_y = pRstData[PYG_CENTER_POINT_Y_ID].value.F32_Value;
        PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
        PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
        PixelCvt(&pix_sub_x,&pix_real_x,CVT_SUB2REAL|CVT_F2I|CVT_DATA);
        PixelCvt(&pix_sub_y,&pix_real_y,CVT_SUB2REAL|CVT_F2I|CVT_DATA);
        m_point.setX(pix_vga_x);
        m_point.setY(pix_vga_y);
        info.strValue = "("+QString::number(pix_vga_x)+","+\
                QString::number(pix_vga_y)+")";
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);

        info.strName = "中心坐标(物理):";
        info.strValue = "("+QString::number(pRstData[PYG_CENTER_POINT_PHY_X_ID].value.F32_Value)+","+\
                QString::number(pRstData[PYG_CENTER_POINT_PHY_Y_ID].value.F32_Value)+")";
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
    LineParameter pLine1Para;
    LineParameter pLine2Para;
    LineParameter pLine3Para;
    LineParameter pLine4Para;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step);
    int i_task1_index = (int)pStephead->step_link.link_info[0].step_index;
    int i_result1_index = (int)pStephead->step_link.link_info[0].result_index;
    int i_task2_index =(int) pStephead->step_link.link_info[1].step_index;
    int i_result2_index = (int)pStephead->step_link.link_info[1].result_index;
    int i_task3_index =(int) pStephead->step_link.link_info[2].step_index;
    int i_result3_index = (int)pStephead->step_link.link_info[2].result_index;
    int i_task4_index = 0;
    int i_result4_index = 0;
    m_line_cnt = (int)pStephead->step_link.link_count;
    if(m_line_cnt == 4)
    {
        i_task4_index =(int) pStephead->step_link.link_info[3].step_index;
        i_result4_index = (int)pStephead->step_link.link_info[3].result_index;
        measure_ref_line_result_get(i_task2_index,i_result2_index,(void*)&pLine2Para,0);
        Line_Osd_Init(&pLine4Para,&line4);
    }
    else
    {
        line4 = QLine(-10,-10,-10,-10);
    }

    int ret = measure_ref_line_result_get(i_task1_index,i_result1_index,(void*)&pLine1Para,0);
    Line_Osd_Init(&pLine1Para,&line1);
    if(ret != 0)
    {
        return;
    }
    ret = measure_ref_line_result_get(i_task2_index,i_result2_index,(void*)&pLine2Para,0);
    Line_Osd_Init(&pLine2Para,&line2);
    if(ret != 0)
    {
        return;
    }
    ret = measure_ref_line_result_get(i_task3_index,i_result3_index,(void*)&pLine3Para,0);
    Line_Osd_Init(&pLine3Para,&line3);
    if(ret != 0)
    {
        return;
    }
}

/**
 * @brief ResolveRunData::Line_Paint_Base_On_KB_SubPixel
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点的子函数
 */
int ResolveRunData::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
{
    int i = 0;
    int count = 0;
    QPointF calc_point[4];

    calc_point[0].setX(0);
    calc_point[0].setY(b_f);
    /* Point1 x=640, calculate y  */
    calc_point[1].setX(VGA_WIDTH);
    calc_point[1].setY(k_f*VGA_WIDTH+b_f);
    /* Point1 y=0, calculate x  */
    calc_point[2].setX((0-b_f)/k_f);
    calc_point[2].setY(0);
    /* Point1 y=480, calculate x  */
    calc_point[3].setX((VGA_HEIGHT-b_f)/k_f);
    calc_point[3].setY(VGA_HEIGHT);

    for(i = 0; i < 4; i++)
    {
        //DRV_PRINT(LOCATION_DEBUG, "point%d: x=%d, y=%d\n", i, (int)calc_point[i].x_f, (int)calc_point[i].y_f);
        if(calc_point[i].x()>=0 && calc_point[i].x()<=VGA_WIDTH && calc_point[i].y()>=0 && calc_point[i].y()<=VGA_HEIGHT)
        {
            if(count == 0)
            {
                count++;
                pOsd_line->setP1(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
            else
            {
                pOsd_line->setP2(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
        }
    }

    return 0;
}

/**
 * @brief ResolveRunData::Line_Osd_Init
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点
 */
int ResolveRunData::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
{
    float line_kf = 0;
    float line_bf = 0;
    float line_k, line_b;

    float pix_vga_y = 0.0;
    float pix_vga_x = 0.0;
    float pix_sub_y = (float)pLinePara->y;
    float pix_sub_x = (float)pLinePara->x;
    PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    line_kf = tan(pLinePara->theta);
//    line_bf = (X_Y_CONVERT_SUB2UI((float)pLinePara->y) - line_kf * X_Y_CONVERT_SUB2UI((float)pLinePara->x));
    line_bf = (pix_vga_y - line_kf * pix_vga_x);
    line_k = (int)(line_kf*10000);
    line_b = (int)(line_bf*10000);

    if(line_k == 0x7fffffff || line_k == 0x80000000 || line_b == 0x7fffffff || line_b == 0x80000000)
    {
//        Vertical_Line_Paint((unsigned int)pLinePara->x, pOsdLine);

        pOsdLine->setP1(QPoint(pix_vga_x,0));
        pOsdLine->setP2(QPoint(pix_vga_x,VGA_HEIGHT));
    }else
    {
        Line_Paint_Base_On_KB_SubPixel(line_kf, line_bf, pOsdLine);
    }

    return 0;
}
