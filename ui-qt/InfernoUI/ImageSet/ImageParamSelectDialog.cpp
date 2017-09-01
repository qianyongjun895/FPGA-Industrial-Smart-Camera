#include "ImageParamSelectDialog.h"
#include "ui_ImageParamSelectDialog.h"
#include "MultiCmosParam.h"
#include <QLabel>
#include <QListWidgetItem>
#include <QMessageBox>
ImageParamSelectDialog::ImageParamSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageParamSelectDialog)
{
    ui->setupUi(this);
    for(int i = 0; i < CMOS_PARAM_NUM_MAX; i++){
        M_CMOS_PARAM coms_param;
        int ret = M_Cmos_Param_Get(i, &coms_param);
        if(ret != 0){
            continue;
        }
        QLabel *label = new QLabel;
        label->setText("参数"+QString::number(i+1));
        QFont font;
        font.setPixelSize(20);
        label->setFont(font);
        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget_Image_Param_Select);
        ui->listWidget_Image_Param_Select->setItemWidget(listItem, (QWidget*)label);
        ui->listWidget_Image_Param_Select->item(i)->setSizeHint(QSize(200,31));
    }
}

ImageParamSelectDialog::~ImageParamSelectDialog()
{
    delete ui;
}

void ImageParamSelectDialog::on_pushButton_Select_Param_OK_clicked()
{
    int current_index = ui->listWidget_Image_Param_Select->currentRow();
    if(current_index < 0){
//        QMessageBox::warning(NULL, "警告", "请选择coms参数!", QMessageBox::Yes, QMessageBox::Yes || QMessageBox::No);
//        return;
        Select_Param_index = 0;
    }else{
        Select_Param_index = current_index+1;
    }
    QDialog::accept();
}

void ImageParamSelectDialog::on_pushButton_Select_Param_Cancel_clicked()
{
    QDialog::reject();
}

int ImageParamSelectDialog::GetSelectParamIndex()
{
    return Select_Param_index;
}
