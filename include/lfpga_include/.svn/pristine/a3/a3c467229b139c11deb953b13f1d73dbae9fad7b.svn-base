#ifndef LINK_H
#define LINK_H

#include "define.h"
#include "AcceCommon.h"

#define POWER2_30	1073741824
#define POWER2_32	4294967296


/** Model(P40)连通域 */
#define LINK_CTRL_REG				    0x278   	///<  连通域寄存器
#define LINK_CTRL_EN_MASK	            0x1         ///<  连通域模块使能掩码
#define LINK_CTRL_EN_OFFSET             0
#define LINK_CTRL_SRC_SEL_MASK	        0x3f00	    ///<  输入图像源选择掩码
#define LINK_CTRL_SRC_SEL_OFFSET	    8
#define LINK_DATA_WR_ADDR_REG		    0x279		///<  连通域结果写入DDR地址
#define LINK_RESULT_NUM_REG		        0x1163      ///<  连通域数量
#define LINK_RESULT_NUM_MASK			0xfff
#define LINK_RESULT_NUM_OFFSET			0
#define LINK_RESULT_NUM_ERR_MASK		0x80000000
#define LINK_RESULT_NUM_ERR_OFFSET      28

#define LINK_RST_MEM_SIZE				84
#define LINK_NUM_MAX					1000

typedef struct {
    unsigned int pixel_num;				///< 连通域内像素数量
    unsigned short x_max;				///< 连通域最右位置
    unsigned short x_min;				///< 连通域最左位置
    unsigned short y_max;				///< 连通域最下位置
    unsigned short y_min;				///< 连通域最上位置
    unsigned int x_sum_up;				///< x累加和上半部
    unsigned int x_sum_down;			///< x累加和下半部
    unsigned int y_sum_up;				///< y累加和上半部
    unsigned int y_sum_down;			///< y累加和下半部
    unsigned int x2_sum_up;				///< x平方累加和上半部
    unsigned int x2_sum_down;			///< x平方累加和下半部
    unsigned int y2_sum_up;				///< y平方累加和上半部
    unsigned int y2_sum_down;			///< y平方累加和下半部
    unsigned int xy_sum_up;				///< xy累加和上半部
    unsigned int xy_sum_down;			///< xy累加和下半部
    unsigned int x2y_sum_up;			///< x2y累加和上半部
    unsigned int x2y_sum_down;			///< x2y累加和下半部
    unsigned int xy2_sum_up;			///< xy2累加和上半部
    unsigned int xy2_sum_down;			///< xy2累加和下半部
    unsigned int x3_sum_up;				///< x3累加和上半部
    unsigned int x3_sum_down;			///< x3累加和下半部
    unsigned int y3_sum_up;				///< y3累加和上半部
    unsigned int y3_sum_down;			///< y3累加和下半部
}LINK_FPGA_RESULT;

typedef struct {
    double area;
    double x_sum;
    double y_sum;
    double x2_sum;
    double y2_sum;
    double xy_sum;
    double x2y_sum;
    double xy2_sum;
    double x3_sum;
    double y3_sum;
}LINK_RESULT;
typedef struct {
    unsigned int pixel_num;				///< 连通域像素数量
    POINT_F center_pixel;               ///< 中心点像素坐标
    POINT_F center_phy;                 ///< 中心点物理坐标
}LINK_SINGLE_INFO;

typedef struct {
    unsigned int total_pixel_num;		///< 所有连通域像素数量
    unsigned int link_count;			///< 连通域数量
    LINK_SINGLE_INFO link[LINK_NUM_MAX];///< 单个连通域信息
}LINK_AREA_INFO;


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Link_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化连通域模块参数
 */
DLLSHARED_EXPORT int Link_Model_Init(u32 acce_index);

/**
 * @brief Link_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域参数设置函数
 */
DLLSHARED_EXPORT int Link_Model_Param_Set(u32 acce_index);

/**
 * @brief Link_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块输入源获取
 */
DLLSHARED_EXPORT inline int Link_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Link_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块输入源获取
 */
DLLSHARED_EXPORT void Link_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Link_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块使能关闭
 */
DLLSHARED_EXPORT inline void Link_Model_Disable(void);

/**
 * @brief Link_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块使能开启
 */
DLLSHARED_EXPORT inline void Link_Model_Enable(void);

/**
 * @brief Link_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块写DDR使能开启
 */
DLLSHARED_EXPORT inline void Link_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Link_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Link_Model_Write_DDR_Off(void);

/**
 * @brief Link_Model_Num_Get
 * @param pLinkCnt: 连通域个数指针
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域个数获取
 */
DLLSHARED_EXPORT int Link_Model_Num_Get(unsigned int *pLinkCnt);

/**
 * @brief Link_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块寄存器数据打印
 */
DLLSHARED_EXPORT void Link_Model_Reg_Show(void);

/**
 * @brief Link_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id
 * @author Vincent
 * @date 2017/5/12
 * @note 连通域模块输入源设置
 */
DLLSHARED_EXPORT inline void Link_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief Set_Link_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 设置连通域使能状态
 */
DLLSHARED_EXPORT void Set_Link_Enable(u32 flag);

/**
 * @brief Set_Link_Src_Sel
 * @param imgSrc
 * @author Vincent
 * @date 2017/5/12
 * @note 设置连通域图像源
 */
DLLSHARED_EXPORT void Set_Link_Src_Sel(u32 imgSrc);

/**
 * @brief Set_Link_Wr_Addr
 * @param imgSrc
 * @author Vincent
 * @date 2017/5/12
 * @note 设置连通域写DDR地址
 */
DLLSHARED_EXPORT void Set_Link_Wr_Addr(u32 imgSrc);


#ifdef __cplusplus
}
#endif


#endif // LINK_H
