#include <QDebug>
#include "PolygonCenterWidget.h"
#include "ui_PolygonCenterWidget.h"
#include "FWPolygonCenterLabel.h"
#include <QMessageBox>
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

PolygonCenterWidget::PolygonCenterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PolygonCenterWidget)
{
    ui->setupUi(this);
    m_label = new FWPolygonCenterLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    m_line_cnt = 3;
    ui->labelNum->setText("3");
    ui->GroupBoxEdge4->setEnabled(false);
    connect(ui->comboBoxLine1, SIGNAL(currentIndexChanged(int)), this, SLOT(Line1TaskChangeSlot(int)));
    connect(ui->comboBoxLine2, SIGNAL(currentIndexChanged(int)), this, SLOT(Line2TaskChangeSlot(int)));
    connect(ui->comboBoxLine3, SIGNAL(currentIndexChanged(int)), this, SLOT(Line3TaskChangeSlot(int)));
    connect(ui->comboBoxLine4, SIGNAL(currentIndexChanged(int)), this, SLOT(Line4TaskChangeSlot(int)));
    connect(ui->comboBoxLine1Result, SIGNAL(activated(int)), this, SLOT(Line1ResultChangeSlot(int)));
    connect(ui->comboBoxLine2Result, SIGNAL(activated(int)), this, SLOT(Line2ResultChangeSlot(int)));
    connect(ui->comboBoxLine3Result, SIGNAL(activated(int)), this, SLOT(Line3ResultChangeSlot(int)));
    connect(ui->comboBoxLine4Result, SIGNAL(activated(int)), this, SLOT(Line4ResultChangeSlot(int)));
}

PolygonCenterWidget::~PolygonCenterWidget()
{
    delete ui;
}
QPoint PolygonCenterWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
int PolygonCenterWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLine1Result->currentIndex());
    int i_task2_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task2_index,&i_task_id);
    int i_result2_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLine2Result->currentIndex());
    int i_task3_index = atoi(ui->comboBoxLine3->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task3_index,&i_task_id);
    int i_result3_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLine3Result->currentIndex());
    int i_task4_index = atoi(ui->comboBoxLine4->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task4_index,&i_task_id);
    int i_result4_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLine4Result->currentIndex());
    if((i_task1_index == i_task2_index && i_result1_index == i_result2_index) ||\
            (i_task1_index == i_task3_index && i_result1_index == i_result3_index)||\
            (i_task1_index == i_task4_index && i_result1_index == i_result4_index)||\
            (i_task2_index == i_task3_index && i_result2_index == i_result3_index)||\
            (i_task2_index == i_task4_index && i_result2_index == i_result4_index)||\
            (i_task3_index == i_task4_index && i_result3_index == i_result4_index))
    {
        return 0;
    }
    pStephead->step_link.link_count = m_line_cnt;
    pStephead->step_link.link_info[0].step_index = i_task1_index;
    pStephead->step_link.link_info[0].result_index = i_result1_index;
    pStephead->step_link.link_info[1].step_index = i_task2_index;
    pStephead->step_link.link_info[1].result_index = i_result2_index;
    pStephead->step_link.link_info[2].step_index = i_task3_index;
    pStephead->step_link.link_info[2].result_index = i_result3_index;

    if(m_line_cnt == 4)
    {
        pStephead->step_link.link_info[3].step_index = i_task4_index;
        pStephead->step_link.link_info[3].result_index = i_result4_index;
    }
    if(pInputPara == NULL)
    {
        return 0;
    }
    ((PYG_CENTER_INPUT_PARAM *)pInputPara)->line_num = m_line_cnt;
    return 1;
}

void PolygonCenterWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWPolygonCenterLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    m_i_load_first = 0;

    m_line_cnt= ((PYG_CENTER_INPUT_PARAM *)pInputPara)->line_num;
    if(m_line_cnt != 3 ||m_line_cnt != 4)
        m_line_cnt = 3;
    ui->labelNum->setText(QString::number(m_line_cnt));
    unsigned int i_task_id = 0;
    int i = 0;
    ui->comboBoxLine1->addItem("");
    ui->comboBoxLine2->addItem("");
    ui->comboBoxLine3->addItem("");
    ui->comboBoxLine4->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitLineCombobox(i+1,i_task_id);
            if(!name.isEmpty())
            {
                ui->comboBoxLine1->addItem(QString::number(i+1)+"."+name);
                ui->comboBoxLine2->addItem(QString::number(i+1)+"."+name);
                ui->comboBoxLine3->addItem(QString::number(i+1)+"."+name);
                ui->comboBoxLine4->addItem(QString::number(i+1)+"."+name);
            }
        }
    }

    if(new_flag)
    {

        TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
        pStephead->step_link.link_count = 0;
        pStephead->step_link.link_info[0].step_index = 0;
        pStephead->step_link.link_info[0].result_index = 0;
        pStephead->step_link.link_info[1].step_index = 0;
        pStephead->step_link.link_info[1].step_index = 0;
        pStephead->step_link.link_info[2].result_index = 0;
        pStephead->step_link.link_info[2].step_index = 0;
        pStephead->step_link.link_info[3].result_index = 0;
        pStephead->step_link.link_info[4].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
    }
    InitData(i_step_index);
    m_i_load_first = 1;
}


