#include "LibTaskFun.h"
#include <QMessageBox>
#include "task/TaskGlobal.h"

LibTaskFun::LibTaskFun()
{

}
LibTaskFun::~LibTaskFun()
{


}
int LibTaskFun::Task_Addr_Init()
{
    int ret = 1;

    ret=TaskInitialization();

    return ret;
}

int LibTaskFun::TaskList_AddStep_Proc(unsigned int addStepIndex, unsigned int stepTypeID, unsigned int modelTypeFlag)
{
    int ret = 1;
    ret=TaskListAddStepProc(addStepIndex,stepTypeID,modelTypeFlag);
    return ret;
}
int LibTaskFun::TaskList_DelStep_Proc(unsigned int delStepIndex)
{
    int ret = 1;
    TaskListDelStepProc(delStepIndex);
    return ret;
}
int LibTaskFun::TaskClear_Proc(void)
{
    int ret = 1;
    ret = TaskClearProc();
    return ret;
}
unsigned int LibTaskFun::Get_TaskStep_Count(void)
{
    unsigned int ret = 0;
    ret = GetTaskStepCount();
    return ret;
}
int LibTaskFun::TaskStep_Type_ID_Get(unsigned int step_index, unsigned int *pTypeID)
{
    int ret = 1;
    ret=Task_Step_Type_ID_Get(step_index,pTypeID);
    return ret;
}
void * LibTaskFun::Get_Task_Step_Input_Para(unsigned int step_index)
{
    return Task_Step_Input_Para_Get(step_index);
}
QVector<int>LibTaskFun::Get_taskID()
{
    QVector<int> vt_taskid;
    unsigned int count = GetTaskStepCount();

    for(unsigned int i = 0; i<count;i++)
    {
        unsigned int taskid = 0;
        if(Task_Step_Type_ID_Get(i+1,&taskid)==0)
        {
            vt_taskid.append(taskid);
        }
    }
    return vt_taskid;
}
