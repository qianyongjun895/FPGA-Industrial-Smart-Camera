#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <fcntl.h>
#include "define.h"
#include "BaseStruct.h"
#include "sys/types.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief system_result
 * @param status system()函数的返回值
 * @return -1:失败 0:成功
 * @author Vincent
 * @date 2017/5/12
 * @note 检查system() 函数调用结果是否成功
 */
DLLSHARED_EXPORT s32 system_result(pid_t status);

/**
 * @brief SystemCmd
 * @param pCmd
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 调用系统命令
 */
DLLSHARED_EXPORT s32 SystemCmd(s8 * pCmd);

/**
 * @brief SystemFileCheck
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 系统文件的检查
 */
DLLSHARED_EXPORT s32 SystemFileCheck(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEMINFO_H
