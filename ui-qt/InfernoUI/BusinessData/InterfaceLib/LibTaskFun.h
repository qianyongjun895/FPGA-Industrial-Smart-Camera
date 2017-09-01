#ifndef LIBTASKFUN_H
#define LIBTASKFUN_H

#include "BaseLibInterface.h"

class LibTaskFun : public BaseLibInterface
{
public:
    LibTaskFun();
    ~LibTaskFun();
    /**
     * @brief 任务相关地址初始化
     * @param task_phy_addr: 任务物理地址
     *        task_size: 任务空间大小
     *        rst_phy_addr: 结果物理地址
     *        rst_size: 结果空间大小
     *        model_phy_addr: 模板物理地址
     *        model_size: 模板空间大小
     * @return 0: 成功，other: 失败
     * @author <szj>
     * @note
     */
    int Task_Addr_Init();

    /**
     * @brief   任务列表添加步骤
     * @param   addStepIndex 添加步骤的位置索引
     * @param   stepTypeID  添加步骤的类型ID
     * @param   modelTypeFlag 模板类型标志 0:表示没有 1:圆形模板 2:矩形模板
     * @return  0:成功 -1:失败
     * @author  <szj>
     */
    int TaskList_AddStep_Proc(unsigned int addStepIndex, unsigned int stepTypeID, unsigned int modelTypeFlag);

    /**
     * @brief   任务列表删除步骤
     * @param   addStepIndex 删除步骤的索引
     * @return  0:成功 -1:失败
     * @author  <szj>
     */
    int TaskList_DelStep_Proc(unsigned int delStepIndex);

    /**
     * @brief   任务列表清空
     * @return  0:成功 -1:失败
     * @author  <szj>
     */
    int TaskClear_Proc(void);
    /**
     * @brief   获取任务步骤总数
     * @return  任务步骤总数
     * @author  <szj>
     */
    unsigned int Get_TaskStep_Count(void);
    /**
     * @brief 获取任务步骤的类型ID
     * @param step_index：步骤号
     *        pTypeID：任务类型指针
     * @return 0:成功，其它：失败
     * @author <Terry>
     * @note
     */
    int TaskStep_Type_ID_Get(unsigned int step_index, unsigned int *pTypeID);
    /**
     * @brief 获取任务步骤输入参数
     * @param step_index：步骤号
     *        pTypeID：任务类型指针
     * @return 任务类型指针
     * @author <szj>
     * @note
     */
    void * Get_Task_Step_Input_Para(unsigned int step_index);

    QVector<int>Get_taskID();



private:



};

#endif // LIBTASKFUN_H
