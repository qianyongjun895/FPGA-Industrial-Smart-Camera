#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
#include <qmath.h>
#include <QTime>
#include "AreaSelect.h"
ResolveRunData::ResolveRunData()
{
    m_Point_cnt = 0;
    m_ok_cnt = -1;
    m_ng_cnt = -1;
    m_excute_flag = 1;
}
ResolveRunData::~ResolveRunData()
{

}

/**
 * @brief ResolveRunData::Paint
 * @param paint
 * @param step
 * @author dgq
 * @note OSD显示
 */
void ResolveRunData::Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
    QTime time;
    time.start();
    PEN_STYLE_RUN *pen = (PEN_STYLE_RUN *)penStyle;

    if(m_ok_ng_flag)
        paint->setPen(pen->pen_ok_solidLine);
    else
        paint->setPen(pen->pen_ng_solidLine);

    float fLen =20.0;

    for(int i = 0; i<m_Point_cnt;i++)
    {
        if(Blob_Height[i] >40.0)
        {
            fLen = Blob_Height[i]/2.0;
        }
        else
            fLen = 20.0;
        QPoint lastPoint;
        if(Blob_Pix_Center[i].x() >= 0 && Blob_Pix_Center[i].x() <= 640 \
                &&Blob_Pix_Center[i].y() >= 0 && Blob_Pix_Center[i].y() <= 480)
        {
            lastPoint.setX(Blob_Pix_Center[i].x());
            lastPoint.setY(Blob_Pix_Center[i].y());
            int x = (int)(Blob_Pix_Center[i].x() + fLen*cos(Blob_Theta[i]));
            int y = (int)(Blob_Pix_Center[i].y() + fLen*sin(Blob_Theta[i]));
            QPoint endPoint;
            endPoint.setX(x);
            endPoint.setY(y);
            DrawArrow(paint,lastPoint,endPoint,10.0);
            paint->drawText(lastPoint,QString::number(i+1));
        }
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
 * @brief ResolveRunData::DrawArrow
 * @param painter
 * @param lastPoint 起点
 * @param endPoint 终点
 * @param iArrowLen 箭头的两条线长度
 * @author dgq
 * @date 2017/5/23
 * @note 画箭头
 */
void ResolveRunData::DrawArrow(QPainter *painter,QPoint lastPoint,QPoint endPoint,float iArrowLen)
{

    float x1 = lastPoint.x();         //lastPoint 起点
    float y1 = lastPoint.y();
    float x2 = endPoint.x();           //endPoint 终点
    float y2 = endPoint.y();
    if(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))>640*480)
    {
        return;
    }
    //float iArrowLen = 10.0;                   //箭头的那长度
    float a = 0.5;                       //箭头与线段角度
    float x3 = x2 - iArrowLen * cos(atan2((y2 - y1) , (x2 - x1)) - a);
    float y3 = y2 - iArrowLen * sin(atan2((y2 - y1) , (x2 - x1)) - a);
    float x4 = x2 - iArrowLen * sin(atan2((x2 - x1) , (y2 - y1)) - a);
    float y4 = y2 - iArrowLen * cos(atan2((x2 - x1) , (y2 - y1)) - a);

    painter->drawLine(x2,y2,x3,y3);
    painter->drawLine(x2,y2,x4,y4);
    painter->drawLine(lastPoint,endPoint);
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
    m_excute_flag = 0;
    QVector<STRU_KEY_VALUE> vt;
    BLOB_OUTPUT_PARAM *pRunPara = (BLOB_OUTPUT_PARAM *)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE value;
    value.strName = "任务名称:Blob";
    value.strValue = "\r\n";
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
    if((m_ok_cnt == -1 && m_ng_cnt == -1) || (m_ok_cnt > pRunPara->common_param.OK_count || m_ng_cnt > pRunPara->common_param.NG_count))
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
 * @param step
 * @return
 * @author dgq
 * @note 获取本步特有参数
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    RST_VALUE_STRUCT *pRstData =  (RST_VALUE_STRUCT *)TaskStepResultMemGet(step);
    RST_VALUE_STRUCT *pRstTemp = NULL;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
    ClearOsdData();
