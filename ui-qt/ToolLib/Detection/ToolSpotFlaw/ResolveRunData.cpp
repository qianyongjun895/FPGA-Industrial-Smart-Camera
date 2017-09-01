#include "ResolveRunData.h"
#include "AreaSelect.h"
#include <qmath.h>

ResolveRunData::ResolveRunData()
{
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
    if(m_ok_ng_flag)
        paint->setPen(pen->pen_ok_solidLine);
    else
        paint->setPen(pen->pen_ng_solidLine);
    for(int i = 0; i < m_Points.count(); i++)
    {
        paint->drawText(m_Points[i].x(),m_Points[i].y()-20,QString::number(i+1));
        paint->drawLine(m_Points[i].x()-5,m_Points[i].y(),m_Points[i].x()+5,m_Points[i].y());
        paint->drawLine(m_Points[i].x(),m_Points[i].y()-5,m_Points[i].x(),m_Points[i].y()+5);
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

/**
 * @brief ResolveRunData::GetHead
 * @param step
 * @return 通用输出详细信息
 * @author dgq
 * @note 获取
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    SPOT_FLAW_OUTPUT_PARAM *pRunPara = (SPOT_FLAW_OUTPUT_PARAM *)Task_Step_Output_Para_Get(step);

    STRU_KEY_VALUE value;
    value.strName = "任务名称:斑点缺陷";
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
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
    RST_VALUE_STRUCT *pRstTemp = NULL;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;

    m_Points.clear();
    m_Real_Points.clear();
    m_Area.clear();
//    if(pRstData->resultflag)//该数据有效
    {
        m_Point_cnt = pRstData[SPOT_FLAW_NUM_ID].value.U32_Value;
        *count = m_Point_cnt;
        unsigned int area_sum = pRstData[SPOT_FLAW_AREA_SUM_ID].value.U32_Value;
        int pix_vga_x = 0;
        int pix_vga_y = 0;
        int pix_real_x = 0;
        int pix_real_y = 0;
        int  id = 0;
        for(int i = 0; i < m_Point_cnt; i++)
        {
            id = 3*i;
            pRstTemp = &pRstData[id];
            unsigned int area = pRstTemp[SPOT_FLAW0_AREA_ID].value.U32_Value;
            m_Area.append(area);
            int pix_sub_x = pRstTemp[SPOT_FLAW0_PIXEL_X_ID].value.I32_Value;
            int pix_sub_y = pRstTemp[SPOT_FLAW0_PIXEL_Y_ID].value.I32_Value;

            PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_I2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_I2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_x),(void *)(&pix_real_x),CVT_SUB2REAL|CVT_I2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_y),(void *)(&pix_real_y),CVT_SUB2REAL|CVT_I2I|CVT_DATA);
            m_Points.append(QPoint(pix_vga_x,pix_vga_y));
            m_Real_Points.append(QPoint(pix_real_x,pix_real_y));
        }
        if(index <= m_Point_cnt)
        {
            int m_point_index =index-1;
            info.strName = "总面积:";
            info.strValue = QString::number(area_sum);
            vt.append(info);
            info.strName = " ";
            info.strValue =" ";
            vt.append(info);
            info.strName = "斑点缺陷"+QString::number(index)+"  面积:";
            info.strValue = QString::number(m_Area[m_point_index]);
            vt.append(info);
            info.strName = " ";
            info.strValue =" ";
            vt.append(info);
            info.strName = "中心点(像素):";
            info.strValue = "("+QString::number(m_Real_Points[m_point_index].x())+","+QString::number(m_Real_Points[m_point_index].y())+")";
            vt.append(info);
        }

    }
    return vt;
}



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
