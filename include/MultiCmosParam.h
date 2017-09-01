#ifndef __MULTICMOSPARAM_H__
#define __MULTICMOSPARAM_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define CMOS_PARAM_INVALID		0
#define CMOS_PARAM_VALID		1
#define CMOS_PARAM_NUM_MAX		64
#define CMOS_PARAM_FILE_PATH 	"task/tmp/MultiCmosParam/CmosParam.bin"
#define CMOS_PARAM_DIR_PATH		"task/tmp/MultiCmosParam"

typedef struct {
	unsigned int param_valid_flag;
	unsigned int exposure_ms;
	unsigned int exposure_us;
	unsigned int gain;
	unsigned int flip_mode;
	unsigned short clip_startY;
	unsigned short clip_height;
} M_CMOS_PARAM;

/**
 * @brief 全局数据初始化，UI启动的时候调用该函数
 * @param
 * @return 0:成功，other:失败
 * @author <Terry>
 * @note
 */
int Multi_Cmos_Param_Init(void);

/**
 * @brief 保存数据到指定位置
 * @param index：索引号
 		  pCmosParam：输入参数指针
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int M_Cmos_Param_Set(unsigned int index, M_CMOS_PARAM *pCmosParam);

/**
 * @brief 获取指定的数据
 * @param index：索引号
 		  pCmosParam：输入参数指针
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int M_Cmos_Param_Get(unsigned int index, M_CMOS_PARAM *pCmosParam);

/**
 * @brief 保存所有的CMOS配置的数据
 * @param 
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int M_Cmos_Param_Save(void);

/**
 * @brief 重新加载任务CMOS配置数据，切换任务的时候用
 * @param 
 * @return 0：成功，other：失败
 * @author <Terry>
 * @note
 */
int M_Cmos_Param_ReLoad(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __MULTICMOSPARAM_H__ */
