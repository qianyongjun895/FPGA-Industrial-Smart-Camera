#ifndef __SPI_H_
#define __SPI_H_

#define SPI_MEM_ADR_REG         0x88	///<  SPI地址寄存器
#define SPI_MEML_WR_DAT_REG	0x89	///<  SPI写数据寄存器
#define SPI_CTRL_WR_REG         0x8a	///<  SPI写使能寄存器
#define SPI_CTRL_WR_MASK	0x1	///<  SPI写使能掩码
#define SPI_CTRL_RD_REG         0x8b	///<  SPI读使能寄存器
#define SPI_CTRL_RD_MASK	0x1	///<  SPI读使能掩码
#define SPI_MEM_RD_DAT_REG	0x1082	///<  SPI读数据寄存器

#endif

