/**
  * @file  [FWMatchSkeletonLabel.h]
  * @brief  FWMatchSkeletonLabel
  * @author  <dgq>
  * @date  <2017/5/25>
  * @version  <1.0>
  * @note 轮廓匹配的界面
  * detailed  description
  */
#ifndef SKELETONWIDGET_H
#define SKELETONWIDGET_H

#include <QWidget>
#include "FWMatchSkeletonLabel.h"
#include <QLabel>
#include <QTime>
#include <QLibrary>
#include <QPushButton>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include <SkeletonMatchGlobal.h>

/*获取小键盘Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
/*获取普通数字输入值的函数指针*/
typedef QString (*Fun_GetNumString)();

namespace Ui {
class SkeletonWidget;
}

class SkeletonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SkeletonWidget(QWidget *parent = 0);
    ~SkeletonWidget();
    QPoint Get_Image_Pos();

    /**
     * @brief Set_Parameter_To_Ram
     * @author dgq
     * @note 写内Input存接口，每个工具必须要实现的接口
     */
    int Set_Parameter_To_Ram();

    /**
     * @brief Init_Input_Ptr
     * @param ptr 指向本步骤Input参数内存起始地址的指针
     * @param i_step_index 步骤号
     * @param new_flag 新加任务标志 1:新加 0:编辑
     * @author dgq
     * @note 初始化接口，每个工具必须要实现的接口
     */
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

private slots:
    void on_btnSkeletonUp_pressed();

    void on_btnSkeletonDown_pressed();

    void on_btnSkeletonLeft_pressed();

    void on_btnSkeletonRight_pressed();

    void GetCurrentTime();
    void RectPointChange(QPoint point, int index);
    void on_radioButtonSkeletonStudyBit1_clicked();

    void on_radioButtonSkeletonStudyBit2_clicked();

    void on_radioButtonSkeletonFindBit1_clicked();

    void on_radioButtonSkeletonFindBit2_clicked();
    void on_horizontalSliderSensitivity_valueChanged(int value);
    void on_btnSubSensitivity_pressed();

    void on_btnAddSensitivity_pressed();

    void on_btnSubScore_pressed();

    void on_btnAddScore_pressed();

    void on_horizontalSliderScore_valueChanged(int value);

protected:
    /**
     * @brief eventFilter
     * @param watched 监听对象
     * @param event 监听事件
     * @return
     * @author dgq
     * @note 事件过滤器，用来模拟行文本编辑框点击事件
     */
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::SkeletonWidget *ui;
    QLabel *m_label;
    QTime startTime;
    QTime stopTime;
    SKELETON_INPUT_PARAM *pInputPara;
    int m_step_index;//当前步骤索引
    int m_i_load_first;//
    QLibrary m_keyBoard_Lib;
    QTimer *CalcTimer;
    int Calc_rst_flag;//当前是否计算的结果

    void SetBtnRepeatParam(QPushButton *btn);
    void RotateAngleInputPro();
    /**
     * @brief InitData
     * @author dgq
     * @note 初始化界面显示
     */
    void InitData();

    /**
     * @brief LoadKeyBoardLib
     * @author dgq
     * @note 加载输入软键盘库
     */
    void LoadKeyBoardLib();

};

#endif // SKELETONWIDGET_H
