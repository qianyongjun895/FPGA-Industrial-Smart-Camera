#include <QDebug>
#include <QMessageBox>
#include "LineFlawWidget.h"
#include "ui_LineFlawWidget.h"
#include "stdio.h"
#include "FWLineFlawLabel.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"


LineFlawWidget::LineFlawWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineFlawWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();

    m_label = new FWLineFlawLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->stackedWidget->setCurrentIndex(0);
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
    ui->tableWidget_CalcResult->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_i_load_first  = 0;
    ui->tabWidgetPara->setCurrentIndex(0);


    ui->checkBoxAuto->setChecked(true);
    ui->comboBoxDir->addItem(tr("X正方向"));
    ui->comboBoxDir->addItem(tr("X负方向"));
    ui->comboBoxDir->addItem(tr("Y正方向"));
    ui->comboBoxDir->addItem(tr("Y负方向"));
    ui->comboBoxDir->setCurrentIndex(0);
    ui->comboBoxTestType->addItem(tr("正缺陷"));
    ui->comboBoxTestType->addItem(tr("负缺陷"));
    ui->comboBoxTestType->addItem(tr("正负缺陷"));
    ui->comboBoxTestType->setCurrentIndex(0);

    RegisterEventFilter();
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &LineFlawWidget::CalcTimerSlot);
}


LineFlawWidget::~LineFlawWidget()
{
    disconnect(this,0,0,0);
    UnRegisterEventFilter();

    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}


/**
 * @brief LineFlawWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint LineFlawWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

/**
 * @brief LineFlawWidget::
 * @author dgq
 * @note 将界面参数写入内存
 */
int LineFlawWidget::Set_Parameter_To_Ram()
{
    unsigned int i_task_id;
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(m_step_index);
    int i_task_index = atoi(ui->comboBoxLineStep->currentText().toStdString().c_str());
    Task_Step_Type_ID_Get(i_task_index,&i_task_id);
    int i_result_index = Get_Point_Or_Line_Result_Id(i_task_id,ui->comboBoxLineIndex->currentIndex());
    pStephead->step_link.link_count = 1;
    pStephead->step_link.link_info[0].step_index = i_task_index;
    pStephead->step_link.link_info[0].result_index = i_result_index;

    SetDataToLib();
    return 1;
}

/**
 * @brief LineFlawWidget::Init_Input_Ptr
 * @param ptr
 * @param i_step_index
 * @param new_flag
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void LineFlawWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWLineFlawLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (LINE_FLAW_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }

    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->flaw_check_dir = 0;
        pInputPara->flaw_check_type = 0;
        pInputPara->flaw_num_max = 50;
        pInputPara->flaw_level_low_th = 0;
        pInputPara->flaw_length_low_th = 1;
        pInputPara->flaw_area_low_th = 3;
        pInputPara->flaw_level_threshold.high_enable = 0;
        pInputPara->flaw_level_threshold.low_enable = 0;
        pInputPara->flaw_length_total_threshold.high_enable = 0;
        pInputPara->flaw_length_total_threshold.low_enable = 0;
        pInputPara->flaw_area_total_threshold.high_enable = 0;
        pInputPara->flaw_area_total_threshold.low_enable = 0;
        pInputPara->flaw_count_threshold.high_enable = 0;
        pInputPara->flaw_count_threshold.low_enable = 0;
    }
    InitComboBox(i_step_index);
    InitData();
}

/**
 * @brief LineFlawWidget::InitLineCombobox
 * @param id
 * @return
 * @author dgq
 * @note 根据任务ID获取相应的点任务或线任务名称
 */
QString LineFlawWidget::InitLineCombobox(int TaskIndex, int id)
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
 * @brief LineFlawWidget::RegisterEventFilter
 * @author vincent
 * @note 文本编辑框注册事件过滤器
 */
