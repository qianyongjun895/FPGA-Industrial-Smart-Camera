/**
  * @file  [BlobWidget.h]
  * @brief  BlobWidget
  * @author  <dgq>
  * @date  <2017/5/23>
  * @version  <1.0>
  * @note blob工具界面
  * detailed  description
  */
#ifndef BLOBWIDGET_H
#define BLOBWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLibrary>
#include <QTimer>
#include "TaskStepGlobal.h"
#include "TaskRstGlobal.h"
#include "BlobGlobal.h"

/*获取小键盘Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();

/*门限值输入*/
typedef void (*Fun_SetRangeInput)(QString max, QString min, int flag);

/*获取门限的输入值函数指针*/
typedef QString (*Fun_GetRangeNum)();

/*获取普通数字输入值的函数指针*/
typedef QString (*Fun_GetNumString)();

/*获取取样进度条Dialog指针的函数指针*/
typedef QDialog* (*Fun_GetLearnDialog)();

/*设置进度条对话框结果显示的函数指针*/
typedef void* (*Fun_SetResultString)(QString str);

/*下门限*/
#define THRESHOLD_LOW   0
/*上门限*/
#define THRESHOLD_HIGH  1

namespace Ui {
class BlobWidget;
}

class BlobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlobWidget(QWidget *parent = 0);
    ~BlobWidget();

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
     * @brief on_btnPrePage_clicked
     * @author dgq
     * @note 上一页按钮响应函数
     */
    void on_btnPrePage_clicked();

    /**
     * @brief on_btnPrePage_clicked
     * @author dgq
     * @note 下一页按钮响应函数
     */
    void on_btnNextPage_clicked();

    /**
     * @brief on_btnPrePage_clicked
     * @author dgq
     * @note 计算按钮响应函数
     */
    void on_btnAutoCalc_clicked();

    /**
     * @brief CalcTimerSlot
     * @author dgq
     * @note 计算或取样的过程定时器响应函数
     */
    void CalcTimerSlot();

private:
    Ui::BlobWidget *ui;
    QLabel *m_label;//显示图像用的QLabel
    BLOB_INPUT_PARAM *pInputPara;//Input参数指针
    int m_step_index;//当前步骤索引
    int m_i_load_first;//
    QLibrary m_keyBoard_Lib;
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;
    int Calc_rst_flag;//当前是否计算的结果

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

    /**
     * @brief BlobNumInputPro
     * @author dgq
     * @note blob最大检查个数的输入响应函数
     */
    void BlobNumInputPro();

    /**
     * @brief SetDataToLib
     * @author dgq
     * @note 将界面的配置参数写入内存
     */
    void SetDataToLib();

    /**
     * @brief RangeInputPro
     * @param pEditMax 上门限输入框指针
     * @param pEditMin 下门限输入框指针
     * @param calc_value 计算值
     * @param flag 当前点击的输入框是上门限还是下门限标志，1:上门限 0:下门限
     * @author dgq
     * @note 门限值输入
     */
    void RangeInputPro(QLineEdit *pEditMax, QLineEdit *pEditMin, QString calc_value, int flag);

    /**
     * @brief LoadLearnLib
     * @author dgq
     * @note 加载取样或计算过程进度条弹窗的库
     */
    void LoadLearnLib();
};

#endif // BLOBWIDGET_H
