#ifndef ETHERNETPORT_H
#define ETHERNETPORT_H

#include "ethernetport_global.h"
#include <QWidget>

class ETHERNETPORTSHARED_EXPORT EthernetPort
{

public:
    EthernetPort();
};

extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void SetProtocolType(int type);
extern "C" Q_DECL_EXPORT bool GetEnableFlag(void);

#endif // ETHERNETPORT_H
