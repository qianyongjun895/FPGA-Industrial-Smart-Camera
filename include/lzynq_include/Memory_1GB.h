#ifndef HARDWARE_1GB_H
#define HARDWARE_1GB_H

#include "Hardware_Common.h"


/**  @brief  1GB内存、彩色相机  */
#define FRAME_BUFFER_PHYADDR_RGB_1GB        0x20000000      ///< Linux的framebuffer
#define FRAME_BUFFER_SIZE_RGB_1GB           0x00600000

#define MODBUS_PHYADDR_RGB_1GB              0x20600000      ///< MODBUS_ADDR Modbus数据在内存中的起始地址
#define MODBUS_SIZE_RGB_1GB                 0x000a0000

#define INTERCOM_MODBUS_PHYADDR_RGB_1GB     0x206A0000      ///< INTERCOM_MODBUS_ADDR 内部Modbus数据在内存中的起始地址
#define INTERCOM_MODBUS_SIZE_RGB_1GB        0x00060000

#define USDF_DATA_PHYADDR_RGB_1GB           0x20700000      ///< USER_DEFINE_DATA_ADDR 内存中所要发送的数据的起始地址
#define USDF_DATA_SIZE_RGB_1GB              0x00100000

#define PLC_COMM_PHYADDR_RGB_1GB            0x20800000      ///< PLC_ADDR 1MB PLC数据在内存中的起始地址
#define PLC_COMM_SIZE_RGB_1GB               0x00100000

#define ACCELERATOR_PHYADDR_RGB_1GB         0x20900000      ///< 加速器模块参数保存地址
#define ACCELERATOR_SIZE_RGB_1GB            0x00400000      ///< 加速器模块参数占用内存的总大小

#define TASK_BASE_PHYADDR_RGB_1GB           0x20D00000      ///< TASK_BASE_ADDR
#define TASK_BASE_SIZE_RGB_1GB              0x00200000

#if 0
#define TASK_OUTPUT_PHYADDR_RGB_1GB         0x20F00000      ///< TASK_OUTPUT_BASE_ADDR Every step result datas will be stored start from here
#define TASK_OUTPUT_SIZE_RGB_1GB            0x00100000
#else
#define TASK_OUTPUT_PHYADDR_RGB_1GB			0x20F00000      ///< TASK_OUTPUT_BASE_ADDR Every step result datas will be stored start from here
#define TASK_OUTPUT_SIZE_RGB_1GB			0x000F8000
#define TASK_GDATA_PHYADDR_RGB_1GB			0x20FF8000      ///< TASK_GDATA_PHYADDR Gdatas will be stored start from here
#define TASK_GDATA_SIZE_RGB_1GB				0x00008000
#endif

#define TASK_MODEL_PHYADDR_RGB_1GB          0x21000000      ///< TASK_MODEL_BASE_ADDR The model bin file will be load to or save from this physical address
#define TASK_MODEL_SIZE_RGB_1GB             0x0F000000


#if 0 ///< 以下宏定义暂不使用
#define CPT_COLOR_PIC_PHYADDR_RGB_1GB       0x18000000  ///< CMOS抓图彩色图像保存区域(30W)
#define CPT_COLOR_PIC_SIZE_RGB_1GB          0x00180000

#define CPT_MONO_PIC_PHYADDR_RGB_1GB        0x18180000  ///< CMOS抓图黑白图像保存区域(30W)
#define CPT_MONO_PIC_SIZE_RGB_1GB           0x00080000

#define SKE_FEATURE_POINTS_PHYADDR_RGB_1GB  0x18300000  ///< fpga计算轮廓匹配特征点坐标信息保存区
#define SKE_FEATURE_POINTS_SIZE_RGB_1GB     0x00180000

#define SKE_DIR_INFO_PHYADDR_RGB_1GB        0x18500000  ///< fpga计算轮廓匹配特征点方向信息保存区
#define SKE_DIR_INFO_SIZE_RGB_1GB           0x00200000

#define SKE_MAXIMA_INFO_PHYADDR_RGB_1GB     0x18700000  ///< fpga计算轮廓匹配极值点信息保存区
#define SKE_MAXIMA_INFO_SIZE_RGB_1GB        0x00200000

