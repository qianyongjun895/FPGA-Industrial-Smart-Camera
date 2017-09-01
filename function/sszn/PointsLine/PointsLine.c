/**
  * @file  [PointsLine.c]
  * @brief  两点线段功能
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  * 提供两点线段需要的相关函数
  */

#include "sszn_basic.h"
#include "PointsLine.h"

/**
 * @brief 设置两点线段的结果大小
 * @param
 * @return 两点线段的结果大小
 * @author <Terry>
 * @note
 */
unsigned int PointsLine_Output_Size_Set(void)
{
    return sizeof(RST_VALUE_STRUCT)*P2PL_END;
}

/**
 * @brief 初始化两点线段结果的类型
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void PointsLine_Output_Memory_Type_Init(unsigned int step_index)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);

    DBL_RST_VALUE_INIT(pRst_Value, P2PL_THETA_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_DEGREE_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_ROTATE_DEG_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_COS_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_SIN_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_POINT_X_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_POINT_Y_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_PHY_POINT_X_ID);
    DBL_RST_VALUE_INIT(pRst_Value, P2PL_PHY_POINT_Y_ID);
}

/**
 * @brief 保存结果数据
 * @param
 * @return
 * @author <Terry>
 * @note
 */
int __P2PL_Output_Param_Set(unsigned int step_index, P2PL_RESULT *pp2pl_rst)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
    if(pRst_Value) {
        DBL_RST_VALUE_SET(pRst_Value, P2PL_THETA_ID, pp2pl_rst->p2p_line_rst.theta);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_DEGREE_ID, pp2pl_rst->p2p_line_rst.degree);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_ROTATE_DEG_ID, pp2pl_rst->p2p_line_rst.rotate_deg);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_COS_ID, pp2pl_rst->p2p_line_rst.cos);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_SIN_ID, pp2pl_rst->p2p_line_rst.sin);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_POINT_X_ID, pp2pl_rst->p2p_line_rst.x);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_POINT_Y_ID, pp2pl_rst->p2p_line_rst.y);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_PHY_POINT_X_ID, pp2pl_rst->p2p_line_rst.phy_x);
        DBL_RST_VALUE_SET(pRst_Value, P2PL_PHY_POINT_Y_ID, pp2pl_rst->p2p_line_rst.phy_y);
    }
    return 0;
}

void __P2PLine_Task_Post_Processing(unsigned int step_index, P2PL_RESULT *pp2pl_rst, int mid_result)
{
    if(mid_result) {
        Task_Step_Result_Output_Mem_Clear(step_index, P2PL_END);
    } else {
        __P2PL_Output_Param_Set(step_index, pp2pl_rst);
    }
}

