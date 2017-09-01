#include <QDebug>
#include "PolarWidget.h"
#include "ui_PolarWidget.h"
#include "QMessageBox"

PolarWidget::PolarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PolarWidget)
{
    ui->setupUi(this);
    this->installEventFilter(this);

    m_label = new FWMatchPolarLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    connect(ui->btnAddRadiusIn,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnSubRadiusIn,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnAddRadiusOut,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnSubRadiusOut,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnAddSamplingAngle,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnSubSamplingAngle,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnAddSearchAngle,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->btnSubSearchAngle,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->SimilarlityDownBtn,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect(ui->SimilarlityUpBtn,&QPushButton::released,this,&PolarWidget::GetCurrentTime);
    connect((FWMatchPolarLabel*)m_label,&FWMatchPolarLabel::signalPointsChange,\
            this,&PolarWidget::ShowAngleValue);
    connect((FWMatchPolarLabel*)m_label,&FWMatchPolarLabel::signalRadiuChange,\
            this,&PolarWidget::ShowRadiuValue);


}

PolarWidget::~PolarWidget()
{
    this->removeEventFilter(this);
    delete ui;
}

QPoint PolarWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

int PolarWidget::Set_Parameter_To_Ram()
{
    TASK_STEP_HEADER *pTaskHead = Task_Step_Head_Get(m_step_index);
    if(!pTaskHead->compass_enable)
    {
        QMessageBox::about(this,tr(""),tr("请先使能关联定位，并选择关联数据"));
        return -1;
    }
    unsigned int inner_radius = ((FWMatchPolarLabel *)m_label)->getRadiusMin();
    unsigned int outer_radius = ((FWMatchPolarLabel *)m_label)->getRadiusMax();
    unsigned int precision;
    if(ui->radioButton_Low->isChecked())
        precision = 1;
    else if(ui->radioButton_Mid->isChecked())
        precision = 2;
    else
        precision = 3;
    unsigned int score_threshold = ui->SimilarlitySlider->value();
    float sample_window_start = ((FWMatchPolarLabel *)m_label)->getLearnStartAngle();
    float sample_window_end = ((FWMatchPolarLabel *)m_label)->getLearnEndAngle();
    float search_window_start = ((FWMatchPolarLabel *)m_label)->getSearchStartAngle();
    float search_window_end = ((FWMatchPolarLabel *)m_label)->getSearchEndAngle();
    unsigned int search_all_window_flag;
    if(ui->radioButton_Global->isChecked())
        search_all_window_flag = 1;
    else
        search_all_window_flag = 0;
    pInputPara->inner_radius = inner_radius;
    pInputPara->outer_radius = outer_radius;
    pInputPara->precision = precision;
    pInputPara->score_threshold = score_threshold;
    pInputPara->sample_window_start = sample_window_start;
    pInputPara->sample_window_end = sample_window_end;
    pInputPara->search_window_start = search_window_start;
    pInputPara->search_window_end = search_window_end;
    pInputPara->search_all_window_flag = search_all_window_flag;
    qDebug()<<"set inner_radius = "<<inner_radius;
    qDebug()<<"set outer_radius = "<<outer_radius;
    qDebug()<<"set precision = "<<precision;
    qDebug()<<"set score_threshold = "<<score_threshold;
    qDebug()<<"set sample_window_start = "<<sample_window_start;
    qDebug()<<"set sample_window_end = "<<sample_window_end;
    qDebug()<<"set search_window_start = "<<search_window_start;
    qDebug()<<"set search_window_end = "<<search_window_end;
    qDebug()<<"set search_all_window_flag = "<<search_all_window_flag;
    return 1;
}

void PolarWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchPolarLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (POLAR_MATCH_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->inner_radius = 40;
        pInputPara->outer_radius = 100;
        pInputPara->precision = 1;
        pInputPara->score_threshold = 80;
        pInputPara->sample_window_start = 30;
        pInputPara->sample_window_end = 60;
        pInputPara->search_window_start = 0;
        pInputPara->search_window_end = 90;
        pInputPara->search_all_window_flag = 1;
    }
    InitData();
}


