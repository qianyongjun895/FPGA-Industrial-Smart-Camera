#include "ExternalCommWidget.h"
#include "ui_ExternalCommWidget.h"
#include <QMessageBox>
#include "stdio.h"
#include "ProtocolManageGlobal.h"
#include <QDebug>
#include "ProtocolInitGlobal.h"
ExternalCommWidget::ExternalCommWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExternalCommWidget)
{
    ui->setupUi(this);
    m_pWidget = NULL;
    m_Protocol_Widget = NULL;

    Param_Set_Flag = -1;
    Current_Protocol_Type = -1;
    Current_Protocol_index = -1;
    Current_Comm_Mode = -1;
    CommModeLayout = new QGridLayout;
    ProtocolLayout = new QGridLayout;

    m_Comm_Mode1_lib = new QLibrary();
    m_Comm_Mode2_lib = new QLibrary();
    m_Comm_Mode3_lib = new QLibrary();
    CommMode_Lib_Vector.append(m_Comm_Mode1_lib);
    CommMode_Lib_Vector.append(m_Comm_Mode2_lib);
    CommMode_Lib_Vector.append(m_Comm_Mode3_lib);

    m_Protocol1_lib = new QLibrary();
    m_Protocol2_lib = new QLibrary();
    m_Protocol3_lib = new QLibrary();
    m_Protocol4_lib = new QLibrary();
    m_Protocol5_lib = new QLibrary();
    Protocol_Lib_Vector.append(m_Protocol1_lib);
    Protocol_Lib_Vector.append(m_Protocol2_lib);
    Protocol_Lib_Vector.append(m_Protocol3_lib);
    Protocol_Lib_Vector.append(m_Protocol4_lib);
    Protocol_Lib_Vector.append(m_Protocol5_lib);


    EnableCheckTimer = new QTimer;
    connect(EnableCheckTimer, &QTimer::timeout, this, &ExternalCommWidget::CheckEnableFlag);
    IniData();
//    ui->tabWidget->setCurrentIndex(0);
}

ExternalCommWidget::~ExternalCommWidget()
{
    SetProtocolParam();
    DeleteProtocolWidgetInLayout();
    DeleteCommModeWidgetInLayout();

    int num = CommMode_Lib_Vector.count();
    for(int j = 0; j < num; j++)
    {
        QLibrary *lib =  CommMode_Lib_Vector.at(j);
        if(lib->isLoaded())
        {
            lib->unload();
        }
        delete lib;
        lib = NULL;
    }
    int size = Protocol_Lib_Vector.count();
    for(int i = 0; i < size; i++)
    {
        QLibrary *lib =  Protocol_Lib_Vector.at(i);
        if(lib->isLoaded())
        {
            lib->unload();
        }
        delete lib;
        lib = NULL;
    }
    EnableCheckTimer->stop();
    delete EnableCheckTimer;
    EnableCheckTimer = NULL;
    delete ui;
}

void ExternalCommWidget::SetProtocolParam()
{
    if(Current_Protocol_index < 0 || Param_Set_Flag != 1)
        return;

    QLibrary *lib = Protocol_Lib_Vector.at(Current_Protocol_index);
    if(lib->isLoaded())
    {
        Fun_SetProtocolData SetProtocolData = (Fun_SetProtocolData)lib->resolve("SetProtocolData");
        if(SetProtocolData)
        {
            SetProtocolData();
        }
        else
        {
            QMessageBox::information(NULL,"提示","设置协议数据失败!");
        }
    }
}

void ExternalCommWidget::LoadAllCommLib()
{
    for(int i = 0; ((i < CommMode_Lib_Path_List.count()) && (CommMode_Lib_Vector.count() >= CommMode_Lib_Path_List.count())); i++)
    {
        QLibrary *lib = CommMode_Lib_Vector.at(i);
        lib->setFileName(CommMode_Lib_Path_List.at(i));
        if(!lib->load())
        {
            QMessageBox::about(NULL, tr("提示"), tr("加载")+CommMode_Lib_Path_List.at(i)+tr("失败,原因:")+lib->errorString());
        }
    }

    for(int i = 0; ((i < Protocol_Lib_Path_List.count()) && (Protocol_Lib_Vector.count() >= Protocol_Lib_Path_List.count())); i++)
    {
        QLibrary *lib = Protocol_Lib_Vector.at(i);
        lib->setFileName(Protocol_Lib_Path_List.at(i));
        if(!lib->load())
        {
            QMessageBox::about(NULL, tr("提示"), tr("加载")+Protocol_Lib_Path_List.at(i)+tr("失败,原因:")+lib->errorString());
        }
    }
}

