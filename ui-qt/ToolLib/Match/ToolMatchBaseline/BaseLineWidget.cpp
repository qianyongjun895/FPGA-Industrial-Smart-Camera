#include <QDebug>
#include "BaseLineWidget.h"
#include "ui_BaseLineWidget.h"
#include <QMessageBox>

BaseLineWidget::BaseLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseLineWidget)
{
    ui->setupUi(this);
    m_label = new FWMatchBaseLineLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->radioButton_Point1->setChecked(true);
    connect(ui->btnMoveUp,&QPushButton::released,this,&BaseLineWidget::GetCurrentTime);
    connect(ui->btnMoveDown,&QPushButton::released,this,&BaseLineWidget::GetCurrentTime);
    connect(ui->btnMoveLeft,&QPushButton::released,this,&BaseLineWidget::GetCurrentTime);
    connect(ui->btnMoveRight,&QPushButton::released,this,&BaseLineWidget::GetCurrentTime);
    connect((FWMatchBaseLineLabel*)m_label,&FWMatchBaseLineLabel::Point1ChangeSignal,\
            this,&BaseLineWidget::ShowCurrentPoint1Coordinate);
    connect((FWMatchBaseLineLabel*)m_label,&FWMatchBaseLineLabel::Point2ChangeSignal,\
            this,&BaseLineWidget::ShowCurrentPoint2Coordinate);

}

BaseLineWidget::~BaseLineWidget()
{
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete ui;
}

/**
 * @brief BaseLineWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint BaseLineWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

/**
 * @brief BaseLineWidget::SetBtnRepeatParam
 * @param btn 需要设置长按参数的按钮
 * @author dgq
 * @note 设置按钮长按加速参数
 */
void BaseLineWidget::SetBtnRepeatParam(QPushButton *btn)
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
 * @brief BaseLineWidget::on_btnMoveUp_pressed
 * @author dgq
 * @note 向上坐标微调
 */
void BaseLineWidget::on_btnMoveUp_pressed()
{
    SetBtnRepeatParam(ui->btnMoveUp);
    if(ui->btnMoveUp->autoRepeatInterval() == 10)
        ((FWMatchBaseLineLabel*)m_label)->MoveUp(5);
    else
        ((FWMatchBaseLineLabel*)m_label)->MoveUp(1);
}

/**
 * @brief BaseLineWidget::on_btnMoveDown_pressed
 * @author dgq
 * @note 向下坐标微调
 */
void BaseLineWidget::on_btnMoveDown_pressed()
{
    SetBtnRepeatParam(ui->btnMoveDown);
    if(ui->btnMoveDown->autoRepeatInterval() == 10)
        ((FWMatchBaseLineLabel*)m_label)->MoveDown(5);
    else
        ((FWMatchBaseLineLabel*)m_label)->MoveDown(1);
}

/**
 * @brief BaseLineWidget::on_btnMoveLeft_pressed
 * @author dgq
 * @note 向左坐标微调
 */
void BaseLineWidget::on_btnMoveLeft_pressed()
{
    SetBtnRepeatParam(ui->btnMoveLeft);
    if(ui->btnMoveLeft->autoRepeatInterval() == 10)
        ((FWMatchBaseLineLabel*)m_label)->MoveLeft(5);
    else
        ((FWMatchBaseLineLabel*)m_label)->MoveLeft(1);
}

/**
 * @brief BaseLineWidget::on_btnMoveRight_pressed
 * @author dgq
 * @note 向右坐标微调
 */
void BaseLineWidget::on_btnMoveRight_pressed()
{
    SetBtnRepeatParam(ui->btnMoveRight);
    if(ui->btnMoveRight->autoRepeatInterval() == 10)
        ((FWMatchBaseLineLabel*)m_label)->MoveRight(5);
    else
        ((FWMatchBaseLineLabel*)m_label)->MoveRight(1);
}

/**
 * @brief BaseLineWidget::GetCurrentTime
 * @author dgq
 * @note 获取按钮释放的时间
 */
void BaseLineWidget::GetCurrentTime()
{
    startTime = QTime::currentTime();
}

/**
 * @brief BaseLineWidget::ShowCurrentPoint1Coordinate
 * @param point 基准线的点a坐标
 * @param index 基准线的索引
 * @author dgq
 * @note 将OSD返回的当前基准线信息在对应的控件上显示出来
 */
void BaseLineWidget::ShowCurrentPoint1Coordinate( QPoint point,int index)
{
    QString point_info = "("+QString::number(point.x())+","+QString::number(point.y())+")";
    ui->txtCurrentLine->setText(QString::number(index+1));
    ui->txtPoint1Coor->setText(point_info);
    ui->radioButton_Point1->setChecked(true);
}

/**
 * @brief BaseLineWidget::ShowCurrentPoint2Coordinate
 * @param point 基准线的点b坐标
 * @param index 基准线的索引
 * @author dgq
 * @note 将OSD返回的当前基准线信息在对应的控件上显示出来
 */
void BaseLineWidget::ShowCurrentPoint2Coordinate(QPoint point,int index)
{
    QString point_info = "("+QString::number(point.x())+","+QString::number(point.y())+")";
    ui->txtCurrentLine->setText(QString::number(index+1));
    ui->txtPoint2Coor->setText(point_info);
    ui->radioButton_Point2->setChecked(true);
}

