#include "ResolveRunData.h"
#include "DataStatGlobal.h"
ResolveRunData::ResolveRunData()
{

}
/**
 * @brief ResolveRunData::GetHead
 * @param step
 * @return
 * @author th
 * @note 获取任务通用输出数据
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    DATASTST_OUTPUT_PARAM* pRunPara = (DATASTST_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);

    STRU_KEY_VALUE value;
    value.strName = "任务名称:统计";
    value.strValue = "\n";
    vt.append(value);

    if(pRunPara->common_param.err_type_id != 0)
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
    value.strValue = QString::number(pRunPara->common_param.OK_count);
    vt.append(value);
    value.strName = "NG计数:";
    value.strValue = QString::number(pRunPara->common_param.NG_count);
    vt.append(value);
    value.strName = "运行时间:";
    value.strValue = QString::number(pRunPara->common_param.step_cost_time)+"ms";
    vt.append(value);
    return vt;
}

/**
 * @brief ResolveRunData::GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步任务特有的输出数据
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    RST_VALUE_STRUCT *pRstData = TaskStepResultMemGet(step);
    STRU_KEY_VALUE info;
    QVector<STRU_KEY_VALUE> vt;

    info.strName = "最后的值";
    info.strValue = QString::number(pRstData[DS_LAST_VALUE].value.F32_Value);
    vt.append(info);

    info.strName = "最小值";
    info.strValue = QString::number(pRstData[DS_MIN_VALUE].value.F32_Value);
    vt.append(info);

    info.strName = "最大值";
    info.strValue = QString::number(pRstData[DS_MAX_VALUE].value.F32_Value);
    vt.append(info);

    info.strName = "平均值";
    info.strValue = QString::number(pRstData[DS_MEAN_VALUE].value.F32_Value);
    vt.append(info);

    info.strName = "累加和";
    info.strValue = QString::number(pRstData[DS_SUM_VALUE].value.D64_Value);
    vt.append(info);

    info.strName = "成品率";
    info.strValue = QString::number(pRstData[DS_SUCCESS_RATIO].value.F32_Value);
    vt.append(info);

    info.strName = "统计次数";
    info.strValue = QString::number(pRstData[DS_TOTAL_CNT].value.U32_Value);
    vt.append(info);

    info.strName = "成功次数";
    info.strValue = QString::number(pRstData[DS_SUCCESS_CNT].value.U32_Value);
    vt.append(info);

    info.strName = "无效次数";
    info.strValue = QString::number(pRstData[DS_INVALID_CNT].value.U32_Value);
    vt.append(info);

    info.strName = "失败次数";
    info.strValue = QString::number(pRstData[DS_FAIL_CNT].value.U32_Value);
    vt.append(info);
    return vt;
}
