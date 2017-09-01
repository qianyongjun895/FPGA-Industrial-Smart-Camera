#include <QDebug>
#include "L2LDistanceWidget.h"
#include "ui_L2LDistanceWidget.h"
#include "FWL2LDistanceLabel.h"
#include <QMessageBox>
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"

L2LDistanceWidget::L2LDistanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::L2LDistanceWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    ui->MaxValidData->installEventFilter(this);
    ui->MinValidData->installEventFilter(this);
    m_label = new FWL2LDistanceLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->radioButton_pix->setChecked(true);
    CalcTimer = new QTimer;
    connect(ui->comboBoxLine1, SIGNAL(currentIndexChanged(int)), this, SLOT(Line1TaskChangeSlot(int)));
    connect(ui->comboBoxLine2, SIGNAL(currentIndexChanged(int)), this, SLOT(Line2TaskChangeSlot(int)));
    connect(ui->comboBoxLine1Result, SIGNAL(activated(int)), this, SLOT(Line1ResultChangeSlot(int)));
    connect(ui->comboBoxLine2Result, SIGNAL(activated(int)), this, SLOT(Line2ResultChangeSlot(int)));
    connect(CalcTimer, &QTimer::timeout, this, &L2LDistanceWidget::CalcTimerSlot);
}

/**
 * @brief L2LDistanceWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint L2LDistanceWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}
L2LDistanceWidget::~L2LDistanceWidget()
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
 * @brief L2LDistanceWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 取样
 */
int L2LDistanceWidget::Set_Parameter_To_Ram()
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
    SetRangetoLib();
    return 1;
}

/**
 * @brief L2LDistanceWidget::Init_Input_Ptr
 * @param ptr
 * @param i_step_index
 * @param new_flag
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void L2LDistanceWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWL2LDistanceLabel*)m_label)->SetPenColor(pen_color);
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
    ui->comboBoxLine1->addItem("");
    ui->comboBoxLine2->addItem("");
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
            }
        }
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }
    InitData(i_step_index);
    m_i_load_first = 1;
}

/**
 * @brief L2LDistanceWidget::InitLineCombobox
 * @param id
 * @return
 * @author dgq
 * @note 根据任务ID获取相应的点任务或线任务名称
 */
QString L2LDistanceWidget::InitLineCombobox(int TaskIndex, int id)
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

/**
 * @brief L2LDistanceWidget::InitData
 * @param i_step_index
 * @author dgq
 * @note 初始化界面显示
 */
void L2LDistanceWidget::InitData(int i_step_index)
{
    int i = 0;
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
    measure_ref_line_result_get(i_task1_index,i_result1_index,(void *)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWL2LDistanceLabel*)m_label)->SetLine1(line);

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
    ((FWL2LDistanceLabel*)m_label)->SetLine2(line);
    InitRangeData();
}

/**
 * @brief L2LDistanceWidget::InitRangeData
 * @author dgq
 * @note 初始化门限控件的显示
 */
