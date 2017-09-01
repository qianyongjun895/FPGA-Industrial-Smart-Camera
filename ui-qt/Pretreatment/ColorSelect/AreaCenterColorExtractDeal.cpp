#include "AreaCenterColorExtractDeal.h"
#include <math.h>
#include <QDebug>
#define PI 3.1415926
#include <stdio.h>
AreaCenterColorExtractDeal::AreaCenterColorExtractDeal()
{
    m_List_image = QImage(640,480,QImage::Format_RGB888);
    m_black_r = 0;
    m_black_g = 0;
    m_black_b = 0;
}
void AreaCenterColorExtractDeal::RGBToHSI(int R,int G,int B,int *H,int *S,int *I)
{
    float r,g,b;
    float h,s,i;

    int SumRGB = R+G+B;
    r= (R*1.0)/(SumRGB*1.0);
    g= (G*1.0)/(SumRGB*1.0);
    b= (B*1.0)/(SumRGB*1.0);

    if (R==0 && G==0 && B==0)
    {
        *H=160;
        *S=0;
        *I=0;
    }
    else if (R==255 && G==255 && B==255)
    {
        *H=160;
        *S=0;
        *I=240;
    }else
    {
        i = (SumRGB*1.0)/(3*255);
        //i = (SumRGB*1.0)/(3*1.0);

        float w;

        if(R==G && G==B)
        {
            *H = 0;
            *S = 0;
            *I = i*255;
            //*I =i;
        }else
        {
            w = acos((2*R-G-B)/( 2*sqrt((R-G)*(R-G)+(R-B)*(G-B))));
            if(b <=g)
            {
                h = w;
            }else
            {
                h = 2*PI-w;
            }
            float fMin = r;

            if(fMin > g)
            {
                fMin = g;
            }
            if(fMin > b)
            {
                fMin = b;
            }
            s = 1 - 3*fMin;
            *H = h*180/PI;
            *S = s*100;
            *I = i*255;
            //*I = i;
        }
    }
}
void AreaCenterColorExtractDeal::HSIToRgb(int H,int S,int I,int *R,int *G,int *B)
{
    float h,s,i;
    float x,y,z;
    float r,g,b;

    h = (H*PI)/180;
    s= S/100.0;
    i=I/255.0;
    x = i*(1-s);
    y =i*(1+s*cos(h)/cos(PI/3-h));
    z = 3*i-x-y;

    if(h<2*PI/3)
    {
        b = x;
        r=y;
        g = z;
    }else if(h>=2*PI/3 && h<4*PI/3)
    {
        h = h-2*PI/3;
        y =i*(1+s*cos(h)/cos(PI/3-h));
        z = 3*i-x-y;
        r = x;
        g =y;
        b = z;

    }else if(h>=4*PI/3 && h<2*PI)
    {
        h = h-4*PI/3;
        y =i*(1+s*cos(h)/cos(PI/3-h));
        z = 3*i-x-y;
        g = x;
        b = y;
        r = z;
    }else
    {
        g = 255;
        b = 255;
        r = 255;
    }

    *R = r*255;
    *B = b*255;
    *G = g*255;

    if(r > 1)
        *R = 255;
    if(b >1)
        *B = 255;
    if(g > 1)
        *G = 255;
}
void AreaCenterColorExtractDeal::FindMinMaxRGB(QRect rect)
{
    unsigned char *p_img = m_Imag->bits();
    //unsigned char *p_img = (unsigned char*)m_pic_buf;
    int x_start = rect.topLeft().x();
    int y_start = rect.topLeft().y();
    int x_end = rect.bottomRight().x();
    int y_end = rect.bottomRight().y();
    m_r_min = 255;
    m_r_max = 0;

    m_g_min = 255;
    m_g_max = 0;

    m_b_min = 255;
    m_b_max = 0;

    for(int i= y_start; i< y_end;i++)
    {
        for(int j= x_start; j< x_end;j++)
        {


            if(m_r_min >= (unsigned char)p_img[i*640*3 +j*3])
                m_r_min = (unsigned char) p_img[i*640*3 +j*3];
            if(m_r_max <= (unsigned char)p_img[i*640*3 +j*3])
                m_r_max =(unsigned char) p_img[i*640*3 +j*3];

            if(m_g_min >= (unsigned char)p_img[i*640*3 +j*3+1])
                m_g_min = (unsigned char)p_img[i*640*3 +j*3+1];
            if(m_g_max <= (unsigned char)p_img[i*640*3 +j*3+1])
                m_g_max = (unsigned char)p_img[i*640*3 +j*3+1];

            if(m_b_min >= (unsigned char)p_img[i*640*3 +j*3+2])
                m_b_min =  (unsigned char)p_img[i*640*3 +j*3+2];
            if(m_b_max <= (unsigned char)p_img[i*640*3 +j*3+2])
                m_b_max = (unsigned char)p_img[i*640*3 +j*3+2];

        }
    }
}
void AreaCenterColorExtractDeal::RGBPicToHSI(QRect rect)
{
    unsigned char *p_img = m_Imag->bits();
    //unsigned char *p_img = (unsigned char*)m_pic_buf;
    int x_start = rect.topLeft().x();
    int y_start = rect.topLeft().y();
    int x_end = rect.bottomRight().x();
    int y_end = rect.bottomRight().y();
    int r = 0;
    int g = 0;
    int b = 0;
    int hValue,sValue,iValue;
    m_H.clear();
    m_S.clear();
    m_I.clear();
    hMax = 0;
    sMax = 0;
    iMax = 0;
    hMin = 360;
    sMin = 255;
    iMin= 255;

    m_r_Average = 0;
    m_g_Average = 0;
    m_b_Average = 0;

    for(int i= y_start; i< y_end;i++)
    {
        for(int j= x_start; j< x_end;j++)
        {
            r = (unsigned char)p_img[i*640*3 +j*3];
            g = (unsigned char)p_img[i*640*3 +j*3+1];
            b = (unsigned char)p_img[i*640*3 +j*3+2];
            m_r_Average += r;
            m_g_Average += g;
            m_b_Average += b;

            RGBToHSI(r,g,b,&hValue,&sValue,&iValue);
            m_H.append(hValue/2+10);
            m_S.append(100-sValue+10);
            m_I.append(128-iValue/2+10);
            if(hMax <= hValue)
                hMax = hValue;
            if(sMax <= sValue)
                sMax = sValue;
            if(iMax <= iValue)
                iMax = iValue;
            if(hMin >= hValue)
                hMin = hValue;
            if(sMin >= sValue)
                sMin = sValue;
            if(iMin >= iValue)
                iMin = iValue;
        }
    }
    m_list_r = r;
    m_list_g = g;
    m_list_b = b;

    m_r_Average = m_r_Average/((y_end-y_start)*(x_end-x_start));
    m_g_Average = m_g_Average/((y_end-y_start)*(x_end-x_start));
    m_b_Average = m_b_Average/((y_end-y_start)*(x_end-x_start));
}

