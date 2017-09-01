#include "IOOutput.h"
#include "IOOutputWidget.h"
#include <stdio.h>
IOOutputWidget* P_Widget = NULL;
IOOutput::IOOutput()
{
}

QWidget* GetWidget()
{
    P_Widget = new IOOutputWidget();
    return P_Widget;
}
