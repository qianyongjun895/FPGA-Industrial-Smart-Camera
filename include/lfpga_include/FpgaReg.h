#ifndef FPGAREG_H
#define FPGAREG_H

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "emio.h"
#include "define.h"
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define RS_ENABLE   1
#define RS_DISABLE  0

extern u32 g_RegNum;




//#define CMOS_START_Y_REG        0xb3    ///<  CMOS采集图像Y起始地址设置寄存器
//#define CMOS_START_Y_MASK       0xffff  ///<  CMOS采集图像Y起始地址设置掩码


/** 中断控制寄存器 */
#define FPGA_DNA_CHECK_REG0			    0x10f4     ///<  DNA验证通过标志 1表示DNA验证通过，0表示失败
#define FPGA_DNA_GET_REG0			    0x10f5     ///<  DNA序列号低4字节
#define FPGA_DNA_GET_REG1			    0x10f6     ///<  DNA序列号高4字节

#define FPGA_IMAGE_SIZE_REG			    0x10fc     ///<  彩色，全局，30w
#define FPGA_VERSION_REG			    0x10ff     ///<  16年11月25日，版本0

#define I2C_CTRL_DEV_ADDR_REG	0x81	///<  i2c设备地址寄存器
#define I2C_CTRL_DEV_ADDR_MASK	0xffff	///<  i2c设备地址掩码
#define I2C_CTRL_REG_ADDR_REG	0x82	///<  i2c设备寄存器地址寄存器
#define I2C_CTRL_REG_ADDR_MASK	0xffff	///<  i2c设备寄存器地址掩码
#define I2C_CTRL_TX_DATA_REG	0x83	///<  i2c设备发送数据寄存器
#define I2C_CTRL_TX_DATA_MASK	0xffff	///<  i2c设备发送数据掩码
#define I2C_CTRL_TX_PS_REG	0x84	///<  i2c设备发送使能寄存器
#define I2C_CTRL_TX_PS_MASK	0x1	///<  i2c设备发送使能掩码
#define I2C_CTRL_RX_PS_REG	0x85	///<  i2c设备接收使能寄存器
#define I2C_CTRL_RX_PS_MASK	0x1	///<  i2c设备接收使能掩码

#define I2C_CTRL_RX_DATA_REG	0x1081	///<  i2c设备接收数据寄存器

#define SPI_MEM_ADR_REG	0x88	///<  SPI地址寄存器
#define SPI_MEML_WR_DAT_REG	0x89	///<  SPI写数据寄存器
#define SPI_CTRL_WR_REG	0x8a	///<  SPI写使能寄存器
#define SPI_CTRL_WR_MASK	0x1	///<  SPI写使能掩码
#define SPI_CTRL_RD_REG	0x8b	///<  SPI读使能寄存器
#define SPI_CTRL_RD_MASK	0x1	///<  SPI读使能掩码

#define SPI_MEM_RD_DAT_REG	0x1082	///<  SPI读数据寄存器


//#define SYS_CTRL_CMOS_CPT_TRIGGER_REG		0x16000510	///<  触发CMOS拍照一次，仅对CMOS配置成触发拍照模式有效
#define SYS_MEM_VGA_START_ADDR_REG	0xbf		///<  VGA显示起始地址




#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


extern int FGPA_Dna_Read(unsigned int *pDnaHigh, unsigned int *pDnaLow);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* FPGAREG_H */
