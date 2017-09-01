#ifndef __ERROR_CODE_H_
#define __ERROR_CODE_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define STEP_NOT_EXEC				0xdeadbeef
#define MMAP_TASK_ADDR_FAIL         0x10000000
#define MMAP_RST_ADDR_FAIL          0x10000001
#define MMAP_MODEL_ADDR_FAIL        0x10000002
#define MMAP_ACCE_ADDR_FAIL         0x10000002

#define INPUT_POINTER_NULL          0x10001000
#define MALLOC_FAIL                 0x10001001
#define INDEX_OUT_OF_RANGE          0x10001002
#define STRING_LEN_OUT_OF_RANGE     0x10001003
#define BUFFER_LEN_NOT_ENOUGH       0x10001004

/* 任务相关错误 */
#define TASK_STEP_INDEX_INVALID                 0x20000000
#define TASK_TYPE_ID_INVALID                    0x20000001
#define TASK_INPUT_PARA_INVALID                 0x20000002
#define TASK_STEP_COUNT_INVALID                 0x20000003
#define TASK_REF_STEP_RST_TYPE_INVALID          0x20000004
#define TASK_REF_STEP_RST_ADDR_INVALID          0x20000005
#define TASK_REF_STEP_RST_FLAG_INVALID          0x20000006
#define TASK_REF_STEP_RUN_STATUS_FAIL           0x20000007
#define TASK_REF_STEP_MODEL_RST_INVALID         0x20000008
#define TASK_REF_STEP_NUM_UNMATCH               0x20000009
#define TASK_REF_STEP_EXEC_OFF                  0x2000000a
#define TASK_HEAD_POINTER_NULL                  0x2000000b
#define TASK_STEP_PARAM_INVALID                 0x2000000c
#define TASK_CBF_PARENT_POINTER_INVALID         0x2000000d
#define TASK_CBF_CHILD_POINTER_INVALID          0x2000000e
#define TASK_MODEL_MEM_ALLOC_FAIL				0x2000000f
#define TASK_MODEL_MEM_UNUSED_SIZE_NOT_ENOUGH   0x20000010
#define TASK_MODEL_MEM_FREE_SIZE_NOT_ENOUGH     0x20000011
#define TASK_COMPASS_NOT_ENABLE                 0x20000012      ///< 任务关联定位没有使能
#define TASK_COMPASS_PARAM_ERROR                0x20000013      ///< 关联定位参数存在空的
#define TASK_HOMO_PARA_GET_FAIL					0x20000014
#define TASK_SCALE_PARA_GET_FAIL				0x20000015
#define TASK_OUTPUT_MEM_ALLOC_FAIL				0x20000016
#define TASK_OUTPUT_RST_INDEX_INVALID			0x20000017		///< 输出结果的索引号无效
#define TASK_ACCE_MODEL_OUTPUT_GET_FAILED		0x20000018		///< 加速器输出地址获取失败

#define TASK_HAS_NO_CBFUN                       0x20000100
#define TASK_HAS_NO_OPSIZE_CBFUN                0x20000101
#define TASK_HAS_NO_MEM_TYPE_INIT_CBFUN         0x20000102
#define TASK_HAS_NO_M2O_CBFUN                   0x20000103
#define TASK_HAS_NO_SET_CBFUN                   0x20000104
#define TASK_HAS_NO_RUN_CBFUN                   0x20000105
#define TASK_HAS_NO_RST_CNT_GET_CBFUN           0x20000106
#define TASK_HAS_NO_LINK_UPDATE_CBFUN           0x20000107
#define TASK_HAS_NO_DEL_UPDATE_CBFUN            0x20000108
#define TASK_HAS_NO_LINKED_CHK_CBFUN            0x20000109

#define CALC_UNKNOWN_OPERATOR                   0x20001000
#define CALC_OPRAND_TYPE_INVALID                0x20001001
#define CALC_OPRAND_REF_DATA_INVALID            0x20001002
#define CALC_OPRAND_REF_STEP_INVALID            0x20001003
#define CALC_OPRAND_REF_DATA_NULL               0x20001004
#define CALC_MODBUS_DATA_TYPE_INVALID           0x20001005
#define CALC_PRE_ITEM_INDEX_INVALID             0x20001006
#define CALC_LN_OPRAND_NEGTIVE                  0x20001007
#define CALC_LG_OPRAND_NEGTIVE                  0x20001008
#define CALC_SQRT_OPRAND_NEGTIVE                0x20001009

/* 门限相关错误 */
#define TH_CHK_LOWER_THAN_LOW                   0x20002000
#define TH_CHK_HIGHER_THAN_HIGH                 0x20002001
#define TH_SET_LOW_HIGHER_THAN_HIGH             0x20002002

/* 像素转换错误 */
#define CVT_UNKNOWN_CVT_TYPE                    0x20003000
#define CVT_UNKNOWN_DATA_TYPE                   0x20003001
#define CVT_UNKNOWN_POINTER_TYPE                0x20003002
#define CVT_UNSUPPORT_DBL_POINT					0x20003003

/* 全局数据相关错误 */
#define G_DATA_INDEX_OUT_RANGE					0x20004000
#define G_DATA_TYPE_UNKNOWN						0x20004001
#define G_DATA_SAVE_FAILED						0x20004002
#define G_DATA_INVALID							0x20004003
#define G_DATA_FILE_NOT_EXIST					0x20004004

/* 多套CMOS参数相关错误 */
#define M_CMOS_PARAM_INDEX_INVALID				0x20005000
#define M_CMOS_PARAM_SAVE_FAILED				0x20005001
#define M_CMOS_PARAM_READ_FAILED				0x20005002
#define M_CMOS_PARAM_FILE_NOT_EXIST				0x20005003
#define M_CMOS_PARAM_INVALID					0x20005004


#define LINES_PARALLELISM_NOT_WELL              0x30000000

#define ERR_FPGA_ACCE_INT_TIMEOUT				0x06000900		/* FPGA 中断等待超时 */

/* 脚本相关错误 */
#define SCRIPT_FILE_NOT_EXIST					0x07000000		/* 脚本文件不存在 */
#define SCRIPT_TYPE_UNKNOW						0x07000001		/* 脚本类型不明 */
#define SCRIPT_RST_NUM_OVER						0x07000002		/* 脚本结果数量超过上限 */
#define SCRIPT_EXEC_UNFINISH					0x07000003		/* 脚本任务未执行完成 */

/* 统计相关错误 */
#define DATA_STST_REF_VALUE_STEP_GREATER		0x07001000		/* 索引数据步骤超过最大步骤 */
#define DATA_STST_OPRAND_REF_VALUE_INVALD		0x07001001		/* 索引数据无效 */
#define DATA_STST_CALC_REF_STEP_MEM_NULL		0x07001002		/* 索引步骤内存地址无效 */
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
