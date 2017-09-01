#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P43)直方图统计 */
#define HIST_CTRL_REG               0x187		///<  直方图寄存器
#define HIST_RD_ADDR_MASK           0xfff       ///<  直方图结果回读地址，0~255，对应灰度0~255
#define HIST_RD_ADDR_OFFSET         0
#define HIST_STAT_SRC_SEL_MASK      0x3f0000    ///<  直方图统计源选择信号,有效值为：0、17、32、42
#define HIST_STAT_SRC_SEL_OFFSET    16
#define HIST_MODE_SEL_MASK          0x1000000   ///< 0表示全图统计，1表示只统计二值化数据；
#define HIST_MODE_SEL_OFFSET        24
#define HIST_BW_DIR_SEL_MASK        0x2000000   ///< 统计方向（二值化统计模式下生效） 0表示按列统计二值化数据，1表示按行
#define HIST_BW_DIR_SEL_OFFSET      25
#define HIST_BW_COLOR_SEL_MASK      0x4000000   ///< 统计颜色（二值化统计模式下生效） 0表示统计白像素，1表示统计黑像素
#define HIST_BW_COLOR_SEL_OFFSET    26
#define HIST_RD_STATUS_REG          0x188		///<  读直方图均衡的状态标记位的寄存器
#define HIST_RD_STATUS_MASK         0x1		    ///<  读直方图均衡的状态标记位掩码,1表示正在读取,不读直方图数据时需置为0
#define HIST_RD_STATUS_OFFSET       0
#define HIST_RD_DATA_REG            0x1188		///<  对应灰度的直方图统计结果


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Hist_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化直方图统计模块参数
 */
DLLSHARED_EXPORT int Hist_Model_Init(u32 acce_index);

/**
 * @brief HistModelParamSet
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块参数设置函数
 */
DLLSHARED_EXPORT int Hist_Model_Param_Set(u32 acce_index);

/**
 * @brief Hist_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块输入源获取
 */
DLLSHARED_EXPORT inline int Hist_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Hist_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块输出结果获取
 */
DLLSHARED_EXPORT void Hist_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Hist_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块使能关闭
 */
DLLSHARED_EXPORT inline void Hist_Model_Disable(void);

/**
 * @brief Hist_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块使能开启
 */
DLLSHARED_EXPORT inline void Hist_Model_Enable(void);

/**
 * @brief Hist_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计写DDR使能开启
 */
DLLSHARED_EXPORT inline void Hist_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Hist_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块写DDE使能关闭
 */
DLLSHARED_EXPORT inline void Hist_Model_Write_DDR_Off(void);

/**
 * @brief Hist_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块寄存器数据打印
 */
DLLSHARED_EXPORT void Hist_Model_Reg_Show(void);

/**
 * @brief Hist_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 直方图统计模块输入源设置
 */
DLLSHARED_EXPORT inline void Hist_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief Set_Hist_Stat_Src_Sel
 * @param src
 * @author Vincent
 * @date 2017/5/12
 * @note 设置直方图统计源选择信号
 */
DLLSHARED_EXPORT void Set_Hist_Stat_Src_Sel(u32 src);

/**
 * @brief Set_Hist_Mode_Sel
 * @param mode
 * @author Vincent
 * @date 2017/5/12
 * @note 设置直方图统计模式选择信号
 */
DLLSHARED_EXPORT void Set_Hist_Mode_Sel(u32 flag);

/**
 * @brief Set_Hist_BW_DIR_Sel
 * @param flag
 * @author Vincent
 * @date 2017/6/28
 * @note 设置直方图统计二值化方向选择信号
 */
DLLSHARED_EXPORT void Set_Hist_BW_DIR_Sel(u32 flag);

/**
 * @brief Set_Hist_BW_Color_Sel
 * @param flag
 * @author Vincent
 * @date 2017/6/28
 * @note 设置直方图统计二值化黑白颜色选择信号
 */
DLLSHARED_EXPORT void Set_Hist_BW_Color_Sel(u32 flag);

/**
 * @brief Set_Hist_Read_Status
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置直方图统计状态寄存器
 */
DLLSHARED_EXPORT void Set_Hist_Read_Status(u32 flag);

/**
 * @brief Get_Hist_Rd_Data
 * @param hist  接受统计数据数组
 * @param size  hist数组长度
 * @param mode_sel  统计模式
 * @param bw_dir_sel  二值化统计
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取直方图统计结果
 */
DLLSHARED_EXPORT s32 Get_Hist_Rd_Data(u32 *hist, u32 size, u32 mode_sel, u32 bw_dir_sel);



#ifdef __cplusplus
}
#endif

#endif // HISTOGRAM_H
