/**
  * @file  [Pretreatment.h]
  * @brief  Pretreatment
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  预处理模块对外接口
  */

#ifndef PRETREATMENT_H
#define PRETREATMENT_H

#include "pretreatment_global.h"
#include "PreMain.h"
class PRETREATMENTSHARED_EXPORT Pretreatment
{

public:
    Pretreatment();
};
/**
 * @brief GetWidget
 * @author szj
 * @return QWidget  返回预处理模块界面
 * @date 2017/05/08
 * @note 获取预处理模块QWidget界面
 */
extern "C" Q_DECL_EXPORT QWidget *GetWidget();
/**
 * @brief SetIdAndStep
 * @param id 图像工具ID
 * @param step 图像工具步骤号
 * @param x 父窗口的x坐标
 * @param y 父窗口的y坐标
 * @param edit 当前是否编辑状态
 * @param QVector<int>vt 所有任务工具的名称
 * @author szj
 * @date 2017/05/08
 * @note 初始化预处理模块
 */
extern "C" Q_DECL_EXPORT void SetIdAndStep(int id,int step,int x,int y,int edit,QVector<int>vt);
/**
 * @brief PreModuleConfigAll
 * @author szj
 * @date 2017/05/08
 * @note 配置所有加速器模块参数
 */
extern "C" Q_DECL_EXPORT void PreModuleConfigAll();
/**
 * @brief PreAllModuleDisable
 * @author szj
 * @date 2017/05/08
 * @note 关闭加速器模块
 */
extern "C" Q_DECL_EXPORT void PreAllModuleDisable();
/**
 * @brief GetImageOutPut
 * @author szj
 * @date 2017/05/08
 * @note 获取图像输出源
 */
extern "C" Q_DECL_EXPORT void GetImageOutPut();
/**
 * @brief ListCptVga
 * @author szj
 * @date 2017/05/08
 * @note 设置当前图像为cpt模块源显示
 */
extern "C" Q_DECL_EXPORT void ListCptVga();
/**
 * @brief StepAcceleratorModuleEnable
 * @return
 * @author szj
 * @date 2017/6/22
 * @note 单个步骤加速器模块参数配置与使能
 */
extern "C" Q_DECL_EXPORT void StepAcceleratorModuleEnable();
/**
 * @brief SetTaskListName
 * @return
 * @author szj
 * @date 2017/6/22
 * @note 下拉框加载当前步骤之前的所有任务
 */
extern "C" Q_DECL_EXPORT void SetTaskListName(QVector<QString>vtName);
extern "C" Q_DECL_EXPORT void SetColor(void *pen);
#endif // PRETREATMENT_H
