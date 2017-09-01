#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P17)预处理模块 */
#define PRE_CTRL_REG                        0x114       ///<  图像预处理模块控制寄存器
#define PRE_CTRL_WR_DDR_EN_MASK             0x1         ///<  图像预处理模块的DDR写使能信号
#define PRE_CTRL_WR_DDR_EN_OFFSET           0
#define PRE_CTRL_EN_MASK                    0x10        ///<  图像预处理模块使能信号
#define PRE_CTRL_EN_OFFSET                  4
#define PRE_CTRL_SRC_SEL_MASK               0x3f00      ///<  图像预处理模块的输出信号源选择,有效值为：0、1、2、3、4
#define PRE_CTRL_SRC_SEL_OFFSET             8
#define PRE_CTRL_PIPELINE_MODE_SEL_MASK     0xf0000     ///<  预处理流水线模式选择有效值为：0、1、2
#define PRE_CTRL_PIPELINE_MODE_SEL_OFFSET   16
#define PRE_CTRL_SRC_IN_SEL_MASK            0x3f000000  ///<  图像预处理模块的输入信号源选择有效值为：0、42
#define PRE_CTRL_SRC_IN_SEL_OFFSET          24
#define PRE_MEM_WR_DDR_ADDR_REG             0x115       ///<  图像预处理模块的写DDR地址


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Pre_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/18
 * @note 初始化预处理模块参数
 */
DLLSHARED_EXPORT int Pre_Model_Init(u32 acce_index);

/**
 * @brief Pre_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/18
 * @note fpga预处理模块参数配置
 */
DLLSHARED_EXPORT int Pre_Model_Param_Set(u32 acce_index);

/**
 * @brief Pre_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块输入源获取
 */
DLLSHARED_EXPORT int Pre_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Pre_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 预处理模块输出数据获取
 */
DLLSHARED_EXPORT void Pre_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Pre_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块使能关闭
 */
DLLSHARED_EXPORT inline void Pre_Model_Disable(void);

/**
 * @brief Pre_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块使能开启
 */
DLLSHARED_EXPORT inline void Pre_Model_Enable(void);

/**
 * @brief Pre_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块写DDR使能开启
 */
DLLSHARED_EXPORT inline void Pre_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Pre_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Pre_Model_Write_DDR_Off(void);

/**
 * @brief Pre_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块寄存器数据打印
 */
DLLSHARED_EXPORT void Pre_Model_Reg_Show(void);

/**
 * @brief Pre_Model_Out_Auto_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 自动设置图像预处理输出源
 */
DLLSHARED_EXPORT void Pre_Model_Out_Src_Auto_Set(u32 acce_index);

/**
 * @brief Pre_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 图像预处理模块输入源设置
 */
DLLSHARED_EXPORT inline void Pre_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief Set_Preprocess_Wr_Ddr_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/18
 * @note 设置预处理模块写DDR使能
 */
DLLSHARED_EXPORT void Set_Preprocess_Wr_Ddr_Enable(u32 flag);

/**
 * @brief Set_Preprocess_Src_Sel
 * @param imgSrc
 * @author Vincent
 * @date 2017/5/18
 * @note 设置图像预处理模块的输出信号源选择
 */
DLLSHARED_EXPORT void Set_Preprocess_Src_Sel(u8 imgSrc);

/**
 * @brief Set_Preprocess_Src_In_Sel
 * @param src
 * @author Vincent
 * @date 2017/5/18
 * @note 设置图像预处理模块的输入信号源选择
 */
DLLSHARED_EXPORT void Set_Preprocess_Src_In_Sel(u8 src);

/**
 * @brief Set_Preprocess_Pipeline_Mode_Sel
 * @param mode
 * @author Vincent
 * @date 2017/5/18
 * @note 设置预处理流水线模式选择
 */
DLLSHARED_EXPORT void Set_Preprocess_Pipeline_Mode_Sel(u8 mode);

/**
 * @brief Set_Preprocess_Wr_Ddr_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/18
 * @note 设置图像预处理模块的写DDR地址
 */
DLLSHARED_EXPORT void Set_Preprocess_Wr_Ddr_Addr(u32 addr);

#ifdef __cplusplus
}
#endif



#endif // PREPROCESS_H
