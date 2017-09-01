#include "SampleWidget.h"
#include "ui_SampleWidget.h"
#include <QMessageBox>
#include "FWMatchSampleLabel.h"


SampleWidget::SampleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SampleWidget)
{
    ui->setupUi(this);
    m_label = NULL;
    m_label = new FWMatchSampleLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->comboBoxColor->addItem(tr("绿"));
    ui->comboBoxColor->addItem(tr("蓝"));
    ui->comboBoxColor->addItem(tr("红"));
    ui->comboBoxWidth->addItem("1");
    ui->comboBoxWidth->addItem("2");
    ui->comboBoxWidth->addItem("3");
    ui->comboBoxWidth->addItem("4");
    ui->comboBoxWidth->addItem("5");
    ui->comboBoxColor->setCurrentIndex(0);
    ui->comboBoxWidth->setCurrentIndex(0);

}
SampleWidget::~SampleWidget()
{
    delete ui;
}

QPoint SampleWidget::Get_Image_Pos()
{
    QPoint point(-1024,-768);
    if(m_label != NULL)
    {
        point = m_label->pos();
    }
}

int SampleWidget::Set_Parameter_To_Ram()
{
    pInputPara->param1 = ui->comboBoxColor->currentIndex();
    pInputPara->param2 = ui->comboBoxWidth->currentIndex()+1;
    return 1;
}

void SampleWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchSampleLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (TOOLTEST_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)//新加步骤
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->param1 = 0;
        pInputPara->param2 = 1;
    }
    InitData();
}

void SampleWidget::InitData()
{
    int iParam1 = pInputPara->param1;
    int iParam2 = pInputPara->param2;
    switch (iParam1)
    {
    case 0:
        ui->comboBoxColor->setCurrentIndex(0);
        break;
    case 1:
        ui->comboBoxColor->setCurrentIndex(1);
        break;
    case 2:
        ui->comboBoxColor->setCurrentIndex(2);
        break;
    default:
        ui->comboBoxColor->setCurrentIndex(0);
        break;
    }

    switch (iParam2) {
    case 1:
        ui->comboBoxWidth->setCurrentIndex(0);
        break;
    case 2:
        ui->comboBoxWidth->setCurrentIndex(1);
        break;
    case 3:
        ui->comboBoxWidth->setCurrentIndex(2);
        break;
    case 4:
        ui->comboBoxWidth->setCurrentIndex(3);
        break;
    case 5:
        ui->comboBoxWidth->setCurrentIndex(4);
        break;
    default:
        ui->comboBoxWidth->setCurrentIndex(0);
        break;
    }
}

void SampleWidget::Get_Result_From_Ram()
{
    void *pPrivate = Task_Step_Private_Para_Get(m_step_index);
    //do nothing
}
