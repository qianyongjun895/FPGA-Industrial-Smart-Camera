#ifndef IOOUTPUT_H
#define IOOUTPUT_H

#include "iooutput_global.h"
#include <QWidget>
class IOOUTPUTSHARED_EXPORT IOOutput
{

public:
    IOOutput();
};
extern "C" Q_DECL_EXPORT QWidget* GetWidget();

#endif // IOOUTPUT_H
