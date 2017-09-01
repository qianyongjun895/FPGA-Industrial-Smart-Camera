#include "InfernoUI.h"
#include <QApplication>
#include <QSharedMemory>
#include <QThread>
#include <QFile>
#include <QMutex>
#include "Comm/keyBoard/frminput.h"
#include "Comm/GlobalParameter.h"
#include "Comm/OSDStyle.h"
#include "BusinessData/InterfaceLib/LibTaskXMLParse.h"
#include "Comm/FileIniControl.h"
#include "../Global/UtilitiesFun.h"
#include "LinkDataGlobal.h"
#include <qdebug.h>
#include "calc_common.h"
#include "LinkDataGlobal.h"
#include "sszn_basic.h"
#include "ProtocolInitGlobal.h"
#include "ProtocolManageGlobal.h"
#include "UartGlobal.h"
#include "TcpGlobal.h"
#include "UdpGlobal.h"
#include "ModbusGlobal.h"
#include "IOInitGlobal.h"
#include "TaskRstGlobal.h"
#include "io.h"
#include "cmos_common.h"
#include "System.h"
#include "IntercomModbusGlobal.h"
#include "UserDefinedGlobal.h"
#include "MitFxPlcGlobal.h"
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;
       switch(type)
       {
       case QtDebugMsg:
           text = QString("Debug:");
           break;

       case QtWarningMsg:
           text = QString("Warning:");
           break;

       case QtCriticalMsg:
           text = QString("Critical:");
           break;

       case QtFatalMsg:
           text = QString("Fatal:");
       }

       QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
       QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
       QString current_date = QString("(%1)").arg(current_date_time);
       QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

        QFile outFile1("/mnt/emmc4/LaVitaNuovaExe/debuglog1.txt");
        QFile outFile2("/mnt/emmc4/LaVitaNuovaExe/debuglog2.txt");
        outFile1.open(QIODevice::WriteOnly | QIODevice::Append);
        if(outFile1.size() >= 1024*10 )
        {
           outFile1.close();
           outFile2.remove();
           QFile::copy("/mnt/emmc4/LaVitaNuovaExe/debuglog1.txt","/mnt/emmc4/LaVitaNuovaExe/debuglog2.txt");
           outFile1.remove();

           QFile outFile3("/mnt/emmc4/LaVitaNuovaExe/debuglog1.txt");
           outFile3.open(QIODevice::WriteOnly | QIODevice::Append);
           QTextStream ts(&outFile3);
           ts << message << endl;
        }
        else
        {
            QTextStream ts(&outFile1);
            ts << message << endl;
        }
        mutex.unlock();
}

/**
 * @brief IsInfernoStart
 * @return 1程序已经启动 0没有启动
 * @author szj
 * @date 2017/05/13
 * @note 应用程序是否已经启动
 */
int IsInfernoStart()
{
    QSharedMemory *shareMem = new QSharedMemory(QString("SingleInferno"));
    volatile short i = 2;
    while (i--)
    {
        if (shareMem->attach(QSharedMemory::ReadOnly))
        {
            shareMem->detach();
        }
    }

    if (!shareMem->create(1))
    {
        if(NULL != shareMem)
        {
            delete shareMem;
            shareMem = NULL;
        }
        return 1;
    }
    return 0;
}
/**
 * @brief attachSyle
 * @return 空
 * @author szj
 * @date 2017/05/13
 * @note 加载控件皮肤
 */