void LineFlawWidget::RegisterEventFilter()
{
    ui->txtLineFlawArea->installEventFilter(this);
    ui->txtLineLength->installEventFilter(this);
    ui->txtLineNum->installEventFilter(this);
    ui->txtLineStrength->installEventFilter(this);

    ui->txtFlawAreaHigh->installEventFilter(this);
    ui->txtFlawAreaLow->installEventFilter(this);
    ui->txtFlawLengthHigth->installEventFilter(this);
    ui->txtFlawLengthLow->installEventFilter(this);
    ui->txtFlawLevelHigh->installEventFilter(this);
    ui->txtFlawLevelLow->installEventFilter(this);
    ui->txtFlawNumHigh->installEventFilter(this);
    ui->txtFlawNumLow->installEventFilter(this);
}
/**
 * @brief LineFlawWidget::UnRegisterEventFilter
 * @author vincent
 * @note 文本编辑框注销事件过滤器
 */
void LineFlawWidget::UnRegisterEventFilter()
{
    ui->txtLineFlawArea->removeEventFilter(this);
    ui->txtLineLength->removeEventFilter(this);
    ui->txtLineNum->removeEventFilter(this);
    ui->txtLineStrength->removeEventFilter(this);

    ui->txtFlawAreaHigh->removeEventFilter(this);
    ui->txtFlawAreaLow->removeEventFilter(this);
    ui->txtFlawLengthHigth->removeEventFilter(this);
    ui->txtFlawLengthLow->removeEventFilter(this);
    ui->txtFlawLevelHigh->removeEventFilter(this);
    ui->txtFlawLevelLow->removeEventFilter(this);
    ui->txtFlawNumHigh->removeEventFilter(this);
    ui->txtFlawNumLow->removeEventFilter(this);

}

/**
 * @brief LineFlawWidget::InitComboBox
 * @param i_step_index
 * @author dgq
 * @note 初始化下拉框的显示
 */
void LineFlawWidget::InitComboBox(int i_step_index)
{
    m_i_load_first = 0;
    unsigned int i_task_id = 0;
    int i = 0;
    ui->comboBoxLineStep->addItem("");
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitLineCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->comboBoxLineStep->addItem(QString::number(i+1)+"."+name);
        }
    }
    TASK_STEP_HEADER *pStephead = Task_Step_Head_Get(i_step_index);
    int i_task_index = pStephead->step_link.link_info[0].step_index;
    int i_result_index = pStephead->step_link.link_info[0].result_index;
    for(i = 0; i < ui->comboBoxLineStep->count(); i++)
    {
        if(i_task_index == atoi(ui->comboBoxLineStep->itemText(i).toStdString().c_str()))
            ui->comboBoxLineStep->setCurrentIndex(i);
    }
    ui->comboBoxLineIndex->addItem(" ");
    unsigned int i_mul_rst_cnt = 0;

    if(i_task_index > 0)
    {
        int ret = TaskMultiRstNumGet(i_task_index,1,&i_mul_rst_cnt);
        if(ret == 0)
        {
            for(i = 1; i < i_mul_rst_cnt+1; i++)
            {
                ui->comboBoxLineIndex->addItem(tr("直线")+QString::number(i));
            }
        }
    }
    LineParameter pLinePara;
    unsigned int id;
    Task_Step_Type_ID_Get(i_task_index,&id);
    int  Mul_Flag = Get_Multi_Result_Task_Flag(id);
    if(Mul_Flag == -1)
    {
        ui->comboBoxLineIndex->setEnabled(false);
    }else
    {
        ui->comboBoxLineIndex->setCurrentIndex(Point_Or_Line_Result_Id_Change_UI_Id(id,i_result_index));
    }
    measure_ref_line_result_get(i_task_index,i_result_index,(void*)&pLinePara,1);
    QLine line;
    Line_Osd_Init(&pLinePara,&line);
    ((FWLineFlawLabel*)m_label)->SetLine(line);
    m_i_load_first = 1;
}

/**
 * @brief LineFlawWidget::InitData
 * @author dgq
 * @note 初始化界面显示
 */
