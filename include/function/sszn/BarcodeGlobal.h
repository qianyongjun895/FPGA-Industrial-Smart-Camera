/**
  * @file  [ShapeCodeGlobal.h]
  * @brief  条形码扫描对外接口函数
  * @author  <th>
  * @date  <2017/7/25>
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

#define BARCODE_RESULT_LENGTH  1024
#define BARCODE_Segmentation_Data_Num      4
#define BARCODE_FAIL_OUTPUT_LENGTH         60
#define BARCODE_CMP_DATA_LENGTH            120

typedef enum{
	ERROR_TYPE_ID = 0,
	BARCODE_OK_NG_ID,
	BARCODE_TYPE_ID,
	BARCODE_RESULT_LENGTH_ID,
	BARCODE_ENUM_END
} BARCODE_RESULT;


typedef struct{
    unsigned int Data_flag;
    unsigned int start_bit;
    unsigned int length;
}BARCODE_READ_DATA_CONFIG;

typedef struct{
    unsigned int Fill_Flag;
    char Fill_Data;
    char pad[3];
}BARCODE_FILL_DATA_CONFIG;

typedef struct{
    unsigned int Fail_Output_Flag;
    char Fail_Output_Data[BARCODE_FAIL_OUTPUT_LENGTH];
}BARCODE_FAIL_OUTPUT_CONFIG;

typedef struct{
    int Cmp_Type;
    char Cmp_Data[BARCODE_CMP_DATA_LENGTH];
}BARCODE_CMP_DATA_CONFIG;

typedef struct {
    unsigned int Code_Type;
    unsigned int scale;
    unsigned int Read_Data_Flag;
    unsigned int start_bit;
    unsigned int Data_length;
    BARCODE_READ_DATA_CONFIG Data_Config[BARCODE_Segmentation_Data_Num];
    BARCODE_FILL_DATA_CONFIG Fill_Config;
    BARCODE_FAIL_OUTPUT_CONFIG Fail_Config;
    BARCODE_CMP_DATA_CONFIG Cmp_Config;
} BARCODE_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} BARCODE_OUTPUT_PARAM;

typedef struct {
	unsigned int OK_NG_Flag;
	unsigned int Code_Type;
	unsigned int Code_Length;
    char Code_Result[BARCODE_RESULT_LENGTH];
} BARCODE_RST;


typedef struct {
	BARCODE_RST Barcode_Rst;
} BARCODE_PRIVATE_PARAM;


typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    BARCODE_INPUT_PARAM *pBarcodeInputParam;
    BARCODE_OUTPUT_PARAM *pBarcodeOutputParam;
    BARCODE_PRIVATE_PARAM *pBarcodePrivateParam;
} TASK_BARCODE_CHECK;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif



