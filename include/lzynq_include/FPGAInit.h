#ifndef __FPGAINIT_H__
#define __FPGAINIT_H__

#include "define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief FPGAWorkEnvInit
 * @param start_x
 * @param start_y
 * @param back_color
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化FPGA的工作环境
 */
DLLSHARED_EXPORT void FPGAWorkEnvInit(u32 start_x, u32 start_y, u32 back_color);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __FPGAINIT_H__ */