void LineFlawWidget::InitData()
{
    int ret = 0;
    float fret;


    ret = pInputPara->flaw_check_dir;
    if(ret>=0 && ret <=3)
        ui->comboBoxDir->setCurrentIndex(ret);

    ret = pInputPara->flaw_check_type;
    if(ret>=0 && ret <=2)
        ui->comboBoxTestType->setCurrentIndex(ret);

    ret =pInputPara->flaw_num_max;
    ui->txtLineNum->setText(QString::number(ret));

    fret = pInputPara->flaw_level_low_th;
    ui->txtLineStrength->setText(QString::number(fret));

    ret = pInputPara->flaw_length_low_th;
    ui->txtLineLength->setText(QString::number(ret));

    fret = pInputPara->flaw_area_low_th;
    ui->txtLineFlawArea->setText(QString::number(fret));


    //获取缺陷强度上门限使能 0：不使能，1使能
    if(pInputPara->flaw_level_threshold.high_enable == 1){
        fret = pInputPara->flaw_level_threshold.high_threshold;
        ui->txtFlawLevelHigh->setText(QString::number(fret));
    }else{
        ui->txtFlawLevelHigh->setText("---");
    }

    //获取缺陷强度下门限使能 0：不使能，1使能
    if(pInputPara->flaw_level_threshold.low_enable == 1){
        fret = pInputPara->flaw_level_threshold.low_threshold;
        ui->txtFlawLevelLow->setText(QString::number(fret));
    }else{
        ui->txtFlawLevelLow->setText("---");
    }

    //获取缺陷长度上门限使能 0：不使能，1使能
    if(pInputPara->flaw_length_total_threshold.high_enable == 1){
        ret = pInputPara->flaw_length_total_threshold.high_threshold;
        ui->txtFlawLengthHigth->setText(QString::number(ret));
    }else{
        ui->txtFlawLengthHigth->setText("---");
    }

    //获取缺陷长度下门限使能 0：不使能，1使能
    if(pInputPara->flaw_length_total_threshold.low_enable == 1){
        ret = pInputPara->flaw_length_total_threshold.low_threshold;
        ui->txtFlawLengthLow->setText(QString::number(ret));
    }else{
        ui->txtFlawLengthLow->setText("---");
    }

    //获取缺陷总面积上门限使能 0：不使能，1使能
    if(pInputPara->flaw_area_total_threshold.high_enable == 1){
        fret = pInputPara->flaw_area_total_threshold.high_threshold;
        ui->txtFlawAreaHigh->setText(QString::number(fret));
    }else{
        ui->txtFlawAreaHigh->setText("---");
    }

    //获取缺陷总面积下门限使能 0：不使能，1使能
    if(pInputPara->flaw_area_total_threshold.low_enable == 1){
        fret = pInputPara->flaw_area_total_threshold.low_threshold;
        ui->txtFlawAreaLow->setText(QString::number(fret));
    }else{
        ui->txtFlawAreaLow->setText("---");
    }

    //获取缺陷总数上门限使能 0：不使能，1使能
    if(pInputPara->flaw_count_threshold.high_enable == 1){
        ret = pInputPara->flaw_count_threshold.high_threshold;
        ui->txtFlawNumHigh->setText(QString::number(ret));
    }else{
        ui->txtFlawNumHigh->setText("---");
    }
    //获取缺陷总数下门限使能 0：不使能，1使能
    if(pInputPara->flaw_count_threshold.low_enable == 1){
        ret = pInputPara->flaw_count_threshold.low_threshold;
        ui->txtFlawNumLow->setText(QString::number(ret));
    }else{
        ui->txtFlawNumLow->setText("---");
    }

}

/**
 * @brief LineFlawWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void LineFlawWidget::LoadKeyBoardLib()
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
 * @brief LineFlawWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器，文本编辑框模拟点击事件
 */
