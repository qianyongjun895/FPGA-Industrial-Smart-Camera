#ifndef __SYS_CTRL_H_
#define __SYS_CTRL_H_

#include "define.h"


#define CMOS_I2C_DEVICE_ADDR                0x00000090
#define EMIO_BK3_L_SW_ADRESS                0xE000A018
#define EMIO_BK3_M_SW_ADRESS                0xE000A01c
#define EMIO_BK3_DOUT_ADRESS                0xE000A04c
#define EMIO_BK3_DIN_ADRESS                 0xE000A06c
#define EMIO_BK3_DIRM_ADRESS                0xE000A2c4
#define EMIO_BK3_OPN_ADRESS                 0xE000A2c8

#define EMIO_BASSADRESS                     0xE000A000
#define EMIO_BK2_L_SW_ADRESS                0xE000A010
#define EMIO_BK2_M_SW_ADRESS                0xE000A014
#define EMIO_BK2_DOUT_ADRESS                0xE000A048
#define EMIO_BK2_DIN_ADRESS                 0xE000A068
#define EMIO_BK2_DIRM_ADRESS                0xE000A284
#define EMIO_BK2_OPN_ADRESS                 0xE000A288

#define EMIO_PHYADDR_ZYNQ                   0xE000A000
#define EMIO_REG_SIZE                       0x1000
#define EMIO_BK2_L_SW_OFFSET                0x00000010
#define EMIO_BK2_M_SW_OFFSET                0x00000014
#define EMIO_BK3_L_SW_OFFSET                0x00000018
#define EMIO_BK3_M_SW_OFFSET                0x0000001c
#define EMIO_BK2_DOUT_OFFSET                0x00000048
#define EMIO_BK3_DOUT_OFFSET                0x0000004c
#define EMIO_BK2_DIN_OFFSET                 0x00000068
#define EMIO_BK3_DIN_OFFSET                 0x0000006c
#define EMIO_BK2_DIRM_OFFSET                0x00000284
#define EMIO_BK2_OPN_OFFSET                 0x00000288
#define EMIO_BK3_DIRM_OFFSET                0x000002c4
#define EMIO_BK3_OPN_OFFSET                 0x000002c8


#define ARM_DIN_ROUGH_COO                   0x15100001
#define ARM_DIN_CPT_ROUGH_CNT               0x15100002
#define PL_STATUS1_ADDR                     0x15300001
#define ARM_DIN_PL_INT_REG                  0x15300007
#define ARM_DIN_SUM_SIDE_PIX                0x15100003

#define FPGA_OUTPUT_VALUE_CFG_ADDR          0x19000001
#define FPGA_FLASH_OUT_CFG_ADDR             0x19000002
#define FPGA_OUTPUT0_PULSE_WIDTH_CFG_ADDR   0x19000010
#define FPGA_OUTPUT1_PULSE_WIDTH_CFG_ADDR   0x19000011
#define FPGA_OUTPUT2_PULSE_WIDTH_CFG_ADDR   0x19000012
#define FPGA_OUTPUT3_PULSE_WIDTH_CFG_ADDR   0x19000013
#define FPGA_INPUT_VALUE_READ_ADDR          0x15a00001

#define DEFAULT_PULSE_WIDTH     500000 /* 10ms */
#define DEFAULT_OUTPUT_VALUE    1
extern unsigned int g_RegNum;

#define EMIO_SET_BIT_STATUS(addr,mask,status)   if ( status == RS_ENABLE ){\
        g_RegNum = EMIO_RD(addr);\
        EMIO_WR(addr, g_RegNum | mask);\
    }\
    else{\
        g_RegNum = EMIO_RD(addr);\
        EMIO_WR(addr, g_RegNum & (~mask));\
    }

#define EMIO_SET_BITS_NUM(addr,mask,num,offset)   g_RegNum = EMIO_RD(addr);\
    EMIO_WR(addr, (g_RegNum & (~mask)) | ((num << offset) & mask));


#define EMIO_GET_BITS_NUM(RegNum,addr,mask,offset)   g_RegNum = EMIO_RD(addr);\
    RegNum = ((g_RegNum & (mask)) >> offset);


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief EMIO_Init
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化EMIO
 */
DLLSHARED_EXPORT int EMIO_Init(void);

/**
 * @brief EMIO_DeInit
 * @author Vincent
 * @date 2017/5/12
 * @note EMIO析构
 */
DLLSHARED_EXPORT void EMIO_DeInit(void);

/**
 * @brief EMIO_WR
 * @param emio_addr
 * @param emio_data_out
 * @author Vincent
 * @date 2017/5/12
 * @note 写EMID接口
 */
DLLSHARED_EXPORT void EMIO_WR(unsigned int emio_addr, unsigned int emio_data_out);

/**
 * @brief EMIO_RD
 * @param emio_addr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 读EMIO接口
 */
DLLSHARED_EXPORT unsigned int EMIO_RD(unsigned int emio_addr);

#ifdef __cplusplus
}
#endif

#endif //__SYS_CTRL_H_

