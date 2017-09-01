#ifndef BLUR_H
#define BLUR_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P1)模糊处理模块寄存器 */
#define BLUR_CTRL_REG               0x133       ///< 模糊处理控制寄存器
#define BLUR_CTRL_EN_MASK           0x1         ///< 模块使能掩码
#define BLUR_CTRL_EN_OFFSET         0
#define BLUR_CTRL_MODE_SEL_MASK     0xf0        ///< 模糊处理模式选择，有效值为1-9
#define BLUR_CTRL_MODE_SEL_OFFSET   4



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Blur_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化模糊处理模块参数
 */
DLLSHARED_EXPORT int Blur_Model_Init(u32 acce_index);

/**
 * @brief Blur_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块参数设置函数
 */
DLLSHARED_EXPORT int Blur_Model_Param_Set(u32 acce_index);

/**
 * @brief Blur_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块输入源获取
 */
DLLSHARED_EXPORT inline int Blur_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Blur_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块输出数据获取
 */
DLLSHARED_EXPORT void Blur_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Blur_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块使能关闭
 */
DLLSHARED_EXPORT inline void Blur_Model_Disable(void);

/**
 * @brief Blur_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块使能开启
 */
DLLSHARED_EXPORT inline void Blur_Model_Enable(void);

/**
 * @brief Blur_Model_Write_DDR_On
 * @param acce_index
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块写DDR使能开启
 */
DLLSHARED_EXPORT inline void Blur_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Blur_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Blur_Model_Write_DDR_Off(void);

/**
 * @brief Blur_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块寄存器数据显示
 */
DLLSHARED_EXPORT void Blur_Model_Reg_Show(void);

/**
 * @brief Blur_Model_Src_Sel
 * @param acce_index
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 模糊处理模块输入源设置
 */
DLLSHARED_EXPORT inline void Blur_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

/**
 * @brief Set_Blur_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置模糊处理模块使能状态
 */
DLLSHARED_EXPORT void Set_Blur_Enable(u32 flag);

/**
 * @brief Set_Blur_Mode_Sel
 * @param mode
 * @author Vincent
 * @date 2017/5/12
 * @note 设置模糊处理模式
 */
DLLSHARED_EXPORT void Set_Blur_Mode_Sel(u32 mode);


#ifdef __cplusplus
}
#endif

#endif // BLUR_H
