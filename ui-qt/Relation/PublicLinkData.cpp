#include <QDebug>
#include "PublicLinkData.h"
#include <stdio.h>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "stdio.h"
#include "LinkDataGlobal.h"
PublicLinkData* PublicLinkData::PublicInstance = NULL;

PublicLinkData *PublicLinkData::GetPublicLinkInstance()
{
    if(PublicInstance == NULL)
    {
        PublicInstance = new PublicLinkData();
    }
    return PublicInstance;
}

PublicLinkData::PublicLinkData()
{

}

PublicLinkData::~PublicLinkData()
{

}


unsigned int PublicLinkData::GetListAllTask()
{
    return GetTaskStepCount();
}

QString PublicLinkData::GetLinkDataPointTaskStr(int task_index)
{
    if(task_index < 1){
        return QString::null;
    }
    unsigned int type = 0;
    int ret = Task_Step_Type_ID_Get(task_index, &type);
    if(ret == 0 && Get_Task_Link_Type_Flag(type, Task_link_X_index) == 1){
        char taskName[40];
        memset(taskName, 0, 40);
        ret = Get_Task_Name(task_index, taskName);
        if(ret == 0){
            return QString::fromUtf8(taskName);
        }
    }
    return QString::null;
}

QString PublicLinkData::GetLinkDataAngleString(int task_index)
{
    if(task_index < 1){
        return QString::null;
    }
    unsigned int type = 0;
    int ret = Task_Step_Type_ID_Get(task_index, &type);
    if(ret == 0 && Get_Task_Link_Type_Flag(type, Task_link_D_index) == 1){
        char taskName[40];
        memset(taskName, 0, 40);
        ret = Get_Task_Name(task_index, taskName);
        if(ret == 0){
            return QString::fromUtf8(taskName);
        }
    }
    return QString::null;
}

QStringList PublicLinkData::GetResultString(int task_index, int link_type_index)
{
    QStringList ResultString;
    int current_index = 0;
    ResultString.clear();
    RESULT_NAME MultiResult;
    if(task_index < 1){
        return ResultString;
    }
    unsigned int type = 0;
    int ret = 0;
    ret = Task_Step_Type_ID_Get(task_index, &type);
    if(ret == 0){
        if(Get_Multi_Result_Task_Flag(type) == -1){
            ret = Init_AssociationMap_Task_Result_String(type, -1, link_type_index);
            if(ret > 0){
                for(int multiIndex = 0; multiIndex < ret; multiIndex++)
                {
                    memset(MultiResult.Result_Name, 0, sizeof(RESULT_NAME));
                    int rst = Get_AssociationMap_Result_String(multiIndex, &MultiResult);
                    if(rst == -1){
                        return ResultString;
                    }
                    current_index++;
                    ResultString.append(QString::fromUtf8(MultiResult.Result_Name));
                }
            }
        }else{
            unsigned int ResultCount = 0;
            ret = TaskMultiRstNumGet(task_index, 1, &ResultCount);
            if(ret != 0){
                return ResultString;
            }
            ret = Init_AssociationMap_Task_Result_String(type, ResultCount, link_type_index);
            if(ret > 0){
                for(int multiIndex = 0; multiIndex < ret; multiIndex++)
                {
                    memset(MultiResult.Result_Name, 0, sizeof(RESULT_NAME));
                    int rst = Get_AssociationMap_Result_String(multiIndex, &MultiResult);
                    if(rst == -1){
                        return ResultString;
                    }
                    current_index++;
                    ResultString.append(QString::fromUtf8(MultiResult.Result_Name));
                }
            }
        }
    }
    return ResultString;
}


QStringList PublicLinkData::GetLinkDataAngleStr(int task_index)
{
    return GetResultString(task_index, Task_link_D_index);
}

QStringList PublicLinkData::GetLinkDataYResultStr(int task_index)
{
    return GetResultString(task_index, Task_link_Y_index);
}

