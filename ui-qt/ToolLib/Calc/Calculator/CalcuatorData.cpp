#include <QDebug>
#include "CalcuatorData.h"
#include "TaskHeaderGlobal.h"
#include "TaskRstGlobal.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"
CalcuatorData::CalcuatorData()
{

}
CalcuatorData::~CalcuatorData()
{

}


int CalcuatorData::LoadPositionData(void *pInpuPara, int TaskListIndex, int new_flag)
{
    step_index = TaskListIndex;
    if(!new_flag){
        CALC_INPUT_PARAM* p_InputParam= (CALC_INPUT_PARAM*)pInpuPara;
        calc_item_count = p_InputParam->calc_item_count;
        CALC_PRIVATE_PARAM *p_PrivateParam = (CALC_PRIVATE_PARAM*)Task_Step_Private_Para_Get(TaskListIndex);
        for(unsigned int i = 0; i < calc_item_count; i++){
            calc_select_flag[i] = p_InputParam->calc_select_flag[i];
            memcpy(&calc_item[i], &p_PrivateParam->calc_item[i], sizeof(CALC_ITEM));
        }
    }else
    {
        Task_Step_Synthetic_Judge_Flag_Set(TaskListIndex,1);
        calc_item_count = 0;
    }
    return 0;
}

int CalcuatorData::LearnStart(int TaskListIndex)
{
    CALC_INPUT_PARAM* p_InputParam= (CALC_INPUT_PARAM*)Task_Step_Input_Para_Get(TaskListIndex);
    p_InputParam->calc_item_count = calc_item_count;
    CALC_PRIVATE_PARAM *p_PrivateParam = (CALC_PRIVATE_PARAM*)Task_Step_Private_Para_Get(TaskListIndex);
    for(unsigned int i = 0; i < calc_item_count; i++){
        p_InputParam->calc_select_flag[i] = calc_select_flag[i];
        memcpy(&p_PrivateParam->calc_item[i], &calc_item[i], sizeof(CALC_ITEM));
    }
    return 0;
}

void CalcuatorData::CleanData()
{
    CALC_INPUT_PARAM* p_InputParam= (CALC_INPUT_PARAM*)Task_Step_Input_Para_Get(step_index);
    p_InputParam->calc_item_count = 0;
    memset(p_InputParam->calc_select_flag, 0, CALC_ITEM_NUM_MAX);
    CALC_PRIVATE_PARAM *p_PrivateParam = (CALC_PRIVATE_PARAM*)Task_Step_Private_Para_Get(step_index);
    memset(p_PrivateParam->calc_item, 0, sizeof(CALC_ITEM)*CALC_ITEM_NUM_MAX);
}

unsigned int CalcuatorData::GetTaskMuchResultCount(unsigned int task_index)
{
    unsigned int count = 0;
    int ret = TaskMultiRstNumGet(task_index, 1, &count);
    if(ret == 0){
        return count;
    }
    return 0;
}

int CalcuatorData::GetTaskTypeFlag(unsigned int index)
{
    unsigned int task_type = 0;
    int ret = Task_Step_Type_ID_Get(index, &task_type);
    if(ret == 0){
        ret = Get_Multi_Result_Task_Flag(task_type);
        if(ret == 1){
            return 1;
        }
        return 0;
    }
    return 0;
}


unsigned int CalcuatorData::GetListAllTask()
{
    return GetTaskStepCount();
}



QString CalcuatorData::GetTaskListString(unsigned int index)
{
    char TaskName[40];
    memset(TaskName, 0, 40);
    int ret = Get_Task_Name(index, TaskName);
    if(ret == 0){
        return QString::number(index)+"."+QString::fromUtf8(TaskName);
    }
    return QString::null;
}

