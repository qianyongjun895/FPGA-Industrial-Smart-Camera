#ifndef VGADISPLAY_H
#define VGADISPLAY_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P31)VGA显示 */
#define VGA_CTRL_REG                    0xb8        ///<  VGA模块寄存器地址
#define VGA_CTRL_SRC_SEL_MASK           0x3f        ///<  VGA显示图像源选择有效值为：0、15、16、17、32、37、41、42
#define VGA_CTRL_SRC_SEL_OFFSET         0
#define VGA_MEM_HP_WR_ADDR_REG          0xb9        ///<  VGA显示的DDR写地址


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Vga_Model_Init
 * @param acce_index: 步骤索引号
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块参数初始化
 */
DLLSHARED_EXPORT int Vga_Model_Init(u32 acce_index);

/**
 * @brief Vga_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note 配置VGA显示模块参数寄存器
 */
DLLSHARED_EXPORT int Vga_Model_Param_Set(u32 acce_index);

/**
 * @brief Vga_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块输入源获取
 */
DLLSHARED_EXPORT inline int Vga_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Vga_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块输出数据获取
 */
DLLSHARED_EXPORT void Vga_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Vga_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块使能关闭
 */
DLLSHARED_EXPORT inline void Vga_Model_Disable(void);

/**
 * @brief Vga_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块使能开启
 */
DLLSHARED_EXPORT inline void Vga_Model_Enable(void);

/**
 * @brief Vga_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块写DDR使能开启
 */
DLLSHARED_EXPORT inline void Vga_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Vga_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Vga_Model_Write_DDR_Off(void);

/**
 * @brief Vga_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块寄存器数据打印
 */
DLLSHARED_EXPORT inline void Vga_Model_Reg_Show(void);

/**
 * @brief Vga_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id: 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note VGA显示模块输入源设置
 */
DLLSHARED_EXPORT inline void Vga_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief VGA_CTRL_SRC_SEL
 * @param src
 * @author Vincent
 * @date 2017/6/1
 * @note 设置VGA模块显示图像源
 */
DLLSHARED_EXPORT void VGA_CTRL_SRC_SEL(u32 src);

/**
 * @brief VGA_CTRL_WR_ADDR
 * @param addr
 * @author Vincent
 * @date 2017/6/1
 * @note 设置VGA模块显示地址
 */
DLLSHARED_EXPORT void VGA_CTRL_WR_ADDR(u32 addr);


#ifdef __cplusplus
}
#endif

#endif // VGADISPLAY_H
