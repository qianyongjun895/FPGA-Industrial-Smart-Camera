#ifndef CAPTURE_H
#define CAPTURE_H

#include "define.h"
#include "AcceCommon.h"



/** Model(P0)图像采集 */
#define CPT_CTRL_TRIGGER_REG                    0x100           ///<  CPT触发抓图的寄存器，写入1触发一次采图
#define CPT_CTRL_REG                            0x101           ///<  CPT图像输入寄存器
#define CPT_CTRL_IN_EN_MASK                     0x1             ///<  CPT图像输入模块使能掩码
#define CPT_CTRL_IN_EN_OFFSET                   0
#define CPT_CTRL_ROI_EN_MASK                    0x4             ///<  CPT图像输入模块启用小图像模式，ROI使能掩码
#define CPT_CTRL_ROI_EN_OFFSET                  2
#define CPT_CTRL_MONO_WR_DDR_EN_MASK            0x10            ///<  CPT图像输入模块获取的黑白图像写入DDR使能掩码
#define CPT_CTRL_MONO_WR_DDR_EN_OFFSET          4
#define CPT_CTRL_COLOR_WR_DDR_EN_MASK           0x20            ///<  CPT图像输入模块获取的彩色图像写入DDR使能掩码
#define CPT_CTRL_COLOR_WR_DDR_EN_OFFSET         5
#define CPT_CTRL_MONO_EN_MASK                   0x40            ///<  CPT图像输入模块黑白图像使能掩码
#define CPT_CTRL_MONO_EN_OFFSET                 6
#define CPT_CTRL_SRC_SEL_MASK                   0x3f00          ///<  CPT图像输入模块图像源选择掩码 0:CMOS;   1:DDR_A     2:|CMOS-DDR_A| 3:|DDR_A-DDR_B|
#define CPT_CTRL_SRC_SEL_OFFSET                 8

#define CPT_CTRL_PIC_CHANNEL_REG                0x102           ///<  彩色相机的灰度通道选择寄存器
#define CPT_CTRL_PIC_CHANNEL_MASK               0x3             ///<  彩色相机的灰度通道选择信号掩码 0:亮度通道，1:R通道，2:G通道，3:B通道
#define CPT_CTRL_PIC_CHANNEL_OFFSET             0

#define SYS_MEM_DDR_SRC_A_ADDR_REG              0x104           ///<  FPGA从DDRA指定内存位置读取图像数据
#define SYS_MEM_DDR_SRC_B_ADDR_REG              0x105           ///<  FPGA从DDRB指定内存位置读取图像数据
#define SYS_MEM_PIC_IN_MONO_HP_WR_ADDR_REG      0x106           ///<  获取黑白图像存储地址
#define SYS_MRM_PIC_IN_COLOR_HP_WR_ADDR_REG     0x107           ///<  获取彩色图像存储地址

#define CPT_CTRL_SRC_A_START_REG                0x108           ///<  CPT图像DDR_A 地址寄存器
#define CPT_CTRL_SRC_A_START_X_PS_MASK          0xffff          ///<  CPT图像输入DDR_A端口，ROI起始x地址掩码
#define CPT_CTRL_SRC_A_START_X_PS_OFFSET        0
#define CPT_CTRL_SRC_A_START_Y_PS_MASK          0xffff0000      ///<  CPT图像输入DDR_A端口，ROI起始y地址掩码
#define CPT_CTRL_SRC_A_START_Y_PS_OFFSET        16

#define CPT_CTRL_SRC_A_WIDTH_REG                0x109           ///<  CPT图像DDR_A 长度寄存器
#define CPT_CTRL_SRC_A_WIDTH_PS_MASK            0xffff          ///<  CPT图像输入DDR_A端口，ROI起始x长度掩码
#define CPT_CTRL_SRC_A_WIDTH_PS_OFFSET          0
#define CPT_CTRL_SRC_A_HIGH_PS_MASK             0xffff0000      ///<  CPT图像输入DDR_A端口，ROI起始x高度掩码
#define CPT_CTRL_SRC_A_HIGH_PS_OFFSET           16

#define CPT_CTRL_SRC_B_START_REG                0x10a           ///<  CPT图像DDR_B 地址寄存器
#define CPT_CTRL_SRC_B_START_X_PS_MASK          0xffff          ///<  CPT图像输入DDR_B端口，ROI起始x地址掩码
#define CPT_CTRL_SRC_B_START_X_PS_OFFSET        0
#define CPT_CTRL_SRC_B_START_Y_PS_MASK          0xffff0000      ///<  CPT图像输入DDR_B端口，ROI起始y地址掩码
#define CPT_CTRL_SRC_B_START_Y_PS_OFFSET        16

