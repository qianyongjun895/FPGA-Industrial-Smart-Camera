#ifndef TASKBASEIMAGESELECT_H
#define TASKBASEIMAGESELECT_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief task_step_select_base_image_set
 * @param step_index
 * @param image_name
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 设置任务步骤关联基准图片
 */
int task_step_select_base_image_set(unsigned int step_index, char *image_name);

/**
 * @brief task_step_select_base_image_get
 * @param step_index
 * @param image_name
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 获取任务步骤关联基准图片
 */
int task_step_select_base_image_get(unsigned int step_index, char *image_name);

/**
 * @brief task_step_del_update_select_base_image
 * @param del_step
 * @param step_cnt
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 删除任务更新选择的基准图片列表
 */
int task_step_del_update_select_base_image(unsigned int del_step, unsigned int step_cnt);

/**
 * @brief task_step_add_update_select_base_image
 * @param add_step
 * @param step_cnt
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 删除任务更新选择的基准图片列表
 */
int task_step_add_update_select_base_image(unsigned int add_step, unsigned int step_cnt);

/**
 * @brief task_clean_update_select_base_image
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 清空任务更新选择的基准图片列表
 */
int task_clean_update_select_base_image(void);
/**
 * @brief base_image_cfg_file_save
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 保存任务步骤关联的基准图片的配置
 */
int base_image_cfg_file_save(void);

/**
 * @brief base_image_cfg_file_load
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 加载任务步骤关联的基准图片的配置
 */
int base_image_cfg_file_load(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // TASKBASEIMAGESELECT_H
