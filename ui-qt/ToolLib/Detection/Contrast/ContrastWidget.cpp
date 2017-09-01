#include <QDebug>
#include <QMessageBox>
#include "ContrastWidget.h"
#include "ui_ContrastWidget.h"
#include "TaskStepGlobal.h"
#include "FWContrastLabel.h"

ContrastWidget::ContrastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContrastWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    ui->HighThreshold->installEventFilter(this);
    ui->LowThreshold->installEventFilter(this);
    m_label = new FWContrastLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &ContrastWidget::CalcTimerSlot);
}

ContrastWidget::~ContrastWidget()
{
    ui->HighThreshold->removeEventFilter(this);
    ui->LowThreshold->removeEventFilter(this);

    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}

/**
 * @brief ContrastWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint ContrastWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

/**
 * @brief ContrastWidget::InitData
 * @author dgq
 * @note 初始化界面显示
 */
void ContrastWidget::InitData()
{
    int i_num = 0;

    if(pInputPara->valid_contrast_range.high_enable){
        i_num = pInputPara->valid_contrast_range.high_threshold;
        ui->HighThreshold->setText(QString::number(i_num));
    }

    if(pInputPara->valid_contrast_range.low_enable){
        i_num = pInputPara->valid_contrast_range.low_threshold;
        ui->LowThreshold->setText(QString::number(i_num));
    }

    CONTRAST_PRIVATE_PARAM *pPrivate = NULL;
    pPrivate = (CONTRAST_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    i_num = pPrivate->model_contrast_rst.contrast;
    ui->ModelContrastLabel->setText(QString::number(i_num));

}

/**
 * @brief ContrastWidget::Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void ContrastWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (CONTRAST_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->valid_contrast_range.high_enable = 0;
        pInputPara->valid_contrast_range.low_enable = 0;
    }
    InitData();

}

/**
 * @brief ContrastWidget::SetParamtoRam
 * @return
 * @author dgq
 * @note 将界面数据写入内存
 */
int ContrastWidget::SetParamtoRam()
{
    if(ui->HighThreshold->text() == "---"){
        pInputPara->valid_contrast_range.high_enable = 0;
    }else{
        pInputPara->valid_contrast_range.high_enable = 1;
        pInputPara->valid_contrast_range.high_threshold = ui->HighThreshold->text().toInt();
    }

    if(ui->LowThreshold->text() == "---"){
        pInputPara->valid_contrast_range.low_enable = 0;
    }else{
        pInputPara->valid_contrast_range.low_enable = 1;
        pInputPara->valid_contrast_range.low_threshold = ui->LowThreshold->text().toInt();
    }
    return 0;
}

/**
 * @brief ContrastWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 取样
 */
int ContrastWidget::Set_Parameter_To_Ram()
{
    if(pInputPara == NULL)
    {
        return 0;
    }
    SetParamtoRam();
    return 1;
}

/**
 * @brief ContrastWidget::on_ContrastCalc_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void ContrastWidget::on_ContrastCalc_clicked()
{
    Set_Parameter_To_Ram();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief ContrastWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程定时器响应函数
 */
void ContrastWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        int i_range = 0;
        CONTRAST_PRIVATE_PARAM *pPrivate = NULL;
        pPrivate = (CONTRAST_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
        i_range = pPrivate->model_contrast_rst.contrast;
        ui->ModelContrastLabel->setText(QString::number(i_range));
        if(ui->checkBox_AutoSet->isChecked())
        {
            int iXMax ;
            int iXMin;
            iXMax = i_range*1.2;
            iXMin = i_range*0.8;
            if(iXMax > 100)
                iXMax = 100;
            ui->HighThreshold->setText(QString::number(iXMax));
            ui->LowThreshold->setText(QString::number(iXMin));
        }
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

/**
 * @brief ContrastWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样过程的进度条弹窗库
 */
void ContrastWidget::LoadLearnLib()
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
 * @brief ContrastWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author dgq
 * @note 事件过滤器，行文本框模拟点击数件
 */
bool ContrastWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->HighThreshold)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(ui->LowThreshold->text() != "---")
            {
                NumKeyBoardDlg(watched, event, ui->LowThreshold->text().toInt(), 255);
            }
            else
            {
                NumKeyBoardDlg(watched, event, 0, 255);
            }
        }
    }
    if(watched == ui->LowThreshold)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(ui->HighThreshold->text() != "---")
            {
                NumKeyBoardDlg(watched, event, 0, ui->HighThreshold->text().toInt());
            }
            else
            {
                NumKeyBoardDlg(watched, event, 0, 255);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief ContrastWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void ContrastWidget::LoadKeyBoardLib()
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
 * @brief ContrastWidget::NumKeyBoardDlg
 * @param watched
 * @param event
 * @param Min_value
 * @param Max_value
 * @author th
 * @note 行文本框输入响应函数
 */
void ContrastWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
{

    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        Numkey = GetNumKeyBoardDlg();
        ShowRangeEn RangEn = (ShowRangeEn)m_keyBoard_Lib.resolve("SetRangeEnvBtn");
        if(RangEn)
        {
            RangEn();
        }
        else
        {
            return;
        }
        int ret = Numkey->exec();
        if(ret == QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if(num.toInt() > Max_value || num.toInt() < Min_value)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                    return;
                }
                ((QLineEdit *)watched)->setText(num);
            }
        }
        delete Numkey;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}
