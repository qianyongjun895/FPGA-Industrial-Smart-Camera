#include "EthernetPort.h"
#include "EthernetPortWidget.h"
#include <stdio.h>

EthernetPortWidget *pWidget = NULL;

EthernetPort::EthernetPort()
{
}

QWidget *GetWidget()
{
    pWidget = new EthernetPortWidget();
    return  pWidget;
}

void SetProtocolType(int type)
{
    pWidget->Protocol_Type = type;
    pWidget->IniData();
}


bool GetEnableFlag(void)
{
    return pWidget->EnableFlag;
}
