#ifndef SIDECHOOSE_H
#define SIDECHOOSE_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P38)边沿筛选模块寄存器 */
#define SIDE_CHOOSE_CTRL_REG                    0x200
#define SIDE_CHOOSE_LINE_PIXEL_START_MASK       0x1         ///<  直线像素筛选触发信号，发1时触发一次直线像素筛选过程
#define SIDE_CHOOSE_LINE_PIXEL_START_OFFSET     0
#define SIDE_CHOOSE_CIR_PIXEL_START_MASK        0x2         ///<  环形像素筛选触发信号，发1时触发一次环形像素筛选过程
#define SIDE_CHOOSE_CIR_PIXEL_START_OFFSET      1
#define SIDE_CHOOSE_ANGLE_EN_MASK               0x4         ///<  是否选择角度筛选1为使能角度筛选，0为不使能
#define SIDE_CHOOSE_ANGLE_EN_OFFSET             2
#define SIDE_CHOOSE_W2B_EN_MASK                 0x8         ///<  1：白到黑，0：黑到白
#define SIDE_CHOOSE_W2B_EN_OFFSET               3
#define SIDE_CHOOSE_SRC_POINT_NUM_REG           0x201
#define SIDE_CHOOSE_SRC_POINT_NUM_MASK          0x7fffff    ///<  需要从DDR读出的像素点总数
#define SIDE_CHOOSE_SRC_POINT_NUM_OFFSET        0
#define SIDE_CHOOSE_POINT_RD_ADDR_REG           0x202       ///<  需要从DDR读出的像素点的存储起始地址
#define SIDE_CHOOSE_ANGLE_TH_CRT_REG            0x204
#define SIDE_CHOOSE_ANGLE_TH_MASK               0xffff      ///<  角度筛选的阈值
#define SIDE_CHOOSE_ANGLE_TH_OFFSET             0
#define SIDE_CHOOSE_ANGLE_RST_MASK              0xffff0000  ///<  直线的角度信息
#define SIDE_CHOOSE_ANGLE_RST_OFFSET            16
#define SIDE_CHOOSE_RING_CENTER_REG             0x205
#define SIDE_CHOOSE_RING_CENTER_X_MASK          0xffff      ///<  环形的圆心X坐标
#define SIDE_CHOOSE_RING_CENTER_X_OFFSET        0
#define SIDE_CHOOSE_RING_CENTER_Y_MASK          0xffff0000  ///<  环形的圆心Y坐标
#define SIDE_CHOOSE_RING_CENTER_Y_OFFSET        16
#define SIDE_CHOOSE_RING_RADIUS_MIN_REG         0x206       ///<  环形筛选距离的最小值
#define SIDE_CHOOSE_RING_RADIUS_MAX_REG         0x207       ///<  环形筛选距离的最大值
#define SIDE_CHOOSE_RING_DIST_REG               0x208       ///<  环形筛选距离的实际值
#define SIDE_CHOOSE_LINE_DIST_REG               0x209       ///<  直线筛选距离的实际值
#define SIDE_CHOOSE_LINE_XY_REG                 0x20a
#define SIDE_CHOOSE_LINE_X_MASK                 0xffff      ///<  直线的X坐标点
#define SIDE_CHOOSE_LINE_X_OFFSET               0
#define SIDE_CHOOSE_LINE_Y_MASK                 0xffff0000  ///<  直线的Y坐标点
#define SIDE_CHOOSE_LINE_Y_OFFSET               16
#define SIDE_CHOOSE_LINE_COS_REG                0x20b       ///<  直线角度的cos值
#define SIDE_CHOOSE_LINE_SIN_REG                0x20c       ///<  直线角度的sin值
#define SIDE_CHOOSE_POINT_WR_ADDR_REG           0x20d       ///<  筛选之后边缘点存放在DDR的起始地址
#define SIDE_CHOOSE_RST_POINT_NUM_REG           0x118a      ///<  筛选出的边缘点数量
#define SIDE_CHOOSE_DELT_DIST_SUM_REG           0x118b      ///<  统计出的距离偏差累加和


typedef struct {
    int angle_check_th;					///< 角度检查门限
    int angle_crt;						///< 当前角度
    unsigned int dir_check;				///< 0:w2b, 1:b2w
    unsigned int point_num_th;			///< 待筛选点门限
    unsigned int point_rd_num;			///< 待筛选的点数
    unsigned int point_rd_addr;			///< 待筛选的点源地址
    unsigned int point_wr_addr;			///< 筛选出的点保存地址
    unsigned int x;						///< 拟合模块计算出来的mean_x，亚像素
    unsigned int y;						///< 拟合模块计算出来的mean_y，亚像素
    int cos;							///< 拟合模块计算出来的cos值
    int sin;							///< 拟合模块计算出来的sin值
    unsigned int dist_th;				///< 距离门限，亚像素
}SIDE_CHOOSE_LINE_COND;

