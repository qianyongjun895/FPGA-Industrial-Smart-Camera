#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
#include <QVector>
#include "PixelConvert.h"
#include "AreaSelect.h"
#include <qmath.h>

ResolveRunData::ResolveRunData()
{
    m_line_cnt = 0;
    m_ok_cnt = 0;
    m_ng_cnt = 0;
    m_excute_flag = 1;
}
ResolveRunData::~ResolveRunData()
{

}
void ResolveRunData::Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    PEN_STYLE_RUN *pen = (PEN_STYLE_RUN *)penStyle;
    paint->setPen(pen->pen_ok_solidLine);

    for(int i = 0; i < m_line_cnt;i++)
    {
        paint->drawLine(m_line[i]);
    }
    if(!m_excute_flag)
    {
        return;
    }
    if(paintAreaSelect == LIST_NG_ROI)
    {
        if(!m_ok_ng_flag)
            GetPreData(paint,step,1);
    }else if(paintAreaSelect == LIST_OK_ROI)
    {
        if(m_ok_ng_flag)
            GetPreData(paint,step,1);
    }else if(paintAreaSelect ==  LIST_NG_OK_ROI)
    {
        GetPreData(paint,step,1);
    }
}
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    pRunPara = (LINE_OUTPUT_PARAM *)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE value;
    value.strName = "任务名称:直线定位";
    value.strValue = "\n";
    vt.append(value);

    if(pRunPara->common_param.err_type_id != 0)
    {
        m_ok_ng_flag = 0;
        value.strName = "执行结果:";
        value.strValue = "NG";
    }else
    {
        m_ok_ng_flag = 1;
        value.strName = "执行结果:";
        value.strValue = "OK";
    }
    vt.append(value);
    value.strName = "OK计数:";
    value.strValue = QString::number(pRunPara->common_param.OK_count);
    vt.append(value);
    value.strName = "NG计数:";
    value.strValue = QString::number(pRunPara->common_param.NG_count);
    vt.append(value);
    value.strName = "运行时间:";
    value.strValue = QString::number(pRunPara->common_param.step_cost_time)+"ms";
    vt.append(value);

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
    QVector<STRU_KEY_VALUE> vt;

    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);

    RST_VALUE_STRUCT *pRstTemp = NULL;

    STRU_KEY_VALUE info;
//    if(pRstData->resultflag)//该数据有效
    {
        m_line_cnt = pRstData[LINE_NUM].value.I32_Value;
        *count = m_line_cnt;
        if(m_line_cnt > 20)
        {
            m_line_cnt = 0;
        }

        int id = 0;
        for(int i = 0; i < m_line_cnt; i++)
        {
            id = 10*i;
            pRstTemp = &pRstData[id];
            m_line_para[i].theta = pRstTemp[LINE0_THETA_ID].value.D64_Value;
            m_line_para[i].degree = pRstTemp[LINE0_DEGREE_ID].value.D64_Value;
            m_line_para[i].rotate_deg = pRstTemp[LINE0_ROTATE_DEG_ID].value.D64_Value;
            m_line_para[i].cos = pRstTemp[LINE0_COS_ID].value.D64_Value;
            m_line_para[i].sin = pRstTemp[LINE0_SIN_ID].value.D64_Value;
            m_line_para[i].x = pRstTemp[LINE0_PIXEL_X_ID].value.D64_Value;
            m_line_para[i].y = pRstTemp[LINE0_PIXEL_Y_ID].value.D64_Value;
            m_line_para[i].phy_x = pRstTemp[LINE0_PHY_X_ID].value.D64_Value;
            m_line_para[i].phy_y = pRstTemp[LINE0_PHY_Y_ID].value.D64_Value;
            Line_Osd_Init(&m_line_para[i],&m_line[i]);
        }
        if(index <= m_line_cnt)
        {
            int m_line_index = index-1;
            int pix_real_x = 0;
            int pix_real_y = 0;
            int pix_vga_x = m_line[m_line_index].p1().x();
            int pix_vga_y = m_line[m_line_index].p1().y();
            PixelCvt(&pix_vga_x,&pix_real_x,CVT_VGA2REAL|CVT_I2I|CVT_DATA);
            PixelCvt(&pix_vga_y,&pix_real_y,CVT_VGA2REAL|CVT_I2I|CVT_DATA);
            info.strName = "直线"+QString::number(index)+"点1坐标(像素):";

            info.strValue = "("+QString::number(pix_real_x)+","+QString::number(pix_real_y)+")";
            vt.append(info);

            info.strName = " ";
            info.strValue = " ";
            vt.append(info);
            pix_vga_x = m_line[index].p2().x();
            pix_vga_y = m_line[index].p2().y();
            PixelCvt(&pix_vga_x,&pix_real_x,CVT_VGA2REAL|CVT_I2I|CVT_DATA);
            PixelCvt(&pix_vga_y,&pix_real_y,CVT_VGA2REAL|CVT_I2I|CVT_DATA);
            info.strName = "直线"+QString::number(index)+"点2坐标(像素):";
            info.strValue = "("+QString::number(pix_real_x)+","+QString::number(pix_real_y)+")";
            vt.append(info);

            info.strName = " ";
            info.strValue = " ";
            vt.append(info);
            info.strName = "直线"+QString::number(index)+"弧度:";
            info.strValue = QString::number(m_line_para[m_line_index].theta);
            vt.append(info);
            info.strName = " ";
            info.strValue = " ";
            vt.append(info);
            info.strName = "直线"+QString::number(index)+"角度:";
            info.strValue = QString::number(m_line_para[m_line_index].degree);
            vt.append(info);
            info.strName = " ";
            info.strValue = " ";
            vt.append(info);
            info.strName = "直线"+QString::number(index)+"旋转角度:";
            info.strValue = QString::number(m_line_para[m_line_index].rotate_deg);
            vt.append(info);
        }
    }
    return vt;
}
#if 1

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
    line_bf = (pix_vga_y - line_kf * pix_vga_x);
    line_k = (int)(line_kf*10000);
    line_b = (int)(line_bf*10000);

    if(line_k == 0x7fffffff || line_k == 0x80000000 || line_b == 0x7fffffff || line_b == 0x80000000)
    {
        pOsdLine->setP1(QPoint(pix_vga_x,0));
        pOsdLine->setP2(QPoint(pix_vga_x,VGA_HEIGHT));
    }else
    {
        Line_Paint_Base_On_KB_SubPixel(line_kf, line_bf, pOsdLine);
    }

    return 0;
}

