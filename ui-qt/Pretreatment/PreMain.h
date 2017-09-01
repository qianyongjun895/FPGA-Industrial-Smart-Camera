/**
  * @file  [PreMain.h]
  * @brief  FileIniControl
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef PREMAIN_H
#define PREMAIN_H

#include <QWidget>
#include <QMap>
#include "PreBasicHead.h"
#include <QTimer>
#include <QVector>


namespace Ui {
class PreMain;
}
/**
  * @class  <PreMain>  [TaskListStepWidget.h]  [PreMain]
  * @brief  预处理处主界面
  * @author  <szj>
  * @note
  * detailed  description
  */
class PreMain : public QWidget
{
    Q_OBJECT

public:

    explicit PreMain(QWidget *parent = 0);
    ~PreMain();
    /**
     * @brief AddItemData
     * @param strName 预处理模块名称
     * @param index 预处理模块ID
     * @param bCheck 预处理模块是否使能
     * @author szj
     * @date 2017/05/08
     * @note 增加预处理模块
     */
    void AddItemData(QString strName, int index, int bCheck, int current);
    /**
     * @brief InitAccTaskID
     * @author szj
     * @date 2017/05/08
     * @note 设置预处理模块的个数及任务id
     */
    void InitAccTaskID();
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
    void SetIdAndStep(int id, int step, int x, int y, int edit,QVector<int>vt);
    /**
     * @brief ConnectEdgePointSlot
     * @param dlg 边沿提取模块指针
     * @author szj
     * @date 2017/05/08
     * @note 连接边沿提取信号
     */
    void ConnectEdgePointSlot(void *dlg);
    /**
     * @brief SetIdAndStep
     * @param dlg 边沿提取模块指针
     * @author szj
     * @date 2017/05/08
     * @note 取消边沿提取信号
     */
    void DisConnectEdgePointSlot(void *dlg);
    /**
     * @brief ModuleConfigAll
     * @author szj
     * @date 2017/05/08
     * @note 配置所有加速器模块参数
     */
    void ModuleConfigAll();
    /**
     * @brief ModuleConfigAll
     * @author szj
     * @date 2017/05/08
     * @note 关闭加速器模块
     */
    void PreAllModuleDisable();
    /**
     * @brief SetDDRPicLimit
     * @author szj
     * @date 2017/05/08
     * @note 设置图像边界线
     */
    void SetDDRPicLimit();
    /**
     * @brief GetImageOutPut
     * @author szj
     * @date 2017/05/08
     * @note 获取图像输出源
     */
    int GetImageOutPut();
    /**
     * @brief ListCptVga
     * @author szj
     * @date 2017/05/08
     * @note 设置当前图像为cpt模块源显示
     */
    void ListCptVga();
    /**
     * @brief AcceleratorModuleEnable
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 单个步骤加速器模块参数配置与使能
     */
    void AcceleratorModuleEnable();
    /**
     * @brief SetTaskListName
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 下拉框加载当前步骤之前的所有任务
     */
    void SetTaskListName(QVector<QString>vtName);

    void SetColor(void *pen_color);
public:
    int m_task_id;
    int m_step;
    void *m_pre_ptr;
    int m_listX;
    int m_listY;
    void *m_pen_color;
private slots:
    void Time_Out();
    void OperateSlots(int iOperate,int itaskKind,int value,int current);
    void on_btnAdd_clicked();
    void on_btnDell_clicked();
    void on_btnClear_clicked();
    void SwitchListEdgePointsSlot(int value);
    void on_checkBoxRun_clicked();

    void on_btnCopy_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

signals :
    void PointChangeSignal(QVector<int>vt);

private:
    Ui::PreMain *ui;

    unsigned char m_buf[64];
    QMap<int,STRUCT_FUN_PTR>m_fun_ptr;
    int m_image_out_src;
    QTimer *m_timer;
    QVector<int>m_vt_points_taskid;

    /**
     * @brief InitFunPtr
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 初始化预处理模块函数指针
     */
    void InitFunPtr();
    /**
     * @brief SetItemCurrentRow
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 设置预处理模块所在列表中的位置
     */
    void SetItemCurrentRow();
    /**
     * @brief SetItemCurrentRow
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 初始化预处理模块列表
     */
    void InitPreList(int iEdit, QVector<int>vt);
    /**
     * @brief SetItemCurrentRow
     * @param taskId 预处理模块ID
     * @return 返回当前预处理模块是否使能
     * @author szj
     * @date 2017/6/22
     * @note 获取当前预处理模块是否使能
     */
    int PreModelEnabel(int taskId);
    /**
     * @brief IniPreSrc
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 初始化预处理模块输入源
     */
    void IniPreSrc();
    /**
     * @brief Start_timer
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 开启定时器
     */
    void Start_timer(int time = 1000);
    /**
     * @brief Stop_timer
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 停止定时器
     */
    void Stop_timer();
    /**
     * @brief Stop_timer
     * @param taskid 预处理模块ID
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 将需要描点的预处理模块加入队列中
     */
    void InitPaintPoints(int taskid);
    /**
     * @brief RemovePointsVt
     * @param taskid 预处理模块ID
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 将需要描点的预处理模块从队列中移除
     */
    void RemovePointsVt(int taskid);
    /**
     * @brief IsAddPreItem
     * @param index 预处理模块ID
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 判断模块是否加以加在列表中
     */
    int IsAddPreItem(int index);
    /**
     * @brief IsAddPreItem
     * @param index 预处理模块ID
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 判断模块输入输出源连接是否正常
     */
    int IsPreSel(int index);
    /**
     * @brief IsAddPreItem
     * @param taskId 预处理模块ID
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 判断模块是否在预处理模块中
     */
    int FindTaskInTable(int taskId);
    /**
     * @brief ExchangeItemData
     * @param iRow 列表行号
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 交换列表数据
     */
    void ExchangeItemData(int iRow);
    /**
     * @brief CheckBoxControItemEnable
     * @param value 1使能 0不使能
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 扫描预处理模块列表，然后设置列表中模块使能
     */
    void CheckBoxControItemEnable(int value);
    /**
     * @brief SetItemEnable
     * @param flag
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 设置列表中模块使能
     */
    void SetItemEnable(int flag);
    /**
     * @brief PaintPicPoint
     * @return
     * @author szj
     * @date 2017/6/22
     * @note 描点(边沿点，轮廓点等）
     */
    void PaintPicPoint();

    QString GetStrInfor(int taskId);
    void ListInfo(QString strInfo);
    void ListCurrentRowInfo();
    void InitAreaLimit();
};

#endif // PREMAIN_H
