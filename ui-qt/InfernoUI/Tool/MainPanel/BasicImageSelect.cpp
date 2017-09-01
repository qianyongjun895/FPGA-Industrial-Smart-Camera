#include "BasicImageSelect.h"
#include "ui_BasicImageSelect.h"
#include <QMessageBox>
#include "BusinessData/InterfaceLib/BaseImageData.h"
#include "Comm/FileIniControl.h"
#include "Home/RegisterImageDlg.h"
#include "../Global/UtilitiesFun.h"

BasicImageSelect::BasicImageSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasicImageSelect)
{
    ui->setupUi(this);
    ui->radioButtonBig->setChecked(false);
    ui->radioButtonSmall->setChecked(true);
    ui->listWidgetImage->setIconSize(QSize(64,48));
    //m_str_pic_path = "/mnt/emmc3/picture/BaseImage/thumbnail/";
    m_str_pic_path = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","thumbnailPath");
    IniImageNameList();
}

BasicImageSelect::~BasicImageSelect()
{
    delete ui;
}

void BasicImageSelect::on_btnOk_clicked()
{
    int row = ui->listWidgetImage->currentRow();

    if(row >=0)
    {
        m_pic_name = ui->listWidgetImage->item(row)->text();

    }else
    {
        QMessageBox::about(NULL,tr("Inforation"),tr("Please select row"));
        return;
    }

    QDialog::accept();
}

void BasicImageSelect::on_btnQuit_clicked()
{
    QDialog::reject();
}
void BasicImageSelect::IniImageNameList()
{
    BaseImageData baseImageData;
    QVector<QString> strNameList = baseImageData.GetBaseImageDirAllName();
    int count = strNameList.count();
    ui->listWidgetImage->clear();
    for(int i = 0; i<count;i++)
    {
        AddItemData(strNameList[i]);
    }

}
void BasicImageSelect::AddItemData(QString strName)
{
    ui->listWidgetImage->addItem(strName);
    int count = ui->listWidgetImage->count();
    QListWidgetItem *item = ui->listWidgetImage->item(count-1);
    if(ui->radioButtonBig->isChecked())
        item->setSizeHint(QSize(item->sizeHint().width(), 112));
    else
        item->setSizeHint(QSize(item->sizeHint().width(), 64));
    QString Name;
    Name = m_str_pic_path;
    Name += strName;
    //Name += "_thumbnail.bmp";
    Name += FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","thumbnailLastName");
    item->setIcon(QIcon(QPixmap(Name)));

}

void BasicImageSelect::on_listWidgetImage_clicked(const QModelIndex &index)
{
    int row = index.row();
    if(row >= 0)
    {
        QString strName = ui->listWidgetImage->item(row)->text();
        BaseImageData baseImageData;
        baseImageData.LoadBaseImage(strName);
    }

}

void BasicImageSelect::on_radioButtonBig_clicked()
{
    ui->listWidgetImage->setIconSize(QSize(128,96));

    for(int i= 0; i<ui->listWidgetImage->count();i++)
    {
        QListWidgetItem *item = ui->listWidgetImage->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), 112));
    }
}

void BasicImageSelect::on_radioButtonSmall_clicked()
{
    ui->listWidgetImage->setIconSize(QSize(64,48));

    for(int i= 0; i<ui->listWidgetImage->count();i++)
    {
        QListWidgetItem *item = ui->listWidgetImage->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), 64));
    }
}

void BasicImageSelect::on_btnRegister_clicked()
{
    RegisterImageDlg dlg;
    dlg.exec();
    UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
    IniImageNameList();
}
