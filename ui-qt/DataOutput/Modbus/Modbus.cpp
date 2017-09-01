#include "Modbus.h"
#include "ModbusWidget.h"
#include "ModbusGlobal.h"

ModbusWidget *P_Widget = NULL;

Modbus::Modbus()
{
}


/**
 * @brief 协议的初始化函数
 * @param void
 * @return void
 * @author <th>
 * @note 在GetWidget函数前调用，是注册协议的初始化函数，不是ui的初始化函数
 */
extern "C" Q_DECL_EXPORT void InitProtocol()
{
    modbus_init();
}

/**
 * @brief 获取UI的QWidget指针
 * @param void
 * @return UI的QWidget指针
 * @author <th>
 * @note
 */
extern "C" Q_DECL_EXPORT QWidget *GetWidget()
{
    P_Widget = new ModbusWidget();
    return  P_Widget;
}

/**
 * @brief show UI的QWidget之前的初始化函数
 * @param void
 * @return void
 * @author <th>
 * @note
 */
extern "C" Q_DECL_EXPORT void InitShowData()
{
    P_Widget->IniSlaveOrHost();
}

/**
 * @brief 设置协议的数据
 * @param void
 * @return void
 * @author <th>
 * @note
 */
extern "C" Q_DECL_EXPORT void SetProtocolData()
{
    P_Widget->SetModbusData();
}


