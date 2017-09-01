#include "SerialPort.h"
#include "SerialPortWidget.h"

SerialPortWidget *pWidget = NULL;

SerialPort::SerialPort()
{
}


QWidget *GetWidget()
{
    pWidget = new SerialPortWidget();
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
