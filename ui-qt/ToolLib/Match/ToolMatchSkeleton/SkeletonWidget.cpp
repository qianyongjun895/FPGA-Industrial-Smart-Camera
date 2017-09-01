#include <QDebug>
#include "SkeletonWidget.h"
#include "ui_SkeletonWidget.h"
#include "QMessageBox"

SkeletonWidget::SkeletonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkeletonWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    ui->txtAngle->installEventFilter(this);
    m_label = new FWMatchSkeletonLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    connect(ui->btnSkeletonUp,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnSkeletonDown,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnSkeletonLeft,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnSkeletonRight,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnAddSensitivity,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnSubSensitivity,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnAddScore,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect(ui->btnSubScore,&QPushButton::released,this,&SkeletonWidget::GetCurrentTime);
    connect((FWMatchSkeletonLabel *)m_label,&FWMatchSkeletonLabel::signalPointsChange,this,&SkeletonWidget::RectPointChange);
}

SkeletonWidget::~SkeletonWidget()
{
    ui->txtAngle->removeEventFilter(this);
    delete ui;
}
QPoint SkeletonWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

int SkeletonWidget::Set_Parameter_To_Ram()
{
    unsigned int scopeRotation = ui->txtAngle->text().toInt();
    unsigned int calc_type;
    if(ui->checkBoxFast->isChecked())
    {
        calc_type = 1;
    }else
    {
        calc_type = 0;
    }
    unsigned int sensitivity = ui->horizontalSliderSensitivity->value();
    unsigned int score = ui->horizontalSliderScore->value();
    QRect train_rect = ((FWMatchSkeletonLabel*)m_label)->GetTrainRect();
    QRect search_rect = ((FWMatchSkeletonLabel*)m_label)->GetSearchRect();;
    pInputPara->scopeRotation = scopeRotation;
    pInputPara->calc_type = calc_type;
    pInputPara->sensitivity = sensitivity;
    pInputPara->score_threshold = score;
    pInputPara->train_roi_point[0].x_f = train_rect.topLeft().x();
    pInputPara->train_roi_point[0].y_f = train_rect.topLeft().y();
    pInputPara->train_roi_point[1].x_f = train_rect.bottomRight().x();
    pInputPara->train_roi_point[1].y_f = train_rect.bottomRight().y();
    pInputPara->search_roi_point[0].x_f = search_rect.topLeft().x();
    pInputPara->search_roi_point[0].y_f = search_rect.topLeft().y();
    pInputPara->search_roi_point[1].x_f = search_rect.bottomRight().x();
    pInputPara->search_roi_point[1].y_f = search_rect.bottomRight().y();
    return 1;
}

void SkeletonWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchSkeletonLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (SKELETON_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->train_roi_point[0].x_f = 200;
        pInputPara->train_roi_point[0].y_f = 200;
        pInputPara->train_roi_point[1].x_f = 400;
        pInputPara->train_roi_point[1].y_f = 300;
        pInputPara->search_roi_point[0].x_f = 30;
        pInputPara->search_roi_point[0].y_f = 30;
        pInputPara->search_roi_point[1].x_f = 610;
        pInputPara->search_roi_point[1].y_f = 450;
        pInputPara->sensitivity = 40;
        pInputPara->scopeRotation = 180;
        pInputPara->score_threshold = 80;
        pInputPara->calc_type = 0;
    }
    InitData();
}

/**
 * @brief SkeletonWidget::on_btnSkeletonUp_pressed
 * @author dgq
 * @note 向上坐标微调
 */
void SkeletonWidget::on_btnSkeletonUp_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonUp);
    if(ui->btnSkeletonUp->autoRepeatInterval() == 10)
        ((FWMatchSkeletonLabel*)m_label)->MoveUp(5);
    else
        ((FWMatchSkeletonLabel*)m_label)->MoveUp(1);
}

/**
 * @brief SkeletonWidget::on_btnSkeletonDown_pressed
 * @author dgq
 * @note 向下坐标微调
 */
void SkeletonWidget::on_btnSkeletonDown_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonDown);
    if(ui->btnSkeletonDown->autoRepeatInterval() == 10)
        ((FWMatchSkeletonLabel*)m_label)->MoveDown(5);
    else
        ((FWMatchSkeletonLabel*)m_label)->MoveDown(1);
}

/**
 * @brief SkeletonWidget::on_btnSkeletonLeft_pressed
 * @author dgq
 * @note 向左坐标微调
 */