void PolarWidget::InitData()
{
    unsigned int inner_radius = pInputPara->inner_radius;
    unsigned int outer_radius = pInputPara->outer_radius;
    unsigned int precision = pInputPara->precision;
    unsigned int score_threshold = pInputPara->score_threshold;
    float sample_window_start = pInputPara->sample_window_start;
    float sample_window_end = pInputPara->sample_window_end;
    float search_window_start = pInputPara->search_window_start;
    float search_window_end = pInputPara->search_window_end;
    unsigned int search_all_window_flag = pInputPara->search_all_window_flag;

    qDebug()<<"get inner_radius = "<<inner_radius;
    qDebug()<<"get outer_radius = "<<outer_radius;
    qDebug()<<"get precision = "<<precision;
    qDebug()<<"get score_threshold = "<<score_threshold;
    qDebug()<<"get sample_window_start = "<<sample_window_start;
    qDebug()<<"get sample_window_end = "<<sample_window_end;
    qDebug()<<"get search_window_start = "<<search_window_start;
    qDebug()<<"get search_window_end = "<<search_window_end;
    qDebug()<<"get search_all_window_flag = "<<search_all_window_flag;
    ((FWMatchPolarLabel *)m_label)->setRadiusMin(inner_radius);
    ((FWMatchPolarLabel *)m_label)->setRadiusMax(outer_radius);
    ((FWMatchPolarLabel *)m_label)->setLearnStartAngle(sample_window_start);
    ((FWMatchPolarLabel *)m_label)->setLearnEndAngle(sample_window_end);
    ((FWMatchPolarLabel *)m_label)->setSearchStartAngle(search_window_start);
    ((FWMatchPolarLabel *)m_label)->setSearchEndAngle(search_window_end);

    if(precision == 1)
    {
        ui->radioButton_Low->setChecked(true);
    }else if(precision == 2)
    {
        ui->radioButton_Mid->setChecked(true);
    }else if(precision == 3)
    {
        ui->radioButton_Hight->setChecked(true);
    }else
    {
        ui->radioButton_Low->setChecked(true);
    }

    if(search_all_window_flag)
    {
        ui->radioButton_Global->setChecked(true);
    }else
    {
        ui->radioButton_Part->setChecked(true);
    }
    ui->SimilarlitySlider->setValue(score_threshold);
}

void PolarWidget::on_radioButton_Global_clicked()
{
    ((FWMatchPolarLabel *)m_label)->setSearchMode(1);
}

void PolarWidget::on_radioButton_Part_clicked()
{
    ((FWMatchPolarLabel *)m_label)->setSearchMode(0);
}

void PolarWidget::ShowAngleValue(double angle,int kind)
{
    switch (kind) {
    case 1:
        ui->txtSamplingAngelStart->setText(QString::number(angle*(180/M_PI)));
        break;
    case 2:
        ui->txtSamplingAngelEnd->setText(QString::number(angle*(180/M_PI)));
        break;
    case 3:
        ui->txtSearchAngelStart->setText(QString::number(angle*(180/M_PI)));
        break;
    case 4:
        ui->txtSearchAngelEnd->setText(QString::number(angle*(180/M_PI)));
        break;
    default:
        break;
    }

}
void PolarWidget::ShowRadiuValue(int r,int kind)
{
    if(kind == 1)
    {
        ui->txtRadiusIN->setText(QString::number(r));
    }else
    {
        ui->txtRadiusOut->setText(QString::number(r));
    }
}


/**
 * @brief PolarWidget::SetBtnRepeatParam
 * @param btn 需要设置长按参数的按钮
 * @author dgq
 * @note 设置按钮长按加速参数
 */
void PolarWidget::SetBtnRepeatParam(QPushButton *btn)
{
    static int i_delay = 300;
    static int i_interV = 100;
    static int m_calc = 0;
    if(m_calc > 0)
    {
        stopTime = QTime::currentTime();
        int elapsed = startTime.msecsTo(stopTime);
        if(abs(elapsed )> i_interV)
        {
            m_calc = 0;
            i_delay = 300;
            i_interV = 100;
            btn->setAutoRepeat(false);
        }
    }
    m_calc++;
    if(m_calc < 2)
    {
        i_delay = 300;
        i_interV = 100;
    }
    if(m_calc > 2 && m_calc < 5)
    {
        i_delay = 100;
        i_interV = 100;
    }
    if(m_calc > 5)
    {
        i_delay = 10;
        i_interV = 10;
    }
    btn->setAutoRepeat(true);
    btn->setAutoRepeatDelay(i_delay);
    btn->setAutoRepeatInterval(i_interV);
}

/**
 * @brief BaseLineWidget::GetCurrentTime
 * @author dgq
 * @note 获取按钮释放的时间
 */
