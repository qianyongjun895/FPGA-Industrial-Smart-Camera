/**
  * @file  [AreaCenterColorExtractDeal.h]
  * @brief  AreaCenterColorExtractDeal
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef AREACENTERCOLOREXTRACTDEAL_H
#define AREACENTERCOLOREXTRACTDEAL_H
#include <QImage>
#include <QPixmap>
#include <QLabel>

typedef struct
{
    char m_r_max;
    char m_r_min;
    char m_g_max;
    char m_g_min;
    char m_b_max;
    char m_b_min;

    short m_h_max;
    short m_h_min;
    short m_s_max;
    short m_s_min;
    short m_i_max;
    short m_i_min;

    short m_r_Average;
    short m_g_Average;
    short m_b_Average;

    char m_list_r;
    char m_list_g;
    char m_list_b;


    bool flag;
    bool bFlagColorExcept;

}RGB_LIMIT;
/**
  * @class  <AreaCenterColorExtractDeal>  [AreaCenterColorExtractDeal.h]  [AreaCenterColorExtractDeal]
  * @brief  颜色抽取处理类
  * @author  <szj>
  * @note
  * detailed  description
  */
class AreaCenterColorExtractDeal
{
public:
    AreaCenterColorExtractDeal();
    /**
     * @brief HSIToRgb
     * @param H H值
     * @param S S值
     * @param I I值
     * @param *R 返回R值
     * @param *G 返回G值
     * @param *B 返回B值
     * @author szj
     * @date 2017/05/08
     * @note HSI转RGB
     */
    void HSIToRgb(int H,int S,int I,int *R,int *G,int *B);
    /**
     * @brief RGBToHSI
     * @param R R值
     * @param G G值
     * @param B B值
     * @param *H 返回H值
     * @param *S 返回S值
     * @param *I 返回I值
     * @author szj
     * @date 2017/05/08
     * @note HSI转RGB
     */
    void RGBToHSI(int R,int G,int B,int *H,int *S,int *I);
    /**
     * @brief RGBToHSI
     * @param rect 矩形区域
     * @author szj
     * @date 2017/05/08
     * @note 找出选中区域中的RGB最大最小值
     */
    void FindMinMaxRGB(QRect rect);
    /**
     * @brief RGBToHSI
     * @param rect 矩形区域
     * @author szj
     * @date 2017/05/08
     * @note 矩形区域中RGB转HSI
     */
    void RGBPicToHSI(QRect rect);
    /**
     * @brief RGBToHSI
     * @author szj
     * @date 2017/05/08
     * @note RGB转HSI
     */
    void RGBToHSIPic();
    void FindHSIPicFlag(int HMax,int HMin,int SMax,int SMin,int IMax,int IMin);
    void SetImgByHSI();
    void SetImgByRGB(QLabel *label);
    void SetRGB(QLabel *label,RGB_LIMIT *rgb_limit);
    void SetBinaryImag(QLabel *label);
public:
    QImage *m_Imag;
    unsigned char m_buf[640*480];
    //unsigned char *m_buf;
    //unsigned char m_pic_buf[640*480*3];
    QImage m_List_image;
    unsigned char m_r_max;
    unsigned char m_r_min;
    unsigned char m_g_max;
    unsigned char m_g_min;
    unsigned char m_b_max;
    unsigned char m_b_min;

    unsigned char m_list_r;
    unsigned char m_list_g;
    unsigned char m_list_b;

    int m_r_Average;
    int m_g_Average;
    int m_b_Average;

    int hMax;
    int sMax;
    int iMax;
    int hMin;
    int sMin;
    int iMin;

    int m_black_r;
    int m_black_g;
    int m_black_b;

    QVector<int> m_H;
    QVector<int> m_S;
    QVector<int> m_I;

    QVector<short>m_H_Pic;
    QVector<short>m_S_Pic;
    QVector<short>m_I_Pic;

};

#endif // AREACENTERCOLOREXTRACTDEAL_H
