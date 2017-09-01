#include "ResetCameraDialog.h"
#include "ui_ResetCameraDialog.h"
#include "SystemSet/Upgrade/UpgradeWidget.h"
#include "SystemSet/LicenseInfo/LicenseInfo.h"

ResetCameraDialog::ResetCameraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetCameraDialog)
{
    ui->setupUi(this);
    m_ViewLayout = new QGridLayout;
    ui->btnClose->hide();
}

ResetCameraDialog::~ResetCameraDialog()
{    
    DeleteWidgetInLayout();
    delete ui;
}

void ResetCameraDialog::ShowDnaErrorPanel()
{
    DeleteWidgetInLayout();
    ui->label->setText(tr("DNA错误"));
    UpgradeWidget *upgradeWidget = new UpgradeWidget;
    upgradeWidget->resize(800,600);
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(upgradeWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
    this->exec();
}

void ResetCameraDialog::ShowLicenseExpirePanel()
{
    DeleteWidgetInLayout();
    ui->label->setText(tr("已到期"));
    LicenseInfo *licenseWidget = new LicenseInfo;
    connect(licenseWidget, &LicenseInfo::LicensePass, this, &ResetCameraDialog::closeBtnShow);
    licenseWidget->resize(800,600);
    m_ViewLayout->setContentsMargins(0,0,0,0);
    m_ViewLayout->addWidget(licenseWidget, 0, 0);
    ui->widget->setLayout(m_ViewLayout);
    this->exec();
}

void ResetCameraDialog::closeBtnShow()
{
    ui->label->setText(tr("认证通过"));
    ui->btnClose->show();
}

void ResetCameraDialog::DeleteWidgetInLayout()
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

void ResetCameraDialog::on_btnClose_clicked()
{
    this->close();
}
