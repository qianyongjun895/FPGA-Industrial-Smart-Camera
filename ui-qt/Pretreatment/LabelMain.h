/**
  * @file  [LabelMain.h]
  * @brief  LabelMain
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef LABELMAIN_H
#define LABELMAIN_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

/**
  * @class  <LabelMain>  [LabelMain.h]  [LabelMain]
  * @brief  预处理模块osd
  * @author  <szj>
  * @note
  * detailed  description
  */
class LabelMain: public QLabel
{
	Q_OBJECT

    typedef struct {
        unsigned short x;
        unsigned short y;
        int theta;
    } FPGA_EDGE_CALC_POINT;

public:
    explicit LabelMain(QWidget *parent = 0);
    /**
     * @brief Set_startX
     * @param x 设置图像起始x坐标
     * @author szj
     * @date 2017/05/08
     * @note 设置图像边界
     */
    void Set_startX(int x);
    /**
     * @brief Set_endX
     * @param x 设置图像终止x坐标
     * @author szj
     * @date 2017/05/08
     * @note 设置图像边界
     */
    void Set_endX(int x);
    /**
     * @brief Set_startY
     * @param y 设置图像起始y坐标
     * @author szj
     * @date 2017/05/08
     * @note 设置图像边界
     */
    void Set_startY(int y);
    /**
     * @brief Set_end
     * @param y 设置图像终止y坐标
     * @author szj
     * @date 2017/05/08
     * @note 设置图像边界
     */
    void Set_endY(int y);
    /**
     * @brief SetEdgePtr
     * @param ptr 边沿点指针
     * @author szj
     * @date 2017/05/08
     * @note 设置边沿点提取指针
     */
    void SetEdgePtr(void *ptr);
    /**
     * @brief SetSkeletonMatchPtr
     * @param ptr 轮廓点指针
     * @author szj
     * @date 2017/05/08
     * @note 设置轮廓点指针
     */
    void SetSkeletonMatchPtr(void *ptr);
    /**
     * @brief SetHWCVga2Sub
     * @param pix 图像点倍数
     * @author szj
     * @date 2017/05/08
     * @note 设置倍数
     */
    void SetHWCVga2Sub(int mode);
    void SetPenColor(void *pen);
signals:

public slots :
    void paintPointSlot(QVector<int>vt);

protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual  void  mouseReleaseEvent(QMouseEvent *e);
	virtual void paintEvent(QPaintEvent *e);

private:
    int m_start_x;
    int m_start_y;
    int m_end_x;
    int m_end_y;
    QVector<int>m_vt;
    void *m_edge_ptr;
    void *m_skeletonMatch_ptr;
    void *m_pen_color;
    int m_scaleMode;
    int m_pixSel;
    /**
     * @brief paintEdgePoint
     * @param painter 绘图指针
     * @author szj
     * @date 2017/05/08
     * @note 绘边沿提取点
     */
    void paintEdgePoint(QPainter *painter);
    /**
     * @brief Set_startX
     * @param painter 绘图指针
     * @author szj
     * @date 2017/05/08
     * @note 绘轮廓点
     */
    void paintSkeletonMatch(QPainter *painter);


};

#endif // LABLISTPIC_H
