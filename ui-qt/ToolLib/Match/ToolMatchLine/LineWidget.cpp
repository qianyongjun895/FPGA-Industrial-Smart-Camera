#include "LineWidget.h"
#include "ui_LineWidget.h"
#include <QDebug>
#include <QMessageBox>
#include "PixelConvert.h"
LineWidget::LineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);
    m_label = new FWMatchLineLabel(this);

    connect((FWMatchLineLabel*)m_label,&FWMatchLineLabel::Point1ChangeSignal,this,&LineWidget::Point1ChangeSlot);
    connect((FWMatchLineLabel*)m_label,&FWMatchLineLabel::Point2ChangeSignal,this,&LineWidget::Point2ChangeSlot);

    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    m_timer  = new QTimer;
}

LineWidget::~LineWidget()
{
    disconnect(this,0,0,0);

    if(m_timer  !=NULL)
    {
        delete m_timer;
        m_timer = NULL;
    }
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete ui;
}
void LineWidget::Point1ChangeSlot(QPoint point1,int kind )
{
    QString strTmep;
    strTmep = "(";
    strTmep +=QString::number(point1.x());
    strTmep += ",";
    strTmep +=QString::number(point1.y());
    strTmep += ")";
    ui->txtPoint1Coor->setText(strTmep);

    if(kind == 1)
    {
        int index = ((FWMatchLineLabel*)m_label)->GetLineCurrence();
        ui->txtCurrentLine->setText(QString::number(index+1));
        GetLinePara(index);
    }
}
void LineWidget::Point2ChangeSlot(QPoint point2,int kind )
{
    QString strTmep;
    strTmep = "(";
    strTmep +=QString::number(point2.x());
    strTmep += ",";
    strTmep +=QString::number(point2.y());
    strTmep += ")";
    ui->txtPoint2Coor->setText(strTmep);
    if(kind == 1)
    {
        int index = ((FWMatchLineLabel*)m_label)->GetLineCurrence();
        ui->txtCurrentLine->setText(QString::number(index+1));
        GetLinePara(index);
    }
}
QPoint LineWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
int LineWidget::Set_Parameter_To_Ram()
{
    SetDataToLib();
    return 1;
}
void LineWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMatchLineLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (LINE_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    m_num = 1;
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        InitNewAddControlData();
        SetDataToLibByIndex(m_num-1);
    }
    InitData();
}
void LineWidget::GetLinePara(int index)
{
    int lineNum = pInputPara->line_num;
    int scandirs[20];
    int i = 0;
    for(i = 0;i<lineNum;i++)
    {
        float theta = pInputPara->line_paras[i].anchor_theta;
        unsigned char sensitivity = pInputPara->line_paras[i].sensitivity;
        unsigned char scan_dir = pInputPara->line_paras[i].scan_dir;
        unsigned char color_tran_dir = pInputPara->line_paras[i].color_tran_dir;
        unsigned char angle_filter_th= pInputPara->line_paras[i].angle_filter_th;
        unsigned char search_range= pInputPara->line_paras[i].search_range;
        scandirs[i] = (int)scan_dir;

        if(i == index)
        {
            ui->horizontalSliderSensitivity->setValue(sensitivity); //灵敏度
            ui->txtSensitivity->setText(QString::number(sensitivity));
            ui->horizontalSliderRange->setValue(search_range); //搜索范围
            ui->txtRange->setText(QString::number(search_range));
            ui->txtAngleLimit->setText(QString::number(angle_filter_th));
            ui->horizontalSliderAngleLimit->setValue(angle_filter_th); //角度门限
            if(scandirs[i] == 0)
            {
                ui->radioButtonNegativeDir->setChecked(false);
                ui->radioButtonPositiveDir->setChecked(true);
            }else if(scandirs[i] == 1)
            {
                ui->radioButtonNegativeDir->setChecked(true);
                ui->radioButtonPositiveDir->setChecked(false);
            }
            if (color_tran_dir == 0)
            {
                ui->radioButtonW2B->setChecked(false);
                ui->radioButtonB2W->setChecked(true);

            }else if(color_tran_dir == 1) //明到暗
            {
                ui->radioButtonW2B->setChecked(true);
                ui->radioButtonB2W->setChecked(false);
            }
            ui->labelTheta->setText(QString::number(theta,'f',3));
        }
    }
}
void LineWidget::InitData()
{
    memset(&m_line_input,0,sizeof(LINE_INPUT_PARAM));
    memcpy(&m_line_input,pInputPara,sizeof(LINE_INPUT_PARAM));
    int lineNum = pInputPara->line_num;
    m_num = lineNum;
    unsigned int iRange[20];
    int i = 0;
    for(i = 0;i<lineNum;i++)
    {
        int x1 = pInputPara->line_paras[i].anchor[0].x_i;
        int y1 = pInputPara->line_paras[i].anchor[0].y_i;
        int x2 = pInputPara->line_paras[i].anchor[1].x_i;
        int y2 = pInputPara->line_paras[i].anchor[1].y_i;

        float theta = pInputPara->line_paras[i].anchor_theta;
        unsigned char sensitivity = pInputPara->line_paras[i].sensitivity;
        unsigned char scan_dir = pInputPara->line_paras[i].scan_dir;
        unsigned char color_tran_dir = pInputPara->line_paras[i].color_tran_dir;
        unsigned char angle_filter_th= pInputPara->line_paras[i].angle_filter_th;
        unsigned int search_range= pInputPara->line_paras[i].search_range;
        iRange[i] = (int)search_range;
        m_points1[i].setX(x1);
        m_points1[i].setY(y1);
        m_points2[i].setX(x2);
        m_points2[i].setY(y2);

        if(i == 0)
        {
            ui->horizontalSliderSensitivity->setValue(sensitivity); //灵敏度
            ui->txtSensitivity->setText(QString::number(sensitivity));
            ui->horizontalSliderRange->setValue(search_range); //搜索范围
            ui->txtRange->setText(QString::number(search_range));
            ui->txtAngleLimit->setText(QString::number(angle_filter_th));
            ui->horizontalSliderAngleLimit->setValue(angle_filter_th); //角度门限
            if(scan_dir == 0)
            {
                ui->radioButtonNegativeDir->setChecked(false);
                ui->radioButtonPositiveDir->setChecked(true);
            }else if(scan_dir == 1)
            {
                ui->radioButtonNegativeDir->setChecked(true);
                ui->radioButtonPositiveDir->setChecked(false);

            }
            if (color_tran_dir == 0)
            {
                ui->radioButtonW2B->setChecked(false);
                ui->radioButtonB2W->setChecked(true);

            }else if(color_tran_dir == 1) //明到暗
            {
                ui->radioButtonW2B->setChecked(true);
                ui->radioButtonB2W->setChecked(false);
            }

            ui->radioButton_Point1->setChecked(true);
            QString strTmep;
            strTmep = "(";
            strTmep +=QString::number(x1);
            strTmep += ",";
            strTmep +=QString::number(y1);
            strTmep += ")";
            ui->txtPoint1Coor->setText(strTmep);
            strTmep = "(";
            strTmep +=QString::number(x2);
            strTmep += ",";
            strTmep +=QString::number(y2);
            strTmep += ")";
            ui->txtPoint2Coor->setText(strTmep);
            ui->txtLineNum->setText(QString::number(lineNum));
            ui->txtCurrentLine->setText(QString::number(1));
            ui->labelTheta->setText(QString::number(theta,'f',3));
            m_point1.setX(x1);
            m_point1.setY(y1);
            m_point2.setX(x2);
            m_point2.setY(y2);
        }
    }
    ((FWMatchLineLabel*)m_label)->SetScanDirs((int *)iRange,lineNum);
    ((FWMatchLineLabel*)m_label)->SetPoints(m_points1,m_points2,lineNum);
}
void LineWidget::InitNewAddControlData()
{
    ui->horizontalSliderSensitivity->setValue(40); //灵敏度
    ui->txtSensitivity->setText(QString::number(40));
    ui->horizontalSliderRange->setValue(39); //搜索范围
    ui->txtRange->setText(QString::number(39));
    ui->txtAngleLimit->setText(QString::number(16));
    ui->horizontalSliderAngleLimit->setValue(16); //角度门限
    ui->radioButtonW2B->setChecked(true);
    ui->radioButtonPositiveDir->setChecked(true);
    ui->radioButton_Point1->setChecked(true);
    ui->txtPoint1Coor->setText("(320,100)");
    ui->txtPoint2Coor->setText("(320,300)");
    ui->txtLineNum->setText(QString::number(1));
    ui->txtCurrentLine->setText(QString::number(1));
    ui->labelTheta->setText(QString::number(0));
}
void LineWidget::on_btnPreLine_clicked()
{
    int current = ui->txtCurrentLine->text().toInt();
    if(current > 1)
    {
        current--;
        ui->txtCurrentLine->setText(QString::number(current));
        ((FWMatchLineLabel*)m_label)->SetLineCurrence(current-1);
    }
}