void AreaCenterColorExtractDeal::RGBToHSIPic()
{
    unsigned char *p_img = m_Imag->bits();
    //unsigned char *p_img = (unsigned char *)m_pic_buf;
    int r,g,b;
    int hValue,sValue,iValue;

    m_H_Pic.clear();
    m_S_Pic.clear();
    m_I_Pic.clear();

    for(int i=0; i<480;i++)
    {
        for(int j= 0; j<640;j++)
        {
            r = (unsigned char)p_img[i*640*3 +j*3];
            g = (unsigned char)p_img[i*640*3 +j*3+1];
            b = (unsigned char)p_img[i*640*3 +j*3+2];
            RGBToHSI(r,g,b,&hValue,&sValue,&iValue);
            m_H_Pic.append(hValue);
            m_S_Pic.append(sValue);
            m_I_Pic.append(iValue);
        }
    }
}

void AreaCenterColorExtractDeal::FindHSIPicFlag(int HMax,int HMin,int SMax,int SMin,int IMax,int IMin)
{
    memset(m_buf,0,sizeof(m_buf));
    if(HMax < HMin)
    {
        for(int i= 0; i< 480; i++)
        {
            for(int j= 0; j<640;j++)
            {
                if(((m_H_Pic[i*640+j] >= 0 && m_H_Pic[i*640+j]<= HMax)\
                    ||(m_H_Pic[i*640+j] >= HMin && m_H_Pic[i*640+j]<= 360))\
                        && m_S_Pic[i*640+j]>=SMin && m_S_Pic[i*640+j]<=SMax \
                        && m_I_Pic[i*640+j]>=IMin && m_I_Pic[i*640+j]<=IMax)
                {
                    m_buf[i*640+j] = 1;

                }else
                {
                    m_buf[i*640+j] = 0;
                }
            }
        }


    }else
    {
        for(int i= 0; i< 480; i++)
        {
            for(int j= 0; j<640;j++)
            {

                if(m_H_Pic[i*640+j] >= HMin && m_H_Pic[i*640+j]<= HMax \
                        && m_S_Pic[i*640+j]>=SMin && m_S_Pic[i*640+j]<=SMax \
                        && m_I_Pic[i*640+j]>=IMin && m_I_Pic[i*640+j]<=IMax)
                {

                    m_buf[i*640+j] = 1;


                }else
                {
                    m_buf[i*640+j] = 0;
                }
            }
        }
    }
}

