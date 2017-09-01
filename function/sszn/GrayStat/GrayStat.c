/**
  * @file  [GrayStat.c]
  * @brief  统计符合约束条件的像素数
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  * 计算符合约束条件的像素数
  */

#include "sszn_basic.h"
#include "GrayStat.h"
#include "fpga_global.h"

/**
 * @brief 设置彩色面积的结果大小
 * @param
 * @return 彩色面积的结果大小
 * @author <Terry>
 * @note
 */
unsigned int Gray_Stat_Output_Size_Set(void)
{
    return GRAY_STAT_END*sizeof(RST_VALUE_STRUCT);
}

/**
 * @brief 初始化彩色面积结果的类型
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void Gray_Stat_Output_Memory_Type_Init(unsigned int step_index)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);

    UINT_RST_VALUE_INIT(pRst_Value, GRAY_STAT_NUM);
    UINT_RST_VALUE_INIT(pRst_Value, GRAY_STAT_OK_NG_ID);
}

/**
 * @brief 写入结果数据
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void __Gray_Stat_Output_Param_Set(unsigned int step_index, GRAY_STAT_RESULT *pGrayStatRst)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
    if(pRst_Value) {
        UINT_RST_VALUE_SET(pRst_Value, GRAY_STAT_NUM, pGrayStatRst->pixel_num);
        UINT_RST_VALUE_SET(pRst_Value, GRAY_STAT_OK_NG_ID, pGrayStatRst->detect_ok_ng_flag);
    }
}
/**
 * @brief 设置彩色面积模板
 * @param
 * @return 0：模板设置成功，其它：失败
 * @author <Terry>
 * @note
 */
int Gray_Stat_Set(void *pTaskStructCommon)
{
    int ret = 0;
    TASK_GRAY_STAT_CHECK *pGrayStatParam = NULL;
    POINT_F pixel_center = {0};
    SELECT_MODEL_RESULT SelectModelResult = {0};
    pGrayStatParam = (TASK_GRAY_STAT_CHECK *)pTaskStructCommon;

    ret = Task_Step_Accelerator_Model_Work(GRAY_STAT_HEADER->step_index, 1);
    if(0 == ret){
        /* Read result from select model */
        Select_Model_Result_Get(&SelectModelResult);
        GRAY_STAT_PTE_PARA->model_stat_rst.pixel_num = SelectModelResult.valid_pixel_num;
    }else{
        return ret;
    }

    ret = Task_Compass_Info_Check_In_Model_Setting(GRAY_STAT_HEADER);
	return ret;
}

/**
 * @brief 彩色面积运行
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Gray_Stat_Run(void *pTaskStructCommon)
{
    int ret = 0;
    int vga_x, vga_y;
    TASK_GRAY_STAT_CHECK *pGrayStatParam = NULL;
    GRAY_STAT_RESULT area_center_rst = {0};
    SELECT_MODEL_RESULT SelectModelResult = {0};
    pGrayStatParam = (TASK_GRAY_STAT_CHECK *)pTaskStructCommon;

    ret = Task_Compass_Ref_Step_Run_Status_Check(GRAY_STAT_HEADER);
    if(0 == ret){
        ret = Task_Step_Accelerator_Model_Work(GRAY_STAT_HEADER->step_index, 0);
        if(0 == ret){
            /* Read result from select model */
            Select_Model_Result_Get(&SelectModelResult);
            area_center_rst.pixel_num = SelectModelResult.valid_pixel_num;
			ret = ThresholdIntCheck(&GRAY_STAT_IN_PARA->pixel_num_threshold, (int)(area_center_rst.pixel_num));
        }
    }
    area_center_rst.detect_ok_ng_flag = ret?DETECT_NG:DETECT_OK;
    __Gray_Stat_Output_Param_Set(GRAY_STAT_HEADER->step_index, &area_center_rst);

    return ret;
}

/**
 * @brief 彩色面积模板结果拷贝到内存
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Gray_Stat_Model_Rst_To_Output_Memory(unsigned int step_index)
{
	GRAY_STAT_PRIVATE_PARAM *pGrayStatPrivateParam = (GRAY_STAT_PRIVATE_PARAM *)Task_Step_Private_Para_Get(step_index);

	if(Task_Step_Model_Result_Valid_Flag_Check(step_index)){
		return TASK_REF_STEP_MODEL_RST_INVALID;
	}else{
		__Gray_Stat_Output_Param_Set(step_index, &pGrayStatPrivateParam->model_stat_rst);
	}
	
	return 0;
}

TASK_CB_FUNC Gray_Stat_CallBack = {
    Gray_Stat_Output_Size_Set,
    Gray_Stat_Output_Memory_Type_Init,
    Gray_Stat_Model_Rst_To_Output_Memory,
    Gray_Stat_Set,
    Gray_Stat_Run,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief 获取灰度统计功能的TASK_CB_FUNC结构体
 * @param
 * @return 灰度统计回调函数结构体指针
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC * GrayStat_CallBack_Reg(void)
{
    return &Gray_Stat_CallBack;
}


