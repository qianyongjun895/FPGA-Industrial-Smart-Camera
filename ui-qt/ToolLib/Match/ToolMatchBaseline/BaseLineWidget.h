#ifndef BASELINEWIDGET_H
#define BASELINEWIDGET_H

#include <QWidget>
#include "FWMatchBaseLineLabel.h"
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include "BaseLineGlobal.h"

namespace Ui {
class BaseLineWidget;
}

class BaseLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseLineWidget(QWidget *parent = 0);
    ~BaseLineWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
private slots:
    void on_btnMoveUp_pressed();

    void on_btnMoveDown_pressed();

    void on_btnMoveLeft_pressed();

    void on_btnMoveRight_pressed();

    void GetCurrentTime();
    void ShowCurrentPoint1Coordinate(QPoint point, int index);
    void ShowCurrentPoint2Coordinate(QPoint point,int index);
    void on_btnLineSub_clicked();

    void on_btnLineAdd_clicked();

    void on_btnPreLine_clicked();

    void on_btnNextLine_clicked();

    void on_radioButton_Point1_clicked();

    void on_radioButton_Point2_clicked();

private:
    Ui::BaseLineWidget *ui;
    QLabel *m_label;
    QTime startTime;
    QTime stopTime;
    int m_index;
    BASE_LINE_INPUT_PARAM *pInputPara;
    int m_step_index;


    void SetBtnRepeatParam(QPushButton *btn);
    void InitData();
};

#endif // BASELINEWIDGET_H
