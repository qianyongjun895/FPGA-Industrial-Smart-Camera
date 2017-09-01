#include <QDebug>
#include "BasePointWidget.h"
#include "ui_BasePointWidget.h"
#include "QMessageBox"

BasePointWidget::BasePointWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasePointWidget)
{
    ui->setupUi(this);

    m_current_index = 0;

    m_label = new FWMatchBasePointLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    connect(ui->btnMoveUp,&QPushButton::released,this,&BasePointWidget::GetCurrentTime);
    connect(ui->btnMoveDown,&QPushButton::released,this,&BasePointWidget::GetCurrentTime);
    connect(ui->btnMoveLeft,&QPushButton::released,this,&BasePointWidget::GetCurrentTime);
    connect(ui->btnMoveRight,&QPushButton::released,this,&BasePointWidget::GetCurrentTime);
    connect((FWMatchBasePointLabel*)m_label,&FWMatchBasePointLabel::CurrentPointChangeSignal,\
            this,&BasePointWidget::ShowCurrentPointCoordinate);
}

BasePointWidget::~BasePointWidget()
{
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete ui;
}


/**
 * @brief BasePointWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint BasePointWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
/**
 * @brief BasePointWidget::SetBtnRepeatParam
 * @param btn 需要设置长按参数的按钮
 * @author dgq
 * @note 设置按钮长按加速参数
 */
void BasePointWidget::SetBtnRepeatParam(QPushButton *btn)
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
 * @brief BasePointWidget::GetCurrentTime
 * @author dgq
 * @note 获取按钮释放的时间
 */
void BasePointWidget::GetCurrentTime()
{
    startTime = QTime::currentTime();
}


/**
 * @brief BasePointWidget::on_btnMoveUp_pressed
 * @author dgq
 * @note 向上坐标微调
 */
void BasePointWidget::on_btnMoveUp_pressed()
{
    SetBtnRepeatParam(ui->btnMoveUp);
    if(ui->btnMoveUp->autoRepeatInterval() == 10)
        ((FWMatchBasePointLabel*)m_label)->KeyMoveUp(5);
    else
        ((FWMatchBasePointLabel*)m_label)->KeyMoveUp(1);
}

/**
 * @brief BasePointWidget::on_btnMoveDown_pressed
 * @author dgq
 * @note 向下坐标微调
 */
void BasePointWidget::on_btnMoveDown_pressed()
{
    SetBtnRepeatParam(ui->btnMoveDown);
    if(ui->btnMoveDown->autoRepeatInterval() == 10)
        ((FWMatchBasePointLabel*)m_label)->KeyMoveDown(5);
    else
        ((FWMatchBasePointLabel*)m_label)->KeyMoveDown(1);
}

/**
 * @brief BasePointWidget::on_btnMoveLeft_pressed
 * @author dgq
 * @note 向左坐标微调
 */
void BasePointWidget::on_btnMoveLeft_pressed()
{
    SetBtnRepeatParam(ui->btnMoveLeft);
    if(ui->btnMoveLeft->autoRepeatInterval() == 10)
        ((FWMatchBasePointLabel*)m_label)->KeyMoveLeft(5);
    else
        ((FWMatchBasePointLabel*)m_label)->KeyMoveLeft(1);
}

/**
 * @brief BasePointWidget::on_btnMoveRight_pressed
 * @author dgq
 * @note 向右坐标微调
 */
void BasePointWidget::on_btnMoveRight_pressed()
{
    SetBtnRepeatParam(ui->btnMoveRight);
    if(ui->btnMoveRight->autoRepeatInterval() == 10)
        ((FWMatchBasePointLabel*)m_label)->KeyMoveRight(5);
    else
        ((FWMatchBasePointLabel*)m_label)->KeyMoveRight(1);
}

/**
 * @brief BasePointWidget::ShowCurrentPointCoordinate
 * @param index 当前点的索引
 * @param point 当前点的坐标
 * @author dgq
 * @note 将OSD返回的当前点信息在对应的控件上显示出来
 */
void BasePointWidget::ShowCurrentPointCoordinate(int index, QPoint point)
{
    QString point_info = "("+QString::number(point.x())+","+QString::number(point.y())+")";
    ui->txtCurrentPoint->setText(QString::number(index+1));
    ui->txtPoint1Coor->setText(point_info);
}

