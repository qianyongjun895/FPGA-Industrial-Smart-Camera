#ifndef SIDEEXTRACT_H
#define SIDEEXTRACT_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P37)边沿(像素)提取 */
#define SIDE_SEL_CTRL_REG                   0x2a0   	///<  区域选择寄存器
#define SIDE_SEL_CTRL_EN_MASK               0x1			///<  边沿提取模块使能掩码
#define SIDE_SEL_CTRL_EN_OFFSET             0
#define SIDE_SEL_KERNEL_TYPE_MASK           0xf0		///<  边沿提取算子掩码
#define SIDE_SEL_KERNEL_TYPE_OFFSET         4
#define SIDE_SEL_SCAN_DIR_MASK              0x300		///<  边沿提取方向选择
#define SIDE_SEL_SCAN_DIR_OFFSET            8
#define SIDE_SEL_SRC_SEL_MASK               0xff0000	///<  边沿提取源的选择mask
#define SIDE_SEL_SRC_SEL_OFFSET             16
#define SIDE_SEL_SUB_PIXEL_MASK             0x1000000	///<  边沿提取亚像素使能
#define SIDE_SEL_SUB_PIXEL_OFFSET           24
#define SIDE_SEL_MODE_SEL_MASK              0x10000000  ///<  边沿提取模式选择
#define SIDE_SEL_MODE_SEL_OFFSET            28
#define SIDE_SEL_EDGE_PIC_WR_EN_MASK        0x20000000  ///<  在输出提取的边沿图模式下的DDR写使能
#define SIDE_SEL_EDGE_PIC_WR_EN_OFFSET      29
#define SIDE_SEL_TH_REG                     0x2a1		///<  边沿阈值寄存器
#define SIDE_SEL_LOW_TH_MASK                0xffff		///<  边沿提取模块阈值下限
#define SIDE_SEL_LOW_TH_OFFSET              0
#define SIDE_SEL_HIGH_TH_MASK               0xffff0000	///<  边沿提取模块阈值上限
#define SIDE_SEL_HIGH_TH_OFFSET             16
#define SIDE_SEL_DATA_WR_ADDR_REG           0x2a2		///<  边缘点的坐标及角度信息存储在DDR的起始地址
#define SIDE_SEL_EDGE_WR_ADDR_REG           0x2a3       ///<  在输出提取的边沿图模式下的DDR写地址
#define SIDE_SEL_RESULT_NUM_REG             0x11a0		///<  边沿点数量寄存器


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Side_Select_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化边缘提取模块参数
 */
DLLSHARED_EXPORT int Side_Select_Model_Init(u32 acce_index);

/**
 * @brief Side_Select_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘提取模块参数设置函数
 */
DLLSHARED_EXPORT int Side_Select_Model_Param_Set(u32 acce_index);

/**
 * @brief Side_Select_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘提取模块输入源获取
 */
DLLSHARED_EXPORT inline int Side_Select_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Side_Select_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 输出结果指针
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘提取模块输出数据获取
 */
DLLSHARED_EXPORT void Side_Select_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Side_Select_Model_Result_Get
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取边沿提取模块边沿点数量
 */
DLLSHARED_EXPORT unsigned int Side_Select_Model_Result_Get(void);

/**
 * @brief Side_Select_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块使能关闭
 */
DLLSHARED_EXPORT inline void Side_Select_Model_Disable(void);

/**
 * @brief Side_Select_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块使能打开
 */
DLLSHARED_EXPORT inline void Side_Select_Model_Enable(void);

/**
 * @brief Side_Select_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void Side_Select_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Side_Select_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Side_Select_Model_Write_DDR_Off(void);

/**
 * @brief Side_Select_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块寄存器参数打印
 */
DLLSHARED_EXPORT void Side_Select_Model_Reg_Show(void);

/**
 * @brief Side_Select_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块输入源设置
 */
DLLSHARED_EXPORT inline void Side_Select_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief Set_Side_Sel_Amplitude_High_Th
 * @param high
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取幅度上限设置函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Amplitude_High_Th(u32 high);

/**
 * @brief Set_Side_Sel_Amplitude_Low_Th
 * @param low
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取幅度下限设置函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Amplitude_Low_Th(u32 low);

/**
 * @brief Set_Side_Sel_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取模块使能函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Enable(u32 flag);

/**
 * @brief Set_Side_Sel_Kernel_Type
 * @param type
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取算子类型选择函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Kernel_Type(u32 type);

/**
 * @brief Set_Side_Sel_Scan_Dir
 * @param scanDir
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取方向选择函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Scan_Dir(u32 scanDir);

/**
 * @brief Set_Side_Sel_Src_Sel
 * @param imgSrc
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取输入源选择函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Src_Sel(u32 imgSrc);

/**
 * @brief Set_Side_Sel_Sub_Pixel_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取亚像素使能函数
 */
DLLSHARED_EXPORT void Set_Side_Sel_Sub_Pixel_Enable(u32 flag);

/**
 * @brief Set_Side_Sel_Mode_Sel
 * @param flag 0：输出边沿点信息；1：输出提取的边沿图
 * @author Vincent
 * @date 2017/5/31
 * @note 边沿提取模式选择信号
 */
DLLSHARED_EXPORT void Set_Side_Sel_Mode_Sel(u32 flag);

/**
 * @brief Set_Side_Sel_Edge_Pic_Wr_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/31
 * @note 在输出提取的边沿图模式下的DDR写使能
 */
DLLSHARED_EXPORT void Set_Side_Sel_Edge_Pic_Wr_Enable(u32 flag);

/**
 * @brief Set_Side_Sel_Wr_Data_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿提取结果写入DDR地址
 */
DLLSHARED_EXPORT void Set_Side_Sel_Wr_Data_Addr(u32 addr);

/**
 * @brief Set_Side_Sel_Edge_Pic_Wr_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/31
 * @note 边沿图像写入DDR地址
 */
DLLSHARED_EXPORT void Set_Side_Sel_Edge_Pic_Wr_Addr(u32 addr);

/**
 * @brief GET_SIDE_SEL_POINT_NUM
 * @return 边沿点数量
 * @author Vincent
 * @date 2017/5/31
 * @note 获取边沿点数量
 */
DLLSHARED_EXPORT u32 GET_SIDE_SEL_POINT_NUM(void);

#ifdef __cplusplus
}
#endif

#endif // SIDEEXTRACT_H
