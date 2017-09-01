/**
  * @file  [ColorSelectDialog.h]
  * @brief  ColorSelectDialog
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef COLORSELECTDIALOG_H
#define COLORSELECTDIALOG_H
#include <QDialog>
#include "AreaCenterColorExtractDeal.h"
#include "PreBasicHead.h"
#include <QTimer>
#include "AcceCommon.h"
namespace Ui {
class ColorSelectDialog;
}
/**
  * @class  <ColorSelectDialog>  [ColorSelectDialog.h]  [ColorSelectDialog]
  * @brief  颜色抽取
  * @author  <szj>
  * @note
  * detailed  description
  */
class ColorSelectDialog : public QDialog
{
    Q_OBJECT

public:

    typedef union {

        unsigned short value;
        unsigned char buf[2];
    }RGBLIMITUNION;

    explicit ColorSelectDialog(QWidget *parent = 0);
    ~ColorSelectDialog();
    int m_color_task_id;
    int m_step;
    void *m_pre_ptr;
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 初始化颜色抽取数据
     */
    void IniData();

private slots:

    void SlotHS(int hMax,int hMin,int sMax,int sMin);
    void SlotI(int iMax,int iMin);
    void SlotRGBRect();

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_radioButtonColor0_clicked();

    void on_radioButtonColor1_clicked();

    void on_radioButtonColor2_clicked();

    void on_radioButtonColor3_clicked();

    void on_radioButtonColor4_clicked();

    void on_radioButtonColor5_clicked();

    void on_radioButtonColor6_clicked();

    void on_radioButtonColor7_clicked();

    void on_checkBoxColor0_clicked();

    void on_checkBoxColor1_clicked();

    void on_checkBoxColor2_clicked();

    void on_checkBoxColor3_clicked();

    void on_checkBoxColor4_clicked();

    void on_checkBoxColor5_clicked();

    void on_checkBoxColor6_clicked();

    void on_checkBoxColor7_clicked();

    void on_comboBoxBackGroundColor_currentIndexChanged(int index);

    void on_checkBoxSetMultiple_clicked();

    void on_comboBoxImageType_currentIndexChanged(int index);


    void updatImage(QPixmap pix);

    void on_btnClear_clicked();

    void on_checkBoxExceptColor_clicked();


    void on_checkBoxColorReverse_clicked();

    void on_checkBoxAutoSet_clicked();

    void on_btnUpdataImage_clicked();


    void btnMinHSub(int value =1);

    void btnMinHAdd(int value =1);

    void btnMaxHSub(int value =1);

    void btnMaxHAdd(int value =1);

    void btnMinSSub(int value =1);

    void btnMinSAdd(int value =1);

    void btnMaxSSub(int value =1);

    void btnMaxSAdd(int value =1);

    void btnMinISub(int value =1);

    void btnMinIAdd(int value =1);

    void btnMaxISub(int value =1);

    void btnMaxIAdd(int value =1);

    void on_btnMinHSub_pressed();

    void on_btnMinHSub_released();

    void on_btnMinHAdd_pressed();

    void on_btnMinHAdd_released();

    void on_btnMaxHSub_pressed();

    void on_btnMaxHSub_released();

    void on_btnMaxHAdd_pressed();

    void on_btnMaxHAdd_released();

    void on_btnMinSSub_pressed();

    void on_btnMinSSub_released();

    void on_btnMinSAdd_pressed();

    void on_btnMinSAdd_released();

    void on_btnMaxSSub_pressed();

    void on_btnMaxSSub_released();

    void on_btnMaxSAdd_pressed();

    void on_btnMaxSAdd_released();

    void on_btnMinISub_pressed();

    void on_btnMinISub_released();

    void on_btnMinIAdd_pressed();

    void on_btnMinIAdd_released();

    void on_btnMaxISub_pressed();

    void on_btnMaxISub_released();

    void on_btnMaxIAdd_pressed();

    void on_btnMaxIAdd_released();

private:
    Ui::ColorSelectDialog *ui;

    QTimer *timerUpData;
    int m_iPresstimes;
    int m_ini_data;
    QImage m_Imag;
    AreaCenterColorExtractDeal m_ColorExtractDeal;
    RGB_LIMIT rgbLimt[8];
    int m_i_copy_image;
    COLOR_DRAW_MODEL_CFG m_cfg;
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 更新图像HSI中I数据
     */
    void UpdateIColor();
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 初始化图像HSI数据
     */
    void IniHSI();
    /**
     * @brief ListImageBySelect
     * @author szj
     * @date 2017/05/08
     * @note 显示图像选择（原图，抽取后的图像）
     */
    void ListImageBySelect();
    /**
     * @brief IniData
     * @author szj
     * @date 2017/05/08
     * @note 保存数据
     */
    void SetDataToMonkeyLib();
    /**
     * @brief InirgbLimt
     * @param rgbLimt RGB_LIMIT结构体指针
     * @author szj
     * @date 2017/05/08
     * @note 初始RGB_LIMIT结构值
     */
    void InirgbLimt(RGB_LIMIT *rgbLimt);
    /**
     * @brief SetRgbLimt
     * @param rgbLimt RGB_LIMIT结构体指针
     * @author szj
     * @date 2017/05/08
     * @note 设置RGB_LIMIT结构值
     */
    void SetRgbLimt();
    /**
     * @brief SetRgbLimt
     * @author szj
     * @date 2017/05/08
     * @note 设置RGB_LIMIT结构值
     */
    void SetRgbLimt(RGB_LIMIT *rgbLimt);
    /**
     * @brief IniCheckBoxEnable
     * @param rgbLimt RGB_LIMIT结构体指针
     * @author szj
     * @date 2017/05/08
     * @note 设置控件HSI值显示
     */
    void SetControlValueByColor(RGB_LIMIT *rgbLimt);
    /**
     * @brief IniCheckBoxEnable
     * @param bflag 1.表示使能，0不表示不使能
     * @param label 需要显示颜色的Label控件
     * @param index 数组下标
     * @author szj
     * @date 2017/05/08
     * @note 设置QLabel颜色（1-8控件）
     */
    void SetLabelColor(int bflag,QLabel *label,int index);
    /**
     * @brief GetBitValue
     * @param index 数组下标
     * @param value 数据值
     * @author szj
     * @date 2017/05/08
     * @note 设置bit位(1--7）的值
     */
    unsigned char GetBitValue(int index,unsigned char value);
    /**
     * @brief GetBitEnable
     * @param num 1---7位
     * @param value 数据值
     * @author szj
     * @date 2017/05/08
     * @note 获取当前bit位上的值
     */
    int GetBitEnable(int num,int value);
    /**
     * @brief IniCheckBoxEnable
     * @author szj
     * @date 2017/05/08
     * @note 颜色抽取checkbox使能（1到8中控件）
     */
    void IniCheckBoxEnable(int index);
    /**
     * @brief SetLabelsColor
     * @return 返回背景颜色
     * @author szj
     * @date 2017/05/08
     * @note 获取背景颜色
     */
    int GetBlackColor();
    /**
     * @brief SetLabelsColor
     * @author szj
     * @date 2017/05/08
     * @note 设置抽取图像后的Label（1到8中控件）控件颜色
     */
    void SetLabelsColor();
    /**
     * @brief SetHSIData
     * @author szj
     * @date 2017/05/08
     * @note 保存HSI数据
     */
    void SetHSIData();
};

#endif // COLORSELECTDIALOG_H