void PolarWidget::GetCurrentTime()
{
    startTime = QTime::currentTime();
}

void PolarWidget::on_btnAddRadiusIn_pressed()
{
    SetBtnRepeatParam(ui->btnAddRadiusIn);
    if(ui->btnAddRadiusIn->autoRepeatInterval() == 10)
        ((FWMatchPolarLabel*)m_label)->AddRadiuMin(5);
    else
        ((FWMatchPolarLabel*)m_label)->AddRadiuMin(1);
}

void PolarWidget::on_btnSubRadiusIn_pressed()
{
    SetBtnRepeatParam(ui->btnSubRadiusIn);
    if(ui->btnSubRadiusIn->autoRepeatInterval() == 10)
        ((FWMatchPolarLabel*)m_label)->SubRadiuMin(5);
    else
        ((FWMatchPolarLabel*)m_label)->SubRadiuMin(1);
}

void PolarWidget::on_btnAddRadiusOut_pressed()
{
    SetBtnRepeatParam(ui->btnAddRadiusOut);
    if(ui->btnAddRadiusOut->autoRepeatInterval() == 10)
        ((FWMatchPolarLabel*)m_label)->AddRadiuMax(5);
    else
        ((FWMatchPolarLabel*)m_label)->AddRadiuMax(1);
}

void PolarWidget::on_btnSubRadiusOut_pressed()
{
    SetBtnRepeatParam(ui->btnSubRadiusOut);
    if(ui->btnSubRadiusOut->autoRepeatInterval() == 10)
        ((FWMatchPolarLabel*)m_label)->SubRadiuMax(5);
    else
        ((FWMatchPolarLabel*)m_label)->SubRadiuMax(1);
}

void PolarWidget::on_btnAddSamplingAngle_pressed()
{
    float add_value = 0.0;
    float value = 0.0;
    SetBtnRepeatParam(ui->btnAddSamplingAngle);
    if(ui->btnAddSamplingAngle->autoRepeatInterval() == 10)
        add_value = 5;
    else
        add_value = 1;
    if(ui->radioButtonSamplingAngelStart->isChecked())
    {
        float current_angle = ui->txtSamplingAngelStart->text().toFloat();
        if(add_value + current_angle > 360)
        {
            value = add_value + current_angle - 360;
        }else
        {
            value = add_value + current_angle;
        }
        ((FWMatchPolarLabel*)m_label)->setLearnStartAngle(value);
    }
    else
    {
        float current_angle = ui->txtSamplingAngelEnd->text().toFloat();
        if(add_value + current_angle > 360)
        {
            value = add_value + current_angle - 360;
        }else
        {
            value = add_value + current_angle;
        }
        ((FWMatchPolarLabel*)m_label)->setLearnEndAngle(value);
    }
}

void PolarWidget::on_btnSubSamplingAngle_pressed()
{
    float sub_value = 0.0;
    float value = 0.0;
    SetBtnRepeatParam(ui->btnSubSamplingAngle);
    if(ui->btnSubSamplingAngle->autoRepeatInterval() == 10)
        sub_value = 5;
    else
        sub_value = 1;
    if(ui->radioButtonSamplingAngelStart->isChecked())
    {
        float current_angle = ui->txtSamplingAngelStart->text().toFloat();
        if(current_angle - sub_value < 0)
        {
            value = current_angle - sub_value + 360;
        }else
        {
            value = current_angle - sub_value;
        }
        ((FWMatchPolarLabel*)m_label)->setLearnStartAngle(value);
    }
    else
    {
        float current_angle = ui->txtSamplingAngelEnd->text().toFloat();
        if(current_angle - sub_value < 0)
        {
            value = current_angle - sub_value + 360;
        }else
        {
            value = current_angle - sub_value;
        }
        ((FWMatchPolarLabel*)m_label)->setLearnEndAngle(value);
    }
}

void PolarWidget::on_btnAddSearchAngle_pressed()
{
    float add_value = 0.0;
    float value = 0.0;
    SetBtnRepeatParam(ui->btnAddSearchAngle);
    if(ui->btnAddSearchAngle->autoRepeatInterval() == 10)
        add_value = 5;
    else
        add_value = 1;
    if(ui->radioButtonSearchAngelStart->isChecked())
    {
        float current_angle = ui->txtSearchAngelStart->text().toFloat();
        if(add_value + current_angle > 360)
        {
            value = add_value + current_angle - 360;
        }else
        {
            value = add_value + current_angle;
        }
        ((FWMatchPolarLabel*)m_label)->setSearchStartAngle(value);
    }
    else
    {
        float current_angle = ui->txtSearchAngelEnd->text().toFloat();
        if(add_value + current_angle > 360)
        {
            value = add_value + current_angle - 360;
        }else
        {
            value = add_value + current_angle;
        }
        ((FWMatchPolarLabel*)m_label)->setSearchEndAngle(value);
    }
}

