#ifndef CONTRASTENHANCEMENT_H
#define CONTRASTENHANCEMENT_H

#include "define.h"
#include "AcceCommon.h"


extern u8 g_balanceLut[256];


/** Model(P3)对比度增强 */
#define BALANCE_CTRL_REG                    0x184       ///<  均衡寄存器
#define BALANCE_CTRL_EN_MASK                0x1         ///<  均衡使能
#define BALANCE_CTRL_EN_OFFSET              0
#define BALANCE_CTRL_COEF_REG               0x185       ///<  均衡系数写入FPGA控制寄存器
#define BALANCE_CTRL_COEF_WR_EN_MASK        0x1         ///<  均衡系数写入FPGA使能
#define BALANCE_CTRL_COEF_WR_EN_OFFSET      0
#define BALANCE_CTRL_COEF_WR_DAT_MASK       0xff0000    ///<  均衡系数写入FPGA数据
#define BALANCE_CTRL_COEF_WR_DAT_OFFSET     16
#define BALANCE_CTRL_COEF_WR_ADDR_MASK      0xff000000  ///<  均衡系数写入FPGA地址
#define BALANCE_CTRL_COEF_WR_ADDR_OFFSET    24


#ifdef __cplusplus
extern "C" {
#endif

DLLSHARED_EXPORT int Balance_Model_Init(u32 acce_index);
DLLSHARED_EXPORT int Balance_Model_Param_Set(u32 acce_index);
DLLSHARED_EXPORT inline int Balance_Model_Input_Model_Get(unsigned int acce_index);
DLLSHARED_EXPORT void Balance_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);
DLLSHARED_EXPORT inline void Balance_Model_Disable(void);
DLLSHARED_EXPORT inline void Balance_Model_Enable(void);
DLLSHARED_EXPORT inline void Balance_Model_Write_DDR_On(unsigned int acce_index);
DLLSHARED_EXPORT inline void Balance_Model_Write_DDR_Off(void);
DLLSHARED_EXPORT void Balance_Model_Reg_Show(void);
DLLSHARED_EXPORT inline void Balance_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT s32 SetImageBalanceCoef(BALANCE_POINT_INFO * pBalanceParam, u8 pointsY[]);

DLLSHARED_EXPORT void Set_Balance_Coef_Data(POINT_I * point);
DLLSHARED_EXPORT void Set_Balance_Coef_Wr_Ddr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Balance_Enable(u32 flag);

DLLSHARED_EXPORT void BALANCE_CTRL_COEF_WR_ADDR(u32 addr);
DLLSHARED_EXPORT void BALANCE_CTRL_COEF_WR_DAT(u32 num);
DLLSHARED_EXPORT void BALANCE_CTRL_COEF_WR_DISABLE(void);
DLLSHARED_EXPORT void BALANCE_CTRL_COEF_WR_ENABLE(void);
DLLSHARED_EXPORT void BALANCE_CTRL_DISABLE(void);
DLLSHARED_EXPORT void BALANCE_CTRL_ENABLE(void);

#ifdef __cplusplus
}
#endif



#endif // CONTRASTENHANCEMENT_H