void ExternalCommWidget::GetProtocolXmlData()
{
    int ret = -1;
    char ProtocolName[100];
    char ProtocolLibPath[100];
    char CommModeName[100];
    char CommModeLibPath[100];
    for(int i = 0; ; i++)
    {
        memset(ProtocolName, 0, 100);
        ret = Get_Protocol_Name(i, ProtocolName);
        if(ret == -1)
        {
            break;
        }
        QString str = QString::fromUtf8(ProtocolName);
        Protocol_Name_List.append(str);

        ret = Get_Protocol_Type(i);
        if(ret == -1)
        {
            break;
        }
        Protocol_Type_Hash.insert(i, ret);

        memset(ProtocolLibPath, 0, 100);
        ret = Get_Protocol_Lib_Path(i, ProtocolLibPath);
        if(ret == -1)
        {
            break;
        }
        QString Path = QString::fromUtf8(ProtocolLibPath);
        Protocol_Lib_Path_List.append(Path);
        QStringList CommModeList;
        for(int j = 0; ; j++)
        {
            memset(CommModeName, 0, 100);
            ret = Get_Protocol_CommMode_Name(i, j, CommModeName);
            if(ret == -1)
            {
                break;
            }
            QString CommModeStr = QString::fromUtf8(CommModeName);
            CommModeList.append(CommModeStr);
            CommMode_Type_Hash[i].insert(CommModeStr, j);
        }
        CommMode_Vector.append(CommModeList);
    }
    for(int i = 0; ; i++)
    {
        memset(CommModeName, 0, 100);
        ret = Get_Comm_Mode_Name(i,CommModeName);
        if(ret == -1)
        {
            break;
        }
        QString CommModeNameStr = QString::fromUtf8(CommModeName);
        CommMode_Index_Hash.insert(CommModeNameStr, i);
        Comm_Type_Hash.insert(CommModeNameStr,Get_Comm_Mode_Type(i));

        memset(CommModeLibPath, 0, 100);
        ret = Get_Comm_Mode_Lib_Path(i, CommModeLibPath);
        if(ret == -1)
        {
            break;
        }
        QString CommModePath = QString::fromUtf8(CommModeLibPath);
        CommMode_Lib_Path_List.append(CommModePath);
    }
}

void ExternalCommWidget::IniData()
{
    Parse_Protocol_Data();
    GetProtocolXmlData();
    LoadAllCommLib();
    PROTOCOL_SELECT protocol_status;
    protocol_select_get(&protocol_status);

    ui->selectProtocolcomboBox->addItems(Protocol_Name_List);
    Current_Protocol_index = Protocol_Type_Hash.key(protocol_status.protocol_type);
    ui->selectProtocolcomboBox->setCurrentIndex(Current_Protocol_index);
    int Comm_index = CommMode_Type_Hash[Current_Protocol_index].value(Comm_Type_Hash.key(protocol_status.comm_type));
    ui->ModelSelectComboBox->setCurrentIndex(Comm_index);
    EnableCheckTimer->start(50);
}

void ExternalCommWidget::DeleteProtocolWidgetInLayout()
{
    for(int i=0; i < ProtocolLayout->count(); ++i)
    {
        QWidget* p_widget = ProtocolLayout->itemAt(i)->widget();
        ProtocolLayout->removeWidget(p_widget);
        p_widget->setParent(0);
        if(p_widget !=NULL)
        {
            delete p_widget;
            p_widget = NULL;
        }
    }
}

/** @brief 协议的选择 */
void ExternalCommWidget::on_selectProtocolcomboBox_currentIndexChanged(int index)
{
    if(index < 0)
    {
        return;
    }

    Current_Protocol_index = index;
    Current_Protocol_Type = Protocol_Type_Hash.value(Current_Protocol_index);
    DeleteProtocolWidgetInLayout();
    QLibrary *lib = Protocol_Lib_Vector.at(Current_Protocol_index);
    Fun_InitProtocol InitProtocol = (Fun_InitProtocol)lib->resolve("InitProtocol");
    if(InitProtocol)
    {
        InitProtocol();
    }
    else
    {
        QMessageBox::information(NULL,"提示","获取InitProtocol函数名失败!");
        m_pWidget = NULL;
        return;
    }
    Fun_GetToolWidget GetProtocolWidget = (Fun_GetToolWidget)lib->resolve("GetWidget");
    if(GetProtocolWidget)
    {
        m_Protocol_Widget = GetProtocolWidget();
    }
    else
    {
        m_Protocol_Widget = NULL;
        QMessageBox::information(NULL,"提示","获取GetWidget函数名失败!");
    }
    ui->ModelSelectComboBox->clear();
    ui->ModelSelectComboBox->addItems(CommMode_Vector.at(Current_Protocol_index));
}

