#ifndef BLOBCOUNT_H
#define BLOBCOUNT_H

#include "blobcount_global.h"
#include <QWidget>
#include "../../BasicDefine.h"
class BLOBCOUNTSHARED_EXPORT BlobCount
{

public:
    BlobCount();
};
extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void ReleaseWidget(QWidget *pWidget);
extern "C" Q_DECL_EXPORT void ReleaseQMap();
extern "C" Q_DECL_EXPORT void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
extern "C" Q_DECL_EXPORT void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram();
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetHead(int step);
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
extern "C" Q_DECL_EXPORT QPoint Get_Image_Pos();

#endif // BLOBCOUNT_H
