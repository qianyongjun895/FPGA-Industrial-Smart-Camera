#include "ResolveRunData.h"

ResolveRunData::ResolveRunData()
{
    pRunPara = NULL;
}

ResolveRunData::~ResolveRunData()
{

}

void ResolveRunData::Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect)
{
}

QVector<STRU_KEY_VALUE> ResolveRunData::GetHead(int step)
{
    QVector<STRU_KEY_VALUE> vt;
    pRunPara = Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE info;
    info.strName = "任务名称:脚本";
    info.strValue = "\r\n";
    vt.append(info);

    if(((SCRIPT_OUTPUT_PARAM*)pRunPara)->common_param.err_type_id != 0)
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
    info.strValue = QString::number(((SCRIPT_OUTPUT_PARAM*)pRunPara)->common_param.OK_count);
    vt.append(info);
    info.strName = "NG计数:";
    info.strValue = QString::number(((SCRIPT_OUTPUT_PARAM*)pRunPara)->common_param.NG_count);
    vt.append(info);
    info.strName = "运行时间:";
    info.strValue = QString::number(((SCRIPT_OUTPUT_PARAM*)pRunPara)->common_param.step_cost_time)+"ms";
    vt.append(info);
    return vt;
}


QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    *count =3;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
    for(int i = 0; i < 6; i++)
    {
        int rst_id = 6*(index-1)+i;
        if(rst_id == 17)
        {
            break;
        }
        info.strName = "结果"+QString::number(rst_id+1)+":";

        switch (pRstData[rst_id].resulttype) {
        case DATA_SINT:
            info.strValue = QString::number(pRstData[rst_id].value.I32_Value);
            break;
        case DATA_SINT_INV:
            info.strValue = QString::number(pRstData[rst_id].value.I32_Value_Revert);
            break;
        case DATA_UINT:
            info.strValue = QString::number(pRstData[rst_id].value.U32_Value);
            break;
        case DATA_UINT_INV:
            info.strValue = QString::number(pRstData[rst_id].value.U32_Value_Revert);
            break;
        case DATA_FLT:
            info.strValue = QString::number(pRstData[rst_id].value.F32_Value);
            break;
        case DATA_FLT_INV:
            info.strValue = QString::number(pRstData[rst_id].value.F32_Value_Revert);
            break;
        case DATA_DBL:
            info.strValue = QString::number(pRstData[rst_id].value.D64_Value);
            break;
        case DATA_DBL_INV:
            info.strValue = QString::number(pRstData[rst_id].value.D64_Value_Revert);
            break;
        default:
            break;
        }
        vt.append(info);

        info.strName = " ";
        info.strValue = " ";
        vt.append(info);
    }

    return vt;
}
