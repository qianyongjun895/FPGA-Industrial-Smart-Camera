/**
  * @file  [ImageSetWidget.h]
  * @brief  ImageSetWidget
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef IMAGESETWIDGET_H
#define IMAGESETWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
namespace Ui {
class ImageSetWidget;
}
/**
  * @class  <ImageSetWidget>  [ImageSetWidget.h]  [ImageSetWidget]
  * @brief  图像设置
  * @author  <szj>
  * @note
  * detailed  description
  */
class ImageSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageSetWidget(QWidget *parent = 0);
    ~ImageSetWidget();

private slots:
    void on_btnSubGain_clicked();
    void on_btnAddGain_clicked();
    void on_btnSubExplosion_clicked();
    void on_btnAddExplosion_clicked();
    void on_btnMsSubExplosion_clicked();
    void on_btnMsAddExplosion_clicked();

    void on_btnSubGain_pressed();
    void on_btnSubGain_released();
    void on_btnAddGain_pressed();
    void on_btnAddGain_released();
    void on_btnSubExplosion_pressed();
    void on_btnSubExplosion_released();
    void on_btnAddExplosion_pressed();
    void on_btnAddExplosion_released();
    void on_btnMsSubExplosion_pressed();
    void on_btnMsSubExplosion_released();
    void on_btnMsAddExplosion_pressed();
    void on_btnMsAddExplosion_released();

    void on_horizontalSliderGain_valueChanged(int value);
    void on_horizontalSliderExplosion_valueChanged(int value);
    void on_horizontalSliderMsExplosion_valueChanged(int value);
    void on_horizontalSliderMsExplosion_sliderPressed();
    void on_horizontalSliderMsExplosion_sliderReleased();
    void on_horizontalSliderExplosion_sliderPressed();
    void on_horizontalSliderExplosion_sliderReleased();
    void on_horizontalSliderGain_sliderPressed();
    void on_horizontalSliderGain_sliderReleased();

    //自动设置白平
    void on_btnStartTriger_clicked();
    //手动设置白平
    void on_btnByManual_clicked();
    void on_btnSuBRWB_clicked();

    void on_btnAddRWB_clicked();

    void on_btnSubBWB_clicked();

    void on_btnAddBWB_clicked();

    void on_horizontalSliderRWB_valueChanged(int value);

    void on_horizontalSliderRWB_sliderPressed();

    void on_horizontalSliderRWB_sliderReleased();

    void on_horizontalSliderBWB_sliderPressed();

    void on_horizontalSliderBWB_sliderReleased();

    void on_horizontalSliderBWB_valueChanged(int value);

    void on_btnSuBRWB_pressed();

    void on_btnSuBRWB_released();

    void on_btnAddRWB_pressed();

    void on_btnAddRWB_released();

    void on_btnSubBWB_pressed();

    void on_btnSubBWB_released();

    void on_btnAddBWB_pressed();

    void on_btnAddBWB_released();


    void LabelLineSlot(int kind);

    void on_btnSkeletonUpLine_clicked();

    void on_btnSkeletonDownLine_clicked();

    void on_btnSkeletonUpLine_pressed();

    void on_btnSkeletonUpLine_released();

    void on_btnSkeletonDownLine_pressed();

    void on_btnSkeletonDownLine_released();

    void on_radioButtonUpLineLimit_clicked();

    void on_radioButtonDownLineLimit_clicked();


    void on_tabWidget_tabBarClicked(int index);

    void on_radioButton_Normal_clicked();

    void on_radioButton_Left_Right_clicked();

    void on_radioButton_Up_Down_clicked();

    void on_radioButton_Both_clicked();

    void on_pushButton_Param_Save_clicked();

    void on_pushButton_Param_del_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_clear_Param_clicked();

private:
    Ui::ImageSetWidget *ui;
    int m_ini_first;
    QTimer *timerUpData;
    int m_iPresstimes;
    int m_key_state;
    QTime startTime;
    QTime stopTime;
    QTimer ClickTimer;
    void IniData();
    int IsTimeOut();
    unsigned char  m_rotate_type;

    void SetImageParam();
};

#endif // IMAGESETWIDGET_H
