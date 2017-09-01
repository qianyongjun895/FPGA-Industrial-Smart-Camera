#ifndef EROSIONDILATIONA_H
#define EROSIONDILATIONA_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P34)腐蚀膨胀A */
#define ED_A_LOOP_NUM_REG               0x166       ///<  腐蚀膨胀A循环次数寄存器
#define ED_A_LOOP_NUM_MASK              0xf         ///<  腐蚀膨胀A循环次数掩码
#define ED_A_LOOP_NUM_OFFSET            0
#define ED_A_BOUNDARY_EXTR_EN_MASK      0x100		///<  腐蚀膨胀A提取边沿功能使能掩码
#define ED_A_BOUNDARY_EXTR_EN_OFFSET    8
#define ED_A_CTRL_REG                   0x167       ///<  腐蚀膨胀A控制寄存器
#define ED_A_CTRL_EN_MASK               0x1         ///<  腐蚀膨胀A使能掩码
#define ED_A_CTRL_EN_OFFSET             0
#define ED_A_CTRL_SIDE_DEL_EN_MASK      0x2         ///<  腐蚀膨胀A边界删除使能掩码
#define ED_A_CTRL_SIDE_DEL_EN_OFFSET    1
#define ED_A_CTRL_MODE_MASK             0x8         ///<  腐蚀/膨胀 模式切换掩码 1=腐蚀 0=膨胀
#define ED_A_CTRL_MODE_OFFSET           3
#define ED_A_CTRL_TH_MASK               0xff0000    ///<  腐蚀膨胀A门限掩码
#define ED_A_CTRL_TH_OFFSET             16
#define ED_A_CTRL_MDOE_MASK             0xff000000  ///<  腐蚀膨胀A模板大小 1表示3x3，2表示5x5,即模板的大小为2xN+1
#define ED_A_CTRL_MDOE_OFFSET           24
#define ED_A_MEM_MODEL_N1_REG           0x169       ///<  腐蚀膨胀A模板1寄存器
#define ED_A_MEM_MODEL_0_MASK           0x1fff      ///<  腐蚀膨胀A模板第1行
#define ED_A_MEM_MODEL_0_OFFSET         0
#define ED_A_MEM_MODEL_1_MASK           0x1fff0000  ///<  腐蚀膨胀A模板第2行
#define ED_A_MEM_MODEL_1_OFFSET         16
#define ED_A_MEM_MODEL_N2_REG           0x16a       ///<  腐蚀膨胀A模板2寄存器
#define ED_A_MEM_MODEL_2_MASK           0x1fff      ///<  腐蚀膨胀A模板第3行
#define ED_A_MEM_MODEL_2_OFFSET         0
#define ED_A_MEM_MODEL_3_MASK           0x1fff0000  ///<  腐蚀膨胀A模板第4行
#define ED_A_MEM_MODEL_3_OFFSET         16
#define ED_A_MEM_MODEL_N3_REG           0x16b       ///<  腐蚀膨胀A模板3寄存器
#define ED_A_MEM_MODEL_4_MASK           0x1fff      ///<  腐蚀膨胀A模板第5行
#define ED_A_MEM_MODEL_4_OFFSET         0
#define ED_A_MEM_MODEL_5_MASK           0x1fff0000  ///<  腐蚀膨胀A模板第6行
#define ED_A_MEM_MODEL_5_OFFSET         16
#define ED_A_MEM_MODEL_N4_REG           0x16c       ///<  腐蚀膨胀A模板4寄存器
#define ED_A_MEM_MODEL_6_MASK           0x1fff      ///<  腐蚀膨胀A模板第7行
#define ED_A_MEM_MODEL_6_OFFSET         0
#define ED_A_MEM_MODEL_7_MASK           0x1fff0000  ///<  腐蚀膨胀A模板第8行
#define ED_A_MEM_MODEL_7_OFFSET         16
#define ED_A_MEM_MODEL_N5_REG           0x16d       ///<  腐蚀膨胀A模板5寄存器
#define ED_A_MEM_MODEL_8_MASK           0x1fff      ///<  腐蚀膨胀A模板第8行
#define ED_A_MEM_MODEL_8_OFFSET         0
#define ED_A_MEM_MODEL_9_MASK           0x1fff0000  ///<  腐蚀膨胀A模板第9行
#define ED_A_MEM_MODEL_9_OFFSET         16
#define ED_A_MEM_MODEL_N6_REG           0x16e       ///<  腐蚀膨胀A模板6寄存器
#define ED_A_MEM_MODEL_10_MASK          0x1fff      ///<  腐蚀膨胀A模板第10行
#define ED_A_MEM_MODEL_10_OFFSET        0
#define ED_A_MEM_MODEL_11_MASK          0x1fff0000  ///<  腐蚀膨胀A模板第11行
#define ED_A_MEM_MODEL_11_OFFSET        16
#define ED_A_MEM_MODEL_N7_REG           0x16f       ///<  腐蚀膨胀A模板7寄存器
#define ED_A_MEM_MODEL_12_MASK          0x1fff      ///<  腐蚀膨胀A模板第12行
#define ED_A_MEM_MODEL_12_OFFSET        0


#ifdef __cplusplus
extern "C" {
#endif

DLLSHARED_EXPORT int EDA_Model_Init(u32 acce_index);
DLLSHARED_EXPORT int EDA_Model_Param_Set(u32 acce_index);
DLLSHARED_EXPORT inline int EDA_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void EDA_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void EDA_Model_Disable(void);
DLLSHARED_EXPORT inline void EDA_Model_Enable(void);
DLLSHARED_EXPORT inline void EDA_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void EDA_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT void EDA_Model_Reg_Show(void);
DLLSHARED_EXPORT inline void EDA_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_ED_A_Boundary_Extr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_A_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_A_Hp_Wr_Ddr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_A_Loop_Num(u32 num);
DLLSHARED_EXPORT void Set_ED_A_Model_Type(u32 type, u16 * mask);
DLLSHARED_EXPORT void Set_ED_A_Mode_Sel(u32 mode);
DLLSHARED_EXPORT void Set_ED_A_Side_Del_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_A_Threshold(u32 th);

DLLSHARED_EXPORT void ED_A_CTRL_DILATE_MODE(void);
DLLSHARED_EXPORT void ED_A_CTRL_DISABLE(void);
DLLSHARED_EXPORT void ED_A_CTRL_ENABLE(void);
DLLSHARED_EXPORT void ED_A_CTRL_ERODE_MODE(void);
DLLSHARED_EXPORT void ED_A_CTRL_SIDE_DEL_DISABLE(void);
DLLSHARED_EXPORT void ED_A_CTRL_SIDE_DEL_ENABLE(void);
DLLSHARED_EXPORT void ED_A_CTRL_TH(u32 src);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_0(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_1(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_10(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_11(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_12(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_2(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_3(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_4(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_5(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_6(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_7(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_8(u32 num);
DLLSHARED_EXPORT void ED_A_MEM_MODEL_9(u32 num);

#ifdef __cplusplus
}
#endif

#endif // EROSIONDILATIONA_H
