/**
  * @file  [TaskListStepWidget.h]
  * @brief  TaskListStepWidget
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef AREASELECTDIALOG_H
#define AREASELECTDIALOG_H

#include <QDialog>
#include "PreBasicHead.h"
#include<QTimer>
#include "AcceCommon.h"

namespace Ui {
class AreaSelectDialog;
}
/**
  * @class  <AreaSelectDialog>  [AreaSelectDialog.h]  [AreaSelectDialog]
  * @brief  区域筛选预处理模块
  * @author  <szj>
  * @note
  * detailed  description
  */
class AreaSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AreaSelectDialog(QWidget *parent = 0);
    ~AreaSelectDialog();
    int m_color_select_task_id;
    int m_step;
    void *m_pre_ptr;
    void *pen;
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 初始化区域筛选数据
     */
    void IniData();
    /**
     * @brief IniPolygon
     * @author szj
     * @param value 多边形类型（3，4，5，6，7，8）
     * @param ibEnable 取反标志
     * @param p_point_arr 多边形点坐标
     * @date 2017/05/08
     * @note 初始化区域筛选多边形数据
     */
    void IniPolygon(unsigned char value,int ibEnable,void *p_point_arr);
    /**
     * @brief IniPolygonOsdPoint
     * @author szj
     * @param value 多边形类型（3，4，5，6，7，8）
     * @param p_point_arr 多边形点坐标
     * @param ibEnable 取反标志
     * @date 2017/05/08
     * @note 初始化区域筛选多边形osd数据
     */
    void IniPolygonOsdPoint(int value,void *p_point_arr,int ibEnable);
    /**
     * @brief IniCircleData
     * @author szj
     * @param ibEnable 取反标志
     * @param rOut 外圆环半径
     * @param rIn 内圆环半径
     * @param x  圆环中心(x坐标）
     * @param y  圆环中心(y坐标）
     * @date 2017/05/08
     * @note 初始化区域筛选圆环数据
     */
    void IniCircleData(int ibEnable,int rOut,int rIn,int x, int y);
    /**
     * @brief SetDataToLib
     * @author szj
     * @date 2017/05/08
     * @note 保存数据
     */
    void SetDataToLib();
private slots:
    void on_btnOK_clicked();

    void on_btnQuit_clicked();

    void on_btnRect_clicked();

    void on_btnCircle_clicked();

    void on_btnRing_clicked();

    void on_btnPolygon_clicked();

    void on_bntDel_clicked();

    void on_tableWidgetTool_clicked(const QModelIndex &index);

    void on_btnPolygonAddPoint_clicked();

    void on_btnPolygonSubPoint_clicked();

    void on_btnPolygonPrev_clicked();

    void on_btnPolygonNext_clicked();

    void btnPolygonUp();

    void btnPolygonRight();

    void btnPolygonDown();

    void btnPolygonLeft();

    void btnAddRadiusOut();

    void btnSubRadiusOut();

    void btnCircleUPOut();

    void btnCircleDownOut();

    void btnCircleLeftOut();

    void btnCircleRightOut();

    void btnAddRadiusIn();

    void btnSubRadiusIn();

    void on_btnAddRadiusOut_pressed();

    void on_btnAddRadiusOut_released();

    void on_btnSubRadiusOut_pressed();

    void on_btnSubRadiusOut_released();

    void on_btnAddRadiusIn_pressed();

    void on_btnAddRadiusIn_released();

    void on_btnSubRadiusIn_released();

    void on_btnCircleUPOut_pressed();

    void on_btnCircleUPOut_released();

    void on_btnCircleRightOut_pressed();

    void on_btnCircleRightOut_released();

    void on_btnCircleDownOut_pressed();

    void on_btnCircleDownOut_released();

    void on_btnCircleLeftOut_pressed();

    void on_btnCircleLeftOut_released();

    void on_btnPolygonLeft_pressed();

    void on_btnPolygonLeft_released();

    void on_btnPolygonUp_pressed();

    void on_btnPolygonUp_released();

    void on_btnPolygonRight_pressed();

    void on_btnPolygonRight_released();

    void on_btnPolygonDown_pressed();

    void on_btnPolygonDown_released();

    void SlotValueChange(TOOL_KIND kind);

    void on_btnOrNot_clicked();

    void on_btnSubRadiusIn_pressed();
    void updatImage(QPixmap pix);

    void on_btnRectUp_clicked();

    void on_btnRectDown_clicked();

    void on_btnRectLeft_clicked();

    void on_btnRectRight_clicked();

    void on_btnRectUp_pressed();

    void on_btnRectUp_released();

    void on_btnRectDown_pressed();

    void on_btnRectDown_released();

    void on_btnRectLeft_pressed();

    void on_btnRectLeft_released();

    void on_btnRectRight_pressed();

    void on_btnRectRight_released();

private:
    Ui::AreaSelectDialog *ui;
    QString GetStrXY(int ix, int iy);
    void ListImageBySelect();
    QVector<TOOL_KIND>m_vt_tool_kind;
    QTimer *timerUpData;
    int m_iPresstimes;
    int m_i_poloygon_num;
    int m_i_circle_num;
    int m_image_scale;
    SELECT_MODEL_CFG m_select_model_cfg;

    /**
     * @brief GetOctagonVertexEn
     * @author szj
     * @date 2017/05/08
     * @note 八边形顶点使能参数
     */
    int GetOctagonVertexEn(int num);  
    /**
     * @brief ClearOsdData
     * @author szj
     * @date 2017/05/08
     * @note 清除osd数据
     */
    void ClearOsdData();
    /**
     * @brief IniToolTable
     * @author szj
     * @date 2017/05/08
     * @note 初始化osd工具列表
     */
    void IniToolTable();
    /**
     * @brief RemoveToolTableData
     * @author szj
     * @date 2017/05/08
     * @note 删除osd工具列表
     */
    void RemoveToolTableData();
    /**
     * @brief AddToolTableData
     * @param strName osd名称(矩形，圆环，多边形等)
     * @param TOOL_KIND osd类型
     * @author szj
     * @date 2017/05/08
     * @note 将osd类型添加到数据表格中
     */
    void AddToolTableData(QString strName,TOOL_KIND toolKind);

    /**
     * @brief FindToolIndex
     * @param row 数据列表选中行
     * @author szj
     * @date 2017/05/08
     * @note 查找当前行osd工具在同类osd集合中的位置
     */
    int FindToolIndex(int row);
    /**
     * @brief ListOsdAdjustWidget
     * @param TOOL_KIND osd类型
     * @author szj
     * @date 2017/05/08
     * @note 显示当前类型osd数据
     */
    void ListOsdAdjustWidget(TOOL_KIND toolKind);
    /**
     * @brief SetLabelXY
     * @author szj
     * @date 2017/05/08
     * @note 显示多边形坐标点
     */
    void SetLabelXY();
    /**
     * @brief SetLabelXYVisable
     * @author szj
     * @date 2017/05/08
     * @note 隐藏多边形坐标控件
     */
    void SetLabelXYVisable();
};

#endif // AREASELECTDIALOG_H
