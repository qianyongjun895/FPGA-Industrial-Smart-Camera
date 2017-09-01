#include "ResolveRunData.h"
#include "CalculatorGlobal.h"
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
    CALC_OUTPUT_PARAM* pRunPara = (CALC_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);

    STRU_KEY_VALUE value;
    value.strName = "任务名称:计算器";
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
    *count =1;
    RST_VALUE_STRUCT *pRstData = TaskStepResultMemGet(step);
    STRU_KEY_VALUE info;
    QVector<STRU_KEY_VALUE> vt;
    if(pRstData[CALC_OK_NG_ID].value.U32_Value)
    {
//        info.strName = "结果数:";
//        info.strValue = QString::number(pRstData[CALC_RESULT_NUM].value.U32_Value);
        vt.append(info);
        for(int i = 0; i < pRstData[CALC_RESULT_NUM].value.U32_Value;i++){
            info.strName = ("结果")+(QString::number(i+1))+(":");
            info.strValue = QString::number(pRstData[CALC_RESULT0+i].value.F32_Value);
            vt.append(info);
        }
    }
    return vt;
}
