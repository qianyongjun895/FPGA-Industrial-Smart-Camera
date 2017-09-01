#ifndef IOTRIGGER_H
#define IOTRIGGER_H

#include "iotrigger_global.h"
#include <QWidget>
class IOTRIGGERSHARED_EXPORT IOTrigger
{

public:
    IOTrigger();
};

extern "C" Q_DECL_EXPORT QWidget* GetWidget();
#endif // IOTRIGGER_H
