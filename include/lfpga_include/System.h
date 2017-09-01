#ifndef SYSTEM_H
#define SYSTEM_H

#include "define.h"
#include "AcceCommon.h"

#define USER_STATUS_EDIT        0
#define USER_STATUS_RUN         1
#define USER_STATUS_SIMULATE    2


/** 系统通用 */
#define CMOS_START_Y_REG                0xb3        ///<  CMOS图像高度偏移地址设置寄存器
#define CMOS_START_Y_MASK               0xffff      ///<  CMOS图像高度偏移地址设置掩码
#define CMOS_START_Y_OFFSET             0
#define PIXEL_NUM_REG                   0x103       ///<  像素数设置寄存器
#define PIC_PIXEL_NUM_MASK              0xfff       ///<  每行图像像素个数设置掩码
#define PIC_PIXEL_NUM_OFFSET            0
#define PIC_LINE_NUM_MASK               0x7ff0000   ///<  每幅图像像素行数设置掩码
#define PIC_LINE_NUM_OFFSET             16
#define USER_STATUS_REG                 0x00a       ///<  0表示编辑状态，1表示运行状态
#define EDITED_STATUS_REG               0x00b       ///<  编辑状态寄存器
#define EDITED_STATUS_MASK              0x7f        ///<  编辑状态时填入当前编辑界面的标号，和模板编号保持一致，非模块编辑界面时为全1
#define EDITED_STATUS_OFFSET            0
#define SIMULAT_STATUS_MASK             0x80        ///<  仿真状态标号
#define SIMULAT_STATUS_OFFSET           7
#define VGA_MEM_VIDEO_ADDR              0xbf        ///<  VGA视频显示起始地址（FPGA读）0x19000000
#define VGA_CTRL_VIDEO_REG              0x010       ///<  视频显示控制寄存器
#define VGA_CTRL_RGB_BKG_MASK           0xffffff    ///<  底色的RGB数据掩码 R=[23:16], G=[15:8], B=[7:0]
#define VGA_CTRL_RGB_BKG_OFFSET         0
#define VGA_CTRL_MONO_EN_MASK           0x1000000   ///<  指定显示彩色还是黑白，1：黑白，0：彩色
#define VGA_CTRL_MONO_EN_OFFSET         24
#define VGA_CTRL_VIDEO_DIS_EN_MASK      0x2000000   ///<  使能视频显示功能 1:使能，0:禁止
#define VGA_CTRL_VIDEO_DIS_EN_OFFSET    25
#define VGA_CTRL_VIDEO_START_REG        0x011       ///<  视频显示起始坐标寄存器
#define VGA_CTRL_VIDEO_START_X_MASK     0xffff      ///<  视频显示的起始X坐标掩码
#define VGA_CTRL_VIDEO_START_X_OFFSET   0
#define VGA_CTRL_VIDEO_START_Y_MASK     0xffff0000  ///<  视频显示的起始Y坐标掩码
#define VGA_CTRL_VIDEO_START_Y_OFFSET   16

#define PIC_SIZE_REG                    0x1087      ///<  当前图像尺寸寄存器（CMOS或DDR裁图后的宽高）
#define PIC_WIDTH_MASK                  0xffff      ///<  当前图像的宽度
#define PIC_WIDTH_OFFSET                0
#define PIC_HEIGHT_MASK                 0xffff0000  ///<  当前图像的高度
#define PIC_HEIGHT_OFFSET               16
#define COORDINATE_OFFSET_REG           0x1088      ///<  当前图像的坐标偏移寄存器（CMOS或DDR裁图后的起始坐标）
#define COORDINATE_OFFSET_X_MASK        0xffff      ///<  当前图像的X坐标偏移
#define COORDINATE_OFFSET_X_OFFSET      0
#define COORDINATE_OFFSET_Y_MASK        0xffff0000  ///<  当前图像的Y坐标偏移
#define COORDINATE_OFFSET_Y_OFFSET      16


/** 各模块输出结果是否有效的状态、控制寄存器 */
#define FPGA_MODULE_OUTPUT_CLEAR_REG                0xfa        ///<  模块输出状态清零寄存器
#define FPGA_MODULE_OUTPUT_VALID_REG0               0x10f7      ///<  模块输出结果状态寄存器0，对应模块0到31
#define FPGA_MODULE_OUTPUT_VALID_REG1               0x10f8      ///<  模块输出结果状态寄存器1，对应模块32到63

