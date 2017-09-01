#include <QDebug>
#include "L2LAngleWidget.h"
#include "ui_L2LAngleWidget.h"
#include "TaskStepGlobal.h"
#include "FWL2LAngleLabel.h"
#include <QMessageBox>
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

L2LAngleWidget::L2LAngleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::L2LAngleWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    ui->MaxValidData->installEventFilter(this);
    ui->MinValidData->installEventFilter(this);
    ui->radioButtonAcuteAngel->setChecked(true);
    m_label = new FWL2LAngleLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;
    connect(ui->comboBoxLine1, SIGNAL(currentIndexChanged(int)), this, SLOT(Line1TaskChangeSlot(int)));
    connect(ui->comboBoxLine2, SIGNAL(currentIndexChanged(int)), this, SLOT(Line2TaskChangeSlot(int)));
    connect(ui->comboBoxLine1Result, SIGNAL(activated(int)), this, SLOT(Line1ResultChangeSlot(int)));
    connect(ui->comboBoxLine2Result, SIGNAL(activated(int)), this, SLOT(Line2ResultChangeSlot(int)));
    connect(CalcTimer, &QTimer::timeout, this, &L2LAngleWidget::CalcTimerSlot);


}

L2LAngleWidget::~L2LAngleWidget()
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
 * @brief L2LAngleWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint L2LAngleWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

/**
 * @brief L2LAngleWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int L2LAngleWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task1_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task1_index,&i_task_id);
    int i_result1_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLine1Result->currentIndex());
    int i_task2_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task2_index,&i_task_id);
    int i_result2_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLine2Result->currentIndex());

    if(i_task1_index == i_task2_index && i_result1_index == i_result2_index)
    {
        return 0;
    }
    pStephead->step_link.link_count = 2;
    pStephead->step_link.link_info[0].step_index = i_task1_index;
    pStephead->step_link.link_info[0].result_index = i_result1_index;
    pStephead->step_link.link_info[1].step_index = i_task2_index;
    pStephead->step_link.link_info[1].result_index = i_result2_index;
    if(pInputPara == NULL)
    {
        return 0;
    }
    if(ui->radioButtonAcuteAngel->isChecked())
        ((L2L_ANGLE_INPUT_PARAM *)pInputPara)->angle_type = ACUTE_ANGLE;
    if(ui->radioButtonObtuseAngle->isChecked())
        ((L2L_ANGLE_INPUT_PARAM *)pInputPara)->angle_type = OBTUSE_ANGLE;
    SetRangetoLib();
    return 1;
}

/**
 * @brief L2LAngleWidget::Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void L2LAngleWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
   ((FWL2LAngleLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
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
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->angle_type = ACUTE_ANGLE;
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;
}

/**
 * @brief L2LAngleWidget::InitLineCombobox
 * @param id
 * @return
 * @author dgq
 * @note 根据任务Id获取对应任务的中文字名称
 */
QString L2LAngleWidget::InitLineCombobox(int TaskIndex, int id)
{
    QString name = QString::null;

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


/**
 * @brief L2LAngleWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化函数
 */
void L2LAngleWidget::InitData(int i_step_index)
{
    m_i_load_first = 0;
    unsigned int i_task_id = 0;
    int i = 0;
    ui->comboBoxLine1->addItem("");
    ui->comboBoxLine2->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitLineCombobox(i+1, i_task_id);
            if(!name.isEmpty())
            {
                ui->comboBoxLine1->addItem(QString::number(i+1)+"."+name);
                ui->comboBoxLine2->addItem(QString::number(i+1)+"."+name);
            }
        }
    }
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task1_index = pStephead->step_link.link_info[0].step_index;
    int i_result1_index = pStephead->step_link.link_info[0].result_index;
    int i_task2_index = pStephead->step_link.link_info[1].step_index;
    int i_result2_index = pStephead->step_link.link_info[1].result_index;

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

    ui->comboBoxLine1Result->addItem(" ");
    ui->comboBoxLine2Result->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;
    if(i_task1_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task1_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
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
            for(unsigned int i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLine2Result->addItem(tr("直线")+QString::number(i));
            }
        }
    }
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
    measure_ref_line_result_get(i_task2_index,i_result1_index,(void *)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWL2LAngleLabel*)m_label)->SetLine1(line);

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
    ((FWL2LAngleLabel*)m_label)->SetLine2(line);

    if(((L2L_ANGLE_INPUT_PARAM *)pInputPara)->angle_type == ACUTE_ANGLE)
    {
        m_angle_flag = 0;
        ui->radioButtonAcuteAngel->setChecked(true);
    }
    if(((L2L_ANGLE_INPUT_PARAM *)pInputPara)->angle_type == OBTUSE_ANGLE)
    {
        m_angle_flag = 1;
        ui->radioButtonObtuseAngle->setChecked(true);
    }
    InitRangeData();

}

