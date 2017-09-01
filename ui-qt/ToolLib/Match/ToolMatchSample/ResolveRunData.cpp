#include "ResolveRunData.h"
#include <qdebug.h>
#include <QThread>
#include "tool_testGlobal.h"

ResolveRunData::ResolveRunData()
{
    pRunPara = NULL;
    m_line_cnt =1;
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

    int iParam1 = pInputPara->param1;
    int iParam2 = pInputPara->param2;
    switch (iParam1) {
    case 0:
        pen.setColor(Qt::green);
        break;
    case 1:
        pen.setColor(Qt::blue);
        break;
    case 2:
        pen.setColor(Qt::red);
        break;
    default:
        pen.setColor(Qt::green);
        break;
    }

    switch (iParam2) {
    case 1:
        pen.setWidth(1);
        break;
    case 2:
        pen.setWidth(2);
        break;
    case 3:
        pen.setWidth(3);
        break;
    case 4:
        pen.setWidth(4);
        break;
    case 5:
        pen.setWidth(5);
        break;
    default:
        pen.setWidth(1);
        break;
    }
    paint->setPen(pen);
    paint->drawLine(m_pix_x-10,m_pix_y,m_pix_x+10,m_pix_y);
    paint->drawLine(m_pix_x,m_pix_y-10,m_pix_x,m_pix_y+10);

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
    pRunPara = (BASE_LINE_OUTPUT_PARAM*)Task_Step_Output_Para_Get(step);
    STRU_KEY_VALUE value;
    value.strName = "任务名称:测试程序";
    value.strValue = "\r\n";
    vt.append(value);

    if(((TOOLTEST_OUTPUT_PARAM*)pRunPara)->common_param.err_type_id != 0)
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
 * @note 获取本步骤特有数据
 */
QVector<STRU_KEY_VALUE> ResolveRunData::GetContent(int step, int index, int *count)
{
    *count =1;
    QVector<STRU_KEY_VALUE> vt;
    RST_VALUE_STRUCT *pRstData =  TaskStepResultMemGet(step);
    STRU_KEY_VALUE info;
    int rst1 = pRstData[TOOL_TEST_RST1].value.I32_Value;
    float rst2 = pRstData[TOOL_TEST_RST2].value.F32_Value;
    float pix = pRstData[TOOL_TEST_POINT_PIX_X].value.F32_Value;
    float piy = pRstData[TOOL_TEST_POINT_PIX_Y].value.F32_Value;
    float phx = pRstData[TOOL_TEST_POINT_PHY_X].value.F32_Value;
    float phy = pRstData[TOOL_TEST_POINT_PHY_Y].value.F32_Value;
    PixelCvt(&pix,&m_pix_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&piy,&m_pix_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    float phx_vga =0.0;
    float phy_vga =0.0;
    PixelCvt(&phx,&phx_vga,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&phy,&phy_vga,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    info.strName = "结果1:";
    info.strValue = QString::number(rst1);
    vt.append(info);
    info.strName = "结果2:";
    info.strValue = QString::number(rst2);
    vt.append(info);
    QString strTemp = "";
    info.strName = "点(像素):";
    strTemp = "(";
    strTemp += QString::number(m_pix_x);
    strTemp += ",";
    strTemp += QString::number(m_pix_y);
    strTemp += ")";
    info.strValue = strTemp;
    vt.append(info);
    info.strName = "点(物理):";
    strTemp = "(";
    strTemp += QString::number(phx_vga);
    strTemp += ",";
    strTemp += QString::number(phy_vga);
    strTemp += ")";
    info.strValue = strTemp;
    vt.append(info);
    return vt;
}

void ResolveRunData::SetInputPtr(void *ptr)
{
    pInputPara = (TOOLTEST_INPUT_PARAM*)ptr;
}

