#include <QDebug>
#include "P2LDistanceWidget.h"
#include "ui_P2LDistanceWidget.h"
#include "FWP2LDistanceLabel.h"
#include <QMessageBox>
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

P2LDistanceWidget::P2LDistanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::P2LDistanceWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    ui->MaxValidData->installEventFilter(this);
    ui->MinValidData->installEventFilter(this);
    m_label = new FWP2LDistanceLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;

    ui->radioButton_pix->setChecked(true);
    connect(ui->comboBoxDot, SIGNAL(currentIndexChanged(int)), this, SLOT(PointTaskChangeSlot(int)));
    connect(ui->comboBoxLine, SIGNAL(currentIndexChanged(int)), this, SLOT(LineTaskChangeSlot(int)));
    connect(ui->comboBoxDotResult, SIGNAL(activated(int)), this, SLOT(PointResultChangeSlot(int)));
    connect(ui->comboBoxLineResult, SIGNAL(activated(int)), this, SLOT(LineResultChangeSlot(int)));
    connect(CalcTimer, &QTimer::timeout, this, &P2LDistanceWidget::CalcTimerSlot);
}

P2LDistanceWidget::~P2LDistanceWidget()
{
    ui->MaxValidData->removeEventFilter(this);
    ui->MinValidData->removeEventFilter(this);
    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}

/**
 * @brief P2LDistanceWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int P2LDistanceWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index = atoi(ui->comboBoxDot->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxDotResult->currentIndex());

    int i_task2_index = atoi(ui->comboBoxLine->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task2_index,&i_task_id);
    int i_result2_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLineResult->currentIndex());
    pStephead->step_link.link_count = 2;
    pStephead->step_link.link_info[0].step_index = i_task1_index;
    pStephead->step_link.link_info[0].result_index = i_result1_index;
    pStephead->step_link.link_info[1].step_index = i_task2_index;
    pStephead->step_link.link_info[1].result_index = i_result2_index;

    SetRangetoLib();
    return 1;

}

/**
 * @brief P2LDistanceWidget::Init_Input_Ptr
 * @param ptr 输入结构体内存指针
 * @param i_step_index 任务步骤号
 * @param new_flag 新加任务标志 1 新加 0 编辑
 * @author dgq
 * @note 初始化Input结构体指针
 */
void P2LDistanceWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWP2LDistanceLabel*)m_label)->SetPenColor(pen_color);
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
    ui->comboBoxDot->addItem("");
    ui->comboBoxLine->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitPointCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->comboBoxDot->addItem(QString::number(i+1)+"."+name);
            name = InitLineCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->comboBoxLine->addItem(QString::number(i+1)+"."+name);
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
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;

}
//Task_Step_TypeID_Get_By_Index

QString P2LDistanceWidget::InitPointCombobox(int TaskIndex, int id)
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
QString P2LDistanceWidget::InitLineCombobox(int TaskIndex, int id)
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
 * @brief P2LDistanceWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化
 */
void P2LDistanceWidget::InitData(int i_step_index)
{
//    int i_task_count = GetTaskStepCount();
    int i = 0;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task1_index = pStephead->step_link.link_info[0].step_index;
    int i_result1_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = pStephead->step_link.link_info[1].step_index;
    int i_result2_index = pStephead->step_link.link_info[1].result_index;
    for(i = 0; i < ui->comboBoxDot->count(); i++)
    {
        if(i_task1_index == atoi(ui->comboBoxDot->itemText(i).toStdString().c_str()))
            ui->comboBoxDot->setCurrentIndex(i);
    }
    for(i = 0; i < ui->comboBoxLine->count(); i++)
    {
        if(i_task2_index == atoi(ui->comboBoxLine->itemText(i).toStdString().c_str()))
            ui->comboBoxLine->setCurrentIndex(i);
    }
//    ui->comboBoxLine->setCurrentIndex(i_task2_index);
    ui->comboBoxDotResult->addItem(" ");
    ui->comboBoxLineResult->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    if(i_task1_index > 0 )
    {
        int ret = TaskMultiRstNumGet(i_task1_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxDotResult->addItem(tr("点")+QString::number(i));
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
                ui->comboBoxLineResult->addItem(tr("直线")+QString::number(i));
            }
        }
    }
    QPoint point;
    LineParameter pLinePara;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task1_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxDotResult->setEnabled(false);
    }else
    {
        ui->comboBoxDotResult->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result1_index));
    }
    GetRefPara(i_task1_index,i_result1_index,&point);
    ((FWP2LDistanceLabel*)m_label)->SetPoint(point);

    Task_Step_Type_ID_Get(i_task2_index,&id);
    Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxLineResult->setEnabled(false);
    }else
    {
        ui->comboBoxLineResult->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result2_index));
    }
    measure_ref_line_result_get(i_task2_index,i_result2_index,(void*)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWP2LDistanceLabel*)m_label)->SetLine(line);
    InitRangeData();
}