/**
 * @brief BaseLineWidget::on_btnLineSub_clicked
 * @author dgq
 * @note 基准线数量减一
 */
void BaseLineWidget::on_btnLineSub_clicked()
{
    int lineNum = ui->txtLineNum->text().toInt();
    if(lineNum > 1)
    {
        lineNum--;
        ui->txtLineNum->setText(QString::number(lineNum));
        //ui->labelPic->SetLineNum(lineNum);
        ((FWMatchBaseLineLabel*)m_label)->SetBaseLineNum(lineNum);
//        SetLineMatchLineNum(lineNum);
    }
}

/**
 * @brief BaseLineWidget::on_btnLineAdd_clicked
 * @autor dgq
 * @note 基准线数量加一
 */
void BaseLineWidget::on_btnLineAdd_clicked()
{
    int lineNum = ui->txtLineNum->text().toInt();
    if(lineNum < 20)
    {
        lineNum++;
        ui->txtLineNum->setText(QString::number(lineNum));
        ((FWMatchBaseLineLabel*)m_label)->SetBaseLineNum(lineNum);
//        SetLineMatchLineNum(lineNum);
    }
}

/**
 * @brief BaseLineWidget::on_btnPreLine_clicked
 * @author dgq
 * @note 切换到上一条基准线
 */
void BaseLineWidget::on_btnPreLine_clicked()
{
    m_index = ui->txtCurrentLine->text().toInt();
    if(m_index > 1)
    {
        m_index--;

    }else
    {
        m_index = ui->txtLineNum->text().toInt();
    }
    ui->txtCurrentLine->setText(QString::number(m_index));
    int value = (m_index-1);
    ((FWMatchBaseLineLabel*)m_label)->SetBaseLineCurrentIndex(value);
}

/**
 * @brief BaseLineWidget::on_btnNextLine_clicked
 * @author dgq
 * @note 切换到下一条基准线
 */
void BaseLineWidget::on_btnNextLine_clicked()
{
    m_index = ui->txtCurrentLine->text().toInt();
    if(m_index < ui->txtLineNum->text().toInt())
    {
        m_index++;

    }
    else
    {
        m_index = 1;
    }
    ui->txtCurrentLine->setText(QString::number(m_index));
    int value = (m_index-1);
    ((FWMatchBaseLineLabel*)m_label)->SetBaseLineCurrentIndex(value);
}

/**
 * @brief BaseLineWidget::on_radioButton_Point1_clicked
 * @author dgq
 * @note 切换当前基准线的编辑点为点a
 */
void BaseLineWidget::on_radioButton_Point1_clicked()
{
    ((FWMatchBaseLineLabel*)m_label)->SetBaseLineCurrentPoint(1);
}

/**
 * @brief BaseLineWidget::on_radioButton_Point2_clicked
 * @author dgq
 * @note 切换当前基准线的编辑点为点b
 */
void BaseLineWidget::on_radioButton_Point2_clicked()
{
    ((FWMatchBaseLineLabel*)m_label)->SetBaseLineCurrentPoint(2);
}


/**
 * @brief BasePointWidget::Init_Input_Ptr
 * @param ptr
 * @author
 * @note 获取任务内存指针
 */
void BaseLineWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchBaseLineLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (BASE_LINE_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_num = 1;
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[0].line_points[0].x_i = 320;
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[0].line_points[0].y_i = 10;
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[0].line_points[1].x_i = 320;
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[0].line_points[1].y_i = 470;
    }
    InitData();
}

int BaseLineWidget::Set_Parameter_To_Ram()
{
    if(pInputPara == NULL)
    {
        return 0;
    }
    QVector<QLine> vt_lines = ((FWMatchBaseLineLabel*)m_label)->GetBaseLines();
    int i_line_cnt = vt_lines.count();
    ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_num = i_line_cnt;
    for(int i = 0; i < i_line_cnt; i++)
    {
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[0].x_i = vt_lines[i].x1();
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[0].y_i = vt_lines[i].y1();
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[1].x_i = vt_lines[i].x2();
        ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[1].y_i = vt_lines[i].y2();
    }
    return 1;
}

/**
 * @brief BaseLineWidget::InitData
 * @author dgq
 * @note 初始化界面
 */
void BaseLineWidget::InitData()
{
    int i_num = ((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_num;
    if(i_num <= 0 || i_num > 20)
    {
//        QMessageBox::about(this,tr(""),tr("基准点个数为0"));SetBaseLinePoints
        return;
    }
    QPoint point1[20];
    QPoint point2[20];
    for(int i = 0; i < i_num; i++)
    {
        point1[i].setX(((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[0].x_i);
        point1[i].setY(((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[0].y_i);
        point2[i].setX(((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[1].x_i);
        point2[i].setY(((BASE_LINE_INPUT_PARAM *)pInputPara)->base_line_info[i].line_points[1].y_i);
    }
    ((FWMatchBaseLineLabel*)m_label)->SetBaseLinePoints(point1,point2,i_num);
    ui->txtLineNum->setText(QString::number(i_num));
}