void LineWidget::on_btnNextLine_clicked()
{
    int current = ui->txtCurrentLine->text().toInt();
    int count = ui->txtLineNum->text().toInt();
    if(current >= 1 && current < count)
    {
        current++;
        ui->txtCurrentLine->setText(QString::number(current));
        ((FWMatchLineLabel*)m_label)->SetLineCurrence(current-1);
    }
}

void LineWidget::on_btnLineSub_clicked()
{
    if(m_num > 1)
    {
        this->m_num--;
        ((FWMatchLineLabel*)m_label)->SetLineNum(m_num);
        ui->txtLineNum->setText(QString::number(m_num));
    }
}

void LineWidget::on_btnLineAdd_clicked()
{
    if(m_num < 20)
    {
        this->m_num++;
        ((FWMatchLineLabel*)m_label)->SetLineNum(m_num,1);
        InitNewAddControlData();
        ui->txtLineNum->setText(QString::number(m_num));
        SetDataToLibByIndex(m_num-1);
        ui->txtCurrentLine->setText(QString::number(m_num));
    }
}
void LineWidget::moveUp()
{
    int step = GetStepValue();
    QPoint *point1s = ((FWMatchLineLabel*)m_label)->GetPoints1();
    QPoint *point2s = ((FWMatchLineLabel*)m_label)->GetPoints2();
    int index = ui->txtCurrentLine->text().toInt()-1;
    int y = 0;
    int x = 0;
    if(ui->radioButton_Point1->isChecked())
    {
        x = point1s[index].x();
        y = point1s[index].y();
    }else if(ui->radioButton_Point2->isChecked())
    {
        x = point2s[index].x();
        y = point2s[index].y();
    }

    if(y - step >= 0)
    {
        QPoint point;
        point.setX(x);
        point.setY(y-step);

        if(ui->radioButton_Point1->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint1(point);


        }else if(ui->radioButton_Point2->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint2(point);
        }
    }
}
void LineWidget::moveDown()
{
    int step = GetStepValue();
    QPoint *point1s = ((FWMatchLineLabel*)m_label)->GetPoints1();
    QPoint *point2s = ((FWMatchLineLabel*)m_label)->GetPoints2();
    int index = ui->txtCurrentLine->text().toInt()-1;
    int y = 0;
    int x = 0;
    if(ui->radioButton_Point1->isChecked())
    {
        x = point1s[index].x();
        y = point1s[index].y();
    }else if(ui->radioButton_Point2->isChecked())
    {
        x = point2s[index].x();
        y = point2s[index].y();
    }

    if(y + step <= 480)
    {
        QPoint point;
        point.setX(x);
        point.setY(y+step);

        if(ui->radioButton_Point1->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint1(point);


        }else if(ui->radioButton_Point2->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint2(point);
        }
    }
}
void LineWidget::moveLeft()
{
    int step = GetStepValue();
    QPoint *point1s = ((FWMatchLineLabel*)m_label)->GetPoints1();
    QPoint *point2s = ((FWMatchLineLabel*)m_label)->GetPoints2();
    int index = ui->txtCurrentLine->text().toInt()-1;
    int y = 0;
    int x = 0;
    if(ui->radioButton_Point1->isChecked())
    {
        x = point1s[index].x();
        y = point1s[index].y();
    }else if(ui->radioButton_Point2->isChecked())
    {
        x = point2s[index].x();
        y = point2s[index].y();
    }

    if(x - step >= 0)
    {
        QPoint point;
        point.setX(x - step);
        point.setY(y);
        if(ui->radioButton_Point1->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint1(point);


        }else if(ui->radioButton_Point2->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint2(point);
        }
    }
}
void LineWidget::moveRight()
{
    int step = GetStepValue();
    QPoint *point1s = ((FWMatchLineLabel*)m_label)->GetPoints1();
    QPoint *point2s = ((FWMatchLineLabel*)m_label)->GetPoints2();
    int index = ui->txtCurrentLine->text().toInt()-1;
    int y = 0;
    int x = 0;
    if(ui->radioButton_Point1->isChecked())
    {
        x = point1s[index].x();
        y = point1s[index].y();
    }else if(ui->radioButton_Point2->isChecked())
    {
        x = point2s[index].x();
        y = point2s[index].y();
    }

    if(x + step <= 640)
    {
        QPoint point;
        point.setX(x +step);
        point.setY(y);

        if(ui->radioButton_Point1->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint1(point);


        }else if(ui->radioButton_Point2->isChecked())
        {
            ((FWMatchLineLabel*)m_label)->SetPoint2(point);
        }
    }
}
void LineWidget::on_btnMoveUp_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveUp()));
    m_timer->start(100);
}

