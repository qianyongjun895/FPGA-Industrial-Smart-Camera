#include "TouchScreenCalibrate.h"
#include "ui_TouchScreenCalibrate.h"
#include <cstdlib>
#include <QMessageBox>
#include "Comm/CheckMouse.h"
TouchScreenCalibrate::TouchScreenCalibrate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchScreenCalibrate)
{
    ui->setupUi(this);
}

TouchScreenCalibrate::~TouchScreenCalibrate()
{
    delete ui;
}

void TouchScreenCalibrate::on_btnScreenCalibrate_clicked()
{
    CheckMouse check;
    if(check.GetFind() == 1)
    {
        QMessageBox::about(NULL,"提示","不能在外接鼠标情况下使用，谢谢！");
        return;
    }
    QMessageBox::StandardButton rb = \
            QMessageBox::warning(NULL, \
                                 tr("Warning"), \
                                 tr("确定重新校准触摸屏?"), \
                                 QMessageBox::Yes | QMessageBox::No, \
                                 QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        system("/mnt/emmc4/Script/Shell/call_ts_calibrate.sh");
    }

}