QString PolygonCenterWidget::InitLineCombobox(int TaskIndex, int id)
{
    QString name;
    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 1)//线任务
    {
        char taskName[40];
        memset(taskName,0,40);
        int ret = Get_Task_Name(TaskIndex, taskName);
        if(ret != -1)
        {
            name = QString::fromUtf8(taskName);
        }
    }
    return name;
}

void PolygonCenterWidget::InitData(int i_step_index)
{
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);

    InitTaskComboBox(pStephead);
    InitResultComboBox(pStephead);
    InitOsdData(pStephead);
}

void PolygonCenterWidget::InitTaskComboBox(TASK_STEP_HEADER *p)
{
    int i_task1_index = p->step_link.link_info[0].step_index;
    int i_task2_index = p->step_link.link_info[1].step_index;
    int i_task3_index = p->step_link.link_info[2].step_index;
    int i_task4_index = p->step_link.link_info[3].step_index;
    int i = 0;
    for(i = 0; i < ui->comboBoxLine1->count(); i++)
    {
        if(i_task1_index == atoi(ui->comboBoxLine1->itemText(i).toStdString().c_str()))
            ui->comboBoxLine1->setCurrentIndex(i);
    }
    for(i = 0; i < ui->comboBoxLine2->count(); i++)
    {
        if(i_task2_index == atoi(ui->comboBoxLine2->itemText(i).toStdString().c_str()))
            ui->comboBoxLine2->setCurrentIndex(i);
    }

    for(i = 0; i < ui->comboBoxLine3->count(); i++)
    {
        if(i_task3_index == atoi(ui->comboBoxLine3->itemText(i).toStdString().c_str()))
            ui->comboBoxLine3->setCurrentIndex(i);
    }
    if(m_line_cnt == 4)
    {
        for(i = 0; i < ui->comboBoxLine4->count(); i++)
        {
            if(i_task4_index == atoi(ui->comboBoxLine4->itemText(i).toStdString().c_str()))
                ui->comboBoxLine4->setCurrentIndex(i);
        }
    }
}


void PolygonCenterWidget::InitResultComboBox(TASK_STEP_HEADER *p)
{
    unsigned int i = 0;
    int i_task1_index = p->step_link.link_info[0].step_index;
    int i_task2_index = p->step_link.link_info[1].step_index;
    int i_task3_index = p->step_link.link_info[2].step_index;
    int i_task4_index = p->step_link.link_info[3].step_index;
    ui->comboBoxLine1Result->clear();
    ui->comboBoxLine2Result->clear();
    ui->comboBoxLine3Result->clear();
    ui->comboBoxLine4Result->clear();
    ui->comboBoxLine1Result->addItem(" ");
    ui->comboBoxLine2Result->addItem(" ");
    ui->comboBoxLine3Result->addItem(" ");
    ui->comboBoxLine4Result->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    if(i_task1_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task1_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLine1Result->addItem(tr("直线")+QString::number(i));
            }
        }
    }
    if(i_task2_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task2_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLine2Result->addItem(tr("直线")+QString::number(i));
            }
        }
    }
    if(i_task3_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task3_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLine3Result->addItem(tr("直线")+QString::number(i));
            }
        }
    }
    if(i_task4_index > 0 && m_line_cnt == 4)
    {
        int ret = TaskMultiRstNumGet(i_task4_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLine4Result->addItem(tr("直线")+QString::number(i));
            }
        }
    }
}

void PolygonCenterWidget::InitOsdData(TASK_STEP_HEADER *p)
{
    int i_task1_index = p->step_link.link_info[0].step_index;
    int i_task2_index = p->step_link.link_info[1].step_index;
    int i_task3_index = p->step_link.link_info[2].step_index;
    int i_task4_index = p->step_link.link_info[3].step_index;
    int i_result1_index = p->step_link.link_info[0].result_index;
    int i_result2_index = p->step_link.link_info[1].result_index;
    int i_result3_index = p->step_link.link_info[2].result_index;
    int i_result4_index = p->step_link.link_info[3].result_index;
    LineParameter pLinePara;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task1_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxLine1Result->setEnabled(false);
    }else
    {
        ui->comboBoxLine1Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result1_index));
    }
    measure_ref_line_result_get(i_task1_index,i_result1_index,(void *)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine1(line);

    Task_Step_Type_ID_Get(i_task2_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxLine2Result->setEnabled(false);
    }else
    {
        ui->comboBoxLine2Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result2_index));
    }
    measure_ref_line_result_get(i_task2_index,i_result2_index,(void *)&pLinePara,1);
    Line_Osd_Init(&pLinePara,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine2(line);

    Task_Step_Type_ID_Get(i_task3_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxLine3Result->setEnabled(false);
    }else
    {
        ui->comboBoxLine3Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result3_index));
    }
    measure_ref_line_result_get(i_task3_index,i_result3_index,(void *)&pLinePara,1);
    Line_Osd_Init(&pLinePara,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine3(line);

    if(m_line_cnt == 4)
    {
        Task_Step_Type_ID_Get(i_task4_index,&id);
        Mul_Flag = Get_Multi_Result_Task_Flag(id);
        ui->GroupBoxEdge4->setEnabled(true);
        if(Mul_Flag == -1)
        {
            ui->comboBoxLine4Result->setEnabled(false);
        }else
        {
            ui->comboBoxLine4Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result4_index));
        }
        measure_ref_line_result_get(i_task4_index,i_result4_index,(void *)&pLinePara,1);
        Line_Osd_Init(&pLinePara,&line);
        ((FWPolygonCenterLabel*)m_label)->SetLine4(line);
    }
}

