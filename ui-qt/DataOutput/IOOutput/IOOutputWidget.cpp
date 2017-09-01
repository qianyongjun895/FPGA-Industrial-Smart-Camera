#include "IOOutputWidget.h"
#include "ui_IOOutputWidget.h"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include <QMessageBox>
#include <stdio.h>
#include <stdlib.h>
#include <QThread>
#include "IOInitGlobal.h"
IOOutputWidget::IOOutputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOOutputWidget)
{
    ui->setupUi(this);
    Model_Flag = -1;
    long_press_value = 0;
    memset(&IO_output_param, 0, sizeof(IO_OUTPUT_CONFIG));
    memset(&Flash_output_param, 0, sizeof(FLASH_OUTPUT_CONFIG));
    IO_Output_Config_Get(&IO_output_param);
    IO_output_param.IO_sum = 4;
    GetIOParam();
    Flash_Output_Config_Get(&Flash_output_param);
    GetFlashParam();
}

IOOutputWidget::~IOOutputWidget()
{
    SaveIOOutputParam();
    delete ui;
}

void IOOutputWidget::SaveIOOutputParam()
{
    int index = 0;
    for(index = 0; index < 4; index++){
        Set_IO_Width(index, IO_output_param.width[index]);
    }
    Set_IO_Valid_Flag(IO_output_param.IO_valid_flag);
    Set_Flash_Output_Param(Flash_output_param.flash_width, Flash_output_param.flash_valid_flag);
    IO_Config_Save();
}

void IOOutputWidget::GetIOParam()
{
    unsigned int mode = 0;
    Task_IO_OutPut_Mode_Get(&mode);
    if(mode == 0){
        ui->BasisButton->setChecked(true);
        ui->AdvancedButton->setChecked(false);
        Model_Flag = 0;
    }else{
        ui->BasisButton->setChecked(false);
        ui->AdvancedButton->setChecked(true);
        Model_Flag = 1;
    }

    ui->IO1Slider->setSliderPosition(IO_output_param.width[0]);
    ui->IO1PulseValue->setText(QString::number(IO_output_param.width[0]));
    if((IO_output_param.IO_valid_flag & OUTPUT_PIN_0) == OUTPUT_PIN_0){
        ui->radioButton_IO1_high->setChecked(true);
        ui->radioButton_IO1_low->setChecked(false);
    }else{
        ui->radioButton_IO1_high->setChecked(false);
        ui->radioButton_IO1_low->setChecked(true);
    }
    ui->IO2Slider->setSliderPosition(IO_output_param.width[1]);
    ui->IO2PulseValue->setText(QString::number(IO_output_param.width[1]));
    if((IO_output_param.IO_valid_flag & OUTPUT_PIN_1) == OUTPUT_PIN_1){
        ui->radioButton_IO2_high->setChecked(true);
        ui->radioButton_IO2_low->setChecked(false);
    }else{
        ui->radioButton_IO2_high->setChecked(false);
        ui->radioButton_IO2_low->setChecked(true);
    }

    ui->IO3Slider->setSliderPosition(IO_output_param.width[2]);
    ui->IO3PulseValue->setText(QString::number(IO_output_param.width[2]));
    if((IO_output_param.IO_valid_flag & OUTPUT_PIN_2) == OUTPUT_PIN_2){
        ui->radioButton_IO3_high->setChecked(true);
        ui->radioButton_IO3_low->setChecked(false);
    }else{
        ui->radioButton_IO3_high->setChecked(false);
        ui->radioButton_IO3_low->setChecked(true);
    }

    ui->IO4Slider->setSliderPosition(IO_output_param.width[3]);
    ui->IO4PulseValue->setText(QString::number(IO_output_param.width[3]));
    if((IO_output_param.IO_valid_flag & OUTPUT_PIN_3) == OUTPUT_PIN_3){
        ui->radioButton_IO4_high->setChecked(true);
        ui->radioButton_IO4_low->setChecked(false);
    }else{
        ui->radioButton_IO4_high->setChecked(false);
        ui->radioButton_IO4_low->setChecked(true);
    }
}