/**
 * @brief L2LAngleWidget::InitRangeData
 * @author dgq
 * @note 初始化门限控件的显示
 */
void L2LAngleWidget::InitRangeData()
{
    if(((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.low_enable == 0){
        ui->MinValidData->setText("---");
    }else{
        ui->MinValidData->setText(QString::number(((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.low_threshold));
    }

    if(((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.high_enable == 0){
        ui->MaxValidData->setText("---");
    }else{
        ui->MaxValidData->setText(QString::number(((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.high_threshold));
    }
}

/**
 * @brief L2LAngleWidget::Line1TaskChangeSlot
 * @param index
 * @author dgq
 * @note 直线1的任务选择下拉框槽函数
 */
void L2LAngleWidget::Line1TaskChangeSlot(int index)
{
    ((FWL2LAngleLabel*)m_label)->SetLine1(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine1Result,&line);
    ((FWL2LAngleLabel*)m_label)->SetLine1(line);
}

/**
 * @brief L2LAngleWidget::Line2TaskChangeSlot
 * @param index
 * @author dgq
 * @note 直线2的任务选择下拉框槽函数
 */
void L2LAngleWidget::Line2TaskChangeSlot(int index)
{
    ((FWL2LAngleLabel*)m_label)->SetLine2(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine2Result,&line);
    ((FWL2LAngleLabel*)m_label)->SetLine2(line);
}

/**
 * @brief L2LAngleWidget::LineResulChangetSlot
 * @param task_index
 * @param mCom
 * @param line
 * @author dgq
 * @note 直线任务改变时的响应函数
 */
void L2LAngleWidget::LineResulChangetSlot(int task_index,QComboBox *mCom,QLine *line)
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
//        qDebug()<<"task id = "<<id;
//        qDebug()<<"Mul_Flag = "<<Mul_Flag;
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
/**
 * @brief L2LAngleWidget::Line1ResultChangeSlot
 * @param index
 * @author dgq
 * @note 直线1的结果选择下拉框槽函数
 */
void L2LAngleWidget::Line1ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine1Result->currentIndex();
        if(Result_index == 0)
        {
            ((FWL2LAngleLabel*)m_label)->SetLine1(QLine(0,0,0,0));
            return;
        }
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
            QMessageBox::about(this,tr(""),info);
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWL2LAngleLabel*)m_label)->SetLine1(line);
    }
}

/**
 * @brief L2LAngleWidget::Line2ResultChangeSlot
 * @param index
 * @author dgq
 * @note 直线2的结果选择下拉框槽函数
 */
void L2LAngleWidget::Line2ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine2Result->currentIndex();
        if(Result_index == 0)
        {
            ((FWL2LAngleLabel*)m_label)->SetLine2(QLine(0,0,0,0));
            return;
        }
        unsigned int id;
        Task_Step_Type_ID_Get(Task_index,&id);
        int ret = measure_ref_line_result_get(Task_index,Get_Point_Or_Line_Result_Id(id,Result_index),(void*)&pLinePara,1);
        if(ret != 0)
        {
            QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
            QMessageBox::about(this,tr(""),info);
            return;
        }
        QLine line;
        Line_Osd_Init(&pLinePara,&line);
        ((FWL2LAngleLabel*)m_label)->SetLine2(line);
    }
}

/**
 * @brief L2LAngleWidget::Line_Paint_Base_On_KB_SubPixel
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点的子函数
 */
int L2LAngleWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
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

/**
 * @brief L2LAngleWidget::Line_Osd_Init
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点
 */
int L2LAngleWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
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

/**
 * @brief L2LAngleWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void L2LAngleWidget::LoadKeyBoardLib()
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

/**
 * @brief L2LAngleWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器，行文本编辑框模拟点击事件
 */
bool L2LAngleWidget::eventFilter(QObject *watched, QEvent *event)
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

                        if(ui->radioButtonAcuteAngel->isChecked())
                        {
                            int imax = GetRangeNum().toInt();
                            if(imax > 90)
                            {
                                imax = 90;
                                ((QLineEdit *)watched)->setText("90");
                            }else
                            {
                                ((QLineEdit *)watched)->setText(GetRangeNum());
                            }
                        }
                        else
                        {
                            int imin = GetRangeNum().toInt();
                            if(imin < 90)
                            {
                                imin = 90;
                                ((QLineEdit *)watched)->setText("90");
                            }else
                            {
                                ((QLineEdit *)watched)->setText(GetRangeNum());
                            }
                        }
                    }
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief L2LAngleWidget::SetRangetoLib
 * @return
 * @author dgq
 * @note 将界面的参数写入内存
 */
int L2LAngleWidget::SetRangetoLib()
{
    if(ui->MaxValidData->text() == "---"){
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
    }else{
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 1;
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.high_threshold = ui->MaxValidData->text().toFloat();
    }

    if(ui->MinValidData->text() == "---"){
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }else{
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 1;
        ((L2L_ANGLE_INPUT_PARAM*)pInputPara)->valid_range.low_threshold = ui->MinValidData->text().toFloat();
    }
    return 0;
}

/**
 * @brief L2LAngleWidget::on_btnCalculation_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void L2LAngleWidget::on_btnCalculation_clicked()
{
    int ret = Set_Parameter_To_Ram();
    if(ret == 0)
    {
        QMessageBox::about(this,tr("警告"),tr("参数有误，请仔细检查并修改无误后重试！"));
        return;
    }
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief L2LAngleWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程定时器响应函数
 */
void L2LAngleWidget::CalcTimerSlot()
{
    Calc_rst_flag = 1;
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
    Calc_rst_flag = 0;
    CalcTimer->stop();
}

/**
 * @brief L2LAngleWidget::Get_Result_From_Ram
 * @author dgq
 * @note 从内存中获取计算结果更新界面显示
 */
void L2LAngleWidget::Get_Result_From_Ram()
{
    double i_range = 0.0;
    void *pPrivate = NULL;
    pPrivate = Task_Step_Private_Para_Get(m_step_index);
    i_range = ((L2L_ANGLE_PRIVATE_PARAM *)pPrivate)->model_l2l_angle_result.angle;
    ui->lineEdit_Dist->setText(QString::number(i_range));
    if(ui->checkBox_AutoSet->isChecked() && Calc_rst_flag == 1)
    {
        double iXMax ;
        double iXMin;
        iXMax = i_range*1.2;
        iXMin = i_range*0.8;
        if(ui->radioButtonAcuteAngel->isChecked())
        {
            if(iXMax > 90)
                iXMax = 90;
        }else
        {
            if(iXMin < 90)
                iXMin = 90;
        }
        ui->MaxValidData->setText(QString::number(iXMax));
        ui->MinValidData->setText(QString::number(iXMin));
    }
    GetMesureOsdData(m_step_index,&((L2L_ANGLE_PRIVATE_PARAM *)pPrivate)->model_l2l_angle_result);
    ((FWL2LAngleLabel*)m_label)->SetArcData(m_arc);
}

/**
 * @brief L2LAngleWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样精度条弹窗库
 */
void L2LAngleWidget::LoadLearnLib()
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

/**
 * @brief L2LAngleWidget::on_radioButtonAcuteAngel_clicked
 * @author dgq
 * @note 切换到锐角
 */
void L2LAngleWidget::on_radioButtonAcuteAngel_clicked()
{
    if(m_angle_flag == 1)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空范围数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButtonObtuseAngle->setChecked(true);
            return;
        }
        m_angle_flag = 0;
        ui->lineEdit_Dist->setText("");
        ui->lineEdit_Dist->setText("");
        ui->MaxValidData->setText("---");
        ui->MinValidData->setText("---");
    }
}