void LineWidget::on_btnMoveUp_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(moveUp()));
    moveUp();
}

void LineWidget::on_btnMoveDown_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveDown()));
    m_timer->start(100);
}

void LineWidget::on_btnMoveDown_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(moveDown()));
    moveDown();
}

void LineWidget::on_btnMoveLeft_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveLeft()));
    m_timer->start(100);
}

void LineWidget::on_btnMoveLeft_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(moveLeft()));
    moveLeft();
}

void LineWidget::on_btnMoveRight_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveRight()));
    m_timer->start(100);
}

void LineWidget::on_btnMoveRight_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(moveRight()));
    moveRight();
}
void LineWidget::SubSensitivity()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    int step = GetStepValue();
    int value = ui->horizontalSliderSensitivity->value();

    if(value -step >= 0)
    {
        ui->horizontalSliderSensitivity->setValue(value - step);
        ui->txtSensitivity->setText(QString::number(value - step));
        pInputPara->line_paras[index].sensitivity = ui->horizontalSliderSensitivity->value();
    }
}
void LineWidget::AddSensitivity()
{
    int step = GetStepValue();
    int value = ui->horizontalSliderSensitivity->value();
    int index = ui->txtCurrentLine->text().toInt()-1;
    if(value +step <= 100)
    {
        ui->horizontalSliderSensitivity->setValue(value+step);
        ui->txtSensitivity->setText(QString::number(step+value));
        pInputPara->line_paras[index].sensitivity = ui->horizontalSliderSensitivity->value();
    }
}
void LineWidget::RangeDown()
{
    int step = GetStepValue();
    int value = ui->horizontalSliderRange->value();
    int index = ui->txtCurrentLine->text().toInt()-1;
    if(value -step >= 1)
    {
        ui->horizontalSliderRange->setValue(value -step);
        ui->txtRange->setText(QString::number(value-step));
        pInputPara->line_paras[index].search_range = ui->horizontalSliderRange->value();
    }
}
void LineWidget::RangeUp()
{
    int step = GetStepValue();
    int value = ui->horizontalSliderRange->value();
    int index = ui->txtCurrentLine->text().toInt()-1;
    if(value +step >= 1)
    {
        ui->horizontalSliderRange->setValue(value + step);
        ui->txtRange->setText(QString::number(value + step));
        pInputPara->line_paras[index].search_range = ui->horizontalSliderRange->value();
    }
}
void LineWidget::SubAngleLimit()
{
    int step = GetStepValue();
    int value = ui->horizontalSliderAngleLimit->value();
    int index = ui->txtCurrentLine->text().toInt()-1;
    if(value -step >= 0)
    {
        ui->horizontalSliderAngleLimit->setValue(value -step);
        ui->txtAngleLimit->setText(QString::number(value-step));
        pInputPara->line_paras[index].angle_filter_th = ui->horizontalSliderAngleLimit->value();
    }
}
void LineWidget::AddAngleLimit()
{
    int step = GetStepValue();
    int value = ui->horizontalSliderAngleLimit->value();
    int index = ui->txtCurrentLine->text().toInt()-1;
    if(value + step <= 100)
    {
        ui->horizontalSliderAngleLimit->setValue(value + step);
        ui->txtAngleLimit->setText(QString::number(value + step));
        pInputPara->line_paras[index].angle_filter_th = ui->horizontalSliderAngleLimit->value();
    }
}
void LineWidget::on_btnSubSensitivity_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SubSensitivity()));
    m_timer->start(100);
}