/** CMOS_VGA MODEL */
#define CMOS_CTRL_RST_REG               0xb0            ///<  复位CMOS的寄存器
#define CMOS_CTRL_RST_MASK              0x1             ///<  复位CMOS寄存器到初始化状态的掩码
#define CMOS_CTRL_RST_OFFSET            0
#define WB_CTRL_AUTO_TRIG_REG           0xb1            ///<  自动白平衡计算，触发信号寄存器
#define WB_CTRL_AUTO_TRIG_MASK          0x1             ///<  自动白平衡计算，触发信号掩码
#define WB_CTRL_AUTO_TRIG_OFFSET        0
#define WB_CTRL_MANUAL_REG              0xb2            ///<  白平衡设置寄存器
#define WB_CTRL_MANUAL_RGAIN_I_MASK     0xffff          ///<  手动白平衡，Red通道增益设置掩码
#define WB_CTRL_MANUAL_RGAIN_I_OFFSET   0
#define WB_CTRL_MANUAL_BGAIN_I_MASK     0xffff0000      ///<  手动白平衡，blue通道增益设置掩码
#define WB_CTRL_MANUAL_BGAIN_I_OFFSET   16
#define WB_CTRL_AUTO_REG                0x1189          ///<  白平衡设置寄存器
#define WB_CTRL_AUTO_RGAIN_I_MASK       0xffff          ///<  手动白平衡，Red通道增益设置掩码
#define WB_CTRL_AUTO_RGAIN_I_OFFSET     0
#define WB_CTRL_AUTO_BGAIN_I_MASK       0xffff0000      ///<  手动白平衡，blue通道增益设置掩码
#define WB_CTRL_AUTO_BGAIN_I_OFFSET     16


#define MANUAL_WHITE_BALANCE    0       ///<  手动白平衡
#define AUTO_WHITE_BALANCE      1       ///<  自动白平衡

