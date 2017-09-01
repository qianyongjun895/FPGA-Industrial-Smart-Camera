#ifndef LICENSE_H
#define LICENSE_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 初始化认证信息
 * @param
 * @return
 * @author <AutumnX>
 * @note
 * 系统启动时，先调用此接口
 */
void initLicenseData(void);

/**
 * @brief 检查DNA是否正确
 * @param
 * @return 0:正确 -1:错误
 * @author <AutumnX>
 * @note
 */
int isDNARight(void);

/**
 * @brief 认证是否到期
 * @param
 * @return 0:未到期 1:已到期
 * @author <AutumnX>
 * @note
 */
int isLicenseExpire(void);

/**
 * @brief 注册码校验
 * @param reg_code 注册码
 * @return 0:注册码错误 1:临时注册 2:永久注册
 * @author <AutumnX>
 * @note
 * 相机注册时，调用此接口
 */
int isLicenseRight(const char *reg_code);

/**
 * @brief 获取注册状态
 * @param
 * @return 0:未注册或已到期 1:临时注册 2:永久注册
 * @author <AutumnX>
 * @note
 * 相机注册时，调用些接口
 */
unsigned int GetLicenseStatus(void);
/**
 * @brief 相机临时注册时，获取到期时间
 * @param
 * @return 到期时间
 * @author <AutumnX>
 * @note
 */
unsigned int GetExpireDate(void);

/**
 * @brief 相机临时注册时，获取剩余天数
 * @param
 * @return 剩余天数
 * @author <AutumnX>
 * @note
 */
unsigned int GetRemainDays(void);

/**
 * @brief 获取相机回报码
 * @param rcode_high 指针参数，传出 回报码高位部分
 * @param rcode_low 指针参数，传出 回报码低位部分
 * @return
 * @author <AutumnX>
 * @note
 */
void GetResponseCode(unsigned int *rcode_high, unsigned int *rcode_low);

/**
 * @brief 获取相机序列号
 * @param snum_high 指针参数，传出 序列号高位部分
 * @param snum_low 指针参数，传出 序列号低位部分
 * @return
 * @author <AutumnX>
 * @note
 */
void GetSerialNumber(unsigned int *snum_high, unsigned int *snum_low);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
