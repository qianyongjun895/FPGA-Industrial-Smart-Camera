#ifndef HARDWARE_512MB_H
#define HARDWARE_512MB_H

#include "Hardware_Common.h"


/**  @brief  512MB内存、彩色相机  */
#define FRAME_BUFFER_PHYADDR_RGB_512M       0x10000000      ///< Linux的framebuffer
#define FRAME_BUFFER_SIZE_RGB_512M          0x00600000

#define MODBUS_PHYADDR_RGB_512M             0x10600000      ///< MODBUS_ADDR Modbus数据在内存中的起始地址
#define MODBUS_SIZE_RGB_512M                0x000a0000

#define INTERCOM_MODBUS_PHYADDR_RGB_512M    0x106A0000      ///< INTERCOM_MODBUS_ADDR 内部Modbus数据在内存中的起始地址
#define INTERCOM_MODBUS_SIZE_RGB_512M       0x00060000

#define USDF_DATA_PHYADDR_RGB_512M          0x10700000      ///< USER_DEFINE_DATA_ADDR 内存中所要发送的数据的起始地址
#define USDF_DATA_SIZE_RGB_512M             0x00100000

#define PLC_COMM_PHYADDR_RGB_512M           0x10800000      ///< PLC_ADDR 1MB PLC数据在内存中的起始地址
#define PLC_COMM_SIZE_RGB_512M              0x00100000

#define ACCELERATOR_PHYADDR_RGB_512M	    0x10900000	    ///< 加速器模块参数保存地址
#define ACCELERATOR_SIZE_RGB_512M           0x00400000	    ///< 加速器模块参数占用内存的总大小

#define TASK_BASE_PHYADDR_RGB_512M          0x10D00000      ///< TASK_BASE_ADDR
#define TASK_BASE_SIZE_RGB_512M             0x00200000

#define TASK_OUTPUT_PHYADDR_RGB_512M        0x10F00000      ///< TASK_OUTPUT_BASE_ADDR Every step result datas will be stored start from here
#define TASK_OUTPUT_SIZE_RGB_512M           0x00100000

#define TASK_MODEL_PHYADDR_RGB_512M         0x11000000      ///< TASK_MODEL_BASE_ADDR The model bin file will be load to or save from this physical address
#define TASK_MODEL_SIZE_RGB_512M            0x07000000



#define CIRCLE_MODEL_PHYADDR_RGB_512M           0xc300000
#define TEMPLATE_MODEL_PHYADDR_RGB_512M         0xc950000
#define CIRCLE_MODEL_SIZE_MONOCHROME_RGB        0x50000     ///< 320KB
#define TEMPLATE_MODEL_SIZE_MONOCHROME_RGB      0x220000    ///< 5MB + 320KB
#define CIRCLE_MODEL_NUM_MAX_RGB_512M           20          ///< Cost size: 0x650000
#define TEMPLATE_MODEL_NUM_MAX_RGB_512M         46          ///< Cost size: 0x5500000


#ifdef __cplusplus
extern "C" {
#endif



/**
 * @brief Memory_512M_Alloc_30W
 * @param pHardwareConfig
 * @author Vincent
 * @date 2017/5/12
 * @note 512MB内存下30W像素的相机配置参数初始化
 */
DLLSHARED_EXPORT void Memory_512M_Alloc_30W(HARDWARE_CONFIG *pHardwareConfig);

/**
 * @brief Memory_512M_Alloc_130W
 * @param pHardwareConfig
 * @author Vincent
 * @date 2017/5/12
 * @note 512MB内存下130W像素的相机配置参数初始化
 */
DLLSHARED_EXPORT void Memory_512M_Alloc_130W(HARDWARE_CONFIG *pHardwareConfig);



#ifdef __cplusplus
}
#endif



#endif // HARDWARE_512MB_H
