#ifndef IOOUTPUTWIDGET_H
#define IOOUTPUTWIDGET_H

#include <QWidget>
#include "ListWidgetIOOutputItem.h"
#include "../../../include/lzynq_include/io.h"
#include <QTimer>
namespace Ui {
class IOOutputWidget;
}

class IOOutputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOOutputWidget(QWidget *parent = 0);
    ~IOOutputWidget();

private slots:
    void on_IO1Slider_sliderMoved(int position);

    void on_IO2Slider_sliderMoved(int position);

    void on_IO3Slider_sliderMoved(int position);

    void on_IO4Slider_sliderMoved(int position);

    void on_FlashSlider_sliderMoved(int position);

    void on_tabWidget_currentChanged(int index);

    void on_BasisButton_clicked();

    void on_AdvancedButton_clicked();

    void on_IO4Slider_sliderReleased();

    void on_IO3Slider_sliderReleased();

    void on_IO2Slider_sliderReleased();

    void on_IO1Slider_sliderReleased();

    void on_FlashSlider_sliderReleased();

    void on_btnIO1Sub_clicked();
    void on_btnIO2Sub_clicked();
    void on_btnIO3Sub_clicked();
    void on_btnIO4Sub_clicked();
    void on_FlashSub_clicked();


    void on_btnIO1Sub_pressed();
    void on_btnIO1Sub_released();

    void on_btnIO2Sub_pressed();
    void on_btnIO2Sub_released();

    void on_btnIO3Sub_pressed();
    void on_btnIO3Sub_released();

    void on_btnIO4Sub_pressed();
    void on_btnIO4Sub_released();

    void on_FlashSub_pressed();
    void on_FlashSub_released();

    void on_btnIO1Add_clicked();
    void on_btnIO2Add_clicked();
    void on_btnIO3Add_clicked();
    void on_btnIO4Add_clicked();
    void on_FlashAdd_clicked();

    void on_btnIO1Add_pressed();
    void on_btnIO1Add_released();

    void on_btnIO2Add_pressed();
    void on_btnIO2Add_released();

    void on_btnIO3Add_pressed();
    void on_btnIO3Add_released();

    void on_btnIO4Add_pressed();
    void on_btnIO4Add_released();

    void on_FlashAdd_pressed();
    void on_FlashAdd_released();


    void on_radioButton_IO1_high_clicked();

    void on_radioButton_IO1_low_clicked();

    void on_radioButton_IO2_high_clicked();

    void on_radioButton_IO2_low_clicked();

    void on_radioButton_IO3_high_clicked();

    void on_radioButton_IO3_low_clicked();

    void on_radioButton_IO4_high_clicked();

    void on_radioButton_IO4_low_clicked();

    void on_radioButton_Flash_high_clicked();

    void on_radioButton_Flash_low_clicked();

    void on_btnIO1OutputTest_clicked();

    void on_btnIO2OutputTest_clicked();

    void on_btnIO3OutputTest_clicked();

    void on_btnIO4OutputTest_clicked();

    void on_btnFlashOutputTest_clicked();

private:
    Ui::IOOutputWidget *ui;
    int Model_Flag;///<0:基础; 1:高级
    int long_press_value;
    QTimer Long_Press_Time;
    IO_OUTPUT_CONFIG IO_output_param;
    FLASH_OUTPUT_CONFIG Flash_output_param;
    void AddIOOutputSetItem(ListWidgetIOOutputItem *item);
    void LoadTaskIOOutputItem();
    void ClearListWidget();
    void SetLongPressValue(int value);
    void GetIOParam();
    void GetFlashParam();
    void SaveIOOutputParam();
};

#endif // IOOUTPUTWIDGET_H