typedef struct {
    unsigned int dir_check;				///< 0:w2b, 1:b2w
    unsigned int point_rd_num;			///< 待筛选的点数
    unsigned int point_rd_addr;			///< 待筛选的点源地址
    unsigned int point_wr_addr;			///< 筛选出的点保存地址
    unsigned int x;						///< 圆心X坐标，亚像素
    unsigned int y;						///< 圆心Y坐标，亚像素
    unsigned int min_radius_square;		///< 内环半径平方
    unsigned int max_radius_square;		///< 外环半径平方
    unsigned int dist_th;				///< 距离门限，亚像素
}SIDE_CHOOSE_CIRCLE_COND;


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Side_Choose_Model_Init
 * @param acce_index: 步骤索引号: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化边缘筛选模块参数
 */
DLLSHARED_EXPORT int Side_Choose_Model_Init(u32 acce_index);

/**
 * @brief Side_Choose_Model_Line_Config
 * @param pLineChooseCond
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块直线筛选模式参数配置
 */
DLLSHARED_EXPORT void Side_Choose_Model_Line_Config(SIDE_CHOOSE_LINE_COND *pLineChooseCond);

/**
 * @brief Side_Choose_Model_Circle_Config
 * @param pCircleChooseCond
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块圆形筛选模式参数配置
 */
DLLSHARED_EXPORT void Side_Choose_Model_Circle_Config(SIDE_CHOOSE_CIRCLE_COND *pCircleChooseCond);

/**
 * @brief Side_Choose_Model_Param_Set
 * @param acce_index: 步骤索引号: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 边缘筛选模块参数设置函数
 */
DLLSHARED_EXPORT int Side_Choose_Model_Param_Set(u32 acce_index);

/**
 * @brief Side_Choose_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块输入源获取
 */
DLLSHARED_EXPORT inline int Side_Choose_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Side_Choose_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type
 * @param pContainer
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块输出数据获取
 */
DLLSHARED_EXPORT void Side_Choose_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Side_Choose_Model_Result_Point_Num_Get
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模筛选出的边沿点个数获取
 */
DLLSHARED_EXPORT unsigned int Side_Choose_Model_Result_Point_Num_Get(void);

/**
 * @brief Side_Choose_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块使能关闭
 */
DLLSHARED_EXPORT inline void Side_Choose_Model_Disable(void);

/**
 * @brief Side_Choose_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块使能打开
 */
DLLSHARED_EXPORT inline void Side_Choose_Model_Enable(void);

/**
 * @brief Side_Choose_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void Side_Choose_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Side_Choose_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Side_Choose_Model_Write_DDR_Off(void);

/**
 * @brief Side_Choose_Model_Line_Pixel_Start
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块直线筛选开始信号
 */
DLLSHARED_EXPORT void Side_Choose_Model_Line_Pixel_Start(void);

/**
 * @brief Side_Choose_Model_Circle_Pixel_Start
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块圆形筛选开始信号
 */
DLLSHARED_EXPORT void Side_Choose_Model_Circle_Pixel_Start(void);

/**
 * @brief Side_Choose_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块寄存器参数打印
 */
DLLSHARED_EXPORT void Side_Choose_Model_Reg_Show(void);

/**
 * @brief Side_Choose_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 边沿筛选模块输入源设置
 */
DLLSHARED_EXPORT inline void Side_Choose_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

DLLSHARED_EXPORT void Set_Side_Choose_Addr(u32 addr);
DLLSHARED_EXPORT void Set_Side_Choose_Angle_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Side_Choose_Angle_Th(u32 num);
DLLSHARED_EXPORT void Set_Side_Choose_Point_Wr_Addr(u32 addr);
DLLSHARED_EXPORT void Set_Side_Choose_Ring_Max_Radius(u32 num);
DLLSHARED_EXPORT void Set_Side_Choose_Ring_Min_Radius(u32 num);
DLLSHARED_EXPORT void Set_Side_Choose_Ring_X(u32 num);
DLLSHARED_EXPORT void Set_Side_Choose_Ring_Y(u32 num);
DLLSHARED_EXPORT void Set_Side_Choose_W2B_Enable(u32 flag);


#ifdef __cplusplus
}
#endif

#endif // SIDECHOOSE_H
