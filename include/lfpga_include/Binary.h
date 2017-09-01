#ifndef BINARY_H
#define BINARY_H

#include "define.h"
#include "AcceCommon.h"


/* Model(P33)二值化 */
#define BW_CTRL_REG                 0x180       ///< 二值化模块寄存器地址
#define BW_CTRL_EN_MASK             0x1         ///< 二值化模块使能掩码
#define BW_CTRL_EN_OFFSET           0
#define BW_CTRL_INV_EN_MASK         0x2         ///< 二值化模块结果取反使能
#define BW_CTRL_INV_EN_OFFSET       1
#define BW_CTRL_TH_HIGH_MASK        0xff000000  ///< 二值化高门限写入DDR地址
#define BW_CTRL_TH_HIGH_OFFSET      24
#define BW_CTRL_TH_LOW_MASK         0xff0000    ///< 二值化低门限写入DDR地址
#define BW_CTRL_TH_LOW_OFFSET       16
#define BW_CTRL_AUTO_REG            0x181       ///< 自动二值化触发寄存器地址
#define BW_CTRL_AUTO_TH_EN_MASK     0x1         ///< 自动二值化触发信号掩码
#define BW_CTRL_AUTO_TH_EN_OFFSET   0
#define BW_CTRL_AUTO_TH_REG         0x1086      ///< 回读的二值化阈值寄存器地址
#define BW_CTRL_AUTO_TH_LOW_MASK    0xff        ///< 二值化低门限回读地址
#define BW_CTRL_AUTO_TH_LOW_OFFSET  0
#define BW_CTRL_AUTO_TH_HIGH_MASK   0xff00      ///< 二值化高门限回读地址
#define BW_CTRL_AUTO_TH_HIGH_OFFSET 8




#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief BW_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化模块参数初始化
 */
DLLSHARED_EXPORT int BW_Model_Init(unsigned int acce_index);

/**
 * @brief BW_Model_Param_Set
 * @param acce_index：步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化模块参数设置
 */
DLLSHARED_EXPORT int BW_Model_Param_Set(unsigned int acce_index);


DLLSHARED_EXPORT int BW_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void BW_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void BW_Model_Disable(void);
DLLSHARED_EXPORT inline void BW_Model_Enable(void);
DLLSHARED_EXPORT inline void BW_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void BW_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT void BW_Model_Reg_Show(void);

/**
 * @brief BW_Model_Src_Sel
 * @param acce_index
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化模块输入源设置
 */
DLLSHARED_EXPORT inline void BW_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);
DLLSHARED_EXPORT int BW_Model_Auto_TH_Trigger(unsigned int acce_index);


DLLSHARED_EXPORT void Set_BW_Enable_Switch(u32 flag);
DLLSHARED_EXPORT void Set_BW_High_TH(u32 cpt_bw_high);
DLLSHARED_EXPORT void Set_BW_Inversion(u32 flag);
DLLSHARED_EXPORT void Set_BW_Low_TH(u32 cpt_bw_low);

DLLSHARED_EXPORT void BW_CTRL_DISABLE(void);
DLLSHARED_EXPORT void BW_CTRL_ENABLE(void);
DLLSHARED_EXPORT void BW_CTRL_INV_DISABLE(void);
DLLSHARED_EXPORT void BW_CTRL_INV_ENABLE(void);
DLLSHARED_EXPORT void BW_CTRL_TH_HIGH(u32 th_high);
DLLSHARED_EXPORT void BW_CTRL_TH_LOW(u32 th_low);

#ifdef __cplusplus
}
#endif

#endif // BINARY_H
