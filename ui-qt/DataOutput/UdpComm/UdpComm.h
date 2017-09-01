#ifndef UDPCOMM_H
#define UDPCOMM_H

#include "udpcomm_global.h"
#include <QWidget>
class UDPCOMMSHARED_EXPORT UdpComm
{

public:
    UdpComm();
};
extern "C" Q_DECL_EXPORT QWidget *GetWidget();
extern "C" Q_DECL_EXPORT void SetProtocolType(int type);
extern "C" Q_DECL_EXPORT bool GetEnableFlag(void);
#endif // UDPCOMM_H
