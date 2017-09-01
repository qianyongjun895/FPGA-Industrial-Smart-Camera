#ifndef BWPROCESS_H
#define BWPROCESS_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P32)二值化处理模块 */
#define BW_PROCESS_CTRL_REG                 0x182       ///<  二值化处理模块寄存器地址
#define BW_PROCESS_CTRL_EN_MASK             0x1         ///<  二值化处理模块使能
#define BW_PROCESS_CTRL_EN_OFFSET           0
#define BW_PROCESS_CTRL_SRC_SEL_MASK        0x3f00      ///<  二值化处理模块结果输出选择信号
#define BW_PROCESS_CTRL_SRC_SEL_OFFSET      8
#define BW_PROCESS_CTRL_WR_DDR_EN_MASK      0x10000     ///<  二值化处理模块结果DDR写使能信号
#define BW_PROCESS_CTRL_WR_DDR_EN_OFFSET    16
#define BW_PROCESS_CTRL_SRC_IN_MASK         0x3f000000  ///<  二值化处理模块输入源选择信号
#define BW_PROCESS_CTRL_SRC_IN_OFFSET       24
#define BW_PROCESS_MEM_HP_WR_ADDR_REG       0x183       ///<  二值化处理模块结果DDR写地址


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BW_Process_Model_Init
 * @param bw_process_model
 * @author Vincent
 * @date 2017/5/18
 * @note 二值化处理模块参数初始化函数
 */
DLLSHARED_EXPORT int BW_Process_Model_Init(u32 acce_index);

/**
 * @brief BWProcessModelParamSet
 * @param pAcce
 * @author Vincent
 * @date 2017/5/18
 * @note 二值化处理模块参数配置函数
 */
DLLSHARED_EXPORT int BW_Process_Model_Param_Set(u32 acce_index);

/**
 * @brief BW_Process_Model_Input_Model_Get
 * @param acce_index
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块输入源获取
 */
DLLSHARED_EXPORT int BW_Process_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief BW_Process_Model_Output_Get
 * @param acce_index
 * @param output_type
 * @param pContainer
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块结果数据获取
 */
DLLSHARED_EXPORT void BW_Process_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief BW_Process_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块使能关闭
 */
DLLSHARED_EXPORT inline void BW_Process_Model_Disable(void);

/**
 * @brief BW_Process_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块使能打开
 */
DLLSHARED_EXPORT inline void BW_Process_Model_Enable(void);

/**
 * @brief BW_Process_Model_Write_DDR_On
 * @param acce_index
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void BW_Process_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief BW_Process_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void BW_Process_Model_Write_DDR_Off(void);

/**
 * @brief BW_Process_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块寄存器数据显示
 */
DLLSHARED_EXPORT void BW_Process_Model_Reg_Show(void);

/**
 * @brief BW_Process_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id: 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note 二值化处理模块输入源设置
 */
DLLSHARED_EXPORT inline void BW_Process_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

/**
 * @brief BW_Process_Model_Out_Src_Auto_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 自动设置二值化处理模块输出源
 */
DLLSHARED_EXPORT void BW_Process_Model_Out_Src_Auto_Set(u32 acce_index);

DLLSHARED_EXPORT void Set_BW_Process_Src_Sel(u8 imgSrc);
DLLSHARED_EXPORT void Set_BW_Process_Src_In(u8 inSrc);
DLLSHARED_EXPORT void Set_BW_Process_Wr_Ddr_Addr(u32 addr);
DLLSHARED_EXPORT void Set_BW_Process_Wr_Ddr_Enable(u32 flag);

#ifdef __cplusplus
}
#endif

#endif // BWPROCESS_H
