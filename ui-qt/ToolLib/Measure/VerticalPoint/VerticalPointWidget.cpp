#include <QDebug>
#include "VerticalPointWidget.h"
#include "ui_VerticalPointWidget.h"
#include "FWVerticalPointLabel.h"
#include <QMessageBox>
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

VerticalPointWidget::VerticalPointWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerticalPointWidget)
{
    ui->setupUi(this);
    m_label = new FWVerticalPointLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->setupUi(this);
    connect(ui->PointComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(PointTaskChangeSlot(int)));
    connect(ui->LineComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(LineTaskChangeSlot(int)));
    connect(ui->PointResultComboBox, SIGNAL(activated(int)), this, SLOT(PointResultChangeSlot(int)));
    connect(ui->LineResultComboBox, SIGNAL(activated(int)), this, SLOT(LineResultChangeSlot(int)));
}

VerticalPointWidget::~VerticalPointWidget()
{
    delete ui;
}

/**
 * @brief VerticalPointWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int VerticalPointWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index = atoi(ui->PointComboBox->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->PointResultComboBox->currentIndex());
    int i_task2_index = atoi(ui->LineComboBox->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task2_index,&i_task_id);
    int i_result2_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->LineResultComboBox->currentIndex());
    pStephead->step_link.link_count = 2;
    pStephead->step_link.link_info[0].step_index = i_task1_index;
    pStephead->step_link.link_info[0].result_index = i_result1_index;
    pStephead->step_link.link_info[1].step_index = i_task2_index;
    pStephead->step_link.link_info[1].result_index = i_result2_index;
    return 1;
}

/**
 * @brief VerticalPointWidget::Init_Input_Ptr
 * @param ptr 输入结构体内存指针
 * @param i_step_index 任务步骤号
 * @author dgq
 * @note 初始化Input结构体指针
 */
void VerticalPointWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    m_i_load_first = 0;
    unsigned int i_task_id = 0;
    int i = 0;
    ui->PointComboBox->addItem("");
    ui->LineComboBox->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitPointCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->PointComboBox->addItem(QString::number(i+1)+"."+name);
            name = InitLineCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->LineComboBox->addItem(QString::number(i+1)+"."+name);
        }
    }
    if(new_flag)
    {
        TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
        pStephead->step_link.link_count = 0;
        pStephead->step_link.link_info[0].step_index = 0;
        pStephead->step_link.link_info[0].result_index = 0;
        pStephead->step_link.link_info[1].step_index = 0;
        pStephead->step_link.link_info[1].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
    }
    InitData(i_step_index);
    m_i_load_first = 1;

}

//Task_Step_TypeID_Get_By_Index

QString VerticalPointWidget::InitPointCombobox(int TaskIndex, int id)
{
    QString name;
    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 0)
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
QString VerticalPointWidget::InitLineCombobox(int TaskIndex, int id)
{
    QString name;

    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 1)
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

/**
 * @brief VerticalPointWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化
 */
void VerticalPointWidget::InitData(int i_step_index)
{
    int i = 0;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task1_index = pStephead->step_link.link_info[0].step_index;
    int i_result1_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = pStephead->step_link.link_info[1].step_index;
    int i_result2_index = pStephead->step_link.link_info[1].result_index;
    for(i = 0; i < ui->PointComboBox->count(); i++)
    {
        if(i_task1_index == atoi(ui->PointComboBox->itemText(i).toStdString().c_str()))
            ui->PointComboBox->setCurrentIndex(i);
    }
    for(i = 0; i < ui->LineComboBox->count(); i++)
    {
        if(i_task2_index == atoi(ui->LineComboBox->itemText(i).toStdString().c_str()))
            ui->LineComboBox->setCurrentIndex(i);
    }
//    ui->LineComboBox->setCurrentIndex(i_task2_index);
    ui->PointResultComboBox->addItem(" ");
    ui->LineResultComboBox->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    int ret = TaskMultiRstNumGet(i_task1_index,1,&i_mul_rst_cnt);
    if(ret == 0)
    {
        for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
        {
            ui->PointResultComboBox->addItem(tr("点")+QString::number(i));
        }
    }
    ret = TaskMultiRstNumGet(i_task2_index,1,&i_mul_rst_cnt);
    if(ret == 0)
    {
        for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
        {
            ui->LineResultComboBox->addItem(tr("直线")+QString::number(i));
        }
    }
    QPoint point;
    LineParameter pLinePara;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task1_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->PointResultComboBox->setEnabled(false);
    }else
    {
        ui->PointResultComboBox->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result1_index));
    }
    GetRefPara(i_task1_index,i_result1_index,&point);
    ((FWVerticalPointLabel*)m_label)->SetPoint(point);
    Task_Step_Type_ID_Get(i_task2_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->LineResultComboBox->setEnabled(false);
    }else
    {
        ui->LineResultComboBox->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result2_index));
    }
    measure_ref_line_result_get(i_task2_index,i_result2_index,(void*)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWVerticalPointLabel*)m_label)->SetLine(line);
}