void ExternalCommWidget::DeleteCommModeWidgetInLayout()
{
    for(int i=0; i < CommModeLayout->count(); ++i)
    {

        QWidget* p_widget = CommModeLayout->itemAt(i)->widget();
        CommModeLayout->removeWidget(p_widget);
        p_widget->setParent(0);

        if(p_widget !=NULL)
        {
            delete p_widget;
            p_widget = NULL;
        }
    }
}

void ExternalCommWidget::LoadWidget()
{
    if(m_pWidget != NULL)
    {
        CommModeLayout->setContentsMargins(0,0,0,0);
        CommModeLayout->addWidget(m_pWidget, 0, 0);
        ui->CommTypeWidget->setLayout(CommModeLayout);
    }
}

/** @brief 通讯模式的选择 */
void ExternalCommWidget::on_ModelSelectComboBox_currentIndexChanged(int index)
{
    if(index < 0)
    {
        return;
    }
    Current_Comm_Mode = index;
    DeleteCommModeWidgetInLayout();

    int libindex = CommMode_Index_Hash.value(ui->ModelSelectComboBox->currentText());
    QLibrary* lib = CommMode_Lib_Vector.at(libindex);
    Fun_GetToolWidget toolWidget = (Fun_GetToolWidget)lib->resolve("GetWidget");
    if(toolWidget)
    {
        m_pWidget = toolWidget();
    }
    else
    {
        QMessageBox::information(NULL,"提示","获取GetWidget函数名失败!");
        m_pWidget = NULL;
        return;
    }
    Fun_SetProcotolType ProcotolType = (Fun_SetProcotolType)lib->resolve("SetProtocolType");
    if(ProcotolType)
    {
        ProcotolType(Current_Protocol_Type);
    }
    else
    {
        QMessageBox::information(NULL,"提示","获取SetProtocolType函数名失败!");
        return;
    }
    LoadWidget();
}

void ExternalCommWidget::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
    {

    }
    if(index == 1)
    {
        Param_Set_Flag = 0;
//        DeleteProtocolWidgetInLayout();
//        QLibrary *lib = Protocol_Lib_Vector.at(Current_Protocol_index);
//        Fun_GetToolWidget GetProtocolWidget = (Fun_GetToolWidget)lib->resolve("GetWidget");
//        if(GetProtocolWidget)
//        {
//            m_Protocol_Widget = GetProtocolWidget();
//        }
//        else
//        {
//            m_Protocol_Widget = NULL;
//            QMessageBox::information(NULL,"提示","获取GetWidget函数名失败!");
//        }

        if(ui->selectProtocolcomboBox->currentIndex() >= 0)
        {
            QLibrary *lib = Protocol_Lib_Vector.at(ui->selectProtocolcomboBox->currentIndex());
            InitShowData InitShow = (InitShowData)lib->resolve("InitShowData");
            if(InitShow)
            {
                InitShow();
            }
        }
        if(m_Protocol_Widget != NULL)
        {
            ProtocolLayout->setContentsMargins(0,0,0,0);
            ProtocolLayout->addWidget(m_Protocol_Widget, 0, 0);
            ui->Protocol_widget->setLayout(ProtocolLayout);
            Param_Set_Flag = 1;
        }
    }
}

void ExternalCommWidget::CheckEnableFlag()
{
    int libindex = CommMode_Index_Hash.value(ui->ModelSelectComboBox->currentText());
    QLibrary* lib = CommMode_Lib_Vector.at(libindex);
    if(lib->isLoaded())
    {
        typedef bool (*Fun_GetEnableFlag)(void);
        Fun_GetEnableFlag GetEnableFlag = (Fun_GetEnableFlag)lib->resolve("GetEnableFlag");
        if(GetEnableFlag)
        {
            ui->selectProtocolcomboBox->setEnabled(GetEnableFlag());
            ui->ModelSelectComboBox->setEnabled(GetEnableFlag());
        }
    }
}
