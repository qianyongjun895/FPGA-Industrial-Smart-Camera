/**
  * @file  [EmmcHandle.h]
  * @brief  EMMC分区文件操作接口
  * @author  <AutumnX>
  * @date  <2017/05/18>
  * @version  <v1.0>
  * @note
  * 提供EMMC各分区文件操作接口
  */
#ifndef __EMMCHANDLE_H__
#define __EMMCHANDLE_H__

#define EMMC_P1 1
#define EMMC_P2 2
#define EMMC_P3 3
#define EMMC_P4 4

#define EMMC_P1_PATH "/mnt/emmc1/"
#define EMMC_P2_PATH "/mnt/emmc2/"
#define EMMC_P3_PATH "/mnt/emmc3/"
#define EMMC_P4_PATH "/mnt/emmc4/"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

// 以下接口不需要包含EMMC根目录，调用对应的分区接口即可
extern int emmc1_add_file (const char *fileName);
extern int emmc1_clean_file(const char *fileName);
extern int emmc1_create_directory (const char *dirName);
extern int emmc1_file_whether_exist (const char *fileName);
extern int emmc1_force_delete_files (const char *fileName);
extern int emmc1_get_file_size (const char *fileName, unsigned long *fileSize);
extern int emmc1_read_file (const char *fileName, void *buf, unsigned int *readLen, long *offset);
extern int emmc1_write_file (const char *fileName, const void *buf, unsigned int *writeLen, long *offset);
extern int emmc2_add_file (const char *fileName);
extern int emmc2_clean_file(const char *fileName);
extern int emmc2_create_directory (const char *dirName);
extern int emmc2_file_whether_exist (const char *fileName);
extern int emmc2_force_delete_files (const char *fileName);
extern int emmc2_get_file_size (const char *fileName, unsigned long *fileSize);
extern int emmc2_read_file (const char *fileName, void *buf, unsigned int *readLen, long *offset);
extern int emmc2_write_file (const char *fileName, const void *buf, unsigned int *writeLen, long *offset);
extern int emmc3_add_file (const char *fileName);
extern int emmc3_clean_file(const char *fileName);
extern int emmc3_create_directory (const char *dirName);
extern int emmc3_file_whether_exist (const char *fileName);
extern int emmc3_force_delete_files (const char *fileName);
extern int emmc3_get_file_size (const char *fileName, unsigned long *fileSize);
extern int emmc3_read_file (const char *fileName, void *buf, unsigned int *readLen, long *offset);
extern int emmc3_write_file (const char *fileName, const void *buf, unsigned int *writeLen, long *offset);
extern int emmc4_add_file (const char *fileName);
extern int emmc4_clean_file(const char *fileName);
extern int emmc4_create_directory (const char *dirName);
extern int emmc4_file_whether_exist (const char *fileName);
extern int emmc4_force_delete_files (const char *fileName);
extern int emmc4_get_file_size (const char *fileName, unsigned long *fileSize);
extern int emmc4_read_file (const char *fileName, void *buf, unsigned int *readLen, long *offset);
extern int emmc4_write_file (const char *fileName, const void *buf, unsigned int *writeLen, long *offset);

// 以下接口需要自行指定要操作的EMMC目录
extern int Emmc_Add_File (const char *fileName);
extern int Emmc_Clean_File (const char *fileName);
extern int Emmc_Create_Directory (const char *dirName);
extern int Emmc_File_Whether_Exist (const char *fileName);
extern int Emmc_Force_Delete_Files (const char *fileName);
extern int Emmc_Get_File_Size (const char *fileName, unsigned long *fileSize);
extern int Emmc_Read_File (const char *fileName, void *buf, unsigned int *readLen, long *offset);
extern int Emmc_Write_File (const char *fileName, const void *buf, unsigned int *writeLen, long *offset);
extern int Emmc_Move_File(const char *oldName, const char *newName);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __EMMCHANDLE_H__ */

