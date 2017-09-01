/**
  * @file  [MonoArea.c]
  * @brief  计算指定区域指定黑白面积功能
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  * 计算指定区域指定黑白面积功能
  */

#include "sszn_basic.h"
#include "MonoArea.h"
#include "fpga_global.h"
	
/**
 * @brief 设置黑白面积的结果大小
 * @param
 * @return 黑白面积的结果大小
 * @author <Terry>
 * @note
 */
unsigned int Mono_Area_Output_Size_Set(void)
{
	return MONO_AREA_END*sizeof(RST_VALUE_STRUCT);
}

/**
 * @brief 初始化黑白面积结果的类型
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void Mono_Area_Output_Memory_Type_Init(unsigned int step_index)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);

	UINT_RST_VALUE_INIT(pRst_Value, MONO_AREA);
	UINT_RST_VALUE_INIT(pRst_Value, MONO_AREA_OK_NG_ID);
}

/**
 * @brief 写入结果数据
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void __Mono_Area_Output_Param_Set(unsigned int step_index, MONO_AREA_RESULT *pMonoAreaRst)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
	if(pRst_Value) {
		UINT_RST_VALUE_SET(pRst_Value, MONO_AREA, pMonoAreaRst->area);
		UINT_RST_VALUE_SET(pRst_Value, MONO_AREA_OK_NG_ID, pMonoAreaRst->detect_ok_ng_flag);
	}
}
/**
 * @brief 设置黑白面积模板
 * @param
 * @return 0：模板设置成功，其它：失败
 * @author <Terry>
 * @note
 */
int Mono_Area_Set(void *pTaskStructCommon)
{
	int ret = 0;
	unsigned int blob_num = 0;
	unsigned int blob_index = 0;
	unsigned int total_area = 0;
	unsigned int white_area = 0;
	unsigned int black_area = 0;
	TASK_MONO_AREA_CHECK *pMonoAreaParam = NULL;
	SELECT_MODEL_RESULT SelectModelResult = {0};
	LINK_FPGA_RESULT *pLinkResult = (LINK_FPGA_RESULT *)GetLinkRstAddr();
	pMonoAreaParam = (TASK_MONO_AREA_CHECK *)pTaskStructCommon;

	ret = Task_Step_Accelerator_Model_Work(MONO_AREA_HEADER->step_index, 1);
	if(0 == ret){
		/* 先根据连通域计算白色区域的面积 */
		ret = Link_Model_Num_Get(&blob_num);
		if(ret){
			return ret;
		}
		for(blob_index = 0; blob_index < blob_num; blob_index++){
			white_area += pLinkResult[blob_index].pixel_num;
		}
		/* Read result from select model */
		Select_Model_Result_Get(&SelectModelResult);
		total_area = SelectModelResult.valid_pixel_num;
		if(MONO_AREA_IN_PARA->check_type == CHECK_BLACK_AREA){
			MONO_AREA_PTE_PARA->model_area_rst.area = total_area - white_area;
		}else{
			MONO_AREA_PTE_PARA->model_area_rst.area = white_area;
		}
	}else{
		return ret;
	}

	ret = Task_Compass_Info_Check_In_Model_Setting(MONO_AREA_HEADER);
	return ret;
}

/**
 * @brief 黑白面积运行
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Mono_Area_Run(void *pTaskStructCommon)
{
	int ret = 0;
	unsigned int blob_num = 0;
	unsigned int blob_index = 0;
	unsigned int total_area = 0;
	unsigned int white_area = 0;
	unsigned int black_area = 0;
	TASK_MONO_AREA_CHECK *pMonoAreaParam = NULL;
	MONO_AREA_RESULT area_center_rst = {0};
	SELECT_MODEL_RESULT SelectModelResult = {0};
	LINK_FPGA_RESULT *pLinkResult = (LINK_FPGA_RESULT *)GetLinkRstAddr();
	pMonoAreaParam = (TASK_MONO_AREA_CHECK *)pTaskStructCommon;

	ret = Task_Compass_Ref_Step_Run_Status_Check(MONO_AREA_HEADER);
	if(0 == ret){
		ret = Task_Step_Accelerator_Model_Work(MONO_AREA_HEADER->step_index, 0);
		if(0 == ret){
			/* 先根据连通域计算白色区域的面积 */
			ret = Link_Model_Num_Get(&blob_num);
			if(ret){
				__Mono_Area_Output_Param_Set(MONO_AREA_HEADER->step_index, &area_center_rst);
				return ret;
			}
			for(blob_index = 0; blob_index < blob_num; blob_index++){
				white_area += pLinkResult[blob_index].pixel_num;
			}
			/* Read result from select model */
			Select_Model_Result_Get(&SelectModelResult);
			total_area = SelectModelResult.valid_pixel_num;
			if(MONO_AREA_IN_PARA->check_type == CHECK_BLACK_AREA){
				area_center_rst.area = total_area - white_area;
			}else{
				area_center_rst.area = white_area;
			}

			ret = ThresholdIntCheck(&MONO_AREA_IN_PARA->area_threshold, (int)(area_center_rst.area));
		}
	}
	area_center_rst.detect_ok_ng_flag = ret?DETECT_NG:DETECT_OK;
	__Mono_Area_Output_Param_Set(MONO_AREA_HEADER->step_index, &area_center_rst);

	return ret;
}

/**
 * @brief 黑白面积模板结果拷贝到内存
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Mono_Area_Model_Rst_To_Output_Memory(unsigned int step_index)
{
	MONO_AREA_PRIVATE_PARAM *pMonoAreaPrivateParam = (MONO_AREA_PRIVATE_PARAM *)Task_Step_Private_Para_Get(step_index);

	if(Task_Step_Model_Result_Valid_Flag_Check(step_index)){
		return TASK_REF_STEP_MODEL_RST_INVALID;
	}else{
		__Mono_Area_Output_Param_Set(step_index, &pMonoAreaPrivateParam->model_area_rst);
	}

	return 0;
}

TASK_CB_FUNC Mono_Area_CallBack = {
    Mono_Area_Output_Size_Set,
    Mono_Area_Output_Memory_Type_Init,
    Mono_Area_Model_Rst_To_Output_Memory,
    Mono_Area_Set,
    Mono_Area_Run,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief 获取黑白面积功能的TASK_CB_FUNC结构体
 * @param
 * @return 黑白面积回调函数结构体指针
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC * MonoArea_CallBack_Reg(void)
{
    return &Mono_Area_CallBack;
}

