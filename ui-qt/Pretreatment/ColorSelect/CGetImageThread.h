#ifndef CGETIMAGETHREAD_H
#define CGETIMAGETHREAD_H

#include <QObject>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#define PICWIDTH 640*2
#define PICHEIGH 480*2

class CGetImageThread : public QObject
{
    Q_OBJECT
public:

    ~CGetImageThread();
    void start(int times);
    void stop();
    QImage  GetImage(){return m_image;}
    QPixmap GetPixmap(){return m_Pixmap;}
    void GetSingleImag();
    static CGetImageThread *Instance();
    void copyData(char *data);
    void SetPixel(int pix);
signals:
    void SignalPic(QPixmap pix);
public slots:

private:
    explicit CGetImageThread(QObject *parent = 0);
    static CGetImageThread *m_CGetImageThread;
    void *vga_save_virtaddr;//图片地址
    QImage m_image;
    QPixmap m_Pixmap;
    bool m_b_timer_start;
    char m_pic_buf[PICWIDTH*PICHEIGH*3];
    int m_width;
    int m_height;
    int m_pixel;
    QImage  PicDataToImage(char* buf,int width,int height);
    QPixmap PicDataToPixmag(char* buf,int width,int height);
    QPixmap PicDataToColorPixmag(char* buf,int width,int height);
};

#endif // CGETIMAGETHREAD_H