#ifdef __cplusplus
extern "C" {
#endif



/**
 * @brief System_Model_Param_Init
 * @param pSystem_cfg
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 系统模块参数初始化
 */
DLLSHARED_EXPORT u32 System_Model_Param_Init(SYSTEM_MODEL_CFG * pSystem_cfg);

/**
 * @brief System_Model_Param_Get
 * @param pSystem_cfg
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 系统模块参数获取
 */
DLLSHARED_EXPORT u32 System_Model_Param_Get(SYSTEM_MODEL_CFG * pSystem_cfg);

/**
 * @brief System_Model_Param_Set
 * @param pSystem_cfg
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 系统模块参数设置
 */
DLLSHARED_EXPORT u32 System_Model_Param_Set(SYSTEM_MODEL_CFG * pSystem_cfg);

/**
 * @brief Vga_XY_Edit_Status_Set
 * @param start_x
 * @param start_y
 * @param edited_status
 * @author Vincent
 * @date 2017/5/12
 * @note 图像显示起始XY与编辑状态设置
 */
DLLSHARED_EXPORT void Vga_XY_Edit_Status_Set(u32 start_x, u32 start_y, u32 edited_status);

/**
 * @brief White_Balance_Param_Set
 * @param type: 设置类型 0 手动 1 自动
 * @param r_gain：Red通道增益指针
 * @param b_gain：Blue通道增益指针
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 白平衡参数设置接口函数
 */
DLLSHARED_EXPORT u32 White_Balance_Param_Set(u32 type,u32 * r_gain,u32 * b_gain);

/**
 * @brief Set_CPT_Cmos_Start_Y_And_Height
 * @param start_y: 起始Y坐标
 * @param height: 图像高度
 * @param rotate_type: 旋转类型 0：无 1：水平 2：垂直 3：原点
 * @author Vincent
 * @date 2017/5/12
 * @note 设置图像采集模块CMOS采图时的Y起始地址与高度
 */
DLLSHARED_EXPORT void Set_CPT_Cmos_Start_Y_And_Height(u32 start_y, u32 height, u32 rotate_type);

/**
 * @brief Get_Cmos_Start_Y
 * @return 起始Y
 * @author Vincent
 * @date 2017/5/12
 * @note 获取CMOS裁图起始Y
 */
DLLSHARED_EXPORT unsigned int Get_Cmos_Start_Y(void);

/**
 * @brief Get_Cmos_Height
 * @return 像素行数
 * @author Vincent
 * @date 2017/5/12
 * @note 获取CMOS裁图后像素行数
 */
DLLSHARED_EXPORT unsigned int Get_Cmos_Height(void);

/**
 * @brief CMOS_CTRL_START_Y
 * @param num
 * @author Vincent
 * @date 2017/6/1
 * @note CMOS采集图像Y起始位置
 */
DLLSHARED_EXPORT void CMOS_CTRL_START_Y(u32 num);

/**
 * @brief SYS_PIC_LINE_PIXEL_NUM
 * @param height
 * @author Vincent
 * @date 2017/6/1
 * @note 每行像素数与图像总行数
 */
DLLSHARED_EXPORT void SYS_PIC_LINE_PIXEL_NUM(u32 height);

/**
 * @brief SET_SYSTEM_USER_STATUS
 * @param status
 * @author Vincent
 * @date 2017/6/1
 * @note 设置工作状态
 */
DLLSHARED_EXPORT void SET_SYSTEM_USER_STATUS(u32 status);

/**
 * @brief SET_SYSTEM_EDITED_STATUS
 * @param status
 * @author Vincent
 * @date 2017/6/1
 * @note 设置工作状态
 */
DLLSHARED_EXPORT void SET_SYSTEM_EDITED_STATUS(u32 status);

/**
 * @brief SET_SYSTEM_SIMULAT_STATUS
 * @param status
 * @author Vincent
 * @date 2017/7/21
 * @note 设置仿真状态
 */
DLLSHARED_EXPORT void SET_SYSTEM_SIMULAT_STATUS(u32 status);

/**
 * @brief GET_SYSTEM_SIMULAT_STATUS
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取仿真状态
 */
DLLSHARED_EXPORT u32 GET_SYSTEM_SIMULAT_STATUS(void);

/**
 * @brief SET_VGA_MEM_VIDEO_ADDR
 * @param num
 * @author Vincent
 * @date 2017/5/12
 * @note 设置视频显示地址
 */
DLLSHARED_EXPORT void SET_VGA_MEM_VIDEO_ADDR(u32 num);

/**
 * @brief VGA_CTRL_VIDEO_RGB_BKG
 * @param num
 * @author Vincent
 * @date 2017/5/12
 * @note 设置底色的RGB数据
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_RGB_BKG(u32 num);

/**
 * @brief VGA_CTRL_VIDEO_MONO
 * @author Vincent
 * @date 2017/5/12
 * @note 指定显示黑白图像
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_MONO(void);

/**
 * @brief VGA_CTRL_VIDEO_COLOR
 * @author Vincent
 * @date 2017/5/12
 * @note 指定显示彩色图像
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_COLOR(void);

/**
 * @brief VGA_CTRL_VIDEO_DIS_ENABLE
 * @author Vincent
 * @date 2017/5/12
 * @note 视频显示使能
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_DIS_ENABLE(void);

/**
 * @brief VGA_CTRL_VIDEO_DIS_DISABLE
 * @author Vincent
 * @date 2017/5/12
 * @note 视频显示不使能
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_DIS_DISABLE(void);

/**
 * @brief VGA_CTRL_VIDEO_START_X
 * @param num
 * @author Vincent
 * @date 2017/5/12
 * @note 指定视屏显示起始地址X
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_START_X(u32 num);

/**
 * @brief VGA_CTRL_VIDEO_START_Y
 * @param num
 * @author Vincent
 * @date 2017/5/12
 * @note 指定视频显示起始地址Y
 */
DLLSHARED_EXPORT void VGA_CTRL_VIDEO_START_Y(u32 num);

DLLSHARED_EXPORT void FPGA_STATUS_REG_CLEAR();

/**
 * @brief FPGA_STATUS_CHECK
 * @param acce_id: 需要查询模块的ID
 * @return 0: 成功 Other: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note FPGA模块状态监测
 */
DLLSHARED_EXPORT int FPGA_STATUS_CHECK(unsigned int acce_id);



/**
 * @brief CMOS_CTRL_AUTO_TRIG
 * @param num
 * @author Vincent
 * @date 2017/6/12
 * @note 自动白平衡计算，触发信号
 */
DLLSHARED_EXPORT void CMOS_CTRL_AUTO_TRIG(u32 num);

/**
 * @brief CMOS_CTRL_MANUAL_BGAIN
 * @param num
 * @author Vincent
 * @date 2017/6/12
 * @note 手动白平衡，blue通道增益设置
 */
DLLSHARED_EXPORT void CMOS_CTRL_MANUAL_BGAIN(u32 num);

/**
 * @brief CMOS_CTRL_MANUAL_RGAIN
 * @param num
 * @author Vincent
 * @date 2017/6/12
 * @note 手动白平衡，Red通道增益设置
 */
DLLSHARED_EXPORT void CMOS_CTRL_MANUAL_RGAIN(u32 num);

/**
 * @brief CMOS_CTRL_RD_AUTO_BGAIN
 * @return
 * @author Vincent
 * @date 2017/6/12
 * @note 自动白平衡，blue通道增益获取
 */
DLLSHARED_EXPORT u32 CMOS_CTRL_RD_AUTO_BGAIN(void);

/**
 * @brief CMOS_CTRL_RD_AUTO_RGAIN
 * @return
 * @author Vincent
 * @date 2017/6/12
 * @note 自动白平衡，Red通道增益获取
 */
DLLSHARED_EXPORT u32 CMOS_CTRL_RD_AUTO_RGAIN(void);

/**
 * @brief CMOS_CTRL_RST
 * @param num
 * @author Vincent
 * @date 2017/6/12
 * @note 复位CMOS寄存器到初始状态
 */
DLLSHARED_EXPORT void CMOS_CTRL_RST(u32 num);

/**
 * @brief Get_Current_Pic_Width
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取当前图像宽度
 */
DLLSHARED_EXPORT u32 Get_Current_Pic_Width(void);

/**
 * @brief Get_Current_Pic_Height
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取当前图像高度
 */
DLLSHARED_EXPORT u32 Get_Current_Pic_Height(void);

/**
 * @brief Get_Current_Coordinate_Offset_X
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取当前图像起始X坐标
 */
DLLSHARED_EXPORT u32 Get_Current_Coordinate_Offset_X(void);

/**
 * @brief Get_Current_Coordinate_Offset_Y
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取当前图像起始Y坐标
 */
DLLSHARED_EXPORT u32 Get_Current_Coordinate_Offset_Y(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_H
