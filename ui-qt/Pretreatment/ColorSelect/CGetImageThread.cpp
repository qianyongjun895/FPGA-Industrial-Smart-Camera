#include "CGetImageThread.h"
#include <qdebug.h>
#include <stdio.h>
#include "AcceCommon.h"


CGetImageThread *CGetImageThread::m_CGetImageThread = NULL;

CGetImageThread *CGetImageThread::Instance()
{
    if(m_CGetImageThread == NULL)
    {
        m_CGetImageThread = new CGetImageThread;
    }
    return m_CGetImageThread;
}

CGetImageThread::CGetImageThread(QObject *parent) : QObject(parent)
{
    vga_save_virtaddr = GetCptColorPicAddr();
    this->m_width = 640;
    this->m_height =480;
}
CGetImageThread::~CGetImageThread()
{
    //close(memfd);
    if(m_CGetImageThread !=NULL)
    {
        delete m_CGetImageThread;
        m_CGetImageThread = NULL;
    }
}

void CGetImageThread::GetSingleImag()
{
    if(vga_save_virtaddr !=NULL)
    {
         copyData((char*)((unsigned int)vga_save_virtaddr));
         m_Pixmap = PicDataToColorPixmag(m_pic_buf,m_width,m_height);
         SignalPic(this->m_Pixmap);
    }
}
QImage CGetImageThread::PicDataToImage(char* buf,int width,int height)
{
    QImage tempImag = QImage((unsigned char*)buf,width,height,QImage::Format_RGB888);
    return tempImag;
}
QPixmap CGetImageThread::PicDataToPixmag(char* buf,int width,int height)
{
    QImage tempImag = QImage((unsigned char*)buf,width,height,QImage::Format_Indexed8);
    QPixmap tempQPixmap = QPixmap::fromImage(tempImag);
    this->m_image = tempImag;
    return tempQPixmap ;
}
QPixmap CGetImageThread::PicDataToColorPixmag(char* buf,int width,int height)
{
    QImage tempImag = QImage((unsigned char*)buf,width,height,QImage::Format_RGB888);
    QPixmap tempQPixmap = QPixmap::fromImage(tempImag);
    this->m_image = tempImag.scaled(640,480,Qt::KeepAspectRatio);
    return tempQPixmap ;
}
void CGetImageThread::copyData(char *data)
{
    for(int i=0; i< m_height;i++)
    {
        for(int j=0; j<m_width;j++)
        {
            m_pic_buf[i*m_width*3+j*3]= data[i*m_width*4+j*4+2];
            m_pic_buf[i*m_width*3+j*3+1]= data[i*m_width*4+j*4+1];
            m_pic_buf[i*m_width*3+j*3+2]= data[i*m_width*4+j*4+0];
        }
    }
}
void CGetImageThread::SetPixel(int pix)
{
    this->m_pixel = pix;
    if(m_pixel == 0x02)
    {
       this->m_width = 640;
        this->m_height =480;
    }else if(m_pixel == 0x04)
    {
        this->m_width = 640*2;
         this->m_height =480*2;
    }else if(m_pixel == 0x10)
    {
        /*this->m_width = 640*4;
        this->m_height =480*4;*/
        ;
    }
}

