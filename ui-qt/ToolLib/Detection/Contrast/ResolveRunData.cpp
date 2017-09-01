#include "QDebug"
#include "ResolveRunData.h"
#include "AreaSelect.h"
#include <qmath.h>

ResulveRunData::ResulveRunData()
{
    m_ok_cnt = 0;
    m_ng_cnt = 0;
    m_excute_flag = 1;
}

ResulveRunData::~ResulveRunData()
{

}

/**
 * @brief ResulveRunData::Paint
 * @param paint
 * @param step
 * @author dgq
 * @note osd显示
 */
void ResulveRunData::Paint(QPainter *paint, int step,void *penStyle,int paintAreaSelect)
{
    PEN_STYLE_RUN *pen = (PEN_STYLE_RUN *)penStyle;
    if(!m_excute_flag)
    {
        return;
    }
    if(m_ok_ng_flag)
        paint->setPen(pen->pen_ok_solidLine);
    else
        paint->setPen(pen->pen_ng_solidLine);
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
 * @brief ResulveRunData::GetHead
 * @param step
 * @return
 * @author dgq
 * @note 获取任务通用输出数据
 */
QVector<STRU_KEY_VALUE> ResulveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;

    CONTRAST_OUTPUT_PARAM *pRunPara = (CONTRAST_OUTPUT_PARAM *)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:对比度";
    info.strValue = "\r\n";
    vt.append(info);

    if(pRunPara->common_param.err_type_id != 0)
    {
        m_ok_ng_flag = 0;
        info.strName = "执行结果:";
        info.strValue = "NG";
    }else
    {
        m_ok_ng_flag = 1;
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
 * @brief ResulveRunData::GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步骤特有输出数据
 */
QVector<STRU_KEY_VALUE> ResulveRunData::GetContent(int step, int index, int *count)
{
    *count =1;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
//    if(pRstData->resultflag)//该数据有效
    {
        m_contrast_result.contrast = pRstData[CONTRAST_ID].value.U32_Value;
        info.strName = "对比度:";
        info.strValue = QString::number(m_contrast_result.contrast );
        vt.append(info);
    }
    return vt;
}
void ResulveRunData::GetPreData(QPainter *paint, int iStep,int iSwitch)
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

void ResulveRunData::GetRoiData(QPainter *paint,SELECT_AREA_PARAM del_model)
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

void ResulveRunData::DrawPolygon(QPainter *paint, OCTAGON_CFG_PARA points)
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

void ResulveRunData::DrawRing(QPainter *paint, CIRCULAR ring)
{
    QPoint m_center = QPoint(ring.center_x,ring.center_y);
    paint->drawEllipse(m_center,sqrt(ring.inner_radius_square),sqrt(ring.inner_radius_square));
    paint->drawEllipse(m_center,sqrt(ring.outer_radius_square),sqrt(ring.outer_radius_square));
}