#define CPT_CTRL_SRC_B_WIDTH_REG                0x10b           ///<  CPT图像DDR_B 长度寄存器
#define CPT_CTRL_SRC_B_WIDTH_PS_MASK            0xffff          ///<  CPT图像输入DDR_B端口，ROI起始x长度掩码
#define CPT_CTRL_SRC_B_WIDTH_PS_OFFSET          0
#define CPT_CTRL_SRC_B_HIGH_PS_MASK             0xffff0000      ///<  CPT图像输入DDR_B端口，ROI起始x高度掩码
#define CPT_CTRL_SRC_B_HIGH_PS_OFFSET           16



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CPT_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化CPT模块参数
 */
DLLSHARED_EXPORT int CPT_Model_Init(u32 acce_index);

/**
 * @brief CPT_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note CPT模块参数设置
 */
DLLSHARED_EXPORT int CPT_Model_Param_Set(unsigned int acce_index);

/**
 * @brief CPT_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return 输入源ID
 * @author Vincent
 * @date 2017/6/13
 * @note cpt模块输入源获取
 */
DLLSHARED_EXPORT inline int CPT_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief CPT_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 获取cpt模块输出数据
 */
DLLSHARED_EXPORT void CPT_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief CPT_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 图像采集模块使能关闭
 */
DLLSHARED_EXPORT inline void CPT_Model_Disable(void);

/**
 * @brief CPT_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 图像采集模块使能打开
 */
DLLSHARED_EXPORT inline void CPT_Model_Enable(void);

/**
 * @brief CPT_Model_Write_DDR_On
 * @param acce_index
 * @author Vincent
 * @date 2017/5/12
 * @note 图像采集模块写DDR使能打开
 */
DLLSHARED_EXPORT void CPT_Model_Write_DDR_On(u32 acce_index);

/**
 * @brief CPT_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 图像采集模块写DDR使能关闭
 */
DLLSHARED_EXPORT void CPT_Model_Write_DDR_Off(void);

/**
 * @brief CPT_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 图像采集模块寄存器数据显示
 */
DLLSHARED_EXPORT void CPT_Model_Reg_Show(void);

/**
 * @brief CPT_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id: 输入源ID
 * @author Vincent
 * @date 2017/7/7
 * @note CPT模块输入源设置
 */
DLLSHARED_EXPORT inline void CPT_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

/**
 * @brief InitSystemCPTModelCfg
 * @param pCpt
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化系统CPT模块的参数
 */
DLLSHARED_EXPORT void InitSystemCPTModelCfg(CPT_MODEL_CFG * pCpt);

/**
 * @brief SystemCPTModelParamSet
 * @param pCpt
 * @author Vincent
 * @date 2017/5/12
 * @note 系统CPT模块参数设置
 */
DLLSHARED_EXPORT void SystemCPTModelParamSet(CPT_MODEL_CFG * pCpt);

/**
 * @brief CPT_Model_Compass_Result_Set
 * @param ddra_roi: 计算关联定位后的ROI结构体指针
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/7/12
 * @note DDRA的ROI关联定位后的位置设置
 */
DLLSHARED_EXPORT int CPT_Model_Compass_Result_Set(CPT_ROI_PARAM * ddra_roi);

/**
 * @brief Check_Step_CPT_Model
 * @param acce_index: 步骤索引号
 * @param ddra_roi: 接收DDRA_ROI参数的结构体指针
 * @return 1: 使用了区域筛选 0: 未使用区域筛选 -1: 传入指针为NULL
 * @author Vincent
 * @date 2017/7/12
 * @note 检查指定步骤是否使用CPT的DDR模式
 */
DLLSHARED_EXPORT int Check_Step_CPT_Model(unsigned int acce_index, CPT_ROI_PARAM * ddra_roi);

/**
 * @brief Set_CPT_Color_Pic_Save_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块彩色图像保存地址
 */
DLLSHARED_EXPORT void Set_CPT_Color_Pic_Save_Addr(u32 addr);

/**
 * @brief Set_CPT_Color_Wr_Ddr
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块彩色图像写DDR使能状态
 */
DLLSHARED_EXPORT void Set_CPT_Color_Wr_Ddr(u32 flag);

/**
 * @brief Set_CPT_Color_Wr_Ddr
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块彩色图像写DDR使能状态
 */
DLLSHARED_EXPORT void Set_CPT_Mono_En(u32 flag);

/**
 * @brief Set_CPT_DDR_Src_A_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块DDRA源地址
 */
DLLSHARED_EXPORT void Set_CPT_DDR_Src_A_Addr(u32 addr);

