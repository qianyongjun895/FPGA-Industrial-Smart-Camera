#ifndef COLOREXTRACT_H
#define COLOREXTRACT_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P41)色彩抽取 */
#define COLOR_DRAW_CTRL_REG                 0x1c0       ///<  色彩抽取寄存器
#define COLOR_DRAW_CTRL_EN_MASK             0x1         ///<  色彩抽取使能掩码
#define COLOR_DRAW_CTRL_EN_OFFSET           0
#define COLOR_DRAW_CTRL_WR_DDR_EN_MASK      0x10        ///<  色彩抽取结果写入DDR使能掩码
#define COLOR_DRAW_CTRL_WR_DDR_EN_OFFSET    4
#define COLOR_DRAW_CTRL_ALL_REV_EN_MASK     0x8000      ///<  全部颜色指定反转掩码
#define COLOR_DRAW_CTRL_ALL_REV_EN_OFFSET   12
#define COLOR_DRAW_CTRL_ZONE_REV_MASK       0xff0000	///<  8个色彩抽取，分别取反掩码
#define COLOR_DRAW_CTRL_ZONE_REV_OFFSET     16
#define COLOR_DRAW_CTRL_ZONE_SEL_MASK       0xff000000	///<  8个色彩抽取，分别使能掩码
#define COLOR_DRAW_CTRL_ZONE_SEL_OFFSET     24
#define COLOR_DRAW_CTRL_RGB_BCK_REG         0x1c1       ///<  没有抽取到的部分，背景颜色设置寄存器
#define COLOR_DRAW_CTRL_RGB_BCK_MASK        0xffffff	///<  没有抽取到的部分，背景颜色设置掩码
#define COLOR_DRAW_CTRL_RGB_BCK_OFFSET      0
#define COLOR_DRAW_CTRL_WR_DDR_REG          0x1c2       ///<  色彩抽取结果，写入DDR地址

#define COLOR_DRAW_CTRL_R_TH01_REG          0x1c3       ///<  区域0 1 红色抽取门限寄存器
#define COLOR_DRAW_CTRL_R_TH0_MASK          0xffff      ///<  区域0红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH0_OFFSET        0
#define COLOR_DRAW_CTRL_R_TH1_MASK          0xffff0000	///<  区域1红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH1_OFFSET        16
#define COLOR_DRAW_CTRL_R_TH23_REG          0x1c4       ///<  区域2 3 红色抽取门限寄存器
#define COLOR_DRAW_CTRL_R_TH2_MASK          0xffff      ///<  区域2红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH2_OFFSET        0
#define COLOR_DRAW_CTRL_R_TH3_MASK          0xffff0000	///<  区域3红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH3_OFFSET        16
#define COLOR_DRAW_CTRL_R_TH45_REG          0x1c5       ///<  区域4 5 红色抽取门限寄存器
#define COLOR_DRAW_CTRL_R_TH4_MASK          0xffff      ///<  区域4红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH4_OFFSET        0
#define COLOR_DRAW_CTRL_R_TH5_MASK          0xffff0000	///<  区域5红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH5_OFFSET        16
#define COLOR_DRAW_CTRL_R_TH67_REG          0x1c6       ///<  区域6 7 红色抽取门限寄存器
#define COLOR_DRAW_CTRL_R_TH6_MASK          0xffff      ///<  区域6红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH6_OFFSET        0
#define COLOR_DRAW_CTRL_R_TH7_MASK          0xffff0000	///<  区域7红色抽取门限掩码
#define COLOR_DRAW_CTRL_R_TH7_OFFSET        16

#define COLOR_DRAW_CTRL_G_TH01_REG          0x1c7       ///<  区域01 绿色抽取门限寄存器
#define COLOR_DRAW_CTRL_G_TH0_MASK          0xffff      ///<  区域0绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH0_OFFSET        0
#define COLOR_DRAW_CTRL_G_TH1_MASK          0xffff0000	///<  区域1绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH1_OFFSET        16
#define COLOR_DRAW_CTRL_G_TH23_REG          0x1c8       ///<  区域23 绿色抽取门限寄存器
#define COLOR_DRAW_CTRL_G_TH2_MASK          0xffff      ///<  区域2绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH2_OFFSET        0
#define COLOR_DRAW_CTRL_G_TH3_MASK          0xffff0000	///<  区域3绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH3_OFFSET        16
#define COLOR_DRAW_CTRL_G_TH45_REG          0x1c9       ///<  区域45 绿色抽取门限寄存器
#define COLOR_DRAW_CTRL_G_TH4_MASK          0xffff      ///<  区域4绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH4_OFFSET        0
#define COLOR_DRAW_CTRL_G_TH5_MASK          0xffff0000	///<  区域5绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH5_OFFSET        16
#define COLOR_DRAW_CTRL_G_TH67_REG          0x1ca       ///<  区域67 绿色抽取门限寄存器
#define COLOR_DRAW_CTRL_G_TH6_MASK          0xffff      ///<  区域6绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH6_OFFSET        0
#define COLOR_DRAW_CTRL_G_TH7_MASK          0xffff0000	///<  区域7绿色抽取门限掩码
#define COLOR_DRAW_CTRL_G_TH7_OFFSET        16