void P2LDistanceWidget::InitRangeData()
{
    if(((P2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag == 0)
    {
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
    }else
    {
        ui->radioButton_phy->setChecked(true);
        pix_phy_flag = 1;
    }
    if(((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable == 0){
        ui->MinValidData->setText("---");
    }else{
        ui->MinValidData->setText(QString::number(((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_threshold));
    }

    if(((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable == 0){
        ui->MaxValidData->setText("---");
    }else{
        ui->MaxValidData->setText(QString::number(((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_threshold));
    }

}

/**
 * @brief P2LDistanceWidget::PointTaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void P2LDistanceWidget::PointTaskChangeSlot(int index)
{
    ((FWP2LDistanceLabel*)m_label)->SetPoint(QPoint(-20,-20));
    if(m_i_load_first == 1)
    {
        int point_id = atoi(ui->comboBoxDot->currentText().toStdString().c_str());
        if(point_id == 0)
        {
            ui->comboBoxDotResult->clear();
            return;
        }
        ui->comboBoxDotResult->setEnabled(true);

        ui->comboBoxDotResult->clear();
        ui->comboBoxDotResult->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(point_id ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(point_id,1,&i_mul_rst_cnt);
            for(unsigned int i = 1; i<= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = tr("点")+QString::number(i);
                ui->comboBoxDotResult->addItem(strLineIndex);
            }
        }
        else
        {
            ui->comboBoxDotResult->setEnabled(false);
            QPoint point1;
            int i_result1_index = Get_Point_Or_Line_Result_Id(id,0);
            GetRefPara(point_id,i_result1_index,&point1);
            ((FWP2LDistanceLabel*)m_label)->SetPoint(point1);
        }

    }
}

/**
 * @brief P2LDistanceWidget::LineTaskChangeSlot
 * @param index 下拉框的当前索引
 * @author dgq
 * @note 点1的关联任务发生改变时的处理
 */
void P2LDistanceWidget::LineTaskChangeSlot(int index)
{
    ((FWP2LDistanceLabel*)m_label)->SetLine(QLine(0,0,0,0));
    if(m_i_load_first == 1)
    {
        int line_id = atoi(ui->comboBoxLine->currentText().toStdString().c_str());
        if(line_id == 0)
        {
            ui->comboBoxLineResult->clear();
            return;
        }
        ui->comboBoxLineResult->setEnabled(true);

        ui->comboBoxLineResult->clear();
        ui->comboBoxLineResult->addItem(" ");
        unsigned int id;
        Task_Step_Type_ID_Get(line_id ,&id);
        int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
        if(Mul_Flag == 1)
        {
            unsigned int i_mul_rst_cnt = 0;
            TaskMultiRstNumGet(line_id,1,&i_mul_rst_cnt);
            for(unsigned int i = 1; i <= i_mul_rst_cnt;i++)
            {
                QString strLineIndex;
                strLineIndex = "直线"+QString::number(i);
                ui->comboBoxLineResult->addItem(strLineIndex);
            }
        }
        else
        {
            LineParameter pLinePara;
            ui->comboBoxLineResult->setEnabled(false);

            int i_result_index = Get_Point_Or_Line_Result_Id(id,0);
            int ret = measure_ref_line_result_get(line_id,i_result_index,(void*)&pLinePara,1);
            if(ret != 0)
            {
                QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
                QMessageBox::about(this,tr(""),info);
                return;
            }
            QLine line;
            Line_Osd_Init(&pLinePara,&line);
            ((FWP2LDistanceLabel*)m_label)->SetLine(line);
        }

    }
}

/**
 * @brief P2LDistanceWidget::PointResultChangeSlot
 * @param index 下拉框索引
 * @author dgq
 * @note 引用结果发生改变时的处理
 */
void P2LDistanceWidget::PointResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        int Result1_index = ui->comboBoxDotResult->currentIndex();
        int Task_index1 = atoi(ui->comboBoxDot->currentText().toStdString().c_str());

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
        ((FWP2LDistanceLabel*)m_label)->SetPoint(point);
#endif


    }
}

void P2LDistanceWidget::LineResultChangeSlot(int index)
{

    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index2 = atoi(ui->comboBoxLine->currentText().toStdString().c_str());
        int Result2_index = ui->comboBoxLineResult->currentIndex();
        if(Result2_index == 0)
        {
            ((FWP2LDistanceLabel*)m_label)->SetLine(QLine(0,0,0,0));
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
        ((FWP2LDistanceLabel*)m_label)->SetLine(line);
    }
}


int P2LDistanceWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
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

int P2LDistanceWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
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


void P2LDistanceWidget::GetRefPara(int ref_step,int ref_result,QPoint *point)
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
QPoint P2LDistanceWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

void P2LDistanceWidget::LoadKeyBoardLib()
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


bool P2LDistanceWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->MaxValidData || watched == ui->MinValidData)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指点击事件)
        {
            QDialog *dlg;
            Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
            if(GetNumKeyBoardDlg)
            {
                dlg = GetNumKeyBoardDlg();
                Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
                if(SetRangeInput)
                {
                    if(watched == ui->MaxValidData)
                    {
                        if(ui->MaxValidData->text() != "---"){
                            SetRangeInput(ui->MaxValidData->text(),ui->MinValidData->text(),1);
                        }else{
                            SetRangeInput(ui->lineEdit_Dist->text(),ui->MinValidData->text(),1);
                        }
                    }
                    if(watched == ui->MinValidData)
                    {
                        if(ui->MinValidData->text() != "---"){
                            SetRangeInput(ui->MaxValidData->text(),ui->MinValidData->text(),0);
                        }else{
                            SetRangeInput(ui->MaxValidData->text(),ui->lineEdit_Dist->text(),0);
                        }
                    }
                    int ret = dlg->exec();
                    if(ret == QDialog::Accepted)
                    {
                        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
                        if(GetRangeNum)
                        {
                            ((QLineEdit *)watched)->setText(GetRangeNum());
                        }
                    }
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void P2LDistanceWidget::on_radioButton_phy_clicked()
{
    unsigned int i_caliPara;
    Task_Step_Scale_Cali_Param_Index_Get(m_step_index,&i_caliPara);
    if(i_caliPara == 0)
    {
        QMessageBox::about(this,tr("提示"),tr("本步骤没有关联刻度校准参数，无法切换到物理值"));
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
        return;
    }
    else if(pix_phy_flag == 0)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空范围数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_pix->setChecked(true);
            return;
        }
        pix_phy_flag = 1;
        ui->lineEdit_Dist->setText("");
        ui->MaxValidData->setText("---");
        ui->MinValidData->setText("---");
    }

}

void P2LDistanceWidget::on_radioButton_pix_clicked()
{
    if(pix_phy_flag == 1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空范围数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButton_phy->setChecked(true);
            return;
        }
        pix_phy_flag = 0;
        ui->lineEdit_Dist->setText("");
        ui->MaxValidData->setText("---");
        ui->MinValidData->setText("---");
    }
}


int P2LDistanceWidget::SetRangetoLib()
{
    if(ui->radioButton_phy->isChecked())
    {
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 1;
    }
    else
    {
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
    }
    if(ui->MaxValidData->text() == "---"){
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
    }else{
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 1;
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_threshold = ui->MaxValidData->text().toFloat();
    }

    if(ui->MinValidData->text() == "---"){
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }else{
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 1;
        ((P2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_threshold = ui->MinValidData->text().toFloat();
    }
    return 0;
}


void P2LDistanceWidget::on_btnCalculation_clicked()
{
    Set_Parameter_To_Ram();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}
void P2LDistanceWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        Get_Result_From_Ram();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

void P2LDistanceWidget::Get_Result_From_Ram()
{
    float i_range = 0.0;
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    if(ui->radioButton_phy->isChecked())
    {
        i_range = ((P2L_DIST_PRIVATE_PARAM *)pPrivate)->model_p2l_dist_result.phy_distance;
    }
    else
    {
        i_range = ((P2L_DIST_PRIVATE_PARAM *)pPrivate)->model_p2l_dist_result.distance;
    }
    ui->lineEdit_Dist->setText(QString::number(i_range));
    if(ui->checkBox_AutoSet->isChecked())
    {
        float iXMax ;
        float iXMin;
        iXMax = i_range*1.2;
        iXMin = i_range*0.8;
        ui->MaxValidData->setText(QString::number(iXMax));
        ui->MinValidData->setText(QString::number(iXMin));

    }
    int pix_vga_x = 0;
    int pix_vga_y = 0;
    float pix_sub_x = ((P2L_DIST_PRIVATE_PARAM *)pPrivate)->model_p2l_dist_result.stroke_point.x_f;
    float pix_sub_y = ((P2L_DIST_PRIVATE_PARAM *)pPrivate)->model_p2l_dist_result.stroke_point.y_f;
    PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);

    ((FWP2LDistanceLabel*)m_label)->SetVPoint(QPoint(pix_vga_x,pix_vga_y));

}

void P2LDistanceWidget::LoadLearnLib()
{
    m_Learn_Lib.setFileName("libLearningDialog.so");
    if(m_Learn_Lib.isLoaded())
    {
        qDebug()<<"load libLearningDialog.so isLoaded";
        return;
    }
    if(m_Learn_Lib.load())
    {
        printf("libLearningDialog.so OK\n");
    }
    else
    {
        qDebug()<<"load libLearningDialog.so fail"<<m_Learn_Lib.errorString();
    }
}