/**
 * @brief L2LAngleWidget::on_radioButtonObtuseAngle_clicked
 * @author dgq
 * @note 切换到钝角
 */
void L2LAngleWidget::on_radioButtonObtuseAngle_clicked()
{
    qDebug()<<"m_angle_flag =="<<m_angle_flag;
    if(m_angle_flag == 0)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空范围数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            ui->radioButtonAcuteAngel->setChecked(true);
            return;
        }
        m_angle_flag = 1;
        ui->lineEdit_Dist->setText("");
        ui->lineEdit_Dist->setText("");
        ui->MaxValidData->setText("---");
        ui->MinValidData->setText("---");
    }
}


/**
 * @brief L2LAngleWidget::GetMesureOsdData
 * @param i_step
 * @param rst
 * @author dgq
 * @note 获取osd显示数据
 */
void L2LAngleWidget::GetMesureOsdData(int i_step,L2L_ANGLE_RESULT *rst)
{
    int pix_vga_x = 0;
    int pix_vga_y = 0;
    float pix_sub_x = rst->cross_point.x_f;
    float pix_sub_y = rst->cross_point.y_f;
    PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    m_arc.r = 20;
    m_arc.x = pix_vga_x;
    m_arc.y = pix_vga_y;
    LineParameter pLine1Para;
    LineParameter pLine2Para;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step);
    int i_task1_index = (int)pStephead->step_link.link_info[0].step_index;
    int i_result1_index = (int)pStephead->step_link.link_info[0].result_index;
    int i_task2_index =(int) pStephead->step_link.link_info[1].step_index;
    int i_result2_index = (int)pStephead->step_link.link_info[1].result_index;

    int ret = measure_ref_line_result_get(i_task1_index,i_result1_index,(void*)&pLine1Para,0);
    if(ret != 0)
    {
        return;
    }
    ret = measure_ref_line_result_get(i_task2_index,i_result2_index,(void*)&pLine2Para,0);
    if(ret != 0)
    {
        return;
    }
    ArcAngleGet(&m_arc,&pLine1Para,&pLine2Para,rst);
}