#define EDGE_POINTS_PHYADDR_RGB_1GB         0x19700000  ///< fpga计算边沿点信息保存区
#define EDGE_POINTS_SIZE_RGB_1GB            0x00100000

#define BINARY_AREA0_PHYADDR_RGB_1GB        0x19A00000  ///< fpga二值化输出空间0
#define BINARY_AREA0_SIZE_RGB_1GB           0x00080000

#define BINARY_AREA1_PHYADDR_RGB_1GB        0x19A80000  ///< fpga二值化输出空间1
#define BINARY_AREA1_SIZE_RGB_1GB           0x00080000

#define BINARY_AREA2_PHYADDR_RGB_1GB        0x19B00000  ///< fpga二值化输出空间2
#define BINARY_AREA2_SIZE_RGB_1GB           0x00080000

#define BINARY_AREA3_PHYADDR_RGB_1GB        0x19B80000  ///< fpga二值化输出空间3
#define BINARY_AREA3_SIZE_RGB_1GB           0x00080000

#define EROSION_AREA0_PHYADDR_RGB_1GB       0x19C00000  ///< fpga腐蚀膨胀输出空间0
#define EROSION_AREA0_SIZE_RGB_1GB          0x00080000

#define EROSION_AREA1_PHYADDR_RGB_1GB       0x19C80000  ///< fpga腐蚀膨胀输出空间1
#define EROSION_AREA1_SIZE_RGB_1GB          0x00080000

#define CONNECT_DOMAIN_RST_PHYADDR_RGB_1GB  0x19D00000  ///< fpga计算连通域结果保存空间
#define CONNECT_DOMAIN_RST_SIZE_RGB_1GB     0x00080000

#define EPS_SELECT_RST_PHYADDR_RGB_1GB      0x19D80000  ///< fpga边沿筛选结果保存空间
#define EPS_SELECT_RST_SIZE_RGB_1GB         0x00080000

#define PIC_PRE_PROC_RST_PHYADDR_RGB_1GB    0x19E00000  ///< fpga图像预处理结果（滤波、均衡等操作结果）
#define PIC_PRE_PROC_RST_SIZE_RGB_1GB       0x00200000

#define VGA_DISPLAY_PHYADDR_RGB_1GB         0x1A600000  ///< Linux的VGA图像存储地址(30W)
#define VGA_DISPLAY_SIZE_RGB_1GB            0x00200000
#endif

#define CIRCLE_MODEL_PHYADDR_RGB_1GB            0xc300000
#define TEMPLATE_MODEL_PHYADDR_RGB_1GB          0xc950000
#define CIRCLE_MODEL_SIZE_MONOCHROME_RGB        0x50000     ///< 320KB
#define TEMPLATE_MODEL_SIZE_MONOCHROME_RGB      0x220000    ///< 5MB + 320KB
#define CIRCLE_MODEL_NUM_MAX_RGB_1GB            20          ///< Cost size: 0x650000
#define TEMPLATE_MODEL_NUM_MAX_RGB_1GB          46          ///< Cost size: 0x5500000



#ifdef __cplusplus
extern "C" {
#endif



/**
 * @brief Memory_1G_Alloc_30W
 * @param pHardwareConfig
 * @author Vincent
 * @date 2017/5/12
 * @note 1GB内存下30W像素的相机配置参数初始化
 */
DLLSHARED_EXPORT void Memory_1G_Alloc_30W(HARDWARE_CONFIG *pHardwareConfig);

/**
 * @brief Memory_1G_Alloc_130W
 * @param pHardwareConfig
 * @author Vincent
 * @date 2017/5/12
 * @note 1GB内存下130W像素的相机配置参数初始化
 */
DLLSHARED_EXPORT void Memory_1G_Alloc_130W(HARDWARE_CONFIG *pHardwareConfig);

/**
 * @brief Memory_1G_Alloc_500W
 * @param pHardwareConfig
 * @author Vincent
 * @date 2017/5/12
 * @note 1GB内存下500W像素的相机配置参数初始化
 */
DLLSHARED_EXPORT void Memory_1G_Alloc_500W(HARDWARE_CONFIG *pHardwareConfig);



#ifdef __cplusplus
}
#endif

#endif // HARDWARE_1GB_H
