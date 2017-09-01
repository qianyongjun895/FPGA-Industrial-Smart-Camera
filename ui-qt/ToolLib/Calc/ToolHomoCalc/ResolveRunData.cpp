#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>

ResolveRunData::ResolveRunData()
{

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
   HOMO_CALC_OUTPUT_PARAM *pRunPara = (HOMO_CALC_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:坐标转换";
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
        POINT_I point_pix_real;
        POINT_F point_pix_sub;
        point_pix_sub.x_f = pRstData[HOMO_CALC_PIX_X].value.F32_Value;
        point_pix_sub.y_f = pRstData[HOMO_CALC_PIX_Y].value.F32_Value;
        PixelCvt((void *)(&point_pix_sub),(void *)(&point_pix_real),CVT_SUB2REAL|CVT_F2I|CVT_POINT);
        info.strName = "像素坐标:";
        info.strValue = "("+QString::number(point_pix_real.x_i)\
                +","+QString::number(point_pix_real.y_i)+")";
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);
        info.strName = "物理坐标:";
        info.strValue = "("+QString::number(pRstData[HOMO_CALC_PHY_X].value.F32_Value)\
                +","+QString::number(pRstData[HOMO_CALC_PHY_Y].value.F32_Value)+")";
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);
        info.strName = "偏移量:";
        info.strValue = "("+QString::number(pRstData[HOMO_OFFSET_X].value.F32_Value)\
                +","+QString::number(pRstData[HOMO_OFFSET_Y].value.F32_Value)+")";
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);
        info.strName = "旋转角度:";
        info.strValue = QString::number(pRstData[HOMO_ROT_DEGREE].value.F32_Value);
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);
        info.strName = "旋转弧度:";
        info.strValue = QString::number(pRstData[HOMO_ROT_THETA].value.F32_Value);
        vt.append(info);
    }
    return vt;
}
