#ifndef RELATION_H
#define RELATION_H

#include "relation_global.h"
#include "RLMain.h"
class RELATIONSHARED_EXPORT Relation
{

public:
    Relation();
};
extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT int IniLinkData(int task_Index);
extern "C" Q_DECL_EXPORT int SetLinkData();

#endif // RELATION_H
