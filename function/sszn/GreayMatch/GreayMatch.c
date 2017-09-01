/**
  * @file  [GreayMatch.c]
  * @brief  计算灰度匹配得分的功能
  * @author  <Terry>
  * @date  <2017/6/20>
  * @version  <v1.0>
  * @note
  * 计算灰度匹配得分的功能
  */

#include "sszn_basic.h"
#include "GreayMatch.h"
#include "fpga_global.h"
#include<stdio.h>
#include<string.h>


/**
 * @brief 设置黑白面积的结果大小
 * @param
 * @return 黑白面积的结果大小
 * @author <Terry>
 * @note
 */
unsigned int Greay_Match_Output_Size_Set(void)
{
	return GREAY_MATCH_END*sizeof(RST_VALUE_STRUCT);
}

/**
 * @brief 初始化输出匹配分数
 * @param
 * @return
 * @author <Terry>
 * @note
 */
void Greay_Match_Output_Memory_Type_Init(unsigned int step_index)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);

	UINT_RST_VALUE_INIT(pRst_Value, GREAY_MATCH_SCORE);
	UINT_RST_VALUE_INIT(pRst_Value, GREAY_MATCH_OK_NG_ID);
}

void __Greay_Match_Output_Param_Set(unsigned int step_index, GREAY_MATCH_RESULT *pGreayMatchRst)
{
	RST_VALUE_STRUCT *pRst_Value = TaskStepResultMemGet(step_index);
	if(pRst_Value) {
		UINT_RST_VALUE_SET(pRst_Value, GREAY_MATCH_SCORE, pGreayMatchRst->Score);
		UINT_RST_VALUE_SET(pRst_Value, GREAY_MATCH_OK_NG_ID, pGreayMatchRst->detect_ok_ng_flag);
	}
}

int Alg_Difference(void *ModelBuf,void *Currbuf,int nWidth,int nHeight,THRESHOLD_INT rect,int nDifferValue, int *nSimilarity)
{
	int i,j; 
	int nNgNum = 0;   // 与原图灰度差异大于阈值的像素点数量
	int nSumNum = 0;  // 像素点总数量
    unsigned char *SrcImage = (unsigned char *)Currbuf;
	unsigned char *ModelImage = (unsigned char *)ModelBuf;
	
	for (j=rect.low_enable;j<rect.low_threshold;j++)
	{
		for (i=rect.high_enable;i<rect.high_threshold;i++)
		{
			nSumNum++;
			if ( abs(ModelImage[j*nWidth+i] - SrcImage[j*nWidth+i]) > nDifferValue) 
			{
				nNgNum++;
			}
		}
	}

	if(nSumNum >0)
	{
		nSimilarity =((nSumNum-nNgNum)*1000)/nSumNum;
	}

	return 0;
}


int Greay_Match_Set(void *pTaskStructCommon,unsigned int step_index)
{
	int ret = 0;
	TASK_GREAY_MATCH_CHECK *pGreayMatchParam = NULL;
	pGreayMatchParam = (TASK_GREAY_MATCH_CHECK *)pTaskStructCommon;	
	pGreayMatchParam->pGreayMatchInputParam->Mod_Image_Ptr =  GetCptColorPicAddr(); //获取模板图片的指针
	void* Mode_Ptr = NULL;
	unsigned int iWithe = Get_HWC_Pixel_Width(); //获取图片的宽度
	unsigned int iHeight = Get_HWC_Pixel_Height(); //获取图片的高度
	GetTaskStepModelAddr(step_index,iWithe*iHeight*3,Mode_Ptr); //根据ID确定模板的的保存地址
	memcpy(pGreayMatchParam->pGreayMatchInputParam->Mod_Image_Ptr,Mode_Ptr,iWithe*iHeight*3);
	Alg_Difference(pGreayMatchParam->pGreayMatchInputParam->Mod_Image_Ptr,GetCptColorPicAddr(),iWithe,iHeight,pGreayMatchParam->pGreayMatchInputParam->In_Put_ROI,pGreayMatchParam->pGreayMatchInputParam->Differential_threshold,pGreayMatchParam->pGreayMatchInputParam->Score);//算法执行函数
	
	return ret;
}

/*算法执行函数*/
int Greay_Match_Run(void *pTaskStructCommon)
{
	int ret = 0;
	TASK_GREAY_MATCH_CHECK *pGreayMatchParam = NULL;
	pGreayMatchParam = (TASK_GREAY_MATCH_CHECK *)pTaskStructCommon;	
	unsigned int iWithe = Get_HWC_Pixel_Width(); //获取图片的宽度
	unsigned int iHeight = Get_HWC_Pixel_Height(); //获取图片的高度
	void *Mod_Image = pGreayMatchParam->pGreayMatchInputParam->Mod_Image_Ptr;
	Alg_Difference(Mod_Image,GetCptColorPicAddr(),iWithe,iHeight,pGreayMatchParam->pGreayMatchInputParam->In_Put_ROI,pGreayMatchParam->pGreayMatchInputParam->Differential_threshold,pGreayMatchParam->pGreayMatchInputParam->Score);//算法执行函数
	if(pGreayMatchParam->pGreayMatchInputParam->Min_Score<pGreayMatchParam->pGreayMatchInputParam->Score<pGreayMatchParam->pGreayMatchInputParam->Max_Score)
	{
		pGreayMatchParam->pGreayMatchPrivateParam->model_area_rst.detect_ok_ng_flag = 0;
		pGreayMatchParam->pGreayMatchPrivateParam->model_area_rst.Score = pGreayMatchParam->pGreayMatchInputParam->Score;
	}
	else
	{
		pGreayMatchParam->pGreayMatchPrivateParam->model_area_rst.detect_ok_ng_flag = 1;
		pGreayMatchParam->pGreayMatchPrivateParam->model_area_rst.Score = pGreayMatchParam->pGreayMatchInputParam->Score;
	}
	return ret;

}

//拷贝结果到指针内存里面
int Greay_Match_Model_Rst_To_Output_Memory(unsigned int step_index)
{
	GREAY_MATCH_PRIVATE_PARAM *pMonoAreaPrivateParam = (GREAY_MATCH_PRIVATE_PARAM *)Task_Step_Private_Para_Get(step_index); //获取内存结果的接口

	//内存的结果接口
	if(Task_Step_Model_Result_Valid_Flag_Check(step_index)){
		return TASK_REF_STEP_MODEL_RST_INVALID;
	}else{
		__Greay_Match_Output_Param_Set(step_index, &pMonoAreaPrivateParam->model_area_rst);
	}

	return 0;
}

TASK_CB_FUNC Greay_Match_CallBack = {
    Greay_Match_Output_Size_Set,
    Greay_Match_Output_Memory_Type_Init,
    Greay_Match_Model_Rst_To_Output_Memory,
    Greay_Match_Set,
    Greay_Match_Run,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

TASK_CB_FUNC * Greay_Match_Reg(void)
{
    return &Greay_Match_CallBack;
}


