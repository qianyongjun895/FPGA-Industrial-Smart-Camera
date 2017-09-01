#include <QDebug>
#include "ui_ImageManagemnet.h"
#include <QMessageBox>
#include "ImageManagemnet.h"
#include "../Global/UtilitiesFun.h"
#include "BusinessData/InterfaceLib/BaseImageData.h"
#include "image_include/ImageScanGlobal.h"
#include "image_include/ImageManageGlobal.h"
#include "image_include/ImageSimulationGlobal.h"

ImageManagemnet::ImageManagemnet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageManagemnet)
{
    ui->setupUi(this);
    m_image_count = 1;
    m_image_index =1;

}

ImageManagemnet::~ImageManagemnet()
{
    delete ui;
}
void ImageManagemnet::InitData()
{
    unsigned int ret = image_scan_dir_type_get();

    switch (ret ) {
    case 0:
        ui->radioButton_Save->setChecked(true);
        break;
    case 1:
        ui->radioButton_Base->setChecked(true);
        break;
    case 2:
        ui->radioButton_OK->setChecked(true);
        break;
    case 3:
        ui->radioButton_Failed->setChecked(true);
        break;
    default:
        break;
    }
    IniImageNameList();
    UtilitiesFun::Instance()->SetCPT(CPT_DDR_PIC);
    UtilitiesFun::Instance()->ListVGA(ui->labelImage->pos().x(),ui->labelImage->pos().y());
}
void ImageManagemnet::on_btnExit_clicked()
{

    QDialog::reject();

}
void ImageManagemnet::IniImageNameList()
{
    char imageName[2000][IMAGE_FILE_NAME_SIZE_MAX];
    QVector<QString> strNameList ;
    int iNum =0;
    if(ui->radioButton_Save->isChecked())
    {
        iNum = image_dir_all_file_name_get(IMAGE_SAVE_DIR,imageName);
    }else if(ui->radioButton_Base->isChecked())
    {
        iNum = image_dir_all_file_name_get(BASE_IMAGE_DIR,imageName);

    }else if(ui->radioButton_OK->isChecked())
    {
        iNum = image_dir_all_file_name_get(OK_IMAGE_DIR,imageName);
    }else if(ui->radioButton_Failed->isChecked())
    {
        iNum = image_dir_all_file_name_get(NG_IMAGE_DIR,imageName);
    }

    for(int j = 0; j < iNum; j++)
    {
        strNameList.append(QString::fromLocal8Bit(imageName[j]));
    }

    int count = strNameList.count();

    for(int i = 0; i<count;i++)
    {
        AddItemData(strNameList[i]);
    }
    m_image_count = count;
    m_image_index =1;
    if(m_image_count == 0)
        m_image_index =0;
    QString strTemp = GetPageNumber(m_image_index,m_image_count);
    ui->labelImgIndex->setText(strTemp);
}
QString ImageManagemnet::GetPageNumber(int index,int count)
{
    QString strTemp;
    strTemp = QString::number(index);
    strTemp +="/";
    strTemp +=QString::number(count);
    return strTemp;
}
void ImageManagemnet::AddItemData(QString strName)
{
    ui->listWidgetImage->addItem(strName);
    int count = ui->listWidgetImage->count();
    QListWidgetItem *item = ui->listWidgetImage->item(count-1);
    item->setSizeHint(QSize(item->sizeHint().width(), 32));
}

void ImageManagemnet::on_radioButton_Save_clicked()
{
    image_scan_init(IMAGE_SAVE_DIR);
    ui->listWidgetImage->clear();
    IniImageNameList();
}

void ImageManagemnet::on_radioButton_Failed_clicked()
{
    image_scan_init(NG_IMAGE_DIR);
    ui->listWidgetImage->clear();
    IniImageNameList();
}

void ImageManagemnet::on_radioButton_OK_clicked()
{
    image_scan_init(OK_IMAGE_DIR);
    ui->listWidgetImage->clear();
    IniImageNameList();
}

void ImageManagemnet::on_radioButton_Base_clicked()
{
    image_scan_init(BASE_IMAGE_DIR);
    ui->listWidgetImage->clear();
    IniImageNameList();
}

void ImageManagemnet::on_btnFirst_clicked()
{
    image_scan_pic_load(IMAGE_SCAN_FIRST_PIC);
    this->m_image_index =1;
    QString strTemp = GetPageNumber(m_image_index,m_image_count);
    ui->labelImgIndex->setText(strTemp);
    ui->listWidgetImage->setCurrentRow(0);
}

void ImageManagemnet::on_btnPrev_clicked()
{
    image_scan_pic_load(IMAGE_SCAN_PRE_PIC);
    if(m_image_index >1)
    {
        this->m_image_index--;
        QString strTemp = GetPageNumber(m_image_index,m_image_count);
        ui->labelImgIndex->setText(strTemp);
        ui->listWidgetImage->setCurrentRow(m_image_index -1);
    }
}