bool LineFlawWidget::eventFilter(QObject *watched, QEvent *event)
{
//    if(!((QLineEdit*)watched)->isEnabled() || ((QLineEdit*)watched)->isReadOnly())
//        return QWidget::eventFilter(watched, event);
    if(watched == ui->txtLineFlawArea)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ParamInputPro(-1920*1920,640*480,ui->txtLineFlawArea);
        }
    }else if(watched == ui->txtLineLength)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ParamInputPro(-1920*1920,640*480,ui->txtLineLength);
        }
    }else if(watched == ui->txtLineNum)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ParamInputPro(0,100,ui->txtLineNum);
        }
    }else if(watched == ui->txtLineStrength)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ParamInputPro(-1920*1920,640*480,ui->txtLineStrength);
        }
    }else if(watched == ui->txtFlawAreaHigh)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawAreaHigh,ui->txtFlawAreaLow,1);
        }
    }else if(watched == ui->txtFlawAreaLow)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawAreaHigh,ui->txtFlawAreaLow,0);
        }
    }else if(watched == ui->txtFlawLengthHigth)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawLengthHigth,ui->txtFlawLengthLow,1);
        }
    }else if(watched == ui->txtFlawLengthLow)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawLengthHigth,ui->txtFlawLengthLow,0);
        }
    }else if(watched == ui->txtFlawLevelHigh)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawLevelHigh,ui->txtFlawLevelLow,1);
        }
    }else if(watched == ui->txtFlawLevelLow)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawLevelHigh,ui->txtFlawLevelLow,0);
        }
    }else if(watched == ui->txtFlawNumHigh)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawNumHigh,ui->txtFlawNumLow,1);
        }
    }else if(watched == ui->txtFlawNumLow)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            ThresholdInputPro(ui->txtFlawNumHigh,ui->txtFlawNumLow,0);
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief LineFlawWidget::ParamInputPro
 * @param iMin 最小值
 * @param iMax 最大值
 * @param pEdit 文本框对象指针
 * @author dgq
 * @note 文本框输入响应函数
 */
void LineFlawWidget::ParamInputPro(int iMin,int iMax,QLineEdit *pEdit)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        QDialog *Numkey = GetNumKeyBoardDlg();
        int ret = Numkey->exec();
        if(ret== QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if( num.toInt()>=iMin && num.toInt()<= iMax)
                {
                    pEdit->setText(num);
                }
                else
                {
                    QString strTemp;
                    if(iMin != iMax){
                        strTemp = tr("请输入")+QString::number(iMin)+tr("到")+QString::number(iMax)+tr("之间数");
                    }else{
                        strTemp = tr("请输入正确的数值");
                    }
                    QMessageBox::information(NULL,tr("提示"),strTemp);
                }
            }
        }
    }
}

/**
 * @brief LineFlawWidget::ThresholdInputPro
 * @param pEditMax 上限输入框对象指针
 * @param pEditMin 下限输入框对象指针
 * @param flag 上下限标志位，1上限，0下限
 * @author Vincent
 * @note 门限值输入响应函数
 */
void LineFlawWidget::ThresholdInputPro(QLineEdit *pEditMax,QLineEdit *pEditMin,int flag)
{
    QLineEdit * pEdit;
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");

    if (flag == THRESHOLD_LOW) {
        pEdit = pEditMin;
    } else {
        pEdit = pEditMax;
    }

    if(pEdit->text() != "---"){
        SetRangeInput(pEditMax->text(),pEditMin->text(),flag);
    }else{
        SetRangeInput(pEditMax->text(),pEditMax->text(),flag);
    }
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        pEdit->setText(GetRangeNum());
    }
}

/**
 * @brief LineFlawWidget::SetDataToLib
 * @author dgq
 * @note 将界面参数写入到内存
 */
