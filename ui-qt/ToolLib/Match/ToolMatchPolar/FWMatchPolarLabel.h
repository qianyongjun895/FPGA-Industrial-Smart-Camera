/**
  * @file  [FWMatchPolarLabel.h]
  * @brief  FWMatchPolarLabel
  * @author  <dgq>
  * @date  <2017/7/25>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef FWMATCHPOLARLABEL_H
#define FWMATCHPOLARLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

const QPointF ClickArea(10, 10);
//获取方式，全园范围
#define SELECT_TYPE_ALL
class FWMatchPolarLabel : public QLabel
{
    Q_OBJECT

public:

    explicit FWMatchPolarLabel(QWidget *parent = 0);
    ~FWMatchPolarLabel();

    //设置关联圆半径大小
    void setRadius(int r);
    //设置外圆半径大小
    void setRadiusMin(int r);
    //设置内圆半径大小
    void setRadiusMax(int r);
    //设置是否全局搜索
    void setSearchMode(int b);
    //获取关联圆半径大小
    int getRadius(void);
    //获取内圆半径大小
    int getRadiusMin(void);
    //获取外圆半径大小
    int getRadiusMax(void);
    //获取取样起始角度
    float getLearnStartAngle(void);
    //获取取样终止角度
    float getLearnEndAngle(void);
    //获取搜索起始角度
    float getSearchStartAngle(void);
    //获取搜索终止角度
    float getSearchEndAngle(void);
    //设置取样起始角度
    void setLearnStartAngle(float a);
    //设置取样终止角度
    void setLearnEndAngle(float a);
    //设置搜索起始角度
    void setSearchStartAngle(float a);
    //设置搜索终止角度
    void setSearchEndAngle(float a);
    void setCenterPoint(QPoint centerPoint);
    void AddRadiuMin(int value);
    void SubRadiuMax(int value);
    void AddRadiuMax(int value);
    void SubRadiuMin(int value);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
//    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void signalPointsChange(double angle,int kind);
    void signalRadiuChange(int angle,int kind);
private:
    int radius;//关联园半径
    int radiusMin;//内圆半径
    int radiusMax;//  外圆半径
    int Global;//是否全局搜索
    QPointF center;//中点
    QPointF m_center;
    QPoint PointA1;
    QPoint PointA2;
    QPoint PointB1;
    QPoint PointB2;
    int selectRect;
    double angle[4];
    QRectF ClickRect[4];
    bool Editing;
    QRectF m_WorkRect;
    void *m_pen_color;

};

#endif // FWMATCHPOLARLABEL_H
