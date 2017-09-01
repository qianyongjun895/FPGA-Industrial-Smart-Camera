#ifndef TOOLMATCHBOUNDARY_H
#define TOOLMATCHBOUNDARY_H

#include "toolmatchboundary_global.h"
#include <QWidget>
#include "BoundaryWidget.h"

class TOOLMATCHBOUNDARYSHARED_EXPORT ToolMatchBoundary
{

public:
    ToolMatchBoundary();
};
extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void ReleaseWidget(QWidget *PWidget);
extern "C" Q_DECL_EXPORT void ReleaseQMap();
extern "C" Q_DECL_EXPORT void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
//extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetHead(int step);
//extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
extern "C" Q_DECL_EXPORT QPoint Get_Image_Pos();
#endif // TOOLMATCHBOUNDARY_H