void LineWidget::on_btnSubSensitivity_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(SubSensitivity()));
    SubSensitivity();
}

void LineWidget::on_btnAddSensitivity_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(AddSensitivity()));
    m_timer->start(100);
}

void LineWidget::on_btnAddSensitivity_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(AddSensitivity()));
    AddSensitivity();
}

void LineWidget::on_horizontalSliderSensitivity_sliderReleased()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].sensitivity = ui->horizontalSliderSensitivity->value();
}

void LineWidget::on_btnRangeDown_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(RangeDown()));
    m_timer->start(100);
}

void LineWidget::on_btnRangeDown_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(RangeDown()));
    RangeDown();
}

void LineWidget::on_btnRangeUp_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(RangeUp()));
    m_timer->start(100);
}

void LineWidget::on_btnRangeUp_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(RangeUp()));
    RangeUp();
}

void LineWidget::on_horizontalSliderRange_sliderReleased()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].search_range = ui->horizontalSliderRange->value();
}

void LineWidget::on_btnSubAngleLimit_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SubAngleLimit()));
    m_timer->start(100);
}

void LineWidget::on_btnSubAngleLimit_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(SubAngleLimit()));
    SubAngleLimit();
}

void LineWidget::on_btnAddAngleLimit_pressed()
{
    m_iPresstimes =1;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(AddAngleLimit()));
    m_timer->start(100);
}