/**
 * @brief BasePointWidget::on_btnPrePoint_clicked
 * @author dgq
 * @note 切换到上一个点
 */
void BasePointWidget::on_btnPrePoint_clicked()
{
    m_current_index = ui->txtCurrentPoint->text().toInt();
    if(m_current_index > 1)
    {
        m_current_index--;

    }else
    {
        m_current_index = ui->txtPointNum->text().toInt();
    }
    ui->txtCurrentPoint->setText(QString::number(m_current_index));
    int value = (m_current_index-1);
    ((FWMatchBasePointLabel*)m_label)->SetBasePointCurrentIndex(value);
}

/**
 * @brief BasePointWidget::on_btnNextPoint_clicked
 * @author dgq
 * @note 切换到下一个点
 */
void BasePointWidget::on_btnNextPoint_clicked()
{
    m_current_index = ui->txtCurrentPoint->text().toInt();
    if(m_current_index < ui->txtPointNum->text().toInt())
    {
        m_current_index++;

    }
    else
    {
        m_current_index = 1;
    }
    ui->txtCurrentPoint->setText(QString::number(m_current_index));
    int value = (m_current_index-1);
    ((FWMatchBasePointLabel*)m_label)->SetBasePointCurrentIndex(value);
}

/**
 * @brief BasePointWidget::on_btnPointSub_clicked
 * @author dgq
 * @note 减少一个基准点
 */
void BasePointWidget::on_btnPointSub_clicked()
{
    int PointNum = ui->txtPointNum->text().toInt();
    if(PointNum > 1)
    {
        PointNum--;
        ui->txtPointNum->setText(QString::number(PointNum));
        ((FWMatchBasePointLabel*)m_label)->SetBasePointNum(PointNum);
    }
}

/**
 * @brief BasePointWidget::on_btnPointAdd_clicked
 * @author dgq
 * @note 增加一个基准点
 */
void BasePointWidget::on_btnPointAdd_clicked()
{
    int PointNum = ui->txtPointNum->text().toInt();
    if(PointNum < BASE_POINT_NUM_MAX)
    {
        PointNum++;
        ui->txtPointNum->setText(QString::number(PointNum));
        ((FWMatchBasePointLabel*)m_label)->SetBasePointNum(PointNum);
    }
}

/**
 * @brief BasePointWidget::Init_Input_Ptr
 * @param ptr
 * @author
 * @note 获取任务内存指针
 */
void BasePointWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchBasePointLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (BASEPOINT_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_point_num = 1;
        ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_points[0].x_i = 320;
        ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_points[0].y_i = 240;
    }
    InitData();
}

/**
 * @brief BasePointWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 取样按钮响应函数
 */
int BasePointWidget::Set_Parameter_To_Ram()
{
    if(pInputPara == NULL)
    {
        return 0;
    }
    int i_num = ((FWMatchBasePointLabel*)m_label)->GetBasePointNum();
    QVector<QPoint> vt = ((FWMatchBasePointLabel*)m_label)->GetBasePointData();
    
    ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_point_num = i_num;
    for(int i = 0; i < vt.count(); i++)
    {
        ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_points[i].x_i = vt[i].x();
        ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_points[i].y_i = vt[i].y();
    }
    return 1;
}

/**
 * @brief BasePointWidget::InitData
 * @author dgq
 * @note 初始化界面
 */
void BasePointWidget::InitData()
{
    memset(&m_base_point_input,0,sizeof(BASEPOINT_INPUT_PARAM));
    memcpy(&m_base_point_input,pInputPara,sizeof(BASEPOINT_INPUT_PARAM));
    int i_num = ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_point_num;
    if(i_num <= 0 || i_num > 20)
    {
//        QMessageBox::about(this,tr(""),tr("基准点个数为0"));
        return;
    }
    QVector<QPoint> points;
    for(int i = 0; i < i_num; i++)
    {
        points.append(QPoint(((BASEPOINT_INPUT_PARAM *)pInputPara)->base_points[i].x_i,
                             ((BASEPOINT_INPUT_PARAM *)pInputPara)->base_points[i].y_i));
    }
    ((FWMatchBasePointLabel*)m_label)->SetBasePointNum(i_num);
    ((FWMatchBasePointLabel*)m_label)->SetBasePointData(points);
    ui->txtPointNum->setText(QString::number(i_num));
}

