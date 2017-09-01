/**
  * @file  [PretreatmentLibFun.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/22>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef PRETREATMENTLIBFUN_H
#define PRETREATMENTLIBFUN_H
#include <QWidget>
#include "BaseLibInterface.h"
/**
  * @class  <PretreatmentLibFun>  [PretreatmentLibFun.h]  [PretreatmentLibFun]
  * @brief  预处理界面lib
  * @author  <szj>
  * @note
  * detailed  description
  */
class PretreatmentLibFun : public BaseLibInterface
{
public:
    PretreatmentLibFun();
    ~PretreatmentLibFun();
    /**
     * @brief GetToolWidget
     * @return 返回图像预处理界面Qwidget
     * @author szj
     * @date 2017/05/08
     * @note
     */
    QWidget *GetPreWidget();
    void Set_id_step(int iTask, int iStep, int x, int y, int edit,QVector<int>vt);
    void ConfigAllPreModule();
    void PreAllPreModuleDisable();
    void GetImageOutPut();
    void ListCptVga();
    void StepAcceleratorModuleEnable();
    void SetTaskNameVt(QVector<QString>vt);
    void SetColor(void *pen_color);
private:
    QWidget *m_pWidget;
};

#endif // PRETREATMENTLIBFUN_H
