#include <QDebug>
#include "P2PLineWidget.h"
#include "ui_P2PLineWidget.h"
#include "TaskStepGlobal.h"
#include "FWP2PLineLabel.h"
#include "PixelConvert.h"
#include <QMessageBox>
#include "TaskRstGlobal.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

P2PLineWidget::P2PLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::P2PLineWidget)
{
    ui->setupUi(this);
    m_label = new FWP2PLineLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    connect(ui->comboBoxPoint1, SIGNAL(currentIndexChanged(int)), this, SLOT(Point1TaskChangeSlot(int)));
    connect(ui->comboBoxPoint2, SIGNAL(currentIndexChanged(int)), this, SLOT(Point2TaskChangeSlot(int)));
    connect(ui->comboBoxPoint1Result, SIGNAL(activated(int)), this, SLOT(Point1ResultChangeSlot(int)));
    connect(ui->comboBoxPoint2Result, SIGNAL(activated(int)), this, SLOT(Point2ResultChangeSlot(int)));
}

P2PLineWidget::~P2PLineWidget()
{
    delete ui;
}

/**
 * @brief P2PLineWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int P2PLineWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index =  atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxPoint1Result->currentIndex());
    int i_task2_index =  atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task2_index,&i_task_id);
    int i_result2_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxPoint2Result->currentIndex());
    if(i_task1_index == i_task2_index && i_result1_index == i_result2_index)
    {
        return 0;
    }
    pStephead->step_link.link_count = 2;
    pStephead->step_link.link_info[0].step_index = i_task1_index;
    pStephead->step_link.link_info[0].result_index = i_result1_index;
    pStephead->step_link.link_info[1].step_index = i_task2_index;
    pStephead->step_link.link_info[1].result_index = i_result2_index;

    return 1;
}
/**
 * @brief P2PLineWidget::Init_Input_Ptr
 * @param ptr 输入结构体内存指针
 * @param i_step_index 任务步骤号
 * @author dgq
 * @note 初始化Input结构体指针
 */
void P2PLineWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWP2PLineLabel*)m_label)->SetPenColor(pen_color);
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
    ui->comboBoxPoint1->addItem("");
    ui->comboBoxPoint2->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitPointCombobox(i+1,i_task_id);
            if(!name.isEmpty())
            {
                ui->comboBoxPoint1->addItem(QString::number(i+1)+"."+name);
                ui->comboBoxPoint2->addItem(QString::number(i+1)+"."+name);
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
        pStephead->step_link.link_info[1].result_index = 0;
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
    }
    InitData(i_step_index);
    m_i_load_first = 1;

}

QString P2PLineWidget::InitPointCombobox(int TaskIndex, int id)
{
    QString name;
    int ret = Get_Point_Or_Line_Flag(id);
    if(ret == 0)//线任务
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
 * @brief P2PDistanceWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化
 */
void P2PLineWidget::InitData(int i_step_index)
{
    int i = 0;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task1_index = pStephead->step_link.link_info[0].step_index;
    int i_result1_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = pStephead->step_link.link_info[1].step_index;
    int i_result2_index = pStephead->step_link.link_info[1].result_index;

    for(i = 0; i < ui->comboBoxPoint1->count(); i++)
    {
        if(i_task1_index == atoi(ui->comboBoxPoint1->itemText(i).toStdString().c_str()))
            ui->comboBoxPoint1->setCurrentIndex(i);
    }
    for(i = 0; i < ui->comboBoxPoint2->count(); i++)
    {
        if(i_task2_index == atoi(ui->comboBoxPoint2->itemText(i).toStdString().c_str()))
            ui->comboBoxPoint2->setCurrentIndex(i);
    }
    ui->comboBoxPoint1Result->addItem(" ");
    ui->comboBoxPoint2Result->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    if(i_task1_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task1_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxPoint1Result->addItem(tr("点")+QString::number(i));
            }
        }
    }
    if(i_task2_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task2_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxPoint2Result->addItem(tr("点")+QString::number(i));
            }
        }
    }
    QPoint point;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task1_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxPoint1Result->setEnabled(false);
    }else
    {
        ui->comboBoxPoint1Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result1_index));
    }
    GetRefPara(i_task1_index ,i_result1_index,&point);
    ((FWP2PLineLabel*)m_label)->SetPoint1(point);
    Task_Step_Type_ID_Get(i_task2_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxPoint2Result->setEnabled(false);
    }else
    {
        ui->comboBoxPoint2Result->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result2_index));
    }
    GetRefPara(i_task2_index ,i_result2_index,&point);
    ((FWP2PLineLabel*)m_label)->SetPoint2(point);
}