void LineWidget::on_btnAddAngleLimit_released()
{
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(AddAngleLimit()));
    AddAngleLimit();
}

void LineWidget::on_horizontalSliderAngleLimit_sliderReleased()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].angle_filter_th = ui->horizontalSliderAngleLimit->value();
}

void LineWidget::on_radioButtonPositiveDir_clicked()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].scan_dir = 0;

}

void LineWidget::on_radioButtonNegativeDir_clicked()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].scan_dir = 1;

}

void LineWidget::on_radioButtonW2B_clicked()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].color_tran_dir = 1;
}

void LineWidget::on_radioButtonB2W_clicked()
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    pInputPara->line_paras[index].color_tran_dir = 0;
}
void LineWidget::SetDataToLibByIndex(int index)
{
    QPoint *points1 = ((FWMatchLineLabel*)m_label)->GetPoints1();
    QPoint *points2 = ((FWMatchLineLabel*)m_label)->GetPoints2();
    pInputPara->line_num = m_num;
    pInputPara->line_paras[index].anchor[0].x_i = points1[index].x();
    pInputPara->line_paras[index].anchor[0].y_i = points1[index].y();
    pInputPara->line_paras[index].anchor[1].x_i = points2[index].x();
    pInputPara->line_paras[index].anchor[1].y_i = points2[index].y();

    if(ui->radioButtonPositiveDir->isChecked())
    {
        pInputPara->line_paras[index].scan_dir =0;
    }else
    {
        pInputPara->line_paras[index].scan_dir =1;
    }
    if(ui->radioButtonW2B->isChecked())
    {
        pInputPara->line_paras[index].color_tran_dir =  1;
    }else
    {
        pInputPara->line_paras[index].color_tran_dir =  0;
    }
    pInputPara->line_paras[index].sensitivity = ui->horizontalSliderSensitivity->value();
    pInputPara->line_paras[index].angle_filter_th = ui->horizontalSliderAngleLimit->value();
    pInputPara->line_paras[index].search_range = ui->horizontalSliderRange->value();

}
void LineWidget::SetDataToLib()
{
    QPoint *points1 = ((FWMatchLineLabel*)m_label)->GetPoints1();
    QPoint *points2 = ((FWMatchLineLabel*)m_label)->GetPoints2();
    pInputPara->line_num = m_num;
    int i = 0;

    for(i = 0;i<m_num;i++)
    {
        pInputPara->line_paras[i].anchor[0].x_i = points1[i].x();
        pInputPara->line_paras[i].anchor[0].y_i = points1[i].y();
        pInputPara->line_paras[i].anchor[1].x_i = points2[i].x();
        pInputPara->line_paras[i].anchor[1].y_i = points2[i].y();

        /*if(ui->radioButtonPositiveDir->isChecked())
        {
            pInputPara->line_paras[i].scan_dir =0;
        }else
        {
            pInputPara->line_paras[i].scan_dir =1;
        }
        if(ui->radioButtonW2B->isChecked())
        {
            pInputPara->line_paras[i].color_tran_dir =  1;
        }else
        {
            pInputPara->line_paras[i].color_tran_dir =  0;
        }
        pInputPara->line_paras[i].sensitivity = ui->horizontalSliderSensitivity->value();
        pInputPara->line_paras[i].angle_filter_th = ui->horizontalSliderAngleLimit->value();
        pInputPara->line_paras[i].search_range = ui->horizontalSliderRange->value();*/
    }
    //((FWMatchLineLabel*)m_label)->SetScanDirs[scandirs,lineNum];
    //((FWMatchLineLabel*)m_label)->SetPoints(m_points1,m_points2,lineNum);
}
int LineWidget::GetStepValue()
{
    if(this->m_iPresstimes>0 && m_iPresstimes< 8)
    {
        m_iPresstimes++;
        return 1;
    }
    int value=1;

    m_iPresstimes++;

    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;
    else
        value =1;
    return value;
}

