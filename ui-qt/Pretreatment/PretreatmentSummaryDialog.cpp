#include "PretreatmentSummaryDialog.h"
#include "ui_PretreatmentSummaryDialog.h"
#include <QMessageBox>
#include <stdio.h>


PretreatmentSummaryDialog::PretreatmentSummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PretreatmentSummaryDialog)
{
    ui->setupUi(this);

    IniListData();
}

PretreatmentSummaryDialog::~PretreatmentSummaryDialog()
{
    delete ui;
}
void PretreatmentSummaryDialog::SetLocation(int x, int y)
{
    this->move(x,y);
}
void PretreatmentSummaryDialog::on_btnOk_clicked()
{
    int row = ui->listWidget->currentRow();

    if(row >=0)
    {
        m_str_name = ui->listWidget->item(row)->text();
        m_index = m_vt_index[row];
        /*CGetImageThread *imageThread = CGetImageThread::Instance();
        if(imageThread->m_iSensorType == SENSORTYPEBW)
        {
            if(m_index == ACCE_COLOR_EXTRACT_MODLE_ID)//20
            {
                QMessageBox::about(NULL,tr("提示"),tr("此功能为彩色相机功能"));
                return;
            }
        }*/
    }else
    {
        QMessageBox::about(NULL,tr("Information"),tr("Please Select row"));
        return ;
    }
    QDialog::accept();
}
void PretreatmentSummaryDialog::IniListData()
{
    ui->listWidget->setStyleSheet("QListWidget{background:rgba(255,255,255,255);color:#19649F;border:0px solid gray;padding:0px -2px 5px -2px;}"
                                  "QListWidget::item{width:321;height:40px;border:1px solid white;padding-left:0px;}"
                                  "QListWidget::item:!selected{background:#b4b4b4;}"
                                  "QListWidget::item:selected:active{background:#b2d1ff;color:#19649F;border-width:-1;}"
                                  "QListWidget::item:selected{background:#b2d1ff;color:#19649F;}");

    m_vt_strName.append(tr("抓图模块"));//抓图模块中断索引
    m_vt_strName.append(tr("区域筛选"));//区域筛选中断索引
    m_vt_strName.append(tr("二值化"));//二值化中断索引
    m_vt_strName.append(tr("轮廓匹配"));//轮廓匹配中断索引
    m_vt_strName.append(tr("色彩提取"));//色彩提取中断索引
    m_vt_strName.append(tr("腐蚀膨胀A"));//腐蚀膨胀A模块1中断索引
    m_vt_strName.append(tr("腐蚀膨胀B"));//膨胀膨胀B模块1中断索引
    m_vt_strName.append(tr("边沿提取"));//边沿提取中断索引
    m_vt_strName.append(tr("连通域"));//连通域中断索引
    m_vt_strName.append(tr("对比度增强"));//直方图模块中断索引
    m_vt_strName.append(tr("高斯滤波"));//5*5高斯滤波模块中断索引
    m_vt_strName.append(tr("实时浓淡补正"));//实时浓淡补正
    m_vt_strName.append(tr("对比度转换"));//实时浓淡补正


    m_vt_index.append(1);
    m_vt_index.append(2);
    m_vt_index.append(3);
    m_vt_index.append(4);
    m_vt_index.append(5);
    m_vt_index.append(6);
    m_vt_index.append(7);
    m_vt_index.append(8);
    m_vt_index.append(9);
    m_vt_index.append(10);
    m_vt_index.append(11);
    m_vt_index.append(12);
    m_vt_index.append(13);

    ui->listWidget->addItem(m_vt_strName[0]);//抓图模块中断索引
    ui->listWidget->addItem(m_vt_strName[1]);//区域筛选中断索引
    ui->listWidget->addItem(m_vt_strName[2]);//二值化中断索引
    ui->listWidget->addItem(m_vt_strName[3]);//轮廓匹配中断索引
    ui->listWidget->addItem(m_vt_strName[4]);//色彩提取中断索引
    ui->listWidget->addItem(m_vt_strName[5]);//腐蚀模块1中断索引
    ui->listWidget->addItem(m_vt_strName[6]);//膨胀模块1中断索引
    ui->listWidget->addItem(m_vt_strName[7]);//边沿提取中断索引
    ui->listWidget->addItem(m_vt_strName[8]);//连通域
    ui->listWidget->addItem(m_vt_strName[9]);//直方图模块中断索引
    ui->listWidget->addItem(m_vt_strName[10]);//5*5高斯滤波模块中断索引
    ui->listWidget->addItem(m_vt_strName[11]);//实时浓淡补正
    ui->listWidget->addItem(m_vt_strName[12]);//实时浓淡补正
}

void PretreatmentSummaryDialog::on_btnQuit_clicked()
{
    QDialog::reject();
}
int PretreatmentSummaryDialog::GetNameIndexById(int id)
{
    int count = m_vt_index.count();
    int ret = -1;
    for(int i = 0; i<count;i++)
    {
        if(m_vt_index[i] == id)
        {
            ret = i;
            break;
        }
    }
    return ret;
}
QString PretreatmentSummaryDialog::GetStrNameByArrIndex(int index)
{
    return m_vt_strName[index];
}
