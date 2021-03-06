#ifndef TOOLMATCHSAMPLE_H
#define TOOLMATCHSAMPLE_H
#include <QWidget>
#include "../../BasicDefine.h"
#include "toolmatchsample_global.h"

class TOOLMATCHSAMPLESHARED_EXPORT ToolMatchSample
{

public:
    ToolMatchSample();
};
/**
 * @brief GetWidget
 * @return
 * @author dgq
 * @note 获取界面对象指针
 */
extern "C" Q_DECL_EXPORT QWidget *GetWidget();

/**
 * @brief ReleaseWidget
 * @param PWidget
 * @author dgq
 * @note 释放界面对象指针
 */
extern "C" Q_DECL_EXPORT void ReleaseWidget(QWidget *PWidget);
extern "C" Q_DECL_EXPORT void ReleaseQMap();
/**
 * @brief Paint
 * @param paint
 * @param step
 * @author dgq
 * @note OSD显示
 */
extern "C" Q_DECL_EXPORT void Paint(QPainter *paint,int step,void *penStyle,int paintAreaSelect);

/**
 * @brief Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化任务Input结构体指针
 */
extern "C" Q_DECL_EXPORT void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

/**
 * @brief Get_Result_From_Ram
 * @author dgq
 * @note 获取取样、计算结果数据更新
 */
extern "C" Q_DECL_EXPORT void Get_Result_From_Ram();

/**
 * @brief Set_Parameter_To_Ram
 * @author dgq
 * @note 将配置参数写入内存
 */
extern "C" Q_DECL_EXPORT int Set_Parameter_To_Ram();

/**
 * @brief GetHead
 * @param step
 * @return 通用输出详细信息
 * @author dgq
 * @note 获取任务通用输出数据
 */
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetHead(int step);

/**
 * @brief GetContent
 * @param step
 * @return
 * @author dgq
 * @note 获取本步详细输出数据
 */
extern "C" Q_DECL_EXPORT QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);


/**
 * @brief Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
extern "C" Q_DECL_EXPORT QPoint Get_Image_Pos();
#endif // TOOLMATCHSAMPLE_H