#define COLOR_DRAW_CTRL_B_TH01_REG          0x1cb       ///<  区域0 1 蓝色抽取门限寄存器
#define COLOR_DRAW_CTRL_B_TH0_MASK          0xffff      ///<  区域0蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH0_OFFSET        0
#define COLOR_DRAW_CTRL_B_TH1_MASK          0xffff0000	///<  区域1蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH1_OFFSET        16
#define COLOR_DRAW_CTRL_B_TH23_REG          0x1cc       ///<  区域2 3 蓝色抽取门限寄存器
#define COLOR_DRAW_CTRL_B_TH2_MASK          0xffff      ///<  区域2蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH2_OFFSET        0
#define COLOR_DRAW_CTRL_B_TH3_MASK          0xffff0000	///<  区域3蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH3_OFFSET        16
#define COLOR_DRAW_CTRL_B_TH45_REG          0x1cd       ///<  区域4 5 蓝色抽取门限寄存器
#define COLOR_DRAW_CTRL_B_TH4_MASK          0xffff      ///<  区域4蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH4_OFFSET        0
#define COLOR_DRAW_CTRL_B_TH5_MASK          0xffff0000	///<  区域5蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH5_OFFSET        16
#define COLOR_DRAW_CTRL_B_TH67_REG          0x1ce       ///<  区域6 7 蓝色抽取门限寄存器
#define COLOR_DRAW_CTRL_B_TH6_MASK          0xffff      ///<  区域6蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH6_OFFSET        0
#define COLOR_DRAW_CTRL_B_TH7_MASK          0xffff0000	///<  区域7蓝色抽取门限掩码
#define COLOR_DRAW_CTRL_B_TH7_OFFSET        16



#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Color_Draw_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块参数初始化
 */
DLLSHARED_EXPORT int Color_Draw_Model_Init(u32 acce_index);

/**
 * @brief Color_Draw_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块参数的设置
 */
DLLSHARED_EXPORT int Color_Draw_Model_Param_Set(u32 acce_index);

/**
 * @brief Color_Draw_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块输入源获取
 */
DLLSHARED_EXPORT inline int Color_Draw_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Color_Draw_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出标志
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块输出结果获取
 */
DLLSHARED_EXPORT void Color_Draw_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Color_Draw_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块使能关闭
 */
DLLSHARED_EXPORT inline void Color_Draw_Model_Disable(void);

/**
 * @brief Color_Draw_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块使能打开
 */
DLLSHARED_EXPORT inline void Color_Draw_Model_Enable(void);

/**
 * @brief Color_Draw_Model_Write_DDR_On
 * @param acce_index
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void Color_Draw_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Color_Draw_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Color_Draw_Model_Write_DDR_Off(void);

/**
 * @brief Color_Draw_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块寄存器参数显示
 */
DLLSHARED_EXPORT void Color_Draw_Model_Reg_Show(void);

/**
 * @brief Color_Draw_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 颜色抽取模块寄存器参数显示
 */
DLLSHARED_EXPORT inline void Color_Draw_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_Color_Draw_All_Rev_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Color_Draw_Blue_Th(u16 * blue_th);
DLLSHARED_EXPORT void Set_Color_Draw_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Color_Draw_Green_Th(u16 * green_th);
DLLSHARED_EXPORT void Set_Color_Draw_Red_Th(u16 * red_th);
DLLSHARED_EXPORT void Set_Color_Draw_Rgb_Bck(u32 num);
DLLSHARED_EXPORT void Set_Color_Draw_Wr_Ddr_Addr(u32 addr);
DLLSHARED_EXPORT void Set_Color_Draw_Wr_Ddr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Color_Draw_Zone_Rev(u32 num);
DLLSHARED_EXPORT void Set_Color_Draw_Zone_Sel(u32 num);

DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_ALL_REV_DISABLE(void);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_ALL_REV_ENABLE(void);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH0(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH1(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH2(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH3(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH4(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH5(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH6(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_B_TH7(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_DISABLE(void);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_ENABLE(void);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH0(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH1(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH2(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH3(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH4(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH5(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH6(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_G_TH7(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_RGB_BCK(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH0(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH1(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH2(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH3(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH4(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH5(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH6(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_R_TH7(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_WR_DDR(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_WR_DDR_DISABLE(void);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_WR_DDR_ENABLE(void);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_ZONE_REV(u32 num);
DLLSHARED_EXPORT inline void COLOR_DRAW_CTRL_ZONE_SEL(u32 num);

#ifdef __cplusplus
}
#endif

#endif // COLOREXTRACT_H
