#ifndef IMAGESIMULATIONGLOBAL_H
#define IMAGESIMULATIONGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "ImageManageGlobal.h"


typedef enum{
    SIMULATION_RUN_ONE_ROUND = 0,
    SIMULATION_RUN_NEXT_PIC,
    SIMULATION_RUN_PRE_PIC,
    SIMULATION_RUN_FIRST_PIC,
    SIMULATION_RUN_LAST_PIC
}SIMULATION_RUN_TYPE;

/**
 * @brief simulation_run_init
 * @param dir_type
 * @author pml
 * @date 2017/5/12
 * @note 仿真初始化，选择目录的时候调用
 */
void simulation_run_init(IMAGE_DIR_TYPE dir_type);

/**
 * @brief simulation_run_load_pic
 * @param simulation_type
 * @author pml
 * @date 2017/5/12
 * @note 仿真运行加载图片到内存
 */
void simulation_run_load_pic(SIMULATION_RUN_TYPE simulation_type);

/**
 * @brief simulation_cur_pic_del
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 删除当前加载的图片
 */
int simulation_cur_pic_del(void);

/**
 * @brief simulation_dir_type_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取仿真目录类型
 */
unsigned int simulation_dir_type_get(void);


/**
 * @brief simulation_cur_pic_name_get
 * @param file_name
 * @author pml
 * @date 2017/5/12
 * @note 获取当前仿真图片名称
 */
void simulation_cur_pic_name_get(char *file_name);

/**
 * @brief simulation_pic_load_over_get
 * @return 结束标志：0：结束，1：未结束
 * @author pml
 * @date 2017/5/12
 * @note 图片运行加载结束
 */
unsigned int simulation_pic_load_over_get(void);

/**
 * @brief simulation_pic_load_over_get
 * @return 判断是否为第一张图片或最后一张：0：无，1：第一张，2：最后一张
 * @author pml
 * @date 2017/5/12
 * @note 图片运行加载结束
 */

unsigned int simulation_pic_first_or_last_flag_get(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // IMAGESIMULATIONGLOBAL_H
