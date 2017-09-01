#ifndef GAUSS_H
#define GAUSS_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P2)高斯滤波 */
#define GAUSS_CTRL_REG             0x150        ///<  高斯滤波控制寄存器
#define GAUSS_CTRL_EN_MASK         0x1          ///<  高斯滤波使能
#define GAUSS_CTRL_EN_OFFSET       0
#define GAUSS_KERNEL_PARA_REG1	   0x157		///<  1: 0-15; 2: 16-31
#define GAUSS_KERNEL_PARA_REG2	   0x158		///<  3: 0-15
#define GAUSS_KERNEL_PARA_REG3	   0x159		///<  4: 16-31; 5: 0-15


#ifdef __cplusplus
extern "C" {
#endif

DLLSHARED_EXPORT int Gauss_Model_Init(u32 acce_index);
DLLSHARED_EXPORT int Gauss_Model_Param_Set(u32 acce_index);
DLLSHARED_EXPORT inline int Gauss_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void Gauss_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void Gauss_Model_Disable(void);
DLLSHARED_EXPORT inline void Gauss_Model_Enable(void);
DLLSHARED_EXPORT inline void Gauss_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void Gauss_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT void Gauss_Model_Reg_Show(void);
DLLSHARED_EXPORT inline void Gauss_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_Gauss_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Gauss_Kernel_Param(u16 * gauss_kernel);

extern void GAUSS_CTRL_DISABLE(void);
extern void GAUSS_CTRL_ENABLE(void);

#ifdef __cplusplus
}
#endif


#endif // GAUSS_H
