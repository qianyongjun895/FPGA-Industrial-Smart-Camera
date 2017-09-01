#ifndef HANSROBOTGLOBAL_H
#define HANSROBOTGLOBAL_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "UartGlobal.h"
#include "TcpGlobal.h"
#include "UdpGlobal.h"


/**
  * @struct  <HANS_ROBOT_COMM>
  * @brief  HansRobot命令结构体
  */
typedef struct {
    unsigned char command[50];
} HANS_ROBOT_COMM;

/**
  * @struct  <HANS_ROBOT_COMM>
  * @brief  HansRobot参数共用体
  */
typedef union{
	int inum;     ///<整型
	double dnum;  ///<双精度型
}HANS_RBT_UNION;

/**
  * @struct  <HANS_ROBOT_COMM>
  * @brief  HansRobot参数结构体
  */
typedef struct{
	int data_type;        ///<数据类型
	HANS_RBT_UNION param; ///<参数
}HANS_RBT_PARAM;

/**
  * @enum  <HANS_ROBOT_ID>
  * @brief  HansRobot命令ID枚举
  */
typedef enum {
    Electrify = 0,                  ///< 机器人上电
    BlackOut,                       ///< 机器人断电
    StartMaster,                    ///< 启动主站
    CloseMaster,                    ///< 关闭主站
    GrpPowerOn,                     ///< 使能机器人
    GrpPowerOff,                    ///< 去使能机器人
    GrpStop,                        ///< 机器人急停
    GrpReset,                       ///< 复位，用于清除错误
    MoveHoming,                     ///< 机器人回到原点
    MoveJ,                          ///< 机器人运动到指定的角度坐标位置
    MoveL,                          ///< 机器人直线运动到指定的空间坐标位置
    MoveP,                          ///< 机器人运动到指定的空间坐标位置
    MoveB,                          ///< 立即将机器人当前运动的终点更改为指定的空间坐标位置
    MoveRelL,                       ///< 机器人指定空间坐标轴运动一段距离
    MoveRelJ,                       ///< 机器人指定角度坐标轴运动一段距离
    ShortJogJ,                      ///< 角度运动，固定距离运动
    ShortJogL,                      ///< 空间运动，固定距离运动
    LongJogJ,                       ///< 角度运动，不固定距离运动
    LongJogL,                       ///< 空间运动，不固定距离运动
    SetConveyorScale,               ///< 设置传送带比例
    SetHomePosition,                ///< 设置机械原点
    SetKinematicCoordinate,         ///< 设置刀具坐标
    SetUserCoordinate,              ///< 设置用户坐标
    SetOverride,                    ///< 设置速度比
    SetSpeedUp,                     ///< 加速
    SetSpeedDown,                   ///< 减速
    SetOutIOState,                  ///< 设置输出IO 状态
    SetAcsSafeSpaceLimit,           ///< 设置角度安全范围
    SetPcsSafeSpaceLimit,           ///< 设置空间安全范围
    SetSerialDO,                    ///< 设置串口输出IO 状态
    SetTrackingSwitch,              ///< 设置控制跟随开关
    UpdateSystemPointInfo,          ///< 系统点位更新
    ReadSystemPointInfo,            ///< 读取系统点位
    ReadAcsActualPos,               ///< 读取角度坐标实际位置
    ReadPcsActualPos,               ///< 读取空间坐标实际位置
    ReadAnalogInput,                ///< 读取模拟输入的值
    ReadOverride,                   ///< 读取速度
    ReadConveyorValue,              ///< 读取传送带编码器的值
    ReadInIOState,                  ///< 读取输入IO 的状态
    ReadOutIOState,                 ///< 读取输出IO 的状态
    ReadMoveState,                  ///< 读取机器人的运动状态
    ReadMultiEndatPos,              ///< 读取机器人当前轴多圈绝对位置
    ReadMultiInIOState,             ///< 读取多个输入IO 的状态
    ReadMultiOutIOState,            ///< 读取多个输出IO 的状态
    ReadRobotState,                 ///< 读取机器人的状态
    ReadSerialAllDI,                ///< 获取整个串口数字输入的状态
    ReadSerialAllDO,                ///< 获取整个串口数字输出的状态
    ReadSerialDI,                   ///< 获取串口指定的数字输入位的状态
    ReadSerialDO,                   ///< 获取串口指定的数字输出位的状态
    ReadCurrentScript,              ///< 读取默认脚本
    ScriptCompile,                  ///< 编译默认脚本
    RobotCommandMax
}HANS_ROBOT_ID;

/**
  * @enum  <HANS_RBT_REL>
  * @brief  MoveRel（指定坐标轴运动）命令对应参数的枚举
  */
typedef enum {
    REL_RBTID = 0,          ///< 机器人索引，从0 开始计数
    REL_AXISID,             ///< 空间坐标轴ID，从0 开始计数
    REL_DIRECTION,          ///< 运动方向：0=负向；1=正向；
    REL_DISTANCE,           ///< 相对运动距离，X、Y、Z 单位毫米，A、B、C 单位度
} HANS_RBT_REL;

