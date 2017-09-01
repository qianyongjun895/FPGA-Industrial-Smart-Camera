#ifndef CHECKMOUSE_H
#define CHECKMOUSE_H

#include <QObject>
#include <QString>
class CheckMouse
{
public:
    CheckMouse();
    int GetFind(){return m_find;}
private:
    void scanConnectedDevices();
    bool checkDeviceType(const QString &device);
    int m_find;
};

#endif // CHECKMOUSE_H
