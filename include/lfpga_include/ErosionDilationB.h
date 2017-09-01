#ifndef EROSIONDILATIONB_H
#define EROSIONDILATIONB_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P35)腐蚀膨胀B */
#define ED_B_LOOP_NUM_REG               0x176       ///<  腐蚀膨胀B循环次数寄存器
#define ED_B_LOOP_NUM_MASK              0xf         ///<  腐蚀膨胀B循环次数掩码
#define ED_B_LOOP_NUM_OFFSET            0
#define ED_B_BOUNDARY_EXTR_EN_MASK      0x100		///<  腐蚀膨胀B提取边沿功能使能掩码
#define ED_B_BOUNDARY_EXTR_EN_OFFSET    8
#define ED_B_CTRL_REG                   0x177       ///<  腐蚀膨胀B控制寄存器
#define ED_B_CTRL_EN_MASK               0x1         ///<  腐蚀膨胀B使能掩码
#define ED_B_CTRL_EN_OFFSET             0
#define ED_B_CTRL_SIDE_DEL_EN_MASK      0x2         ///<  腐蚀膨胀B边界删除使能掩码
#define ED_B_CTRL_SIDE_DEL_EN_OFFSET    1
#define ED_B_CTRL_MODE_MASK             0x8         ///<  腐蚀/膨胀 模式切换掩码 1=腐蚀 0=膨胀
#define ED_B_CTRL_MODE_OFFSET           3
#define ED_B_CTRL_TH_MASK               0xff0000    ///<  腐蚀膨胀B门限掩码
#define ED_B_CTRL_TH_OFFSET             16
#define ED_B_CTRL_MDOE_MASK             0xff000000  ///<  腐蚀膨胀B模板大小 1表示3x3，2表示5x5,即模板的大小为2xN+1
#define ED_B_CTRL_MDOE_OFFSET           24
#define ED_B_MEM_MODEL_N1_REG           0x179       ///<  腐蚀膨胀B模板1寄存器
#define ED_B_MEM_MODEL_0_MASK           0x1fff      ///<  腐蚀膨胀B模板第1行
#define ED_B_MEM_MODEL_0_OFFSET         0
#define ED_B_MEM_MODEL_1_MASK           0x1fff0000  ///<  腐蚀膨胀B模板第2行
#define ED_B_MEM_MODEL_1_OFFSET         16
#define ED_B_MEM_MODEL_N2_REG           0x17a       ///<  腐蚀膨胀B模板2寄存器
#define ED_B_MEM_MODEL_2_MASK           0x1fff      ///<  腐蚀膨胀B模板第3行
#define ED_B_MEM_MODEL_2_OFFSET         0
#define ED_B_MEM_MODEL_3_MASK           0x1fff0000  ///<  腐蚀膨胀B模板第4行
#define ED_B_MEM_MODEL_3_OFFSET         16
#define ED_B_MEM_MODEL_N3_REG           0x17b       ///<  腐蚀膨胀B模板3寄存器
#define ED_B_MEM_MODEL_4_MASK           0x1fff      ///<  腐蚀膨胀B模板第5行
#define ED_B_MEM_MODEL_4_OFFSET         0
#define ED_B_MEM_MODEL_5_MASK           0x1fff0000  ///<  腐蚀膨胀B模板第6行
#define ED_B_MEM_MODEL_5_OFFSET         16
#define ED_B_MEM_MODEL_N4_REG           0x17c       ///<  腐蚀膨胀B模板4寄存器
#define ED_B_MEM_MODEL_6_MASK           0x1fff      ///<  腐蚀膨胀B模板第7行
#define ED_B_MEM_MODEL_6_OFFSET         0
#define ED_B_MEM_MODEL_7_MASK           0x1fff0000  ///<  腐蚀膨胀B模板第8行
#define ED_B_MEM_MODEL_7_OFFSET         16
#define ED_B_MEM_MODEL_N5_REG           0x17d       ///<  腐蚀膨胀B模板5寄存器
#define ED_B_MEM_MODEL_8_MASK           0x1fff      ///<  腐蚀膨胀B模板第8行
#define ED_B_MEM_MODEL_8_OFFSET         0
#define ED_B_MEM_MODEL_9_MASK           0x1fff0000  ///<  腐蚀膨胀B模板第9行
#define ED_B_MEM_MODEL_9_OFFSET         16
#define ED_B_MEM_MODEL_N6_REG           0x17e       ///<  腐蚀膨胀B模板6寄存器
#define ED_B_MEM_MODEL_10_MASK          0x1fff      ///<  腐蚀膨胀B模板第10行
#define ED_B_MEM_MODEL_10_OFFSET        0
#define ED_B_MEM_MODEL_11_MASK          0x1fff0000  ///<  腐蚀膨胀B模板第11行
#define ED_B_MEM_MODEL_11_OFFSET        16
#define ED_B_MEM_MODEL_N7_REG           0x17f       ///<  腐蚀膨胀B模板7寄存器
#define ED_B_MEM_MODEL_12_MASK          0x1fff      ///<  腐蚀膨胀B模板第12行
#define ED_B_MEM_MODEL_12_OFFSET        0


#ifdef __cplusplus
extern "C" {
#endif

DLLSHARED_EXPORT int EDB_Model_Init(u32 acce_index);
DLLSHARED_EXPORT int EDB_Model_Param_Set(u32 acce_index);
DLLSHARED_EXPORT inline int EDB_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void EDB_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void EDB_Model_Disable(void);
DLLSHARED_EXPORT inline void EDB_Model_Enable(void);
DLLSHARED_EXPORT inline void EDB_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void EDB_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT void EDB_Model_Reg_Show(void);
DLLSHARED_EXPORT inline void EDB_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_ED_B_Boundary_Extr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_B_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_B_Loop_Num(u32 num);
DLLSHARED_EXPORT void Set_ED_B_Model_Type(u32 type, u16 * mask);
DLLSHARED_EXPORT void Set_ED_B_Mode_Sel(u32 mode);
DLLSHARED_EXPORT void Set_ED_B_Side_Del_Enable(u32 flag);
DLLSHARED_EXPORT void Set_ED_B_Threshold(u32 th);

DLLSHARED_EXPORT void ED_B_CTRL_DILATE_MODE(void);
DLLSHARED_EXPORT void ED_B_CTRL_DISABLE(void);
DLLSHARED_EXPORT void ED_B_CTRL_ENABLE(void);
DLLSHARED_EXPORT void ED_B_CTRL_ERODE_MODE(void);
DLLSHARED_EXPORT void ED_B_CTRL_SIDE_DEL_DISABLE(void);
DLLSHARED_EXPORT void ED_B_CTRL_SIDE_DEL_ENABLE(void);
DLLSHARED_EXPORT void ED_B_CTRL_TH(u32 src);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_0(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_1(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_10(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_11(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_12(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_2(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_3(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_4(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_5(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_6(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_7(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_8(u32 num);
DLLSHARED_EXPORT void ED_B_MEM_MODEL_9(u32 num);

#ifdef __cplusplus
}
#endif

#endif // EROSIONDILATIONB_H
