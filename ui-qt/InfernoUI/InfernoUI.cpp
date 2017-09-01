#include "InfernoUI.h"
#include "ui_InfernoUI.h"
#include <QDir>
#include <qdebug.h>
#include <QMessageBox>
#include "Tool/MainPanel/ToolIconMenuMainWnd.h"
#include "Home/HomeWidget.h"
#include "ImageSet/ImageSetWidget.h"
#include "SystemSet/SystemSetWiget.h"
#include "Comm/FileIniControl.h"
#include "Comm/ControlStyle.h"
#include "Comm/GlobalParameter.h"
#include "SystemSet/UserManage/LoginDialog.h"
#include "DataOutput/DataOutputWidget.h"
#include <qmap.h>
#include "CalibrationWidget/CalibrationWidget.h"
#include "ResetCameraDialog.h"
#include "sszn_basic.h"

InfernoUI::InfernoUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InfernoUI)
{
    ui->setupUi(this);
    m_btn_pre = NULL;
    m_frm = NULL;
    IniNavigation();
    IniMainWidget();
    SetBtnEnable(0);

    ResetCameraDialog rsDlg;
    // 检查 DNA
    int dnaRight = isDNARight();
    if (dnaRight != 0)
    {
        rsDlg.ShowDnaErrorPanel();
    }
    // 检查权限是否到期
    int licenseExpire = isLicenseExpire();
    if (licenseExpire == 1)
    {
        rsDlg.ShowLicenseExpirePanel();
    }
}

InfernoUI::~InfernoUI()
{
    DeleteWidgetInLayout();

    if(MainViewLayout != NULL)
    {
        delete MainViewLayout;
        MainViewLayout = NULL;
    }
    delete ui;
}
void InfernoUI::IniMainWidget()
{
    MainViewLayout = new QGridLayout();
    MainViewLayout->setContentsMargins(0, 0, 0, 0);
    on_btnHome_clicked();
    ((HomeWidget*)m_frm)->SetBtnEnable(0);
    QString isRun = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","AutoRun");

    if(isRun.toInt() == 1)
    {
        on_btnRun_clicked();
        ui->btnAdmin->setEnabled(false);
    }

}
void InfernoUI::IniNavigation()
{
    IniNavigationButtonStyle(ui->btnHome,"buttonHome");
    IniNavigationButtonStyle(ui->btnImage,"buttonImage");
    IniNavigationButtonStyle(ui->btnTool,"butttonTool");
    IniNavigationButtonStyle(ui->btnDataOut,"butttonDataOut");
    IniNavigationButtonStyle(ui->btnCalibrat,"butttonCalibrat");
    IniNavigationButtonStyle(ui->btnSysSet,"butttonSysSet");
    IniNavigationButtonStyle(ui->btnAdmin,"butttonAdmin");
    IniNavigationButtonStyle(ui->btnRun,"butttonRun");
    IniNavigationButtonStyle(ui->btnRunStep,"butttonRunStep");
}
void InfernoUI::IniNavigationButtonStyle(QToolButton *btn,QString strKey)
{
    QString strPicName = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno",strKey);
    QPixmap pixMatch(strPicName);
    btn->setIcon(QIcon(pixMatch.scaled(QSize(48,48))));
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setStyleSheet("background-color: rgb(150,150,150)");
    /*btn->setStyleSheet("background-color: rgb(77, 77, 77);"
                       "color:rgb(255,255,255);");*/
}

void InfernoUI::AddQWidget(QWidget *qWidget)
{
    MainViewLayout->addWidget(qWidget, 0, 0);
    ui->widgetContent->setLayout(MainViewLayout);
}
void InfernoUI::DeleteWidgetInLayout()
{
    for(int i=0; i<MainViewLayout->count(); ++i)
    {
        QWidget* widget = MainViewLayout->itemAt(i)->widget();
        MainViewLayout->removeWidget(widget);
        if(widget !=NULL)
        {
            delete widget;
            widget = NULL;
        }
    }
}

