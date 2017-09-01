/**
  * @file  [QrCodeGlobal.h]
  * @brief  二维码扫描对外接口函数
  * @author  <th>
  * @date  <2017/7/19>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef __QR_CODE_GLOBAL_H_
#define __QR_CODE_GLOBAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "BaseStruct.h"
#include "TaskGlobal.h"

#define CODE_RESULT_LENGTH         1024
#define Segmentation_Data_Num      4
#define FAIL_OUTPUT_LENGTH         60
#define CMP_DATA_LENGTH            120
typedef enum{
	ERROR_TYPE_ID = 0,
    QC_OK_NG_ID,
    QC_CODE_TYPE_ID,
    QC_RESULT_LENGTH_ID,
    QC_ENUM_END
}QR_CODE_RESULT;

typedef struct{
    unsigned int Data_flag;
    unsigned int start_bit;
    unsigned int length;
}READ_DATA_CONFIG;

typedef struct{
    unsigned int Fill_Flag;
    char Fill_Data;
    char pad[3];
}FILL_DATA_CONFIG;

typedef struct{
    unsigned int Fail_Output_Flag;
    char Fail_Output_Data[FAIL_OUTPUT_LENGTH];
}FAIL_OUTPUT_CONFIG;

typedef struct{
    int Cmp_Type;
    char Cmp_Data[CMP_DATA_LENGTH];
}CMP_DATA_CONFIG;

typedef struct {
    unsigned int Code_Type;
    unsigned int scale;
    unsigned int Read_Data_Flag;
    unsigned int start_bit;
    unsigned int Data_length;
    READ_DATA_CONFIG Data_Config[Segmentation_Data_Num];
    FILL_DATA_CONFIG Fill_Config;
    FAIL_OUTPUT_CONFIG Fail_Config;
    CMP_DATA_CONFIG Cmp_Config;
} QR_CODE_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} QR_CODE_OUTPUT_PARAM;

typedef struct {
	unsigned int OK_NG_Flag;
	unsigned int Code_Type;
	unsigned int Code_Length;
    char Code_Result[CODE_RESULT_LENGTH];
} QR_CODE_RST;


typedef struct {
	QR_CODE_RST QR_Code_Rst;
} QR_CODE_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    QR_CODE_INPUT_PARAM *pQRInputParam;
    QR_CODE_OUTPUT_PARAM *pQROutputParam;
    QR_CODE_PRIVATE_PARAM *pQRPrivateParam;
}TASK_QR_CODE_CHECK;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif



