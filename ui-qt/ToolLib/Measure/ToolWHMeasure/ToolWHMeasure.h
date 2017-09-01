#ifndef TOOLWHMEASURE_H
#define TOOLWHMEASURE_H

#include "toolwhmeasure_global.h"
#include <QWidget>
#include "../../BasicDefine.h"

class TOOLWHMEASURESHARED_EXPORT ToolWHMeasure
{

public:
    ToolWHMeasure();
};

extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void ReleaseWidget(QWidget *PWidget);
extern "C" Q_DECL_EXPORT void ReleaseQMap();
extern "C" Q_DECL_EXPORT void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);
extern "C" Q_DECL_EXPORT void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color);
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram();

/**
 * @brief Get_Result_From_Ram
 * @author dgq
 * @note 获取取样、计算结果数据更新界面显示
 */
extern "C" Q_DECL_EXPORT void Get_Result_From_Ram();
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetHead(int step);
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
extern "C" Q_DECL_EXPORT QPoint Get_Image_Pos();
#endif // TOOLWHMEASURE_H