void L2LDistanceWidget::InitRangeData()
{
    if(((L2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag == 0)
    {
        ui->radioButton_pix->setChecked(true);
        pix_phy_flag = 0;
    }else
    {
        ui->radioButton_phy->setChecked(true);
        pix_phy_flag = 1;
    }
    if(((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable == 0){
        ui->MinValidData->setText("---");
    }else{
        ui->MinValidData->setText(QString::number(((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_threshold));
    }

    if(((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable == 0){
        ui->MaxValidData->setText("---");
    }else{
        ui->MaxValidData->setText(QString::number(((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_threshold));
    }

}

/**
 * @brief L2LDistanceWidget::Line1TaskChangeSlot
 * @param index
 * @author dgq
 * @note 直线一任务下拉框改变时的响应函数
 */
void L2LDistanceWidget::Line1TaskChangeSlot(int index)
{
    ((FWL2LDistanceLabel*)m_label)->SetLine1(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine1Result,&line);
    ((FWL2LDistanceLabel*)m_label)->SetLine1(line);
}

/**
 * @brief L2LDistanceWidget::Line2TaskChangeSlot
 * @param index
 * @author dgq
 * @note 直线二任务下拉框改变时的响应函数
 */
void L2LDistanceWidget::Line2TaskChangeSlot(int index)
{
    ((FWL2LDistanceLabel*)m_label)->SetLine2(QLine(0,0,0,0));
    int task_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
    QLine line;
    LineResulChangetSlot(task_index,ui->comboBoxLine2Result,&line);
    ((FWL2LDistanceLabel*)m_label)->SetLine2(line);

}

/**
 * @brief L2LDistanceWidget::LineResulChangetSlot
 * @param task_index
 * @param mCom
 * @param line
 * @author dgq
 * @note 直线任务改变时的响应函数
 */
void L2LDistanceWidget::LineResulChangetSlot(int task_index,QComboBox *mCom,QLine *line)
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

/**
 * @brief L2LDistanceWidget::Line1ResultChangeSlot
 * @param index
 * @author dgq
 * @note 直线一的结果下拉框改变时的响应函数
 */
void L2LDistanceWidget::Line1ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine1->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine1Result->currentIndex();
        if(Result_index == 0)
        {
            ((FWL2LDistanceLabel*)m_label)->SetLine1(QLine(0,0,0,0));
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
        ((FWL2LDistanceLabel*)m_label)->SetLine1(line);
    }
}

/**
 * @brief L2LDistanceWidget::Line2ResultChangeSlot
 * @param index
 * @author dgq
 * @note 直线二结果下拉框改变时的响应函数
 */
void L2LDistanceWidget::Line2ResultChangeSlot(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLine2->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLine2Result->currentIndex();
        if(Result_index == 0)
        {
            ((FWL2LDistanceLabel*)m_label)->SetLine2(QLine(0,0,0,0));
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
        ((FWL2LDistanceLabel*)m_label)->SetLine2(line);
    }
}

/**
 * @brief L2LDistanceWidget::Line_Paint_Base_On_KB_SubPixel
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点的子函数
 */
int L2LDistanceWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
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
 * @brief L2LDistanceWidget::Line_Osd_Init
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点
 */
int L2LDistanceWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
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
 * @brief L2LDistanceWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void L2LDistanceWidget::LoadKeyBoardLib()
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
 * @brief L2LDistanceWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器，行文本编辑框模拟点击事件
 */
bool L2LDistanceWidget::eventFilter(QObject *watched, QEvent *event)
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

/**
 * @brief L2LDistanceWidget::on_radioButton_phy_clicked
 * @author dgq
 * @note 切换到物理数据
 */
void L2LDistanceWidget::on_radioButton_phy_clicked()
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

/**
 * @brief L2LDistanceWidget::on_radioButton_pix_clicked
 * @author dgq
 * @note 切换到像素数据
 */
void L2LDistanceWidget::on_radioButton_pix_clicked()
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

/**
 * @brief L2LDistanceWidget::SetRangetoLib
 * @return
 * @author dgq
 * @note 将门限数据写入内存
 */
int L2LDistanceWidget::SetRangetoLib()
{
    if(ui->radioButton_phy->isChecked())
    {
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 1;
    }
    else
    {
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->pix_phy_flag = 0;
    }
    if(ui->MaxValidData->text() == "---"){
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 0;
    }else{
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_enable = 1;
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.high_threshold = ui->MaxValidData->text().toFloat();
    }

    if(ui->MinValidData->text() == "---"){
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 0;
    }else{
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_enable = 1;
        ((L2L_DIST_INPUT_PARAM*)pInputPara)->valid_range.low_threshold = ui->MinValidData->text().toFloat();
    }
    return 0;
}

/**
 * @brief L2LDistanceWidget::on_btnCalculation_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void L2LDistanceWidget::on_btnCalculation_clicked()
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
 * @brief L2LDistanceWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程的定时器响应函数
 */
void L2LDistanceWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        Calc_rst_flag = 1;
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
 * @brief L2LDistanceWidget::Get_Result_From_Ram
 * @author dgq
 * @note 计算、取样成功后从内存中获取结果数据更新界面显示
 */
void L2LDistanceWidget::Get_Result_From_Ram()
{
    float i_range = 0.0;
    L2L_DIST_PRIVATE_PARAM *pPrivate = (L2L_DIST_PRIVATE_PARAM*)Task_Step_Private_Para_Get(m_step_index);
    if(ui->radioButton_phy->isChecked())
    {
        i_range = pPrivate->model_l2l_distance_result.phy_distance;
    }
    else
    {
        i_range = pPrivate->model_l2l_distance_result.distance;
    }
    ui->lineEdit_Dist->setText(QString::number(i_range));
    if(ui->checkBox_AutoSet->isChecked() && Calc_rst_flag == 1)
    {
        float iXMax ;
        float iXMin;
        iXMax = i_range*1.2;
        iXMin = i_range*0.8;
        ui->MaxValidData->setText(QString::number(iXMax));
        ui->MinValidData->setText(QString::number(iXMin));
    }
    QLine samp_line;
    int pix_vga_x = 0;
    int pix_vga_y = 0;
    float pix_sub_x = 0.0;
    float pix_sub_y = 0.0;
    pix_sub_x = pPrivate->model_l2l_distance_result.point1.x_f;
    pix_sub_y = pPrivate->model_l2l_distance_result.point1.y_f;
    PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    samp_line.setP1(QPoint(pix_vga_x,pix_vga_y));

    pix_sub_x = pPrivate->model_l2l_distance_result.point2.x_f;
    pix_sub_y = pPrivate->model_l2l_distance_result.point2.y_f;
    PixelCvt(&pix_sub_x,&pix_vga_x,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    PixelCvt(&pix_sub_y,&pix_vga_y,CVT_SUB2VGA|CVT_F2I|CVT_DATA);
    samp_line.setP2(QPoint(pix_vga_x,pix_vga_y));
    ((FWL2LDistanceLabel*)m_label)->SetLineSamp(samp_line);
}

/**
 * @brief L2LDistanceWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样、计算过程进度条的弹窗库
 */
void L2LDistanceWidget::LoadLearnLib()
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