/**
  * @enum  <HANS_RBT_JOG>
  * @brief  JOG（角度运动）命令对应参数的枚举
  */
typedef enum {
    JOG_RBTID = 0,          ///< 机器人索引，从0 开始计数
    JOG_AXISID,             ///< 点动轴ID(0-5)(0:X,1:Y,2:Z,3:A,4:B,5:C)
    JOG_DERECTION           ///< 运动方向：0=负向；1=正向；
} HANS_RBT_JOG;

/**
  * @enum  <HANS_RBT_PCS_POS>
  * @brief  PceActualPos（空间坐标实际位置）相关命令对应参数的枚举
  */
typedef enum {
    PCS_RBTID = 0,          ///< 机器人索引，从0 开始计数
    PCS_X,                  ///< X 轴位置，单位：毫米
    PCS_Y,                  ///< Y 轴位置，单位：毫米
    PCS_Z,                  ///< Z 轴位置，单位：毫米
    PCS_A,                  ///< A 轴位置，单位：度
    PCS_B,                  ///< B 轴位置，单位：度
    PCS_C                   ///< C 轴位置，单位：度
} HANS_RBT_PCS_ACTUAL_POS;


/**
 * @brief hans_robot_init
 * @return 0：失败，1：成功
 * @author pml
 * @date 2017/6/9
 * @note hansrobot协议初始化
 */
int hans_robot_init(void);

/**
 * @brief hans_robot_uart_config_get
 * @param uart
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 设置串口配置信息
 */
void hans_robot_uart_config_set(UART_CONFIG *uart);

/**
 * @brief hans_robot_uart_config_get
 * @param uart
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取串口配置信息
 */
void hans_robot_uart_config_get(UART_CONFIG *uart);

/**
 * @brief hans_robot_tcp_config_set
 * @param tcp
 * @author pml
 * @date 2017/5/12
 * @note 设置TCP配置信息
 */
void hans_robot_tcp_config_set(TCP_CONFIG *tcp);

/**
 * @brief hans_robot_tcp_config_get
 * @param tcp
 * @author pml
 * @date 2017/5/12
 * @note 获取TCP配置信息
 */
void hans_robot_tcp_config_get(TCP_CONFIG *tcp);

/**
 * @brief hans_robot_udp_config_set
 * @param udp
 * @author pml
 * @date 2017/5/12
 * @note 设置UDP配置信息
 */
void hans_robot_udp_config_set(UDP_CONFIG *udp);

/**
 * @brief hans_robot_udp_config_get
 * @param udp
 * @author pml
 * @date 2017/5/12
 * @note 获取UDP配置信息
 */
void hans_robot_udp_config_get(UDP_CONFIG *udp);

/**
 * @brief hans_robot_protocol_status_get
 * @return 0:未启动，1：启动
 * @author pml
 * @date 2017/5/12
 * @note 设置串口配置信息
 */
int hans_robot_protocol_status_get(void);

/**
 * @brief hans_robot_homo_comm_open
 * @param comm_way
 * @return 0:失败，1:成功
 * @author pml
 * @date 2017/5/12
 * @note 开启HansRobot协议标定通信
 */
int hans_robot_homo_comm_open(int comm_way);

/**
 * @brief hans_robot_homo_comm_close
 * @param comm_way
 * @return 0:失败，1:成功
 * @author pml
 * @date 2017/5/12
 * @note 关闭HansRobot协议标定通信
 */
int hans_robot_homo_comm_close(int comm_way);

/**
 * @brief Hans_Rbt_Communicate_Data_Splice
 * @param cmd
 * @param array_size
 * @param pdata
 * @return 0：失败，1：成功
 * @author Vincent
 * @date 2017/5/12
 * @note HansRobot命令格式组合及发送
 */
int Hans_Rbt_Communicate_Data_Splice(unsigned int cmd, unsigned int array_size, HANS_RBT_PARAM * pdata);

/**
 * @brief hans_robot_recv_data_get
 * @param pValue
 * @param n
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 获取收到的参数
 */
int hans_robot_recv_data_get(HANS_RBT_PARAM *pValue, int n);

/**
 * @brief WaitRobotMotionFinish
 * @param robot_id
 * @return
 * @author pml
 * @date 2017/5/12
 * @note 等待机器人运动完毕，超时时间1s；
 */
int WaitRobotMotionFinish(int robot_id);


/**
 * @brief hans_robot_phy_coor_get
 * @param pValue
 * @param robot_id
 * @return 实际参数的个数
 * @author pml
 * @date 2017/5/12
 * @note 获取HansRobot的物理坐标
 */
int hans_robot_phy_coor_get(double *pValue, int robot_id);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // HANSROBOTGLOBAL_H
