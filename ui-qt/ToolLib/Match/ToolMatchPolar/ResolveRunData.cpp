#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
#include "PixelConvert.h"

ResolveRunData::ResolveRunData()
{
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
    STRU_KEY_VALUE value;
    value.strName = "任务名称:圆展开";
    value.strValue = "\r\n";
    vt.append(value);

    if(((POLAR_MATCH_OUTPUT_PARAM*)pRunPara)->common_param.err_type_id != 0)
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
    value.strValue = QString::number(((POLAR_MATCH_OUTPUT_PARAM*)pRunPara)->common_param.OK_count);
    vt.append(value);
    value.strName = "NG计数:";
    value.strValue = QString::number(((POLAR_MATCH_OUTPUT_PARAM*)pRunPara)->common_param.NG_count);
    vt.append(value);
    value.strName = "运行时间:";
    value.strValue = QString::number(((POLAR_MATCH_OUTPUT_PARAM*)pRunPara)->common_param.step_cost_time)+"ms";
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
    *count =1;
    QVector<STRU_KEY_VALUE> vt;
    STRU_KEY_VALUE info;
    RST_VALUE_STRUCT *pRstData =  (RST_VALUE_STRUCT *)TaskStepResultMemGet(step);
    int pix_real_x;
    int pix_real_y;
    int pix_vga_x;
    int pix_vga_y;
    float pix_sub_x = pRstData[POLAR_MATCH_CENTER_X_ID].value.F32_Value;
    float pix_sub_y = pRstData[POLAR_MATCH_CENTER_Y_ID].value.F32_Value;
    PixelCvt((void *)(&pix_sub_x),(void *)(&pix_real_x),CVT_SUB2REAL|CVT_F2I|CVT_DATA);
    PixelCvt((void *)(&pix_sub_y),(void *)(&pix_real_y),CVT_SUB2REAL|CVT_F2I|CVT_DATA);
    PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    pix_center_point.setX(pix_vga_x);
    pix_center_point.setY(pix_vga_y);

    info.strName = "中心点(像素):";
    info.strValue = "("+QString::number(pix_real_x)+","+QString::number(pix_real_y)+")";
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "起始角度:";
    info.strValue = QString::number(pRstData[POLAR_MATCH_CENTER_X_ID].value.F32_Value);
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "结束角度:";
    info.strValue = QString::number(pRstData[POLAR_MATCH_RST_END_DEGREE].value.F32_Value);
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "旋转角度:";
    info.strValue = QString::number(pRstData[POLAR_MATCH_DEGREE_ID].value.F32_Value);
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "旋转弧度:";
    info.strValue = QString::number(pRstData[POLAR_MATCH_THETA_ID].value.F32_Value);
    vt.append(info);
    info.strName = " ";
    info.strValue = " ";
    vt.append(info);
    info.strName = "相似度:";
    info.strValue = QString::number(pRstData[POLAR_MATCH_SCORE_ID].value.U32_Value);
    vt.append(info);
    return vt;
}