void ImageManagemnet::on_btnNext_clicked()
{
    image_scan_pic_load(IMAGE_SCAN_NEXT_PIC);
    if(m_image_index < m_image_count)
    {
        this->m_image_index++;
        QString strTemp = GetPageNumber(m_image_index,m_image_count);
        ui->labelImgIndex->setText(strTemp);
        ui->listWidgetImage->setCurrentRow(m_image_index -1);
    }
}

void ImageManagemnet::on_btnLast_clicked()
{
    image_scan_pic_load(IMAGE_SCAN_LAST_PIC);
    this->m_image_index =m_image_count;
    QString strTemp = GetPageNumber(m_image_index,m_image_count);
    ui->labelImgIndex->setText(strTemp);
    ui->listWidgetImage->setCurrentRow(m_image_count-1);
}

void ImageManagemnet::on_btnDeleteImage_clicked()
{
    int index = ui->listWidgetImage->currentRow();
    if(index >=0)
    {
        QString strName;
        QListWidgetItem *item = ui->listWidgetImage->item(index);
        strName = item->text();
        int ret ;
        if(ui->radioButton_Save->isChecked())
        {
            ret = image_file_delete(IMAGE_SAVE_DIR,strName.toLocal8Bit().data());
        }else if(ui->radioButton_Base->isChecked())
        {
            ret = image_file_delete(BASE_IMAGE_DIR,strName.toLocal8Bit().data());

        }else if(ui->radioButton_OK->isChecked())
        {
            ret = image_file_delete(OK_IMAGE_DIR,strName.toLocal8Bit().data());
        }else if(ui->radioButton_Failed->isChecked())
        {
            ret = image_file_delete(NG_IMAGE_DIR,strName.toLocal8Bit().data());
        }

        if(ret == 1)
        {
            ui->listWidgetImage->removeItemWidget(item);
            delete item;
            this->m_image_count--;

            if(index+1 <= m_image_count)
            {
                ui->listWidgetImage->setCurrentRow(index);

            }else
            {
                m_image_index--;
                ui->listWidgetImage->setCurrentRow(index-1);
            }
            QString strTemp = GetPageNumber(m_image_index,m_image_count);
            ui->labelImgIndex->setText(strTemp);
        }else
        {
            QMessageBox::about(NULL,tr("提示"),tr("图片删除失败"));
        }
    }
    /*int ret = image_file_clean(BASE_IMAGE_DIR);
    return ret;*/
}

void ImageManagemnet::on_listWidgetImage_clicked(const QModelIndex &index)
{
    int row = index.row();
    if(row >= 0)
    {
        QString strName = ui->listWidgetImage->item(row)->text();

        if(ui->radioButton_Save->isChecked())
        {
            image_load_to_mem(IMAGE_SAVE_DIR,strName.toLocal8Bit().data());
        }else if(ui->radioButton_Base->isChecked())
        {
            image_load_to_mem(BASE_IMAGE_DIR,strName.toLocal8Bit().data());
        }else if(ui->radioButton_OK->isChecked())
        {
            image_load_to_mem(OK_IMAGE_DIR,strName.toLocal8Bit().data());
        }else if(ui->radioButton_Failed->isChecked())
        {
            image_load_to_mem(NG_IMAGE_DIR,strName.toLocal8Bit().data());
        }
        this->m_image_index = row+1;
        QString strTemp = GetPageNumber(m_image_index,m_image_count);
        ui->labelImgIndex->setText(strTemp);
    }
}

void ImageManagemnet::on_btnCleanImage_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL,tr("警告"),tr("确定要清空图片列表?"),QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
    if(rb == QMessageBox::No)
    {
        return;
    }

    int ret ;

    if(ui->radioButton_Save->isChecked())
    {
        ret = image_file_clean(IMAGE_SAVE_DIR);
    }else if(ui->radioButton_Base->isChecked())
    {
        ret = image_file_clean(BASE_IMAGE_DIR);
    }else if(ui->radioButton_OK->isChecked())
    {
        ret = image_file_clean(OK_IMAGE_DIR);
    }else if(ui->radioButton_Failed->isChecked())
    {
        ret = image_file_clean(NG_IMAGE_DIR);
    }

    if(ret == 1)
    {
        ui->listWidgetImage->clear();
        this->m_image_index = 0;
        this->m_image_count = 0;
        QString strTemp = GetPageNumber(m_image_index,m_image_count);
        ui->labelImgIndex->setText(strTemp);
    }else
    {
        QMessageBox::about(this,tr("警告"),tr("清空图片列表失败!"));
    }
}
