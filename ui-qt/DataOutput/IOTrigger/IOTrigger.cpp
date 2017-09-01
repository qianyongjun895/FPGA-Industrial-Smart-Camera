#include "IOTrigger.h"
#include "IOTriggerWidget.h"

IOTriggerWidget* P_Widget = NULL;
IOTrigger::IOTrigger()
{
}

QWidget* GetWidget()
{
    P_Widget = new IOTriggerWidget();
    return P_Widget;
}
