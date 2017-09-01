/**
  * @file  [FWAreaSelect.h]
  * @brief  FWAreaSelect
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */

#ifndef FWAREASELECT_H
#define FWAREASELECT_H

#include <QObject>
#include <QLabel>
#include "PolygonTool.h"
#include "RingTool.h"
#include "RectTool.h"
#include <QVector>
#include "PreBasicHead.h"
/**
  * @class  <FWAreaSelect>  [FWAreaSelect.h]  [FWAreaSelect]
  * @brief  区域筛选osd
  * @author  <szj>
  * @note
  * detailed  description
  */
class FWAreaSelect : public QLabel
{
    Q_OBJECT
public:

    explicit FWAreaSelect(QWidget *parent = 0);
    /**
     * @brief AddTool
     * @param TOOL_KIND osd类型
     * @author szj
     * @date 2017/05/08
     * @note 增加osd类型
     */
    void AddTool(TOOL_KIND toolKind);
    /**
     * @brief IniPolygonPoint
     * @param index osd类型
     * @param ipointNum osd类型
     * @param x 多边形x坐标
     * @param y 多边形y坐标
     * @param flag 取反标志
     * @author szj
     * @date 2017/05/08
     * @note 初始化多边形
     */
    void IniPolygonPoint(int index,int ipointNum,int x ,int y,int flag);
    /**
     * @brief DeleteTool
     * @param TOOL_KIND 工具类型
     * @param index 工具类型所在集合中的位置
     * @author szj
     * @date 2017/05/08
     * @note 删除工具
     */
    void DeleteTool(TOOL_KIND toolKind,int index);
    /**
     * @brief SelectTool
     * @param TOOL_KIND 工具类型
     * @param index 工具类型所在集合中的位置
     * @author szj
     * @date 2017/05/08
     * @note 选择工具
     */
    void SelectTool(TOOL_KIND toolKind,int index);
    /**
     * @brief AddPolygonPoint
     * @author szj
     * @date 2017/05/08
     * @note 增加多边形点
     */
    void AddPolygonPoint();
    /**
     * @brief SubPolygonPoint
     * @author szj
     * @date 2017/05/08
     * @note 删除多边形点
     */
    void SubPolygonPoint();
    /**
     * @brief GetPolygonPointNum
     * @return 返回多边形点的数量
     * @author szj
     * @date 2017/05/08
     * @note 获取多边形点的数量
     */
    int GetPolygonPointNum();
    /**
     * @brief GetPolygonPointNum
     * @param i 工具类型所在集合中的位置
     * @return 返回多边形点的坐标
     * @author szj
     * @date 2017/05/08
     * @note 获取多边形坐标点
     */
    QPoint GetPolyGonPoint(int i);
    /**
     * @brief UpPolygonAdjust
     * @param index 工具类型所在集合中的位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形坐标点上移
     */
    void UpPolygonAdjust(int index);
    /**
     * @brief DownPolygonAdjust
     * @param index 工具类型所在集合中的位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形坐标点下移
     */
    void DownPolygonAdjust(int index);
    /**
     * @brief LeftPolygonAdjust
     * @param index 工具类型所在集合中的位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形坐标点左移
     */
    void LeftPolygonAdjust(int index);
    /**
     * @brief LeftPolygonAdjust
     * @param index 工具类型所在集合中的位置
     * @author szj
     * @date 2017/05/08
     * @note 多边形坐标点右移
     */
    void RightPolygonAdjust(int index);
    /**
     * @brief SetRingROut
     * @param r 圆环外半径
     * @author szj
     * @date 2017/05/08
     * @note 设置圆环外半径
     */
    void SetRingROut(int r);
    /**
     * @brief SetRingRIn
     * @param r 圆环内半径
     * @author szj
     * @date 2017/05/08
     * @note 设置圆环内半径
     */
    void SetRingRIn(int r);
    /**
     * @brief SetRingCenter
     * @param x 圆中心坐标(x)
     * @param y 圆中心坐标(y)
     * @author szj
     * @date 2017/05/08
     * @note 设置圆环中心点
     */
    void SetRingCenter(int x,int y);
    /**
     * @brief GetRingROut
     * @return 返回外圆环半径
     * @author szj
     * @date 2017/05/08
     * @note 获取外圆环半径
     */
    int GetRingROut();
    /**
     * @brief GetRingRIn
     * @return 返回内圆环半径
     * @author szj
     * @date 2017/05/08
     * @note 获取内圆环半径
     */
    int GetRingRIn();
    /**
     * @brief GetRingCenter
     * @return 返回圆中心坐标
     * @author szj
     * @date 2017/05/08
     * @note 获取圆中心坐标
     */
    QPoint GetRingCenter();
    /**
     * @brief GetRingOrNot
     * @return 返回圆环取反标志
     * @author szj
     * @date 2017/05/08
     * @note 获取圆环取反标志
     */
    bool GetRingOrNot();
    /**
     * @brief GetPolygonOrNot
     * @return 返回多边形取反标志
     * @author szj
     * @date 2017/05/08
     * @note 获取多边形取反标志
     */
    bool GetPolygonOrNot();
    /**
     * @brief SetRingOrNot
     * @param flag 取反标志
     * @author szj
     * @date 2017/05/08
     * @note 设置圆环取反标志
     */
    void SetRingOrNot(bool flag);
    /**
     * @brief SetPolygonOrNot
     * @param flag 取反标志
     * @author szj
     * @date 2017/05/08
     * @note 设置多边形取反标志
     */
    void SetPolygonOrNot(bool flag);
    /**
     * @brief GetRectOrNot
     * @author szj
     * @date 2017/05/08
     * @note 获取矩形取反标志
     */
    bool GetRectOrNot();
    /**
     * @brief GetRectOrNot
     * @param flag 取反标志
     * @author szj
     * @date 2017/05/08
     * @note 设置矩形取反标志
     */
    void SetRectOrNot(bool flag);
    /**
     * @brief GetRectPoint
     * @param i 工具类型所在集合中的位置
     * @return 返回矩形点的坐标
     * @author szj
     * @date 2017/05/08
     * @note 获取矩形坐标点
     */
    QPoint GetRectPoint(int i);
    /**
     * @brief IniRectPoint
     * @param x1 矩形左顶上点x坐标
     * @param y1 矩形左顶上点y坐标
     * @param x2 矩形右下点x坐标
     * @param y2 矩形右下点y坐标
     * @param flag 取反标志
     * @author szj
     * @date 2017/05/08
     * @note 初始化矩形osd
     */
    void IniRectPoint(int x1, int y1, int x2 , int y2, int flag);
    /**
     * @brief UpRectAdjust
     * @param kind 1 左上顶点 2右下点
     * @param value 移动步进值
     * @author szj
     * @date 2017/05/08
     * @note 坐标点上移
     */
    void UpRectAdjust(int kind,int value =1);
    /**
     * @brief DownRectAdjust
     * @param kind 1 左上顶点 2右下点
     * @param value 移动步进值
     * @author szj
     * @date 2017/05/08
     * @note 坐标点下移
     */
    void DownRectAdjust(int kind,int value=1);
    /**
     * @brief LeftRectAdjust
     * @param kind 1 左上顶点 2右下点
     * @param value 移动步进值
     * @author szj
     * @date 2017/05/08
     * @note 坐标点左移
     */
    void LeftRectAdjust(int kind,int value=1);
    /**
     * @brief RightRectAdjust
     * @param kind 1 左上顶点 2右下点
     * @param value 移动步进值
     * @author szj
     * @date 2017/05/08
     * @note 坐标点右移
     */
    void RightRectAdjust(int kind,int value=1);
    void SetLimit(int startx,int endx,int starty,int endy);
    void SetPen(void *pen);
signals:
    void signalsValueChange(TOOL_KIND kind);
public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    QVector<PolygonTool> m_vt_PolygonTool;
    QVector<RingTool>m_vt_RingTool;
    QVector<RectTool>m_vt_rectTool;
    int m_current_num;
    TOOL_KIND m_toolKind;
    int m_index;
    int m_start_x;
    int m_end_x;
    int m_start_y;
    int m_end_y;
    void *m_pen;
    /**
     * @brief AddPolygonTool
     * @author szj
     * @date 2017/05/08
     * @note 增加多边形工具
     */
    void AddPolygonTool();
    /**
     * @brief AddRingTool
     * @author szj
     * @date 2017/05/08
     * @note 增加圆环工具
     */
    void AddRingTool();
    /**
     * @brief RightRectAdjust
     * @author szj
     * @date 2017/05/08
     * @note 增加矩形工具
     */
    void AddRectTool();
    /**
     * @brief SetSelectFlag
     * @author szj
     * @date 2017/05/08
     * @note 设置当前选中的图形工具
     */
    void SetSelectFlag();

};

#endif // FWAREACENTERTOOLEDIT_H