void InfernoUI::on_btnHome_clicked()
{
    if(m_btn_pre == ui->btnHome)
        return;
    DeleteWidgetInLayout();
    m_frm = new HomeWidget;
    connect((HomeWidget*)m_frm,&HomeWidget::TaskRunSignal,this,&InfernoUI::ControlSetEnable);
    AddQWidget(m_frm);
    ControlStyle::SetToolButtonStyle(m_btn_pre,ui->btnHome);
    m_btn_pre = ui->btnHome;
}
void InfernoUI::on_btnImage_clicked()
{
    if(m_btn_pre == ui->btnImage)
        return;
    m_frm = new ImageSetWidget;
    AddQWidget(m_frm);
    DeleteWidgetInLayout();
    ControlStyle::SetToolButtonStyle(m_btn_pre,ui->btnImage);
    m_btn_pre = ui->btnImage;
}
void InfernoUI::on_btnTool_clicked()
{
    if(m_btn_pre == ui->btnTool)
        return;
    DeleteWidgetInLayout();
    m_frm = new ToolIconMenuMainWnd;
    AddQWidget(m_frm);
    ControlStyle::SetToolButtonStyle(m_btn_pre,ui->btnTool);
    m_btn_pre = ui->btnTool;
}
void InfernoUI::on_btnDataOut_clicked()
{
    if(m_btn_pre == ui->btnDataOut)
        return;
    DeleteWidgetInLayout();
    m_frm = new DataOutputWidget;
    AddQWidget(m_frm);
    DataOutputWidget(m_frm);
    ControlStyle::SetToolButtonStyle(m_btn_pre,ui->btnDataOut);
    m_btn_pre = ui->btnDataOut;
}
void InfernoUI::on_btnCalibrat_clicked()
{
    if(m_btn_pre == ui->btnCalibrat)
        return;
    DeleteWidgetInLayout();
    m_frm = new CalibrationWidget;
    AddQWidget(m_frm);
    ControlStyle::SetToolButtonStyle(m_btn_pre,ui->btnCalibrat);
    m_btn_pre = ui->btnCalibrat;
}
void InfernoUI::on_btnSysSet_clicked()
{
    if(m_btn_pre == ui->btnSysSet)
        return;
    DeleteWidgetInLayout();
    m_frm = new SystemSetWiget;
    AddQWidget(m_frm);
    ControlStyle::SetToolButtonStyle(m_btn_pre,ui->btnSysSet);
    m_btn_pre = ui->btnSysSet;
}
void InfernoUI::SetBtnEnable(int bflag,int runflag)
{
    ui->btnRun->setEnabled(bflag);
    ui->btnRunStep->setEnabled(bflag);
    ui->btnHome->setEnabled(bflag);
    ui->btnImage->setEnabled(bflag);
    ui->btnTool->setEnabled(bflag);
    ui->btnDataOut->setEnabled(bflag);
    ui->btnSysSet->setEnabled(bflag);
    ui->btnCalibrat->setEnabled(bflag);

    if(runflag == 1)
        ui->btnAdmin->setEnabled(bflag);
}
//登录
void InfernoUI::on_btnAdmin_clicked()
{
    if(GlobalParameter::g_login== 1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"), tr("确定要注销管理员权限?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            GlobalParameter::g_login = 0;
            on_btnHome_clicked();
            SetBtnEnable(0);
            if(m_frm != NULL)
            {
                ((HomeWidget*)m_frm)->SetBtnEnable(0);
            }
        }
    }else
    {
        LoginDialog login;
        int ret = login.exec();
        if(ret == QDialog::Accepted)
        {
            GlobalParameter::g_login = 1;
            SetBtnEnable(1);
            if(m_frm != NULL)
            {
                ((HomeWidget*)m_frm)->SetBtnEnable(1);
            }
        }
    }
}
//运行
void InfernoUI::on_btnRun_clicked()
{
    if(m_btn_pre != ui->btnHome)
    {
        on_btnHome_clicked();
    }
    if(m_btn_pre == ui->btnHome)
        ((HomeWidget*)m_frm)->BeginRunTask();
    ui->btnAdmin->setEnabled(false);

}
//单步运行
void InfernoUI::on_btnRunStep_clicked()
{
    ControlSetEnable(1);
    if(m_btn_pre == ui->btnTool)
    {
        connect((ToolIconMenuMainWnd*)m_frm,&ToolIconMenuMainWnd::TaskRunSignal,this,&InfernoUI::ControlSetEnable);
        ((ToolIconMenuMainWnd*)m_frm)->StepExcecute();
    }else
    {
        ControlSetEnable(0);
        QMessageBox::about(NULL,tr("提示"),tr("请在工具界面下应用此功能"));
    }
}

void InfernoUI::ControlSetEnable(bool flag)
{

    if(GlobalParameter::g_login == 1)
    {
        ui->btnAdmin->setEnabled(!flag);
        ui->btnHome->setEnabled(!flag);
        ui->btnImage->setEnabled(!flag);
        ui->btnTool->setEnabled(!flag);
        ui->btnDataOut->setEnabled(!flag);
        ui->btnCalibrat->setEnabled(!flag);
        ui->btnSysSet->setEnabled(!flag);
        ui->btnRun->setEnabled(!flag);
        ui->btnRunStep->setEnabled(!flag);
    }else
    {
        if(flag == 1)
            ui->btnAdmin->setEnabled(false);
        else
            ui->btnAdmin->setEnabled(true);
    }
}
