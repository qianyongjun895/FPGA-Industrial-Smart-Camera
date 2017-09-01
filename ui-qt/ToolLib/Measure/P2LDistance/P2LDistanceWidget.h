/**
  * @file  [FWP2LDistanceLabel.h]
  * @brief  FWP2LDistanceLabel
  * @author  <Vincent>
  * @date  <2017/6/5>
  * @version  <1.0>
  * @note 点线距离界面
  * detailed  description
  */
#ifndef P2LDISTANCEWIDGET_H
#define P2LDISTANCEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QTimer>
#include "TaskStepGlobal.h"
#include "PixelConvert.h"
#include "TaskRstGlobal.h"
#include "PointLineDistGlobal.h"

#define VGA_WIDTH 640 //图像显示区域的宽度
#define VGA_HEIGHT 480 //图像显示区域的高度
namespace Ui {
class P2LDistanceWidget;
}

/*获取小键盘Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();

/*门限值输入*/
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);

/*获取门限的输入值函数指针*/
typedef QString (*Fun_GetRangeNum)();

/*获取取样进度条Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetLearnDialog)();

/*设置进度条对话框结果显示的函数指针*/
typedef void* (*Fun_SetResultString)(QString str);

class P2LDistanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit P2LDistanceWidget(QWidget *parent = 0);
    ~P2LDistanceWidget();

    /**
     * @brief Get_Image_Pos
     * @return 图像显示区域的位置
     * @author dgq
     * @note 编辑界面需要显示图像的工具界面实现该接口
     */
    QPoint Get_Image_Pos();

    /**
     * @brief Set_Parameter_To_Ram
     * @author dgq
     * @note 取样，每个工具必须实现的接口
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

    /**
     * @brief Get_Result_From_Ram
     * @author dgq
     * @note 取样、计算成功后获取结果数据，有计算、取样结果的工具需要实现该接口，从内存中获取相应的结果数据
     */
    void Get_Result_From_Ram();
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
private slots:
    /**
     * @brief PointTaskChangeSlot
     * @param index
     * @author dgq
     * @note 点任务下拉框索引改变的响应函数
     */
    void PointTaskChangeSlot(int index);

    /**
     * @brief LineTaskChangeSlot
     * @param index
     * @author dgq
     * @note 线任务下拉框索引改变的响应函数
     */
    void LineTaskChangeSlot(int index);

    /**
     * @brief PointResultChangeSlot
     * @param index
     * @author dgq
     * @note 点结果下拉框索引改变的响应函数
     */
    void PointResultChangeSlot(int index);

    /**
     * @brief LineResultChangeSlot
     * @param index
     * @author dgq
     * @note 线结果下拉框索引改变的响应函数
     */
    void LineResultChangeSlot(int index);

    /**
     * @brief on_radioButton_phy_clicked
     * @author dgq
     * @note 门限值的数据类型切换为物理值
     */
    void on_radioButton_phy_clicked();

    /**
     * @brief on_radioButton_pix_clicked
     * @author dgq
     * @note 门限值的数据类型切换为像素值
     */
    void on_radioButton_pix_clicked();

    /**
     * @brief on_btnCalculation_clicked
     * @author dgq
     * @note 计算按钮响应函数
     */
    void on_btnCalculation_clicked();

    /**
     * @brief CalcTimerSlot
     * @author dgq
     * @note 计算或取样过程的定时器响应函数
     */
    void CalcTimerSlot();

private:
    Ui::P2LDistanceWidget *ui;
    QLabel *m_label;//用来显示图像的QLabel指针
    void *pInputPara; //Input参数指针
    int m_step_index; //当前步骤号
    int m_i_load_first;
    int pix_phy_flag; //门限值的数据类型 0:像素值 1:物理值
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    /**
     * @brief InitPointCombobox
     * @param id 任务的类型ID
     * @return 返回对应任务类型的任务名称
     * @author dgq
     * @note 初始化点任务下拉框，根据任务的类型id获取对应的点任务的中文名称
     */
    QString InitPointCombobox(int TaskIndex, int id);

    /**
     * @brief InitLineCombobox
     * @param id 任务的类型ID
     * @return 返回对应任务类型的任务名称
     * @author dgq
     * @note 初始化直线任务下拉框，根据任务的类型id获取对应的直线任务的中文名称
     */
    QString InitLineCombobox(int TaskIndex, int id);

    /**
     * @brief GetRefPara
     * @param ref_step 任务步骤号
     * @param ref_result 结果索引号
     * @param point 引用的点数据保存指针
     * @author dgq
     * @note 获取点任务的引用数据
     */
    void GetRefPara(int ref_step, int ref_result, QPoint *point);

    /**
     * @brief InitData
     * @param i_step_index 任务步骤号
     * @author dgq
     * @note 初始化界面显示
     */
    void InitData(int i_step_index);

    /**
     * @brief Line_Paint_Base_On_KB_SubPixel
     * @param k_f
     * @param b_f
     * @param pOsd_line
     * @return
     * @author dgq
     * @note 根据点斜式计算出直线与图像显示区域边界的两个交点
     */
    int Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line);

    /**
     * @brief Line_Osd_Init
     * @param pLinePara
     * @param pOsdLine
     * @return
     * @author dgq
     * @note 根据点斜式计算出直线与图像显示区域边界的两个交点
     */
    int Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine);

    /**
     * @brief InitRangeData
     * @author dgq
     * @note 初始化门限值
     */
    void InitRangeData();

    /**
     * @brief SetRangetoLib
     * @return
     * @author dgq
     * @note 将界面的配置参数写入内存，取样或计算前调用
     */
    int SetRangetoLib();

    /**
     * @brief LoadKeyBoardLib
     * @author dgq
     * @note 加载输入软键盘的库
     */
    void LoadKeyBoardLib();

    /**
     * @brief LoadLearnLib
     * @author dgq
     * @note 加载取样或计算过程的进度条弹窗库
     */
    void LoadLearnLib();
};

#endif // P2LDISTANCEWIDGET_H
