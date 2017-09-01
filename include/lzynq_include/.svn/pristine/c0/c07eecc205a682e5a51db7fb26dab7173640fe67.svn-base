#ifndef __IIC_H_
#define __IIC_H_

#include "define.h"

#define I2C_CTRL_DEV_ADDR_REG	0x81	///<  i2c设备地址寄存器
#define I2C_CTRL_DEV_ADDR_MASK	0xffff	///<  i2c设备地址掩码
#define I2C_CTRL_REG_ADDR_REG	0x82	///<  i2c设备寄存器地址寄存器
#define I2C_CTRL_REG_ADDR_MASK	0xffff	///<  i2c设备寄存器地址掩码
#define I2C_CTRL_TX_DATA_REG	0x83	///<  i2c设备发送数据寄存器
#define I2C_CTRL_TX_DATA_MASK	0xffff	///<  i2c设备发送数据掩码
#define I2C_CTRL_TX_PS_REG      0x84    ///<  i2c设备发送使能寄存器
#define I2C_CTRL_TX_PS_MASK     0x1     ///<  i2c设备发送使能掩码
#define I2C_CTRL_RX_PS_REG      0x85	///<  i2c设备接收使能寄存器
#define I2C_CTRL_RX_PS_MASK     0x1     ///<  i2c设备接收使能掩码
#define I2C_CTRL_RX_DATA_REG	0x1081	///<  i2c设备接收数据寄存器

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/**
 * @brief I2C_WR
 * @param i2c_device_addr
 * @param i2c_reg_addr
 * @param i2c_reg_data
 * @author Vincent
 * @date 2017/5/12
 * @note 读I2C接口
 */
DLLSHARED_EXPORT void I2C_WR(unsigned int i2c_device_addr, unsigned int i2c_reg_addr,  unsigned int i2c_reg_data);

/**
 * @brief I2C_RD
 * @param i2c_device_addr
 * @param i2c_reg_addr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 写I2C接口
 */
DLLSHARED_EXPORT unsigned int I2C_RD(unsigned int i2c_device_addr, unsigned int i2c_reg_addr);

/**
 * @brief I2C_STATUS
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 查询I2C状态接口
 */
DLLSHARED_EXPORT int I2C_STATUS(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

