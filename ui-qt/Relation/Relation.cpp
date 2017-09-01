#include "Relation.h"

RLMain *p_RLMain;
Relation::Relation()
{

}
QWidget *GetWidget()
{
    p_RLMain = new RLMain;
    return p_RLMain;
}

int IniLinkData(int task_Index)
{
    p_RLMain->SetCurrentStepIndex(task_Index);
    return 0;
}

int SetLinkData()
{
    p_RLMain->SetRelateLocationData();
    return 0;
}