int __P2PLine_Task_Run_Processing(TASK_P2P_LINE *pP2PLParam, P2PL_RESULT *pp2pl_rst, unsigned int model_flag)
{
    int ret = 0;
    POINT_F line_center, line_center_phy, point1, point2;

    ret = Task_Step_Link_Step_Check(P2PL_HEADER, 2, model_flag);
    if(ret) return ret;

    /* Get relate steps capture point result */
    ret = measure_ref_point_result_get(P2PL_HEADER->step_link.link_info[PPL_POINT1_SELECT].step_index,
                                       P2PL_HEADER->step_link.link_info[PPL_POINT1_SELECT].result_index,
                                       &point1, model_flag);
    if(ret) return ret;

    ret = measure_ref_point_result_get(P2PL_HEADER->step_link.link_info[PPL_POINT2_SELECT].step_index,
                                       P2PL_HEADER->step_link.link_info[PPL_POINT2_SELECT].result_index,
                                       &point2, model_flag);
    if(ret) return ret;
    /* 计算两点直线的参数 */
    pp2pl_rst->p2p_line_rst.x = (double)(point1.x_f + point2.x_f)/2;
    pp2pl_rst->p2p_line_rst.y = (double)(point1.y_f + point2.y_f)/2;
    pp2pl_rst->p2p_line_rst.theta = atan((point2.y_f-point1.y_f)/(point2.x_f-point1.x_f));
    Theta_to_Degree(pp2pl_rst->p2p_line_rst.theta, &(pp2pl_rst->p2p_line_rst.degree));
    pp2pl_rst->p2p_line_rst.rotate_deg = model_flag?0:(pp2pl_rst->p2p_line_rst.degree-P2PL_PTE_PARA->p2p_line.p2p_line_rst.degree);
    pp2pl_rst->p2p_line_rst.sin = sin(pp2pl_rst->p2p_line_rst.theta);
    pp2pl_rst->p2p_line_rst.cos = cos(pp2pl_rst->p2p_line_rst.theta);
	printf("theta: %.3f, degree: %.3f, rotate_degree: %.3f\n", 
		    pp2pl_rst->p2p_line_rst.theta, pp2pl_rst->p2p_line_rst.degree, pp2pl_rst->p2p_line_rst.rotate_deg);
    /* physical position */
    line_center.x_f = pp2pl_rst->p2p_line_rst.x;
    line_center.y_f = pp2pl_rst->p2p_line_rst.y;
    Homography_Convert(P2PL_HEADER->homo_index,
                       &line_center,
                       &line_center_phy,
                       HOMO_INPUT_SUB | HOMO_CVT_F);
    return ret;
}
/**
 * @brief 设置两点线段模板
 * @param
 * @return 0：模板设置成功，其它：失败
 * @author <Terry>
 * @note
 */
int PointsLine_Set(void *pTaskStructCommon)
{
    int ret = 0;
    TASK_P2P_LINE *pP2PLParam = (TASK_P2P_LINE *)(pTaskStructCommon);
    //DRV_PRINT(MEASURE_DEBUG, "%s\n", __FUNCTION__);

    memset(&P2PL_PTE_PARA->p2p_line, 0, sizeof(P2PL_RESULT));
    ret = __P2PLine_Task_Run_Processing(pP2PLParam, &P2PL_PTE_PARA->p2p_line, 1);

    return ret;
}

/**
 * @brief 两点线段运行
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int PointsLine_Run(void *pTaskStructCommon)
{
    int ret = 0;
    TASK_P2P_LINE *pP2PLParam = (TASK_P2P_LINE *)(pTaskStructCommon);
    P2PL_RESULT p2pl_rst = {{0}};
    //DRV_PRINT(MEASURE_DEBUG, "%s\n", __FUNCTION__);

    ret = __P2PLine_Task_Run_Processing(pP2PLParam, &p2pl_rst, 0);
    __P2PLine_Task_Post_Processing(P2PL_HEADER->step_index, &p2pl_rst, ret);

	return ret;
}

/**
 * @brief 两点线段模板结果拷贝到内存
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int PointsLine_Model_Rst_To_Output_Memory(unsigned int step_index)
{
    P2PL_PRIVATE_PARAM *pP2PLinePrivateParam = (P2PL_PRIVATE_PARAM *)Task_Step_Private_Para_Get(step_index);

    if(Task_Step_Model_Result_Valid_Flag_Check(step_index)){
        return TASK_REF_STEP_RST_FLAG_INVALID;
    }else{
        __P2PL_Output_Param_Set(step_index, &pP2PLinePrivateParam->p2p_line);
    }

    return 0;
}

TASK_CB_FUNC PointsLine_CallBack = {
    PointsLine_Output_Size_Set,
    PointsLine_Output_Memory_Type_Init,
    PointsLine_Model_Rst_To_Output_Memory,
    PointsLine_Set,
    PointsLine_Run,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief 获取两点线段功能的TASK_CB_FUNC结构体
 * @param
 * @return 两点线段回调函数结构体指针
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC * PointsLine_CallBack_Reg(void)
{
    return &PointsLine_CallBack;
}
