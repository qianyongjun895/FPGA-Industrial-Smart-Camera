#include "CheckMouse.h"
#include <qdebug.h>
#include <QHash>
#include <QDir>
#include <linux/input.h>
#include <fcntl.h>


#undef QT_OPEN
#define QT_OPEN         qt_safe_open
int qt_safe_open(const char *pathname, int flags, mode_t mode = 0777)
{
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
    int fd;
    fd = open(pathname, flags, mode);

    if (fd != -1)
    {
        ::fcntl(fd, F_SETFD, FD_CLOEXEC);
    }
    return fd;
}

#define QT_EVDEV_DEVICE_PATH "/dev/input/"
#define LONG_BITS (sizeof(long) * 8 )
#define LONG_FIELD_SIZE(bits) ((bits / LONG_BITS) + 1)

static bool testBit(long bit, const long *field)
{
    return (field[bit / LONG_BITS] >> bit % LONG_BITS) & 1;
}

CheckMouse::CheckMouse()
{
    m_find = 0;
    scanConnectedDevices();
}


void CheckMouse::scanConnectedDevices()
{
    QDir dir;
    dir.setFilter(QDir::System);
    dir.setPath(QString::fromLatin1(QT_EVDEV_DEVICE_PATH));
    foreach (const QString &deviceFile, dir.entryList()) {
        QString absoluteFilePath = dir.absolutePath() + QString::fromLatin1("/") + deviceFile;
        //qDebug()<<"absoluteFilePath====="<<absoluteFilePath;
        if (checkDeviceType(absoluteFilePath))
        {
            m_find =1;
        }
    }

}
bool CheckMouse::checkDeviceType(const QString &device)
{

    bool ret = false;
    int fd = QT_OPEN(device.toLocal8Bit().constData(), O_RDONLY | O_NDELAY, 0);
    if (!fd) {
        //qDebug()<<"Device discovery cannot open device" << device;
        return false;
    }

    long bitsKey[LONG_FIELD_SIZE(KEY_CNT)];
    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(bitsKey)), bitsKey) >= 0 ) {

        qDebug()<<"(ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(bitsKey)), bitsKey) >= 0 )";
        /*if (!ret && (m_types & Device_Keyboard)) {

            if (testBit(KEY_Q, bitsKey)) {
                qDebug()<< "Found keyboard at" << device;
                ret = true;
            }
        }*/

        //if (!ret && (m_types & Device_Mouse)) {
            long bitsRel[LONG_FIELD_SIZE(REL_CNT)];
            if (ioctl(fd, EVIOCGBIT(EV_REL, sizeof(bitsRel)), bitsRel) >= 0 ) {
                if (testBit(REL_X, bitsRel) && testBit(REL_Y, bitsRel) && testBit(BTN_MOUSE, bitsKey)) {
                    //qDebug() << "Found mouse at" << device;
                    ret = true;
                }
            }
        //}
    }
    return ret;
}