void IOOutputWidget::GetFlashParam()
{
    ui->FlashSlider->setSliderPosition(Flash_output_param.flash_width);
    ui->FlashValue->setText(QString::number(Flash_output_param.flash_width));
    if(Flash_output_param.flash_valid_flag == 1){
        ui->radioButton_Flash_high->setChecked(true);
        ui->radioButton_Flash_low->setChecked(false);
    }else{
        ui->radioButton_Flash_high->setChecked(false);
        ui->radioButton_Flash_low->setChecked(true);
    }
}

void IOOutputWidget::on_IO1Slider_sliderMoved(int position)
{
    ui->IO1PulseValue->setText(QString::number(position));
}

void IOOutputWidget::on_IO2Slider_sliderMoved(int position)
{
    ui->IO2PulseValue->setText(QString::number(position));
}

void IOOutputWidget::on_IO3Slider_sliderMoved(int position)
{
    ui->IO3PulseValue->setText(QString::number(position));
}

void IOOutputWidget::on_IO4Slider_sliderMoved(int position)
{
    ui->IO4PulseValue->setText(QString::number(position));
}

void IOOutputWidget::on_FlashSlider_sliderMoved(int position)
{
    ui->FlashValue->setText(QString::number(position));
}

void IOOutputWidget::AddIOOutputSetItem(ListWidgetIOOutputItem* item)
{
    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->TaskIOOutputListWidget->count();
    QListWidgetItem* list_item = new QListWidgetItem(ui->TaskIOOutputListWidget);
    ui->TaskIOOutputListWidget->setItemWidget(list_item, (QWidget*)item);
    ui->TaskIOOutputListWidget->item(size)->setSizeHint(QSize(240, 45));
    ui->TaskIOOutputListWidget->setCurrentRow(0);
}

void IOOutputWidget::ClearListWidget()
{
    int size = ui->TaskIOOutputListWidget->count();
    for(int i = size; i >= 0; i--)
    {
        QListWidgetItem * item = ui->TaskIOOutputListWidget->takeItem(i);
        delete item;
    }
}

void IOOutputWidget::LoadTaskIOOutputItem()
{
    ClearListWidget();
    char taskName[40];
    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(i+1, taskName);
        if(ret != -1)
        {
            ListWidgetIOOutputItem* item = new ListWidgetIOOutputItem;
            item->SetLabelText(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
            item->SetIOModel(Model_Flag);
            AddIOOutputSetItem(item);
        }
    }
}

void IOOutputWidget::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        LoadTaskIOOutputItem();
    }
}

void IOOutputWidget::on_BasisButton_clicked()
{
    if(ui->BasisButton->isChecked())
    {
        if(Model_Flag == 1)
        {
            QMessageBox::StandardButton rb =
                    QMessageBox::warning(NULL,tr("警告"), tr("切换I/O输出模式将会清除当前的配置数据！请确认是否切换"),
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::Yes)
            {
                Model_Flag = 0;
                Task_IO_OutPut_Mode_Set(0);
                unsigned int Task_Count = GetTaskStepCount();
                for(unsigned int index = 0; index < Task_Count; index++){
                    Task_Step_OK_IO_Output_Index_Set(index+1, 0);
                    Task_Step_NG_IO_Output_Index_Set(index+1, 0);

                }
                LoadTaskIOOutputItem();
            }
            else
            {
                ui->BasisButton->setChecked(false);
                ui->AdvancedButton->setChecked(true);
            }
        }
    }
}

void IOOutputWidget::on_AdvancedButton_clicked()
{
    if(ui->AdvancedButton->isChecked())
    {
        if(Model_Flag == 0)
        {
            QMessageBox::StandardButton rb =
                    QMessageBox::warning(NULL,tr("警告"), tr("切换I/O输出模式将会清除当前的配置数据！请确认是否切换"),
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::Yes)
            {
                Model_Flag = 1;
                Task_IO_OutPut_Mode_Set(1);
                unsigned int Task_Count = GetTaskStepCount();
                for(unsigned int index = 0; index < Task_Count; index++){
                    Task_Step_OK_IO_Output_Index_Set(index+1, 0);
                    Task_Step_NG_IO_Output_Index_Set(index+1, 0);

                }
                LoadTaskIOOutputItem();
            }
            else
            {
                ui->AdvancedButton->setChecked(false);
                ui->BasisButton->setChecked(true);
            }
        }
    }
}