void SkeletonWidget::on_btnSkeletonLeft_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonLeft);
    if(ui->btnSkeletonLeft->autoRepeatInterval() == 10)
        ((FWMatchSkeletonLabel*)m_label)->MoveLeft(5);
    else
        ((FWMatchSkeletonLabel*)m_label)->MoveLeft(1);
}

/**
 * @brief SkeletonWidget::on_btnSkeletonRight_pressed
 * @author dgq
 * @note 向右坐标微调
 */
void SkeletonWidget::on_btnSkeletonRight_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonRight);
    if(ui->btnSkeletonRight->autoRepeatInterval() == 10)
        ((FWMatchSkeletonLabel*)m_label)->MoveRight(5);
    else
        ((FWMatchSkeletonLabel*)m_label)->MoveRight(1);
}

/**
 * @brief SkeletonWidget::SetBtnRepeatParam
 * @param btn 需要实现长按效果的按钮对象
 * @author dgq
 * @note 设置按钮长按事件的加速属性
 */
void SkeletonWidget::SetBtnRepeatParam(QPushButton *btn)
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
            btn->setAutoRepeatDelay(i_delay);
            btn->setAutoRepeatInterval(i_interV);
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
 * @brief SkeletonWidget::GetCurrentTime
 * @author dgq
 * @note 获取按钮释放的时间
 */
void SkeletonWidget::GetCurrentTime()
{
    startTime = QTime::currentTime();
}

/**
 * @brief SkeletonWidget::RectPointChange
 * @author dgq
 * @note 获取按钮释放的时间
 */
void SkeletonWidget::RectPointChange(QPoint point,int index)
{
    if(index == 1)
    {
        ui->radioButtonSkeletonFindBit1->setChecked(true);
        QString msg = "("+QString::number(point.x())+","+QString::number(point.y())+")";
        ui->labelFind1->setText(msg);
    }else if(index == 2)
    {
        ui->radioButtonSkeletonFindBit2->setChecked(true);
        QString msg = "("+QString::number(point.x())+","+QString::number(point.y())+")";
        ui->labelFind2->setText(msg);
    }else if(index == 3)
    {
        ui->radioButtonSkeletonStudyBit1->setChecked(true);
        QString msg = "("+QString::number(point.x())+","+QString::number(point.y())+")";
        ui->labelStudy1->setText(msg);
    }else
    {
        ui->radioButtonSkeletonStudyBit2->setChecked(true);
        QString msg = "("+QString::number(point.x())+","+QString::number(point.y())+")";
        ui->labelStudy2->setText(msg);
    }
}

void SkeletonWidget::on_radioButtonSkeletonStudyBit1_clicked()
{
    ((FWMatchSkeletonLabel*)m_label)->SetRectPoint(3);
}

void SkeletonWidget::on_radioButtonSkeletonStudyBit2_clicked()
{
    ((FWMatchSkeletonLabel*)m_label)->SetRectPoint(3);
}

void SkeletonWidget::on_radioButtonSkeletonFindBit1_clicked()
{
    ((FWMatchSkeletonLabel*)m_label)->SetRectPoint(1);
}

void SkeletonWidget::on_radioButtonSkeletonFindBit2_clicked()
{
    ((FWMatchSkeletonLabel*)m_label)->SetRectPoint(2);
}

bool SkeletonWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtAngle){
        if (event->type()==QEvent::MouseButtonPress){
            RotateAngleInputPro();
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief SkeletonWidget::RotateAngleInputPro
 * @author dgq
 * @note blob最大检测个数的输入响应函数
 */
void SkeletonWidget::RotateAngleInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        QDialog *Numkey = GetNumKeyBoardDlg();
        int ret = Numkey->exec();
        if(ret== QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if( num.toInt()>=0 && num.toInt()<=180)
                {
                    ui->txtAngle->setText(num);
                }
                else
                {
                    QString strTemp;
                    strTemp = tr("请输入0到180之间的数值");
                    QMessageBox::information(NULL,tr("提示"),strTemp);
                }
            }
        }
    }
}


void SkeletonWidget::on_horizontalSliderSensitivity_valueChanged(int value)
{
    ui->LabelSensitivity->setText(QString::number(value));
}

