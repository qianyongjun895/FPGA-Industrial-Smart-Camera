#ifndef LABELGRAYHISTOGRAM_H
#define LABELGRAYHISTOGRAM_H


#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

class LabelGrayHistogram: public QLabel
{
	Q_OBJECT

public:
    explicit LabelGrayHistogram(QWidget *parent = 0);
    void SetGrade(unsigned int *gradeArr,int size,int mode,int times);
signals:

public slots :

protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual  void  mouseReleaseEvent(QMouseEvent *e);
	virtual void paintEvent(QPaintEvent *e);

private:
    unsigned int m_max;
    unsigned int m_grade[2560];
    int m_mode; // 0全图 1列 2行
    int m_size;
    int m_times;
    void PaintGray(QPainter *painter);
    void PaintByColoum(QPainter *painter);
    void PaintByRow(QPainter *painter);
};

#endif // LABLISTPIC_H