/**
 * @brief Set_CPT_DDR_Src_B_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块DDRB源地址
 */
DLLSHARED_EXPORT void Set_CPT_DDR_Src_B_Addr(u32 addr);

/**
 * @brief Set_CPT_Mono_Pic_Save_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块黑白图像保存地址
 */
DLLSHARED_EXPORT void Set_CPT_Mono_Pic_Save_Addr(u32 addr);

/**
 * @brief Set_CPT_Mono_Wr_Ddr
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块黑白图像写DDR使能状态
 */
DLLSHARED_EXPORT void Set_CPT_Mono_Wr_Ddr(u32 flag);

/**
 * @brief Set_CPT_Pic_In_Src_A_Height
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_A端口,ROI高度
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_A_Height(u32 height);

/**
 * @brief Set_CPT_Pic_In_Src_A_Start_X
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_A端口,ROI起始x地址
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_A_Start_X(u32 addr);

/**
 * @brief Set_CPT_Pic_In_Src_A_Start_Y
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_A端口,ROI起始Y地址
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_A_Start_Y(u32 addr);

/**
 * @brief Set_CPT_Pic_In_Src_A_Width
 * @param width
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_A端口,ROI长度
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_A_Width(u32 width);

/**
 * @brief Set_CPT_Pic_In_Src_B_Height
 * @param height
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_B端口,ROI高度
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_B_Height(u32 height);

/**
 * @brief Set_CPT_Pic_In_Src_B_Start_X
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_B端口,ROI起始x地址
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_B_Start_X(u32 addr);

/**
 * @brief Set_CPT_Pic_In_Src_B_Start_Y
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_B端口,ROI起始Y地址
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_B_Start_Y(u32 addr);

/**
 * @brief Set_CPT_Pic_In_Src_B_Width
 * @param width
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像输入DDR_B端口,ROI长度
 */
DLLSHARED_EXPORT void Set_CPT_Pic_In_Src_B_Width(u32 width);

/**
 * @brief Set_CPT_Pic_Src_Sel
 * @param src
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块图像源
 */
DLLSHARED_EXPORT void Set_CPT_Pic_Src_Sel(u32 src);

/**
 * @brief Set_CPT_Pic_Channel
 * @param channel
 * @author Vincent
 * @date 2017/6/12
 * @note 设置图像采集模块灰度通道
 */
DLLSHARED_EXPORT void Set_CPT_Pic_Channel(u32 channel);

/**
 * @brief Set_CPT_Model_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块使能状态
 */
DLLSHARED_EXPORT void Set_CPT_Model_Enable(u32 flag);

/**
 * @brief Set_CPT_Roi_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块ROI使能状态
 */
DLLSHARED_EXPORT void Set_CPT_Roi_Enable(u32 flag);


DLLSHARED_EXPORT inline void SYS_CTRL_CMOS_CPT_TRIGGER(void);
DLLSHARED_EXPORT inline void CPT_CTRL_COLOR_WR_DDR_DISABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_COLOR_WR_DDR_ENABLE(void);
DLLSHARED_EXPORT void CPT_CTRL_CONTINUOUS_FRAME(void);
DLLSHARED_EXPORT inline void CPT_CTRL_DISABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_ENABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_MONO_DISABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_MONO_ENABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_MONO_WR_DDR_DISABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_MONO_WR_DDR_ENABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_ROI_DISABLE(void);
DLLSHARED_EXPORT inline void CPT_CTRL_ROI_ENABLE(void);
DLLSHARED_EXPORT void CPT_CTRL_SINGLE_FRAME_TRIGGER(void);
DLLSHARED_EXPORT inline void CPT_CTRL_SRC_SEL_CMOS(u32 num);
DLLSHARED_EXPORT inline void CPT_MEM_COLOR_HP_WR_REG_INIT(u32 num);
DLLSHARED_EXPORT inline void CPT_MEM_DDR_SRC_A_REG_INIT(u32 num);
DLLSHARED_EXPORT inline void CPT_MEM_DDR_SRC_B_REG_INIT(u32 num);
DLLSHARED_EXPORT inline void CPT_MEM_MONO_HP_WR_REG_INIT(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_A_HIGH_ADDR(u32 num);
DLLSHARED_EXPORT inline void CPT_MEM_SRC_A_START_X_ADDR(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_A_START_Y_ADDR(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_A_WIDTH_ADDR(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_B_HIGH_ADDR(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_B_START_X_ADDR(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_B_START_Y_ADDR(u32 num);
DLLSHARED_EXPORT void CPT_MEM_SRC_B_WIDTH_ADDR(u32 num);


#ifdef __cplusplus
}
#endif

#endif // CAPTURE_H
