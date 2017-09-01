/**
  * @file  [BlobGlobal.h]
  * @brief  blob对外接口函数
  * @author  <Terry>
  * @date  <2017/5/11>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _BLOB_GLOBAL_H_
#define _BLOB_GLOBAL_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"
#include "TaskGlobal.h"

#define CALC_DATA_NOT_INUSE	0
#define CALC_DATA_MANUAL	1
#define CALC_DATA_REF		2
#define CALC_DATA_MODBUS	3
#define CALC_DATA_PRE_ITEM	4
#define CALC_DATA_MIT_FX_PLC	5
#define CALC_DATA_DATA_INPUT	6

#define CALC_RST_NUM_MAX	4
#define CALC_OPRAND_NUM_MAX	4
#define CALC_ITEM_NUM_MAX	40

#define MODBUS_REG_TYPE_HOLD 0
#define MODBUS_REG_TYPE_INPUT 1

typedef enum {
	ERROR_TYPE_ID = 0,
    CALC_RESULT0,
    CALC_RESULT1,
    CALC_RESULT2,
    CALC_RESULT3,
    CALC_RESULT_NUM,
    CALC_OK_NG_ID,
    CALC_END
} Calculator_Result;

typedef enum {
    CALC_OPERATOR_ADD = 0,
    CALC_OPERATOR_SUBTRACT,
    CALC_OPERATOR_MULTIPLY,
    CALC_OPERATOR_DIVIDE,
    CALC_OPERATOR_MOD,
    CALC_OPERATOR_POWER,
    CALC_OPERATOR_LOGIC_NOT,
    CALC_OPERATOR_LOGIC_AND,
    CALC_OPERATOR_LOGIC_OR,
    CALC_OPERATOR_LOGIC_XOR,
    CALC_OPERATOR_COMPARE_EQUAL,
    CALC_OPERATOR_COMPARE_UNEQUAL,
    CALC_OPERATOR_COMPARE_GREATER,
    CALC_OPERATOR_COMPARE_SMALLER,
    CALC_OPERATOR_COMPARE_GREATER_OR_EQUAL,
    CALC_OPERATOR_COMPARE_SMALLER_OR_EQUAL,
    CALC_OPERATOR_MAX,
    CALC_OPERATOR_MIN,
    CALC_OPERATOR_MAX_INDEX,
    CALC_OPERATOR_MIN_INDEX,
    CALC_OPERATOR_ABS,
    CALC_OPERATOR_DEG,
    CALC_OPERATOR_RAD,
    CALC_OPERATOR_SQR,
    CALC_OPERATOR_SQRT,
    CALC_OPERATOR_CEIL,
    CALC_OPERATOR_FLOOR,
    CALC_OPERATOR_INT,
    CALC_OPERATOR_ROUND,
    CALC_OPERATOR_LN,
    CALC_OPERATOR_LG,
    CALC_OPERATOR_COS,
    CALC_OPERATOR_SIN,
    CALC_OPERATOR_TAN,
    CALC_OPERATOR_ACOS,
    CALC_OPERATOR_ASIN,
    CALC_OPERATOR_ATAN,
    CALC_OPERATOR_ATAN_P1P2,
    CALC_OPERATOR_BIT_NOT,
    CALC_OPERATOR_BIT_AND,
    CALC_OPERATOR_BIT_OR,
    CALC_OPERATOR_BIT_XOR,
    CALC_OPERATOR_END
}CALC_OPERATOR;

typedef enum {
    CALCOP_TYPE_ARITHMETIC_OPERATOR = 0,
    CALCOP_TYPE_LOGICAL_OPERATOR,
    CALCOP_TYPE_COMPARE_OPERATOR,
    CALCOP_TYPE_GENERAL_FUNCTION,
    CALCOP_TYPE_TRIGONOMETRY_FUNCTION,
    CALCOP_TYPE_BIT_OPERATOR,
    CALCOP_TYPE_END
} CALC_OPERATOR_TYPE;

typedef enum {
    CALC_MODBUS_DATA_TYPE_INT = 0,
    CALC_MODBUS_DATA_TYPE_FLOAT,
    CALC_MODBUS_DATA_TYPE_LONG,
    CALC_MODBUS_DATA_TYPE_DOUBLE,
    CALC_MODBUS_DATA_TYPE_INT_R,
    CALC_MODBUS_DATA_TYPE_FLOAT_R,
    CALC_MODBUS_DATA_TYPE_LONG_R,
    CALC_MODBUS_DATA_TYPE_DOUBLE_R,
    CALC_MODBUS_DATA_TYPE_END
} CALC_MODBUS_DATA_TYPE;

typedef struct{
    float manual_input_op;	/* 手动输入参数 */
}CALC_MANUAL_OP;

