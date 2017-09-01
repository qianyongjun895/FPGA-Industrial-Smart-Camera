#ifndef CONTRASTTRANSFER_H
#define CONTRASTTRANSFER_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P4)对比度转换 */
#define CONTRAST_CTRL_REG                   0x125       ///<  对比度转换控制寄存器
#define CONTRAST_CTRL_EN_MASK               0x1         ///<  对比度转换使能
#define CONTRAST_CTRL_EN_OFFSET             0
#define CONTRAST_CTRL_GAIN_MASK             0xff0000    ///<  对比度转换强度，有效值为0~255
#define CONTRAST_CTRL_GAIN_OFFSET           16
#define CONTRAST_CTRL_MEDIAN_GRAY_MASK      0xff000000  ///<  对比度转换偏移，有效值为0~255
#define CONTRAST_CTRL_MEDIAN_GRAY_OFFSET    24


#ifdef __cplusplus
extern "C" {
#endif

DLLSHARED_EXPORT int CT_Model_Init(u32 acce_index);
DLLSHARED_EXPORT int CT_Model_Param_Set(u32 acce_index);
DLLSHARED_EXPORT inline int CT_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void CT_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void CT_Model_Disable(void);
DLLSHARED_EXPORT inline void CT_Model_Enable(void);
DLLSHARED_EXPORT inline void CT_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void CT_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT inline void CT_Model_Reg_Show(void);
DLLSHARED_EXPORT inline void CT_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_Contrast_Transform_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Contrast_Transform_Gain(u32 gain);
DLLSHARED_EXPORT void Set_Contrast_Transform_Median_Gray(u32 medianGray);

#ifdef __cplusplus
}
#endif

#endif // CONTRASTTRANSFER_H
