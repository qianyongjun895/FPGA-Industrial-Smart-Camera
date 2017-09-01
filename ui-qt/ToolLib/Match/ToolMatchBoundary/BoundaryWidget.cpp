#include "BoundaryWidget.h"
#include "ui_BoundaryWidget.h"
#include "FWMatchBoundaryLabel.h"

BoundaryWidget::BoundaryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoundaryWidget)
{
    ui->setupUi(this);
    m_label = new FWMatchBoundaryLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    connect(ui->btnSkeletonUp,&QPushButton::released,this,&BoundaryWidget::GetCurrentTime);
    connect(ui->btnSkeletonDown,&QPushButton::released,this,&BoundaryWidget::GetCurrentTime);
    connect(ui->btnSkeletonLeft,&QPushButton::released,this,&BoundaryWidget::GetCurrentTime);
    connect(ui->btnSkeletonRight,&QPushButton::released,this,&BoundaryWidget::GetCurrentTime);
    connect((FWMatchBoundaryLabel*)m_label,&FWMatchBoundaryLabel::signalPointsChange,\
            this,&BoundaryWidget::ShowCurrentPointCoordinate);

}

BoundaryWidget::~BoundaryWidget()
{
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete ui;
}
QPoint BoundaryWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

/**
 * @brief BoundaryWidget::on_radioButtonIncongruous_clicked
 * @author dgq
 * @note 设置搜索方向为异向
 */
void BoundaryWidget::on_radioButtonIncongruous_clicked()
{
    ((FWMatchBoundaryLabel*)m_label)->SetListRectY(1);
}

/**
 * @brief BoundaryWidget::on_radioButtonSyntropy_clicked
 * @author dgq
 * @note 设置搜索方向为同向
 */
void BoundaryWidget::on_radioButtonSyntropy_clicked()
{
    ((FWMatchBoundaryLabel*)m_label)->SetListRectY(0);
}

/**
 * @brief BoundaryWidget::on_radioButtonEdgeX_clicked
 * @author dgq
 * @note 设置边沿的方向为x方向
 */
void BoundaryWidget::on_radioButtonEdgeX_clicked()
{
    ((FWMatchBoundaryLabel*)m_label)->SetRectXDirect(0);
}

/**
 * @brief BoundaryWidget::on_radioButtonEdgeY_clicked
 * @author dgq
 * @note 设置边沿的方向为y方向
 */
void BoundaryWidget::on_radioButtonEdgeY_clicked()
{
    ((FWMatchBoundaryLabel*)m_label)->SetRectXDirect(1);
}

/**
 * @brief BoundaryWidget::on_radioButtonRoiX_clicked
 * @author dgq
 * @note 设置Roi方向为x方向
 */
void BoundaryWidget::on_radioButtonRoiX_clicked()
{
    ((FWMatchBoundaryLabel*)m_label)->SetRectYDirect(0);
}

/**
 * @brief BoundaryWidget::on_radioButtonRoiY_clicked
 * @author dgq
 * @note 设置Roi方向为y方向
 */
void BoundaryWidget::on_radioButtonRoiY_clicked()
{
    ((FWMatchBoundaryLabel*)m_label)->SetRectYDirect(1);
}

void BoundaryWidget::on_btnSkeletonUp_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonUp);
    if(ui->btnSkeletonUp->autoRepeatInterval() == 10)
        ((FWMatchBoundaryLabel*)m_label)->MoveUp(5);
    else
        ((FWMatchBoundaryLabel*)m_label)->MoveUp(1);
}

void BoundaryWidget::on_btnSkeletonDown_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonDown);
    if(ui->btnSkeletonDown->autoRepeatInterval() == 10)
        ((FWMatchBoundaryLabel*)m_label)->MoveDown(5);
    else
        ((FWMatchBoundaryLabel*)m_label)->MoveDown(1);
}

void BoundaryWidget::on_btnSkeletonLeft_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonLeft);
    if(ui->btnSkeletonLeft->autoRepeatInterval() == 10)
        ((FWMatchBoundaryLabel*)m_label)->MoveLeft(5);
    else
        ((FWMatchBoundaryLabel*)m_label)->MoveLeft(1);
}

void BoundaryWidget::on_btnSkeletonRight_pressed()
{
    SetBtnRepeatParam(ui->btnSkeletonRight);
    if(ui->btnSkeletonRight->autoRepeatInterval() == 10)
        ((FWMatchBoundaryLabel*)m_label)->MoveRight(5);
    else
        ((FWMatchBoundaryLabel*)m_label)->MoveRight(1);
}

/**
 * @brief BoundaryWidget::GetCurrentTime
 * @author dgq
 * @note 获取按钮释放的时间
 */
void BoundaryWidget::GetCurrentTime()
{
    startTime = QTime::currentTime();
}

/**
 * @brief BoundaryWidget::SetBtnRepeatParam
 * @param btn 需要实现长按效果的按钮对象
 * @author dgq
 * @note 设置按钮长按事件的加速属性
 */
void BoundaryWidget::SetBtnRepeatParam(QPushButton *btn)
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

void BoundaryWidget::ShowCurrentPointCoordinate(QPoint point,int index)
{
    switch (index) {
    case 1:
        ui->labelFind1->setText("("+QString::number(point.x())+","+QString::number(point.y())+")");
        break;
    case 2:
        ui->labelFind2->setText("("+QString::number(point.x())+","+QString::number(point.y())+")");
        break;
    case 3:
        ui->labelStudy1->setText("("+QString::number(point.x())+","+QString::number(point.y())+")");
        break;
    case 4:
        ui->labelStudy2->setText("("+QString::number(point.x())+","+QString::number(point.y())+")");
        break;
    case 5:
        ui->labelEdgePoint1->setText("("+QString::number(point.x())+","+QString::number(point.y())+")");
        break;
    case 6:
        ui->labelEdgePoint2->setText("("+QString::number(point.x())+","+QString::number(point.y())+")");
        break;
    default:
        break;
    }
}
