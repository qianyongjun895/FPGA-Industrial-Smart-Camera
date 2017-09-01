#ifndef __HARDWARECONFIG_H__
#define __HARDWARECONFIG_H__

#include "define.h"
#include "cmos_common.h"
#include "Hardware_Common.h"


#define MMAP_ADDR(phyaddr, size, g_pAddr) \
        g_pAddr = mmap(0, size, PROT_READ |PROT_WRITE, MAP_SHARED, memfd, phyaddr);\
        if(g_pAddr == MAP_FAILED) {\
            printf( "Can't map phyaddr = %#x, size = %#x \n",phyaddr, size);\
            close(memfd);\
            return -1;\
        } else {\
            memset(g_pAddr, 0, size);\
        }

extern HARDWARE_CONFIG *gpHardwareInfo;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief Get_HWC_Accelerator_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取预处理参数存放地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Accelerator_Phyaddr(void);

/**
 * @brief Get_HWC_Accelerator_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取预处理参数存放地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Accelerator_Size(void);

/**
 * @brief Get_HWC_Binary_Area0_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取fpga二值化输出空间
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Binary_Area_Phyaddr(void);

/**
 * @brief Get_HWC_Binary_Area_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga二值化输出空间
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Binary_Area_Size(void);

/**
 * @brief Get_HWC_CaptColor_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取CMOS抓图彩色图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_CaptColor_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_CaptColor_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取CMOS抓图彩色图像存储地址大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_CaptColor_Pic_Size(void);

/**
 * @brief Get_HWC_CaptDdrA_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取CPT模块DDRA图像地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_CaptDdrA_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_CaptMono_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取CMOS抓图黑白图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_CaptMono_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_CaptMono_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取CMOS抓图黑白图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_CaptMono_Pic_Size(void);

/**
 * @brief Get_HWC_PreProc_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/27
 * @note 获取预处理后图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_PreProc_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_PreProc_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/27
 * @note 获取预处理后图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_PreProc_Pic_Size(void);

/**
 * @brief Get_HWC_ColorDraw_Rst_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取颜色抽取结果存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_ColorDraw_Rst_Phyaddr(void);

/**
 * @brief Get_HWC_ColorDraw_Rst_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取颜色抽取结果存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_ColorDraw_Rst_Size(void);

/**
 * @brief Get_HWC_ConnectDomain_Rst_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取fpga计算连通域结果存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_ConnectDomain_Rst_Phyaddr(void);

/**
 * @brief Get_HWC_ConnectDomain_Rst_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga计算连通域结果存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_ConnectDomain_Rst_Size(void);

/**
 * @brief Get_HWC_EdgePoints_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取fpga计算边沿点信息存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_EdgePoints_Phyaddr(void);

/**
 * @brief Get_HWC_EdgePoints_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga计算边沿点信息存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_EdgePoints_Size(void);

/**
 * @brief Get_HWC_EdgePoints_Standby_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取fpga计算边沿点信息临时备份区地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_EdgePoints_Standby_Phyaddr(void);

/**
 * @brief Get_HWC_EdgePoints_Standby_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga计算边沿点信息临时备份区存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_EdgePoints_Standby_Size(void);

/**
 * @brief Get_HWC_Edge_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/31
 * @note 获取fpga边沿图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Edge_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_Edge_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/31
 * @note 获取fpga边沿图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Edge_Pic_Size(void);

/**
 * @brief Get_HWC_Emio_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取EMIO地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Emio_Phyaddr(void);

/**
 * @brief Get_HWC_EpsSelect_Rst_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取fpga边沿筛选结果存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_EpsSelect_Rst_Phyaddr(void);

/**
 * @brief Get_HWC_EpsSelect_Rst_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga边沿筛选结果存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_EpsSelect_Rst_Size(void);

/**
 * @brief Get_HWC_FrameBuffer_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取Linux的framebuffer地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_FrameBuffer_Phyaddr(void);

/**
 * @brief Get_HWC_FrameBuffer_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取Linux的framebuffer空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_FrameBuffer_Size(void);

/**
 * @brief Get_HWC_Intercom_Modbus_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取内部通信MODBUS数据存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Intercom_Modbus_Phyaddr(void);

/**
 * @brief Get_HWC_Intercom_Modbus_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取内部通信MODBUS数据存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Intercom_Modbus_Size(void);

/**
 * @brief Get_HWC_Modbus_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取MODBUS数据存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Modbus_Phyaddr(void);

/**
 * @brief Get_HWC_Modbus_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取MODBUS数据存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Modbus_Size(void);

/**
 * @brief Get_HWC_Pixel_config
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取像素配置
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Pixel_config(void);

/**
 * @brief Get_HWC_Pixel_Than
 * @return
 * @author Vincent
 * @date 2017/5/19
 * @note 获取UI与实际像素比
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Pixel_Than(void);

/**
 * @brief Get_HWC_Plc_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取plc数据存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Plc_Phyaddr(void);

/**
 * @brief Get_HWC_Plc_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取plc数据存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Plc_Size(void);

/**
 * @brief Get_HWC_RAM_Config
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取内存配置
 */
