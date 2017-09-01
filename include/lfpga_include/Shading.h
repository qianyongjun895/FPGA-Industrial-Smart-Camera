#ifndef ZOOMFILTER_H
#define ZOOMFILTER_H

#include "define.h"
#include "AcceCommon.h"


/** Model(16)实时浓淡补正 */
#define SHADING_CTRL_REG                0x120       ///< 实时浓淡补正控制寄存器
#define SHADING_CTRL_EN_MASK            0x1         ///< 实时浓淡补正使能
#define SHADING_CTRL_EN_OFFSET          0
#define SHADING_CTRL_KERNEL_MASK        0xf0000     ///< 阴影补正模式时的窗口大小选择 1:3x3,2:5x5,3:7x7,4:9x9,5:11x11,6:13x13
#define SHADING_CTRL_KERNEL_OFFSET      16
#define SHADING_CTRL_VH_SEL_MASK        0x300000    ///< 阴影补正时的方向选择 0:XY,1:X,2:Y
#define SHADING_CTRL_VH_SEL_OFFSET      20
#define SHADING_CTRL_MODE_MASK          0x3000000   ///< 实时浓淡补正模式选择 0:平均值补正，1:中间值补正，2：阴影补正
#define SHADING_CTRL_MODE_OFFSET        24
#define SHADING_CTRL_DIR_MASK           0x30000000  ///< 缺陷提取选择 0:明，1:暗，2:明暗，3:明暗个别
#define SHADING_CTRL_DIR_OFFSET         28
#define SHADING_CTRL_PARAM_REG          0x121
#define SHADING_CTRL_BRIGHT_GAIN_MASK   0xff        ///< 缺陷增益设置,有效值为0-255 在缺陷提取选择为“明暗个别”时为明增益，其他设置下为缺陷增益
#define SHADING_CTRL_BRIGHT_GAIN_OFFSET 0
#define SHADING_CTRL_DARK_GAIN_MASK     0xff00      ///< 暗缺陷增益设置,有效值为0-255 只在缺陷提取选择为“明暗个别”时有效
#define SHADING_CTRL_DARK_GAIN_OFFSET   8
#define SHADING_CTRL_TH_MASK            0xff0000    ///< 排除干扰，排除阶调值以下的数据点，有效值为0-255
#define SHADING_CTRL_TH_OFFSET          16
#define SHADING_CTRL_VALUE_REG          0x122
#define SHADING_CTRL_BASE_VALUE_MASK    0xff        ///< 在实时浓淡补正模式选择为“平均值补正”及“中间值补正”时使用，请设置选择区域内的灰度平均值或者中间值
#define SHADING_CTRL_BASE_VALUE_OFFSET  0
#define SHADING_MEM_DATA_AVG_REG        0x1084      ///< 实时浓淡补正的图像平均值


#define SHADING_KERNEL_3x3      1
#define SHADING_KERNEL_5x5      2
#define SHADING_KERNEL_7x7      3
#define SHADING_KERNEL_9x9      4
#define SHADING_KERNEL_11x11    5
#define SHADING_KERNEL_13x13    6


#define SHADING_VH_SEL_XY   0
#define SHADING_VH_SEL_X    1
#define SHADING_VH_SEL_Y    2


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Shading_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化实时浓淡补正模块参数
 */
DLLSHARED_EXPORT int Shading_Model_Init(u32 acce_index);

/**
 * @brief Shading_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块参数设置函数
 */
DLLSHARED_EXPORT int Shading_Model_Param_Set(u32 acce_index);

/**
 * @brief Rt_Shade_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块输入源获取
 */
DLLSHARED_EXPORT inline int Rt_Shade_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Rt_Shade_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块输出数据获取
 */
DLLSHARED_EXPORT void Rt_Shade_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Rt_Shade_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块使能关闭
 */
DLLSHARED_EXPORT inline void Rt_Shade_Model_Disable(void);

/**
 * @brief Rt_Shade_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块使能开启
 */
DLLSHARED_EXPORT inline void Rt_Shade_Model_Enable(void);

/**
 * @brief Rt_Shade_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块写DDR使能开启
 */
DLLSHARED_EXPORT inline void Rt_Shade_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Rt_Shade_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Rt_Shade_Model_Write_DDR_Off(void);

/**
 * @brief Rt_Shade_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块寄存器数据打印
 */
DLLSHARED_EXPORT void Rt_Shade_Model_Reg_Show(void);

/**
 * @brief Rt_Shade_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 实时浓淡补正模块输入源设置
 */
DLLSHARED_EXPORT inline void Rt_Shade_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief Set_Shading_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置实时浓淡补正模块使能状态
 */
DLLSHARED_EXPORT void Set_Shading_Enable(u32 flag);

/**
 * @brief Set_Shading_Kernel_Mode
 * @param kernel
 * @author Vincent
 * @date 2017/5/12
 * @note 设置阴影补正时的窗口大小
 */
DLLSHARED_EXPORT void Set_Shading_Kernel_Mode(u32 kernel);

/**
 * @brief Set_Shading_Vh_Sel
 * @param sel
 * @author Vincent
 * @date 2017/5/12
 * @note 设置阴影补正时的方向选择
 */
DLLSHARED_EXPORT void Set_Shading_Vh_Sel(u32 sel);

/**
 * @brief Set_Shading_Mode_Sel
 * @param mode
 * @author Vincent
 * @date 2017/5/12
 * @note 设置实时浓淡补正模式选择
 */
DLLSHARED_EXPORT void Set_Shading_Mode_Sel(u32 mode);
DLLSHARED_EXPORT void Set_Shading_Dir_Sel(u32 dir);
DLLSHARED_EXPORT void Set_Shading_Bright_Sel(u32 sel);
DLLSHARED_EXPORT void Set_Shading_Dark_Gain_Sel(u32 gain);
DLLSHARED_EXPORT void Set_Shading_Th_Sel(u32 th);
DLLSHARED_EXPORT void Set_Shading_Base_Value_Sel(u32 value);
DLLSHARED_EXPORT u32 Get_Shading_Data_Avg(void);




#ifdef __cplusplus
}
#endif

#endif // ZOOMFILTER_H