QStringList CalcuatorData::GetTaskResultString(unsigned int index)
{
    QStringList Task_Result_List;
    Task_Result_List.clear();
    unsigned int task_type = 0;
    int ret = Task_Step_Type_ID_Get(index, &task_type);
    if(ret == 0){
        unsigned int Result_count = 0;
        RESULT_NAME Task_Result[250];
        TaskMultiRstNumGet(index, 1, &Result_count);
        ret = Get_Multi_Result_Task_Result_String(Calc_index, task_type, Result_count, Task_Result);
        for(int i = 0; i < ret; i++){
            Task_Result_List.append(QString::fromUtf8(Task_Result[i].Result_Name));
        }
    }
    return Task_Result_List;
}

unsigned int CalcuatorData::NewSetResultID(int task_index, int rst_index, unsigned int result_ID)
{
    unsigned int task_type = 0;
    int ret = Task_Step_Type_ID_Get(task_index, &task_type);
    if(ret == 0){
        if(rst_index != -1){
            ret = UIId_Change_ResultID(Calc_index, task_type, rst_index+1, result_ID+1);
            if(ret != -1){
                return ret;
            }
        }else{
            ret = UIId_Change_ResultID(Calc_index, task_type, -1, result_ID+1);
            if(ret != -1){
                return ret;
            }
        }
    }
    return 0;
}


int CalcuatorData::NewGetResultID(int* count,int task_index, unsigned int result_index)
{
    unsigned int task_type = 0;
    int ret = Task_Step_Type_ID_Get(task_index, &task_type);
    if(ret == 0){
        ret = ResultId_Change_UIID(count, Calc_index, task_type, result_index);
        if(!(ret == -1 && *count == -1)){
            if(*count != -1){
                if(ret == -1){
                    *count = 0;
                    return 0;
                }
                else{
                    *count = *count - 1;
                    return ret;
                }
            }else if(ret > 0 && *count == -1){
                *count = -1;
                return ret;
            }
        }
    }
    return 0;
}

QStringList CalcuatorData::GetSendDataStringList(unsigned int index, unsigned int result_index)
{
    char Result_Data[100];
    QStringList TaskStringList;
    TaskStringList.clear();
    unsigned int task_type = 0;
    int ret = Task_Step_Type_ID_Get(index, &task_type);
    if(ret == 0){
        for(int i = 0; ;i++){
            memset(Result_Data, 0, 100);
            if(result_index != -1){
                result_index = result_index+1;
            }
            int ret = Get_Task_Result_String(Calc_index, task_type, result_index, i, Result_Data);
            if(ret == 1){
                TaskStringList.append(QString::fromUtf8(Result_Data));
            }else if(ret == -1){
                return TaskStringList;
            }
        }
    }
    return TaskStringList;
}

//    int type = GetTaskListType(index);
//    int i = 0;
//    QStringList TaskStringList;
//    TaskStringList.clear();
//    QVector<QString> TaskDataString;
//    TASK_RESULT_STRU* Taskdatastruct;
//    PublicLinkData* publicData = PublicLinkData::GetPublicLinkInstance();
//    TaskDataString = publicData->GetTaskResultString(type);
//    Taskdatastruct = GetTaskDataHandleStruct(type, Calc_index);
//    if(Taskdatastruct == NULL)
//    {
//        return TaskStringList;
//    }
//    if(result_index == 0)
//    {
//        if(GetTaskTypeFlag(index) == 4 ||
//           GetTaskTypeFlag(index) == 5 ||
//           GetTaskTypeFlag(index) == 6)
//        {
//            TaskStringList.append(TaskDataString.at(0));
//            TaskStringList.append(TaskDataString.at(1));
//            TaskStringList.append(TaskDataString.at(2));
//        }
//        return TaskStringList;

//    }
//    for(i = 0; i < TaskDataString.count(); i++)
//    {
//        if(Taskdatastruct[i].calc == 1)
//        {
//            TaskStringList.append(TaskDataString[i]);
//        }
//    }
//    return TaskStringList;
//}