QStringList PublicLinkData::GetLinkDataXResultStr(int task_index)
{
    return GetResultString(task_index, Task_link_X_index);
}

int PublicLinkData::PublicLinkDataInit(int task_index)
{
    current_step = task_index;
    TASK_STEP_HEADER *p_TaskHeader = Task_Step_Head_Get(current_step);
    if(p_TaskHeader == NULL){
        return -1;
    }
    compass_enable = p_TaskHeader->compass_enable;
    for(int i = 0; i < 3; i++)
    {
        compass_type[i] = p_TaskHeader->compass_info[i].compass_type;
        compass_step[i] = p_TaskHeader->compass_info[i].compass_step;
        ref_value_index[i] = p_TaskHeader->compass_info[i].ref_value_index;
        compass_ori_value[i] = p_TaskHeader->compass_info[i].compass_ori_value;
    }

    if(compass_type[0] == 2)
    {
        unsigned int type = 0;
        int ret = 0;
        ret = Task_Step_Type_ID_Get(compass_step[0], &type);
        if(ret == 0){
            ref_value_index[0] = AssociationMap_Change_UIID(type, ref_value_index[0], Task_link_X_index) - 1;
        }
    }
    if(compass_type[1] == 2)
    {
        unsigned int type = 0;
        int ret = 0;
        ret = Task_Step_Type_ID_Get(compass_step[1], &type);
        if(ret == 0){
            ref_value_index[1] = AssociationMap_Change_UIID(type, ref_value_index[1], Task_link_Y_index) - 1;
        }
    }
    if(compass_type[2] == 2)
    {
        unsigned int type = 0;
        int ret = 0;
        ret = Task_Step_Type_ID_Get(compass_step[2], &type);
        if(ret == 0){
            ref_value_index[2] = AssociationMap_Change_UIID(type, ref_value_index[2], Task_link_D_index) - 1;
        }
    }
    return 0;
}


int PublicLinkData::PublicLinkDataHandleFinish()
{
    if(compass_type[0] == 2)
    {
        unsigned int type = 0;
        int ret = 0;
        ret = Task_Step_Type_ID_Get(compass_step[0], &type);
        if(ret == 0){
            int rst = AssociationMap_Change_TaskResultID(type, ref_value_index[0], Task_link_X_index);
            if(rst == -1){
                compass_type[0] = 0;
            }else{
                ref_value_index[0] = rst;
            }
        }
    }
    if(compass_type[1] == 2)
    {
        unsigned int type = 0;
        int ret = 0;
        ret = Task_Step_Type_ID_Get(compass_step[1], &type);
        if(ret == 0){
            int rst = AssociationMap_Change_TaskResultID(type, ref_value_index[1], Task_link_Y_index);
            if(rst == -1){
                compass_type[1] = 0;
            }else{
                ref_value_index[1] = rst;
            }
        }
    }
    if(compass_type[2] == 2)
    {
        unsigned int type = 0;
        int ret = 0;
        ret = Task_Step_Type_ID_Get(compass_step[2], &type);
        if(ret == 0){
            int rst = AssociationMap_Change_TaskResultID(type, ref_value_index[2], Task_link_D_index);
            if(rst == -1){
                compass_type[2] = 0;
            }else{
                ref_value_index[2] = rst;
            }
        }
    }
    TASK_STEP_HEADER *p_TaskHeader = Task_Step_Head_Get(current_step);
    if(p_TaskHeader == NULL){
        return -1;
    }
    p_TaskHeader->compass_enable = compass_enable;
    for(int i = 0; i < 3; i++)
    {
        p_TaskHeader->compass_info[i].compass_type = compass_type[i];
        p_TaskHeader->compass_info[i].compass_step = compass_step[i];
        p_TaskHeader->compass_info[i].ref_value_index = ref_value_index[i];
        p_TaskHeader->compass_info[i].compass_ori_value = compass_ori_value[i];
    }
    return 0;
}

