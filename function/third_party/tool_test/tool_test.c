/**
  * @file  [tool_test.c]
  * @brief 新功能增加的示例
  * @author  <Terry>
  * @date  <2017/7/15>
  * @version  <v1.0>
  * @note
  * 
  */

#include "sszn_basic.h"
#include "tool_test.h"
#include "my_add.h"
	
/**
 * @brief 设置新功能的结果大小
 * @param
 * @return 新功能的结果大小
 * @author <Terry>
 * @note
 */
unsigned int Tool_Test_Output_Size_Set(void)
{
	return TOOL_TEST_ENUM_END*sizeof(RST_VALUE_STRUCT);
}

/**
 * @brief 初始化新功能结果的类型
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void Tool_Test_Output_Memory_Type_Init(unsigned int step_index)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
	SINT_RST_VALUE_INIT(pRst_Value, TOOL_TEST_RST1);
	FLT_RST_VALUE_INIT(pRst_Value, TOOL_TEST_RST2);
	FLT_RST_VALUE_INIT(pRst_Value, TOOL_TEST_POINT_PIX_X);
	FLT_RST_VALUE_INIT(pRst_Value, TOOL_TEST_POINT_PIX_Y);
	FLT_RST_VALUE_INIT(pRst_Value, TOOL_TEST_POINT_PHY_X);
	FLT_RST_VALUE_INIT(pRst_Value, TOOL_TEST_POINT_PHY_Y);
}

/**
 * @brief 写入结果数据
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void __Tool_Test_Output_Param_Set(unsigned int step_index, TOOLTEST_RESULT *pToolTestRst)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
	if(pRst_Value) {
		SINT_RST_VALUE_SET(pRst_Value, TOOL_TEST_RST1, pToolTestRst->rst1);
		FLT_RST_VALUE_SET(pRst_Value, TOOL_TEST_RST2, pToolTestRst->rst2);
		FLT_RST_VALUE_SET(pRst_Value, TOOL_TEST_POINT_PIX_X, pToolTestRst->point_pix.x_f);
		FLT_RST_VALUE_SET(pRst_Value, TOOL_TEST_POINT_PIX_Y, pToolTestRst->point_pix.y_f);
		FLT_RST_VALUE_SET(pRst_Value, TOOL_TEST_POINT_PHY_X, pToolTestRst->point_phy.x_f);
		FLT_RST_VALUE_SET(pRst_Value, TOOL_TEST_POINT_PHY_Y, pToolTestRst->point_phy.y_f);
	}
}
/**
 * @brief 设置新功能模板
 * @param
 * @return 0：模板设置成功，其它：失败
 * @author <Terry>
 * @note
 */
int Tool_Test_Set(void *pTaskStructCommon)
{
	int ret = 0;
	TASK_TOOL_TEST *pToolTestParam = (TASK_TOOL_TEST *)pTaskStructCommon;

	TOOL_TEST_PTE_PARA->model_testtool_rst.rst1 = TOOL_TEST_IN_PARA->param1;
	TOOL_TEST_PTE_PARA->model_testtool_rst.rst1 = TOOL_TEST_IN_PARA->param2;

	ret = Task_Compass_Info_Check_In_Model_Setting(TOOL_TEST_HEADER);
	return ret;
}

/**
 * @brief 新功能运行
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Tool_Test_Run(void *pTaskStructCommon)
{
	int ret = 0;
	TOOLTEST_RESULT tool_test_rst;
	TASK_TOOL_TEST *pToolTestParam = (TASK_TOOL_TEST *)pTaskStructCommon;

	tool_test_rst.rst1 = add_2num(TOOL_TEST_IN_PARA->param1, TOOL_TEST_IN_PARA->param2);//shit
	tool_test_rst.rst2 = pow(tool_test_rst.rst1, 2);

	tool_test_rst.point_pix.x_f = 120;
	tool_test_rst.point_pix.y_f = 240;
	PixelCvt(&tool_test_rst.point_pix, &tool_test_rst.point_pix, CVT_VGA2SUB|CVT_F2F|CVT_POINT);
	Homography_Convert(TOOL_TEST_HEADER->homo_index, &tool_test_rst.point_pix, &tool_test_rst.point_phy, HOMO_CVT_F | HOMO_INPUT_SUB);
	
	__Tool_Test_Output_Param_Set(TOOL_TEST_HEADER->step_index, &tool_test_rst);

	return ret;
}

/**
 * @brief 新功能模板结果拷贝到内存
 * @param
 * @return 0：成功，其它：失败
 * @author <Terry>
 * @note
 */
int Tool_Test_Model_Rst_To_Output_Memory(unsigned int step_index)
{
	TOOLTEST_PRIVATE_PARAM *pToolTestPrivateParam = (TOOLTEST_PRIVATE_PARAM *)Task_Step_Private_Para_Get(step_index);
	
	if(Task_Step_Model_Result_Valid_Flag_Check(step_index)){
		return TASK_REF_STEP_MODEL_RST_INVALID;
	}else{
		__Tool_Test_Output_Param_Set(step_index, pToolTestPrivateParam->model_testtool_rst);
	}
	
	return 0;
}

TASK_CB_FUNC Tool_Test_CallBack = {
    Tool_Test_Output_Size_Set,
    Tool_Test_Output_Memory_Type_Init,
    Tool_Test_Model_Rst_To_Output_Memory,
    Tool_Test_Set,
    Tool_Test_Run,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief 获取新功能功能的TASK_CB_FUNC结构体
 * @param
 * @return 新功能回调函数结构体指针
 * @author <Terry>
 * @note
 */
TASK_CB_FUNC * TestTool_CallBack_Reg(void)
{
    return &Tool_Test_CallBack;
}

