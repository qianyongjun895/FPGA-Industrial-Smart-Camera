#ifndef POLARWIDGET_H
#define POLARWIDGET_H

#include <QWidget>
#include "FWMatchPolarLabel.h"
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include "PolarMatchGlobal.h"

namespace Ui {
class PolarWidget;
}

class PolarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PolarWidget(QWidget *parent = 0);
    ~PolarWidget();
    QPoint Get_Image_Pos();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_radioButton_Global_clicked();

    void on_radioButton_Part_clicked();

    void ShowAngleValue(double angle, int kind);
    void ShowRadiuValue(int r, int kind);
    void on_btnAddRadiusIn_pressed();

    void on_btnSubRadiusIn_pressed();

    void on_btnAddRadiusOut_pressed();

    void on_btnSubRadiusOut_pressed();

    void on_btnAddSamplingAngle_pressed();

    void on_btnSubSamplingAngle_pressed();

    void on_btnAddSearchAngle_pressed();

    void on_btnSubSearchAngle_pressed();

    void on_SimilarlityDownBtn_pressed();
    void on_SimilarlityUpBtn_pressed();
    void on_SimilarlitySlider_valueChanged(int value);

private:
    Ui::PolarWidget *ui;
    QLabel *m_label;
    QTime startTime;
    QTime stopTime;
    int m_index;
    POLAR_MATCH_INPUT_PARAM *pInputPara;
    int m_step_index;


    void SetBtnRepeatParam(QPushButton *btn);
    void InitData();
    void GetCurrentTime();
    void GetCompassData();
};

#endif // POLARWIDGET_H