void SkeletonWidget::on_btnSubSensitivity_pressed()
{
    SetBtnRepeatParam(ui->btnSubSensitivity);
    int value = 0;
    if(ui->btnSubSensitivity->autoRepeatInterval() == 10)
    {
        value = ui->horizontalSliderSensitivity->value()-2;
    }
    else
    {
        value = ui->horizontalSliderSensitivity->value()-1;
    }
    if(value < 0)
        value = 0;
    ui->LabelSensitivity->setText(QString::number(value));
    ui->horizontalSliderSensitivity->setValue(value);
}

void SkeletonWidget::on_btnAddSensitivity_pressed()
{
    SetBtnRepeatParam(ui->btnAddSensitivity);
    int value = 0;
    if(ui->btnAddSensitivity->autoRepeatInterval() == 10)
    {
        value = ui->horizontalSliderSensitivity->value()+2;
    }
    else
    {
        value = ui->horizontalSliderSensitivity->value()+1;
    }
    if(value > 100)
        value = 100;
    ui->LabelSensitivity->setText(QString::number(value));
    ui->horizontalSliderSensitivity->setValue(value);
}


void SkeletonWidget::InitData()
{
    m_i_load_first  = 0;
    unsigned int scopeRotation = pInputPara->scopeRotation;
    unsigned int calc_type = pInputPara->calc_type;
    unsigned int sensitivity = pInputPara->sensitivity;
    unsigned int score = pInputPara->score_threshold;
    QRect train_rect;
    QRect search_rect;
    train_rect.setTopLeft(QPoint(pInputPara->train_roi_point[0].x_f,pInputPara->train_roi_point[0].y_f));
    train_rect.setBottomRight(QPoint(pInputPara->train_roi_point[1].x_f,pInputPara->train_roi_point[1].y_f));

    search_rect.setTopLeft(QPoint(pInputPara->search_roi_point[0].x_f,pInputPara->search_roi_point[0].y_f));
    search_rect.setBottomRight(QPoint(pInputPara->search_roi_point[1].x_f,pInputPara->search_roi_point[1].y_f));

    ui->txtAngle->setText(QString::number(scopeRotation));
    if(calc_type == 0)
    {
        ui->checkBoxFast->setChecked(false);
    }else
    {
        ui->checkBoxFast->setChecked(true);
    }
    ui->horizontalSliderSensitivity->setValue(sensitivity);
    ui->horizontalSliderScore->setValue(score);
    ((FWMatchSkeletonLabel*)m_label)->SetTrainRect(train_rect);
    ((FWMatchSkeletonLabel*)m_label)->SetSearchRect(search_rect);
    ui->radioButtonSkeletonFindBit1->setChecked(true);
    ((FWMatchSkeletonLabel*)m_label)->SetRectPoint(1);
    ui->labelFind1->setText("("+QString::number(search_rect.topLeft().x())+","+QString::number(search_rect.topLeft().y())+")");
    ui->labelFind2->setText("("+QString::number(search_rect.bottomRight().x())+","+QString::number(search_rect.bottomRight().y())+")");
    ui->labelStudy1->setText("("+QString::number(train_rect.topLeft().x())+","+QString::number(train_rect.topLeft().y())+")");
    ui->labelStudy2->setText("("+QString::number(train_rect.bottomRight().x())+","+QString::number(search_rect.bottomRight().y())+")");
    m_i_load_first  =1;
}


/**
 * @brief SkeletonWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void SkeletonWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        qDebug()<<"load libFrmInputKeyBoard.so isLoaded";
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void SkeletonWidget::on_btnSubScore_pressed()
{
    SetBtnRepeatParam(ui->btnSubScore);
    int value = 0;
    if(ui->btnSubScore->autoRepeatInterval() == 10)
    {
        value = ui->horizontalSliderScore->value()-2;
    }
    else
    {
        value = ui->horizontalSliderScore->value()-1;
    }
    if(value < 0)
        value = 0;
    ui->LabelScore->setText(QString::number(value));
    ui->horizontalSliderScore->setValue(value);
}

void SkeletonWidget::on_btnAddScore_pressed()
{
    SetBtnRepeatParam(ui->btnAddScore);
    int value = 0;
    value = ui->horizontalSliderScore->value()+1;
    if(value > 100)
        value = 100;
    ui->LabelScore->setText(QString::number(value));
    ui->horizontalSliderScore->setValue(value);
}

void SkeletonWidget::on_horizontalSliderScore_valueChanged(int value)
{
    ui->LabelScore->setText(QString::number(value));
}