void IOOutputWidget::on_IO4Slider_sliderReleased()
{
    IO_output_param.width[3] = ui->IO4PulseValue->text().toUShort();
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_IO3Slider_sliderReleased()
{
    IO_output_param.width[2] = ui->IO3PulseValue->text().toUShort();
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_IO2Slider_sliderReleased()
{
    IO_output_param.width[1] = ui->IO2PulseValue->text().toUShort();
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_IO1Slider_sliderReleased()
{
    IO_output_param.width[0] = ui->IO1PulseValue->text().toUShort();
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_FlashSlider_sliderReleased()
{
    Flash_output_param.flash_width = ui->FlashValue->text().toUInt();
    Flash_Output_Config_Set(&Flash_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::SetLongPressValue(int value)
{
    if(value > 30){
        long_press_value = 12;
    }else if(value > 20){
        long_press_value = 4;
    }else if(value > 10){
        long_press_value = 2;
    }else{
        long_press_value = 1;
    }
}

void IOOutputWidget::on_btnIO1Sub_clicked()
{
    int value = ui->IO1PulseValue->text().toInt();
    if(value > 1){
        if(long_press_value == 0){
            ui->IO1PulseValue->setText(QString::number(value - 1));
            ui->IO1Slider->setSliderPosition(value - 1);
        }else{
            if(value > long_press_value) {
                ui->IO1PulseValue->setText(QString::number(value - long_press_value));
                ui->IO1Slider->setSliderPosition(value - long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO1PulseValue->setText(QString::number(1));
                ui->IO1Slider->setSliderPosition(1);
            }
        }
    }
    on_IO1Slider_sliderReleased();
}

void IOOutputWidget::on_btnIO2Sub_clicked()
{
    int value = ui->IO2PulseValue->text().toInt();
    if(value > 1){
        if(long_press_value == 0){
            ui->IO2PulseValue->setText(QString::number(value - 1));
            ui->IO2Slider->setSliderPosition(value - 1);
        }else{
            if(value > long_press_value) {
                ui->IO2PulseValue->setText(QString::number(value - long_press_value));
                ui->IO2Slider->setSliderPosition(value - long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO2PulseValue->setText(QString::number(1));
                ui->IO2Slider->setSliderPosition(1);
            }
        }
    }
    on_IO2Slider_sliderReleased();
}

void IOOutputWidget::on_btnIO3Sub_clicked()
{
    int value = ui->IO3PulseValue->text().toInt();
    if(value > 1){
        if(long_press_value == 0){
            ui->IO3PulseValue->setText(QString::number(value - 1));
            ui->IO3Slider->setSliderPosition(value - 1);
        }else{
            if(value > long_press_value) {
                ui->IO3PulseValue->setText(QString::number(value - long_press_value));
                ui->IO3Slider->setSliderPosition(value - long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO3PulseValue->setText(QString::number(1));
                ui->IO3Slider->setSliderPosition(1);
            }
        }
    }
    on_IO3Slider_sliderReleased();
}

void IOOutputWidget::on_btnIO4Sub_clicked()
{
    int value = ui->IO4PulseValue->text().toInt();
    if(value > 1){
        if(long_press_value == 0){
            ui->IO4PulseValue->setText(QString::number(value - 1));
            ui->IO4Slider->setSliderPosition(value - 1);
        }else{
            if(value > long_press_value) {
                ui->IO4PulseValue->setText(QString::number(value - long_press_value));
                ui->IO4Slider->setSliderPosition(value - long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO4PulseValue->setText(QString::number(1));
                ui->IO4Slider->setSliderPosition(1);
            }
        }
    }
    on_IO4Slider_sliderReleased();
}

void IOOutputWidget::on_FlashSub_clicked()
{
    int value = ui->FlashValue->text().toInt();
    if(value > 1){
        if(long_press_value == 0){
            ui->FlashValue->setText(QString::number(value - 1));
            ui->FlashSlider->setSliderPosition(value - 1);
        }else{
            if(value > long_press_value) {
                ui->FlashValue->setText(QString::number(value - long_press_value));
                ui->FlashSlider->setSliderPosition(value - long_press_value);
                SetLongPressValue(value);
            }else{
                ui->FlashValue->setText(QString::number(1));
                ui->FlashSlider->setSliderPosition(1);
            }
        }
    }
    on_FlashSlider_sliderReleased();
}

void IOOutputWidget::on_btnIO1Sub_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO1Sub_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO1Sub_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO1Sub_clicked);
    long_press_value = 0;
}


void IOOutputWidget::on_btnIO2Sub_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO2Sub_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO2Sub_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO2Sub_clicked);
    long_press_value = 0;
}


void IOOutputWidget::on_btnIO3Sub_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO3Sub_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO3Sub_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO3Sub_clicked);
    long_press_value = 0;
}


void IOOutputWidget::on_btnIO4Sub_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO4Sub_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO4Sub_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO4Sub_clicked);
    long_press_value = 0;
}

void IOOutputWidget::on_FlashSub_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_FlashSub_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_FlashSub_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_FlashSub_clicked);
    long_press_value = 0;
}

