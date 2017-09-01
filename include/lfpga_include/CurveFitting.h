#ifndef CURVEFITTING_H
#define CURVEFITTING_H

#include "define.h"
#include "AcceCommon.h"


/** Model(P39)曲线拟合模块寄存器 */
#define CURVE_FIT_CTRL_REG				0x220		///<  曲线拟合控制寄存器
#define CURVE_FIT_TIRGGER_MASK			0x1         ///<  曲线拟合触发信号
#define CURVE_FIT_TIRGGER_OFFSET        0
#define CURVE_FIT_MIN_XY_REG			0x1190		///<  x、y坐标的最小值
#define CURVE_FIT_MIN_X_MASK			0xffff		///<  x、y坐标的最小值x掩码
#define CURVE_FIT_MIN_X_OFFSET          0
#define CURVE_FIT_MIN_Y_MASK			0xffff0000	///<  x、y坐标的最小值y掩码
#define CURVE_FIT_MIN_Y_OFFSET          16
#define CURVE_FIT_MAX_XY_REG			0x1191		///<  x、y坐标的最大值
#define CURVE_FIT_MAX_X_MASK			0xffff		///<  x、y坐标的最大值x掩码
#define CURVE_FIT_MAX_X_OFFSET          0
#define CURVE_FIT_MAX_Y_MASK			0xffff0000  ///<  x、y坐标的最大值y掩码
#define CURVE_FIT_MAX_Y_OFFSET          06
#define CURVE_FIT_X1_REG				0x1192		///<  x1坐标累加和
#define CURVE_FIT_Y1_REG				0x1193		///<  y1坐标累加和
#define CURVE_FIT_X2_LOW_REG			0x1194		///<  x2坐标累加和下半部
#define CURVE_FIT_X2_HIGH_REG			0x1195		///<  x2坐标累加和上半部
#define CURVE_FIT_Y2_LOW_REG			0x1196		///<  y2坐标累加和下半部
#define CURVE_FIT_Y2_HIGH_REG			0x1197		///<  y2坐标累加和上半部
#define CURVE_FIT_X3_LOW_REG			0x1198		///<  x3坐标累加和下半部
#define CURVE_FIT_X3_HIGH_REG			0x1199		///<  x3坐标累加和上半部
#define CURVE_FIT_Y3_LOW_REG			0x119a		///<  y3坐标累加和下半部
#define CURVE_FIT_Y3_HIGH_REG			0x119b		///<  y3坐标累加和上半部
#define CURVE_FIT_X1Y1_LOW_REG			0x119c		///<  x1y1坐标累加和下半部
#define CURVE_FIT_X1Y1_HIGH_REG			0x119d		///<  x1y1坐标累加和上半部
#define CURVE_FIT_X1Y2_LOW_REG			0x119e		///<  x1y2坐标累加和下半部
#define CURVE_FIT_X1Y2_HIGH_REG			0x119f		///<  x1y2坐标累加和上半部
#define CURVE_FIT_X2Y1_LOW_REG			0x11b0		///<  x2y1坐标累加和下半部
#define CURVE_FIT_X2Y1_HIGH_REG			0x11b1		///<  x2y1坐标累加和上半部

typedef struct {
    unsigned int fitting_min_xy;	///<  x,y坐标的最小值,高16位为y最小值,低16位为x最小值
    unsigned int fitting_max_xy;	///<  x,y坐标的最大值 高16位为y最大值,低16位为x最大值
    unsigned int fitting_x1;        ///<  x坐标累加和
    unsigned int fitting_y1;        ///<  y坐标累加和
    unsigned int fitting_x2_low;	///<  x2坐标累加和 0x1195存放[47:32],0x1194存放[31:00]
    unsigned int fitting_x2_up;
    unsigned int fitting_y2_low;	///<  y2坐标累加和 0x1197存放[47:32],0x1196存放[31:00]
    unsigned int fitting_y2_up;
    unsigned int fitting_x3_low;	///<  x3坐标累加和 0x1199存放[63:32],0x1198存放[31:00]
    unsigned int fitting_x3_up;
    unsigned int fitting_y3_low;	///<  y3坐标累加和 0x119b存放[63:32],0x119a存放[31:00]
    unsigned int fitting_y3_up;
    unsigned int fitting_x1y1_low;	///<  xy乘积累加和 0x119d存放[47:32],0x119c存放[31:00]
    unsigned int fitting_x1y1_up;
    unsigned int fitting_x1y2_low;	///<  xy2乘积累加和 0x119f存放[63:32],0x119e存放[31:00]
    unsigned int fitting_x1y2_up;
    unsigned int fitting_x2y1_low;	///<  x2y乘积累加和 0x11b1存放[63:32],0x11b0存放[31:00]
    unsigned int fitting_x2y1_up;
}CURVE_FIT_RESULT;

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Curve_Fit_Model_Init
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块参数初始化
 */
DLLSHARED_EXPORT int Curve_Fit_Model_Init(unsigned int acce_index);

/**
 * @brief Curve_Fit_Model_Config
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块参数设置
 */
DLLSHARED_EXPORT int Curve_Fit_Model_Config(unsigned int acce_index);

/**
 * @brief Curve_Fit_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块输入源获取
 */
DLLSHARED_EXPORT inline int Curve_Fit_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Curve_Fit_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type: 输出类型
 * @param pContainer: 结果数据指针
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块数据结果获取
 */
DLLSHARED_EXPORT void Curve_Fit_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Curve_Fit_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块使能打开
 */
DLLSHARED_EXPORT inline void Curve_Fit_Model_Enable(void);

/**
 * @brief Curve_Fit_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块使能关闭
 */
DLLSHARED_EXPORT inline void Curve_Fit_Model_Disable(void);

/**
 * @brief Curve_Fit_Model_Write_DDR_On
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块写DDR使能打开
 */
DLLSHARED_EXPORT inline void Curve_Fit_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Curve_Fit_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块写DDR使能关闭
 */
DLLSHARED_EXPORT inline void Curve_Fit_Model_Write_DDR_Off(void);

/**
 * @brief Curve_Fit_Result_Get
 * @param pCurveFitRst
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块结果数据获取
 */
DLLSHARED_EXPORT void Curve_Fit_Result_Get(CURVE_FIT_RESULT *pCurveFitRst);

/**
 * @brief Curve_Fit_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块寄存器数据显示
 */
DLLSHARED_EXPORT void Curve_Fit_Model_Reg_Show(void);

/**
 * @brief Curve_Fit_Model_Reg_Show
 * @author Vincent
 * @date 2017/5/12
 * @note 曲线拟合模块寄存器数据显示
 */
DLLSHARED_EXPORT inline void Curve_Fit_Src_Sel(unsigned int acce_index, unsigned int acce_id);


#ifdef __cplusplus
}
#endif

#endif // CURVEFITTING_H
