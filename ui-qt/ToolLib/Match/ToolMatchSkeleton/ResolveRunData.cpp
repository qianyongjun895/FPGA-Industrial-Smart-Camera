#include "ResolveRunData.h"
#include <qdebug.h>
#include "AreaSelect.h"
#include <qmath.h>
#include <QThread>
ResolveRunData::ResolveRunData()
{
    m_width = 0.0;
    m_height = 0.0;
    m_ok_ng_flag = 0;
    m_ok_cnt = 0;
    m_ng_cnt = 0;
    m_excute_flag = 1;
}
ResolveRunData::~ResolveRunData()
{

}
void ResolveRunData::Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    QPen pen;
    pen.setColor(Qt::green);
    if(!m_ok_ng_flag ||!m_excute_flag)
        return;
    pen.setWidth(2);
    paint->setPen(pen);
    paint->drawLine(pix_center_point.x()-15,pix_center_point.y(),pix_center_point.x()+15,pix_center_point.y());
    paint->drawLine(pix_center_point.x(),pix_center_point.y()-15,pix_center_point.x(),pix_center_point.y()+15);
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
#if 1
    SetInputPtr(step);
    float dCos = cos(m_theta);
    float dSin = sin(m_theta);
    POINT_F point1,point2,point3,point4;
    POINT_F point_center;
    point_center.x_f = (float)pix_center_point.x();
    point_center.y_f = (float)pix_center_point.y();
    POINT_F point_dis;
    point_dis.x_f = -m_height;
    point_dis.y_f = m_width;
    Coordinate_Rotate_Calc(&point1,&point_center,&point_dis,dSin,dCos);
    point_dis.x_f = m_height;
    point_dis.y_f = -m_width;
    Coordinate_Rotate_Calc(&point2,&point_center,&point_dis,dSin,dCos);
    point_dis.x_f = m_height;
    point_dis.y_f = m_width;
    Coordinate_Rotate_Calc(&point3,&point_center,&point_dis,dSin,dCos);
    point_dis.x_f = -m_height;
    point_dis.y_f = -m_width;
    Coordinate_Rotate_Calc(&point4,&point_center,&point_dis,dSin,dCos);
    Coordinate_Rotate_Calc(&point4,&point_center,&point_dis,dSin,dCos);
    paint->drawLine(QPointF(point1.x_f,point1.y_f),QPointF(point4.x_f,point4.y_f));
    paint->drawLine(QPointF(point4.x_f,point4.y_f),QPointF(point2.x_f,point2.y_f));
    paint->drawLine(QPointF(point2.x_f,point2.y_f),QPointF(point3.x_f,point3.y_f));
    paint->drawLine(QPointF(point1.x_f,point1.y_f),QPointF(point3.x_f,point3.y_f));

#endif

}
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    SKELETON_OUTPUT_PARAM *pRunPara = (SKELETON_OUTPUT_PARAM *)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE value;
    value.strName = "任务名称:轮廓匹配";
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
    *count =1;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;

    RST_VALUE_STRUCT *pRstData =  (RST_VALUE_STRUCT *)TaskStepResultMemGet(step);
    POINT_I point_pix_real;
    POINT_I point_pix_vga;
    POINT_F point_pix_sub;
    point_pix_sub.x_f = pRstData[S_CENTER_POINT_X_ID].value.F32_Value;
    point_pix_sub.y_f = pRstData[S_CENTER_POINT_Y_ID].value.F32_Value;
    PixelCvt((void *)(&point_pix_sub),(void *)(&point_pix_real),CVT_SUB2REAL|CVT_F2I|CVT_POINT);
    PixelCvt((void *)(&point_pix_sub),(void *)(&point_pix_vga),CVT_SUB2VGA|CVT_F2I|CVT_POINT);
    pix_center_point = QPoint(point_pix_vga.x_i,point_pix_vga.y_i);

    phy_center_point.setX(pRstData[S_PHY_CENTER_POINT_X_ID].value.F32_Value);
    phy_center_point.setY(pRstData[S_PHY_CENTER_POINT_Y_ID].value.F32_Value);
    m_theta = pRstData[S_ROTATA_THETA_ID].value.D64_Value;

    info.strName = "中心点(像素):";
    info.strValue = "("+QString::number(point_pix_real.x_i)+","+QString::number(point_pix_real.y_i)+")";
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "中心点(物理):";
    info.strValue = "("+QString::number(phy_center_point.x())+","+QString::number(phy_center_point.y())+")";
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "旋转角度:";
    info.strValue = QString::number(pRstData[S_ROTATE_ANGLE_ID].value.D64_Value);
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "旋转弧度:";
    info.strValue = QString::number(m_theta);
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "相似度:";
    info.strValue = QString::number(pRstData[S_SCORE_ID].value.D64_Value);
    vt.append(info);
    return vt;
}


void ResolveRunData::SetInputPtr(int step)
{
    void *ptr = Task_Step_Input_Para_Get(step);
    m_width = abs(((SKELETON_INPUT_PARAM*)ptr)->train_roi_point[0].y_f - ((SKELETON_INPUT_PARAM*)ptr)->train_roi_point[1].y_f)*0.5;
    m_height = abs(((SKELETON_INPUT_PARAM*)ptr)->train_roi_point[0].x_f - ((SKELETON_INPUT_PARAM*)ptr)->train_roi_point[1].x_f)*0.5;
}

inline void ResolveRunData::Coordinate_Rotate_Calc(POINT_F *OutPoint, POINT_F *ref_point, POINT_F *ref_delt, float sin_a, float cos_a)
{
    OutPoint->x_f = (cos_a*ref_delt->x_f - sin_a*ref_delt->y_f + (ref_point->x_f));
    OutPoint->y_f = (sin_a*ref_delt->x_f + cos_a*ref_delt->y_f + (ref_point->y_f));
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
