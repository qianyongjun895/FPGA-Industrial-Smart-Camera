#ifndef LABELHEIGHTADJUST_H
#define LABELHEIGHTADJUST_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

class LabelHeightAdjust: public QLabel
{
	Q_OBJECT

public:
	explicit LabelHeightAdjust(QWidget *parent = 0);

	void SetSize(int iwidth, int iheigth);
	void Up();
	void Down();

	typedef void(*fun)(int, int, void*);
	void *m_p_this;
	fun m_fun;
	void setCallBack(void(*fun)(int, int, void*), void *pthis);

	void setLineVaule(double, double);	
	int getLine1Value() const { return m_y1; }
	int getLine2Value() const { return m_y2; }

	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;

	int m_width;
	int m_heigth;
	int lineKind; //1 ,2;
    int m_r;
    int m_g;
    int m_b;
    void SetRGB(int r,int g,int b);
	void setTextShowEnable(bool b) { showtextEnable = b; }
	void SetEditPaint(bool bflag);
    void SetLowHighYValue(int yLow,int yHight);
    void SetVtPic(QVector<int>vtPic);
signals:
	void LineMovedSignal();
    void SignalI(int iMax,int iMin);
public slots :


protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual  void  mouseReleaseEvent(QMouseEvent *e);
	virtual void paintEvent(QPaintEvent *e);

private:
	double df_line1;	
	double df_line2;
	bool showtextEnable;
	bool m_b_edit_paint;
    QTime startTime;
    QTime stopTime;
    QVector<int>m_vt_i_pic;
};

#endif // LABLISTPIC_H
