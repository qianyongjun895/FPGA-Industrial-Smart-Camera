#include "UserDefined.h"
#include "UserDefinedWidget.h"
#include "UserDefinedGlobal.h"
#include <stdio.h>
UserDefinedWidget *P_Widget = NULL;
UserDefined::UserDefined()
{
}

QWidget *GetWidget()
{
    P_Widget = new UserDefinedWidget();
    return  P_Widget;
}


void SetProtocolData()
{
    P_Widget->SetUserDefinedData();
}

void InitShowData()
{
    return;
}

void InitProtocol()
{
    user_defined_init();
}