/**
 * @brief VerticalPointWidget::PointTaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void VerticalPointWidget::PointTaskChangeSlot(int index)
{
    ((FWVerticalPointLabel*)m_label)->SetPoint(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int index1 = atoi(ui->PointComboBox->currentText().toStdString().c_str());
        if(index1 == 0)
        {
            ui->PointResultComboBox->clear();
            return;
        }
        ui->PointResultComboBox->setEnabled(true);

        ui->PointResultComboBox->clear();
        ui->PointResultComboBox->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(index1 ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag ==1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(index1,1,&i_mul_rst_cnt);
            for(unsigned int i = 1; i<= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = tr("点")+QString::number(i);
                ui->PointResultComboBox->addItem(strLineIndex);
            }
        }
        else
        {
            ui->PointResultComboBox->setEnabled(false);
            QPoint point1;
            int i_result1_index = Get_Point_Or_Line_Result_Id(id,0);
            GetRefPara(index1,i_result1_index,&point1);
            ((FWVerticalPointLabel*)m_label)->SetPoint(point1);
        }

    }
}

/**
 * @brief VerticalPointWidget::LineTaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void VerticalPointWidget::LineTaskChangeSlot(int index)
{
    ((FWVerticalPointLabel*)m_label)->SetLine(QLine(0,0,0,0));
    if(m_i_load_first == 1)
    {
        int index2 = atoi(ui->LineComboBox->currentText().toStdString().c_str());
        if(index2 == 0)
        {
            ui->LineResultComboBox->clear();
            return;
        }
        ui->LineResultComboBox->setEnabled(true);

        ui->LineResultComboBox->clear();
        ui->LineResultComboBox->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(index2 ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag ==1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(index2,1,&i_mul_rst_cnt);
            for(unsigned int i = 1; i <= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = "直线"+QString::number(i);
                ui->LineResultComboBox->addItem(strLineIndex);
            }
        }
        else
        {
            LineParameter pLinePara;
            ui->LineResultComboBox->setEnabled(false);
            int i_result_index = Get_Point_Or_Line_Result_Id(id,0);

            int ret = measure_ref_line_result_get(index2,i_result_index,(void*)&pLinePara,1);
            if(ret != 0)
            {
                QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
                QMessageBox::about(this,tr(""),info);
                return;
            }
            QLine line;
            Line_Osd_Init(&pLinePara,&line);
            ((FWVerticalPointLabel*)m_label)->SetLine(line);
        }

    }
}

/**
 * @brief VerticalPointWidget::PointResultChangeSlot
 * @param index 下拉框索引
 * @author dgq
 * @note 引用结果发生改变时的处理
 */
void VerticalPointWidget::PointResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result1_index = ui->PointResultComboBox->currentIndex();
        int Task_index1 = atoi(ui->PointComboBox->currentText().toStdString().c_str());

        QPoint point;
        float point_pix_vga_x = 0.0;
        float point_pix_vga_y = 0.0;
        float point_pix_sub_x = 0.0;
        float point_pix_sub_y = 0.0;
#if 1
        POINT_F pointf;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index1,&id);
        int result_index = Get_Point_Or_Line_Result_Id(id,Result1_index);
        int ret = measure_ref_point_result_get(Task_index1,result_index,&pointf,1);
        if(ret != 0)
        {
            qDebug()<<"measure_ref_point_result_get ret = "<<ret;
        }
        point_pix_sub_x = pointf.x_f;
        point_pix_sub_y = pointf.y_f;
        PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
        point.setX(point_pix_vga_x);
        point.setY(point_pix_vga_y);
        ((FWVerticalPointLabel*)m_label)->SetPoint(point);
#endif


    }
}

void VerticalPointWidget::LineResultChangeSlot(int index)
{

    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index2 = atoi(ui->LineComboBox->currentText().toStdString().c_str());
        int Result2_index = ui->LineResultComboBox->currentIndex();
        if(Result2_index == 0)
        {
            ((FWVerticalPointLabel*)m_label)->SetLine(QLine(0,0,0,0));
            return;
        }

        unsigned int id;
        Task_Step_Type_ID_Get(Task_index2,&id);
        int ret = measure_ref_line_result_get(Task_index2,Get_Point_Or_Line_Result_Id(id,Result2_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
            QMessageBox::about(this,tr(""),info);
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWVerticalPointLabel*)m_label)->SetLine(line);
    }
}


int VerticalPointWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
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

int VerticalPointWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
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

void VerticalPointWidget::GetRefPara(int ref_step,int ref_result,QPoint *point)
{
    float point_pix_vga_x = 0.0;
    float point_pix_vga_y = 0.0;
    float point_pix_sub_x = 0.0;
    float point_pix_sub_y = 0.0;
    POINT_F pointf;
    int ret = measure_ref_point_result_get(ref_step,ref_result,&pointf,1);
    if(ret != 0)
    {
        qDebug()<<"measure_ref_point_result_get ret = "<<__LINE__<<ret;
    }
    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    point->setX(point_pix_vga_x);
    point->setY(point_pix_vga_y);
}


void VerticalPointWidget::Get_Result_From_Ram()
{
    P2LS_PRIVATE_PARAM *pPrivate = (P2LS_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);

    int pix_vga_x = 0;
    int pix_vga_y = 0;
    float pix_sub_x = pPrivate->model_p2l_stroke_result.stroke_pixel.x_f;
    float pix_sub_y = pPrivate->model_p2l_stroke_result.stroke_pixel.y_f;
    PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    ((FWVerticalPointLabel*)m_label)->SetSet_Parameter_To_RamPoint(QPoint(pix_vga_x,pix_vga_y));
}

QPoint VerticalPointWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
