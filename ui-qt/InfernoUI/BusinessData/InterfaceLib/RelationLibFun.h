/**
  * @file  [RelationLibFun.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/22>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef RELATIONLIBFUN_H
#define RELATIONLIBFUN_H
#include <QWidget>
#include "BaseLibInterface.h"

/**
  * @class  <RelationLibFun>  [RelationLibFun.h]  [RelationLibFun]
  * @brief  关联定位界面lib
  * @author  <szj>
  * @note
  * detailed  description
  */
class RelationLibFun : public BaseLibInterface
{
public:
    RelationLibFun();
    ~RelationLibFun();
    /**
     * @brief GetToolWidget
     * @return 返回关联定位界面Qwidget
     * @author szj
     * @date 2017/05/08
     * @note
     */
    QWidget *GetRLWidget();
    int IniRLData(int task_Index);
    int SetRLData();
private:
    QWidget *m_pWidget;
};

#endif // RELATIONLIBFUN_H
