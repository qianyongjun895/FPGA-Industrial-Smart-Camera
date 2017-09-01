/**
  * @file  [GRstData.h]
  * @brief  全局数据管理接口
  * @author  <Terry>
  * @date  <2017/06/03>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef RST_DATA_H
#define RST_DATA_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "BaseStruct.h"

/**
 * @brief 设置int型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 *        s_int: 待保存的值
 * @return
 * @author <Terry>
 * @note
 */
void SINT_RST_VALUE_SET(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id, int s_int);

/**
 * @brief 设置unsigned int型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 *        u_int: 待保存的值
 * @return
 * @author <Terry>
 * @note
 */
void UINT_RST_VALUE_SET(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id, unsigned int u_int);

/**
 * @brief 设置float型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 *        f_data: 待保存的值
 * @return
 * @author <Terry>
 * @note
 */
void FLT_RST_VALUE_SET(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id, float f_data);

/**
 * @brief 设置double型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 *        d_data: 待保存的值
 * @return
 * @author <Terry>
 * @note
 */
void DBL_RST_VALUE_SET(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id, double d_data);

/**
 * @brief 初始化int型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 * @return
 * @author <Terry>
 * @note
 */
void SINT_RST_VALUE_INIT(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id);

/**
 * @brief 初始化unsigned int型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 * @return
 * @author <Terry>
 * @note
 */
void UINT_RST_VALUE_INIT(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id);

/**
 * @brief 初始化float型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 * @return
 * @author <Terry>
 * @note
 */
void FLT_RST_VALUE_INIT(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id);

/**
 * @brief 初始化double型结果数据
 * @param pRst_Value: 结果存储的指针
 *        enum_id: 枚举值
 * @return
 * @author <Terry>
 * @note
 */
void DBL_RST_VALUE_INIT(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_id);

/**
 * @brief 清除指定步骤的结果
 * @param step_index: 步骤索引
 *        enum_end: 枚举最大值
 * @return
 * @author <Terry>
 * @note
 */
void RST_VALUE_CLEAR(RST_VALUE_STRUCT *pRst_Value, unsigned int enum_end);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // RST_DATA_H

