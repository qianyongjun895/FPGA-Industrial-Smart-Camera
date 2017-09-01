#ifndef BASEPOINTWIDGET_H
#define BASEPOINTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <QPushButton>
#include "FWMatchBasePointLabel.h"
#include "BasePointGlobal.h"

namespace Ui {
class BasePointWidget;
}

class BasePointWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BasePointWidget(QWidget *parent = 0);
    ~BasePointWidget();
    QPoint Get_Image_Pos();

    void Init_Input_Ptr(void *ptr, int i_step_index, int new_flag, void *pen_color);
    int Set_Parameter_To_Ram();
private slots:
    void on_btnMoveUp_pressed();

    void on_btnMoveDown_pressed();

    void on_btnMoveLeft_pressed();

    void on_btnMoveRight_pressed();
    void GetCurrentTime();

    void ShowCurrentPointCoordinate(int index, QPoint point);
    void on_btnPrePoint_clicked();

    void on_btnNextPoint_clicked();

    void on_btnPointSub_clicked();

    void on_btnPointAdd_clicked();



private:
    Ui::BasePointWidget *ui;
    QLabel *m_label;
    BASEPOINT_INPUT_PARAM *pInputPara;
    QTime startTime;
    QTime stopTime;
    int m_current_index;
    int m_step_index;
    BASEPOINT_INPUT_PARAM m_base_point_input;



    void SetBtnRepeatParam(QPushButton *btn);
    void InitData();
};

#endif // BASEPOINTWIDGET_H
