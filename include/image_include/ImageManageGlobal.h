#ifndef IMAGEMANAGEGLOBAL_H
#define IMAGEMANAGEGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/** @brief 图片名称最大长度 */
#define IMAGE_FILE_NAME_SIZE_MAX 50

/** @brief 图片路径类型，保存在/mnt/emmc3 */
typedef enum{
    IMAGE_SAVE_DIR = 0, ///< 保存在/mnt/emmc3/ImageSave
    BASE_IMAGE_DIR, ///< 保存在/mnt/emmc3/BaseImage
    OK_IMAGE_DIR,///< 保存在/mnt/emmc3/OKImage
    NG_IMAGE_DIR,///< 保存在/mnt/emmc3/FailedImage
    IMAGE_DIR_TYPE_MAX
}IMAGE_DIR_TYPE;

/**
 * @brief image_save_to_file
 * @param image_dir_type
 * @param image_name
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 图片保存
 */
int image_save_to_file(IMAGE_DIR_TYPE image_dir_type, char *image_name);

/**
 * @brief image_save_to_default_file_name
 * @param image_dir_type
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 图片文件名称默认以时间命名
 */
int image_save_to_default_file_name(IMAGE_DIR_TYPE image_dir_type);


/**
 * @brief image_load_to_mem
 * @param image_dir_type
 * @param image_name
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 图片保存加载到内存
 */
int image_load_to_mem(IMAGE_DIR_TYPE image_dir_type, char *image_name);

/**
 * @brief image_file_delete
 * @param image_dir_type
 * @param image_name
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 图片文件删除
 */
int image_file_delete(IMAGE_DIR_TYPE image_dir_type, char *image_name);

/**
 * @brief image_file_clean
 * @param image_dir_type
 * @return 0:失败，1：成功
 * @author pml
 * @date 2017/5/12
 * @note 清空指定目录下的所有图片文件
 */
int image_file_clean(IMAGE_DIR_TYPE image_dir_type);

/**
 * @brief image_dir_all_file_name_get
 * @param image_dir_type
 * @param file_name
 * @return 目录下的文件数
 * @author pml
 * @date 2017/5/12
 * @note 获取图片保存目录下的所有文件名
 */
int image_dir_all_file_name_get(IMAGE_DIR_TYPE image_dir_type, char file_name[][IMAGE_FILE_NAME_SIZE_MAX]);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // IMAGEMANAGEGLOBAL_H