typedef struct {
    unsigned short step_index;        /* 步骤索引 */
    unsigned short result_index;      /* 结果索引，对应步骤结果的ID */
}CALC_REF_OP;

typedef struct {
    unsigned char reg_type;		/* 保持寄存器、输入寄存器 */
    unsigned char data_type;	/* 寄存器里面数据保存的格式，整形、浮点型。。。，影响访问数据的长度 */
    unsigned short reg_addr;	/* 寄存器起始地址 */
}CALC_MBREG_OP;

typedef struct {
    unsigned char data_type;	/* 寄存器里面数据保存的格式，整形、浮点型。。。，影响访问数据的长度 */
    unsigned char pad;			/* 对齐 */
    unsigned short reg_addr;	/* 寄存器起始地址 */
}CALC_MIT_FXPLC_REG_OP;

typedef struct {
    unsigned short pre_item_id;	/* 之前计算item的索引 */
    unsigned short result_id;	/* 结果索引 */
}CALC_PREITEM_OP;

typedef struct{
    unsigned int data_input_type; /* 0:手动配置 1：动态配置 */
    unsigned int data_input_addr; /* 数据输入的地址 */
}CALC_INPUT_DATA_OP;

typedef struct {
    unsigned int op_type;	/* 数据格式的类型 */
    union {
        CALC_MANUAL_OP manual_op;	/* 手动输入的计算参数 */
        CALC_REF_OP ref_value_op;	/* 引用步骤的计算参数 */
        CALC_MBREG_OP modbus_op;	/* modbus寄存器参数 */
        CALC_MIT_FXPLC_REG_OP mit_fx_plc_op;	    /* mit fx系列PLC寄存器参数 */
        CALC_PREITEM_OP pre_item;	/* 引用前面计算项的结果 */
        CALC_INPUT_DATA_OP data_input; /* 数据输入的参数 */
    }oprand;
}CALC_OPRAND;

typedef struct {
    unsigned int result_num;		/* 结果个数 ,根据计算类型输入时设置好*/
    float result[CALC_RST_NUM_MAX];	/* 结果 */
}CALC_RST;

typedef struct {
    unsigned int calc_ok_ng;		/* 最终计算OK\NG */
    unsigned int result_num;		/* 结果个数 ,根据计算类型输入时设置好*/
    float result[CALC_RST_NUM_MAX];	/* 结果 */
}CALC_GLOBAL_RST;

typedef struct {
    unsigned short calc_main_type;		/* 运算符种类,算术运算符、逻辑运算符、三角运算符...,UI显示要用  */
    unsigned short calc_sub_type;		/* CALC_OPERATOR里面对应的操作符 */
    unsigned int oprand_num;			/* CPU0在初始化数据的时候就设置好该参数 */
    CALC_OPRAND calc_op[CALC_OPRAND_NUM_MAX];	/* 计算参数 */
    CALC_RST calc_rst_local;			/* 本部计算结果 */
}CALC_ITEM;

typedef struct {
    unsigned int calc_item_count; /* 计算项的总数，最大 CALC_ITEM_NUM_MAX  */
    unsigned char calc_select_flag[CALC_ITEM_NUM_MAX]; /* 记录计算项是否选中，UI使用  */
} CALC_INPUT_PARAM;

typedef struct {
    OUTPUT_COMMON_PARAM	common_param;	/* common parameter */
} CALC_OUTPUT_PARAM;

typedef struct {
    PRIVATE_COMMON_PARAM private_common;	/* 私有数据的公共结构体 */
    CALC_ITEM calc_item[CALC_ITEM_NUM_MAX];	/* Input结构体中存放不下，放在private中 */
} CALC_PRIVATE_PARAM;

typedef struct {
    TASK_STEP_HEADER *pStepHeader;
    CALC_INPUT_PARAM *pCalcInputParam;
    CALC_OUTPUT_PARAM *pCalcOutputParam;
    CALC_PRIVATE_PARAM *pCalcPrivateParam;
}TASK_CALC_CALC;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
