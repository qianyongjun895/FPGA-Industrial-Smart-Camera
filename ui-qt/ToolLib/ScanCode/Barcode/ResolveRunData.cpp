#include "ResolveRunData.h"
#include "BarcodeGlobal.h"
#include <QDebug>
ResolveRunData::ResolveRunData()
{
    Code_Type.append("EAN8");
    Code_Type.append("EAN13");
    Code_Type.append("CODE-39");
    Code_Type.append("CODE-93");
    Code_Type.append("CODE-128");
    Code_Type.append("I2/5");
    Code_Type.append("UPC-A");
    Code_Type.append("UPC-E");
    Code_Type.append("ITF");
    Code_Type.append("CodaBar");
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
    BARCODE_OUTPUT_PARAM* pRunPara = (BARCODE_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);

    STRU_KEY_VALUE value;
    value.strName = "任务名称:条形码";
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
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step,int index,int *count)
{
    RST_VALUE_STRUCT *pRstData = TaskStepResultMemGet(step);
    STRU_KEY_VALUE info;
    QVector<STRU_KEY_VALUE> vt;
    char Result[1024];
    memset(Result, 0, 1024);
    *count =1;
    if(pRstData[BARCODE_OK_NG_ID].value.U32_Value == 1){
        info.strName = "条形码类型:";
        info.strValue = Code_Type.at(pRstData[BARCODE_TYPE_ID].value.U32_Value);
        vt.append(info);

        info.strName = "";
        info.strValue = "";
        vt.append(info);

        memcpy(Result, pRstData+sizeof(RST_VALUE_STRUCT)*BARCODE_ENUM_END, pRstData[BARCODE_RESULT_LENGTH_ID].value.U32_Value);
        info.strName = "扫码结果:";
        info.strValue = QString::fromUtf8(Result);
        vt.append(info);
    }
    return vt;
}