#endif
void ResolveRunData::GetPreData(QPainter *paint, int iStep,int iSwitch)
{
    ACCE_MODEL *m_pre_ptr = (ACCE_MODEL*)GetStepAcceModelPointer(iStep);
    if(!iSwitch){
        return;
    }else{
        for(int i = 0; i < m_pre_ptr->accelerator_num; i++)
        {
            if(m_pre_ptr->accelerator[i] == ACCE_AREA_SELECT_MODEL_ID){
                TASK_STEP_HEADER *pTaskHead = Task_Step_Head_Get(iStep);
                SELECT_AREA_PARAM sel_model;
                if(pTaskHead->compass_enable){//关联定位使能，取旋转后的数据
                    int ret = Select_Model_Compass_Result_Get(iStep,&sel_model);
                    if(ret == 0){
                        GetRoiData(paint,sel_model);
                    }
                }else{//关联定位没有使能，取原始数据
                    sel_model.valid_flag = 1;
                    memcpy(sel_model.octagons_cfg,m_pre_ptr->image_acce_param.select_model_cfg.octagons_cfg,sizeof(sel_model.octagons_cfg));
                    memcpy(sel_model.ring_cfg,m_pre_ptr->image_acce_param.select_model_cfg.ring_cfg,sizeof(sel_model.ring_cfg));
                    memcpy(sel_model.select_model,m_pre_ptr->image_acce_param.select_model_cfg.select_model,sizeof(sel_model.select_model));
                    GetRoiData(paint,sel_model);
                }
                break;
            }
        }
    }
}

void ResolveRunData::GetRoiData(QPainter *paint,SELECT_AREA_PARAM del_model)
{
    if(!del_model.valid_flag)
    {
        return;
    }
    int poly_index = 0;
    int ring_index = 0;
    for(int i = 0; i < 8; i++)
    {
        if(del_model.select_model[i] == 0){
            break;
        }else if(del_model.select_model[i] == 1 || del_model.select_model[i] == 3 ){//多边形
            DrawPolygon(paint,del_model.octagons_cfg[poly_index]);
            poly_index++;
        }else if(del_model.select_model[i] == 2){//圆环
            DrawRing(paint,del_model.ring_cfg[ring_index].ring);
            ring_index++;
        }
    }
}

void ResolveRunData::DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points)
{
    int point_cnt = qLn(points.octagon_vertex_en+1)/qLn(2);
    for(int i = 0; i < point_cnt-1; i++)
    {

        paint->drawLine(points.octagon_vertexs[i].vertex_x,points.octagon_vertexs[i].vertex_y,\
                        points.octagon_vertexs[i+1].vertex_x,points.octagon_vertexs[i+1].vertex_y);
    }
    paint->drawLine(points.octagon_vertexs[0].vertex_x,points.octagon_vertexs[0].vertex_y,\
                    points.octagon_vertexs[point_cnt-1].vertex_x,points.octagon_vertexs[point_cnt-1].vertex_y);
}

void ResolveRunData::DrawRing(QPainter *paint, CIRCULAR ring)
{
    QPoint m_center = QPoint(ring.center_x,ring.center_y);
    paint->drawEllipse(m_center,sqrt(ring.inner_radius_square),sqrt(ring.inner_radius_square));
    paint->drawEllipse(m_center,sqrt(ring.outer_radius_square),sqrt(ring.outer_radius_square));
}