DLLSHARED_EXPORT unsigned int Get_HWC_RAM_Config(void);

/**
 * @brief Get_HWC_SelectColor_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取区域选择模块彩色图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SelectColor_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_SelectColor_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取区域选择模块彩色图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SelectColor_Pic_Size(void);

/**
 * @brief Get_HWC_SelectMono_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取区域选择模块黑白图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SelectMono_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_SelectMono_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取区域选择模块黑白图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SelectMono_Pic_Size(void);

/**
 * @brief Get_HWC_SimiColor_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取仿真功能彩色图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SimiColor_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_SimiColor_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取仿真功能彩色图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SimiColor_Pic_Size(void);

/**
 * @brief Get_HWC_SimiMono_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取仿真功能黑白图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SimiMono_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_SimiMono_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取仿真功能黑白图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_SimiMono_Pic_Size(void);

/**
 * @brief Get_HWC_TaskList_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取任务列表存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_TaskList_Phyaddr(void);

/**
 * @brief Get_HWC_TaskList_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取任务列表存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_TaskList_Size(void);

/**
 * @brief Get_HWC_TaskModel_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取任务模板起始地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_TaskModel_Phyaddr(void);

/**
 * @brief Get_HWC_TaskModel_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取任务模板存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_TaskModel_Size(void);

/**
 * @brief Get_HWC_TaskOutput_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取任务结果存放地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_TaskOutput_Phyaddr(void);

/**
 * @brief Get_HWC_TaskOutput_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取任务结果存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_TaskOutput_Size(void);

/**
 * @brief Get_HWC_USDF_Data_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取自定义协议发送数据存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_USDF_Data_Phyaddr(void);

/**
 * @brief Get_HWC_USDF_Data_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取自定义协议发送数据存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_USDF_Data_Size(void);

/**
 * @brief Get_HWC_VgaDisplay_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取Linux的VGA图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_VgaDisplay_Phyaddr(void);

/**
 * @brief Get_HWC_VgaDisplay_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取Linux的VGA图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_VgaDisplay_Size(void);

/**
 * @brief Get_HWC_Skeleton_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga计算轮廓匹配特征点坐标信息保存区
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Skeleton_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_Skeleton_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取fpga计算轮廓匹配特征点坐标信息存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Skeleton_Pic_Size(void);

/**
 * @brief Get_HWC_Defect_Rst_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/6/7
 * @note 获取fpga缺陷提取结果存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Defect_Rst_Phyaddr(void);

/**
 * @brief Get_HWC_Defect_Rst_Size
 * @return
 * @author Vincent
 * @date 2017/6/7
 * @note 获取fpga缺陷提取结果存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Defect_Rst_Size(void);

/**
 * @brief Get_HWC_Shading_Mono_Pic_Phyaddr
 * @return
 * @author Vincent
 * @date 2017/6/7
 * @note 获取fpga实时浓淡补正灰度图像存储地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Shading_Mono_Pic_Phyaddr(void);

/**
 * @brief Get_HWC_Shading_Mono_Pic_Size
 * @return
 * @author Vincent
 * @date 2017/6/7
 * @note 获取fpga实时浓淡补正灰度图像存储空间大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Shading_Mono_Pic_Size(void);

/**
 * @brief Get_HWC_Model_Base_Addr
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 获取任务模板保存起始地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Model_Base_Addr(void);

/**
 * @brief Get_HWC_Sample_Model_Max
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 粗模板的最大个数
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Sample_Model_Max(void);

/**
 * @brief Get_HWC_Sample_Model_Size
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 粗模板的大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Sample_Model_Size(void);

/**
 * @brief Get_HWC_Sample_Model_Base_Addr
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 粗模板的物理起始地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Sample_Model_Base_Addr(void);

/**
 * @brief Get_HWC_Sample_Model_End_Addr
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 粗模板的物理结束地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Sample_Model_End_Addr(void);

/**
 * @brief Get_HWC_Full_Model_Max
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 细模板的最大个数
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Full_Model_Max(void);

/**
 * @brief Get_HWC_Full_Model_Size
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 细模板的大小
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Full_Model_Size(void);

/**
 * @brief Get_HWC_Full_Model_Base_Addr
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 细模板的物理起始地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Full_Model_Base_Addr(void);

/**
 * @brief Get_HWC_Full_Model_End_Addr
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 细模板的物理结束地址
 */
DLLSHARED_EXPORT unsigned int Get_HWC_Full_Model_End_Addr(void);

/**
 * @brief HardwareAddrMmap
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 硬件相关地址指针映射
 */
DLLSHARED_EXPORT int HardwareAddrMmap(void);

/**
 * @brief GetTaskModelVirAddr
 * @return
 * @author Vincent
 * @date 2017/7/19
 * @note 获取任务模板存储地址指针
 */
DLLSHARED_EXPORT void * GetTaskModelVirAddr(void);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HARDWARECONFIG_H__ */
