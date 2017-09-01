#include "UdpComm.h"
#include "UdpCommWidget.h"
UdpCommWidget *pWidget = NULL;
UdpComm::UdpComm()
{
}


QWidget *GetWidget()
{
    pWidget = new UdpCommWidget();
    return  pWidget;
}

void SetProtocolType(int type)
{
    pWidget->Protocol_Type = type;
}


bool GetEnableFlag(void)
{
    return pWidget->EnableFlag;
}
