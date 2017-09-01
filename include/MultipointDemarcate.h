#ifndef __MULTIPOINTDEMARCATE_H__
#define __MULTIPOINTDEMARCATE_H__
#include "BaseStruct.h"

#define HOMO_CVT_I    0x1     ///输入POINT_I
#define HOMO_CVT_F    0x2     ///输入POINT_F
#define HOMO_CVT_MASK   0xff

#define HOMO_INPUT_VGA      0x100 ///输入像素点为VGA范围
#define HOMO_INPUT_REAL     0x200 ///输入像素点为真实图像坐标
#define HOMO_INPUT_SUB      0x300 ///输入像素点为亚像素坐标
#define HOMO_INPUT_MASK     0xff00

#define HOMO_CONFIG_MAX 128

#define CAMERA_INSTALL_FIX		0x0		///固定安装
#define CAMERA_INSTALL_MOVE		0x1		///相机安装在机械手上，随着机械手运动
#define CAMERA_INSTALL_AGV		0x2		///相机安装在固定于AGV小车上的机械手上面，由于小车每次移动到拍照位置不固定导致产生角度和位置偏移

#define PIC_ARM_DIR_SAME		0x0
#define PIC_ARM_DIR_REVERT		0x1
typedef struct {
    double img_x;
    double img_y;
    double true_x;
    double true_y;
} POINT_COUPLE;

typedef struct {
    double minU;
    double minV;
    double maxU;
    double maxV;
    double minX;
    double minY;
    double maxX;
    double maxY;
} RESIZE_PAM;

typedef struct {
	int install_mode;		/* 相机安装模式 */
	float origin_theta;		/* 取样时的坐标位置 */
	POINT_F zero;			/* 拍照位置坐标 */
	POINT_F r_pix_pos;		/* 3点找圆计算出来的旋转R轴像素坐标，保存为真实像素值 */
    RESIZE_PAM resizePam;
    double homography[3][3];
} HOMO_PARA;

#define MAX_HOMO_POINT_NUM 50
typedef struct{
    POINT_COUPLE pts[MAX_HOMO_POINT_NUM];
	POINT_F ccc_points[3];	/* 3点找圆的点，保存为真实像素值 */
	POINT_F c_center;		/* 3点找圆找到的圆心 */
    RESIZE_PAM resizePam;
    double homography[3][3];
    int numpt;
    int numpt_valid;
	int dir_revert;		///图像和机械手方向相同或相反
    int valid_flag;
    int trigger_mode;
	int install_mode;	///UI上配置安装模式
	float origin_theta; ///取样时的角度值
    unsigned char pts_mask[MAX_HOMO_POINT_NUM];
} HOMO_T;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief 保存多点标定参数到文件中
 * @param paramIndex 参数索引 范围[0,24]
 * @param pHomo 指针参数，传入多点标定参数
 * @return 0:成功 其它：失败
 * @author <AutumnX>
 * @note
 */
int HomoParamSaveToFile(unsigned int paramIndex, HOMO_T *pHomo);

/**
 * @brief 从文件中载入多点标定参数
 * @param paramIndex 参数索引 范围[0,24]
 * @param pHomo 指针参数，传出多点标定参数
 * @return 0:成功 其它：失败
 * @author <AutumnX>
 * @note
 */
int HomoParamLoadFromFile(unsigned int paramIndex, HOMO_T *pHomo);

/**
 * @brief 获取多点标定参数套数
 * @param
 * @return 多点标定参数套数
 * @author <AutumnX>
 * @note
 */
unsigned int GetHomoParamCount(void);

/**
 * @brief 删除多点标定参数
 * @param paramIndex 参数索引 范围[0,24]
 * @return 0:成功 其它：失败
 * @author <AutumnX>
 * @note
 */
int HomoParamDeleteProc(unsigned int paramIndex);


/**
 * @brief 多点标定参数计算转换
 * @param pHomo 指针参数，传入传出多点标定参数
 * @return 0:成功 其它：失败
 * @author <AutumnX>
 * @note
 * 调用该接口前，需先设置好对应的计算参数
 */
int Homo_Calc_Conver_Parameter(HOMO_T *pHomo);

/**
 * @brief 像素到物理的转换接口
 * @param homo_index:homograph参数索引
 * @param pixel_point:像素指针
 * @param phy_point:物理像素指针
 * @param homo_flag:转换参数组合标志
 * @return
 * @author <Terry>
 * @note
 */
void Homography_Convert(unsigned int homo_index, void *pPixel, void *pPhy, unsigned int homo_flag);

/**
 * @brief 多点标定参数初始化
 * @return
 * @author <AutumnX>
 * @note
 * 任务初始化时调用
 */
void DemarcateParamInit(void);

/**
 * @brief GetHomoParamName
 * @param paramIndex:参数索引
 * @return 对应索引的参数名
 * @note 返回对应索引的参数名
 */
char* GetHomoParamName(unsigned int paramIndex);

/**
 * @brief SetHomoParamName
 * @param paramIndex:参数索引
 * @param paramName:参数名
 * @return 0:成功 other:失败
 * @note 设置参数名字
 */
unsigned int SetHomoParamName(unsigned int paramIndex, const char* paramName);

/**
 * @brief 获取CAMERA_INSTALL_MOVE和CAMERA_INSTALL_AGV这两种模式下的原点信息
 * @param homo_index：索引号
 		  pZero：原点信息
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int HomoParaZeroPointPhyGet(unsigned int homo_index, POINT_F *pZero);

/**
 * @brief 获取相机的安装模式
 * @param homo_index：索引号
 		  pInstallMode：安装模式指针
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int HomoParaInstallModeGet(unsigned int homo_index, unsigned int *pInstallMode);

/**
 * @brief 获取相机原始角度
 * @param homo_index：索引号
 		  pOriginTheta：原始角度信息指针
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int HomoParaOriginThetaGet(unsigned int homo_index, float *pOriginTheta);

/**
 * @brief 获取CAMERA_INSTALL_MOVE和CAMERA_INSTALL_AGV这两种模式下的R轴像素坐标信息
 * @param homo_index：索引号
 		  pRotPoint：旋转轴像素坐标
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int HomoParaRotatePointPixGet(unsigned int homo_index, POINT_F *pRotPoint);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __MULTIPOINTDEMARCATE_H__ */
