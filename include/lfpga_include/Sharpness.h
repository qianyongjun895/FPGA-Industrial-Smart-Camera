#ifndef SHARPNESS_H
#define SHARPNESS_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P5)边缘强调模块寄存器 */
#define SHARPNESS_CTRL_REG              0x127       ///< 边缘强调控制寄存器
#define SHARPNESS_CTRL_EN_MASK          0x1         ///< 模块使能掩码
#define SHARPNESS_CTRL_EN_OFFSET        0
#define SHARPNESS_CTRL_LEVEL_MASK       0x3f00      ///< 边缘强调强度，有效值0~63
#define SHARPNESS_CTRL_LEVEL_OFFSET     8



#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Sharpness_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化边缘强调模块参数
 */
DLLSHARED_EXPORT int Sharpness_Model_Init(u32 acce_index);

/**
 * @brief Sharpness_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块参数设置函数
 */
DLLSHARED_EXPORT int Sharpness_Model_Param_Set(u32 acce_index);

/**
 * @brief Sharpness_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块输入源获取
 */
DLLSHARED_EXPORT inline int Sharpness_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Sharpness_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块输出结果获取
 */
DLLSHARED_EXPORT void Sharpness_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Sharpness_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块使能关闭
 */
DLLSHARED_EXPORT inline void Sharpness_Model_Disable(void);

/**
 * @brief Sharpness_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块使能开启
 */
DLLSHARED_EXPORT inline void Sharpness_Model_Enable(void);

/**
 * @brief Sharpness_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void Sharpness_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Sharpness_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Sharpness_Model_Write_DDR_Off(void);

/**
 * @brief Sharpness_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块寄存器参数打印
 */
DLLSHARED_EXPORT void Sharpness_Model_Reg_Show(void);

/**
 * @brief Sharpness_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id: 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘强调模块输入源设置
 */
DLLSHARED_EXPORT inline void Sharpness_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

/**
 * @brief Set_Sharpness_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置边缘强调模块使能状态
 */
DLLSHARED_EXPORT void Set_Sharpness_Enable(u32 flag);

/**
 * @brief Set_Sharpness_Level
 * @param level
 * @author Vincent
 * @date 2017/5/12
 * @note 设置边缘强调强度
 */
DLLSHARED_EXPORT void Set_Sharpness_Level(u32 level);

#ifdef __cplusplus
}
#endif

#endif // SHARPNESS_H