void AreaCenterColorExtractDeal::SetImgByHSI()
{
    QImage tempImage = *m_Imag;

    unsigned char *p_img_temp = tempImage.bits();

    m_r_max = 0;
    m_r_min = 255;
    m_g_max = 0;
    m_g_min = 255;
    m_b_max = 0;
    m_b_min = 255;

    for(int i=0; i<480;i++)
    {
        for(int j= 0; j<640;j++)
        {

            if((unsigned char)m_buf[i*640+j] == 0) //0-->1
            {
                p_img_temp[i*640*3 +j*3] = 0;
                p_img_temp[i*640*3 +j*3+1] = 0;
                p_img_temp[i*640*3 +j*3+2] = 0;

            }else
            {

                ;
            }
        }
    }

    for(int i = 1; i<479; i++)
    {
        for(int j=1; j<639; j++)
        {
            if((unsigned char)m_buf[i*640+j] == 1)
            {
                if( (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[i*640*3+(j-1)*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[i*640*3+(j+1)*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[(i-1)*640*3+(j-1)*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[(i-1)*640*3+j*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[(i-1)*640*3+(j+1)*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[(i+1)*640*3+(j-1)*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[(i+1)*640*3+j*3] \
                        && (unsigned char)p_img_temp[i*640*3+j*3] > (unsigned char)p_img_temp[(i+1)*640*3+(j+1)*3])
                {
                    ;
                }else if((unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[i*640*3+(j-1)*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[i*640*3+(j+1)*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[(i-1)*640*3+(j-1)*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[(i-1)*640*3+j*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[(i-1)*640*3+(j+1)*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[(i+1)*640*3+(j-1)*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[(i+1)*640*3+j*3] \
                         && (unsigned char)p_img_temp[i*640*3+j*3] < (unsigned char)p_img_temp[(i+1)*640*3+(j+1)*3])

                {

                    ;

                }else
                {
                    if(m_r_max <= (unsigned char)p_img_temp[i*640*3 +j*3])
                        m_r_max = (unsigned char)p_img_temp[i*640*3 +j*3];

                    if(m_r_min >= (unsigned char)p_img_temp[i*640*3 +j*3])
                        m_r_min = (unsigned char)p_img_temp[i*640*3 +j*3];
                }


                if( (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[i*640*3+(j-1)*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[i*640*3+(j+1)*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[(i-1)*640*3+(j-1)*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[(i-1)*640*3+j*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[(i-1)*640*3+(j+1)*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[(i+1)*640*3+(j-1)*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[(i+1)*640*3+j*3+1] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+1] > (unsigned char)p_img_temp[(i+1)*640*3+(j+1)*3+1])
                {
                    ;
                }else if((unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[i*640*3+(j-1)*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[i*640*3+(j+1)*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[(i-1)*640*3+(j-1)*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[(i-1)*640*3+j*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[(i-1)*640*3+(j+1)*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[(i+1)*640*3+(j-1)*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[(i+1)*640*3+j*3+1] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+1] < (unsigned char)p_img_temp[(i+1)*640*3+(j+1)*3+1])

                {

                    ;

                }else
                {
                    if(m_g_max <= (unsigned char)p_img_temp[i*640*3 +j*3+1])
                        m_g_max = (unsigned char)p_img_temp[i*640*3 +j*3+1];

                    if(m_g_min >= (unsigned char)p_img_temp[i*640*3 +j*3+1])
                        m_g_min = (unsigned char)p_img_temp[i*640*3 +j*3+1];
                }



                if( (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[i*640*3+(j-1)*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[i*640*3+(j+1)*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[(i-1)*640*3+(j-1)*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[(i-1)*640*3+j*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[(i-1)*640*3+(j+1)*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[(i+1)*640*3+(j-1)*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[(i+1)*640*3+j*3+2] \
                        && (unsigned char)p_img_temp[i*640*3+j*3+2] > (unsigned char)p_img_temp[(i+1)*640*3+(j+1)*3+2])
                {
                    ;
                }else if((unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[i*640*3+(j-1)*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[i*640*3+(j+1)*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[(i-1)*640*3+(j-1)*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[(i-1)*640*3+j*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[(i-1)*640*3+(j+1)*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[(i+1)*640*3+(j-1)*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[(i+1)*640*3+j*3+2] \
                         && (unsigned char)p_img_temp[i*640*3+j*3+2] < (unsigned char)p_img_temp[(i+1)*640*3+(j+1)*3+2])

                {

                    ;

                }else
                {
                    if(m_b_max <= (unsigned char)p_img_temp[i*640*3 +j*3+2])
                        m_b_max = (unsigned char)p_img_temp[i*640*3 +j*3+2];

                    if(m_b_min >= (unsigned char)p_img_temp[i*640*3 +j*3+2])
                        m_b_min = (unsigned char)p_img_temp[i*640*3 +j*3+2];
                }





            }
        }
    }


    //SetImgByRGB(label);
    //SetRGB(label,rgbLimt);
}

void AreaCenterColorExtractDeal::SetImgByRGB(QLabel *label)
{
    QImage tempImage = *m_Imag;

    unsigned char *p_img = tempImage.bits();

    for(int i=0; i<480;i++)
    {
        for(int j= 0; j<640;j++)
        {
            if(p_img[i*640*3 +j*3]>=m_r_min && p_img[i*640*3 +j*3]<= m_r_max \
                    && p_img[i*640*3 +j*3+1] >= m_g_min && p_img[i*640*3 +j*3+1]<=m_g_max \
                    && p_img[i*640*3 +j*3+2] >= m_b_min && p_img[i*640*3 +j*3+2]<=m_b_max   )
            {
                ;
            }else
            {
                p_img[i*640*3 +j*3] = 0;
                p_img[i*640*3 +j*3+1] = 0;
                p_img[i*640*3 +j*3+2] = 0;
            }
        }
    }
    QPixmap tempQPixmap = QPixmap::fromImage(tempImage);
    label->setPixmap(tempQPixmap);
}

void AreaCenterColorExtractDeal::SetRGB(QLabel *label,RGB_LIMIT *rgb_limit)
{
    QImage tempImage = *m_Imag;
    //QImage tempImage  = QImage(640,480,QImage::Format_RGB888);
    unsigned char *p_img = tempImage.bits();
    bool bIsIn =false;

    bool bIsEnable = false;
    for(int k =0; k<8;k++)
    {
        if(rgb_limit[k].flag)
        {
            qDebug()<<"bIsEnable = true;";
            bIsEnable = true;
            break;
        }
    }

    if(bIsEnable)
    {
        for(int i=0; i<480;i++)
        {
            for(int j= 0; j<640;j++)
            {
                bIsIn = false;
                for(int k =0; k<8;k++)
                {
                    if(!rgb_limit[k].bFlagColorExcept)
                    {
                        if(rgb_limit[k].flag)
                        {
                            if(p_img[i*640*3 +j*3]>=rgb_limit[k].m_r_min && p_img[i*640*3 +j*3]<= rgb_limit[k].m_r_max \
                                    && p_img[i*640*3 +j*3+1] >= rgb_limit[k].m_g_min && p_img[i*640*3 +j*3+1]<=rgb_limit[k].m_g_max \
                                    && p_img[i*640*3 +j*3+2] >= rgb_limit[k].m_b_min && p_img[i*640*3 +j*3+2]<=rgb_limit[k].m_b_max   )
                            {
                                bIsIn = true;

                            }
                        }
                    }else
                    {
                        if(rgb_limit[k].flag)
                        {
                            if(p_img[i*640*3 +j*3]>=rgb_limit[k].m_r_min && p_img[i*640*3 +j*3]<= rgb_limit[k].m_r_max \
                                    && p_img[i*640*3 +j*3+1] >= rgb_limit[k].m_g_min && p_img[i*640*3 +j*3+1]<=rgb_limit[k].m_g_max \
                                    && p_img[i*640*3 +j*3+2] >= rgb_limit[k].m_b_min && p_img[i*640*3 +j*3+2]<=rgb_limit[k].m_b_max   )
                            {
                                bIsIn = false;
                                break;
                            }
                        }
                    }
                }
                if(!bIsIn)
                {
                    p_img[i*640*3 +j*3] = m_black_r;
                    p_img[i*640*3 +j*3+1] = m_black_g;
                    p_img[i*640*3 +j*3+2] = m_black_b;
                }
            }
        }
    }
    m_List_image = tempImage;
    QPixmap tempQPixmap = QPixmap::fromImage(tempImage);
    label->setPixmap(tempQPixmap);
}

void AreaCenterColorExtractDeal::SetBinaryImag(QLabel *label)
{
    QImage tempImage = this->m_List_image;
    //QImage tempImage  = QImage(640,480,QImage::Format_RGB888);
    unsigned char *p_img = tempImage.bits();

    for(int i=0; i<480;i++)
    {
        for(int j= 0; j<640;j++)
        {
            if( p_img[i*640*3 +j*3] != m_black_r  \
                && p_img[i*640*3 +j*3+1] != m_black_g \
                && p_img[i*640*3 +j*3+2] != m_black_b)
            {
                p_img[i*640*3 +j*3] = 255;
                p_img[i*640*3 +j*3+1] = 255;
                p_img[i*640*3 +j*3+2] = 255;

            }else
            {
                p_img[i*640*3 +j*3] = 0;
                p_img[i*640*3 +j*3+1] = 0;
                p_img[i*640*3 +j*3+2] = 0;
            }
        }
    }
    QPixmap tempQPixmap = QPixmap::fromImage(tempImage);
    label->setPixmap(tempQPixmap);
}

