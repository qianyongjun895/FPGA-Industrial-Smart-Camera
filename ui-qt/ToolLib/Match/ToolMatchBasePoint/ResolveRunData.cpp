#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
#include "PixelConvert.h"
ResolveRunData::ResolveRunData()
{
    m_Point_cnt = 0;
    pRunPara = NULL;
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
    QPen pen;
    pen.setColor(Qt::green);
    paint->setPen(pen);
    for(int i = 0; i < m_Point_cnt; i++ )
    {
        paint->drawEllipse(m_BasePointPix[i],10,10);
        paint->drawLine(m_BasePointPix[i].x()+20,m_BasePointPix[i].y(),m_BasePointPix[i].x()-20,m_BasePointPix[i].y());
        paint->drawLine(m_BasePointPix[i].x(),m_BasePointPix[i].y()+20,m_BasePointPix[i].x(),m_BasePointPix[i].y()-20);
//        paint->drawText(QPoint(m_BasePointPix[i].x(),(m_BasePointPix[i].y()-20)),QString::number(i+1));
    }

}


/**
 * @brief ResolveRunData::GetHead
 * @param step
 * @return
 * @author dgq
 * @note 获取通用输出信息
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    pRunPara = Task_Step_Output_Para_Get(step);
//    qDebug()<<"OK_count = "<<((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.OK_count;
//    qDebug()<<"NG_count = "<<((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.NG_count;
//    qDebug()<<"step_cost_time = "<<((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.step_cost_time;

    STRU_KEY_VALUE value;
    value.strName = "任务名称:基准点";
    value.strValue = "\r\n";
    vt.append(value);

    if(((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.err_type_id != 0)
    {
        value.strName = "执行结果:";
        value.strValue = "NG";
    }else
    {

        value.strName = "执行结果:";
        value.strValue = "OK";
    }
    vt.append(value);
    value.strName = "OK计数:";
    value.strValue = QString::number(((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.OK_count);
    vt.append(value);
    value.strName = "NG计数:";
    value.strValue = QString::number(((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.NG_count);
    vt.append(value);
    value.strName = "运行时间:";
    value.strValue = QString::number(((BASEPOINT_OUTPUT_PARAM*)pRunPara)->common_param.step_cost_time)+"ms";
    vt.append(value);
    return vt;
}

/**
 * @brief ResolveRunData::GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步骤特有数据
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
    RST_VALUE_STRUCT *pRstTemp = NULL;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
//    if(pRstData->resultflag)//该数据有效
    {
        m_Point_cnt = pRstData[BASE_POINT_NUM].value.U32_Value;
        *count = m_Point_cnt;
        int pix_vga_x = 0;
        int pix_vga_y = 0;
        int pix_real_x = 0;
        int pix_real_y = 0;
        int id= 0;
        for(int i = 0; i < m_Point_cnt; i++)
        {
            id = 4*i;
            pRstTemp = &pRstData[id];
            float pix_sub_x = pRstTemp[BASE_POINT0_X_ID].value.F32_Value;
            float pix_sub_y = pRstTemp[BASE_POINT0_Y_ID].value.F32_Value;

            PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_x),(void *)(&pix_real_x),CVT_SUB2REAL|CVT_F2I|CVT_DATA);
            PixelCvt((void *)(&pix_sub_y),(void *)(&pix_real_y),CVT_SUB2REAL|CVT_F2I|CVT_DATA);
            m_BasePointPix[i].setX(pix_vga_x);
            m_BasePointPix[i].setY(pix_vga_y);
            m_BasePointReal[i].setX(pix_real_x);
            m_BasePointReal[i].setY(pix_real_y);
            m_BasePointPhy[i].setX(pRstTemp[BASE_POINT0_PHY_X_ID].value.F32_Value);
            m_BasePointPhy[i].setY(pRstTemp[BASE_POINT0_PHY_Y_ID].value.F32_Value);
        }
        if(index <= m_Point_cnt)
        {
            info.strName = "基准点"+QString::number(index)+"坐标(像素):";
            info.strValue = "("+QString::number(m_BasePointReal[index-1].x())+","+QString::number(m_BasePointReal[index-1].y())+")";
            vt.append(info);
            info.strName = " ";
            info.strValue =" ";
            vt.append(info);
            info.strName = "基准点"+QString::number(index)+"坐标(物理):";
            info.strValue = "("+QString::number(m_BasePointPhy[index-1].x())+","+QString::number(m_BasePointPhy[index-1].y())+")";
            vt.append(info);
        }

    }
    return vt;
}
