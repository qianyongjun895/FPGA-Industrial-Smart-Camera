#ifndef DEFECT_H
#define DEFECT_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P15)缺陷提取 */
#define DEFECT_CTRL_REG                 0x130       ///< 缺陷提取控制寄存器
#define DEFECT_CTRL_EN_MASK             0x1         ///< 缺陷提取使能
#define DEFECT_CTRL_EN_OFFSET           0
#define DEFECT_CTRL_WR_DDR_EN_MASK      0x10        ///< 缺陷提取写DDR使能
#define DEFECT_CTRL_WR_DDR_EN_OFFSET    4
#define DEFECT_CTRL_REF_VALUE_MASK      0xff00      ///< 缺陷提取基准值
#define DEFECT_CTRL_REF_VALUE_OFFSET    8
#define DEFECT_CTRL_GAIN_MASK           0x3f0000    ///< 缺陷提取增益,有效值为0~63
#define DEFECT_CTRL_GAIN_OFFSET         16
#define DEFECT_MEM_DATA_AVG_REG         0x1085      ///< 缺陷提取的图像平均值


#ifdef __cplusplus
extern "C" {
#endif

DLLSHARED_EXPORT int Defect_Model_Init(u32 acce_index);
DLLSHARED_EXPORT int Defect_Model_Param_Set(u32 acce_index);
DLLSHARED_EXPORT inline int Defect_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void Defect_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void Defect_Model_Disable(void);
DLLSHARED_EXPORT inline void Defect_Model_Enable(void);
DLLSHARED_EXPORT inline void Defect_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void Defect_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT void Defect_Model_Reg_Show(void);
DLLSHARED_EXPORT inline void Defect_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_Defect_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Defect_Wr_Ddr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Defect_Ref_Value(u32 value);
DLLSHARED_EXPORT void Set_Defect_Gain(u32 gain);
DLLSHARED_EXPORT u32 Get_Defect_Data_Avg(void);



#ifdef __cplusplus
}
#endif

#endif // DEFECT_H
