#include "MitFxPlc.h"
#include "MitFxPlcWidget.h"
#include "MitFxPlcGlobal.h"
MitFxPlcWidget* P_Widget = NULL;
MitFxPlc::MitFxPlc()
{
}

QWidget* GetWidget()
{
    mit_fx_plc_init();
    P_Widget = new MitFxPlcWidget;
    return P_Widget;
}


void SetProtocolData()
{
    P_Widget->SetMitFxPLCConfig();
}

void InitShowData()
{
    return;
}

void InitProtocol()
{
    mit_fx_plc_init();
}
