#include "GrayStatisticsWidget.h"
#include "ui_GrayStatisticsWidget.h"
#include "FWGrayStatisticsLabel.h"
#include "QMessageBox"
#include <QDebug>

GrayStatisticsWidget::GrayStatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrayStatisticsWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
    }
    m_label = new FWGrayStatisticsLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    m_i_load_first  = 0;
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &GrayStatisticsWidget::CalcTimerSlot);

}

GrayStatisticsWidget::~GrayStatisticsWidget()
{
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->removeEventFilter(this);
    }

    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}

/**
 * @brief GrayStatisticsWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint GrayStatisticsWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

/**
 * @brief GrayStatisticsWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int GrayStatisticsWidget::Set_Parameter_To_Ram()
{
    SetDataToLib();
    return 1;
}

/**
 * @brief GrayStatisticsWidget::Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void GrayStatisticsWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (GRAY_STAT_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
//    qDebug()<<__func__<<" m_step_index:"<<m_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }

    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->pixel_num_threshold.high_enable = 0;
        pInputPara->pixel_num_threshold.low_enable = 0;
    }
    InitData();
}

/**
 * @brief GrayStatisticsWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器，行文本框模拟点击事件
 */
bool GrayStatisticsWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->validPixelMax){
        if (event->type()==QEvent::MouseButtonPress){
            GrayStatisticsMaxInputPro();
        }
    }
    if(watched == ui->validPixelMin){
        if (event->type()==QEvent::MouseButtonPress){
            GrayStatisticsMinInputPro();
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief GrayStatisticsWidget::on_btnCalculate_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void GrayStatisticsWidget::on_btnCalculate_clicked()
{
    SetDataToLib();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief GrayStatisticsWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程定时器响应函数
 */
void GrayStatisticsWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        GetDataFromLib();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

/**
 * @brief GrayStatisticsWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样过程进度条弹窗库
 */
void GrayStatisticsWidget::LoadLearnLib()
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
 * @brief GrayStatisticsWidget::InitData
 * @author dgq
 * @note 初始化界面显示
 */
void GrayStatisticsWidget::InitData()
{
    int value;
    if(pInputPara->pixel_num_threshold.high_enable == 1){
        value = pInputPara->pixel_num_threshold.high_threshold;
        ui->validPixelMax->setText(QString::number(value));
    }else{
        ui->validPixelMax->setText("---");
    }
    if(pInputPara->pixel_num_threshold.low_enable == 1){
        value = pInputPara->pixel_num_threshold.low_threshold;
        ui->validPixelMin->setText(QString::number(value));
    }else{
        ui->validPixelMin->setText("---");
    }
}

/**
 * @brief GrayStatisticsWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void GrayStatisticsWidget::LoadKeyBoardLib()
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
 * @brief GrayStatisticsWidget::GrayStatisticsMinInputPro
 * @author dgq
 * @note 文本编辑框输入响应函数
 */
void GrayStatisticsWidget::GrayStatisticsMinInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = \
            (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
    if(ui->validPixelMin->text() != "---"){
        SetRangeInput(ui->validPixelMax->text(),ui->validPixelMin->text(),0);
    }else{
        SetRangeInput(ui->validPixelMax->text(),ui->validPixelResult->text(),0);
    }
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        ui->validPixelMin->setText(GetRangeNum());
    }
}

/**
 * @brief GrayStatisticsWidget::GrayStatisticsMaxInputPro
 * @author dgq
 * @note 文本编辑框输入响应函数
 */
void GrayStatisticsWidget::GrayStatisticsMaxInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = \
            (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
    if(ui->validPixelMax->text() != "---"){
        SetRangeInput(ui->validPixelMax->text(),ui->validPixelMin->text(),1);
    }else{
        SetRangeInput(ui->validPixelResult->text(),ui->validPixelMin->text(),1);
    }
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        ui->validPixelMax->setText(GetRangeNum());
    }
}

/**
 * @brief GrayStatisticsWidget::SetDataToLib
 * @author dgq
 * @note 将界面数据写入内存
 */
void GrayStatisticsWidget::SetDataToLib()
{
    int value = 0;
    //上门限使能(1:使能； 0：不使能)
    if(ui->validPixelMax->text() == "---"){
        pInputPara->pixel_num_threshold.high_enable = 0;
    }else{
        pInputPara->pixel_num_threshold.high_enable = 1;
        value = ui->validPixelMax->text().toInt();
        pInputPara->pixel_num_threshold.high_threshold = value;
    }

    //下门限使能(1:使能； 0：不使能)
    if(ui->validPixelMin->text() == "---"){
        pInputPara->pixel_num_threshold.low_enable = 0;
    }else{
        pInputPara->pixel_num_threshold.low_enable = 1;
        value = ui->validPixelMin->text().toInt();
        pInputPara->pixel_num_threshold.low_threshold = value;
    }
}

/**
 * @brief GrayStatisticsWidget::GetDataFromLib
 * @author dgq
 * @note 从内存获取计算结果更新界面显示
 */
void GrayStatisticsWidget::GetDataFromLib()
{
    GRAY_STAT_PRIVATE_PARAM *pPrivate = \
            (GRAY_STAT_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
//    qDebug() << __func__ << " m_step_index:" << m_step_index;
    int ok_ng_flag = pPrivate->model_stat_rst.detect_ok_ng_flag;
    if(ok_ng_flag != 0)
    {
        QMessageBox::about(this,tr("提示"),tr("检测失败!"));
        return;
    }
    unsigned int i_area = pPrivate->model_stat_rst.pixel_num;
    ui->validPixelResult->setText(QString::number(i_area));
    if(ui->checkBoxAutoSet->isChecked())
    {
        int imax = i_area*1.2;
        int imin = i_area*0.8;
        ui->validPixelMax->setText(QString::number(imax));
        ui->validPixelMin->setText(QString::number(imin));
    }
}
