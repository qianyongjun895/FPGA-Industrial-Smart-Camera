#ifndef PEAKA_H
#define PEAKA_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P6)原图腐蚀膨胀A模块寄存器 */
#define PEAK_A_CTRL_REG                 0x129       ///< 原图腐蚀膨胀A控制寄存器
#define PEAK_A_CTRL_EN_MASK             0x1         ///< 模块使能掩码
#define PEAK_A_CTRL_EN_OFFSET           0
#define PEAK_A_CTRL_MODE_SEL_MASK       0x10        ///< 原图腐蚀膨胀A模式选择，0：腐蚀 1：膨胀
#define PEAK_A_CTRL_MODE_SEL_OFFSET     4
#define PEAK_A_CTRL_LOOP_NUM_MASK       0xf00       ///< 原图腐蚀膨胀A循环次数，有效值为1~5
#define PEAK_A_CTRL_LOOP_NUM_OFFSET     8



#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Peak_A_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化原图腐蚀膨胀A模块参数
 */
DLLSHARED_EXPORT int Peak_A_Model_Init(u32 acce_index);

/**
 * @brief Peak_A_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块参数设置函数
 */
DLLSHARED_EXPORT int Peak_A_Model_Param_Set(u32 acce_index);

/**
 * @brief Peak_A_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块输入源获取
 */
DLLSHARED_EXPORT inline int Peak_A_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Peak_A_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块输出数据获取
 */
DLLSHARED_EXPORT void Peak_A_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Peak_A_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块使能关闭
 */
DLLSHARED_EXPORT inline void Peak_A_Model_Disable(void);

/**
 * @brief Peak_A_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块使能开启
 */
DLLSHARED_EXPORT inline void Peak_A_Model_Enable(void);

/**
 * @brief Peak_A_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块写DDR使能开启
 */
DLLSHARED_EXPORT inline void Peak_A_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Peak_A_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Peak_A_Model_Write_DDR_Off(void);

/**
 * @brief Peak_A_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块寄存器数据打印
 */
DLLSHARED_EXPORT void Peak_A_Model_Reg_Show(void);

/**
 * @brief Peak_A_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 原图腐蚀膨胀A模块输入源设置
 */
DLLSHARED_EXPORT inline void Peak_A_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

/**
 * @brief Set_Peak_A_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/31
 * @note 设置原图腐蚀膨胀A模块使能状态
 */
DLLSHARED_EXPORT void Set_Peak_A_Enable(u32 flag);

/**
 * @brief Set_Peak_A_Mode_Sel
 * @param flag
 * @author Vincent
 * @date 2017/5/31
 * @note 设置原图腐蚀膨胀A模式选择
 */
DLLSHARED_EXPORT void Set_Peak_A_Mode_Sel(u32 flag);

/**
 * @brief Set_Peak_A_Level
 * @param level
 * @author Vincent
 * @date 2017/5/31
 * @note 设置原图腐蚀膨胀A循环次数
 */
DLLSHARED_EXPORT void Set_Peak_A_Loop_Num(u32 loop_num);


#ifdef __cplusplus
}
#endif


#endif // PEAKA_H
