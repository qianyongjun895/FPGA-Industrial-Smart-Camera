#ifndef IMAGESCAN_H
#define IMAGESCAN_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "ImageManageGlobal.h"

typedef enum{
    IMAGE_SCAN_ONE_ROUND = 0,
    IMAGE_SCAN_NEXT_PIC,
    IMAGE_SCAN_PRE_PIC,
    IMAGE_SCAN_FIRST_PIC,
    IMAGE_SCAN_LAST_PIC
}IMAGE_SCAN_TYPE;

/**
 * @brief image_scan_init
 * @param dir_type
 * @author pml
 * @date 2017/5/12
 * @note 浏览图片初始化
 */
void image_scan_init(IMAGE_DIR_TYPE dir_type);

/**
 * @brief image_scan_pic_load
 * @param scan_type
 * @author pml
 * @date 2017/5/12
 * @note 浏览图片的加载
 */
void image_scan_pic_load(unsigned int scan_type);

/**
 * @brief image_scan_cur_pic_name_get
 * @param file_name
 * @author pml
 * @date 2017/5/12
 * @note 获取当前图片名称
 */
void image_scan_cur_pic_name_get(char *file_name);

/**
 * @brief image_scan_cur_pic_del
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 删除当前浏览的图片
 */
int image_scan_cur_pic_del(void);

/**
 * @brief image_scan_dir_type_get
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 浏览图片目录类型
 */
unsigned int image_scan_dir_type_get(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // IMAGESCAN_H