void LineWidget::on_horizontalSliderSensitivity_valueChanged(int value)
{
    ui->txtSensitivity->setText(QString::number(value));
}

void LineWidget::on_horizontalSliderRange_valueChanged(int value)
{
    int index = ui->txtCurrentLine->text().toInt()-1;
    ui->txtRange->setText(QString::number(value));
    ((FWMatchLineLabel*)m_label)->SetCurrentDir(value,index);
}

void LineWidget::on_horizontalSliderAngleLimit_valueChanged(int value)
{
    ui->txtAngleLimit->setText(QString::number(value));
}
void LineWidget::Get_Result_From_Ram()
{
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    int iNum = 0;
    int x1[MULTI_LINE_NUM_MAX];
    int x2[MULTI_LINE_NUM_MAX];
    int y1[MULTI_LINE_NUM_MAX];
    int y2[MULTI_LINE_NUM_MAX];

    for(int i = 0;i<MULTI_LINE_NUM_MAX;i++)
    {
        if(((LINE_PRIVATE_PARAM*)pPrivate)->model_line_valid_flag[i]==1)
        {
            int x = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].x;
            int y = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].y;

            m_line_para[iNum].theta = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].theta;
            m_line_para[iNum].degree = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].degree;
            m_line_para[iNum].rotate_deg = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].rotate_deg;
            m_line_para[iNum].cos = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].cos;
            m_line_para[iNum].sin = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].sin;
            m_line_para[iNum].x = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].x;
            m_line_para[iNum].y = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].y;
            m_line_para[iNum].phy_x =((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].phy_x;
            m_line_para[iNum].phy_y = ((LINE_PRIVATE_PARAM*)pPrivate)->model_line_rst[i].phy_y;
            Line_Osd_Init(&m_line_para[iNum],&m_line[iNum]);
            iNum++;
        }

    }
    for(int j = 0; j<iNum;j++)
    {
        x1[j] = m_line[j].p1().x();
        x2[j] = m_line[j].p2().x();
        y1[j] = m_line[j].p1().y();
        y2[j] = m_line[j].p2().y();
    }
    ((FWMatchLineLabel*)m_label)->SetSampleLines(x1,y1,x2,y2,iNum);
}
#if 1
void LineWidget::Vertical_Line_Paint(unsigned int sub_pixel_x, QLine *pOsd_line)
{
    //pOsd_line->setP1(QPoint((unsigned int)X_Y_CONVERT_SUB2UI((float)sub_pixel_x),0));
    //pOsd_line->setP2(QPoint((unsigned int)X_Y_CONVERT_SUB2UI((float)sub_pixel_x),VGA_HEIGHT));
    pOsd_line->setP1(QPoint(sub_pixel_x/16,0));
    pOsd_line->setP2(QPoint(sub_pixel_x/16,VGA_HEIGHT));
}

int LineWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
{
    int i = 0;
    int count = 0;
    QPointF calc_point[4];

    calc_point[0].setX(0);
    calc_point[0].setY(b_f);
    /* Point1 x=640, calculate y  */
    calc_point[1].setX(VGA_WIDTH);
    calc_point[1].setY(k_f*VGA_WIDTH+b_f);
    /* Point1 y=0, calculate x  */
    calc_point[2].setX((0-b_f)/k_f);
    calc_point[2].setY(0);
    /* Point1 y=480, calculate x  */
    calc_point[3].setX((VGA_HEIGHT-b_f)/k_f);
    calc_point[3].setY(VGA_HEIGHT);

    for(i = 0; i < 4; i++)
    {
        //DRV_PRINT(LOCATION_DEBUG, "point%d: x=%d, y=%d\n", i, (int)calc_point[i].x_f, (int)calc_point[i].y_f);
        if(calc_point[i].x()>=0 && calc_point[i].x()<=VGA_WIDTH && calc_point[i].y()>=0 && calc_point[i].y()<=VGA_HEIGHT)
        {
            if(count == 0)
            {
                count++;
                pOsd_line->setP1(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
            else
            {
                pOsd_line->setP2(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
        }
    }

    return 0;
}

int LineWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
{
    float line_kf = 0;
    float line_bf = 0;
    float line_k, line_b;

    float pix_vga_y = 0.0;
    float pix_vga_x = 0.0;
    float pix_sub_y = (float)pLinePara->y;
    float pix_sub_x = (float)pLinePara->x;
    PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    line_kf = tan(pLinePara->theta);
//    line_bf = (X_Y_CONVERT_SUB2UI((float)pLinePara->y) - line_kf * X_Y_CONVERT_SUB2UI((float)pLinePara->x));
    line_bf = (pix_vga_y - line_kf * pix_vga_x);
    line_k = (int)(line_kf*10000);
    line_b = (int)(line_bf*10000);

    if(line_k == 0x7fffffff || line_k == 0x80000000 || line_b == 0x7fffffff || line_b == 0x80000000)
    {
//        Vertical_Line_Paint((unsigned int)pLinePara->x, pOsdLine);

        pOsdLine->setP1(QPoint(pix_vga_x,0));
        pOsdLine->setP2(QPoint(pix_vga_x,VGA_HEIGHT));
    }else
    {
        Line_Paint_Base_On_KB_SubPixel(line_kf, line_bf, pOsdLine);
    }

    return 0;
}

#endif

