#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "serialport_global.h"
#include <QWidget>

class SERIALPORTSHARED_EXPORT SerialPort
{

public:
    SerialPort();
};

extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void SetProtocolType(int type);
extern "C" Q_DECL_EXPORT bool GetEnableFlag(void);

#endif // SERIALPORT_H
