#ifndef SKELETONEXTRACT_H
#define SKELETONEXTRACT_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P36)轮廓提取 */
#define MATCH_CTRL_REG                  0x280	///<  轮廓匹配寄存器
#define MATCH_CTRL_EN_MASK              0x1	    ///<  轮廓匹配使能掩码
#define MATCH_CTRL_EN_OFFSET            0
#define MATCH_CTRL_SRC_SEL_MASK         0x3f00	///<  输入图像源选择掩码
#define MATCH_CTRL_SRC_SEL_OFFSET       8
#define MATCH_CTRL_ZOOM_MODE_MASK       0x70000	///<  特征提取，缩放模式掩码
#define MATCH_CTRL_ZOOM_MODE_OFFSET     16
#define MATCH_MEM_POINT_ADDR_REG        0x283	///<  特征点，存储在DDR地址
#define MATCH_MEM_MASK_ADDR_REG         0x284	///<  角度幅度及MASK矩阵，存储在DDR地址
#define MATCH_MEM_ANGLE_ADDR_REG        0x285	///<  特征角度矩阵，存储在DDR地址寄存器
#define MATCH_SYS_POINT_NUM_REG         0x1080	///<  提取出来的特征点个数



#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Ske_Match_Model_Init
 * @param acce_index: 步骤索引号
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note 初始化边沿轮廓模块参数
 */
DLLSHARED_EXPORT int Ske_Match_Model_Init(u32 acce_index);

/**
 * @brief Ske_Match_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块参数设置
 */
DLLSHARED_EXPORT int Ske_Match_Model_Param_Set(u32 acce_index);

/**
 * @brief Ske_Match_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块输入源获取
 */
DLLSHARED_EXPORT inline int Ske_Match_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Ske_Match_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 输出数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块输出数据获取
 */
DLLSHARED_EXPORT void Ske_Match_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Ske_Match_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块使能关闭
 */
DLLSHARED_EXPORT inline void Ske_Match_Model_Disable(void);

/**
 * @brief Ske_Match_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块使能开启
 */
DLLSHARED_EXPORT inline void Ske_Match_Model_Enable(void);

/**
 * @brief Ske_Match_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void Ske_Match_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Ske_Match_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Ske_Match_Model_Write_DDR_Off(void);

/**
 * @brief Ske_Match_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块寄存器参数打印
 */
DLLSHARED_EXPORT void Ske_Match_Model_Reg_Show(void);

/**
 * @brief Ske_Match_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id: 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块输入源设置
 */

/**
 * @brief Ske_Match_Model_Src_Sel
 * @param acce_index: 步骤索引号
 * @param acce_id: 输入源模块ID
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块输入源设置
 */
DLLSHARED_EXPORT inline void Ske_Match_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);


/**
 * @brief Set_Skeleton_Enable
 * @param flag
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取模块使能函数
 */
DLLSHARED_EXPORT void Set_Skeleton_Enable(u32 flag);

/**
 * @brief Set_SKE_Feature_Angle_Save_Addr
 * @param addr
 * @author Vincent
 * @date 2017/5/12
 * @note 设置轮廓提取特征角度存放地址
 */
DLLSHARED_EXPORT void Set_SKE_Feature_Angle_Save_Addr(u32 addr);

/**
 * @brief Set_SKE_Src_Sel
 * @param imgSrc
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取输入源选择函数
 */
DLLSHARED_EXPORT void Set_SKE_Src_Sel(u32 imgSrc);

/**
 * @brief Set_SKE_Zoom_Mode
 * @param zoom_mode
 * @author Vincent
 * @date 2017/5/12
 * @note 轮廓提取缩放模式选择函数
 */
DLLSHARED_EXPORT void Set_SKE_Zoom_Mode(u32 zoom_mode);


/** 获取轮廓匹配特征点数量 */
DLLSHARED_EXPORT u32 GET_MATCH_POINT_NUM(void);

/** 轮廓匹配不使能 */
DLLSHARED_EXPORT void MATCH_CTRL_MATCH_DISABLE(void);

/** 轮廓匹配使能 */
DLLSHARED_EXPORT void MATCH_CTRL_MATCH_ENABLE(void);

/** 特征提取 输入图像源选择 */
DLLSHARED_EXPORT void MATCH_CTRL_SRC_SEL(u32 src);

/** 特征提取，缩放模式 0=640*480; 1=320*240; 2=160*120; */
DLLSHARED_EXPORT void MATCH_CTRL_ZOOM_MODE(u32 zoom_num);

/** 特征角度矩阵，存储在DDR地址 */
DLLSHARED_EXPORT void MATCH_MEM_ANGLE_ADDR(u32 angle_addr);

#ifdef __cplusplus
}
#endif

#endif // SKELETONEXTRACT_H