void LineFlawWidget::SetDataToLib()
{
    int ret = 0;
    float fret;
    ret = ui->comboBoxDir->currentIndex();
    pInputPara->flaw_check_dir = ret;
    ret = ui->comboBoxTestType->currentIndex();
    pInputPara->flaw_check_type = ret;
    //设置最大检测个数
    ret = ui->txtLineNum->text().toInt();
    pInputPara->flaw_num_max = ret;
    //设置缺陷强度门限
    fret = ui->txtLineStrength->text().toFloat();
    pInputPara->flaw_level_low_th = fret;
    //设置缺陷段长
    ret = ui->txtLineLength->text().toInt();
    pInputPara->flaw_length_low_th = ret;
    //设置缺陷量
    fret = ui->txtLineFlawArea->text().toFloat();
    pInputPara->flaw_area_low_th = fret;

    //设置缺陷强度上门限使能 0：不使能，1使能
    if(ui->txtFlawLevelHigh->text() == "---"){
        pInputPara->flaw_level_threshold.high_enable = 0;
    }else{
        pInputPara->flaw_level_threshold.high_enable = 1;
        fret =ui->txtFlawLevelHigh->text().toFloat();
        pInputPara->flaw_level_threshold.high_threshold = fret;
    }

    //设置缺陷强度下门限使能 0：不使能，1使能
    if(ui->txtFlawLevelLow->text() == "---"){
        pInputPara->flaw_level_threshold.low_enable = 0;
    }else{
        pInputPara->flaw_level_threshold.low_enable = 1;
        fret = ui->txtFlawLevelLow->text().toFloat();
        pInputPara->flaw_level_threshold.low_threshold = fret;
    }


    //设置缺陷长度上门限使能 0：不使能，1使能
    if(ui->txtFlawLengthHigth->text() == "---"){
        pInputPara->flaw_length_total_threshold.high_enable = 0;
    }else{
        pInputPara->flaw_length_total_threshold.high_enable = 1;
        ret = ui->txtFlawLengthHigth->text().toInt();
        pInputPara->flaw_length_total_threshold.high_threshold = ret;
    }

    //设置缺陷长度下门限使能 0：不使能，1使能
    if(ui->txtFlawLengthLow->text() == "---"){
        pInputPara->flaw_length_total_threshold.low_enable = 0;
    }else{
        pInputPara->flaw_length_total_threshold.low_enable = 1;
        ret = ui->txtFlawLengthLow->text().toInt();
        pInputPara->flaw_length_total_threshold.low_threshold = ret;
    }


    //设置缺陷总面积上门限使能 0：不使能，1使能
    if(ui->txtFlawAreaHigh->text() == "---"){
        pInputPara->flaw_area_total_threshold.high_enable = 0;
    }else{
        pInputPara->flaw_area_total_threshold.high_enable = 1;
        fret =ui->txtFlawAreaHigh->text().toFloat();
        pInputPara->flaw_area_total_threshold.high_threshold = fret;
    }

    //设置缺陷总面积下门限使能 0：不使能，1使能
    if(ui->txtFlawAreaLow->text() == "---"){
        pInputPara->flaw_area_total_threshold.low_enable = 0;
    }else{
        pInputPara->flaw_area_total_threshold.low_enable = 1;
        fret = ui->txtFlawAreaLow->text().toFloat();
        pInputPara->flaw_area_total_threshold.low_threshold = fret;
    }

    //设置缺陷总数上门限使能 0：不使能，1使能
    if(ui->txtFlawNumHigh->text() == "---"){
        pInputPara->flaw_count_threshold.high_enable = 0;
    }else{
        pInputPara->flaw_count_threshold.high_enable = 1;
        ret = ui->txtFlawNumHigh->text().toInt();
        pInputPara->flaw_count_threshold.high_threshold = ret;
    }

    //设置缺陷总数下门限使能 0：不使能，1使能
    if(ui->txtFlawNumLow->text() == "---"){
        pInputPara->flaw_count_threshold.low_enable = 0;
    }else{
        pInputPara->flaw_count_threshold.low_enable = 1;
        ret = ui->txtFlawNumLow->text().toInt();
        pInputPara->flaw_count_threshold.low_threshold = ret;
    }
}

/**
 * @brief LineFlawWidget::Line_Paint_Base_On_KB_SubPixel
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点的子函数
 */
int LineFlawWidget::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
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
 * @brief LineFlawWidget::Line_Osd_Init
 * @param pLinePara
 * @param pOsdLine
 * @return
 * @author dgq
 * @note 根据点斜式换算出直线跟640*480显示区域边界的两个交点
 */
