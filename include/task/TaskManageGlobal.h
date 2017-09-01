/**
  * @file  [TaskManageGlobal.h]
  * @brief  任务管理模块
  * @author  <AutumnX>
  * @date  <2017/5/17>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef __TASKMANAGE_H__
#define __TASKMANAGE_H__

/** @brief 任务内存分区大小 */
#define TASK_MEMORY_PARTITION_SIZE 0x2000 // 8K
#define ACCE_MODEL_STEP_SIZE       0x4000 // 16K

/** @brief 脚本类型枚举 */
typedef enum {
    SHELL_SCRIPT=0, ///< shell 脚本
    LUA_SCRIPT,     ///< lua 脚本
    PYTHON2_SCRIPT, ///< python2.x 脚本
    PYTHON3_SCRIPT, ///< python3.x 脚本
    SCRIPT_TYPE_END ///< 脚本类型枚举结束
} SCRIPT_FILE_TYPE;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief   任务管理模块初始化函数
 * @param   任务内存起始虚地址
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note    使用本模块前，请先调用此初始化函数
 */
int TaskManageModulesInit(unsigned int taskVirtualAddr);

/**
 * @brief   加速器头指针初始化
 * @param   acceVirtualAddr 加速器起始地址
 * @return
 * @author  <AutumnX>
 * @note
 */
void AcceHeadPointerInit(void *pAcceVirtualAddr);

/**
 * @brief   任务列表添加步骤
 * @param   addStepIndex 添加步骤的位置索引
 * @param   stepTypeID  添加步骤的类型ID
 * @param   modelFlag 模板标志 0:没有模板 1:有模板
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int TaskListAddStepProc(unsigned int addStepIndex, unsigned int stepTypeID, unsigned int modelFlag);

/**
 * @brief   任务列表删除步骤
 * @param   addStepIndex 删除步骤的索引
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int TaskListDelStepProc(unsigned int delStepIndex);

/**
 * @brief   任务列表清空
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 */
int TaskClearProc(void);

/**
 * @brief   加载任务文件
 * @param   fileName 任务文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskFileLoad(const char* fileName);

/**
 * @brief   保存任务文件
 * @param   fileName 任务文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskFileSave(const char* fileName);

/**
 * @brief TaskFileLoadFromPath
 * @param fileFullPath 任务文件的完整路径(包括任务文件名)
 * @return 0:成功 其它:失败
 * @note 从指定路径载入任务
 */
int TaskFileLoadFromPath(const char* fileFullPath);

/**
 * @brief TaskFileSaveToPath
 * @param filePath 任务文件保存路径
 * @param fileName 任务文件名称
 * @return 0:成功 其它:失败
 * @author <AutumnX>
 * @note 保存任务文件到指定目录
 */
int TaskFileSaveToPath(const char* filePath, const char* fileName);

/**
 * @brief   删除任务文件
 * @param   fileName 任务文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskFileDelete(const char* fileName);

/**
 * @brief   上传任务文件
 * @param   fileName 任务文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskFileUpload(const char* fileName, const char *serverIP);

/**
 * @brief   下载任务文件
 * @param   fileName 任务文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskFileDownload(const char* fileName, const char *serverIP);


/**
 * @brief StorageTaskFileCopyToPath
 * @param fileName: 任务文件名
 * @param dirPath: 拷贝到的目标路径
 * @return 0:成功 其它:失败
 * @author <AutumnX>
 * @note 把相机保存的任务文件拷贝到指定目录
 */
int StorageTaskFileCopyToPath(const char* fileName, const char* dirPath);

/**
 * @brief StorageTaskFileGetFromPath
 * @param dirFileFullPath:目标文件的完整路径
 * @return 0:成功 其它:失败
 * @author <AutumnX>
 * @note 从其它路径拷贝任务文件到任务保存目录
 */
int StorageTaskFileGetFromPath(const char* dirFileFullPath);

/**
 * @brief   上传脚本文件
 * @param   fileName 脚本文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int ScriptFileUpload(unsigned int fileType, const char* fileName, const char *serverIP);

/**
 * @brief   下载脚本文件
 * @param   fileName 脚本文件名称
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int ScriptFileDownload(unsigned int fileType, const char* fileName, const char *serverIP);

/**
 * @brief   获取某步被关联的信息
 * @param   checkStepIndex 要检查的步骤
 * @param   corInfo[] 用于返回关联步骤的索引
 * @param   corCount corInfo[]的大小
 * @return  返回得到的关联步骤数的个数
 * @author  <AutumnX>
 * @note
 */
unsigned int GetStepCorrelatedInfo(unsigned int checkStepIndex, unsigned int corInfo[], unsigned int corCount);

/**
 * @brief   步骤取样/确定
 * @param   stepIndex 要检查的步骤
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskStepLearnProc(unsigned int stepIndex);

/**
 * @brief   获取步骤参数无效的信息
 * @param   indexArray[] 用于返回步骤参数无效的索引
 * @param   arraySize indexArray[]的大小
 * @return  返回得到的步骤参数无效的步骤数
 * @author  <AutumnX>
 * @note
 */
int GetStepParamInvalidInfo(unsigned int indexArray[], unsigned int arraySize);

/**
 * @brief   任务开始运行
 * @param
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskRunStartProc(void);

/**
 * @brief   任务停止运行
 * @param
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int TaskRunStopProc(void);

/**
 * @brief   下载任务文件
 * @param   serverIP 服务器IP
 * @return  0:成功 其它:失败
 * @author  <AutumnX>
 * @note
 */
int ToolFileDownload(const char *serverIP);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
