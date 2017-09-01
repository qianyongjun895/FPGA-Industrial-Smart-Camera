#ifndef MITFXPLC_H
#define MITFXPLC_H

#include "mitfxplc_global.h"
#include <QWidget>
class MITFXPLCSHARED_EXPORT MitFxPlc
{

public:
    MitFxPlc();
};

/**
 * @brief 获取UI的QWidget指针
 * @param void
 * @return UI的QWidget指针
 * @author <th>
 * @note
 */
extern "C" Q_DECL_EXPORT QWidget *GetWidget();

/**
 * @brief 设置协议的数据
 * @param void
 * @return void
 * @author <th>
 * @note
 */
extern "C" Q_DECL_EXPORT void SetProtocolData();

/**
 * @brief show UI的QWidget之前的初始化函数
 * @param void
 * @return void
 * @author <th>
 * @note
 */
extern "C" Q_DECL_EXPORT void InitShowData();

/**
 * @brief 协议的初始化函数
 * @param void
 * @return void
 * @author <th>
 * @note 在GetWidget函数前调用，是注册协议的初始化函数，不是ui的初始化函数
 */
extern "C" Q_DECL_EXPORT void InitProtocol();
#endif // MITFXPLC_H
