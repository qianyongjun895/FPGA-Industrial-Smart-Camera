#include "SystemSetWiget.h"
#include "ui_SystemSetWiget.h"
#include "Comm/ControlStyle.h"
#include "TouchScreenCalibrate/TouchScreenCalibrate.h"
#include "VersionInfo/VersionInfo.h"
#include "LicenseInfo/LicenseInfo.h"
#include "NetWork/NetWork.h"
#include "UserManage/AdminWidget.h"
#include "Upgrade/UpgradeWidget.h"
#include "TaskImportExport/TaskImportExport.h"
#include "ScriptImportExport/ScriptImportExport.h"
#include "AddToolFiles/AddToolFiles.h"
#include "Comm/GlobalParameter.h"

SystemSetWiget::SystemSetWiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSetWiget)
{
    ui->setupUi(this);

    m_btn_pre = NULL;
    m_ViewLayout = new QGridLayout;

    if (GlobalParameter::g_user_mode == 0)
    {
        ui->btnToolFile->hide();
    }
    else
    {
        ui->btnToolFile->show();
    }

    // 默认显示版本信息页面
    on_btnVersions_clicked();
}

SystemSetWiget::~SystemSetWiget()
{
    delete ui;
}

void SystemSetWiget::DeleteWidgetInLayout()
{
    for(int i=0; i<m_ViewLayout->count(); ++ i)
    {

        QWidget* widget = m_ViewLayout->itemAt(i)->widget();
        m_ViewLayout->removeWidget(widget);
        //widget->hide();
        widget->setParent(0);

        if(widget != NULL)
        {
            delete widget;
            widget = NULL;
        }
    }
}

void SystemSetWiget::SetButtonStyle(QPushButton *pre, QPushButton *current)
{
    if(pre != NULL)
    {
        pre->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    if(current != NULL)
    {
        current->setStyleSheet("background-color: rgb(249, 220, 117);");
    }
}

void SystemSetWiget::on_btnTsCalibrate_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnTsCalibrate);
    m_btn_pre = ui->btnTsCalibrate;
    ui->groupBox->show();

    TouchScreenCalibrate *iWidget = new TouchScreenCalibrate;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnVersions_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnVersions);
    m_btn_pre = ui->btnVersions;
    ui->groupBox->show();

    VersionInfo *iWidget = new VersionInfo;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnLicenseInfo_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnLicenseInfo);
    m_btn_pre = ui->btnLicenseInfo;
    ui->groupBox->show();

    LicenseInfo *iWidget = new LicenseInfo;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnNetWork_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnNetWork);
    m_btn_pre = ui->btnNetWork;
    ui->groupBox->show();

    NetWork *iWidget = new NetWork;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnAdmin_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnAdmin);
    m_btn_pre = ui->btnAdmin;
    ui->groupBox->show();

    AdminWidget *iWidget = new AdminWidget;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnUpgrade_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnUpgrade);
    m_btn_pre = ui->btnUpgrade;
    ui->groupBox->show();

    UpgradeWidget *iWidget = new UpgradeWidget;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnTaskFile_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnTaskFile);
    m_btn_pre = ui->btnTaskFile;
    ui->groupBox->hide();

    TaskImportExport *iWidget = new TaskImportExport;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnScriptFile_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnScriptFile);
    m_btn_pre = ui->btnScriptFile;
    ui->groupBox->hide();

    ScriptImportExport *iWidget = new ScriptImportExport;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}

void SystemSetWiget::on_btnToolFile_clicked()
{
    DeleteWidgetInLayout();
    SetButtonStyle(m_btn_pre, ui->btnToolFile);
    m_btn_pre = ui->btnToolFile;
    ui->groupBox->show();

    AddToolFiles *iWidget = new AddToolFiles;
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(iWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
}
