/**
  * @file  [FWMatchCircleLabel.h]
  * @brief  FWMatchCircleLabel
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef FWMATCHCIRCLELABEL_H
#define FWMATCHCIRCLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

/**
  * @class  <FWMatchCircleLabel>  [FWMatchCircleLabel.h]  [FWMatchCircleLabel]
  * @brief  圆形定位编辑osd
  * @author  <szj>
  * @note
  * detailed  description
  */
class FWMatchCircleLabel : public QLabel
{
    Q_OBJECT

public:

    explicit FWMatchCircleLabel(QWidget *parent = 0);
    ~FWMatchCircleLabel();
    /**
     * @brief GetCenter
     * @return 返回圆心
     * @author szj
     * @date 2017/05/08
     * @note 获取圆心
     */
    QPoint GetCenter();
    /**
     * @brief SetCenter
     * @param center 圆心
     * @author szj
     * @date 2017/05/08
     * @note 设置圆心
     */
    void SetCenter(QPoint center);
    /**
     * @brief SetR
     * @param r 半径
     * @author szj
     * @date 2017/05/08
     * @note 设置半径
     */
    void SetR(int r);
    /**
     * @brief GetR
     * @return 返回圆半径
     * @author szj
     * @date 2017/05/08
     * @note 获取圆半径
     */
    int GetR(){return m_r;}

    /**
     * @brief KeyMoveUp
     * @param value 上移像素值
     * @author szj
     * @date 2017/05/08
     * @note 上移
     */

    void KeyMoveUp(int value = 1);
    /**
     * @brief KeyMoveUp
     * @param value 下移像素值
     * @author szj
     * @date 2017/05/08
     * @note 下移
     */
    void KeyMoveDown(int value = 1);
    /**
     * @brief KeyMoveUp
     * @param value 左移像素值
     * @author szj
     * @date 2017/05/08
     * @note 左移
     */
    void KeyMoveLeft(int value = 1);
    /**
     * @brief KeyMoveUp
     * @param value 右移像素值
     * @author szj
     * @date 2017/05/08
     * @note 右移
     */
    void KeyMoveRight(int value =1);
    void SetSample(QPoint point,int r);
    void SetPenColor(void *pen_color);
signals:
    void signalsCenter();

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    QPoint m_center;
    QPoint m_press_point;
    int m_r;
    int m_b_move;
    QPoint m_sample_center;
    int m_sample_r;
     void *m_pen_color;

};

#endif // FWMATCHLINELABEL_H
