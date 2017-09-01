#include "ResolveRunData.h"

ResolveRunData::ResolveRunData()
{
    pRunPara = NULL;
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
}

/**
 * @brief ResolveRunData::GetHead
 * @param step
 * @return
 * @author dgq
 * @note 获取任务通用输出数据
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    pRunPara = Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:命令跳转";
    info.strValue = "\r\n";
    vt.append(info);

    if(((CMD_JUMP_OUTPUT_PARAM*)pRunPara)->common_param.err_type_id != 0)
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
    info.strValue = QString::number(((CMD_JUMP_OUTPUT_PARAM*)pRunPara)->common_param.OK_count);
    vt.append(info);
    info.strName = "NG计数:";
    info.strValue = QString::number(((CMD_JUMP_OUTPUT_PARAM*)pRunPara)->common_param.NG_count);
    vt.append(info);
    info.strName = "运行时间:";
    info.strValue = QString::number(((CMD_JUMP_OUTPUT_PARAM*)pRunPara)->common_param.step_cost_time)+"ms";
    vt.append(info);
    return vt;
}

/**
 * @brief ResolveRunData::GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步骤特有的输出数据
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    *count =1;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
    if(pRstData->resultflag)//该数据有效
    {
        info.strName = "命令编号:";
        info.strValue = QString::number(pRstData[CMD_JUMP_CMD_INDEX].value.U32_Value);
        vt.append(info);
        info.strName = " ";
        info.strValue = " ";
        vt.append(info);
        info.strName = "跳转步骤编号:";
        info.strValue = QString::number(pRstData[CMD_JUMP_TARGET_STEP_ID].value.U32_Value);
        vt.append(info);
    }
    return vt;
}