int LineFlawWidget::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
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
 * @brief LineFlawWidget::on_btnCalculation_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void LineFlawWidget::on_btnCalculation_clicked()
{
    Set_Parameter_To_Ram();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief LineFlawWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程定时器响应函数
 */
void LineFlawWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        SetTableData();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

/**
 * @brief LineFlawWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样过程进度条的弹窗库
 */
void LineFlawWidget::LoadLearnLib()
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
 * @brief LineFlawWidget::CleaTable
 * @author dgq
 * @note 创建表格
 */
void LineFlawWidget::CleaTable()
{
    int iLen = ui->tableWidget_CalcResult->rowCount();
    for(int i=0;i<iLen;i++)
    {
        ui->tableWidget_CalcResult->removeRow(i);
    }
}

/**
 * @brief LineFlawWidget::SetTableData
 * @author dgq
 * @note 设置表格的数据显示
 */
void LineFlawWidget::SetTableData()
{
    QStringList header;
    LINE_FLAW_PRIVATE_PARAM * pPrivate = (LINE_FLAW_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);

    unsigned int sum_Area = 0;          ///< 缺陷总面积
    QVector<unsigned int> Flaw_Length;  ///< 缺陷段数
    QVector<float> Flaw_Area;           ///< 缺陷面积
    QVector<float> Flaw_Level;          ///< 缺陷等级
    QVector<QPoint> Flaw_Point;         ///< 缺陷坐标

    Flaw_Length.clear();
    Flaw_Area.clear();
    Flaw_Level.clear();
    Flaw_Point.clear();
    sum_Area = pPrivate->model_line_flaw_rst.flaw_area_sum;

    for(unsigned int i = 0; i < pPrivate->model_line_flaw_rst.flaw_cnt; i++)
    {
        Flaw_Length.append(pPrivate->model_line_flaw_rst.flaw_info[i].flaw_length);
        Flaw_Area.append(pPrivate->model_line_flaw_rst.flaw_info[i].flaw_area);
        Flaw_Level.append(pPrivate->model_line_flaw_rst.flaw_info[i].flaw_level);
        Flaw_Point.append(QPoint(pPrivate->model_line_flaw_rst.flaw_info[i].flaw_pos_pixel.x_f,
                                 pPrivate->model_line_flaw_rst.flaw_info[i].flaw_pos_pixel.y_f));
    }

    int num = Flaw_Length.count();
    ui->label_FlawNum->setText(QString::number(num));
    ui->tableWidget_CalcResult->setRowCount(num);
    int i;
    for(i = 0; i < num; i++)
    {
        header.append(QString::number(i+1));
    }
    ui->tableWidget_CalcResult->setVerticalHeaderLabels(header);
    unsigned int flawMin = 0;
    unsigned int flawMax = 0;

    if(num > 0)
    {
        flawMin = Flaw_Length[0];
        flawMax = Flaw_Length[0];
    }
    int sum_flaw = 0;
    for(i = 0; i < Flaw_Length.count();i++)
    {
        sum_flaw = sum_flaw+Flaw_Length[i];
        if(Flaw_Length[i]<flawMin)
        {
            flawMin = Flaw_Length[i];
        }
        if(Flaw_Length[i] > flawMax)
        {
            flawMax = Flaw_Length[i];
        }

        ui->tableWidget_CalcResult->setItem(i,0,new QTableWidgetItem(QString::number(Flaw_Length[i])));
    }
    if(Flaw_Length.count() > 0){
        ui->label_FlawLength->setText(QString::number(sum_flaw));
    }

    float areaMin = 0;
    float areaMax = 0;
    if(num > 0)
    {
        areaMin = abs(Flaw_Area[0]);
        areaMax = abs(Flaw_Area[0]);
    }
    for(i = 0; i < Flaw_Area.count();i++)
    {
        if(abs(Flaw_Area[i])<abs(areaMin))
        {
            areaMin = Flaw_Area[i];
        }
        if(abs(Flaw_Area[i]) > abs(areaMax))
        {
            areaMax = Flaw_Area[i];
        }
        ui->tableWidget_CalcResult->setItem(i,1,new QTableWidgetItem(QString::number(Flaw_Area[i])));
    }
    float levelMin = 0;
    float levelMax = 0;
    if(num > 0)
    {
        levelMin = abs(Flaw_Level[0]);
        levelMax = abs(Flaw_Level[0]);
    }
    float sum_level = 0;
    for(i = 0; i < Flaw_Level.count();i++)
    {
        sum_level = sum_level + Flaw_Level[i];
        if(abs(Flaw_Level[i])<abs(levelMin))
        {
            levelMin = Flaw_Level[i];
        }
        if(abs(Flaw_Level[i]) > abs(levelMax))
        {
            levelMax = Flaw_Level[i];
        }
        ui->tableWidget_CalcResult->setItem(i,2,new QTableWidgetItem(QString::number(Flaw_Level[i])));
    }
    if(Flaw_Level.count() > 0)
    {
        ui->label_FlawLevel->setText(QString::number(sum_level/Flaw_Level.count(),'f',3));
    }

    ui->label_FlawArea->setText(QString::number(sum_Area));
    ui->labelTotalArea->setText(QString::number(sum_Area));
    ui->labelTotal->setText(QString::number(num));
    ui->labelFlawMin->setText(QString::number(flawMin));
    ui->labelFlawMax->setText(QString::number(flawMax));

    ui->labelAreaMin->setText(QString::number(areaMin,'f',2));
    ui->labelAreaMax->setText(QString::number(areaMax,'f',2));

    ui->labelLevelMin->setText(QString::number(levelMin,'f',2));
    ui->labelLevelMax->setText(QString::number(levelMax,'f',2));
    Get_Result_From_Ram();

}

void LineFlawWidget::Get_Result_From_Ram()
{
    LINE_FLAW_PRIVATE_PARAM * pPrivate = (LINE_FLAW_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    QVector<QPoint> points;
    points.clear();
    int flaw_cnt = pPrivate->model_line_flaw_rst.flaw_cnt;
    for(int i = 0 ; i < flaw_cnt; i++)
    {
        POINT_F point_sub = pPrivate->model_line_flaw_rst.flaw_info[i].flaw_pos_pixel;
        POINT_I point_vga;
        PixelCvt(&point_sub,&point_vga,CVT_REAL2VGA|CVT_F2I|CVT_POINT);
        points.append(QPoint(point_vga.x_i,point_vga.y_i));
    }

    ((FWLineFlawLabel *)m_label)->SetOSDData(points);
}

/**
 * @brief LineFlawWidget::on_btnNextPage_clicked
 * @note 下一页
 */
void LineFlawWidget::on_btnNextPage_clicked()
{
    if(ui->stackedWidget->currentIndex() < ui->stackedWidget->count()-1)
    {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
}


/**
 * @brief LineFlawWidget::on_btnPrePage_clicked
 * @note 上一页
 */
void LineFlawWidget::on_btnPrePage_clicked()
{
    if(ui->stackedWidget->currentIndex() > 0)
    {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    }
    ui->label_CurrentIndex->setText(QString::number(ui->stackedWidget->currentIndex()+1));
    ui->label_AllIndex->setText(QString::number(ui->stackedWidget->count()));
}

/**
 * @brief LineFlawWidget::on_comboBoxLineStep_activated
 * @param index
 * @author dgq
 * @note 直线任务下拉框改变的响应函数
 */
void LineFlawWidget::on_comboBoxLineStep_activated(int index)
{
    ((FWLineFlawLabel*)m_label)->SetLine(QLine(0,0,0,0));
    if(m_i_load_first == 1)
    {
        int task_index = atoi(ui->comboBoxLineStep->currentText().toStdString().c_str());
        if(task_index == 0)
        {
            ui->comboBoxLineIndex->clear();
            return;
        }
        ui->comboBoxLineIndex->setEnabled(true);

        ui->comboBoxLineIndex->clear();
        ui->comboBoxLineIndex->addItem(" ");
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
                ui->comboBoxLineIndex->addItem(strLineIndex);
            }
        }
        else
        {
            LineParameter pLinePara;
            ui->comboBoxLineIndex->setEnabled(false);

            int ret = measure_ref_line_result_get(task_index,Point_Or_Line_Result_Id_Change_UI_Id(id,0),(void*)&pLinePara,1);
            if(ret != 0)
            {
                QString info = tr("获取失败!")+tr("错误码:")+QString::number(ret,16);
                QMessageBox::about(this,tr(""),info);
                return;
            }
            QLine line;
            Line_Osd_Init(&pLinePara,&line);
            ((FWLineFlawLabel*)m_label)->SetLine(line);
        }
    }
}

/**
 * @brief LineFlawWidget::on_comboBoxLineIndex_activated
 * @param index
 * @author dgq
 * @note 直线结果下拉框改变的响应函数
 */
void LineFlawWidget::on_comboBoxLineIndex_activated(int index)
{
    if(m_i_load_first ==1)
    {
        LineParameter pLinePara;
        int Task_index = atoi(ui->comboBoxLineStep->currentText().toStdString().c_str());
        int Result_index = ui->comboBoxLineIndex->currentIndex();
        if(Result_index == 0)
        {
            ((FWLineFlawLabel*)m_label)->SetLine(QLine(0,0,0,0));
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
        ((FWLineFlawLabel*)m_label)->SetLine(line);
    }
}