void P2PLineWidget::Get_Result_From_Ram()
{
    ((FWP2PLineLabel*)m_label)->SetSet_Parameter_To_RamFlag(1);
}

/**
 * @brief P2PLineWidget::Point1TaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void P2PLineWidget::Point1TaskChangeSlot(int index)
{
    if(m_i_load_first == 1)
    {
        int task_index1 = atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
        if(task_index1 == 0)
        {
            ui->comboBoxPoint1Result->clear();
            return;
        }
        ui->comboBoxPoint1Result->setEnabled(true);

        ui->comboBoxPoint1Result->clear();
        ui->comboBoxPoint1Result->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index1 ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag ==1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index1,1,&i_mul_rst_cnt);
            ui->comboBoxPoint1Result->setEnabled(true);
            for(unsigned int i = 1; i<= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = tr("点")+QString::number(i);
                ui->comboBoxPoint1Result->addItem(strLineIndex);
            }
        }
        else
        {
            ui->comboBoxPoint1Result->setEnabled(false);
            QPoint point1;
            int i_result1_index = Get_Point_Or_Line_Result_Id(id,0);
            GetRefPara(task_index1 ,i_result1_index,&point1);
            ((FWP2PLineLabel*)m_label)->SetPoint1(point1);
        }
    }
}

/**
 * @brief P2PLineWidget::Point2TaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点2的关联任务发生改变时的处理
 */
void P2PLineWidget::Point2TaskChangeSlot(int index)
{
    ((FWP2PLineLabel*)m_label)->SetPoint2(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int task_index2 = atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
        if(task_index2 == 0)
        {
            ui->comboBoxPoint2Result->clear();
            return;
        }
        ui->comboBoxPoint2Result->setEnabled(true);

        ui->comboBoxPoint2Result->clear();
        ui->comboBoxPoint2Result->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(task_index2,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(task_index2,1,&i_mul_rst_cnt);
            ui->comboBoxPoint2Result->setEnabled(true);
            for(unsigned int i = 1; i <= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = "点"+QString::number(i);
                ui->comboBoxPoint2Result->addItem(strLineIndex);
            }
        }
        else
        {
            ui->comboBoxPoint2Result->setEnabled(false);
            QPoint point2;
            int i_result2_index = Get_Point_Or_Line_Result_Id(id,0);
            GetRefPara(task_index2,i_result2_index,&point2);
            ((FWP2PLineLabel*)m_label)->SetPoint2(point2);
        }
    }
}

/**
 * @brief P2PLineWidget::Point1ResultChangeSlot
 * @param index 下拉框索引
 * @author dgq
 * @note 引用结果发生改变时的处理
 */
void P2PLineWidget::Point1ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result1_index = ui->comboBoxPoint1Result->currentIndex();
        int Task_index1 = atoi(ui->comboBoxPoint1->currentText().toStdString().c_str());
        QPoint point1;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index1,&id);
        int result_index = Get_Point_Or_Line_Result_Id(id,Result1_index);
        GetRefPara(Task_index1,result_index,&point1);
        ((FWP2PLineLabel*)m_label)->SetPoint1(point1);

    }
}
void P2PLineWidget::Point2ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result2_index = ui->comboBoxPoint2Result->currentIndex();
        int Task_index2 = atoi(ui->comboBoxPoint2->currentText().toStdString().c_str());
        QPoint point2;
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index2,&id);
        int result_index = Get_Point_Or_Line_Result_Id(id,Result2_index);
        GetRefPara(Task_index2,result_index,&point2);
        ((FWP2PLineLabel*)m_label)->SetPoint2(point2);
    }
}

void P2PLineWidget::GetRefPara(int ref_step,int ref_result,QPoint *point)
{
    float point_pix_vga_x = 0.0;
    float point_pix_vga_y = 0.0;
    float point_pix_sub_x = 0.0;
    float point_pix_sub_y = 0.0;
    POINT_F pointf;
    int ret = measure_ref_point_result_get(ref_step,ref_result,&pointf,1);
    if(ret != 0)
    {
        qDebug()<<"measure_ref_point_result_get ret = "<<ret;
    }
    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    point->setX(point_pix_vga_x);
    point->setY(point_pix_vga_y);
}
QPoint P2PLineWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
