#ifndef HARDWARE_COMMON_H
#define HARDWARE_COMMON_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "cmos_common.h"

#define RAM_TYPE_512M               0x1
#define RAM_TYPE_1GB                0x2

#define TASK_OUTPUT_PHY_SIZE        0x100000
#define TASK_MODEL_TOTAL_SIZE       0x6400000

/* For skeleton FPGA calculate temp result */
#define SKELETON_FPGA_CALC_SIZE     0x200000 /* 2M */


/********** 相机硬件配置结构体 **********/
typedef struct
{
    unsigned int RAM_config;                    ///< 内存配置
    unsigned int Emio_Phyaddr;                  ///< EMIO地址

    unsigned int FrameBuffer_Phyaddr;           ///< Linux的framebuffer
    unsigned int FrameBuffer_Size;
    unsigned int Accelerator_Phyaddr;           ///< 预处理参数存放地址
    unsigned int Accelerator_Size;
    unsigned int TaskList_Phyaddr;              ///< 任务列表地址
    unsigned int TaskList_Size;
    unsigned int TaskModel_Phyaddr;             ///< 任务模板起始地址
    unsigned int TaskModel_Size;
    unsigned int TaskOutput_Phyaddr;            ///< 任务结果存放地址
    unsigned int TaskOutput_Size;
	unsigned int TaskGData_Phyaddr;				///< GData存放地址
	unsigned int TaskGData_Size;		
    unsigned int USDF_Data_Phyaddr;             ///< 自定义协议发送数据地址
    unsigned int USDF_Data_Size;
    unsigned int Modbus_Phyaddr;                ///< MODBUS数据地址
    unsigned int Modbus_Size;
    unsigned int Intercom_Modbus_Phyaddr;       ///< 内部通信MODBUS数据地址
    unsigned int Intercom_Modbus_Size;
    unsigned int plc_Phyaddr;                   ///< plc数据地址
    unsigned int plc_Size;

    /**  @brief  加速器模块地址 Start  */
    unsigned int CaptColor_Pic_Phyaddr;         ///< CMOS抓图彩色图像保存区域
    unsigned int CaptColor_Pic_Size;
    unsigned int CaptMono_Pic_Phyaddr;          ///< CMOS抓图黑白图像保存区域
    unsigned int CaptMono_Pic_Size;

    unsigned int SimiColor_Pic_Phyaddr;         ///< 仿真模式下彩色图像加载区域
    unsigned int SimiColor_Pic_Size;
    unsigned int SimiMono_Pic_Phyaddr;          ///< 仿真模式下黑白图像加载区域
    unsigned int SimiMono_Pic_Size;

    unsigned int PreProc_Pic_Phyaddr;           ///< 预处理图像保存区域
    unsigned int PreProc_Pic_Size;

    unsigned int VgaDisplay_Phyaddr;            ///< Linux的VGA图像存储地址
    unsigned int VgaDisplay_Size;

    unsigned int Binary_Area_Phyaddr;           ///< 二值化输出空间
    unsigned int Binary_Area_Size;

    unsigned int SelectColor_Pic_Phyaddr;       ///< 区域筛选彩色图像保存空间
    unsigned int SelectColor_Pic_Size;

    unsigned int SelectMono_Pic_Phyaddr;        ///< 区域筛选黑白图像保存空间
    unsigned int SelectMono_Pic_Size;

    unsigned int ColorDraw_Rst_Phyaddr;         ///< 颜色抽取结果保存空间
    unsigned int ColorDraw_Rst_Size;

    unsigned int Skeleton_Pic_Phyaddr;          ///< fpga计算轮廓匹配特征点坐标信息保存区
    unsigned int Skeleton_Pic_Size;

    unsigned int EdgePoints_Phyaddr;            ///< fpga计算边沿点信息保存区
    unsigned int EdgePoints_Size;

    unsigned int EdgePoints_Standby_Phyaddr;    ///< fpga计算边沿点信息临时备份区
    unsigned int EdgePoints_Standby_Size;

    unsigned int EpsSelect_Rst_Phyaddr;         ///< fpga边沿筛选结果保存空间
    unsigned int EpsSelect_Rst_Size;

    unsigned int ConnectDomain_Rst_Phyaddr;     ///< fpga计算连通域结果保存空间
    unsigned int ConnectDomain_Rst_Size;

    unsigned int Edge_Pic_Phyaddr;              ///< fpga边沿图像存储地址
    unsigned int Edge_Pic_Size;

    unsigned int Defect_Rst_Phyaddr;            ///< fpga缺陷提取结果存储地址
    unsigned int Defect_Rst_Size;

    unsigned int Shading_Mono_Pic_Phyaddr;      ///< fpga实时浓淡补正灰度图像存储地址
    unsigned int Shading_Mono_Pic_Size;
    /**  @brief  加速器模块地址 End  */

    unsigned int CaptDdrA_Pic_Phyaddr;          ///< CPT模块DDRA图像地址来源

    /**  @brief  task model memory information */
    unsigned int model_base_addr;               ///< 任务模板保存起始地址
    unsigned int sample_model_max;              ///< 粗模板的最大个数
    unsigned int sample_model_size;             ///< 粗模板的大小
    unsigned int sample_model_base_addr;        ///< 粗模板的物理起始地址
    unsigned int sample_model_end_addr;         ///< 粗模板的物理结束地址
    unsigned int full_model_max;                ///< 细模板的最大个数
    unsigned int full_model_size;               ///< 细模板的大小
    unsigned int full_model_base_addr;          ///< 细模板的物理起始地址
    unsigned int full_model_end_addr;           ///< 细模板的物理结束地址

}HARDWARE_CONFIG;


#endif // HARDWARE_COMMON_H
