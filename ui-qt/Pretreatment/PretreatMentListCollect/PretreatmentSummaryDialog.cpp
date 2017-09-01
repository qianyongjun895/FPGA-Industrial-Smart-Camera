#include "PretreatmentSummaryDialog.h"
#include "ui_PretreatmentSummaryDialog.h"
#include <QMessageBox>
#include <stdio.h>
#include "AcceCommon.h"


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

    m_vt_strName.append(tr("CPT模块"));//图像预处理转换
    m_vt_strName.append(tr("图像预处理转换"));//图像预处理转换
    m_vt_strName.append(tr("二值化处理"));//二值化处理
    m_vt_strName.append(tr("轮廓匹配"));//轮廓匹配
    m_vt_strName.append(tr("边沿提取"));//边沿提取
    m_vt_strName.append(tr("连通域"));//连通域
    m_vt_strName.append(tr("色彩提取"));//色彩提取
    m_vt_strName.append(tr("区域筛选"));//区域筛选
    m_vt_strName.append(tr("直方图统计")); //直方图统计

    m_vt_index.append(ACCE_CPT_MODEL_ID);
    m_vt_index.append(ACCE_PRE_MODEL_ID);
    m_vt_index.append(ACCE_BW_PROC_MODEL_ID);
    m_vt_index.append(ACCE_SKE_MATCH_MODLE_ID);
    m_vt_index.append(ACCE_EDGE_EXTRACT_MODLE_ID);
    m_vt_index.append(ACCE_CONNECT_REGION_MODLE_ID);
    m_vt_index.append(ACCE_COLOR_EXTRACT_MODLE_ID);
    m_vt_index.append(ACCE_AREA_SELECT_MODEL_ID);
    m_vt_index.append(ACCE_HIST_MODEL_ID);

    ui->listWidget->addItem(m_vt_strName[0]);//cpt
    ui->listWidget->addItem(m_vt_strName[1]);//图像预处理转换
    ui->listWidget->addItem(m_vt_strName[2]);//二值化处理
    ui->listWidget->addItem(m_vt_strName[3]);//轮廓匹配
    ui->listWidget->addItem(m_vt_strName[4]);//边沿提取
    ui->listWidget->addItem(m_vt_strName[5]);//连通域
    ui->listWidget->addItem(m_vt_strName[6]);//色彩提取
    ui->listWidget->addItem(m_vt_strName[7]);//区域筛选
    ui->listWidget->addItem(m_vt_strName[8]);//直方图统计
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
