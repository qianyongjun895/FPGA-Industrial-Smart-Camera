#include "HansRobothProtocol.h"
#include "HansRobothWidget.h"
#include "HansRobotGlobal.h"
HansRobothWidget *P_Widget = NULL;
HansRobothProtocol::HansRobothProtocol()
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
    hans_robot_init();
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
    P_Widget = new HansRobothWidget();
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
}

