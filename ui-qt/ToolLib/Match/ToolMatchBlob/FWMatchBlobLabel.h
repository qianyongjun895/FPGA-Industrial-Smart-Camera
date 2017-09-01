/**
  * @file  [FWMatchBlobLabel.h]
  * @brief  FWMatchBlobLabel
  * @author  <dgq>
  * @date  <2017/5/23>
  * @version  <1.0>
  * @note  Blob编辑OSD
  * detailed  description
  */
#ifndef FWMATCHBLOBLABEL_H
#define FWMATCHBLOBLABEL_H


#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

/*blob画OSD需要的数据结构*/
typedef struct
{
    QVector<QPoint> m_vt_point;
    QVector<float> m_angle;
    QVector<float> m_blob_heigth;
    QVector<float> m_blob_width;

}BLOB_OSD_EDIT;

class FWMatchBlobLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FWMatchBlobLabel(QWidget *parent = 0);
    ~FWMatchBlobLabel();
    /**
     * @brief SetOSDData
     * @param data blob取样、计算成功后画OSD需要的数据
     * @author dgq
     * @note 取样成功后将取样、计算得到的结果在OSD上显示出来
     */
    void SetOSDData(BLOB_OSD_EDIT *data);
    void SetPenColor(void *pen_color);
protected:
    void paintEvent(QPaintEvent *e);

private:
    BLOB_OSD_EDIT m_data;
    /**
     * @brief DrawArrow
     * @param painter QPainter指针
     * @param lastPoint 箭头的起点
     * @param endPoint 箭头的终点
     * @param iArrowLen 箭头的两条线段的长度
     * @author szj
     * @note 画blob长轴方向的箭头
     */
    void DrawArrow(QPainter *painter,QPoint lastPoint,QPoint endPoint,float iArrowLen);
    void *m_pen_color;

};

#endif // FWMATCHBLOBLABEL_H
