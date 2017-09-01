#include "RegisterImageDlg.h"
#include "ui_RegisterImageDlg.h"
#include <QMessageBox>
#include <qdebug.h>
#include "Comm/FileIniControl.h"
#include "BusinessData/InterfaceLib/BaseImageData.h"
#include "../Global/UtilitiesFun.h"
RegisterImageDlg::RegisterImageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterImageDlg)
{
    ui->setupUi(this);
    ui->txtImageName->setText("0");
    ui->txtImageName->installEventFilter(this);
    //m_str_pic_path = "/mnt/emmc3/picture/BaseImage/thumbnail/";
    m_str_pic_path = FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","thumbnailPath");;
    ui->radioButtonBig->setChecked(false);
    ui->radioButtonSmall->setChecked(true);
    ui->listWidgetImage->setIconSize(QSize(64,48));
    IniImageNameList();
    UtilitiesFun::Instance()->ListVGA(ui->labelImage->pos().x(),ui->labelImage->pos().y());
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
}

RegisterImageDlg::~RegisterImageDlg()
{
    delete ui;
    ui->txtImageName->removeEventFilter(this);
}
void RegisterImageDlg::IniImageNameList()
{
    BaseImageData baseImageData;
    QVector<QString> strNameList = baseImageData.GetBaseImageDirAllName();
    int count = strNameList.count();
    int i_max;

    if(count != 0){
        i_max = strNameList.at(count-1).toInt();
    }
    else
        i_max = -1;
    ui->txtImageName->setText(QString::number(i_max+1));

    for(int i = 0; i<count;i++)
    {
        AddItemData(strNameList[i]);
    }

}
void RegisterImageDlg::AddItemData(QString strName)
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
    Name += FileIniControl::ReadSettings("./Config/UIIcon.ini","Inferno","thumbnailLastName");;
    item->setIcon(QIcon(QPixmap(Name)));

}

void RegisterImageDlg::on_btnRegister_clicked()
{
    QString strName = ui->txtImageName->text();

    if(strName == "")
    {
        QMessageBox::about(NULL,tr("提示"),tr("图片名称为空"));
        return;
    }
    int count = ui->listWidgetImage->count();
    if(count >=100)
    {
        QMessageBox::about(NULL,tr("提示"),tr("最多只能注册100张图片"));
        return;
    }

    BaseImageData baseImageData;
    int ret = FindNameInTable(strName);
    if(ret == 1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("图片在表格中"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            ret = baseImageData.SaveBaseImage(strName);

            if(ret == 1){
                int i_max = ui->txtImageName->text().toInt();
                ui->txtImageName->setText(QString::number(i_max+1));
            }
            else
                QMessageBox::about(NULL,tr("提示"),tr("图片保存失败"));
            return;
        }else
        {
            return;
        }
    }

    ret = baseImageData.SaveBaseImage(strName);

    if(ret == 1){
        int i_max = ui->txtImageName->text().toInt();
        ui->txtImageName->setText(QString::number(i_max+1));
        AddItemData(strName);
    }
    else
        QMessageBox::about(NULL,tr("提示"),tr("图片保存失败"));

}

int RegisterImageDlg::FindNameInTable(QString strName)
{
    int ret =0;

    int count = ui->listWidgetImage->count();

    for(int i = 0; i < count; i++)
    {
        QListWidgetItem *item = ui->listWidgetImage->item(i);
        QString strNameTemp = item->text();

        if(strName == strNameTemp)
        {
            ret =1;
            break;
        }
    }
    return ret;
}

void RegisterImageDlg::on_btnDel_clicked()
{
    int index = ui->listWidgetImage->currentRow();

    if(index >= 0)
    {
        QString strName;
        QListWidgetItem *item = ui->listWidgetImage->item(index);
        strName = item->text();

        BaseImageData baseImageData;
        int ret = baseImageData.DeleteBaseImage(strName);

        if(ret == 1)
        {
            ui->listWidgetImage->removeItemWidget(item);
            delete item;
        }else
        {
            QMessageBox::about(NULL,tr("提示"),tr("图片删除失败"));
        }

    }
}

void RegisterImageDlg::on_btnQuit_clicked()
{
    QDialog::accept();
}
bool RegisterImageDlg::eventFilter(QObject *watched, QEvent *event)
{

//    if(((QLineEdit *)watched)->isReadOnly() || !((QLineEdit *)watched)->isEnabled())
//    {
//        return QWidget::eventFilter(watched, event);
//    }
    if (watched == ui->txtImageName)         //首先判断控件(这里指 lineEdit1)
    {
         if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
         {
             QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
             m_keyBoardLib.SetNum(ui->txtImageName->text());
             int ret = dlg->exec();
             if(ret == QDialog::Accepted)
             {
                 ui->txtImageName->setText(m_keyBoardLib.GetNum());
             }
         }
    }
    return QWidget::eventFilter(watched, event);
}



void RegisterImageDlg::on_btnClear_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL,tr("警告"),tr("确定要清空图片列表?"),QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
    if(rb == QMessageBox::No)
    {
        return;
    }
    BaseImageData baseImageData;
    int ret = baseImageData.CleanBaseImage();
    if(ret == 1)
    {
        ui->listWidgetImage->clear();
        ui->txtImageName->setText("0");
    }else
    {
        QMessageBox::about(this,tr("警告"),tr("清空图片列表失败!"));
    }
}

void RegisterImageDlg::on_radioButtonSmall_clicked()
{
    ui->listWidgetImage->setIconSize(QSize(64,48));

    for(int i= 0; i<ui->listWidgetImage->count();i++)
    {
        QListWidgetItem *item = ui->listWidgetImage->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), 64));
    }
}

void RegisterImageDlg::on_radioButtonBig_clicked()
{
    ui->listWidgetImage->setIconSize(QSize(128,96));

    for(int i= 0; i<ui->listWidgetImage->count();i++)
    {
        QListWidgetItem *item = ui->listWidgetImage->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), 112));
    }
}
