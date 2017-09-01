/**
  * @file  [UIToolLibFun.h]
  * @brief
  * @author  <szj>
  * @date  <2017/05/15>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef UITOOLLIBFUN_H
#define UITOOLLIBFUN_H
#include <QWidget>
#include "BaseLibInterface.h"
#include "../ToolLib/BasicDefine.h"

/**
  * @class  <UIToolLibFun>  [UIToolLibFun.h]  [UIToolLibFun]
  * @brief  工具dll访问类
  * @author  <szj>
  * @note
  * detailed  description
  */

class UIToolLibFun :public BaseLibInterface
{
public:
    UIToolLibFun();
    ~UIToolLibFun();


    /**
     * @brief IniLib
     * @param strName 控件lib路径
     * @return 1返回成功 0返回失败
     * @author szj
     * @date 2017/05/08
     * @note 设置lib路径
     */
    //int IniLib(QString strName);
    /**
     * @brief GetToolWidget
     * @return 返回图像工具界面Qwidget
     * @author szj
     * @date 2017/05/08
     * @note 设置lib路径
     */
    QWidget *GetToolWidget();
    /**
     * @brief Set_fun_lib_path
     * @param strPath lib路径
     * @author szj
     * @date 2017/05/19
     * @note 设置lib路径
     */
    void Set_fun_lib_path(QString strPath);

    void Paint(QPainter *paint,int step,void *PenStly=NULL,int paintAreaSelect=1);
    void Init_Input_Ptr(void *pInpuPara, int i_step_index, int new_flag,void *pen_color = NULL);
    void Get_Result_From_Ram();

    int Set_Parameter_To_Ram();
    QVector<STRU_KEY_VALUE> GetHead(int step);
    QVector<STRU_KEY_VALUE> GetContent(int step, int index, int *count);
    int SetResultIndex(int index);
    QPoint Get_Image_Pos();
    void ReleaseMap();

private:
    /*QString m_strLib;
    QLibrary m_lib;*/
    QWidget *m_pWidget;
};

#endif // UITOOLLIBFUN_H