void IOOutputWidget::on_btnIO1Add_clicked()
{
    int value = ui->IO1PulseValue->text().toInt();
    if(value < 999){
        if(long_press_value == 0){
            ui->IO1PulseValue->setText(QString::number(value + 1));
            ui->IO1Slider->setSliderPosition(value + 1);
        }else{
            if(value + long_press_value < 999) {
                ui->IO1PulseValue->setText(QString::number(value + long_press_value));
                ui->IO1Slider->setSliderPosition(value + long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO1PulseValue->setText(QString::number(999));
                ui->IO1Slider->setSliderPosition(999);
            }
        }
    }
    on_IO1Slider_sliderReleased();
}

void IOOutputWidget::on_btnIO2Add_clicked()
{
    int value = ui->IO2PulseValue->text().toInt();
    if(value < 999){
        if(long_press_value == 0){
            ui->IO2PulseValue->setText(QString::number(value + 1));
            ui->IO2Slider->setSliderPosition(value + 1);
        }else{
            if(value + long_press_value < 999) {
                ui->IO2PulseValue->setText(QString::number(value + long_press_value));
                ui->IO2Slider->setSliderPosition(value + long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO2PulseValue->setText(QString::number(999));
                ui->IO2Slider->setSliderPosition(999);
            }
        }
    }
    on_IO2Slider_sliderReleased();
}

void IOOutputWidget::on_btnIO3Add_clicked()
{
    int value = ui->IO3PulseValue->text().toInt();
    if(value < 999){
        if(long_press_value == 0){
            ui->IO3PulseValue->setText(QString::number(value + 1));
            ui->IO3Slider->setSliderPosition(value + 1);
        }else{
            if(value + long_press_value < 999) {
                ui->IO3PulseValue->setText(QString::number(value + long_press_value));
                ui->IO3Slider->setSliderPosition(value + long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO3PulseValue->setText(QString::number(999));
                ui->IO3Slider->setSliderPosition(999);
            }
        }
    }
    on_IO3Slider_sliderReleased();
}

void IOOutputWidget::on_btnIO4Add_clicked()
{
    int value = ui->IO4PulseValue->text().toInt();
    if(value < 999){
        if(long_press_value == 0){
            ui->IO4PulseValue->setText(QString::number(value + 1));
            ui->IO4Slider->setSliderPosition(value + 1);
        }else{
            if(value + long_press_value < 999) {
                ui->IO4PulseValue->setText(QString::number(value + long_press_value));
                ui->IO4Slider->setSliderPosition(value + long_press_value);
                SetLongPressValue(value);
            }else{
                ui->IO4PulseValue->setText(QString::number(999));
                ui->IO4Slider->setSliderPosition(999);
            }
        }
    }
    on_IO4Slider_sliderReleased();
}

void IOOutputWidget::on_FlashAdd_clicked()
{
    int value = ui->FlashValue->text().toInt();
    if(value < 999){
        if(long_press_value == 0){
            ui->FlashValue->setText(QString::number(value + 1));
            ui->FlashSlider->setSliderPosition(value + 1);
        }else{
            if(value + long_press_value < 999) {
                ui->FlashValue->setText(QString::number(value + long_press_value));
                ui->FlashSlider->setSliderPosition(value + long_press_value);
                SetLongPressValue(value);
            }else{
                ui->FlashValue->setText(QString::number(999));
                ui->FlashSlider->setSliderPosition(999);
            }
        }
    }
    on_FlashSlider_sliderReleased();
}

void IOOutputWidget::on_btnIO1Add_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO1Add_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO1Add_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO1Add_clicked);
    long_press_value = 0;
}

void IOOutputWidget::on_btnIO2Add_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO2Add_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO2Add_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO2Add_clicked);
    long_press_value = 0;
}

