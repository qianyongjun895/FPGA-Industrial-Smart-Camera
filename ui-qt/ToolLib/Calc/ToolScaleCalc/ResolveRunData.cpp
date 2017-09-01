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
   SCALE_CALC_OUTPUT_PARAM *pRunPara = (SCALE_CALC_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:刻度转换";
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
        info.strName = "像素长度:";
        info.strValue = QString::number(pRstData[SCALE_CALC_PIX_LEN].value.F32_Value);
        vt.append(info);
        info.strName = " ";
        info.strValue =" ";
        vt.append(info);
        info.strName = "物理长度:";
        info.strValue = QString::number(pRstData[SCALE_CALC_PHY_LEN].value.F32_Value);
        vt.append(info);
    }
    return vt;
}
