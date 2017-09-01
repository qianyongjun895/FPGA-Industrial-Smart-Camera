#include "Pretreatment.h"
#include <qdebug.h>
PreMain *p_preMain;
Pretreatment::Pretreatment()
{

}
QWidget *GetWidget()
{
    p_preMain = new PreMain;
    return p_preMain;
}
void SetIdAndStep(int id, int step, int x, int y, int edit,QVector<int>vt)
{
    p_preMain->SetIdAndStep(id,step,x,y,edit,vt);
}
void PreModuleConfigAll()
{
    p_preMain->ModuleConfigAll();
}
void PreAllModuleDisable()
{
    p_preMain->PreAllModuleDisable();
}
void GetImageOutPut()
{
     p_preMain->GetImageOutPut();
}
void ListCptVga()
{
    p_preMain->ListCptVga();
}
void StepAcceleratorModuleEnable()
{
    p_preMain->AcceleratorModuleEnable();
}
void SetTaskListName(QVector<QString>vtName)
{
    p_preMain->SetTaskListName(vtName);
}
void SetColor(void *pen)
{
    p_preMain->SetColor(pen);
}