//    if(pRstData->resultflag)//该数据有效
    {
        m_Point_cnt = pRstData[BLOB_NUM].value.I32_Value;
        *count = m_Point_cnt;
        float pix_vga_x = 0.0;
        float pix_vga_y = 0.0;
        int real_pix_x = 0;
        int real_pix_y = 0;
        int  id = 0;
        for(int i = 0; i < m_Point_cnt; i++)
        {
            id = 12*i;
            pRstTemp = &pRstData[id];
            float pix_sub_x = pRstTemp[BLOB0_PIXEL_CENTER_X_ID].value.F32_Value;
            float pix_sub_y = pRstTemp[BLOB0_PIXEL_CENTER_Y_ID].value.F32_Value;

            PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
            PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);

            PixelCvt((void *)(&pix_sub_x),(void *)(&real_pix_x),CVT_SUB2REAL|CVT_F2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_y),(void *)(&real_pix_y),CVT_SUB2REAL|CVT_F2I|CVT_DATA);
            Blob_Real_Center.append(QPoint(real_pix_x,real_pix_y));
            Blob_Pix_Center.append(QPoint(pix_vga_x,pix_vga_y));
            Blob_Phy_Center.append((QPoint(pRstTemp[BLOB0_PHY_CENTER_X_ID].value.F32_Value,\
                                           pRstTemp[BLOB0_PHY_CENTER_Y_ID].value.F32_Value)));
            Blob_Area.append(pRstTemp[BLOB0_AREA_ID].value.I32_Value);
            Blob_Theta.append(pRstTemp[BLOB0_THETA_ID].value.F32_Value);
            Blob_Angle.append(pRstTemp[BLOB0_DEGREE_ID].value.F32_Value);
            Blob_Rotate_Theta.append(pRstTemp[BLOB0_ROTATE_THETA_ID].value.F32_Value);
            Blob_Rotate_Angle.append(pRstTemp[BLOB0_ROTATE_DEGREE_ID].value.F32_Value);
            Blob_Ratio.append(pRstTemp[BLOB0_RATIO_ID].value.F32_Value);

            float pix_vga_w = 0.0;
            float pix_vga_h = 0.0;
            float pix_sub_w = pRstTemp[BLOB0_WIDTH_ID].value.F32_Value;
            float pix_sub_h = pRstTemp[BLOB0_HEIGHT_ID].value.F32_Value;
            PixelCvt((void *)(&pix_sub_w),(void *)(&pix_vga_w),CVT_REAL2VGA|CVT_F2F|CVT_DATA);
            PixelCvt((void *)(&pix_sub_h),(void *)(&pix_vga_h),CVT_REAL2VGA|CVT_F2F|CVT_DATA);

            Blob_Width.append(pix_vga_w);
            Blob_Height.append(pix_vga_h);
        }
        if(index <= m_Point_cnt)
        {
            int m_point_index =index-1;
            info.strName = "Blob";
            info.strValue = QString::number(index) + "数据:";
            vt.append(info);
            info.strName = " ";
            info.strValue = " ";
            vt.append(info);
            info.strName = "面积:";
            info.strValue = QString::number(Blob_Area[m_point_index]);
            vt.append(info);
            info.strName = "长宽比:";
            info.strValue = QString::number(Blob_Ratio[m_point_index]);
            vt.append(info);
            info.strName = "长度:";
            info.strValue = QString::number(Blob_Height[m_point_index]);
            vt.append(info);
            info.strName = "宽度:";
            info.strValue = QString::number(Blob_Width[m_point_index]);
            vt.append(info);
            info.strName = "弧度:";
            info.strValue = QString::number(Blob_Theta[m_point_index]);
            vt.append(info);
            info.strName = "角度:";
            info.strValue = QString::number(Blob_Angle[m_point_index]);
            vt.append(info);
            info.strName = "旋转弧度:";
            info.strValue = QString::number(Blob_Rotate_Theta[m_point_index]);
            vt.append(info);
            info.strName = "旋转角度:";
            info.strValue = QString::number(Blob_Rotate_Angle[m_point_index]);
            vt.append(info);
            info.strName = "中心点(像素):";
            info.strValue = "("+QString::number(Blob_Real_Center[m_point_index].x())+","+QString::number(Blob_Real_Center[m_point_index].y())+")";
            vt.append(info);
            info.strName = "中心点(物理):";
            info.strValue = "("+QString::number(Blob_Phy_Center[m_point_index].x())+","+QString::number(Blob_Phy_Center[m_point_index].y())+")";
            vt.append(info);
        }

    }
    return vt;
}

int ResolveRunData::ClearOsdData()
{
    Blob_Pix_Center.clear();
    Blob_Real_Center.clear();
    Blob_Phy_Center.clear();
    Blob_Area.clear();
    Blob_Theta.clear();
    Blob_Angle.clear();
    Blob_Rotate_Theta.clear();
    Blob_Rotate_Angle.clear();
    Blob_Ratio.clear();
    Blob_Width.clear();
    Blob_Height.clear();
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