void IOOutputWidget::on_btnIO3Add_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO3Add_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO3Add_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO3Add_clicked);
    long_press_value = 0;
}

void IOOutputWidget::on_btnIO4Add_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO4Add_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_btnIO4Add_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_btnIO4Add_clicked);
    long_press_value = 0;
}

void IOOutputWidget::on_FlashAdd_pressed()
{
    connect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_FlashAdd_clicked);
    long_press_value = 1;
    Long_Press_Time.start(200);
}

void IOOutputWidget::on_FlashAdd_released()
{
    Long_Press_Time.stop();
    disconnect(&Long_Press_Time, &QTimer::timeout, this, &IOOutputWidget::on_FlashAdd_clicked);
    long_press_value = 0;
}



void IOOutputWidget::on_radioButton_IO1_high_clicked()
{
    IO_output_param.IO_valid_flag |= OUTPUT_PIN_0;
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO1_low_clicked()
{
    IO_output_param.IO_valid_flag &= (~OUTPUT_PIN_0);
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO2_high_clicked()
{
    IO_output_param.IO_valid_flag |= OUTPUT_PIN_1;
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO2_low_clicked()
{
    IO_output_param.IO_valid_flag &= (~OUTPUT_PIN_1);
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO3_high_clicked()
{
    IO_output_param.IO_valid_flag |= OUTPUT_PIN_2;
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO3_low_clicked()
{
    IO_output_param.IO_valid_flag &= (~OUTPUT_PIN_2);
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO4_high_clicked()
{
    IO_output_param.IO_valid_flag |= OUTPUT_PIN_3;
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_IO4_low_clicked()
{
    IO_output_param.IO_valid_flag &= (~OUTPUT_PIN_3);
    IO_Output_Config_Set(&IO_output_param);
    SaveIOOutputParam();
}

void IOOutputWidget::on_radioButton_Flash_high_clicked()
{
    Flash_output_param.flash_valid_flag = 1;
    Flash_Output_Config_Set(&Flash_output_param);
}

void IOOutputWidget::on_radioButton_Flash_low_clicked()
{
    Flash_output_param.flash_valid_flag = 0;
    Flash_Output_Config_Set(&Flash_output_param);
}

void IOOutputWidget::on_btnIO1OutputTest_clicked()
{
    IO_Output_Set(OUTPUT_PIN_0);
}

void IOOutputWidget::on_btnIO2OutputTest_clicked()
{
    IO_Output_Set(OUTPUT_PIN_1);
}

void IOOutputWidget::on_btnIO3OutputTest_clicked()
{
    IO_Output_Set(OUTPUT_PIN_2);
}

void IOOutputWidget::on_btnIO4OutputTest_clicked()
{
    IO_Output_Set(OUTPUT_PIN_3);
}

void IOOutputWidget::on_btnFlashOutputTest_clicked()
{
    Flash_Output_Set();
}
