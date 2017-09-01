/**
  * @file  [ColorArea.c]
  * @brief  计算指定区域指定颜色面积功能
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  * 计算指定区域指定颜色面积功能
  */

#include "sszn_basic.h"
#include "ColorArea.h"
#include "fpga_global.h"

/**
 * @brief 设置彩色面积的结果大小
 * @param
 * @return 彩色面积的结果大小
 * @author <Terry>
 * @note
 */
unsigned int Color_Area_Output_Size_Set(void)
{
    return COLOR_AREA_END*sizeof(RST_VALUE_STRUCT);
}

/**
 * @brief 初始化彩色面积结果的类型
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void Color_Area_Output_Memory_Type_Init(unsigned int step_index)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);

    UINT_RST_VALUE_INIT(pRst_Value, COLOR_AREA);
    UINT_RST_VALUE_INIT(pRst_Value, COLOR_AREA_OK_NG_ID);
}

/**
 * @brief 写入结果数据
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void __Color_Area_Output_Param_Set(unsigned int step_index, COLOR_AREA_RESULT *pColorAreaRst)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
    if(pRst_Value) {
        UINT_RST_VALUE_SET(pRst_Value, COLOR_AREA, pColorAreaRst->area);
        UINT_RST_VALUE_SET(pRst_Value, COLOR_AREA_OK_NG_ID, pColorAreaRst->detect_ok_ng_flag);
    }
}
/**
 * @brief 设置彩色面积模板
 * @param
 * @return 0：模板设置成功，其它：失败
 * @author <Terry>
 * @note
 */
int Color_Area_Set(void *pTaskStructCommon)
{
    int ret = 0;
    TASK_COLOR_AREA_CHECK *pColorAreaParam = NULL;
    POINT_F pixel_center = {0};
    SELECT_MODEL_RESULT SelectModelResult = {0};
    pColorAreaParam = (TASK_COLOR_AREA_CHECK *)pTaskStructCommon;

    ret = Task_Step_Accelerator_Model_Work(COLOR_AREA_HEADER->step_index, 1);
    if(0 == ret){
        /* Read result from select model */
        Select_Model_Result_Get(&SelectModelResult);
        COLOR_AREA_PTE_PARA->model_area_rst.area = SelectModelResult.valid_pixel_num;
    }else{
        return ret;
    }

    ret = Task_Compass_Info_Check_In_Model_Setting(COLOR_AREA_HEADER);
	return ret;
}

/**
 * @brief 彩色面积运行
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Color_Area_Run(void *pTaskStructCommon)
{
    int ret = 0;
    int vga_x, vga_y;
    TASK_COLOR_AREA_CHECK *pColorAreaParam = NULL;
    COLOR_AREA_RESULT area_center_rst = {0};
    SELECT_MODEL_RESULT SelectModelResult = {0};
    pColorAreaParam = (TASK_COLOR_AREA_CHECK *)pTaskStructCommon;

    ret = Task_Compass_Ref_Step_Run_Status_Check(COLOR_AREA_HEADER);
    if(0 == ret){
        ret = Task_Step_Accelerator_Model_Work(COLOR_AREA_HEADER->step_index, 0);
        if(0 == ret){
            /* Read result from select model */
            Select_Model_Result_Get(&SelectModelResult);
            area_center_rst.area = SelectModelResult.valid_pixel_num;
			ret = ThresholdIntCheck(&COLOR_AREA_IN_PARA->area_threshold, (int)(area_center_rst.area));
        }
    }
    area_center_rst.detect_ok_ng_flag = ret?DETECT_NG:DETECT_OK;
    __Color_Area_Output_Param_Set(COLOR_AREA_HEADER->step_index, &area_center_rst);

    return ret;
}

/**
 * @brief 彩色面积模板结果拷贝到内存
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Color_Area_Model_Rst_To_Output_Memory(unsigned int step_index)
{
	COLOR_AREA_PRIVATE_PARAM *pColorAreaPrivateParam = (COLOR_AREA_PRIVATE_PARAM *)Task_Step_Private_Para_Get(step_index);

	if(Task_Step_Model_Result_Valid_Flag_Check(step_index)){
		return TASK_REF_STEP_MODEL_RST_INVALID;
	}else{
		__Color_Area_Output_Param_Set(step_index, &pColorAreaPrivateParam->model_area_rst);
	}
	
	return 0;
}

TASK_CB_FUNC Color_Area_CallBack = {
    Color_Area_Output_Size_Set,
    Color_Area_Output_Memory_Type_Init,
    Color_Area_Model_Rst_To_Output_Memory,
    Color_Area_Set,
    Color_Area_Run,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief 获取彩色面积功能的TASK_CB_FUNC结构体
 * @param
 * @return 彩色面积回调函数结构体指针
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC * ColorArea_CallBack_Reg(void)
{
    return &Color_Area_CallBack;
}