void AttachSyle(QApplication *pApp)
{
    QFile styleFile(":/skin/skin.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString setStyleSheet(styleFile.readAll());
    pApp->setStyleSheet(setStyleSheet);
}
/**
 * @brief SetFont
 * @return 空
 * @author szj
 * @date 2017/05/13
 * @note 设置字体
 */
void SetFont(QApplication *pApp)
{
    QFont font;
    font.setFamily(("SimSun"));
    pApp->setFont(font);
}
/**
 * @brief InitCamera
 * @return 空
 * @author szj
 * @date 2017/05/23
 * @note 初始化相机硬件
 */
void InitCamera()
{
    QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","libzynq");
    //GlobalParameter::g_lib_zynq.IniLib(strlibPath);
    GlobalParameter::g_lib_zynq.IniCamera();
}
/**
 * @brief InitTaskLib
 * @return 空
 * @author szj
 * @date 2017/05/23
 * @note 初始化相机任务
 */
void InitTaskLib()
{
    //QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","libtask");
    //GlobalParameter::g_libTaskFun.IniLib(strlibPath);
    GlobalParameter::g_libTaskFun.Task_Addr_Init();
}
/**
 * @brief InitTaskXmlLib
 * @return 空
 * @author szj
 * @date 2017/05/23
 * @note 初始化相机任务XML数据
 */
void InitTaskXmlLib()
{
    printf("start InitTaskXmlLib\n");
    LibTaskXMLParse m_libXmlParse;
    QString strlibPath = FileIniControl::ReadSettings("./Config/UIIcon.ini","libPath","libtaskparse");
    m_libXmlParse.IniLib(strlibPath);
    printf("m_libXmlParse.IniLib(strlibPath)\n");
    m_libXmlParse.InitTaskXML(strlibPath);
}

void InitLicenseInfo()
{
    initLicenseData();
}

void IniUartModebus(QString Work, int devaddr)
{
    modbus_init();
    if(Work == "从机")
    {
        modbus_slave_or_host_set(MODBUS_SLAVE_TYPE);
    }
    else if(Work == "主机")
    {
        modbus_slave_or_host_set(MODBUS_HOST_TYPE);
    }
    modbus_device_dddress_set(devaddr);
}

void IniTcpModebus(QString Work, int devaddr)
{
    modbus_init();
    if(Work == "服务端")
    {
        modbus_slave_or_host_set(MODBUS_SLAVE_TYPE);
    }
    else if(Work == "客户端")
    {
        modbus_slave_or_host_set(MODBUS_HOST_TYPE);
    }
    modbus_device_dddress_set(devaddr);
}

void SetUartCommModeParam(int Protocol_type)
{
    COMM_UART_CONFIG uart_cfg;
    UART_CONFIG uart_param;
    Get_Uart_Config(&uart_cfg);

    if(Protocol_type == MODBUS_PROTOCOL)
    {
        QString WorkMode = QString::fromUtf8(uart_cfg.work_mode);
        IniUartModebus(WorkMode, uart_cfg.dev_addr);
    }
    uart_param.uartport = uart_cfg.uartport;
    uart_param.baudrate = uart_cfg.baudrate;
    uart_param.databit = uart_cfg.databit;
    QString check = QString::fromUtf8(uart_cfg.verifytype);
    if(check == "无校验")
    {
        uart_param.verifytype = UART_PARITY_BITS_NONE;
    }
    else if(check == "奇校验")
    {
        uart_param.verifytype = UART_PARITY_BITS_ODD;
    }
    else if(check == "偶校验")
    {
        uart_param.verifytype = UART_PARITY_BITS_EVEN;
    }
    uart_param.stopbit = uart_cfg.stopbit;
    uart_config_set(&uart_param);
}

void SetTcpCommModeParam(int Protocol_type)
{
    COMM_TCP_CONFIG tcp_cfg;
    TCP_CONFIG tcp_param;
    Get_Tcp_Config(&tcp_cfg);

    QString WorkMode = QString::fromUtf8(tcp_cfg.work_mode);
    if(Protocol_type == MODBUS_PROTOCOL)
    {
        IniTcpModebus(WorkMode, tcp_cfg.dev_addr);
    }
    if(WorkMode == "服务端")
    {
        tcp_param.net_type = 0;
    }
    else if(WorkMode == "客户端")
    {
        tcp_param.net_type = 1;
    }
    tcp_param.port = tcp_cfg.port;
    memcpy(tcp_param.ip, tcp_cfg.ip, 16);
    tcp_config_set(&tcp_param);
}

void SetUdpCommModeParam(int Protocol_type)
{
    COMM_UDP_CONFIG udp_cfg;
    UDP_CONFIG udp_param;
    Get_Udp_Config(&udp_cfg);

    udp_param.local_port = udp_cfg.local_port;
    udp_param.server_port = udp_cfg.Server_port;
    memcpy(udp_param.ip, udp_cfg.Server_ip, 16);
    udp_config_set(&udp_param);
}

int ProtocolInit(int index)
{
    char libPath[100];
    memset(libPath, 0, 100);
    int ret = Get_Protocol_Lib_Path(index, libPath);
    if(ret == 0)
    {
        typedef void (*InitProtocol)();
        QString Lib_Path = QString::fromUtf8(libPath);
        QLibrary *lib = new QLibrary(Lib_Path);
        InitProtocol Init = (InitProtocol)lib->resolve("InitProtocol");
        if(Init)
        {
            Init();
        }
        else
        {
            return -1;
        }
        lib->unload();
        delete lib;
        lib = NULL;
        return 0;

    }
    else
    {
        return -1;
    }
}

void InitProtocolInfo()
{
    Parse_Protocol_Data();
    char str[100];
    for(int i = 0; ;i++)
    {
        int ret = Get_Protocol_Status(i);
        if(ret == -1)
        {
            return;
        }
        else if(ret == 1)
        {
            memset(str, 0, 100);
            Get_Protocol_Comm_Mode(i, str);
            QString CommString = QString::fromUtf8(str);

            for(int j = 0; ;j++)
            {
                memset(str, 0, 100);
                ret = Get_Comm_Mode_Name(j, str);
                if(ret == -1)
                {
                    break;
                }
                QString CommName = QString::fromUtf8(str);
                if(CommName == CommString)
                {
                    int protocol_type = Get_Protocol_Type(i);
                    int comm_type = Get_Comm_Mode_Type(j);
                    ProtocolInit(i);
                    if(comm_type == 0){
                        SetUartCommModeParam(protocol_type);
                    }else if(comm_type == 1){
                        SetTcpCommModeParam(protocol_type);
                    }else if(comm_type == 2){
                        SetUdpCommModeParam(protocol_type);
                    }
                    protocol_non_block_open(comm_type, protocol_type);
                    return;
                }
            }
        }
    }
}
void InitImageSetData()
{
    int iMsExposure;
    int iUsExposure;
    int value;
    int iStartY;
    int iEndY;
    int iHeight =0;
    int m_rotate_type;
    int iGain;
    unsigned int iR;
    unsigned  int iB;
    QString strTaskPath = "/mnt/emmc2/task/tmp/ImageSet.ini";
    QFile file(strTaskPath);

    if(!file.exists())
    {
        strTaskPath = "./Config/UIIcon.ini";
        QString strPath = "/mnt/emmc2/task/tmp/ImageSet.ini";

        iMsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","mExplosion").toInt();
        iUsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","uExplosion").toInt();
        iStartY = FileIniControl::ReadSettings(strTaskPath,"imageSet","startY").toInt();
        iEndY =FileIniControl::ReadSettings(strTaskPath,"imageSet","endY").toInt();
        m_rotate_type = (unsigned char)FileIniControl::ReadSettings(strTaskPath,"imageSet","ImageRollovers").toInt();
        iGain = FileIniControl::ReadSettings(strTaskPath,"imageSet","gain").toInt();
        iR = FileIniControl::ReadSettings(strTaskPath,"imageSet","R").toInt();
        iB = FileIniControl::ReadSettings(strTaskPath,"imageSet","B").toInt();

        FileIniControl::WriteSettings(strPath,"imageSet","mExplosion",QString::number(iMsExposure));
        FileIniControl::WriteSettings(strPath,"imageSet","uExplosion",QString::number(iUsExposure));
        FileIniControl::WriteSettings(strPath,"imageSet","gain",QString::number(iGain));
        FileIniControl::WriteSettings(strPath,"imageSet","startY",QString::number(iStartY));
        FileIniControl::WriteSettings(strPath,"imageSet","endY",QString::number(iEndY));
        FileIniControl::WriteSettings(strPath,"imageSet","R",QString::number(iR));
        FileIniControl::WriteSettings(strPath,"imageSet","B",QString::number(iB));
        FileIniControl::WriteSettings(strPath,"imageSet","ImageRollovers",QString::number(m_rotate_type));
    }else
    {
        iMsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","mExplosion").toInt();
        iUsExposure = FileIniControl::ReadSettings(strTaskPath,"imageSet","uExplosion").toInt();
        iStartY = FileIniControl::ReadSettings(strTaskPath,"imageSet","startY").toInt();
        iEndY =FileIniControl::ReadSettings(strTaskPath,"imageSet","endY").toInt();
        m_rotate_type = (unsigned char)FileIniControl::ReadSettings(strTaskPath,"imageSet","ImageRollovers").toInt();
        iGain = FileIniControl::ReadSettings(strTaskPath,"imageSet","gain").toInt();
        iR = FileIniControl::ReadSettings(strTaskPath,"imageSet","R").toInt();
        iB = FileIniControl::ReadSettings(strTaskPath,"imageSet","B").toInt();
    }

    value = iMsExposure*1000+iUsExposure;
    GlobalParameter::g_lib_zynq.Set_Exposure(value);
    UtilitiesFun::Instance()->SetCmosLimit(iStartY,iEndY);

    iHeight =0;
    iHeight = iEndY - iStartY;

    if(m_rotate_type == 0)
    {
        Set_HWC_CMOS_Flip(IMAGE_NORMAL);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
    }
    else if(m_rotate_type == 1)
    {
        Set_HWC_CMOS_Flip(IMAGE_LEFT_RIGHT_INVERT);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(iStartY, iHeight, m_rotate_type);
    }
    else if(m_rotate_type == 2)
    {
        Set_HWC_CMOS_Flip(IMAGE_UP_DOWN_INVERT);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
    }
    else if(m_rotate_type == 3)
    {
        Set_HWC_CMOS_Flip(IMAGE_TWO_DIR_INVERT);
        UtilitiesFun::Instance()->Set_rotate_type(m_rotate_type);
        UtilitiesFun::Instance()->SetCPTCmosStartYAndHeight(480-iEndY, iHeight, m_rotate_type);
    }
    GlobalParameter::g_lib_zynq.Set_Gain(iGain);
    White_Balance_Param_Set(MANUAL_WHITE_BALANCE,&iR,&iB);

}
void Init_IO_Output_Param()
{
    unsigned int index = 0;
    IO_OUTPUT_CONFIG IO_Output_Param;
    IO_Output_Param.IO_sum = 4;
    for(index = 0; index < IO_Output_Param.IO_sum; index++){
        int ret = Get_IO_Width(index, &IO_Output_Param.width[index]);
        if(ret != 0){
            break;
        }
    }
    Get_IO_Valid_Flag(&IO_Output_Param.IO_valid_flag);
    IO_Output_Config_Set(&IO_Output_Param);
}

void Init_Flash_Output_Param()
{
    FLASH_OUTPUT_CONFIG Flash_Output_Param;
    Get_Flash_Output_Param(&Flash_Output_Param.flash_width, &Flash_Output_Param.flash_valid_flag);
    Flash_Output_Config_Set(&Flash_Output_Param);
}

void Init_IO_Trigger_Param()
{
    IO_TRIGGER_CONFIG IO_Trigger_Param;
    Get_IO_Trigger_Param(0, &IO_Trigger_Param.IO1_delay, &IO_Trigger_Param.IO1_jitters_timer);
    Get_IO_Trigger_Param(1, &IO_Trigger_Param.IO2_delay, &IO_Trigger_Param.IO2_jitters_timer);
    IO_Trigger_Config_Set(&IO_Trigger_Param);
}

void InitIOInfo()
{
    int ret = IO_Config_Init();
    if(ret == 0){
        Init_IO_Output_Param();
        Init_Flash_Output_Param();
        Init_IO_Trigger_Param();
    }
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //判断应用程序是否已经启动
    //qInstallMessageHandler(customMessageHandler);
    if(IsInfernoStart() == 1)
        return 0;
    //设置字体
    SetFont(&a);
    //初始化键盘
    frmInput::Instance()->Init("bottom", "black", 16, 16);
    //加载皮肤
    AttachSyle(&a);
    //初始相机硬件信息
    InitCamera();
    //初始化认证信息
    InitLicenseInfo();
    //初始化相机任务
    InitTaskLib();
    //初始化相机任务XML数据
    InitTaskXmlLib();
    //Sin\Cos数据表
    SinCos_Lut_Init();

    _roiInitLookupTables();
    //初始化任务的结果字符串及关联定位相关的函数
    Init_Link_Data();
    //初始化通信协议的配置
    modbus_init();
    user_defined_init();
    mit_fx_plc_init();
    intercom_modbus_init();
    InitProtocolInfo();
    comm_data_list_load_from_file();
    //初始化IO的配置
    InitIOInfo();
    //初始化图像数据
    InitImageSetData();

    G_Rst_Data_Init();
    Multi_Cmos_Param_Init();


    OSDStyle::iniColorPen();
    OSDStyle::InitOSDConfig(1);
    OSDStyle::InitPenStyle();

    InfernoUI w;
    w.show();
    return a.exec();
}