void PolygonCenterWidget::on_btnNumAdd_clicked()
{
    if(m_line_cnt  == 4)
    {
        return;
    }
    m_line_cnt = 4;
    ui->labelNum->setText(QString::number(m_line_cnt));
    ui->GroupBoxEdge4->setEnabled(true);
}

void PolygonCenterWidget::on_btnSubNum_clicked()
{
    if(m_line_cnt  == 3)
    {
        return;
    }
    m_line_cnt = 3;
    ui->labelNum->setText(QString::number(m_line_cnt));
    ui->comboBoxLine4->setCurrentIndex(0);
    ui->comboBoxLine4Result->setCurrentIndex(0);
    ui->GroupBoxEdge4->setEnabled(false);
    QLine line = QLine(0,0,0,0);
    ((FWPolygonCenterLabel*)m_label)->SetLine4(line);

}

void PolygonCenterWidget::Line1TaskChangeSlot(int index)
{
    ((FWPolygonCenterLabel*)m_label)->SetLine1(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine1Result,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine1(line);
}

void PolygonCenterWidget::Line2TaskChangeSlot(int index)
{
    ((FWPolygonCenterLabel*)m_label)->SetLine2(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine2Result,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine2(line);
}

void PolygonCenterWidget::Line3TaskChangeSlot(int index)
{
    ((FWPolygonCenterLabel*)m_label)->SetLine3(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine3->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine3Result,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine3(line);
}


void PolygonCenterWidget::Line4TaskChangeSlot(int index)
{
    ((FWPolygonCenterLabel*)m_label)->SetLine4(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine4->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine4Result,&line);
    ((FWPolygonCenterLabel*)m_label)->SetLine4(line);
}


void PolygonCenterWidget::LineResulChangetSlot(int task_index,QComboBox *mCom,QLine *line)
{
    if(m_i_load_first == 1)
    {
        if(task_index == 0)
        {
            mCom->clear();
            return;
        }
        mCom->setEnabled(true);

        mCom->clear();
        mCom->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index,1,&i_mul_rst_cnt);
            for(unsigned int i = 1; i <= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = "直线"+QString::number(i);
                mCom->addItem(strLineIndex);
            }
        }
        else
        {
            LineParameter pLinePara;
            mCom->setEnabled(false);
            int ret = measure_ref_line_result_get(task_index,Point_Or_Line_Result_Id_Change_UI_Id(id,0),(void*)&pLinePara,1);
            if(ret != 0)
            {
                QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
                QMessageBox::about(this,tr(""),info);
                return;
            }
            Line_Osd_Init(&pLinePara,line);
        }
    }
}

void PolygonCenterWidget::Line1ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine1Result->currentIndex();

        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            ((FWPolygonCenterLabel*)m_label)->SetLine1(QLine(0,0,0,0));
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWPolygonCenterLabel*)m_label)->SetLine1(line);
    }
}

void PolygonCenterWidget::Line2ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine2Result->currentIndex();
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            ((FWPolygonCenterLabel*)m_label)->SetLine2(QLine(0,0,0,0));
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWPolygonCenterLabel*)m_label)->SetLine2(line);
    }
}


void PolygonCenterWidget::Line3ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine3->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine3Result->currentIndex();
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            ((FWPolygonCenterLabel*)m_label)->SetLine3(QLine(0,0,0,0));
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWPolygonCenterLabel*)m_label)->SetLine3(line);
    }
}

void PolygonCenterWidget::Line4ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine4->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine4Result->currentIndex();
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            ((FWPolygonCenterLabel*)m_label)->SetLine4(QLine(0,0,0,0));
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWPolygonCenterLabel*)m_label)->SetLine4(line);
    }
}

int PolygonCenterWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
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

int PolygonCenterWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
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

void PolygonCenterWidget::Get_Result_From_Ram()
{
    PYG_CENTER_PRIVATE_PARAM *pPrivate = (PYG_CENTER_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);

    int pix_vga_x = 0;
    int pix_vga_y = 0;
    float pix_sub_x = pPrivate->pyg_center_model_rst.center_pixel.x_f;
    float pix_sub_y = pPrivate->pyg_center_model_rst.center_pixel.y_f;
    PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    ((FWPolygonCenterLabel*)m_label)->SetSet_Parameter_To_RamPoint(QPoint(pix_vga_x,pix_vga_y));
}