void PolarWidget::on_btnSubSearchAngle_pressed()
{
    float sub_value = 0.0;
    float value = 0.0;
    SetBtnRepeatParam(ui->btnSubSearchAngle);
    if(ui->btnSubSearchAngle->autoRepeatInterval() == 10)
        sub_value = 5;
    else
        sub_value = 1;
    if(ui->radioButtonSearchAngelStart->isChecked())
    {
        float current_angle = ui->txtSearchAngelStart->text().toFloat();
        if(current_angle - sub_value < 0)
        {
            value = current_angle - sub_value + 360;
        }else
        {
            value = current_angle - sub_value;
        }
        ((FWMatchPolarLabel*)m_label)->setSearchStartAngle(value);
    }
    else
    {
        float current_angle = ui->txtSearchAngelEnd->text().toFloat();
        if(current_angle - sub_value < 0)
        {
            value = current_angle - sub_value + 360;
        }else
        {
            value = current_angle - sub_value;
        }
        ((FWMatchPolarLabel*)m_label)->setSearchEndAngle(value);
    }
}


void PolarWidget::on_SimilarlityDownBtn_pressed()
{
    SetBtnRepeatParam(ui->SimilarlityDownBtn);
    int value = 0;
    if(ui->SimilarlityDownBtn->autoRepeatInterval() == 10)
    {
        value = ui->SimilarlitySlider->value()-2;
    }
    else
    {
        value = ui->SimilarlitySlider->value()-1;
    }
    if(value < 0)
        value = 0;
    ui->LabelSimilarlity->setText(QString::number(value));
    ui->SimilarlitySlider->setValue(value);
}

void PolarWidget::on_SimilarlityUpBtn_pressed()
{
    SetBtnRepeatParam(ui->SimilarlityUpBtn);
    int value = 0;
    if(ui->SimilarlityUpBtn->autoRepeatInterval() == 10)
    {
        value = ui->SimilarlitySlider->value()+2;
    }
    else
    {
        value = ui->SimilarlitySlider->value()+1;
    }
    if(value > 100)
        value = 100;
    ui->LabelSimilarlity->setText(QString::number(value));
    ui->SimilarlitySlider->setValue(value);
}

void PolarWidget::on_SimilarlitySlider_valueChanged(int value)
{
     ui->LabelSimilarlity->setText(QString::number(value));
}


bool PolarWidget::eventFilter(QObject *watched, QEvent *event)
{

    if (event->type()==QEvent::Show){
        GetCompassData();
    }
    return QWidget::eventFilter(watched, event);
}
void PolarWidget::GetCompassData()
{
    TASK_STEP_HEADER *pTaskHead = Task_Step_Head_Get(m_step_index);
    if(!pTaskHead->compass_enable)
    {
        return;
    }
    POINT_F pointx;
    POINT_F pointy;
    if(pTaskHead->compass_info[0].compass_type == 0)
    {
        QMessageBox::about(this,tr(""),tr("X坐标没有引用数据"));
        return;
    }else if(pTaskHead->compass_info[0].compass_type == 1)
    {
        //todo...

    }else
    {
        measure_ref_point_result_get(pTaskHead->compass_info[0].compass_step,\
                pTaskHead->compass_info[0].ref_value_index,&pointx,1);
    }

    if(pTaskHead->compass_info[1].compass_type == 0)
    {
        QMessageBox::about(this,tr(""),tr("Y坐标没有引用数据"));
        return;
    }else if(pTaskHead->compass_info[1].compass_type == 1)
    {
        //todo...

    }else
    {
        measure_ref_point_result_get(pTaskHead->compass_info[1].compass_step,\
                pTaskHead->compass_info[1].ref_value_index-1,&pointy,1);
    }
    int pix_vga_x = 0;
    int pix_vga_y = 0;
    PixelCvt(&pointx.x_f,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pointy.y_f,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    ((FWMatchPolarLabel*)m_label)->setCenterPoint(QPoint(pix_vga_x,pix_vga_y));

}
