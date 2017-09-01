#ifndef TOOLMATCHBASEPOINT_H
#define TOOLMATCHBASEPOINT_H

#include "toolmatchbasepoint_global.h"
#include <QWidget>
#include "BasePointWidget.h"
#include "../../BasicDefine.h"

class TOOLMATCHBASEPOINTSHARED_EXPORT ToolMatchBasePoint
{

public:
    ToolMatchBasePoint();
};
extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void ReleaseWidget(QWidget *PWidget);
extern "C" Q_DECL_EXPORT void ReleaseQMap();
extern "C" Q_DECL_EXPORT void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
extern "C" Q_DECL_EXPORT void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color);
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram();
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetHead(int step);
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
extern "C" Q_DECL_EXPORT QPoint Get_Image_Pos();

#endif // TOOLMATCHBASEPOINT_H