/**
 * @brief L2LAngleWidget::ArcAngleGet
 * @param arc
 * @param pLine1Param
 * @param pLine2Param
 * @param pAngleCalcRst
 * @return
 * @author dgq
 * @note 计算圆弧
 */
int L2LAngleWidget::ArcAngleGet(pOSD_ARC arc, LineParameter *pLine1Param, LineParameter *pLine2Param, L2L_ANGLE_RESULT * pAngleCalcRst)
{
    double rad1=0, rad2=0, ang1=0, ang2=0, temp=0;
    double line1_x=0, line1_y=0, line2_x=0, line2_y=0, x=0, y=0;

    if(pLine1Param == NULL || pLine2Param == NULL || pAngleCalcRst == NULL)
    {
        return -1;
    }

    /*线1的中点*/
    line1_x = pLine1Param->x;
    line1_y = pLine1Param->y;

    /*线2的中点*/
    line2_x = pLine2Param->x;
    line2_y = pLine2Param->y;

    /*两线的交点*/
    x=(double)pAngleCalcRst->cross_point.x_f;
    y=(double)pAngleCalcRst->cross_point.y_f;

    /*两线的斜率*/
    rad1=tan(pLine1Param->theta);
    rad2=tan(pLine2Param->theta);

    /*两线斜率的角度*/
    ang1=atan(rad1)*180/M_PI ;
    ang2=atan(rad2)*180/M_PI ;

    /*线1逆时针与x轴的夹角*/
    if((line1_x >= x) && (line1_y >= y))
    {
        ang1=360-ang1;
    }
    else if((line1_x < x) && (line1_y < y))
    {
        ang1=180-ang1;
    }
    else if((line1_x >= x) && (line1_y <= y))
    {
        ang1=-ang1;
    }
    else if((line1_x < x) && (line1_y >y))
    {
        ang1=180-ang1;
    }

    /*线2逆时针与x轴的夹角*/
    if((line2_x >= x) && (line2_y >= y))
    {
        ang2=360-ang2;
    }
    else if((line2_x < x) && (line2_y < y))
    {
        ang2=180-ang2;
    }
    else if((line2_x >= x) && (line2_y <= y))
    {
        ang2=-ang2;
    }
    else if((line2_x < x) && (line2_y >y))
    {
        ang2=180-ang2;
    }

    /*两线的夹角*/
    arc->angStart = (ang1 < ang2 ? ang1 : ang2);
    arc->angEnd = fabs(ang1 - ang2);

    if(arc->angEnd>180)
    {
        arc->angStart=(ang1 > ang2 ? ang1 : ang2);
        arc->angEnd=360 - arc->angEnd;
     }

    if((pAngleCalcRst->angle > 90 && arc->angEnd < 90) || (pAngleCalcRst->angle < 90 && arc->angEnd > 90))
    {
        arc->r=20;
        arc->angStart=arc->angStart+arc->angEnd;
        arc->angEnd=pAngleCalcRst->angle;
    }
    return 0;
}
